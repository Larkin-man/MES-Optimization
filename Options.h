//---------------------------------------------------------------------------

#ifndef OptionsH
#define OptionsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TOptionsForm : public TForm
{
__published:	// IDE-managed Components
     TPageControl *PageControl;
     TTabSheet *TabSheet1;
     TTabSheet *TabSheet2;
     TCheckBox *Debug;
     TRadioGroup *RadioGroupTime;
     TTabSheet *TabSheet3;
     TGroupBox *GroupBox1;
     TCheckBox *NoOut;
     TBitBtn *BitBtn1;
     TBitBtn *BitBtn2;
     TLabel *Label1;
     TRadioGroup *RadioGroupGant;
     TRadioGroup *RadioGroupFi;
     void __fastcall NoOutClick(TObject *Sender);
     void __fastcall FormShow(TObject *Sender);
     void __fastcall RadioGroupFiClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
     __fastcall TOptionsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
#endif
