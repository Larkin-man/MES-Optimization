//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Graphic.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "MainSource.h"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
     : TForm(Owner)
{
}
//---------------------------------------------------------------------------

int j=0;
float doublekill(int a);

//---------------------------------------------------------------------------

void __fastcall TForm3::BitBtn1Click(TObject *Sender)
{
     Form1->BringToFront();
     Form1->SetFocus();     
}
//---------------------------------------------------------------------------

