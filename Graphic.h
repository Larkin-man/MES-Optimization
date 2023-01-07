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
	TBitBtn *BitBtnToMain;
	TSpeedButton *SpeedBtnColorSave;
	TSpeedButton *SpeedBtnColor;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolBar *ToolBar2;
	TLabel *LabelScale;
	TTrackBar *TrackBar1;
	TToolButton *ToolButton3;
	TPopupMenu *PopupMenu1;
	TMenuItem *NRefresh;
	TMenuItem *NWorkOut;
	TMenuItem *NLineOut;
	TMenuItem *NColorBlock;
	TScrollBar *ScrollBarHorz;
	TScrollBar *ScrollBarVert;
	TMenuItem *NChangeColor;
	TPanel *Panel3;
	TPanel *Panel1;
	TLabel *Label1;
	TColorBox *ColorBox1;
	TPanel *Panel4;
	TCheckBox *CheckBoxNout;
	TCheckBox *CheckBoxColorSave;
	void __fastcall BitBtn1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SpeedBtnColorClick(TObject *Sender);
	void __fastcall SpeedBtnColorSaveClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall TrackBar1Change(TObject *Sender);
	void __fastcall ColorBox1Change(TObject *Sender);
	void __fastcall NRefreshClick(TObject *Sender);
	void __fastcall NWorkOutClick(TObject *Sender);
	void __fastcall NColorBlockClick(TObject *Sender);
	void __fastcall ScrollBarHorzScroll(TObject *Sender,
		TScrollCode ScrollCode, int &ScrollPos);
	void __fastcall ScrollBarVertScroll(TObject *Sender,
		TScrollCode ScrollCode, int &ScrollPos);
	void __fastcall CheckBoxNoutClick(TObject *Sender);
	void __fastcall NChangeColorClick(TObject *Sender);
private:
public:
	__fastcall TGraphicForm(TComponent* Owner);
	void DrawGant(int PosX, int PosY);
	int scr1,scr2;
	int
		GantH,	//Gant Height
		GantW;	//Gant Weight
void __fastcall inline ClearGantField();
};
//---------------------------------------------------------------------------
extern PACKAGE TGraphicForm *GraphicForm;
//---------------------------------------------------------------------------
#endif
