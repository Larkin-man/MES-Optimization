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
#include "CSPIN.h"
//---------------------------------------------------------------------------
class TOptionsForm : public TForm
{
__published:	// IDE-managed Components
     TPageControl *PageControl;
     TTabSheet *TabSheet1;
     TTabSheet *TabSheet2;
     TTabSheet *TabSheet3;
     TBitBtn *BitBtn1;
     TBitBtn *BitBtn2;
   TLabel *Info;
     TRadioGroup *ColorOptions;
     TCheckBox *WorkTimeOut;
     TTabSheet *TabSheet4;
     TCheckBox *Criterion1;
     TCheckBox *Criterion2;
     TRadioGroup *MVGModify;
     TCheckBox *HeightScaling;
     TCSpinEdit *SpinBrightness;
     TLabel *Label2;
     TCheckBox *Contrast;
     TCSpinEdit *OpenCheck;
     TLabel *Label3;
     TCSpinEdit *SpinBI;
     TLabel *Label4;
     TGroupBox *GroupBox2;
     TLabel *Label5;
     TCSpinEdit *RandomFrom;
     TLabel *Label6;
     TCSpinEdit *RandomTo;
     TGroupBox *GroupBox1;
     TCheckBox *NoOut;
     TCheckBox *MvgIdleAll;
     TCheckBox *Debug;
     void __fastcall NoOutClick(TObject *Sender);
     void __fastcall FormShow(TObject *Sender);
     void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
     void __fastcall SpinBrightnessChange(TObject *Sender);
     void __fastcall ColorOptionsClick(TObject *Sender);
     void __fastcall OpenCheckChange(TObject *Sender);
     void __fastcall HeightScalingClick(TObject *Sender);
     void __fastcall RandomFromChange(TObject *Sender);
     void __fastcall RandomToChange(TObject *Sender);
   void __fastcall BitBtn1Click(TObject *Sender);
   void __fastcall BitBtn2Click(TObject *Sender);
private:	// User declarations

public:		// User declarations
     __fastcall TOptionsForm(TComponent* Owner);
     bool Cvetpit;
     bool OptionBool[8];
     int OptionInt[6];


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
