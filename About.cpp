//-------------------------------------------------------------------- -
#include <vcl.h>
#pragma hdrstop

#include "About.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutForm *AboutForm;
//--------------------------------------------------------------------- 
__fastcall TAboutForm::TAboutForm(TComponent* AOwner)
	: TForm(AOwner)
{
	AboutPanel->Font->Size=10;
	AboutPanel->Font->Height=-13;
}
//---------------------------------------------------------------------

