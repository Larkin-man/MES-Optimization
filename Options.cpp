//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Options.h"
#include "MainSource.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
__fastcall TOptionsForm::TOptionsForm(TComponent* Owner)
     : TForm(Owner)
{
     Label1->Caption="";
     //OptimizationWindow=false;
     TabSheet3->Enabled=false;
          //TabSheet4->Hide();
     ShowOptimization(false);
     Cvetpit=ColorOptions->ItemIndex;

}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::NoOutClick(TObject *Sender)
{
     if (NoOut->Checked)
          Label1->Caption="Во время работы алгоритма данные не будут выводится на экран";
     else
          Label1->Caption="";
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::FormShow(TObject *Sender)
{
     Label1->Caption="";
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::RadioGroupFiClick(TObject *Sender)
{
     if (RadioGroupFi->ItemIndex == 0)
          Label1->Caption="В этом несовершенство метода ветвей и границ";
     else
          Label1->Caption="";
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::WorkTimeOutClick(TObject *Sender)
{
     if (OptionsForm->Visible == false)
          WorkTimeOut->Checked = true;
     if(WorkTimeOut->Checked)
     {
          BaseForm->scale=22;
     }
     else
     {
          BaseForm->scale=18;
     }
     delete BaseForm->Gant;
     BaseForm->Gant = new Graphics::TBitmap;
     BaseForm->PaintGant();

}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
     ShowOptimization(false);
     //ShowMessage("On Close");
}
//---------------------------------------------------------------------------



