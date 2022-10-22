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
__fastcall TEnterDataForm::TEnterDataForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//�������� �����
void __fastcall TEnterDataForm::FormShow(TObject *Sender)
{
     if (BitBtnOkResize->Visible)
     {
          EnterDataForm->Field1->EditLabel->Caption="���-�� �����";
          EnterDataForm->Field2->EditLabel->Caption="���-�� ��������";
          Field1->Text="";
          Field2->Text="";
     }
     if (BitBtnOkRandom->Visible)
     {
          EnterDataForm->Field1->EditLabel->Caption="���-�� �������";
          EnterDataForm->Field2->EditLabel->Caption="���-�� �������";
          if (BaseForm->M > 2)
          {
               Field1->Text=IntToStr(BaseForm->M);
               Field2->Text=IntToStr(BaseForm->N);
          }
          else
          {
               Field1->Text="4";
               Field2->Text="3";
          }
     }
     BitBtnOkResize->Default=BitBtnOkResize->Visible;
     BitBtnOkRandom->Default=BitBtnOkRandom->Visible;
     Field1->SetFocus();
}
//---------------------------------------------------------------------------
//��������� ������� �������
void __fastcall TEnterDataForm::BitBtnOkResizeClick(TObject *Sender)
{
     if (EnterDataForm->Field1->Text.operator!=(""))
          BaseForm->Table->RowCount=StrToInt(EnterDataForm->Field1->Text)+1;
     if (EnterDataForm->Field2->Text != "")
          BaseForm->Table->ColCount=StrToInt(EnterDataForm->Field2->Text)+1;
     BaseForm->TableRefresh();
     if ((BaseForm->Table->RowCount-1) < (BaseForm->M))
     {
          BaseForm->M = BaseForm->Table->RowCount-1;
          BaseForm->StatusBar1->Panels->Items[2]->Text=("�������: "+IntToStr(BaseForm->M));
     }
     if ((BaseForm->Table->ColCount-1) < (BaseForm->N))
     {
          BaseForm->N = BaseForm->Table->ColCount-1;
          BaseForm->StatusBar1->Panels->Items[1]->Text=("�������: "+IntToStr(BaseForm->N));
     }
     Close();
}
//---------------------------------------------------------------------------
//���������� ���������� �������
void __fastcall TEnterDataForm::BitBtnOkRandomClick(TObject *Sender)
{
     for (int i=1;i<BaseForm->Table->RowCount;i++)
          for (int j=1;j<BaseForm->Table->ColCount;j++)
               BaseForm->Table->Cells[j][i]="";

     if (EnterDataForm->Field1->Text.operator!=(""))
          BaseForm->M=StrToInt(EnterDataForm->Field1->Text);
     if (EnterDataForm->Field2->Text != "")
          BaseForm->N=StrToInt(EnterDataForm->Field2->Text);

     if (BaseForm->Table->RowCount < BaseForm->M+1)
          BaseForm->Table->RowCount = BaseForm->M+1;
     if (BaseForm->Table->ColCount < BaseForm->N+1)
          BaseForm->Table->ColCount = BaseForm->N+1;
     BaseForm->TableRefresh();
     srand(time(NULL));
	for (int i = 1; i < BaseForm->M+1; i++)
          for (int j = 1; j < BaseForm->N+1; j++)
	     {
		     BaseForm->Table->Cells[j][i] = rand() % 10 + 1;  //1-10
	     }
     BaseForm->StatusBar1->Panels->Items[0]->Text=("��������� ���������� �������");
     BaseForm->Ready();
}
//---------------------------------------------------------------------------

void __fastcall TEnterDataForm::Field1Exit(TObject *Sender)
{
     CheckConvert((TLabeledEdit*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TEnterDataForm::Field2Exit(TObject *Sender)
{
     CheckConvert((TLabeledEdit*)Sender);
}
//---------------------------------------------------------------------------

void __fastcall TEnterDataForm::BitBtn2Click(TObject *Sender)
{
     Close();
}
//---------------------------------------------------------------------------

