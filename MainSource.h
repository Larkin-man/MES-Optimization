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
#include "EnterData.h"
//---------------------------------------------------------------------------

#define max(A,B) (A>B ? A : B)


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
     TMenuItem *NNew;
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
     TMenuItem *NViewTwo;
     TLabel *Label2;
     TLabel *Label3;
     TRadioGroup *RadioGroup1;
     TSpeedButton *SaveBtn;
     TSpeedButton *NewBtn;
     TSpeedButton *OpenBtn;
     TPopupMenu *PopupMenuGant;
     TMenuItem *NGantRepaint;
     TMenuItem *NGantResize;
     TMenuItem *NGantFont;
     TMenuItem *NGantColor;
     TTrackBar *TrackBar1;
     TColorDialog *ColorDialog1;
     TBevel *Bevel2;
     TMenuItem *NMenuOptimiize;
     TMenuItem *NOptSwitch;
     TMenuItem *NOptSimulate;
     TFontDialog *FontDialog2;
     TSpeedButton *RunBtn;
     TBevel *Bevel3;
     TStringGrid *Table;
     TSpeedButton *OptimizationBtn;
     TMenuItem *NGantTime;
     TSpeedButton *GantBtn;
     TMenuItem *N9;
     TPopupMenu *PopupMenuGrid;
     TMenuItem *N1;
     TMenuItem *NTranspon;
     TGroupBox *GroupBox1;
     TCheckBox *CheckBox1;
     TCheckBox *CheckBox2;
     TMenuItem *N2;
     TMenuItem *N3;

     void __fastcall NExitClick(TObject *Sender);
     void __fastcall NOpenClick(TObject *Sender);
     void __fastcall NSaveClick(TObject *Sender);
     void __fastcall NFontClick(TObject *Sender);
     void __fastcall N15Click(TObject *Sender);
     void __fastcall NViewOneClick(TObject *Sender);
     void __fastcall NAboutClick(TObject *Sender);
     void __fastcall BitBtn1Click(TObject *Sender);
     void __fastcall NViewTwoClick(TObject *Sender);
     void __fastcall N12Click(TObject *Sender);
     void __fastcall FormPaint(TObject *Sender);
     void __fastcall NGantRepaintClick(TObject *Sender);
     void __fastcall NGantFontClick(TObject *Sender);
     void __fastcall NGantColorClick(TObject *Sender);
     void __fastcall TrackBar1Change(TObject *Sender);
     void __fastcall NOptSwitchClick(TObject *Sender);
     void __fastcall RunBtnClick(TObject *Sender);
     void __fastcall RadioGroup1Click(TObject *Sender);
     void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
     void __fastcall NewBtnClick(TObject *Sender);
     void __fastcall GantBtnClick(TObject *Sender);
     void __fastcall N1Click(TObject *Sender);
     void __fastcall N2Click(TObject *Sender);
     void __fastcall N3Click(TObject *Sender);
private:	// User declarations
//Только в пределах данного модуля

public:		// User declarations
     MachineOptimizer *Optimizer;// = new MachineOptimizer;
     int vt,scale;
     double min[2];
     double SA,XC;
     bool graphik,ultima;
     int *top;
     int M,N; //M - Станки, N - Детали

     __fastcall TForm1(TComponent* Owner);  //Объявление конструктора

//void PrintMatrix(MachineOptimizer::Link *list,int m,bool prev=false);
//     if(Key == VK_RETURN)       //ДЛЯ ФОКУСИРОВКИ
//          BitBtn1->SetFocus();

void view() //Проверка видимости элементов
{
     //Panel1->Visible=NViewTwo->Checked;
     RunBtn->Enabled=(RadioGroup1->ItemIndex!=-1);
     Label2->Visible=NViewTwo->Checked;
     Bevel2->Visible=NViewTwo->Checked;
     GroupBox1->Visible=NViewOne->Checked;
     Label3->Visible=NViewTwo->Checked;
     TrackBar1->Visible=NViewTwo->Checked;
}

void paint(MachineOptimizer::Link *list)
{
     for(;list != NULL;list = list->next)
     {
     //Output->Lines->Add(list->curr->M);
     Output->Text=Output->Text+" "+FloatToStr(list->curr->m);
     }
}

void PrintMatrix(MachineOptimizer::Link *list,int m,bool prev)
{
     if (list != NULL)
     {
          if (!prev)
          {      
               Output->Lines->Add(IntToStr(list->curr->m)+"  |  ");
               for (int i = 0;i<m;i++)
                    Output->Text=Output->Text+IntToStr(list->curr->T[i])+"  ";   
          }
          else
          {
               Output->Lines->Add(IntToStr(list->prev->curr->m)+"  |  ");
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
          Output->Lines->Add(IntToStr(list->curr->m)+"  |  ");
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
     //Output->Lines->Add(list->curr->M);
     Output->Text=Output->Text+" "+FloatToStr(list->curr->m);
     }
}

void paintUUU(MachineOptimizer::Link *list)
{
     for(;list != NULL;list = list->next)
     {
     //Output->Lines->Add(list->curr->M);
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
          Label2->Canvas->TextOut((SA-Item->curr->T[0])*scale+6,vt+6,Item->curr->m);
          Label2->Canvas->TextOut((XC-Item->curr->T[1])*scale+6,vt+46,Item->curr->m);
             Form3->gant->Canvas->Rectangle((XC-Item->curr->T[1])*scale,vt+40,XC*scale,vt+70);
             Form3->gant->Canvas->TextOut((SA-Item->curr->T[0])*scale+6,vt+6,Item->curr->m);
             Form3->gant->Canvas->TextOut((XC-Item->curr->T[1])*scale+6,vt+46,Item->curr->m);
     }
     Label2->Canvas->TextOut(10,vt+75,"Время работы:");
     Label2->Canvas->TextOut(125,vt+75,XC);
        Form3->gant->Canvas->TextOut(10,vt+75,"Время работы:");
        Form3->gant->Canvas->TextOut(125,vt+75,XC);
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
               Label2->Canvas->TextOut((SA-Item->A)*scale+6,vt+6,Item->M);
               //Label2->Canvas->TextOut((XC-Item->B)*scale+6,vt+46,Item->M);
               if (Item->Next == NULL)      //Условие выхода из бесконечного цикла
                    break;
          }
          Label2->Canvas->TextOut(10,vt+75,"Время работы:");
          Label2->Canvas->TextOut(130,vt+75,XC);


          for (;;Item = Item->Prev)
          {
               Label2->Canvas->Rectangle((XC-Item->B)*scale,vt+40,XC*scale,vt+70);
               Label2->Canvas->TextOut((XC-Item->B)*scale+6,vt+46,Item->M);
               XC-=Item->B;
               if (Item->Prev == NULL)      //Условие выхода из бесконечного цикла
                    break;
          }
          //Label2->Canvas->TextOut(10,vt+75,"Время работы:");
          ///Label2->Canvas->TextOut(130,vt+75,XC);
     } */
}

void DjonsonAlgorithm()
{
     StatusBar1->Panels->Items[0]->Text=("Алгоритм Джонсона для двух станков");
     graphik = false;
     delete Optimizer;
     Optimizer = new MachineOptimizer;  //Экземпляр класса, необходимый для работы. Объявлен в библиотеке OptimizationMtds.h
     int T[2];

     for (int i=1;i<M+1;i++)
     {
          T[0]=atoi(Table->Cells[1][i].c_str());
          T[1]=atoi(Table->Cells[N][i].c_str());
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

void PetrovSokolMethod()
{
     StatusBar1->Panels->Items[0]->Text=("Метод Петрова-Соколицина");
     graphik = false;
     delete Optimizer;
     Optimizer = new MachineOptimizer;
     int *T = new int[N];
     for (int i = 1;i<M+1;i++)
     {
          for (int j = 1;j<N+1;j++)
          {
               T[j-1]=atof(Table->Cells[j][i].c_str());
          }
          Optimizer->add(N,T);
     }
     Output->Lines->Add("Исходная матрица:");
     PrintMatrix(Optimizer->InitBegin,N,false);
     Output->Lines->Add(" ");
     
     Optimizer->PetrovSokolRun();   //Запуск алгоритма Петрова-Соколицина
     top = new int[N];

     Output->Lines->Add("Матрица сумм:");
     PrintMatrix(Optimizer->PSBegin[0],3,false);
     Output->Lines->Add(" ");

     Output->Lines->Add("Матрица 1:");
     PrintMatrix(Optimizer->PSBegin[1],N,true);
     Output->Lines->Add(" ");

     for (int i=0;i<N;i++)
          top[i]=0;

     Output->Lines->Add("Матрица 1 Сроки окончания:");
     PrintMatrixPS(Optimizer->PSBegin[1],N,0,0);
     Output->Lines->Add(" ");

     Output->Lines->Add("Матрица 2:");
     PrintMatrix(Optimizer->PSBegin[2],N,true);
     Output->Lines->Add(" ");

     for (int i=0;i<N;i++)
          top[i]=0;

     Output->Lines->Add("Матрица 2 Сроки окончания:");
     PrintMatrixPS(Optimizer->PSBegin[2],N,0,0);
     Output->Lines->Add(" ");

     Output->Lines->Add("Матрица 3:");
     PrintMatrix(Optimizer->PSBegin[3],N,true);
     Output->Lines->Add(" ");

     for (int i=0;i<N;i++)
          top[i]=0;

     Output->Lines->Add("Матрица 3 Сроки окончания:");
     PrintMatrixPS(Optimizer->PSBegin[3],N,0,0);
     Output->Lines->Add("");
     //StatusBar1->SimpleText=("rowconub"+IntToStr(Table->RowCount)+" COLconub"+IntToStr(Table->ColCount));
}

void MethodBH () //Method  of branches and hordes
{
     int s=1,o=1,d=1;
     //TODO: Это тоже самое что и ПС. убрать в нажатие Расчет
     StatusBar1->Panels->Items[0]->Text=("Метод ветвей и границ");
     graphik = false;
     delete Optimizer;
     Optimizer = new MachineOptimizer;
     int *T = new int[N];
     for (int i = 1;i<M+1;i++)
     {
          for (int j = 1;j<N+1;j++)
          {
               T[j-1]=atof(Table->Cells[j][i].c_str());
          }
          Optimizer->add(N,T);
     }
     Output->Lines->Add("Исходная матрица:");
     PrintMatrix(Optimizer->InitBegin,N,false);
     Output->Lines->Add(" ");

     Optimizer->MethodBHRun();
     Output->Lines->Add("Матрица С:");
     PrintMatrix(Optimizer->C,N,false);
     Output->Lines->Add(" ");
}

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
//Сюда могут помещатся объявления типов, переменных, функций
//которые не включаются в класс формы

#endif
