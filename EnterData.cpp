//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "EnterData.h"
//---------------------------------------------------------------------------
#include "MainSource.h"
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TEnterDataForm *EnterDataForm;
//---------------------------------------------------------------------------
__fastcall TEnterDataForm::TEnterDataForm(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//�������� �����
void __fastcall TEnterDataForm::FormShow(TObject *Sender)
{    Field1->SetFocus();      }
//---------------------------------------------------------------------------
//�������� ��������� ��������
void __fastcall TEnterDataForm::Field1Exit(TObject *Sender)
{    CheckConvert((TLabeledEdit*)Sender);    }
void __fastcall TEnterDataForm::Field2Exit(TObject *Sender)
{    CheckConvert((TLabeledEdit*)Sender);    }
//---------------------------------------------------------------------------

void __fastcall TEnterDataForm::BitBtn2Click(TObject *Sender)
{    Close();       }
//---------------------------------------------------------------------------
//�������� ���������� ��������
void __fastcall TEnterDataForm::Field1Change(TObject *Sender)
{    if (Result == random)
          BitBtnOk->Enabled=!((Field1->Text=="") && (Field2->Text==""));
}
void __fastcall TEnterDataForm::Field2Change(TObject *Sender)
{    if (Result == random)
          BitBtnOk->Enabled=!((Field1->Text=="") && (Field2->Text==""));
}
//---------------------------------------------------------------------------

void __fastcall TEnterDataForm::BitBtnOkClick(TObject *Sender)
{
//��������� ������� �������
if (Result == resize)
{
     if (Field1->Text.operator!=(""))
          BaseForm->Table->RowCount=(StrToInt(EnterDataForm->Field1->Text)+1);
     if (Field2->Text != "")
          BaseForm->Table->ColCount=StrToInt(EnterDataForm->Field2->Text)+1;
     BaseForm->TableRefresh();
     bool NMchange=false;
     if ((BaseForm->Table->RowCount-1) < (BaseForm->M))
     {
          BaseForm->M = BaseForm->Table->RowCount-1;
          NMchange=true;
     }
     if ((BaseForm->Table->ColCount-1) < (BaseForm->N))
     {
          BaseForm->N = BaseForm->Table->ColCount-1;
          NMchange=true;
     }
     if (NMchange)
          BaseForm->Swapf();
     Close();
}

//���������� ���������� �������
if (Result == random)
{
     CheckConvert(Field1);
     CheckConvert(Field2);
     if ((Field1->Text=="") && (Field2->Text==""))
          return;
     for (int i=1;i<BaseForm->Table->RowCount;i++)
          for (int j=1;j<BaseForm->Table->ColCount;j++)
               BaseForm->Table->Cells[j][i]="";

     if (Field1->Text != "")
          BaseForm->M=StrToInt(EnterDataForm->Field1->Text);
     if (Field2->Text != "")
          BaseForm->N=StrToInt(EnterDataForm->Field2->Text);

     if (BaseForm->Table->RowCount < BaseForm->M+1)
          BaseForm->Table->RowCount = BaseForm->M+1;
     if (BaseForm->Table->ColCount < BaseForm->N+1)
          BaseForm->Table->ColCount = BaseForm->N+1;
     BaseForm->TableRefresh();
     srand(time(NULL));
     int max=OptionsForm->RandomTo->Value;
     int min=OptionsForm->RandomFrom->Value;
	for (int i = 1; i < BaseForm->M+1; i++)
          for (int j = 1; j < BaseForm->N+1; j++)
	     {
		     BaseForm->Table->Cells[j][i] = rand() % (max-min+1) + min;  //From min to max
	     }
     BaseForm->StatusBar1->Panels->Items[0]->Text=("��������� ���������� �������");
     BaseForm->Swapf();
     Close();
}

//���������� ���� ������
if (Result == color)
{
     CheckConvert(Field1);
     if (Field1->Text=="")
          return;
     int det = StrToInt(Field1->Text);
     if (det <= BaseForm->ColorSave)
     {
          BaseForm->ColorBox[det-1]=Field2->Color;
          BaseForm->PaintGant();
     }
     Field2->Color=clWindow;
     Field2->Cursor=crDefault;
     Close();
}
}
//---------------------------------------------------------------------------
//����� �����
void __fastcall TEnterDataForm::Field2Click(TObject *Sender)
{
     if (Result == color)
     {
          Field2->OnExit(NULL);
          ColorDialog1->Execute();
          Field2->Color=ColorDialog1->Color;
          Field2->Text="";
          Field1->SetFocus();
     }
}
//---------------------------------------------------------------------------

