//----------------------------------------------------------------------------
#ifndef AboutH
#define AboutH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <jpeg.hpp>
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
