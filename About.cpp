//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox1 *AboutBox1;
//--------------------------------------------------------------------- 
__fastcall TAboutBox1::TAboutBox1(TComponent* AOwner)
	: TForm(AOwner)
{
     Panel1->Font->Size=10;
     Panel1->Font->Height=-13;
}
//---------------------------------------------------------------------

