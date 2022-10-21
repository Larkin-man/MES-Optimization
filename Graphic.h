//---------------------------------------------------------------------------

#ifndef GraphicH
#define GraphicH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>

//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
     TCoolBar *CoolBar1;
     TImage *gant;
private:	// User declarations
public:		// User declarations
     __fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------

#endif
