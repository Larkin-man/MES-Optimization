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
#include "AdvSpin.hpp"
#include <Mask.hpp>
#include <CheckLst.hpp>
//---------------------------------------------------------------------------
class TOptionsForm : public TForm
{
__published:	// IDE-managed Components
     TPageControl *PageControl;
   TTabSheet *TabSheetGeneral;
   TTabSheet *TabSheetMMVG;
   TTabSheet *TabSheetGant;
   TBitBtn *BitBtnOK;
   TBitBtn *BitBtnCancel;
   TLabel *Info;
     TRadioGroup *ColorOptions;
     TCheckBox *WorkTimeOut;
   TTabSheet *TabSheetOptim;
   TCheckBox *Crit4;
   TCheckBox *Crit3;
     TRadioGroup *MVGModify;
     TCheckBox *HeightScaling;
   TLabel *LabelBR;
     TCheckBox *Contrast;
   TLabel *LabelBI;
   TGroupBox *GroupBoxRandom;
   TGroupBox *GroupBoxReport;
     TCheckBox *NoOut;
     TCheckBox *MvgIdleAll;
     TCheckBox *Debug;
   TAdvSpinEdit *RandomFrom;
   TAdvSpinEdit *RandomTo;
   TAdvSpinEdit *SpinBI;
   TAdvSpinEdit *SpinBrightness;
   TCheckBox *OpenCheck;
   TCheckBox *Crit1;
   TCheckBox *Crit2;
   TCheckBox *Crit5;
   TCheckBox *Crit6;
     void __fastcall NoOutClick(TObject *Sender);
     void __fastcall FormShow(TObject *Sender);
     void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
     void __fastcall SpinBrightnessChange(TObject *Sender);
     void __fastcall ColorOptionsClick(TObject *Sender);
     void __fastcall HeightScalingClick(TObject *Sender);
   void __fastcall BitBtnOKClick(TObject *Sender);
   void __fastcall BitBtnCancelClick(TObject *Sender);
   void __fastcall RandomFromChange(TObject *Sender);
   void __fastcall RandomToChange(TObject *Sender);
   void __fastcall Crit1Click(TObject *Sender);
   void __fastcall Crit2Click(TObject *Sender);
private:	// User declarations

public:		// User declarations
     __fastcall TOptionsForm(TComponent* Owner);
     bool Cvetpit;
     bool OptionBool[9];
     int OptionInt[6];
     void __fastcall ShowOptimization(bool OptimizatinWindow);
};
//---------------------------------------------------------------------------
extern PACKAGE TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
#endif
