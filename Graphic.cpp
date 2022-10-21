//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Graphic.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
     : TForm(Owner)
{
}
//---------------------------------------------------------------------------

extern float future;
int j=0;
float doublekill(int a);

//---------------------------------------------------------------------------

void __fastcall TForm3::Button1Click(TObject *Sender)
{
     j++;
     //float task=doublekill(j);
     future = 13;
}
//---------------------------------------------------------------------------

