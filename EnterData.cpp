//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "EnterData.h"

//---------------------------------------------------------------------------
#include "MainSource.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TEnterDataForm *EnterDataForm;
int res1;
//---------------------------------------------------------------------------
__fastcall TEnterDataForm::TEnterDataForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TEnterDataForm::Edit1Change(TObject *Sender)
{
//SpeedButton1->Enabled=Edit1->Text.operator!=("");
}
//---------------------------------------------------------------------------

void __fastcall TEnterDataForm::FormShow(TObject *Sender)
{
Field1->Text="";
Field2->Text="";
Field1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TEnterDataForm::Field1Change(TObject *Sender)
{
//     SpeedButton1->Enabled=(StrToInt(Form2->Field1->Text) >0);
}
//---------------------------------------------------------------------------

void __fastcall TEnterDataForm::BitBtn1Click(TObject *Sender)
{
     if (EnterDataForm->Field1->Text.operator!=(""))
          BaseForm->Table->RowCount=StrToInt(EnterDataForm->Field1->Text)+1;
     if (EnterDataForm->Field2->Text != "")
          BaseForm->Table->ColCount=StrToInt(EnterDataForm->Field2->Text)+1;
     for (int i=1;i<BaseForm->Table->RowCount;i++)
          BaseForm->Table->Cells[0][i]="Деталь " + IntToStr(i)+":";
     for (int j=1;j<BaseForm->Table->ColCount;j++)
          BaseForm->Table->Cells[j][0]=j;//"Станок №"+i;
     Close();
}
//---------------------------------------------------------------------------

void __fastcall TEnterDataForm::BitBtn2Click(TObject *Sender)
{
     Close();
}
//---------------------------------------------------------------------------

