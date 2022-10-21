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
     if(WorkTimeOut->Checked)
     {
          BaseForm->scale=22;
     }
     else
     {
          BaseForm->scale=18;
     }
     BaseForm->PaintGant();

}
//---------------------------------------------------------------------------

