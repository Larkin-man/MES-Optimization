//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Table.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender)
{
        StringGrid1->RowCount=2;
        StringGrid1->Cols[0]->Add("0");
        StringGrid1->Cols[1]->Add("1");
        StringGrid1->Cols[2]->Add("2");
        StringGrid1->Cols[3]->Add("3");
        StringGrid1->Cols[4]->Add("4");
        StringGrid1->Cols[5]->Add("5");
        StringGrid1->Cols[6]->Add("...");
}
//---------------------------------------------------------------------------
 