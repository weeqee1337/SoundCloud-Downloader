//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TEdit *EditURL;
	TEdit *EditFolder;
	TButton *BtnFolder;
	TButton *BtnDownload;
	TComboBox *ComboFormat;
	TComboBox *ComboBrowser;
	TCheckBox *CheckArchive;
	TTimer *Timer1;
	TGroupBox *FormatGroup;
	TGroupBox *AuthenticationGroup;
	TGroupBox *URLGroup;
	TGroupBox *DirectoryGroup;
	TButton *BtnAbout;
	TImageList *ImageList1;
	TGroupBox *GroupBox1;
	void __fastcall BtnFolderClick(TObject *Sender);
	void __fastcall BtnDownloadClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtnAboutClick(TObject *Sender);
private:	// User declarations
	HANDLE DownloadProcess = nullptr;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
