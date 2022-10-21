//---------------------------------------------------------------------------

#ifndef GraphicH
#define GraphicH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ToolWin.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>

//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
     TImage *gant;
     TControlBar *ControlBar1;
     TTrackBar *TrackBar1;
     TBitBtn *BitBtn1;
     void __fastcall BitBtn1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
     __fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------

#endif
