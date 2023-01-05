//-------------------------------------------------------------------------- -
#include <vcl.h>
#pragma hdrstop

#include "Graphic.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "MainSource.h"
TGraphicForm *GraphicForm;
//---------------------------------------------------------------------------
__fastcall TGraphicForm::TGraphicForm(TComponent* Owner) : TForm(Owner)
{
	GraphicForm->Height=Screen->WorkAreaHeight;
	GraphicForm->Width=Screen->WorkAreaWidth;
	GraphicForm->Left=Screen->WorkAreaLeft;
	GraphicForm->Top=Screen->WorkAreaTop;
	gant->Canvas->Brush->Color=clRed;
	SavePictureDialog1->InitialDir=GetCurrentDir();
	scr1=0;
	scr2=0;
	NColorBlock->Checked=true;
}
//---------------------------------------------------------------------------
//Кнопка - Переход в модуль расчета
void __fastcall TGraphicForm::BitBtn1Click(TObject *Sender)
{
	BaseForm->BringToFront();
	BaseForm->SetFocus();
}
//---------------------------------------------------------------------------
//Прикрыть форму
void __fastcall TGraphicForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	//DONE: BitMap->Canvas-> Канва в битмапе!
	BaseForm->gantshow=false;
	BaseForm->SetFocus();
	BaseForm->GantBtn->Down=false;
	//BitMap->Free();
}
//---------------------------------------------------------------------------
//Кнопка - изменение цвета
void __fastcall TGraphicForm::SpeedBtnColorClick(TObject *Sender)
{
	if (NColorBlock->Checked)
		NChangeColorClick(Sender);
	else
	{
		if (GantBrushColor->Execute() == IDOK)
		{
			OptionsForm->ColorOptions->ItemIndex=0;
			BaseForm->multicoloured=false;
			NColorBlock->Checked=false;
			BaseForm->PaintGant();
		}
	}			   
}
//---------------------------------------------------------------------------
//Кнопка - Сохранить изображение диаграммы
void __fastcall TGraphicForm::SpeedBtnColorSaveClick(TObject *Sender)
{
	if (SavePictureDialog1->Execute() == ID_OK)
	{
		//BitMap->Assign (gant->Picture) ;
		BaseForm->Gant->SaveToFile(SavePictureDialog1->FileName);
		//BitMap->SaveToFile (SavePictureDialog1->FileName) ;	   
	}
}
//---------------------------------------------------------------------------
//Показать форму
void __fastcall TGraphicForm::FormShow(TObject *Sender)
{
	//gant->Picture->Free();
	//gant->Canvas->Free();
	BaseForm->CountScale(TrackBar1->Position);
	ClearGantField();
	TrackBar1->Height=35;
	Label1->Height=35;
}
//---------------------------------------------------------------------------
//МАСШТАБ 
void __fastcall TGraphicForm::TrackBar1Change(TObject *Sender)
{							  
	BaseForm->CountScale(TrackBar1->Position);
	ClearGantField();
	BaseForm->PaintGant();
}
//---------------------------------------------------------------------------
//Изменение цвета фона
void __fastcall TGraphicForm::ColorBox1Change(TObject *Sender)
{
	BaseForm->PaintGant();
}
//---------------------------------------------------------------------------
//Обновить
void __fastcall TGraphicForm::NRefreshClick(TObject *Sender)
{
	gant->Refresh();
	BitBtnToMain->SetFocus();
}
//---------------------------------------------------------------------------
//Выводить время работы
void __fastcall TGraphicForm::NWorkOutClick(TObject *Sender)
{
	NWorkOut->Checked=!NWorkOut->Checked;
	OptionsForm->WorkTimeOut->Checked=NWorkOut->Checked;
	BaseForm->CountScale(GraphicForm->TrackBar1->Position);
	BaseForm->PaintGant();
}
//---------------------------------------------------------------------------
//Цветные блоки
void __fastcall TGraphicForm::NColorBlockClick(TObject *Sender)
{
	NColorBlock->Checked=true;
	OptionsForm->ColorOptions->ItemIndex=1;
	BaseForm->multicoloured=true;
	BaseForm->PaintGant();
	GraphicForm->NChangeColor->Enabled=true;
}
//---------------------------------------------------------------------------
//Горизонтальный ползунок двигается
void __fastcall TGraphicForm::ScrollBarHorzScroll(TObject *Sender,
	 TScrollCode ScrollCode, int &ScrollPos)  //параметр ScrollPos - позиция бегунка, передается
{								//по ссылке, можно изменять
	if (scr1 == ScrollPos)
		return;
	scr1=ScrollPos;
	ClearGantField();
	DrawGant(ScrollPos,ScrollBarVert->Position);
}
//---------------------------------------------------------------------------
//Вертикальный ползунок двигается
void __fastcall TGraphicForm::ScrollBarVertScroll(TObject *Sender,
	 TScrollCode ScrollCode, int &ScrollPos)
{
	if (scr2 == ScrollPos)
		return;
	scr2=ScrollPos;
	ClearGantField();
	DrawGant(ScrollBarHorz->Position,ScrollPos);
}
//---------------------------------------------------------------------------
//Отрисовка диаграммы при движении ползунков
void TGraphicForm::DrawGant(int PosX, int PosY)
{
	int FormH=gant->ClientHeight;
	int FormW=gant->ClientWidth;
	int K;
	if (BaseForm->GantW > FormW)
	{
		ScrollBarHorz->Enabled=true;
		K = BaseForm->GantW - FormW;
		ScrollBarHorz->Max=K+50;
	}
	else
		ScrollBarHorz->Enabled=false;

	if (BaseForm->GantH > FormH)
	{
		ScrollBarVert->Enabled=true;
		K = BaseForm->GantH - FormH;
		ScrollBarVert->Max=K+50;
	}
	else
		ScrollBarVert->Enabled=false;
	 gant->Canvas->CopyRect(
			Rect(0,0,FormW,FormH),
			BaseForm->Gant->Canvas,
			Rect(PosX,PosY,FormW+PosX,FormH+PosY));
}
//---------------------------------------------------------------------------
//Установить флажок - станки
void __fastcall TGraphicForm::CheckBoxNoutClick(TObject *Sender)
{
	if (CheckBoxNout->Checked)
		BaseForm->Edge=20;
	else
		BaseForm->Edge=0;
	BaseForm->PaintGant();
}
//---------------------------------------------------------------------------
//Установить цвет детали
void __fastcall TGraphicForm::NChangeColorClick(TObject *Sender)
{
	Application->CreateForm( __classid(TEnterDataForm),&EnterDataForm);
	EnterDataForm->Caption=("Установить цвет детали");
	EnterDataForm->StartColor();
	EnterDataForm->Position=poMainFormCenter;
	EnterDataForm->ShowModal();
	EnterDataForm->Free();
}
//---------------------------------------------------------------------------
//Очистить диаграмму
void __fastcall inline TGraphicForm::ClearGantField()
{
	gant->Canvas->Brush->Color=ColorBox1->Selected;
	gant->Canvas->FillRect(Rect(0,0,gant->Width,gant->Height));
}
//---------------------------------------------------------------------------
