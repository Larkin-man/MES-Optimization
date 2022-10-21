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
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>

//---------------------------------------------------------------------------
class TGraphicForm : public TForm
{
__published:	// IDE-managed Components
     TImage *gant;
     TControlBar *ControlBar1;
     TTrackBar *TrackBar1;
     TSpeedButton *SpeedButton1;
     TBitBtn *BitBtn1;
     TSpeedButton *SpeedButton2;
     TColorDialog *ColorDialog1;
     TSpeedButton *SpeedButton3;
     TSavePictureDialog *SavePictureDialog1;
     void __fastcall BitBtn1Click(TObject *Sender);
     void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
     void __fastcall SpeedButton2Click(TObject *Sender);
     void __fastcall SpeedButton3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
     Graphics::TBitmap *BitMap;// = new Graphics::TBitmap;
     __fastcall TGraphicForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGraphicForm *GraphicForm;
//---------------------------------------------------------------------------

#endif
