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
__fastcall TOptionsForm::TOptionsForm(TComponent* Owner) : TForm(Owner)
{
	Info->Caption="";
	ShowOptimization(false);
	Cvetpit=ColorOptions->ItemIndex;
	BitBtnOKClick(NULL);
}
//---------------------------------------------------------------------------
//ПОКАЗАТЬ ФОРМУ
void __fastcall TOptionsForm::FormShow(TObject *Sender)
{
	Info->Caption="";
	SpinBrightness->Enabled=ColorOptions->ItemIndex;
	Contrast->Visible=(SpinBrightness->Position >= 150);
	SpinBI->Position=BaseForm->BI;
	SpinBI->Max=BaseForm->BH;
	if (SpinBrightness->Position<50)
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
	GraphicForm->NColorBlock->Checked=ColorOptions->ItemIndex;
	GraphicForm->NChangeColor->Enabled=ColorOptions->ItemIndex;
}
//---------------------------------------------------------------------------
//Масштабировать высоту - OnClick
void __fastcall TOptionsForm::HeightScalingClick(TObject *Sender)
{
	SpinBI->Enabled=!HeightScaling->Checked;
}
//---------------------------------------------------------------------------
//Управление отображением
void __fastcall TOptionsForm::ShowOptimization(bool OptimizatinWindow)
{
	//Окно опции
	TabSheetGeneral->TabVisible = !OptimizatinWindow;
	TabSheetMMVG->TabVisible = !OptimizatinWindow;
	TabSheetGant->TabVisible = !OptimizatinWindow;
	TabSheetGeneral->Enabled = !OptimizatinWindow;
	TabSheetMMVG->Enabled = !OptimizatinWindow;
	TabSheetGant->Enabled = !OptimizatinWindow;
	//Окно оптимизации
	TabSheetOptim->TabVisible = OptimizatinWindow;
	TabSheetOptim->Enabled = OptimizatinWindow;
}
//---------------------------------------------------------------------------
//Кнопка ОК - Сохранение настроек
void __fastcall TOptionsForm::BitBtnOKClick(TObject *Sender)
{
	OptionBool[0]=NoOut->Checked;
	OptionBool[1]=Debug->Checked;
	//OptionInt[0]=OpenCheck->Position;  удалил опцию
	OptionInt[1]=RandomFrom->Position;
	OptionInt[2]=RandomTo->Position;  //--------
	//OptionBool[2]=MvgIdleAll->Checked;
	OptionInt[3]=MVGModify->ItemIndex;
	OptionBool[3]=WorkTimeOut->Checked;
	OptionBool[4]=ColorOptions->ItemIndex;
	OptionInt[4]=SpinBrightness->Position;
	OptionBool[5]=Contrast->Checked;
	OptionBool[6]=HeightScaling->Checked;
	OptionInt[5]=SpinBI->Position;
	OptionBool[7]=OpenCheck->Checked;
	OptionBool[8]=MvgMore->Checked;
	OptionBool[9]=NoMiddle->Checked;
}
//---------------------------------------------------------------------------
//Кнопка Cancel - Отмена всех изменений
void __fastcall TOptionsForm::BitBtnCancelClick(TObject *Sender)
{
	NoOut->Checked=OptionBool[0];
	Debug->Checked=OptionBool[1];
	//OpenCheck->Position=OptionInt[0];
	RandomFrom->Position=OptionInt[1];
	RandomTo->Position=OptionInt[2];  //--------
	//MvgIdleAll->Checked=OptionBool[2];
	MVGModify->ItemIndex=OptionInt[3];
	WorkTimeOut->Checked=OptionBool[3];
	ColorOptions->ItemIndex=OptionBool[4];
	SpinBrightness->Position=OptionInt[4];
	Contrast->Checked=OptionBool[5];
	HeightScaling->Checked=OptionBool[6];
	SpinBI->Position=OptionInt[5];
	OpenCheck->Checked=OptionBool[7];
	MvgMore->Checked=OptionBool[8];
	NoMiddle->Checked=OptionBool[9];
}
//---------------------------------------------------------------------------
//Ограничить снизу максимальное
void __fastcall TOptionsForm::RandomFromChange(TObject *Sender)
{
	RandomTo->Min=RandomFrom->Position+1;
	if (RandomTo->Position < RandomFrom->Position)
	RandomTo->Position = RandomFrom->Position+1;
}
//---------------------------------------------------------------------------
//Ограничить сверху минимальное
void __fastcall TOptionsForm::RandomToChange(TObject *Sender)
{
	RandomFrom->Max=RandomTo->Position-1;
}
//---------------------------------------------------------------------------
//Критерий мин. ДПЦ.
void __fastcall TOptionsForm::Crit1Click(TObject *Sender)
{
	Crit1->Checked = true;
}
//---------------------------------------------------------------------------

void __fastcall TOptionsForm::Crit2Click(TObject *Sender)
{
	Info->Caption = "Не работает.";
}
//---------------------------------------------------------------------------

