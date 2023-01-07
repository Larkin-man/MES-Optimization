//----------------------------------------------------------------------------
#ifndef AboutH
#define AboutH
//----------------------------------------------------------------------------
#include <jpeg.hpp>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.StdCtrls.hpp>
//----------------------------------------------------------------------------
class TAboutForm : public TForm
{
__published:
	TPanel *AboutPanel;
	TImage *ProgramIcon;
	TLabel *ProductName;
	TLabel *Version;
	TLabel *Copyright;
	TLabel *Comments;
	TButton *OKButton;
	TLabel *Company;
	TLabel *Comment2;
	TLabel *Comment3;
private:
public:
	virtual __fastcall TAboutForm(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAboutForm *AboutForm;
//----------------------------------------------------------------------------
#endif
