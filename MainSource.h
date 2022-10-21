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
//---------------------------------------------------------------------------

#define max(A,B) (A>B ? A : B)


class TBaseForm : public TForm
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
     TMenuItem *NSize;
     TMenuItem *NMenuHelp;
     TMenuItem *NAbout;
     TMenuItem *NViewTwo;
     TLabel *Label2;
     TRadioGroup *RadioGroup1;
     TPopupMenu *PopupMenuGant;
     TMenuItem *NGantRepaint;
     TMenuItem *NGantResize;
     TMenuItem *NGantFont;
     TMenuItem *NGantColor;
     TColorDialog *ColorDialog1;
     TBevel *Bevel2;
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
     TPopupMenu *PopupMenuMainForm;
     TMenuItem *NRandom;
     TMenuItem *N5;
     TActionList *ActionList1;
     TImageList *ImageList1;
     TFileOpen *FileOpen;
     TFileSaveAs *FileSave;
     TFileRun *FileRun1;
     TFileExit *FileExit;
     TFontEdit *FontEdit1;
     TAction *FileNew;
     TMenuItem *N4;
     TMenuItem *SaveAs1;
     TMenuItem *N6;
     TMenuItem *Exit1;
     TMenuItem *Run1;
     TImageList *ImageList2;

     void __fastcall NExitClick(TObject *Sender);
     void __fastcall NOpenClick(TObject *Sender);
     void __fastcall NSaveClick(TObject *Sender);
     void __fastcall NFontClick(TObject *Sender);
     void __fastcall N15Click(TObject *Sender);
     void __fastcall NViewOneClick(TObject *Sender);
     void __fastcall NAboutClick(TObject *Sender);
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
     void __fastcall ReportBtnClick(TObject *Sender);
     void __fastcall N1Click(TObject *Sender);
     void __fastcall N2Click(TObject *Sender);
     void __fastcall NSizeClick(TObject *Sender);
     void __fastcall NTransponClick(TObject *Sender);
     void __fastcall NOptionsClick(TObject *Sender);
     void __fastcall TableRowMoved(TObject *Sender, int FromIndex,
          int ToIndex);
     void __fastcall TableColumnMoved(TObject *Sender, int FromIndex,
          int ToIndex);
private:	// User declarations
//Только в пределах данного модуля

public:		// User declarations
     MachineOptimizer *Optimizer;// = new MachineOptimizer;
     Graphics::TBitmap *Gant;// = new Graphics::TBitmap;
     int vt,scale,i,j;
     double min[2];
     double SA,XC;
     bool graphik,ultima,debugging;
     int *top;
     int M,N; //M - Станки, N - Детали

     __fastcall TBaseForm(TComponent* Owner);  //Объявление конструктора

//void PrintMatrix(MachineOptimizer::Link *list,int m,bool down=false);
//     if(Key == VK_RETURN)       //ДЛЯ ФОКУСИРОВКИ
//          BitBtn1->SetFocus();

void view() //Проверка видимости элементов
{
     //Panel1->Visible=NViewTwo->Checked;
     RunBtn->Enabled=(RadioGroup1->ItemIndex!=-1);
     Label2->Visible=NViewTwo->Checked;
     Bevel2->Visible=NViewTwo->Checked;
     GroupBox1->Visible=NViewOne->Checked;
     StaticText1->Visible=NViewTwo->Checked;
     TrackBar1->Visible=NViewTwo->Checked;
}

void Print(MachineOptimizer::Link *list)
{
     for(;list != NULL;list = list->next)
          Output->Text=Output->Text+FloatToStr(list->curr->m)+" ";
}

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
     if (list != NULL)   //Todo: Убрать эту функцию
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
               top[i-1]+=StrToInt(Table->Cells[i][j]);
               left = top[i-1];
          }
     }
     return top[N-1];
}

void PaintBlock(MachineOptimizer::Link *Item)
{
     SA=0,XC=0;
     for (;Item != NULL;Item = Item->next)
     {
          SA+=Item->curr->T[0];
          Gant->Canvas->Rectangle((SA-Item->curr->T[0])*scale,vt,SA*scale,vt+30);
             GraphicForm->gant->Canvas->Rectangle((SA-Item->curr->T[0])*scale,vt,SA*scale,vt+30);
          XC = (SA >= XC)? SA+Item->curr->T[1] : XC+Item->curr->T[1];
          Gant->Canvas->Rectangle((XC-Item->curr->T[1])*scale,vt+40,XC*scale,vt+70);
          Gant->Canvas->TextOut((SA-Item->curr->T[0])*scale+6,vt+6,Item->curr->m);
          Gant->Canvas->TextOut((XC-Item->curr->T[1])*scale+6,vt+46,Item->curr->m);
             GraphicForm->gant->Canvas->Rectangle((XC-Item->curr->T[1])*scale,vt+40,XC*scale,vt+70);
             GraphicForm->gant->Canvas->TextOut((SA-Item->curr->T[0])*scale+6,vt+6,Item->curr->m);
             GraphicForm->gant->Canvas->TextOut((XC-Item->curr->T[1])*scale+6,vt+46,Item->curr->m);
     }
     Gant->Canvas->TextOut(10,vt+75,"Время работы:");
     Gant->Canvas->TextOut(125,vt+75,XC);
        GraphicForm->gant->Canvas->TextOut(10,vt+75,"Время работы:");
        GraphicForm->gant->Canvas->TextOut(125,vt+75,XC);

}

void PaintGant()
{
     if (!graphik) return;
     //if (Optimizer == NULL) return;
     Label2->Repaint();    //TODO: repaint ?
     Label2->Canvas->Pen->Width=1;
     Label2->Canvas->TextOut(5,5,"Исходные данные:");

     GraphicForm->gant->Repaint();
     GraphicForm->gant->Canvas->Pen->Width=1;
     GraphicForm->gant->Canvas->TextOut(5,5,"Исходные данные:");

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
     int TimeCycle = Optimizer->DjonsonRun();  //Запуск алгоритма джонсона
     //Output->Lines->Add("Исходная последовательность:");
     //MachineOptimizer::Link *list = Optimizer->InitBegin;
     //paint(Optimizer->InitBegin);
     Output->Lines->Add("Оптимальная последовательность запуска деталей:");
     //Print(Optimizer->Optimal);
     int *data = Optimizer->OutSequence;
     for (int i=0;i<M;i++)
          Output->Text=Output->Text+IntToStr(data[i])+" ";
     Output->Lines->Add("Длительность производственного цикла: "+IntToStr(TimeCycle));
     Output->Lines->Add("");
     graphik = true;
     PaintGant();
}

void PetrovSokolMethod()
{
     StatusBar1->Panels->Items[0]->Text=("Метод Петрова-Соколицина");
     graphik = false;
     int TimeCycle = Optimizer->PetrovSokolRun(Output);   //Запуск алгоритма Петрова-Соколицина
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
     Output->Lines->Add("Длительность производственного цикла: "+IntToStr(TimeCycle));
     Output->Lines->Add("");
}

void MethodBH () //Method  of branches and hordes
{
     StatusBar1->Panels->Items[0]->Text=("Метод ветвей и границ");
     graphik = false;
     int TimeCycle;
     if (OptionsForm->NoOut->Checked)
          TimeCycle=Optimizer->MethodBHRun(NULL);
     else
          TimeCycle=Optimizer->MethodBHRun(Output);
     Output->Lines->Add("Матрица С:");
     PrintMatrix(Optimizer->C,N,false,false);
     Output->Lines->Add(" ");
     Output->Lines->Add("Матрица A:");
     PrintMatrix(Optimizer->C,N,false,true);
     Output->Lines->Add(" ");
     Output->Lines->Add("Длительность производственного цикла: "+IntToStr(TimeCycle));
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

#endif
