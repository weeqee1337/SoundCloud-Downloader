//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include <Winapi.Windows.hpp>
#include <System.IOUtils.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Winapi.ShellAPI.hpp>
#include <vector>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnFolderClick(TObject *Sender)
{
    String folder = EditFolder->Text;

	if (SelectDirectory(L"Select download folder", L"", folder)) {
        EditFolder->Text = folder;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnDownloadClick(TObject *Sender)
{
    String url = Trim(EditURL->Text);
    String folder = Trim(EditFolder->Text);

    bool validURL =
        url.Pos(L"https://soundcloud.com/") == 1 ||
        url.Pos(L"https://www.soundcloud.com/") == 1;

    if (!validURL ||
        url.Pos(L"\"") > 0 ||
        url.Pos(L"\r") > 0 ||
        url.Pos(L"\n") > 0 ||
		url.Pos(L" ") > 0) {
        ShowMessage(L"Please enter a valid SoundCloud URL.");
        return;
    }

	if (folder.IsEmpty()) {
        ShowMessage(L"Please select a download folder.");
        return;
    }

    Form2->StartDownload(
        url,
        folder,
        ComboFormat->ItemIndex,
        ComboBrowser->ItemIndex,
        CheckArchive->Checked
    );
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if (!DownloadProcess)
		return;

	DWORD code = STILL_ACTIVE;

	if (!GetExitCodeProcess(DownloadProcess, &code)) {
        Timer1->Enabled = false;
		CloseHandle(DownloadProcess);
		DownloadProcess = nullptr;
		BtnDownload->Enabled = true;
		return;
    }

	if (code != STILL_ACTIVE) {
        Timer1->Enabled = false;
        CloseHandle(DownloadProcess);
        DownloadProcess = nullptr;
		BtnDownload->Enabled = true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    EditFolder->Text = TPath::Combine(
	TPath::GetDocumentsPath(), L"SoundCloud");
	CheckArchive->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BtnAboutClick(TObject *Sender)
{
int result = MessageDlg(
        L"SoundCloud Downloader\n"
        L"Version 1.0.0\n\n"
        L"Third-party software:\n"
        L"yt-dlp - Media downloading engine\n"
		L"FFmpeg - Audio conversion and processing\n",
		mtInformation,
        TMsgDlgButtons() << mbYes << mbNo, 0);

    if (result == mrYes)
    {
        ShellExecuteW(
            0, L"open",
            L"https://github.com/yt-dlp/yt-dlp",
            nullptr, nullptr, SW_SHOWNORMAL
        );

        ShellExecuteW(
            0, L"open",
            L"https://ffmpeg.org/",
            nullptr, nullptr, SW_SHOWNORMAL
        );
	}
}
//---------------------------------------------------------------------------

