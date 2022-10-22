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
     gant->Canvas->Brush->Color=ColorBox1->Selected;
     gant->Canvas->FillRect(Rect(0,0,gant->Width,gant->Height));
     TrackBar1->Height=35;
     Label1->Height=35;
     //gant->Assign()
}
//---------------------------------------------------------------------------
//������� 
void __fastcall TGraphicForm::TrackBar1Change(TObject *Sender)
{
     FormShow(NULL);
     delete BaseForm->Gant;
     BaseForm->Gant = new Graphics::TBitmap;
     BaseForm->scale=(TrackBar1->Position)+12+(TrackBar1->Position)/3;
     //BaseForm->BH=26+(TrackBar1->Position)/2;
     //BaseForm->BI=(BaseForm->BH)/3;
     BaseForm->PaintGant();
}
//---------------------------------------------------------------------------

void __fastcall TGraphicForm::ColorBox1Change(TObject *Sender)
{
     TrackBar1Change(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGraphicForm::N2Click(TObject *Sender)
{
     if (OptionsForm->WorkTimeOut->Checked == false)
          OptionsForm->WorkTimeOutClick(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TGraphicForm::N1Click(TObject *Sender)
{
     gant->Refresh();
}
//---------------------------------------------------------------------------

