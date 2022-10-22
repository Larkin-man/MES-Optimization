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
     TMenuItem *N11;
     TMenuItem *N12;
     TStatusBar *StatusBar1;
     TMemo *Output;
     TMenuItem *N15;
     TMenuItem *NSize;
     TMenuItem *NMenuHelp;
     TMenuItem *NAbout;
     TRadioGroup *RadioGroup1;
     TMenuItem *NMenuRun;
     TMenuItem *NOptSwitch;
     TMenuItem *NRun;
     TMenuItem *N9;
     TPopupMenu *PopupMenuGrid;
     TMenuItem *N1;
     TMenuItem *NTranspon;
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
     TAction *Repaint;
     TToolButton *ToolButton8;
     TSpeedButton *SpeedButton1;
     TMenuItem *N7;
     TAction *Random;
     TMenuItem *N8;
     TStringGrid *Table;
     TStringGrid *StringGrid1;
     TMenuItem *N10;
     void __fastcall N15Click(TObject *Sender);
     void __fastcall NViewOneClick(TObject *Sender);
     void __fastcall NAboutClick(TObject *Sender);
     void __fastcall NViewTwoClick(TObject *Sender);
     void __fastcall N12Click(TObject *Sender);
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
     void __fastcall FontEditAccept(TObject *Sender);
     void __fastcall TableColumnMoved(TObject *Sender, int FromIndex,
          int ToIndex);
     void __fastcall TableRowMoved(TObject *Sender, int FromIndex,
          int ToIndex);
     void __fastcall SpeedButton1Click(TObject *Sender);
     void __fastcall RandomExecute(TObject *Sender);
     void __fastcall StatusBar1DblClick(TObject *Sender);
     void __fastcall FontEditBeforeExecute(TObject *Sender);
private:	// User declarations
//Только в пределах данного модуля

public:		// User declarations
     MachineOptimizer *Optimizer;
     Graphics::TBitmap *Gant;
     int vertix,scale,i,j;
     int  BH,  //Block Height = 30 (не меньше 14!)
          BI,  //Block Interval = 10
          TX,  //Text Out X = 5
          TY,  //Text Out Y = 8
          GantH,    //Gant Height
          GantW;    //Gant Weight
     int M,N; //M - Станки, N - Детали
     int TimeCycle[4];
     bool gantshow;
     TColor *ColorBox;   //Колорпит для разноцветных красивых блоков
     int Brightness;     //Яркость
     bool multicoloured;


     __fastcall TBaseForm(TComponent* Owner);  //Объявление конструктора

//void PrintMatrix(MachineOptimizer::Link *list,int m,bool down=false);
//     if(Key == VK_RETURN)       //ДЛЯ ФОКУСИРОВКИ
//          BitBtn1->SetFocus();

//Готовность к запуску расчета
void Ready()
{
     StatusBar1->Panels->Items[0]->Width=400;
     StatusBar1->Panels->Items[1]->Text=("Станков: "+IntToStr(N));
     StatusBar1->Panels->Items[2]->Text=("Деталей: "+IntToStr(M));
     if (OptionsForm->RadioGroupTime->ItemIndex != 2)
          StatusBar1->Panels->Items[3]->Text=("Длительность производственного цикла: "+IntToStr(ProductionCycle()));
     FileSave->Enabled=true;
     //Run->Enabled=true;
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
     Brightness = 25;
     TColor red,green,blue;
     srand(time(NULL));
     for (int i = 0;i<M;i++)
     {
     red=TColor(rand()%(256-Brightness)+Brightness);
     green=TColor((rand()%(255-Brightness)+Brightness)*256+256);
     blue=TColor((rand()%(255-Brightness)+Brightness)*256*256+256*256);
     ColorBox[i]=TColor(blue+green+red);
     }
     //ToolBar1->Color=0*256+256;
     //RadioGroup1->Color=254*256*256+254*256+256;
     //Table->Color=ColorBox[0];
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
                    Output->Text=Output->Text+IntToStr(list->curr->T[i]-atoi(Table->Cells[i+1][j].c_str()))+"  ";
          }
     }
}

     int *top;
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
     return top[N-1];
}
//Функция рисует диаграмму Ганта c помощью матрицы длительностей обработки
void DrawDiagramFromDurationMatrix(MachineOptimizer::Link *List, bool down)
{
     vertix+=BH;
     int *SX = new int[N+1];
          for (int o = 0 ; o < N+1; o++)
               SX[o]=0;
     MachineOptimizer::Node *Item;
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
     delete SX;
}
//Функция рисует диаграмму Ганта c помощью матрицы окончаний обработки (С)
void DrawDiagramFromEndingMatrix(MachineOptimizer::Link *Item)
{
     vertix+=BH;
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
                         Gant->Canvas->TextOut(((Item->curr->T[s])-(Item->down->curr->T[s]))*scale+TX-5, vertix+(BH+BI)*s+TY, IntToStr(Item->curr->m)+" ("+IntToStr(Item->down->curr->T[s])+")");
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
     
     TX=(scale-8)/2;
     TY=(BH-14)/2;
     //if (Optimizer == NULL) return;
     GantW=TimeCycle[0];
     for (int i=1;i<4;i++)
          if (TimeCycle[i] > GantW)
               GantW=TimeCycle[i];
     //ShowMessage("Gant weight="+IntToStr(GantW));
     GantW=GantW*scale+1;
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
     //ShowMessage("jvj"+IntToStr(Optimizer->OptimalPS->down->curr->m));
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
     GraphicForm->ClearGantField();
     if (gantshow)
          GraphicForm->gant->Canvas->CopyRect(Rect(0,0,GantW,GantH),Gant->Canvas,Rect(0,0,GantW,GantH));


}
//Пересчитать масштаб диаграммы
void CountScale(int Scroller = 5)
{
     scale=Scroller+12+Scroller/3;
     if (OptionsForm->WorkTimeOut->Checked)
          scale+=4;
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
}

void PetrovSokolMethod()
{
     StatusBar1->Panels->Items[0]->Text=("Метод Петрова-Соколицина");
     TimeCycle[2] = Optimizer->PetrovSokolRun(Output);   //Запуск алгоритма Петрова-Соколицина
     top = new int[N];

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
}

void MethodBH (bool Modify = false) //Method  of branches and hordes
{
     char version = 0;
     if (Modify)
          switch (OptionsForm->MVGModify->ItemIndex)
          {
               case 0:
                    StatusBar1->Panels->Items[0]->Text=("Метод ветвей и границ v1.3");
                    version = 1;
                    break;
               case 1:
                    StatusBar1->Panels->Items[0]->Text=("Метод ветвей и границ v1.4");
                    version = 2;
                    break;
          }
     else
          StatusBar1->Panels->Items[0]->Text=("Метод ветвей и границ");
     if (OptionsForm->NoOut->Checked)
          TimeCycle[3]=Optimizer->MethodBHRun(version, false);
     else
          TimeCycle[3]=Optimizer->MethodBHRun(version, true);
     //Вывод отчета - может повесить прогу
     for (int i= 1;i<Optimizer->Report->Count;i++)
     {
          Output->Lines->Add(Optimizer->Report->Strings[i]);
          if ((i % 250) == 0)
               //Application->MessageBox ("Остановить?", "watchdog" , MB_YESNO);

               if (Application->MessageBox ("Остановить?", "Вывод отчета" , MB_YESNO + MB_ICONQUESTION) == IDNO)
               {
                    Application->ProcessMessages();
                    continue;
               }
               else
                    break;

     }
     Output->Lines->Add("Матрица С:");
     PrintMatrix(Optimizer->OptimalBH,N,false,false);
     Output->Lines->Add(" ");
     Output->Lines->Add("Матрица A:");
     PrintMatrix(Optimizer->OptimalBH,N,false,true);
     Output->Lines->Add(" ");
     Output->Lines->Add("Длительность производственного цикла: "+IntToStr(TimeCycle[3]));
     Output->Lines->Add("");
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
