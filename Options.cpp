//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Options.h"
#include "MainSource.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TOptionsForm *OptionsForm;
//---------------------------------------------------------------------------
__fastcall TOptionsForm::TOptionsForm(TComponent* Owner) : TForm(Owner)
{
     Label1->Caption="";
     //OptimizationWindow=false;
          //TabSheet4->Hide();
     ShowOptimization(false);
     Cvetpit=ColorOptions->ItemIndex;
     //MVGModify->ItemIndex=MVGModify->Items->Count-1;
}
//---------------------------------------------------------------------------
//�������� �����
void __fastcall TOptionsForm::FormShow(TObject *Sender)
{
     Label1->Caption="";
     SpinBrightness->Enabled=ColorOptions->ItemIndex;
     Contrast->Visible=(SpinBrightness->Value>=150);
     SpinBI->Value=BaseForm->BI;
     SpinBI->MaxValue=BaseForm->BH;
     if (SpinBrightness->Value<50)
          Contrast->Checked=false;
}
//---------------------------------------------------------------------------
//��������� ����� ������ - OnClick
void __fastcall TOptionsForm::NoOutClick(TObject *Sender)
{
     if (NoOut->Checked)
          Label1->Caption="�� ����� ������ ��������� ������ �� ����� ��������� �� �����";
     else
          Label1->Caption="";
     Debug->Enabled=!NoOut->Checked;
}
//---------------------------------------------------------------------------
//������� �����
void __fastcall TOptionsForm::FormClose(TObject *Sender, TCloseAction &Action)
{
     ShowOptimization(false);
     //ShowMessage("On Close");
}
//---------------------------------------------------------------------------
//��������� �������
void __fastcall TOptionsForm::SpinBrightnessChange(TObject *Sender)
{
     Label1->Caption="� ����������� ������� ��������� ������������� \n";
}
//---------------------------------------------------------------------------
//������������ ��������� ����
void __fastcall TOptionsForm::ColorOptionsClick(TObject *Sender)
{
     SpinBrightness->Enabled=ColorOptions->ItemIndex;
}
//---------------------------------------------------------------------------
//��������
void __fastcall TOptionsForm::OpenCheckChange(TObject *Sender)
{
     if (OpenCheck->Value==0)
          Label1->Caption="�������� ���������";
}
//---------------------------------------------------------------------------
//�������������� ������ - OnClick
void __fastcall TOptionsForm::HeightScalingClick(TObject *Sender)
{
     SpinBI->Enabled=!HeightScaling->Checked;
}
//---------------------------------------------------------------------------
//���������� ����� ������������
void __fastcall TOptionsForm::RandomFromChange(TObject *Sender)
{
     RandomTo->MinValue=RandomFrom->Value+1;
}
//---------------------------------------------------------------------------
//���������� ������ �����������
void __fastcall TOptionsForm::RandomToChange(TObject *Sender)
{
     RandomFrom->MaxValue=RandomTo->Value-1;
}
//---------------------------------------------------------------------------

