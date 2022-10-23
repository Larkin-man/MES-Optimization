//---------------------------------------------------------------------------
#ifndef EnterDataH
#define EnterDataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <time.h>
#include <stdlib.h>
#include "CSPIN.h"
#include <AppEvnts.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TEnterDataForm : public TForm
{
__published:	// IDE-managed Components
     TLabeledEdit *Field1;
     TLabeledEdit *Field2;
     TBitBtn *BitBtnCancel;
     TBitBtn *BitBtnOk;
     TColorDialog *ColorDialog1;
     void __fastcall FormShow(TObject *Sender);
     void __fastcall BitBtnCancelClick(TObject *Sender);
     void __fastcall Field1Exit(TObject *Sender);
     void __fastcall Field2Exit(TObject *Sender);
     void __fastcall Field1Change(TObject *Sender);
     void __fastcall Field2Change(TObject *Sender);
     void __fastcall BitBtnOkClick(TObject *Sender);
     void __fastcall Field2Click(TObject *Sender);
private:	// User declarations
public:

     enum Okey { random=1, resize=2, color=3 } Result;
     __fastcall TEnterDataForm(TComponent* Owner);

     void StartRandom(const int &m, const int &n)
     {
          Result = random;
          Field1->EditLabel->Caption="Кол-во деталей";
          Field2->EditLabel->Caption="Кол-во станков";
          if (m > 2)
          {
               Field1->Text=IntToStr(m);
               Field2->Text=IntToStr(n);
          }
          else
          {
               Field1->Text="4";
               Field2->Text="3";
          }
     }

     void StartResize()
     {
          Result = resize;
          Field1->EditLabel->Caption="Кол-во строк";
          Field2->EditLabel->Caption="Кол-во столбцов";
          Field1->Text="";
          Field2->Text="";
     }
     
     void StartColor()
     {
          Result = color;
          Field1->EditLabel->Caption="Номер детали";
          Field2->EditLabel->Caption="Цвет";
          Field1->Text="1";
          Field2->Text="";
          Field2->Cursor=crHandPoint;
          Field2->Color=clBlue;
     }

     void __fastcall CheckConvert(TLabeledEdit *Sender)
     {
          if (Sender->Text == "")
               return;
          int c;
          try
          {
               c = StrToInt(Sender->Text);
               if (c == 0)
               {
                  Sender->Text = "";
                  return;
               }
               c = (c<0)? -c : c;
               Sender->Text = c;
          }
          catch (EConvertError&)
          {
               //ShowMessage("Вы ввели ошибочное число");
               Sender->Text="";
          }     
     }


};
//---------------------------------------------------------------------------
extern PACKAGE TEnterDataForm *EnterDataForm;

//---------------------------------------------------------------------------
#endif
