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
//---------------------------------------------------------------------------
class TEnterDataForm : public TForm
{
__published:	// IDE-managed Components
     TLabeledEdit *Field1;
     TLabeledEdit *Field2;
     TBitBtn *BitBtnOkResize;
     TBitBtn *BitBtn2;
     TBitBtn *BitBtnOkRandom;
        void __fastcall FormShow(TObject *Sender);
     void __fastcall BitBtnOkResizeClick(TObject *Sender);
     void __fastcall BitBtn2Click(TObject *Sender);
     void __fastcall BitBtnOkRandomClick(TObject *Sender);
     void __fastcall Field1Exit(TObject *Sender);
     void __fastcall Field2Exit(TObject *Sender);     
private:	// User declarations
public:		// User declarations
        __fastcall TEnterDataForm(TComponent* Owner);

     void CheckConvert(TLabeledEdit *Sender)
     {
          int c;
          try
          {
               c = StrToInt(Sender->Text);
                    if (c<0)
                         Sender->Text = abs(c);
          }
          catch (EConvertError&)
          {
               //ShowMessage("Вы ввели ошибочное число");
               Sender->Text="";  
          }
          if (c == 0)
               Sender->Text = "";

     }
};
//---------------------------------------------------------------------------
extern PACKAGE TEnterDataForm *EnterDataForm;
//---------------------------------------------------------------------------
#endif
