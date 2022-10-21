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
     BitMap = new Graphics::TBitmap;
}
//---------------------------------------------------------------------------

void __fastcall TGraphicForm::BitBtn1Click(TObject *Sender)
{
     BaseForm->BringToFront();
     BaseForm->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TGraphicForm::FormClose(TObject *Sender, TCloseAction &Action)
{
     //TODO: BitMap->Canvas-> Канва в битмапе!
     BaseForm->GantBtn->Down=false;
     BaseForm->SetFocus();
     BitMap->Free();
}
//---------------------------------------------------------------------------


void __fastcall TGraphicForm::SpeedButton2Click(TObject *Sender)
{
     if (ColorDialog1->Execute())
     {
          gant->Canvas->Pen->Color=ColorDialog1->Color;
     }
     BaseForm->PaintGant();
}
//---------------------------------------------------------------------------

void __fastcall TGraphicForm::SpeedButton3Click(TObject *Sender)
{
     if (SavePictureDialog1->Execute())
     {
          BitMap->Assign (gant->Picture) ;
          BitMap->SaveToFile (SavePictureDialog1->FileName) ;

     }
}
//---------------------------------------------------------------------------

