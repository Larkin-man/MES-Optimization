//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "EnterData.h"

//---------------------------------------------------------------------------
#include "MainSource.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
int res1;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::SpeedButton1Click(TObject *Sender)
{
     if (Form2->Field1->Text.operator!=(""))
          Form1->Table->RowCount=StrToInt(Form2->Field1->Text)+1;
     if (Form2->Field2->Text != "")
          Form1->Table->ColCount=StrToInt(Form2->Field2->Text)+1;
     for (int i=1;i<Form1->Table->RowCount;i++)
          Form1->Table->Cells[0][i]="Деталь " + IntToStr(i)+":";
     for (int j=1;j<Form1->Table->ColCount;j++)
          Form1->Table->Cells[j][0]=j;//"Станок №"+i;
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::SpeedButton2Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Edit1Change(TObject *Sender)
{
//SpeedButton1->Enabled=Edit1->Text.operator!=("");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormShow(TObject *Sender)
{
Field1->Text="";
Field2->Text="";
Field1->SetFocus();
}
//---------------------------------------------------------------------------

