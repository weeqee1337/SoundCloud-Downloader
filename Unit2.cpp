//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
#include <System.IOUtils.hpp>
#include <System.SysUtils.hpp>
#include <vector>
#include <cwchar>
#include <cstdlib>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
void __fastcall TForm2::StartDownload(const String &url, const String &folder, int format, int browser, bool useArchive)
{
    if (DownloadProcess)
        return;

    String appDir = ExtractFilePath(Application->ExeName);
    String exe = TPath::Combine(appDir, L"yt-dlp.exe");

    if (!FileExists(exe)) {
        ShowMessage(L"yt-dlp.exe was not found.");
        return;
    }

    if (format == 0 &&
        (!FileExists(TPath::Combine(appDir, L"ffmpeg.exe")) ||
		 !FileExists(TPath::Combine(appDir, L"ffprobe.exe")))) {
        ShowMessage(L"FFmpeg files were not found.");
        return;
    }

	if (!ForceDirectories(folder)) {
        ShowMessage(L"Unable to create download folder.");
        return;
    }

	String args =
		L"--ignore-config "
		L"--yes-playlist "
		L"--no-simulate "
		L"--newline "
		L"--progress "
		L"--encoding utf-8 "
		L"--windows-filenames "
		L"--trim-filenames 180 "
		L"--progress-template "
		L"\"download:SC_PROGRESS|%(progress._percent_str)s|%(progress._speed_str)s\" "
		L"--print \"before_dl:SC_TRACK|%(title)s\" "
		L"--print \"after_move:SC_DONE|%(title)s\" ";

    if (format == 0)
        args += L"-x --audio-format mp3 --audio-quality 0 --embed-metadata ";
    else
        args += L"-f bestaudio ";

    if (useArchive)
        args += L"--download-archive \"downloaded.txt\" ";

	switch (browser) {
        case 1:
            args += L"--cookies-from-browser opera ";
            break;
        case 2:
            args += L"--cookies-from-browser chrome ";
            break;
        case 3:
            args += L"--cookies-from-browser firefox ";
            break;
    }

    args += L"-o \"%(uploader)s - %(title)s.%(ext)s\" ";
    args += L"\"" + url + L"\"";

    SECURITY_ATTRIBUTES sa = {};
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;

    HANDLE readPipe = nullptr;
    HANDLE writePipe = nullptr;

	if (!CreatePipe(&readPipe, &writePipe, &sa, 0)) {
        ShowMessage(L"Failed to create output pipe.");
        return;
    }

    if (!SetHandleInformation(
		readPipe, HANDLE_FLAG_INHERIT, 0)) {
        CloseHandle(readPipe);
        CloseHandle(writePipe);
        ShowMessage(L"Failed to configure output pipe.");
        return;
    }

    HANDLE nullInput = CreateFileW(
        L"NUL",
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        &sa,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

	if (nullInput == INVALID_HANDLE_VALUE) {
        CloseHandle(readPipe);
        CloseHandle(writePipe);
        ShowMessage(L"Failed to initialize process input.");
        return;
    }

    STARTUPINFOW si = {};
    PROCESS_INFORMATION pi = {};

    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = writePipe;
    si.hStdError = writePipe;
    si.hStdInput = nullInput;

    String command = L"\"" + exe + L"\" " + args;

    std::vector<wchar_t> cmd(
        command.c_str(),
        command.c_str() + command.Length() + 1
    );

    BOOL success = CreateProcessW(
        exe.c_str(),
        cmd.data(),
        nullptr,
        nullptr,
        TRUE,
        CREATE_NO_WINDOW | CREATE_SUSPENDED,
        nullptr,
        folder.c_str(),
        &si,
        &pi
    );

    CloseHandle(writePipe);
    CloseHandle(nullInput);

	if (!success) {
        CloseHandle(readPipe);
        ShowMessage(
            L"Failed to start downloader. Error: " +
            IntToStr((int)GetLastError())
        );
        return;
    }

    DownloadJob = CreateJobObjectW(nullptr, nullptr);

	if (DownloadJob)  {
        JOBOBJECT_EXTENDED_LIMIT_INFORMATION info = {};

        info.BasicLimitInformation.LimitFlags =
            JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;

        if (!SetInformationJobObject(
                DownloadJob,
                JobObjectExtendedLimitInformation,
                &info,
                sizeof(info)) ||
            !AssignProcessToJobObject(
				DownloadJob, pi.hProcess)) {
            CloseHandle(DownloadJob);
            DownloadJob = nullptr;
        }
    }

	if (ResumeThread(pi.hThread) == (DWORD)-1) {
        TerminateProcess(pi.hProcess, 1);

        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        CloseHandle(readPipe);

		if (DownloadJob) {
            CloseHandle(DownloadJob);
            DownloadJob = nullptr;
        }

        ShowMessage(L"Failed to resume downloader.");
        return;
    }

    CloseHandle(pi.hThread);

    DownloadProcess = pi.hProcess;
    OutputPipe = readPipe;

	PendingOutput.clear();
	LastError = L"";
    CompletedTracks = 0;
    StopRequested = false;

    LabelTrack->Caption = L"Fetching track information...";
    LabelStatus->Caption = L"Starting...";
    LabelPercent->Caption = L"0%";
    LabelSpeed->Caption = L"Speed: —";
    LabelCount->Caption = L"0";

    ProgressBar1->Position = 0;
    BtnCancel->Enabled = true;
    Timer1->Enabled = true;

    ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ProcessLine(const String &line)
{
	if (line.Pos(L"SC_TRACK|") == 1) {
        LabelTrack->Caption =
            line.SubString(10, line.Length());

        LabelStatus->Caption = L"Downloading...";
        LabelPercent->Caption = L"0%";
        LabelSpeed->Caption = L"Speed: —";
        ProgressBar1->Position = 0;
        return;
    }

	if (line.Pos(L"SC_PROGRESS|") == 1) {
        String data = line.SubString(13, line.Length());
        int separator = data.Pos(L"|");

		if (separator > 0) {
            String percent = Trim(
                data.SubString(1, separator - 1)
            );

            String speed = Trim(
                data.SubString(separator + 1, data.Length())
            );

            String number = StringReplace(
                percent, L"%", L"", TReplaceFlags()
            );

            double value = std::wcstod(
                number.c_str(), nullptr
            );

            if (value < 0) value = 0;
            if (value > 100) value = 100;

            ProgressBar1->Position = (int)(value * 10);
            LabelPercent->Caption = percent;

            if (speed.IsEmpty() || speed == L"NA")
                LabelSpeed->Caption = L"Speed: —";
            else
                LabelSpeed->Caption = L"Speed: " + speed;
        }

        return;
    }

	if (line.Pos(L"SC_DONE|") == 1) {
		CompletedTracks++;

        LabelCount->Caption =
            IntToStr(CompletedTracks);

        LabelStatus->Caption = L"Track completed";
        LabelPercent->Caption = L"100%";
        LabelSpeed->Caption = L"Speed: —";
        ProgressBar1->Position = 1000;
        return;
    }

	if (line.Pos(L"[ExtractAudio]") == 1) {
        LabelStatus->Caption = L"Converting audio...";
        return;
    }

	if (line.Pos(L"ERROR:") > 0) {
		LastError = line;
		LabelStatus->Caption = L"Download error";
		return;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm2::ReadOutput()
{
    if (!OutputPipe)
        return;

    char buffer[4096];

	for (int i = 0; i < 64; i++) {
        DWORD available = 0;

        if (!PeekNamedPipe(
            OutputPipe, nullptr, 0,
            nullptr, &available, nullptr))
            break;

        if (available == 0)
            break;

        DWORD toRead = available < sizeof(buffer)
            ? available : sizeof(buffer);

        DWORD bytesRead = 0;

        if (!ReadFile(
            OutputPipe, buffer, toRead,
            &bytesRead, nullptr) || bytesRead == 0)
            break;

        PendingOutput.append(buffer, bytesRead);

        size_t pos;

        while ((pos = PendingOutput.find('\n'))
			   != std::string::npos) {
            std::string raw =
                PendingOutput.substr(0, pos);

            PendingOutput.erase(0, pos + 1);

            if (!raw.empty() && raw.back() == '\r')
                raw.pop_back();

            UTF8String utf8(raw.c_str());
            ProcessLine(UTF8ToString(utf8));
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FinishDownload(DWORD exitCode)
{
    Timer1->Enabled = false;

    ReadOutput();

	if (!PendingOutput.empty()) {
        UTF8String utf8(PendingOutput.c_str());
        ProcessLine(UTF8ToString(utf8));
        PendingOutput.clear();
    }

	if (DownloadProcess) {
        CloseHandle(DownloadProcess);
        DownloadProcess = nullptr;
    }

	if (OutputPipe) {
        CloseHandle(OutputPipe);
        OutputPipe = nullptr;
    }

	if (DownloadJob) {
        CloseHandle(DownloadJob);
        DownloadJob = nullptr;
    }

    BtnCancel->Enabled = false;

	if (StopRequested) {
        LabelStatus->Caption = L"Download cancelled";
        ModalResult = mrCancel;
    }
	else if (exitCode == 0) {
        LabelStatus->Caption = L"Download completed";
		ModalResult = mrOk;
	}

else {
    LabelStatus->Caption = L"Download failed";

    String message = L"Download failed.";

    if (!LastError.IsEmpty())
        message += L"\n\n" + LastError;
    else
        message += L"\nExit code: " +
                   IntToStr((int)exitCode);

    ShowMessage(message);

    ModalResult = mrAbort;
}
}
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Timer1Timer(TObject *Sender)
{
    if (!DownloadProcess)
        return;

    ReadOutput();

    DWORD result = WaitForSingleObject(
        DownloadProcess, 0
    );

    if (result == WAIT_TIMEOUT)
        return;

    if (result != WAIT_OBJECT_0)
        return;

    DWORD exitCode = 1;

    GetExitCodeProcess(
        DownloadProcess, &exitCode
    );

    FinishDownload(exitCode);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BtnCancelClick(TObject *Sender)
{
	if (!DownloadProcess) {
        ModalResult = mrCancel;
        return;
    }

    StopRequested = true;
    BtnCancel->Enabled = false;
    LabelStatus->Caption = L"Cancelling...";

    BOOL stopped = FALSE;

    if (DownloadJob)
        stopped = TerminateJobObject(DownloadJob, 1);

    if (!stopped)
        stopped = TerminateProcess(DownloadProcess, 1);

    if (!stopped)
        LabelStatus->Caption = L"Unable to cancel";
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if (DownloadProcess) {
        CanClose = false;

        if (!StopRequested)
            BtnCancelClick(Sender);
    }
}
//---------------------------------------------------------------------------
