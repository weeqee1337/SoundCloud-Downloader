//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Winapi.Windows.hpp>
#include <string>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TLabel *LabelTrack;
	TLabel *LabelStatus;
	TLabel *LabelPercent;
	TLabel *LabelSpeed;
	TLabel *LabelCount;
	TProgressBar *ProgressBar1;
	TButton *BtnCancel;
	TTimer *Timer1;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TLabel *LabelText1;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall BtnCancelClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
    HANDLE DownloadProcess = nullptr;
    HANDLE OutputPipe = nullptr;
    HANDLE DownloadJob = nullptr;
    String LastError;
    std::string PendingOutput;

    int CompletedTracks = 0;
    bool StopRequested = false;

    void __fastcall ReadOutput();
    void __fastcall ProcessLine(const String &line);
	void __fastcall FinishDownload(DWORD exitCode);
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
    void __fastcall StartDownload(
    const String &url,
    const String &folder,
    int format,
    int browser,
    bool useArchive
);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
