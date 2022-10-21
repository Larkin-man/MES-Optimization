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
#include "Options.h"
#include <ActnList.hpp>
#include <ExtActns.hpp>
#include <ImgList.hpp>
#include <StdActns.hpp>
#include <time.h>
#include <stdlib.h>
#include "CGRID.h"
//---------------------------------------------------------------------------

#define max(A,B) (A>B ? A : B)


class TBaseForm : public TForm
{
__published:	// IDE-managed Components
     TMainMenu *MainMenu1;
     TPopupMenu *PopupMenuMemo;
     TMenuItem *NMenuFile;
     TMenuItem *NMenuEdit;
     TMenuItem *NMenuView;
     TMenuItem *NFont;
     TMenuItem *NViewOne;
     TMenuItem *N11;
     TMenuItem *N12;
     TFontDialog *FontDialog1;
     TStatusBar *StatusBar1;
     TMemo *Output;
     TMenuItem *N15;
     TMenuItem *NSize;
     TMenuItem *NMenuHelp;
     TMenuItem *NAbout;
     TMenuItem *NViewTwo;
     TRadioGroup *RadioGroup1;
     TPopupMenu *PopupMenuGant;
     TMenuItem *NGantRepaint;
     TMenuItem *NGantResize;
     TMenuItem *NGantFont;
     TMenuItem *NGantColor;
     TColorDialog *GantPenColor;
     TMenuItem *NMenuRun;
     TMenuItem *NOptSwitch;
     TMenuItem *NRun;
     TFontDialog *FontDialog2;
     TStringGrid *Table;
     TMenuItem *NGantTime;
     TMenuItem *N9;
     TPopupMenu *PopupMenuGrid;
     TMenuItem *N1;
     TMenuItem *NTranspon;
     TGroupBox *GroupBox1;
     TCheckBox *CheckBox1;
     TCheckBox *CheckBox2;
     TMenuItem *N2;
     TMenuItem *N3;
     TMenuItem *NMenuOptions;
     TMenuItem *NOptions;
     TToolBar *ToolBar1;
     TToolButton *ToolButton2;
     TSpeedButton *NewBtn;
     TSpeedButton *OpenBtn;
     TSpeedButton *SaveBtn;
     TToolButton *ToolButton1;
     TSpeedButton *RunBtn;
     TSpeedButton *OptimizationBtn;
     TToolButton *ToolButton4;
     TToolButton *ToolButton5;
     TToolButton *ToolButton6;
     TToolButton *ToolButton7;
     TTrackBar *TrackBar1;
     TStaticText *StaticText1;
     TToolButton *ToolButton3;
     TSpeedButton *GantBtn;
     TSpeedButton *ReportBtn;
     TMenuItem *NGant;
     TMenuItem *NReport;
     TActionList *ActionList1;
     TImageList *ImageList1;
     TFileOpen *FileOpen;
     TFileSaveAs *FileSave;
     TFileExit *FileExit;
     TFontEdit *FontEdit1;
     TAction *FileNew;
     TMenuItem *N4;
     TMenuItem *SaveAs1;
     TMenuItem *N6;
     TMenuItem *Exit1;
     TAction *Run;
     TAction *Optimization;
     TAction *GantDiagram;
     TAction *Report;
     TAction *ResizeTable;
     TMenuItem *Pf1;
     TMenuItem *N5;
     TPanel *Panel1;
     TLabel *Label1;
     TAction *Repaint;
     void __fastcall NFontClick(TObject *Sender);
     void __fastcall N15Click(TObject *Sender);
     void __fastcall NViewOneClick(TObject *Sender);
     void __fastcall NAboutClick(TObject *Sender);
     void __fastcall NViewTwoClick(TObject *Sender);
     void __fastcall N12Click(TObject *Sender);
     void __fastcall NGantFontClick(TObject *Sender);
     void __fastcall NGantColorClick(TObject *Sender);
     void __fastcall TrackBar1Change(TObject *Sender);
     void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
     void __fastcall N1Click(TObject *Sender);
     void __fastcall N2Click(TObject *Sender);
     void __fastcall NTransponClick(TObject *Sender);
     void __fastcall NOptionsClick(TObject *Sender);
     void __fastcall FileOpenAccept(TObject *Sender);
     void __fastcall FileNewExecute(TObject *Sender);
     void __fastcall FileSaveAccept(TObject *Sender);
     void __fastcall RunExecute(TObject *Sender);
     void __fastcall OptimizationExecute(TObject *Sender);
     void __fastcall GantDiagramExecute(TObject *Sender);
     void __fastcall ReportExecute(TObject *Sender);
     void __fastcall ResizeTableExecute(TObject *Sender);
     void __fastcall Pf1Click(TObject *Sender);
     void __fastcall RepaintExecute(TObject *Sender);
     void __fastcall NGantTimeClick(TObject *Sender);
private:	// User declarations
//Только в пределах данного модуля

public:		// User declarations
     MachineOptimizer *Optimizer;
     Graphics::TBitmap *Gant;
     int vertix,scale,i,j;
     int  BH,  //Block Height = 30 (не меньше 14!)
          BI,  //Block Interval
          TX,  //Text Out X = 5
          TY,  //Text Out Y = 8
          GantH,    //Gant Height
          GantW;    //Gant Weight
     bool graphik,ultima,debugging;
     int *top;
     int M,N; //M - Станки, N - Детали
     int TimeCycle[4];
     bool gantshow;
     TColor *Box;


     __fastcall TBaseForm(TComponent* Owner);  //Объявление конструктора

//void PrintMatrix(MachineOptimizer::Link *list,int m,bool down=false);
//     if(Key == VK_RETURN)       //ДЛЯ ФОКУСИРОВКИ
//          BitBtn1->SetFocus();
//Проверка видимости элементов
void view()
{
     Label1->Visible=NViewTwo->Checked;
     Panel1->Visible=NViewTwo->Checked;
     GroupBox1->Visible=NViewOne->Checked;
     StaticText1->Visible=NViewTwo->Checked;
     TrackBar1->Visible=NViewTwo->Checked;
}

void Print(MachineOptimizer::Link *list)
{
     for(;list != NULL;list = list->next)
          Output->Text=Output->Text+FloatToStr(list->curr->m)+" ";
}

void Ready()
{
     StatusBar1->Panels->Items[1]->Text=("Станков: "+IntToStr(N));
     StatusBar1->Panels->Items[2]->Text=("Деталей: "+IntToStr(M));
     if (OptionsForm->RadioGroupTime->ItemIndex != 2)
          StatusBar1->Panels->Items[3]->Text=("Длительность производственного цикла: "+IntToStr(ProductionCycle()));
     FileSave->Enabled=true;
     Run->Enabled=true;
     NTranspon->Enabled=true;
}
//Функция выводит матрицу. down - с переходом вниз по дереву; subtractb - с вычитанием матрицы длительностей
void PrintMatrix(MachineOptimizer::Link *list, int n, bool down, bool subtractb)
{
     //ShowMessage("n="+IntToStr(n));
     if (!subtractb)
     {
          MachineOptimizer::Node *Item;
          for (;list != NULL;list = list->next)
          {
               if (down)
                    Item = list->down->curr;      //Спустится вниз по дереву
               else
                    Item = list->curr;

               Output->Lines->Add("");
               Output->Text=Output->Text+IntToStr(Item->m)+"  |  ";
               for (int i = 0;i<n;i++)
                    Output->Text=Output->Text+IntToStr(Item->T[i])+"  ";
          }
     }
     else            
     {
          j=0;
          for (;list != NULL;list = list->next)
          {
               j++;
               Output->Lines->Add("");
               Output->Text=Output->Text+IntToStr(list->curr->m)+"  |  ";
               for (int i = 0;i<n;i++)
                    Output->Text=Output->Text+IntToStr(list->curr->T[i]-StrToInt(Table->Cells[i+1][j]))+"  ";
          }
     }
}


void PrintMatrixPS(MachineOptimizer::Link *list,int n,int one,int left)
{
     if (list != NULL)   //TODO: Убрать эту функцию
     {
          Output->Lines->Add(IntToStr(list->curr->m)+"  |  ");
          one+=list->down->curr->T[0];
          //ShowMessage("one = "+IntToStr(list->down->curr->T[1]));
          Output->Text=Output->Text+IntToStr(one)+"  ";
          left = one;
          int S=0;
          for (int i = 1;i<n;i++)
          {
               if (list->down == NULL)
               {
                    S+=list->down->curr->T[i];
                    top[i]=S;
                    //ShowMessage("S = "+IntToStr(S));
               }
               else
               {
                    S=max(top[i],left)+list->down->curr->T[i];
                    left=S;
                    top[i]=S;    
               }
               //ShowMessage("S = "+IntToStr(S));
               Output->Text=Output->Text+IntToStr(S)+"  ";
          }
          list = list->next;
          PrintMatrixPS(list,n,one,left);
     }
}
//Функция ищет длительность производственного цикла
int ProductionCycle()
{
     int *top = new int[N];
     int left;
     for (int i=0;i<N;i++)
          top[i]=0;
     for (int j=1;j<M+1;j++)
     {
          left=0;
          for (int i=1;i<N+1;i++)
          {
               top[i-1]=max(top[i-1],left);
               top[i-1]+=atoi(Table->Cells[i][j].c_str());
               left = top[i-1];
          }
     }
     return top[N-1];
}
//Функция рисует диаграмму Ганта c помощью матрицы длительностей обработки
void DrawDiagramFromDurationMatrix(MachineOptimizer::Link *List, bool down)
{
     vertix+=BH;
     Gant->Canvas->Brush->Color=GraphicForm->GantBrushColor->Color;
     int *SX = new int[N+1];
          for (int o = 0 ; o < N+1; o++)
               SX[o]=0;
     int del=0;
     MachineOptimizer::Node *Item;
     for (;List != NULL;List = List->next)   //По деталям
     {
          if (down)
               Item=List->down->curr;
          else
               Item=List->curr;
          for (int s = 0 ; s < N; s++)       //По станкам
          {
               //ShowMessage("s="+IntToStr(s)+" del="+IntToStr(del));
               //Table->Cells[s+1][del+4]=Item->down->curr->T[s];
               SX[s+1] = (SX[s] >= SX[s+1])? SX[s]+Item->T[s] : SX[s+1]+Item->T[s];
               Gant->Canvas->Rectangle((SX[s+1]-Item->T[s])*scale, vertix+(BH+BI)*s,
                         SX[s+1]*scale, vertix+(BH+BI)*s+BH);
               if (OptionsForm->WorkTimeOut->Checked)
                    Gant->Canvas->TextOut((SX[s+1]-Item->T[s])*scale+TX-5,vertix+(BH+BI)*s+TY,IntToStr(Item->m)+" ("+IntToStr(Item->T[s])+")");
               else
                    Gant->Canvas->TextOut((SX[s+1]-Item->T[s])*scale+TX,vertix+(BH+BI)*s+TY,Item->m);
          }
     }
     Gant->Canvas->Brush->Color=GraphicForm->ColorBox1->Selected;
     Gant->Canvas->TextOut(TX,vertix+(BH+BI)*N-BI+TY,"Время работы: "+FloatToStr(SX[N]));
     vertix=vertix+(BH+BI)*N-BI+BH;
     delete SX;
}
//Функция рисует диаграмму Ганта c помощью матрицы окончаний обработки (С)
void DrawDiagramFromEndingMatrix(MachineOptimizer::Link *Item)
{
     vertix+=BH;
     Gant->Canvas->Brush->Color=GraphicForm->GantBrushColor->Color;

     for (;Item != NULL;Item = Item->next)   //По деталям
          {
               for (int s = 0 ; s < N; s++)       //По станкам
               {
                    Gant->Canvas->Rectangle(((Item->curr->T[s])-(Item->down->curr->T[s]))*scale, vertix+(BH+BI)*s,
                              (Item->curr->T[s])*scale, vertix+(BH+BI)*s+BH);
                    if (OptionsForm->WorkTimeOut->Checked)
                         Gant->Canvas->TextOut(((Item->curr->T[s])-(Item->down->curr->T[s]))*scale+TX-5, vertix+(BH+BI)*s+TY, IntToStr(Item->curr->m)+" ("+IntToStr(Item->down->curr->T[s])+")");
                    else
                         Gant->Canvas->TextOut(((Item->curr->T[s])-(Item->down->curr->T[s]))*scale+TX, vertix+(BH+BI)*s+TY, Item->curr->m);
               }
          }
     Gant->Canvas->Brush->Color=GraphicForm->ColorBox1->Selected;
     Gant->Canvas->TextOut(TX,vertix+(BH+BI)*N-BI+TY,"Время работы: "+FloatToStr(TimeCycle[3]));
     vertix=vertix+(BH+BI)*N-BI+BH;
}

void PaintGant()
{
     if (!graphik) return;
     vertix=0;
     BH=30;
     BI=10;
     TX=(scale-8)/2;
     TY=(BH-14)/2;
     //if (Optimizer == NULL) return;
     //Label1->Repaint();    //TODO: repaint ?
     GantW=TimeCycle[0];
     for (int i=1;i<4;i++)
          if (TimeCycle[i] > GantW)
               GantW=TimeCycle[i];
     //ShowMessage("Gant weight="+IntToStr(GantW));
     GantW=GantW*scale+1;
     GantH=(BH+BI)*(N-1)*2+BH*6;
     Gant->Width=GantW;
     Gant->Height=GantH;
     Gant->Canvas->Pen->Color=GantPenColor->Color;
     Gant->Canvas->Pen->Width=1;
     //Gant->Canvas->Rectangle(0,0,Gant->Width,Gant->Height);
     Gant->Canvas->TextOut(TX,TY,"Исходные данные:");
     DrawDiagramFromDurationMatrix(Optimizer->InitBegin,false);
     Gant->Canvas->CopyMode=cmSrcCopy;
     //ShowMessage("jvj"+IntToStr(Optimizer->OptimalPS->down->curr->m));
     if ((RadioGroup1->ItemIndex == 0) && (Optimizer->OptimalDJ != NULL))
     {
          Gant->Canvas->TextOut(TX,vertix+TY,"Оптимизация по алгоритму Джонсона:");
          DrawDiagramFromDurationMatrix(Optimizer->OptimalDJ,false);
     }
     if ((RadioGroup1->ItemIndex == 1) && (Optimizer->PSBegin[1] != NULL))
     {
          Gant->Canvas->TextOut(TX,vertix+TY,"Оптимизация по методу Петрова-Соколицина:");
          DrawDiagramFromDurationMatrix(Optimizer->OptimalPS,true);
     }
     if ((RadioGroup1->ItemIndex == 2) && (Optimizer->OptimalBH != NULL))
     {
          Gant->Canvas->TextOut(TX,vertix+TY,"Оптимизация по методу ветвей и границ:");
          DrawDiagramFromEndingMatrix(Optimizer->OptimalBH);
     }

     Label1->Canvas->CopyMode = cmSrcCopy;
     Label1->Canvas->CopyRect(Rect(0,0,Label1->Width,Label1->Height),Gant->Canvas,Rect(0,0,Label1->Width,Label1->Height));
     if (gantshow)
          GraphicForm->gant->Canvas->CopyRect(Rect(0,0,GantW,GantH),Gant->Canvas,Rect(0,0,GantW,GantH));
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
     TimeCycle[1] = Optimizer->DjonsonRun();  //Запуск алгоритма джонсона
     //Output->Lines->Add("Исходная последовательность:");
     //MachineOptimizer::Link *list = Optimizer->InitBegin;
     //paint(Optimizer->InitBegin);
     Output->Lines->Add("Оптимальная последовательность запуска деталей:");
     //Print(Optimizer->Optimal);
     int *data = Optimizer->OutSequence;
     for (int i=0;i<M;i++)
          Output->Text=Output->Text+IntToStr(data[i])+" ";
     Output->Lines->Add("Длительность производственного цикла: "+IntToStr(TimeCycle[1]));
     Output->Lines->Add("");
     graphik = true;
     PaintGant();
}

void PetrovSokolMethod()
{
     StatusBar1->Panels->Items[0]->Text=("Метод Петрова-Соколицина");
     graphik = false;
     TimeCycle[2] = Optimizer->PetrovSokolRun(Output);   //Запуск алгоритма Петрова-Соколицина
     top = new int[N];

     Output->Lines->Add("Матрица сумм:");
     PrintMatrix(Optimizer->PSBegin[0],3,false,false);
     Output->Lines->Add(" ");

     Output->Lines->Add("Матрица 1:");
     PrintMatrix(Optimizer->PSBegin[1],N,true,false);
     Output->Lines->Add(" ");

     for (int i=0;i<N;i++)
          top[i]=0;

     Output->Lines->Add("Матрица 1 Сроки окончания:");
     PrintMatrixPS(Optimizer->PSBegin[1],N,0,0);
     Output->Lines->Add(" ");

     Output->Lines->Add("Матрица 2:");
     PrintMatrix(Optimizer->PSBegin[2],N,true,false);
     Output->Lines->Add(" ");

     for (int i=0;i<N;i++)
          top[i]=0;

     Output->Lines->Add("Матрица 2 Сроки окончания:");
     PrintMatrixPS(Optimizer->PSBegin[2],N,0,0);
     Output->Lines->Add(" ");

     Output->Lines->Add("Матрица 3:");
     PrintMatrix(Optimizer->PSBegin[3],N,true,false);
     Output->Lines->Add(" ");

     for (int i=0;i<N;i++)
          top[i]=0;

     Output->Lines->Add("Матрица 3 Сроки окончания:");
     PrintMatrixPS(Optimizer->PSBegin[3],N,0,0);
     Output->Lines->Add("");
     Output->Lines->Add("");
     Output->Lines->Add("Оптимальная последовательность запуска деталей: ");
     int *data = Optimizer->OutSequence;
     for (int i=0;i<M;i++)
          Output->Text=Output->Text+IntToStr(data[i])+" ";
     Output->Lines->Add("Длительность производственного цикла: "+IntToStr(TimeCycle[2]));
     Output->Lines->Add("");
     graphik = true;
     PaintGant();
}

void MethodBH () //Method  of branches and hordes
{
     StatusBar1->Panels->Items[0]->Text=("Метод ветвей и границ");
     graphik = false;
     if (OptionsForm->NoOut->Checked)
          TimeCycle[3]=Optimizer->MethodBHRun(NULL);
     else
          TimeCycle[3]=Optimizer->MethodBHRun(Output);
     Output->Lines->Add("Матрица С:");
     PrintMatrix(Optimizer->OptimalBH,N,false,false);
     Output->Lines->Add(" ");
     Output->Lines->Add("Матрица A:");
     PrintMatrix(Optimizer->OptimalBH,N,false,true);
     Output->Lines->Add(" ");
     Output->Lines->Add("Длительность производственного цикла: "+IntToStr(TimeCycle[3]));
     Output->Lines->Add("");
     graphik = true;
     PaintGant();
}

void garivogne()
{
          char str[50], *vx;
     //strcpy(str, Edit3->Text.c_str());
     vx = strchr(str,',');              //замена запятой на точку
     if (vx)
          str[vx-str]='.';
     //ListBox1->Items->Add(str);
     StatusBar1->SimpleText=("");
}

void TableRowColumnMoved()
{
     for (int i=1;i<Table->RowCount;i++)
          Table->Cells[0][i]="Деталь " + IntToStr(i)+":";
     for (int j=1;j<Table->ColCount;j++)
          Table->Cells[j][0]=j;
}

};
//---------------------------------------------------------------------------
extern PACKAGE TBaseForm *BaseForm;
//---------------------------------------------------------------------------
//Сюда могут помещатся объявления типов, переменных, функций
//которые не включаются в класс формы
class SequenceStartMethods
{
public:
     int Sequence[4];
     void addMethod(int MethodID)
     {
     }
     SequenceStartMethods()
     {
          for (int i = 0;i<4;i++)
               Sequence[i]=0;
     }

};


#endif
