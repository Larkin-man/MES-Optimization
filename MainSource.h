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
#include "Graphic.h"
//---------------------------------------------------------------------------

#define max(A,B) (A>B ? A : B)
MachineOptimizer *Optimizer;// = new MachineOptimizer;

class TForm1 : public TForm
{
__published:	// IDE-managed Components
     TMainMenu *MainMenu1;
     TPopupMenu *PopupMenuMemo;
     TMenuItem *NMenuFile;
     TMenuItem *NOpen;
     TMenuItem *NSave;
     TMenuItem *NExit;
     TMenuItem *NMenuEdit;
     TMenuItem *NMenuView;
     TMenuItem *NFont;
     TMenuItem *NViewOne;
     TMenuItem *N11;
     TMenuItem *N12;
     TPanel *Panel1;
     TEdit *Edit3;
     TLabel *Label4;
     TLabel *Label5;
     TLabel *Label6;
     TEdit *Edit4;
     TMenuItem *NNew;
     TLabel *Label7;
     TOpenDialog *OpenDialog1;
     TSaveDialog *SaveDialog1;
     TFontDialog *FontDialog1;
     TStatusBar *StatusBar1;
     TMemo *Output;
     TMenuItem *N15;
     TMenuItem *NAdd;
     TMenuItem *NDel;
     TMenuItem *NMenuHelp;
     TMenuItem *NAbout;
     TBitBtn *BitBtn1;
     TMenuItem *NViewTwo;
     TLabel *Label2;
     TLabel *Label3;
     TRadioGroup *RadioGroup1;
     TSpeedButton *SaveBtn;
     TSpeedButton *NewBtn;
     TSpeedButton *AddBtn;
     TSpeedButton *DelBtn;
     TBevel *Bevel1;
     TSpeedButton *OpenBtn;
     TPopupMenu *PopupMenuGant;
     TMenuItem *N25;
     TMenuItem *N26;
     TMenuItem *N27;
     TMenuItem *N28;
     TTrackBar *TrackBar1;
     TColorDialog *ColorDialog1;
     TBevel *Bevel2;
     TMenuItem *NMenuOptimiize;
     TMenuItem *NOptSwitch;
     TMenuItem *NOptSimulate;
     TFontDialog *FontDialog2;
     TSpeedButton *RunBtn;
     TBevel *Bevel3;
     TStringGrid *StringGrid1;
     TSpeedButton *OptimizationBtn;
     TMenuItem *N21;
     TSpeedButton *GantBtn;
     TMenuItem *N9;
     TPopupMenu *PopupMenuGrid;
     TMenuItem *N1;

     void __fastcall NExitClick(TObject *Sender);
     void __fastcall NOpenClick(TObject *Sender);
     void __fastcall NSaveClick(TObject *Sender);
     void __fastcall NFontClick(TObject *Sender);
     void __fastcall N15Click(TObject *Sender);
     void __fastcall NViewOneClick(TObject *Sender);
     void __fastcall NAboutClick(TObject *Sender);
     void __fastcall BitBtn1Click(TObject *Sender);
     void __fastcall NViewTwoClick(TObject *Sender);
     void __fastcall Edit3KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
     void __fastcall Edit4KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
     void __fastcall N12Click(TObject *Sender);
     void __fastcall FormPaint(TObject *Sender);
     void __fastcall N25Click(TObject *Sender);
     void __fastcall N27Click(TObject *Sender);
     void __fastcall N28Click(TObject *Sender);
     void __fastcall TrackBar1Change(TObject *Sender);
     void __fastcall NOptSwitchClick(TObject *Sender);
     void __fastcall RunBtnClick(TObject *Sender);
     void __fastcall RadioGroup1Click(TObject *Sender);
     void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
     void __fastcall NewBtnClick(TObject *Sender);
     void __fastcall GantBtnClick(TObject *Sender);
     void __fastcall N1Click(TObject *Sender);
private:	// User declarations
//Только в пределах данного модуля

public:		// User declarations

     int detal,vt,scale;
     double min[2];
     double SA,XC;
     bool graphik,ultima;
     int *top;
     int N,M;

     __fastcall TForm1(TComponent* Owner);  //Объявление конструктора

//void PrintMatrix(MachineOptimizer::Link *list,int m,bool prev=false);

void view() //Проверка видимости элементов
{
     //Output->Visible=N8->Checked;
     Panel1->Visible=NViewTwo->Checked;
     RunBtn->Enabled=(RadioGroup1->ItemIndex!=-1);

}


void paint(MachineOptimizer::Link *list)
{
     for(;list != NULL;list = list->next)
     {
     //Output->Lines->Add(list->curr->n);
     Output->Text=Output->Text+" "+FloatToStr(list->curr->n);
     }
}

void PrintMatrix(MachineOptimizer::Link *list,int m,bool prev)
{
     if (list != NULL)
     {
          if (!prev)
          {      
               Output->Lines->Add(IntToStr(list->curr->n)+"  |  ");
               for (int i = 0;i<m;i++)
                    Output->Text=Output->Text+IntToStr(list->curr->T[i])+"  ";   
          }
          else
          {
               Output->Lines->Add(IntToStr(list->prev->curr->n)+"  |  ");
               for (int i = 0;i<m;i++)
                    Output->Text=Output->Text+IntToStr(list->prev->curr->T[i])+"  ";
          }
          list = list->next;
          PrintMatrix(list,m,prev);
     }
}

void PrintMatrixPS(MachineOptimizer::Link *list,int m,int one,int left)
{
     if (list != NULL)
     {
          Output->Lines->Add(IntToStr(list->curr->n)+"  |  ");
          one+=list->prev->curr->T[0];
          //ShowMessage("one = "+IntToStr(list->prev->curr->T[1]));
          Output->Text=Output->Text+IntToStr(one)+"  ";
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
               Output->Text=Output->Text+IntToStr(S)+"  ";
          }
          list = list->next;
          PrintMatrixPS(list,m,one,left);
     }
}

void paintn(MachineOptimizer::Link *list)
{
     for(;list != NULL;list = list->next)
     {
     //Output->Lines->Add(list->curr->n);
     Output->Text=Output->Text+" "+FloatToStr(list->curr->n);
     }
}

void paintUUU(MachineOptimizer::Link *list)
{
     for(;list != NULL;list = list->next)
     {
     //Output->Lines->Add(list->curr->n);
     Output->Text=Output->Text+" "+FloatToStr(list->prev->curr->T[0]);
     }
}

void PaintBlock(MachineOptimizer::Link *Item)
{
     SA=0,XC=0;
     for (;Item != NULL;Item = Item->next)
     {
          SA+=Item->curr->T[0];
          Label2->Canvas->Rectangle((SA-Item->curr->T[0])*scale,vt,SA*scale,vt+30);
          Form3->gant->Canvas->Rectangle((SA-Item->curr->T[0])*scale,vt,SA*scale,vt+30);
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
     if (!graphik) return;
     //if (Optimizer == NULL) return;
     Label2->Repaint();    //TODO: repaint ?
     Label2->Canvas->Pen->Width=1;
     Label2->Canvas->TextOut(5,5,"Исходные данные:");

     Form3->gant->Repaint();
     Form3->gant->Canvas->Pen->Width=1;
     Form3->gant->Canvas->TextOut(5,5,"Исходные данные:");

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

void DjonsonRun()
{
     StatusBar1->Panels->Items[0]->Text=("Алгоритм Джонсона для двух станков");
     graphik = false;
     delete Optimizer;
     Optimizer = new MachineOptimizer;  //Экземпляр класса, необходимый для работы. Объявлен в библиотеке OptimizationMtds.h
     int T[2];

     for (int i=1;i<N+1;i++)
     {
          T[0]=atoi(StringGrid1->Cells[1][i].c_str());
          T[1]=atoi(StringGrid1->Cells[M][i].c_str());
          Optimizer->add(2,T);
     }
          Optimizer->DjonsonRun();  //Запуск алгоритма джонсона
          Output->Lines->Add("Исходная последовательность:");

          //MachineOptimizer::Link *list = Optimizer->InitBegin;
          paint(Optimizer->InitBegin);
          Output->Lines->Add("Оптимальная последовательность запуска деталей:");
          paint(Optimizer->Optimal);

     graphik = true;
     PaintGant();
}

void PetrovSokolRun()
{
     StatusBar1->Panels->Items[0]->Text=("Метод Петрова-Соколицина");
     graphik = false;
     delete Optimizer;
     Optimizer = new MachineOptimizer;
     int *T = new int[M];
     for (int i = 1;i<N+1;i++)      //i<StringGrid1->RowCount
     {
          for (int j = 1;j<M+1;j++)     //j<StringGrid1->ColCount
          {
               T[j-1]=atof(StringGrid1->Cells[j][i].c_str());
          }
          //for (int k=0;k<StringGrid1->ColCount-1;k++)
          Optimizer->add(4,T);
     }
     Output->Lines->Add("Исходная матрица:");
     PrintMatrix(Optimizer->InitBegin,M,false);
     Output->Lines->Add(" ");
     
     Optimizer->PetrovSokolRun();   //Запуск алгоритма Петрова-Соколицина
     top = new int[M];

     Output->Lines->Add("Матрица сумм:");
     PrintMatrix(Optimizer->PSBegin[0],3,false);
     Output->Lines->Add(" ");

     Output->Lines->Add("Матрица 1:");
     PrintMatrix(Optimizer->PSBegin[1],M,true);
     Output->Lines->Add(" ");

     for (int i=0;i<M;i++)
          top[i]=0;

     Output->Lines->Add("Матрица 1 Сроки окончания:");
     PrintMatrixPS(Optimizer->PSBegin[1],M,0,0);
     Output->Lines->Add(" ");

     Output->Lines->Add("Матрица 2:");
     PrintMatrix(Optimizer->PSBegin[2],M,true);
     Output->Lines->Add(" ");

     for (int i=0;i<M;i++)
          top[i]=0;

     Output->Lines->Add("Матрица 2 Сроки окончания:");
     PrintMatrixPS(Optimizer->PSBegin[2],M,0,0);
     Output->Lines->Add(" ");

     Output->Lines->Add("Матрица 3:");
     PrintMatrix(Optimizer->PSBegin[3],M,true);
     Output->Lines->Add(" ");

     for (int i=0;i<M;i++)
          top[i]=0;

     Output->Lines->Add("Матрица 3 Сроки окончания:");
     PrintMatrixPS(Optimizer->PSBegin[3],M,0,0);
     Output->Lines->Add("");
     //StatusBar1->SimpleText=("rowconub"+IntToStr(StringGrid1->RowCount)+" COLconub"+IntToStr(StringGrid1->ColCount));
}

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
//Сюда могут помещатся объявления типов, переменных, функций
//которые не включаются в класс формы

#endif
