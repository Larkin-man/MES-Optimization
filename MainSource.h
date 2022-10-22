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
#include "CSPIN.h"
//---------------------------------------------------------------------------

#define max(A,B) (A>B ? A : B)

class TBaseForm : public TForm
{
__published:	// IDE-managed Components
     TMainMenu *MainMenu1;
     TPopupMenu *PopupMenuMemo;
     TMenuItem *NMenuFile;
     TMenuItem *NMenuEdit;
   TMenuItem *NFont1;
   TMenuItem *NClear1;
     TStatusBar *StatusBar1;
     TMemo *Output;
   TMenuItem *NCopy;
     TMenuItem *NSize;
     TMenuItem *NMenuHelp;
     TMenuItem *NAbout;
     TRadioGroup *RadioGroup1;
     TMenuItem *NMenuRun;
     TMenuItem *NOptSwitch;
     TMenuItem *NRun;
     TMenuItem *N9;
     TPopupMenu *PopupMenuGrid;
   TMenuItem *NTest;
     TMenuItem *NTranspon;
   TMenuItem *NClear2;
   TMenuItem *NResize2;
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
     TFontEdit *FontEdit;
     TAction *FileNew;
     TMenuItem *NOpen;
     TMenuItem *NSaveAs;
     TMenuItem *NNew;
     TMenuItem *NExit;
     TAction *Run;
     TAction *Optimization;
     TAction *GantDiagram;
     TAction *Report;
     TAction *ResizeTable;
   TMenuItem *NRandom2;
   TMenuItem *NRun2;
     TAction *Repaint;
     TToolButton *ToolButton8;
     TSpeedButton *SpeedButton1;
     TMenuItem *NRandom;
     TAction *Random;
   TMenuItem *NFont2;
     TStringGrid *Table;
     TMenuItem *NManualMode;
   TPanel *Panel1;
   TStringGrid *ManualTable;
   TSpeedButton *SpeedButton2;
     TLabel *Label1;
     TLabel *Label2;
     TCSpinButton *CSpinButton1;
     void __fastcall NCopyClick(TObject *Sender);
     void __fastcall NAboutClick(TObject *Sender);
     void __fastcall NClear1Click(TObject *Sender);
     void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
     void __fastcall NTestClick(TObject *Sender);
     void __fastcall NClear2Click(TObject *Sender);
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
     void __fastcall FontEditAccept(TObject *Sender);
     void __fastcall TableColumnMoved(TObject *Sender, int FromIndex,
          int ToIndex);
     void __fastcall TableRowMoved(TObject *Sender, int FromIndex,
          int ToIndex);
     void __fastcall SpeedButton1Click(TObject *Sender);
     void __fastcall RandomExecute(TObject *Sender);
     void __fastcall StatusBar1DblClick(TObject *Sender);
     void __fastcall FontEditBeforeExecute(TObject *Sender);
     void __fastcall NManualModeClick(TObject *Sender);
private:	// User declarations
//Только в пределах данного модуля

public:		// User declarations
     __fastcall TBaseForm(TComponent* Owner);  //Объявление конструктора
     MachineOptimizer *Optimizer;
     Graphics::TBitmap *Gant;
     int vertix,scale,i,j;
     int  BH,  //Block Height = 30 (не меньше 14!)
          BI,  //Block Interval = 10
          TX,  //Text Out X = 5
          TY,  //Text Out Y = 8
          GantH,    //Gant Height
          GantW;    //Gant Weight
     int M,N; //N - Станки, M - Детали
     int TimeCycle[4];
     bool gantshow;
     TColor *ColorBox;   //Колорпит для разноцветных красивых блоков
     int Brightness;     //Яркость
     bool multicoloured;

//Готовность к запуску расчета
void Ready(bool Access)
{    
     FileSave->Enabled=Access;
     Optimization->Enabled=Access;
     GantDiagram->Enabled=Access;
     Report->Enabled=Access;
}

void Swapf()
{
     StatusBar1->Panels->Items[0]->Width=400;
     StatusBar1->Panels->Items[1]->Text=("Станков: "+IntToStr(N));
     StatusBar1->Panels->Items[2]->Text=("Деталей: "+IntToStr(M));
     StatusBar1->Panels->Items[3]->Text=("Длительность производственного цикла: "+IntToStr(ProductionCycle()));
     NTranspon->Enabled=true;
}
//Обновить таблицу
void TableRefresh()
{
     Table->Cells[0][0]="    Станок:";
     //Строки - детали Столбцы - станки
     for (int i=1;i<Table->RowCount;i++)
          Table->Cells[0][i]="Деталь " + IntToStr(i)+":";
     for (int j=1;j<Table->ColCount;j++)
          Table->Cells[j][0]=j;//"Станок №"+i;
     if (Table->RowCount <= 10)
          Table->ColWidths[0]=82;
     else if (Table->RowCount <= 100)
          Table->ColWidths[0]=88;
     else
          Table->ColWidths[0]=96;  
}
//Генератор случайных цветов
void ColorPit()
{
     TColor red,green,blue;
     srand(time(NULL));
     for (int i = 0;i<M;i++)
     {
     red=TColor(rand()%(256-Brightness)+Brightness);
     green=TColor(rand()%(255-Brightness)+Brightness);
     blue=TColor(rand()%(255-Brightness)+Brightness);
     if(OptionsForm->Contrast->Checked)
     {
          int c=rand()%6;
          switch (c)
          {
               case 0: red=TColor(red-Brightness);
                    break;
               case 1: green=TColor(green-Brightness);
                    break;
               case 2: blue=TColor(blue-Brightness);
                    break;
               case 3: blue=TColor(blue-Brightness);
                       red=TColor(red-Brightness);
                    break;
               case 4: blue=TColor(blue-Brightness);
                       green=TColor(green-Brightness);
                    break;
               case 5: red=TColor(red-Brightness);
                       green=TColor(green-Brightness);
                    break;
          }
     }


     green=TColor(green*256+256);
     blue=TColor(blue*256*256+256*256);

     ColorBox[i]=TColor(blue+green+red);
     }
     //ToolBar1->Color=red;
     //RadioGroup1->Color=green;
     //Table->Color=blue;
}

//Функция выводит матрицу. down - с переходом вниз по дереву; subtractb - с вычитанием матрицы длительностей
void PrintMatrix(const MachineOptimizer::Link *list, int n, bool down, bool subtractb)
{
     //ShowMessage("n="+IntToStr(n));
     if (!subtractb)
     {
          MachineOptimizer::Detal *Item;
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
                    Output->Text=Output->Text+IntToStr(list->curr->T[i]-atoi(Table->Cells[i+1][j].c_str()))+"  ";
          }
     }
}

//Функция ищет длительность производственного цикла
int ProductionCycle()
{
     float *top = new float[N];
     float left;
     for (int i=0;i<N;i++)
          top[i]=0;
     for (int j=1;j<M+1;j++)
     {
          left=0;
          for (int i=1;i<N+1;i++)
          {
               top[i-1]=max(top[i-1],left);
               top[i-1]+=atof(Table->Cells[i][j].c_str());
               left = top[i-1];
          }
     }
     delete [] top;
     return left;
}
//Функция рисует диаграмму Ганта c помощью матрицы длительностей обработки
void DrawDiagramFromDurationMatrix(const MachineOptimizer::Link *List, bool down)
{
     vertix+=BH;
     int N = Optimizer->GetN();
     int *SX = new int[N+1];
          for (int o = 0 ; o < N+1; o++)
               SX[o]=0;
     MachineOptimizer::Detal *Item;
     for (;List != NULL;List = List->next)   //По деталям
     {
          if (down)
               Item=List->down->curr;
          else
               Item=List->curr;
          if (multicoloured)
               Gant->Canvas->Brush->Color=ColorBox[Item->m-1];
          else
               Gant->Canvas->Brush->Color=GraphicForm->GantBrushColor->Color;
          for (int s = 0 ; s < N; s++)       //По станкам
          {
               //ShowMessage("s="+IntToStr(s)+" del="+IntToStr(del));
               //Table->Cells[s+1][del+4]=Item->down->curr->T[s];
               SX[s+1] = (SX[s] >= SX[s+1])? SX[s]+Item->T[s] : SX[s+1]+Item->T[s];
               Gant->Canvas->Rectangle((SX[s+1]-Item->T[s])*scale, vertix+(BH+BI)*s,
                         SX[s+1]*scale, vertix+(BH+BI)*s+BH);
               if (OptionsForm->WorkTimeOut->Checked)
                    Gant->Canvas->TextOut((SX[s+1]-Item->T[s])*scale+1,vertix+(BH+BI)*s+TY,IntToStr(Item->m)+" ("+IntToStr(Item->T[s])+")");
               else
                    Gant->Canvas->TextOut((SX[s+1]-Item->T[s])*scale+TX,vertix+(BH+BI)*s+TY,Item->m);
          }
     }
     Gant->Canvas->Brush->Color=GraphicForm->ColorBox1->Selected;
     Gant->Canvas->TextOut(TX,vertix+(BH+BI)*N-BI+TY,"Время работы: "+FloatToStr(SX[N]));
     vertix=vertix+(BH+BI)*N-BI+BH;
     delete [] SX;
}
//Функция рисует диаграмму Ганта c помощью матрицы окончаний обработки (С)
void DrawDiagramFromEndingMatrix(const MachineOptimizer::Link *Item)
{
     vertix+=BH;
     int N = Optimizer->GetN();
     for (;Item != NULL;Item = Item->next)   //По деталям
          {
          if (multicoloured)
               Gant->Canvas->Brush->Color=ColorBox[Item->curr->m-1];
          else
               Gant->Canvas->Brush->Color=GraphicForm->GantBrushColor->Color;
               for (int s = 0 ; s < N; s++)       //По станкам
               {
                    Gant->Canvas->Rectangle(((Item->curr->T[s])-(Item->down->curr->T[s]))*scale, vertix+(BH+BI)*s,
                              (Item->curr->T[s])*scale, vertix+(BH+BI)*s+BH);
                    if (OptionsForm->WorkTimeOut->Checked)
                         Gant->Canvas->TextOut(((Item->curr->T[s])-(Item->down->curr->T[s]))*scale+1, vertix+(BH+BI)*s+TY, IntToStr(Item->curr->m)+" ("+IntToStr(Item->down->curr->T[s])+")");
                    else
                         Gant->Canvas->TextOut(((Item->curr->T[s])-(Item->down->curr->T[s]))*scale+TX, vertix+(BH+BI)*s+TY, Item->curr->m);
               }
          } 
     Gant->Canvas->Brush->Color=GraphicForm->ColorBox1->Selected;
     Gant->Canvas->TextOut(TX,vertix+(BH+BI)*N-BI+TY,"Время работы: "+FloatToStr(TimeCycle[3]));
     vertix=vertix+(BH+BI)*N-BI+BH;
}
//Создание диаграммы Ганта и подготовка к рисованию
void PaintGant()
{
     if (!gantshow)
          return;
     delete Gant;
     Gant = new Graphics::TBitmap;    
     vertix=0;
     int N = Optimizer->GetN();
     TX=(scale-8)/2;
     TY=(BH-14)/2;
     //if (Optimizer == NULL) return;
     GantW=TimeCycle[0];
     for (int i=1;i<4;i++)
          if (TimeCycle[i] > GantW)
               GantW=TimeCycle[i];
     //ShowMessage("Gant weight="+IntToStr(GantW));
     GantW=GantW*scale+2;
     GantH=(BH+BI)*(N-1)*2+BH*6;
     Gant->Width=GantW;
     Gant->Height=GantH;
     Gant->Canvas->Pen->Color=clBlack;
     Gant->Canvas->Pen->Width=1;
     Gant->Canvas->Brush->Color=GraphicForm->ColorBox1->Selected;
     Gant->Canvas->FillRect(Rect(0,0,GantW,GantH));
     //Gant->Canvas->Rectangle(0,0,Gant->Width,Gant->Height);
     Gant->Canvas->TextOut(TX,TY,"Исходные данные:");
     DrawDiagramFromDurationMatrix(Optimizer->InitBegin,false);
     Gant->Canvas->CopyMode=cmSrcCopy;
     if ((RadioGroup1->ItemIndex == 0) && (Optimizer->OptimalDJ != NULL))    //TODO: switch case
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
     if ((RadioGroup1->ItemIndex == 3) && (Optimizer->OptimalBH != NULL))
     {
          Gant->Canvas->TextOut(TX,vertix+TY,"Оптимизация по модифицированому методу ветвей и границ:");
          DrawDiagramFromEndingMatrix(Optimizer->OptimalBH);
     }
     if ((RadioGroup1->ItemIndex == 4) && (Optimizer->OptimalNew != NULL))
     {
          //ShowMessage("IHHA");
          Gant->Canvas->TextOut(TX,vertix+TY,"Оптимизация по новому методу:");
           DrawDiagramFromDurationMatrix(Optimizer->OptimalNew,false);
     }

     GraphicForm->ClearGantField();
    // if (gantshow)
    //      GraphicForm->DrawGant(GraphicForm->ScrollBar1->Position,GraphicForm->ScrollBar2->Position);


}

void DrawGant(int PosX, int PosY)
{
     int FormH=GraphicForm->gant->ClientHeight;
     int FormW=GraphicForm->gant->ClientWidth;
     int K;
     if (GantW > FormW)
     {
          GraphicForm->ScrollBar1->Enabled=true;
          K = GantW - FormW;
          GraphicForm->ScrollBar1->Max=K+50;
     }
     else
          GraphicForm->ScrollBar1->Enabled=false;

     if (GantH > FormH)
     {
          GraphicForm->ScrollBar2->Enabled=true;
          K = GantH - FormH;
          GraphicForm->ScrollBar2->Max=K+50;
     }
     else
          GraphicForm->ScrollBar2->Enabled=false;

     GraphicForm->gant->Canvas->CopyRect(
               Rect(0,0,FormW,FormH),
               Gant->Canvas,
               Rect(PosX,PosY,FormW+PosX,FormH+PosY));

}


//Пересчитать масштаб диаграммы
void CountScale(int Scroller = 5)
{
     scale=Scroller+12+Scroller/3;
     if (OptionsForm->WorkTimeOut->Checked)
          scale+=4;
     BI=OptionsForm->SpinBI->Value;
     if (OptionsForm->HeightScaling->Checked)
     {
          BH=26+Scroller/2;
          BI=BH/3;         
     }
}

void DjonsonAlgorithm()
{
     StatusBar1->Panels->Items[0]->Text=("Алгоритм Джонсона для двух станков");
     TimeCycle[1] = Optimizer->DjonsonRun();  //Запуск алгоритма джонсона
     if (!(OptionsForm->NoOut->Checked))
     {
          Output->Lines->Add("Оптимальная последовательность запуска деталей:");
          int *data = Optimizer->OutSequence;
          for (int i=0;i<M;i++)
               Output->Text=Output->Text+IntToStr(data[i])+" ";
          Output->Lines->Add("Длительность производственного цикла: "+IntToStr(TimeCycle[1]));
          Output->Lines->Add("");
     }
}

void PetrovSokolMethod()
{
     StatusBar1->Panels->Items[0]->Text=("Метод Петрова-Соколицина");
     TimeCycle[2] = Optimizer->PetrovSokolRun();   //Запуск алгоритма Петрова-Соколицина
     top = new int[N];

     if (!(OptionsForm->NoOut->Checked))
     {
          Output->Lines->Add("Матрица сумм:");
          PrintMatrix(Optimizer->PSBegin[0],3,false,false);
          Output->Lines->Add(" ");

          Output->Lines->Add("Сортировка по возрастанию первого столбца:");
          PrintMatrix(Optimizer->PSBegin[1],N,true,false);
          Output->Lines->Add(" ");

          for (int i=0;i<N;i++)
               top[i]=0;

          Output->Lines->Add("Матрица 1 Сроки окончания:");
          PrintMatrixPS(Optimizer->PSBegin[1],N,0,0);
          Output->Lines->Add(" ");

          Output->Lines->Add("Сортировка по убыванию второго столбца:");
          PrintMatrix(Optimizer->PSBegin[2],N,true,false);
          Output->Lines->Add(" ");

          for (int i=0;i<N;i++)
               top[i]=0;

          Output->Lines->Add("Матрица 2 Сроки окончания:");
          PrintMatrixPS(Optimizer->PSBegin[2],N,0,0);
          Output->Lines->Add(" ");

          Output->Lines->Add("Сортировка по убыванию третьего столбца:");
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
          delete [] top;
     }
}

void MethodBH (bool Modify = false) //Method  of branches and hordes
{
     char version = 0;

     if (Modify)
     {
          StatusBar1->Panels->Items[0]->Text=("Модифицированный метод ветвей и границ");
          version = (OptionsForm->MVGModify->ItemIndex);
          TimeCycle[3]=Optimizer->MethodBHRun(version,
               OptionsForm->MvgIdle->Checked,
               OptionsForm->MvgIdleAll->Checked);
     }
     else
     {
          StatusBar1->Panels->Items[0]->Text=("Метод ветвей и границ");
          TimeCycle[3]=Optimizer->MethodBHRun(0,
               false,
               false);
     }
     //Вывод отчета - может повесить прогу
     int podric=250;
     for (int i= 1;i<Optimizer->Report->Count;i++)
     {
          Output->Lines->Add(Optimizer->Report->Strings[i]);
          if (i == podric)
               if (Application->MessageBox ("Остановить?", "Вывод отчета" , MB_YESNO + MB_ICONQUESTION) == IDNO)
               {
                    podric=podric*2+50;
                    Application->ProcessMessages();
                    continue;
               }
               else
                    break;

     }
     Application->ProcessMessages();
     Output->Lines->Add("Матрица С:");
     PrintMatrix(Optimizer->OptimalBH,N,false,false);
     Output->Lines->Add(" ");
     Output->Lines->Add("Матрица A:");
     PrintMatrix(Optimizer->OptimalBH,N,false,true);
     Output->Lines->Add(" ");
     Output->Lines->Add("Длительность производственного цикла: "+IntToStr(TimeCycle[3]));
     Output->Lines->Add("");
}

void NewMethod()
{
     StatusBar1->Panels->Items[0]->Text=("Новый метод запущен");
     TimeCycle[3]=Optimizer->NewMethodRun();
     Output->Lines->Add("Итого: "+IntToStr(TimeCycle[3]));

}
     int *top;
void PrintMatrixPS(const MachineOptimizer::Link *list,int n,int one,int left)
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

//Обновить таблицу
void TableRefresh2()
{
     ManualTable->Cells[0][0]="    Станок:";
     //Строки - детали Столбцы - станки
     for (int i=1;i<ManualTable->RowCount;i++)
          ManualTable->Cells[0][i]="Деталь " + IntToStr(i)+":";
     for (int j=1;j<ManualTable->ColCount;j++)
          ManualTable->Cells[j][0]=j;//"Станок №"+i;
     if (ManualTable->RowCount <= 10)
          ManualTable->ColWidths[0]=82;
     else if (ManualTable->RowCount <= 100)
          ManualTable->ColWidths[0]=88;
     else
          ManualTable->ColWidths[0]=96;
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
