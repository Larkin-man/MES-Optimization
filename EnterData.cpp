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

void __fastcall TEnterDataForm::FormShow(TObject *Sender)
{
     if (BitBtnOkResize->Visible)
     {
          EnterDataForm->Field1->EditLabel->Caption="Кол-во строк";
          EnterDataForm->Field2->EditLabel->Caption="Кол-во столбцов";
          Field1->Text="";
          Field2->Text="";
     }
     if (BitBtnOkRandom->Visible)
     {
          EnterDataForm->Field1->EditLabel->Caption="Кол-во деталей";
          EnterDataForm->Field2->EditLabel->Caption="Кол-во станков";
          Field1->Text="4";
          Field2->Text="3";
     }
     BitBtnOkResize->Default=BitBtnOkResize->Visible;
     BitBtnOkRandom->Default=BitBtnOkRandom->Visible;
     Field1->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TEnterDataForm::BitBtnOkResizeClick(TObject *Sender)
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

void __fastcall TEnterDataForm::BitBtnOkRandomClick(TObject *Sender)
{
     for (int i=1;i<BaseForm->Table->RowCount;i++)
          for (int j=1;j<BaseForm->Table->ColCount;j++)
               BaseForm->Table->Cells[j][i]="";
     BaseForm->M=StrToInt(EnterDataForm->Field1->Text);
     BaseForm->N=StrToInt(EnterDataForm->Field2->Text);
     srand(time(NULL));
	for (int i = 1; i < BaseForm->M+1; i++)
          for (int j = 1; j < BaseForm->N+1; j++)
	     {
		     BaseForm->Table->Cells[j][i] = rand() % 10 + 1;  //1-10
	     }
     BaseForm->Ready();
}
//---------------------------------------------------------------------------

