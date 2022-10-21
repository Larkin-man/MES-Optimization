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
     //ShowMessage("Нажми ОК");
     Memo1->Text="";
     detal = 1;
     scale = 18;
     Label7->Caption=detal;
     Label2->Caption="";
     N8->Checked=true;
     graphik=false;
     ultima=false;
     Memo1->Visible=true;
     Panel1->Visible=false;
     del=0;
     RUN->Enabled=false;
     Label2->Canvas->Pen->Color=clHotLight;
     Form1->StringGrid1->Cells[0][0]="Детали:";
     for(int i =1;i<6;i++)
          {
          Form1->StringGrid1->Cells[0][i]=i;
          Form1->StringGrid1->Cells[i][0]=i;//"Станок №"+i;

          }
          //Memo1->Lines->Add("ColCount="+IntToStr(StringGrid1->ColCount));
}
//---------------------------------------------------------------------------
//сюда могут помещатся объявления типов и переменных
//Тут должны быть реализации всех функций,
//объявленных в заголовочном файле
//и других функций не объявленных ранее
//ЗАКРЫТЬ
void __fastcall TForm1::N4Click(TObject *Sender)
{
     /*
     //DeleteList(Optimal);
     //DeleteList(NotOptimal);
     if (Record != NULL)
	{
		delete [] Record;
	}                  */
     Close();
     //Form1->Close();
}

//НАЧАТЬ ЗАНОВО
void __fastcall TForm1::N13Click(TObject *Sender)
{
     ListBox1->Clear();
     ListBox2->Clear();
     Memo1->Clear();
     detal =1;
     Label7->Caption=detal;
               Memo1->Lines->Add(" optimal");
               //print(Optimizer->Optimal);
               //DeleteList(Optimal);
               Memo1->Lines->Add("deleted optimal");
               //print(Optimizer->Optimal);
     //DeleteList(NotOptimal);
     /*if (Record != NULL)
	{
		delete Record;
	}
          if (minimal != NULL)
	{
		delete [] minimal;
	}                          */

     //Edit5->Text=del;


}
//---------------------------------------------------------------------------
//ОТКРЫТЬ
void __fastcall TForm1::N2Click(TObject *Sender)
{
     if(OpenDialog1->Execute()==IDOK)
     {

          ListBox1->Items->LoadFromFile(OpenDialog1->FileName);
          ListBox2->Items->LoadFromFile(OpenDialog1->FileName);
          m = ListBox1->Items->Count;
          for (int i = 0; i< int(m/2) ; i++)
               {
               ListBox1->Items->Delete(int(m/2));
               ListBox2->Items->Delete(0);
               }
          StatusBar1->Panels->Items[0]->Text=OpenDialog1->FileName;
     }

     TStringList *pStrings = new TStringList;
     pStrings->LoadFromFile(OpenDialog1->FileName);
     for(int i=0; i < pStrings->Count; i++)
     {
        StringGrid1->Cells[i%4+1][i/4+1] = pStrings->Strings[i];
     }
     StringGrid1->RowCount=pStrings->Count/4+1;
     delete pStrings;

}
//---------------------------------------------------------------------------
//СОХРАНИТЬ
void __fastcall TForm1::N3Click(TObject *Sender)
{
     if(SaveDialog1->Execute()==IDOK)
     {
          Memo1->Lines->SaveToFile(SaveDialog1->FileName);
          StatusBar1->Panels->Items[0]->Text=SaveDialog1->FileName;
     }

}
//---------------------------------------------------------------------------
//ШРИФТ
void __fastcall TForm1::N7Click(TObject *Sender)
{
     if (FontDialog1->Execute())
     {
          Memo1->Font=FontDialog1->Font;
     }

}
//---------------------------------------------------------------------------
//ТЕСТОВАЯ
void __fastcall TForm1::N14Click(TObject *Sender)
{
     StatusBar1->SimpleText=("");
     char *t = ListBox1->Items->GetText();
     //sprintf(g,"u\nv%d",Sy);
     StatusBar1->SimpleText=t;
             //Label1->Caption = AnsiString(minimum)+buffer;
             //Edit1->Text.IsEmpty()
             //Edit1->Text.sprintf("h\n!");
     char *vx = strchr(Edit3->Text.c_str(),',');
     Memo1->Lines->Add(vx-Edit3->Text.c_str());
     Label2->Canvas->Pen->Color=(TColor)785634;
}
//---------------------------------------------------------------------------
//КОПИРОВАТЬ
void __fastcall TForm1::N15Click(TObject *Sender)
{
     Memo1->CopyToClipboard();
     ShowMessage("Хочешь копировать жми CTRL+C!");
     N20Click(Sender);
}
//---------------------------------------------------------------------------
//УДАЛИТЬ
void __fastcall TForm1::N17Click(TObject *Sender)
{
     if ((ListBox1->ItemIndex == -1)&&(ListBox2->ItemIndex == -1))
          ShowMessage("Чтобы удалить элементы их сперва надо выделить.");
     if (!(ListBox1->ItemIndex == -1))
          ListBox1->Items->Delete(ListBox1->ItemIndex);
     if (!(ListBox2->ItemIndex == -1))
          ListBox2->Items->Delete(ListBox2->ItemIndex);
}
//---------------------------------------------------------------------------
//О ПРОГРАММЕ
void __fastcall TForm1::N19Click(TObject *Sender)
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
     ListBox1->Items->Add(str);

     strcpy(str, Edit4->Text.c_str());
     vx = strchr(str,',');
     if (vx)
     {
          str[vx-str]='.';
     }
     ListBox2->Items->Add(str);

     detal++;
     Label7->Caption=detal;
     StatusBar1->SimpleText=("");
     Edit3->SetFocus();
}
//---------------------------------------------------------------------------
//ОБЫЧНЫЙ ВИД
void __fastcall TForm1::N8Click(TObject *Sender)
{
//N8->Checked=!N8->Checked;
     N8->Checked=true;
     N20->Checked=false;
     view();
}

//---------------------------------------------------------------------------
//РУЧНОЙ ВВОД ДАННЫХ
void __fastcall TForm1::N20Click(TObject *Sender)
{
     N20->Checked=true;
     N8->Checked=false;
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


//---------------------------------------------------------------------------
//ШРИФТ ЕЩЕ ОДИН
void __fastcall TForm1::N21Click(TObject *Sender)
{
     if (FontDialog1->Execute())
          ListBox1->Font=FontDialog1->Font;
          ListBox2->Font=FontDialog1->Font;
}
//---------------------------------------------------------------------------
//ОПЩИПСЬТИТЬ
void __fastcall TForm1::N23Click(TObject *Sender)
{
     ListBox1->Clear();
     ListBox2->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N22Click(TObject *Sender)
{
     ShowMessage("Разделителем дробной части может быть точка(.) или запятая(,). При открытии файла разделителем может быть только точка(.)!");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N12Click(TObject *Sender)
{
     Memo1->Clear();
}
//---------------------------------------------------------------------------
//ГРАФИК
//ОН ПЭЙНТ
void __fastcall TForm1::FormPaint(TObject *Sender)
{
if (graphik == true)
{
     PaintGant();
}
}
//---------------------------------------------------------------------------

//ИЗМЕНИЛСЯ МАСШТАБ
void __fastcall TForm1::N25Click(TObject *Sender)
{
if (graphik == true)
{
     PaintGant();
}
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

void __fastcall TForm1::N30Click(TObject *Sender)
{
     ultima=true;
}
//---------------------------------------------------------------------------
//Рассчет
void __fastcall TForm1::RUNClick(TObject *Sender)
{
     if (RadioGroup1->ItemIndex == 0 )
          DjonsonRun();
     if (RadioGroup1->ItemIndex == 1 )
          PetrovSokolRun();

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

