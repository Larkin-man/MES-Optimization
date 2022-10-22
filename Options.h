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
     TRadioGroup *RadioGroupFi;
     TRadioGroup *ColorOptions;
     TCheckBox *WorkTimeOut;
     TTabSheet *TabSheet4;
     TCheckBox *CheckBox1;
     TCheckBox *CheckBox2;
     TRadioGroup *MVGModify;
     TCheckBox *HeightScaling;
     void __fastcall NoOutClick(TObject *Sender);
     void __fastcall FormShow(TObject *Sender);
     void __fastcall RadioGroupFiClick(TObject *Sender);
     void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations

public:		// User declarations
     __fastcall TOptionsForm(TComponent* Owner);
     bool Cvetpit;


     void ShowOptimization(bool OptimizatinWindow)
     {
          //Окно опции
          TabSheet1->TabVisible = !OptimizatinWindow;
          TabSheet2->TabVisible = !OptimizatinWindow;
          TabSheet3->TabVisible = !OptimizatinWindow;
          TabSheet1->Enabled = !OptimizatinWindow;
          TabSheet2->Enabled = !OptimizatinWindow;
          TabSheet3->Enabled = !OptimizatinWindow;
          //Окно оптимизации

          TabSheet4->TabVisible = OptimizatinWindow;
          TabSheet4->Enabled = OptimizatinWindow;

     }
};
//---------------------------------------------------------------------------
extern PACKAGE TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
#endif
