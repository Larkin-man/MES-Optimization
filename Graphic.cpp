//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Graphic.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "MainSource.h"
TGraphicForm *GraphicForm;
//---------------------------------------------------------------------------
__fastcall TGraphicForm::TGraphicForm(TComponent* Owner)
     : TForm(Owner)
{
     GraphicForm->Height=Screen->WorkAreaHeight;
     GraphicForm->Width=Screen->WorkAreaWidth;
     GraphicForm->Left=Screen->WorkAreaLeft;
     GraphicForm->Top=Screen->WorkAreaTop;
     //ShowMessage("Screen-> width="+IntToStr(Screen->Width)+" he="+IntToStr(Screen->Height));
     //ShowMessage("Desktop width="+IntToStr(Screen->WorkAreaWidth)+" he="+IntToStr(Screen->WorkAreaHeight));
     //GraphicForm->Align=alClient;
     //ShowMessage("Screen-> width="+IntToStr(GraphicForm->Width)+" hei="+IntToStr(GraphicForm->Height));
     //BitMap = new Graphics::TBitmap;
     gant->Canvas->Brush->Color=clRed;
     SavePictureDialog1->InitialDir=GetCurrentDir();
     scr1=0;
     scr2=0;
}
//---------------------------------------------------------------------------
//������� � ������ �������
void __fastcall TGraphicForm::BitBtn1Click(TObject *Sender)
{
     BaseForm->BringToFront();
     BaseForm->SetFocus();
}
//---------------------------------------------------------------------------
//�������� �����
void __fastcall TGraphicForm::FormClose(TObject *Sender, TCloseAction &Action)
{
     //DONE: BitMap->Canvas-> ����� � �������!
     BaseForm->gantshow=false;
     //BaseForm->GantDiagramExecute(NULL);
     BaseForm->SetFocus();
     BaseForm->GantBtn->Down=false;
     //BitMap->Free();
}
//---------------------------------------------------------------------------
//�������
void __fastcall TGraphicForm::SpeedButton2Click(TObject *Sender)
{
     if (GantBrushColor->Execute() == IDOK)
     {
          OptionsForm->ColorOptions->ItemIndex=0;
          BaseForm->multicoloured=false;
          N4->Checked=false;
          BaseForm->PaintGant();
     }
}
//---------------------------------------------------------------------------
//��������� ����������� ���������
void __fastcall TGraphicForm::SpeedButton3Click(TObject *Sender)
{
     if (SavePictureDialog1->Execute())
     {
          //BitMap->Assign (gant->Picture) ;
          BaseForm->Gant->SaveToFile(SavePictureDialog1->FileName);
          //BitMap->SaveToFile (SavePictureDialog1->FileName) ;        
     }
}
//---------------------------------------------------------------------------
//�������� �����
void __fastcall TGraphicForm::FormShow(TObject *Sender)
{
     //gant->Picture->Free();
     //gant->Canvas->CleanupInstance();
     //gant->Canvas->Free();
     //ShowMessage(" gant form show");
     BaseForm->CountScale(TrackBar1->Position);
     ClearGantField();
     TrackBar1->Height=35;
     Label1->Height=35;
     //gant->Assign()
}
//---------------------------------------------------------------------------
//������� 
void __fastcall TGraphicForm::TrackBar1Change(TObject *Sender)
{                                     
     BaseForm->CountScale(TrackBar1->Position);
     ClearGantField();
     BaseForm->PaintGant();
}
//---------------------------------------------------------------------------

void __fastcall TGraphicForm::ColorBox1Change(TObject *Sender)
{
     BaseForm->PaintGant();
}
//---------------------------------------------------------------------------

void __fastcall TGraphicForm::N1Click(TObject *Sender)
{
     gant->Refresh();
     BitBtn4->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TGraphicForm::N2Click(TObject *Sender)
{
     N2->Checked=true;
     OptionsForm->WorkTimeOut->Checked=true;
     BaseForm->CountScale(GraphicForm->TrackBar1->Position);
     BaseForm->PaintGant();
}
//---------------------------------------------------------------------------

void __fastcall TGraphicForm::N4Click(TObject *Sender)
{
     N4->Checked=true;
     OptionsForm->ColorOptions->ItemIndex=1;
     BaseForm->multicoloured=true;
     BaseForm->PaintGant();
}
//---------------------------------------------------------------------------


void __fastcall TGraphicForm::ScrollBar1Scroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
     if (scr1 == ScrollPos)
          return;
     scr1=ScrollPos;
     ClearGantField();
     BaseForm->DrawGant(ScrollPos,ScrollBar2->Position);
}
//---------------------------------------------------------------------------

void __fastcall TGraphicForm::ScrollBar2Scroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
     if (scr2 == ScrollPos)
          return;
     scr2=ScrollPos;
     ClearGantField();
     BaseForm->DrawGant(ScrollBar1->Position,ScrollPos);
}
//---------------------------------------------------------------------------

