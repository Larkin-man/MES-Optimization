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

extern future;
int j=0;

void __fastcall TForm3::FormPaint(TObject *Sender)
{
     //j++;
     //float g = doublekill(j,"c");
     /*
     double SA=0,XC=0;;
     Node *Item=Optimal;
     while(Item->pNext != NULL)
     {
     SA+=Item->A;
     Form3->Canvas->Rectangle((SA-Item->A)*18,20,SA*18,50);
     XC = (SA >= XC)? SA+Item->B : XC+Item->B;
     //Memo1->Lines->Add(XC);
     Form3->Canvas->Rectangle((XC-Item->B)*18,60,XC*18,90);
     Form3->Canvas->TextOut((SA-Item->A)*18+6,30,Item->n);
     Form3->Canvas->TextOut((XC-Item->B)*18+6,70,Item->n);
     Item = Item->pNext;
     }

     //›ÚÓ ÍÓÔËˇ
     SA+=Item->A;
     Form3->Canvas->Rectangle((SA-Item->A)*18,20,SA*18,50);
     XC = (SA >= XC)? SA+Item->B : XC+Item->B;
     Form3->Canvas->Rectangle((XC-Item->B)*18,60,XC*18,90);
     Form3->Canvas->TextOut((SA-Item->A)*18+6,30,Item->n);
     Form3->Canvas->TextOut((XC-Item->B)*18+6,70,Item->n);
     Item = Item->pNext;  //»—œ–¿¬»“‹          */
}
//---------------------------------------------------------------------------
float doublekill(int a, char c);
