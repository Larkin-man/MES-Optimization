//------------файл реализации---------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "MainSource.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
     : TForm(Owner)
{    //при созданиии формы
     Output->Text="";
     detal = 1;
     scale = 18;
     N=0;
     //TTrackBar *n = new TTrackBar(this);
     //n->SetBounds(550,50,150,40);
     //n->Visible=true;
     M=0;
     Label7->Caption=detal;
     Label2->Caption="";
     NViewOne->Checked=true;
     graphik=false;
     ultima=false;
     Output->Visible=true;
     Panel1->Visible=false;
     RunBtn->Enabled=false;
     OptimizationBtn->Enabled=false;
     GantBtn->Enabled=false;
     NSave->Enabled=false;
     OpenDialog1->InitialDir=GetCurrentDir();
     SaveDialog1->InitialDir=GetCurrentDir();
     Label2->Canvas->Pen->Color=clHotLight;
     Form1->StringGrid1->Cells[0][0]="Детали:";

     for (int i=1;i<StringGrid1->RowCount;i++)
          Form1->StringGrid1->Cells[0][i]=i;

     for (int j=1;j<StringGrid1->ColCount;j++)
          Form1->StringGrid1->Cells[j][0]=j;//"Станок №"+i;

          //Output->Lines->Add("ColCount="+IntToStr(StringGrid1->ColCount));
}
//---------------------------------------------------------------------------


//ЗАКРЫТЬ
void __fastcall TForm1::NExitClick(TObject *Sender)
{
     delete Optimizer;
     Close();
     //Form1->Close();
}

//ОТКРЫТЬ
void __fastcall TForm1::NOpenClick(TObject *Sender)
{
     if(OpenDialog1->Execute()==IDOK)
     {
          StatusBar1->Panels->Items[0]->Text=OpenDialog1->FileName;
          for (int i=1;i<StringGrid1->RowCount;i++)
               for (int j=1;j<StringGrid1->ColCount;j++)
                    StringGrid1->Cells[j][i]="";

          TStringList *pStrings = new TStringList;
          pStrings->LoadFromFile(OpenDialog1->FileName);
          for(int i=0; i < pStrings->Count; i++)
          {
               char *s = pStrings->Strings[i].c_str();
               int row = 1;
               for (int j =0;j < pStrings->Strings[i].Length();j++)
               {
                    if (s[j]== ' ')
                    {
                         row++;
                         //StringGrid1->Cells[row][i+1]="";  //clear
                    }
                    else
                    {
                         StringGrid1->Cells[row][i+1]=StringGrid1->Cells[row][i+1]+s[j];
                    }
               }
               M=row;
          }
          N = pStrings->Count;
          StatusBar1->Panels->Items[1]->Text=("Станков: "+IntToStr(N));
          StatusBar1->Panels->Items[2]->Text=("Деталей: "+IntToStr(M));
          delete pStrings;
          NSave->Enabled=true;
     }
}
//---------------------------------------------------------------------------
//СОХРАНИТЬ
void __fastcall TForm1::NSaveClick(TObject *Sender)
{
     if(SaveDialog1->Execute()==IDOK)
     {
          Output->Lines->SaveToFile(SaveDialog1->FileName);
          StatusBar1->Panels->Items[0]->Text=SaveDialog1->FileName;
     }

}
//---------------------------------------------------------------------------
//ШРИФТ
void __fastcall TForm1::NFontClick(TObject *Sender)
{
     if (FontDialog1->Execute())
     {
          Output->Font=FontDialog1->Font;
     }

}
//---------------------------------------------------------------------------
//КОПИРОВАТЬ
void __fastcall TForm1::N15Click(TObject *Sender)
{
     Output->CopyToClipboard();
     ShowMessage("Хочешь копировать жми CTRL+C!");
     NViewTwoClick(Sender);
}
//---------------------------------------------------------------------------

//О ПРОГРАММЕ
void __fastcall TForm1::NAboutClick(TObject *Sender)
{
Application->CreateForm( __classid(TAboutBox1),&AboutBox1);
AboutBox1->ShowModal();
AboutBox1->Free();

}
//---------------------------------------------------------------------------
//ДОБАВИТЬ
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
     if ((Edit3->Text == "")||(Edit4->Text == ""))
          {
               ShowMessage("Введите время работы на станках!");
               //защита от дауна;
               return;
          }

     char str[50], *vx;
     strcpy(str, Edit3->Text.c_str());
     vx = strchr(str,',');
     if (vx)
     {
          str[vx-str]='.';
     }
     //ListBox1->Items->Add(str);

     strcpy(str, Edit4->Text.c_str());
     vx = strchr(str,',');
     if (vx)
     {
          str[vx-str]='.';
     }
     //ListBox2->Items->Add(str);

     detal++;
     Label7->Caption=detal;
     StatusBar1->SimpleText=("");
     Edit3->SetFocus();
}
//---------------------------------------------------------------------------
//ОБЫЧНЫЙ ВИД
void __fastcall TForm1::NViewOneClick(TObject *Sender)
{
//N8->Checked=!N8->Checked;
     NViewOne->Checked=true;
     NViewTwo->Checked=false;
     view();
}

//---------------------------------------------------------------------------
//РУЧНОЙ ВВОД ДАННЫХ
void __fastcall TForm1::NViewTwoClick(TObject *Sender)
{
     NViewTwo->Checked=true;
     NViewOne->Checked=false;
     Label2->Visible=true;
     Bevel2->Visible=true;
     StringGrid1->SetBounds(277,62,188,300);
     Output->SetBounds(8,176,265,185);
     view();

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     if(Key == VK_RETURN)
          Edit4->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit4KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     if(Key == VK_RETURN)
          BitBtn1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N12Click(TObject *Sender)
{
     Output->Clear();
}
//---------------------------------------------------------------------------

//ОН ПЭЙНТ
void __fastcall TForm1::FormPaint(TObject *Sender)
{
     if (graphik)
          PaintGant();
}
//---------------------------------------------------------------------------

//ИЗМЕНИЛСЯ МАСШТАБ
void __fastcall TForm1::N25Click(TObject *Sender)
{
     if (graphik)
          PaintGant();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N27Click(TObject *Sender)
{
     if (FontDialog2->Execute())
     {
          Label2->Font=FontDialog2->Font;
     }
     PaintGant();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N28Click(TObject *Sender)
{
     if (ColorDialog1->Execute())
     {
          Label2->Canvas->Pen->Color=ColorDialog1->Color;
     }
     PaintGant();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
     scale=(TrackBar1->Position)+14;
     PaintGant();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NOptSwitchClick(TObject *Sender)
{
     ultima=true;
}
//---------------------------------------------------------------------------
//Рассчет
void __fastcall TForm1::RunBtnClick(TObject *Sender)
{
     if (RadioGroup1->ItemIndex == 0 )
          DjonsonRun();
     if (RadioGroup1->ItemIndex == 1 )
          PetrovSokolRun();
     OptimizationBtn->Enabled=true;
     GantBtn->Enabled=true;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
     view();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
     delete Optimizer;
}
//---------------------------------------------------------------------------
//NEW CLICK
void __fastcall TForm1::NewBtnClick(TObject *Sender)
{
     Output->Clear();
     detal =1;
     Label7->Caption=detal;
     graphik = false;
     delete Optimizer;
     Optimizer = NULL;
     for (int i=1;i<StringGrid1->RowCount;i++)
          Form1->StringGrid1->Cells[0][i]=i;
     for (int j=1;j<StringGrid1->ColCount;j++)
          Form1->StringGrid1->Cells[j][0]=j;//"Станок №"+j;


}
//---------------------------------------------------------------------------



void __fastcall TForm1::GantBtnClick(TObject *Sender)
{
     Form3->Show();     
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1Click(TObject *Sender)
{
     Output->Lines->Add(StringGrid1->Left);
     Output->Lines->Add(StringGrid1->Top);
     Output->Lines->Add(StringGrid1->Height);
     Output->Lines->Add(StringGrid1->Width);
}
//---------------------------------------------------------------------------


