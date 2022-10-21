//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Graphic.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "MainSource.h"
TGraphicForm *GraphicForm;
//---------------------------------------------------------------------------
__fastcall TGraphicForm::TGraphicForm(TComponent* Owner)
     : TForm(Owner)
{
     GraphicForm->Height=Screen->WorkAreaHeight;
     GraphicForm->Width=Screen->WorkAreaWidth;
     GraphicForm->Left=Screen->WorkAreaLeft;
     GraphicForm->Top=Screen->WorkAreaTop;
     //ShowMessage("Screen-> width="+IntToStr(Screen->Width)+" he="+IntToStr(Screen->Height));
     //ShowMessage("Desktop width="+IntToStr(Screen->WorkAreaWidth)+" he="+IntToStr(Screen->WorkAreaHeight));
     //GraphicForm->Align=alClient;
     //ShowMessage("Screen-> width="+IntToStr(GraphicForm->Width)+" hei="+IntToStr(GraphicForm->Height));
     //BitMap = new Graphics::TBitmap;
     gant->Canvas->Brush->Color=clRed;
}
//---------------------------------------------------------------------------
//Переход в модуль расчета
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
     //BaseForm->GantDiagramExecute(NULL);
     BaseForm->SetFocus();
     BaseForm->GantBtn->Down=false;
     //BitMap->Free();
}
//---------------------------------------------------------------------------
//Цветпит
void __fastcall TGraphicForm::SpeedButton2Click(TObject *Sender)
{
     if (GantBrushColor->Execute())
     {
          gant->Canvas->Brush->Color=GantBrushColor->Color;
     }
     BaseForm->PaintGant();

}
//---------------------------------------------------------------------------
//Сохранить изображение диаграммы
void __fastcall TGraphicForm::SpeedButton3Click(TObject *Sender)
{
     if (SavePictureDialog1->Execute())
     {
          //BitMap->Assign (gant->Picture) ;
          BaseForm->Gant->SaveToFile(SavePictureDialog1->FileName);
          //BitMap->SaveToFile (SavePictureDialog1->FileName) ;

     }
}
//---------------------------------------------------------------------------
//Показать фформу
void __fastcall TGraphicForm::FormShow(TObject *Sender)
{
     //gant->Picture->Free();
     //gant->Canvas->CleanupInstance();
     //gant->Canvas->Free();
     //ShowMessage(" gant form show");
     gant->Canvas->Brush->Color=ColorBox1->Selected;
     gant->Canvas->FillRect(Rect(0,0,gant->Width,gant->Height));
     //gant->Assign()
}
//---------------------------------------------------------------------------


