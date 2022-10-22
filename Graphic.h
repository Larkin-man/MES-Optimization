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
#include <Menus.hpp>

//---------------------------------------------------------------------------
class TGraphicForm : public TForm
{
__published:	// IDE-managed Components
     TImage *gant;
     TColorDialog *GantBrushColor;
     TSavePictureDialog *SavePictureDialog1;
     TControlBar *ControlBar1;
     TToolBar *ToolBar1;
     TBitBtn *BitBtn4;
     TSpeedButton *SpeedButton3;
     TSpeedButton *SpeedButton2;
     TToolButton *ToolButton1;
     TToolButton *ToolButton2;
     TToolBar *ToolBar2;
     TLabel *Label2;
     TTrackBar *TrackBar1;
     TToolBar *ToolBar3;
     TPanel *Panel1;
     TLabel *Label1;
     TColorBox *ColorBox1;
     TToolButton *ToolButton3;
     TPopupMenu *PopupMenu1;
     TMenuItem *N1;
     TMenuItem *N2;
     TMenuItem *N3;
     TMenuItem *N4;
     void __fastcall BitBtn1Click(TObject *Sender);
     void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
     void __fastcall SpeedButton2Click(TObject *Sender);
     void __fastcall SpeedButton3Click(TObject *Sender);
     void __fastcall FormShow(TObject *Sender);
     void __fastcall TrackBar1Change(TObject *Sender);
     void __fastcall ColorBox1Change(TObject *Sender);
     void __fastcall N2Click(TObject *Sender);
     void __fastcall N1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
     //Graphics::TBitmap *BitMap;// = new Graphics::TBitmap;
     __fastcall TGraphicForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGraphicForm *GraphicForm;
//---------------------------------------------------------------------------

#endif
