//---------------------------------------------------------------------------

#ifndef MainSourceH
#define MainSourceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <stdio.h>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include "About.h"
#include "OptimizationMtds.h"
#include <math.h>
#include <ToolWin.hpp>
#include <ExtDlgs.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------

#define max(A,B) (A>B ? A : B)
MachineOptimizer *Optimizer = new MachineOptimizer;

class TForm1 : public TForm
{
__published:	// IDE-managed Components
     TMainMenu *MainMenu1;
     TPopupMenu *PopupMenu1;
     TMenuItem *N1;
     TMenuItem *N2;
     TMenuItem *N3;
     TMenuItem *N4;
     TMenuItem *N5;
     TMenuItem *N6;
     TMenuItem *N7;
     TMenuItem *N8;
     TMenuItem *N9;
     TMenuItem *N10;
     TMenuItem *N11;
     TMenuItem *N12;
     TListBox *ListBox1;
     TLabel *Xsl;
     TListBox *ListBox2;
     TLabel *Ysl;
     TPanel *Panel1;
     TEdit *Edit3;
     TLabel *Label4;
     TLabel *Label5;
     TLabel *Label6;
     TEdit *Edit4;
     TMenuItem *N13;
     TLabel *Label7;
     TOpenDialog *OpenDialog1;
     TSaveDialog *SaveDialog1;
     TFontDialog *FontDialog1;
     TStatusBar *StatusBar1;
     TMenuItem *N14;
     TMemo *Memo1;
     TMenuItem *N15;
     TMenuItem *N16;
     TMenuItem *N17;
     TMenuItem *N18;
     TMenuItem *N19;
     TBitBtn *BitBtn1;
     TMenuItem *N20;
     TPopupMenu *PopupMenu2;
     TMenuItem *N21;
     TMenuItem *N22;
     TMenuItem *N23;
     TMenuItem *U1;
     TLabel *Label2;
     TLabel *Label3;
     TRadioGroup *RadioGroup1;
     TSpeedButton *SpeedButton5;
     TSpeedButton *SpeedButton4;
     TSpeedButton *SpeedButton6;
     TSpeedButton *SpeedButton7;
     TBevel *Bevel1;
     TSpeedButton *SpeedButton3;
     TPopupMenu *PopupMenu3;
     TMenuItem *N25;
     TMenuItem *N26;
     TMenuItem *N27;
     TMenuItem *N28;
     TTrackBar *TrackBar1;
     TColorDialog *ColorDialog1;
     TBevel *Bevel2;
     TMenuItem *N29;
     TMenuItem *N30;
     TMenuItem *N31;
     TFontDialog *FontDialog2;
     TSpeedButton *RUN;
     TBevel *Bevel3;
     TStringGrid *StringGrid1;
     TSpeedButton *SpeedButton1;
     void __fastcall N4Click(TObject *Sender);
     void __fastcall N13Click(TObject *Sender);
     void __fastcall N2Click(TObject *Sender);
     void __fastcall N3Click(TObject *Sender);
     void __fastcall N7Click(TObject *Sender);
     void __fastcall N14Click(TObject *Sender);
     void __fastcall N15Click(TObject *Sender);
     void __fastcall N8Click(TObject *Sender);
     void __fastcall N17Click(TObject *Sender);
     void __fastcall N19Click(TObject *Sender);
     void __fastcall BitBtn1Click(TObject *Sender);
     void __fastcall N20Click(TObject *Sender);
     void __fastcall Edit3KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
     void __fastcall Edit4KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
     void __fastcall N21Click(TObject *Sender);
     void __fastcall N23Click(TObject *Sender);
     void __fastcall N22Click(TObject *Sender);
     void __fastcall N12Click(TObject *Sender);
     void __fastcall FormPaint(TObject *Sender);
     void __fastcall N25Click(TObject *Sender);
     void __fastcall N27Click(TObject *Sender);
     void __fastcall N28Click(TObject *Sender);
     void __fastcall TrackBar1Change(TObject *Sender);
     void __fastcall N30Click(TObject *Sender);
     void __fastcall RUNClick(TObject *Sender);
     void __fastcall RadioGroup1Click(TObject *Sender);
     void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
//Только в пределах данного модуля
     void __fastcall F1(char c);
     int ij;


public:		// User declarations

     int n,m,detal,vt,scale,nDet,del;
	double a,b;
     double min[2];
     double SA,XC;
     bool graphik,ultima;
     int *top;

     __fastcall TForm1(TComponent* Owner);  //Объявление конструктора

//void PrintMatrix(MachineOptimizer::Link *list,int m,bool prev=false);

void view() //Проверка видимости элементов
{
     Memo1->Visible=N8->Checked;
     Panel1->Visible=N20->Checked;
     RUN->Enabled=(RadioGroup1->ItemIndex!=-1);
     StringGrid1->Visible=(RadioGroup1->ItemIndex!=0);
     Xsl->Visible=(RadioGroup1->ItemIndex==0);
     Ysl->Visible=(RadioGroup1->ItemIndex==0);
     ListBox1->Visible=(RadioGroup1->ItemIndex==0);
     ListBox2->Visible=(RadioGroup1->ItemIndex==0);
}


void paint(MachineOptimizer::Link *list)
{
     for(;list != NULL;list = list->next)
     {
     //Memo1->Lines->Add(list->curr->n);
     Memo1->Text=Memo1->Text+" "+FloatToStr(list->curr->T[0]);
     }
}

void PrintMatrix(MachineOptimizer::Link *list,int m,bool prev)
{
     if (list != NULL)
     {
          if (!prev)
          {
               Memo1->Lines->Add(IntToStr(list->curr->n)+"  |  ");
               for (int i = 0;i<m;i++)
                    Memo1->Text=Memo1->Text+IntToStr(list->curr->T[i])+"  ";
               list = list->next;
               PrintMatrix(list,m,prev);
          }
          else
          {
               Memo1->Lines->Add(IntToStr(list->prev->curr->n)+"  |  ");
               for (int i = 0;i<m;i++)
                    Memo1->Text=Memo1->Text+IntToStr(list->prev->curr->T[i])+"  ";
               list = list->next;
               PrintMatrix(list,m,prev);
          }
     }
}

void PrintMatrixPS(MachineOptimizer::Link *list,int m,int one,int left)
{
     if (list != NULL)
     {
          Memo1->Lines->Add(IntToStr(list->curr->n)+"  |  ");
          one+=list->prev->curr->T[0];
          //ShowMessage("one = "+IntToStr(list->prev->curr->T[1]));
          Memo1->Text=Memo1->Text+IntToStr(one)+"  ";
          left = one;
          int S=0;
          for (int i = 1;i<m;i++)
          {

               if (list->prev == NULL)
               {

                    S+=list->prev->curr->T[i];
                    top[i]=S;
                    //ShowMessage("S = "+IntToStr(S));
               }
               else
               {
                    S=max(top[i],left)+list->prev->curr->T[i];

                    left=S;
                    top[i]=S;

               }
               //ShowMessage("S = "+IntToStr(S));
               Memo1->Text=Memo1->Text+IntToStr(S)+"  ";
          }
          list = list->next;
          PrintMatrixPS(list,m,one,left);
     }
}

void paintn(MachineOptimizer::Link *list)
{
     for(;list != NULL;list = list->next)
     {
     //Memo1->Lines->Add(list->curr->n);
     Memo1->Text=Memo1->Text+" "+FloatToStr(list->curr->n);
     }
}

void paintUUU(MachineOptimizer::Link *list)
{
     for(;list != NULL;list = list->next)
     {
     //Memo1->Lines->Add(list->curr->n);
     Memo1->Text=Memo1->Text+" "+FloatToStr(list->prev->curr->T[0]);
     }
}

void PaintBlock(MachineOptimizer::Link *Item)
{
     SA=0,XC=0;
     for (;Item != NULL;Item = Item->next)
     {
          SA+=Item->curr->T[0];
          Label2->Canvas->Rectangle((SA-Item->curr->T[0])*scale,vt,SA*scale,vt+30);
          XC = (SA >= XC)? SA+Item->curr->T[1] : XC+Item->curr->T[1];
          Label2->Canvas->Rectangle((XC-Item->curr->T[1])*scale,vt+40,XC*scale,vt+70);
          Label2->Canvas->TextOut((SA-Item->curr->T[0])*scale+6,vt+6,Item->curr->n);
          Label2->Canvas->TextOut((XC-Item->curr->T[1])*scale+6,vt+46,Item->curr->n);
     }
     Label2->Canvas->TextOut(10,vt+75,"Время работы:");
     Label2->Canvas->TextOut(125,vt+75,XC);
}

void PaintGant()
{
     if (Optimizer->Optimal == NULL) return;
     Label2->Repaint();
     Label2->Canvas->Pen->Width=1;
     Label2->Canvas->TextOut(5,5,"Исходные данные:");
     vt=30;
     PaintBlock(Optimizer->InitBegin);

     Label2->Canvas->TextOut(10,140,"Оптимизированные данные:");
     vt=165;  
     PaintBlock(Optimizer->Optimal);
     /*
     if (ultima)
     {
          vt=290;
          SA=0,XC=0;
          Node *Item=Optimal;
          for (;;Item = Item->Next)
          {
               SA+=Item->A;
               Label2->Canvas->Rectangle((SA-Item->A)*scale,vt,SA*scale,vt+30);
               XC = (SA >= XC)? SA+Item->B : XC+Item->B;
               //Label2->Canvas->Rectangle((XC-Item->B)*scale,vt+40,XC*scale,vt+70);
               Label2->Canvas->TextOut((SA-Item->A)*scale+6,vt+6,Item->n);
               //Label2->Canvas->TextOut((XC-Item->B)*scale+6,vt+46,Item->n);
               if (Item->Next == NULL)      //Условие выхода из бесконечного цикла
                    break;
          }
          Label2->Canvas->TextOut(10,vt+75,"Время работы:");
          Label2->Canvas->TextOut(130,vt+75,XC);


          for (;;Item = Item->Prev)
          {
               Label2->Canvas->Rectangle((XC-Item->B)*scale,vt+40,XC*scale,vt+70);
               Label2->Canvas->TextOut((XC-Item->B)*scale+6,vt+46,Item->n);
               XC-=Item->B;
               if (Item->Prev == NULL)      //Условие выхода из бесконечного цикла
                    break;
          }
          //Label2->Canvas->TextOut(10,vt+75,"Время работы:");
          ///Label2->Canvas->TextOut(130,vt+75,XC);
     } */
}
     /*
void DeleteList (Node *Item)
{               //Функция удаляет список
     del++;
   if (Item->Next != NULL)
   {
      DeleteList (Item->Next);
   }
   ListBox2->Items->Add(Item->B);
   delete Item;
   Item = NULL;
   ListBox1->Items->Add(Item->B);
}           */

void DjonsonRun()
{
     (ListBox1->Items->Count)>(ListBox2->Items->Count) ? m = ListBox2->Items->Count : m = ListBox1->Items->Count;

     //m = point-1;
     StatusBar1->SimpleText=("DjonsonRun");

     int T[2];

     for (int i=0;i<m;i++)
     {
          T[0]=atoi(ListBox1->Items->Strings[i].c_str());
          T[1]=atoi(ListBox2->Items->Strings[i].c_str());
          Optimizer->add(2,T);
     }


          Optimizer->DjonsonRun();
          Memo1->Lines->Add("Исходная последовательность:");

          //MachineOptimizer::Link *list = Optimizer->InitBegin;
          paint(Optimizer->InitBegin);
          Memo1->Lines->Add("Оптимальная последовательность запуска деталей:");
          paint(Optimizer->Optimal);

     graphik = true;
     PaintGant();
}

void PetrovSokolRun()
{
     //Memo1->Lines->Add(StringGrid1->Rows[2]);
     //Memo1->Lines->Add(StringGrid1->Cells[4][1]);
     m=StringGrid1->ColCount-1;
     int *T = new int[m];
     for (int i = 1;i<StringGrid1->RowCount;i++)
     {
          for (int j = 1;j<StringGrid1->ColCount;j++)
          {
               T[j-1]=atof(StringGrid1->Cells[j][i].c_str());
          }
          //for (int k=0;k<StringGrid1->ColCount-1;k++)
          Optimizer->add(4,T);
     }
     Memo1->Lines->Add("INPUT:");
     PrintMatrix(Optimizer->InitBegin,4,false);

     Optimizer->PetrovSokolRun();

     Memo1->Lines->Add("PSBEGIN:");
     PrintMatrix(Optimizer->PSBegin,3,false);
     Memo1->Lines->Add("PSBEGIN PREV:");
     PrintMatrix(Optimizer->PSBegin,4,true);
     Memo1->Lines->Add("MATRIX PS:");
     top = new int[4];
     for (int i=0;i<4;i++)
          top[i]=0;
     PrintMatrixPS(Optimizer->PSBegin,4,0,0);

     //StatusBar1->SimpleText=("rowconub"+IntToStr(StringGrid1->RowCount)+" COLconub"+IntToStr(StringGrid1->ColCount));
}

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
//Сюда могут помещатся объявления типов, переменных, функций
//которые не включаются в класс формы

#endif
