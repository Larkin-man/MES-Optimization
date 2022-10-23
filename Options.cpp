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
     Info->Caption="";
     //OptimizationWindow=false;
          //TabSheet4->Hide();
     ShowOptimization(false);
     Cvetpit=ColorOptions->ItemIndex;
     //MVGModify->ItemIndex=MVGModify->Items->Count-1;
     BitBtn1Click(NULL);
}
//---------------------------------------------------------------------------
//ПОКАЗАТЬ ФОРМУ
void __fastcall TOptionsForm::FormShow(TObject *Sender)
{
     Info->Caption="";
     SpinBrightness->Enabled=ColorOptions->ItemIndex;
     Contrast->Visible=(SpinBrightness->Value>=150);
     SpinBI->Value=BaseForm->BI;
     SpinBI->MaxValue=BaseForm->BH;
     if (SpinBrightness->Value<50)
          Contrast->Checked=false;
}
//---------------------------------------------------------------------------
//Отключить вывод данных - OnClick
void __fastcall TOptionsForm::NoOutClick(TObject *Sender)
{
     if (NoOut->Checked)
     {
          Info->Caption="Во время расчета данные не будут выводится на экран";
          Debug->Checked=false;
     }
     else
          Info->Caption="";
     Debug->Enabled=!NoOut->Checked;
}
//---------------------------------------------------------------------------
//Закрыть форму
void __fastcall TOptionsForm::FormClose(TObject *Sender, TCloseAction &Action)
{
     ShowOptimization(false);
     //ShowMessage("On Close");
}
//---------------------------------------------------------------------------
//Изменение яркости
void __fastcall TOptionsForm::SpinBrightnessChange(TObject *Sender)
{
     Info->Caption="С увеличением яркости снижается контрастность \n";
}
//---------------------------------------------------------------------------
//Использовать случайный цвет
void __fastcall TOptionsForm::ColorOptionsClick(TObject *Sender)
{
     SpinBrightness->Enabled=ColorOptions->ItemIndex;
     GraphicForm->N4->Checked=ColorOptions->ItemIndex;
     GraphicForm->NChangeColor->Enabled=ColorOptions->ItemIndex;
}
//---------------------------------------------------------------------------
//Проверка
void __fastcall TOptionsForm::OpenCheckChange(TObject *Sender)
{
     if (OpenCheck->Value==0)
          Info->Caption="Проверка отключена";
     else
          Info->Caption="";
}
//---------------------------------------------------------------------------
//Масштабировать высоту - OnClick
void __fastcall TOptionsForm::HeightScalingClick(TObject *Sender)
{
     SpinBI->Enabled=!HeightScaling->Checked;
}
//---------------------------------------------------------------------------
//Ограничить снизу максимальное
void __fastcall TOptionsForm::RandomFromChange(TObject *Sender)
{
     RandomTo->MinValue=RandomFrom->Value+1;
}
//---------------------------------------------------------------------------
//Ограничить сверху минимальное
void __fastcall TOptionsForm::RandomToChange(TObject *Sender)
{
     RandomFrom->MaxValue=RandomTo->Value-1;
}
//---------------------------------------------------------------------------
void __fastcall TOptionsForm::BitBtn1Click(TObject *Sender)
{
   OptionBool[0]=NoOut->Checked;
   OptionBool[1]=Debug->Checked;
      OptionInt[0]=OpenCheck->Value;
      OptionInt[1]=RandomFrom->Value;
      OptionInt[2]=RandomTo->Value;  //--------
   OptionBool[2]=MvgIdleAll->Checked;
      OptionInt[3]=MVGModify->ItemIndex;
   OptionBool[3]=WorkTimeOut->Checked;
   OptionBool[4]=ColorOptions->ItemIndex;
      OptionInt[4]=SpinBrightness->Value;
   OptionBool[5]=Contrast->Checked;
   OptionBool[6]=HeightScaling->Checked;
      OptionInt[5]=SpinBI->Value;
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::BitBtn2Click(TObject *Sender)
{
   NoOut->Checked=OptionBool[0];
   Debug->Checked=OptionBool[1];
      OpenCheck->Value=OptionInt[0];
      RandomFrom->Value=OptionInt[1];
      RandomTo->Value=OptionInt[2];  //--------
   MvgIdleAll->Checked=OptionBool[2];
      MVGModify->ItemIndex=OptionInt[3];
   WorkTimeOut->Checked=OptionBool[3];
   ColorOptions->ItemIndex=OptionBool[4];
      SpinBrightness->Value=OptionInt[4];
   Contrast->Checked=OptionBool[5];
   HeightScaling->Checked=OptionBool[6];
      SpinBI->Value=OptionInt[5];
}
//---------------------------------------------------------------------------

