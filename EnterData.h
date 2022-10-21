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
//---------------------------------------------------------------------------
class TEnterDataForm : public TForm
{
__published:	// IDE-managed Components
     TLabeledEdit *Field1;
     TLabeledEdit *Field2;
     TBitBtn *BitBtn1;
     TBitBtn *BitBtn2;
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
     void __fastcall Field1Change(TObject *Sender);
     void __fastcall BitBtn1Click(TObject *Sender);
     void __fastcall BitBtn2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TEnterDataForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEnterDataForm *EnterDataForm;
//---------------------------------------------------------------------------
#endif
