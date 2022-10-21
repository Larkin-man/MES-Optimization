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
#include "Table.h"
#include "Graphic.h"
#include "OptimizationMtds.h"
#include <math.h>
#include <ToolWin.hpp>
#include <ExtDlgs.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
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
     void __fastcall N10Click(TObject *Sender);
     void __fastcall N21Click(TObject *Sender);
     void __fastcall N23Click(TObject *Sender);
     void __fastcall N22Click(TObject *Sender);
     void __fastcall N12Click(TObject *Sender);
     void __fastcall U1Click(TObject *Sender);
     void __fastcall FormPaint(TObject *Sender);
     void __fastcall N25Click(TObject *Sender);
     void __fastcall N27Click(TObject *Sender);
     void __fastcall N28Click(TObject *Sender);
     void __fastcall TrackBar1Change(TObject *Sender);
     void __fastcall N30Click(TObject *Sender);
     void __fastcall RUNClick(TObject *Sender);
     void __fastcall RadioGroup1Click(TObject *Sender);
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

     struct Node    //Cписок деталей
     {
     int n;         //Номер детали
     double A;      //Длительность обработки на первом станке
     double B;      //Длительность обработки на втором станке
     Node *Next;    //Следующая деталь
     Node *Prev;    //Предыдущая деталь
     }
     *Record,       //Исходный список
     *Optimal,      //Список по Джонсону
     *minimal[2],   //Минимальный на первом станке 0, на втором 1
     *NotOptimal;   

     __fastcall TForm1(TComponent* Owner);  //Объявление конструктора

void tests(Node *Item)
{
     if (Item->A==3)
          Item =NULL;

}

void view() //Проверка видимости элементов
{
     Memo1->Visible=N8->Checked;
     Panel1->Visible=N20->Checked;
     RUN->Enabled=(RadioGroup1->ItemIndex!=-1);
     //SpeedButton5->Enabled=StringGrid1->ComponentCount;
}

void print(Node *Item)
{
     while(Item != NULL)
     {
     Memo1->Text=Memo1->Text+IntToStr(Item->n)+" ";
     Item = Item->Next;
     }
}

Node *CreateItem (double A, double B, int i)
{                //Функция создает новый элемент
   Node *pItem = new Node;
   pItem->A=A;
   pItem->B=B;
   pItem->n=i;
   pItem->Next=NULL;
   pItem->Prev=NULL;
   return pItem;
}

Node *InsertAfter (Node *parent, Node *Item)
{                 //Функция связывает два элемента
   if (parent != NULL)
   {
      //Item->Next=parent->Next;
      parent->Next=Item;
      Item->Prev=parent;
   }
   return Item;
}

void concatenate(Node *parent, Node *Item)
{              //Функция соединяет два элемента
     if (parent != NULL)
          parent->Next=Item;
     if (Item!=NULL)
          Item->Prev=parent;
}


Node *getTail (Node *head)
{             //Функция поиска последного элемента ы списке
   if(head == NULL)
      return NULL;
   Node *Item=head;
   while(Item->Next != NULL)
      Item = Item->Next;
   return Item;
}

Node *PushBack (Node *head, Node *Item)
{              //Функция вставляет элемент в конец списка
   Node *tail = getTail(head);
   return InsertAfter (tail, Item);
}

void paint(Node *Item)
{
     while(Item->Next != NULL)
     {
     Memo1->Lines->Add(Item->n);
     Item = Item->Next;
     }
     Memo1->Lines->Add(Item->n);
}

void PaintBlock(Node *Item)
{
     SA=0,XC=0;
     for (;Item != NULL;Item = Item->Next)
     {
          SA+=Item->A;
          Label2->Canvas->Rectangle((SA-Item->A)*scale,vt,SA*scale,vt+30);
          XC = (SA >= XC)? SA+Item->B : XC+Item->B;
          Label2->Canvas->Rectangle((XC-Item->B)*scale,vt+40,XC*scale,vt+70);
          Label2->Canvas->TextOut((SA-Item->A)*scale+6,vt+6,Item->n);
          Label2->Canvas->TextOut((XC-Item->B)*scale+6,vt+46,Item->n);
     }
     Label2->Canvas->TextOut(10,vt+75,"Время работы:");
     Label2->Canvas->TextOut(125,vt+75,XC);
}

void PaintGant()
{
     if (NotOptimal == NULL) return;
     Label2->Repaint();
     Label2->Canvas->Pen->Width=1;  
     Label2->Canvas->TextOut(5,5,"Исходные данные:");
     vt=30;
     PaintBlock(NotOptimal);

     Label2->Canvas->TextOut(10,140,"Оптимизированные данные:");
     vt=165;  
     PaintBlock(Optimal);
     
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
     }
}

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
}

void DjonsonRun()
{
(ListBox1->Items->Count)>(ListBox2->Items->Count) ? m = ListBox2->Items->Count : m = ListBox1->Items->Count;
       //             Edit5->Text=Optimal->n;
     //m = point-1;
     StatusBar1->SimpleText=("");
     //n=StrToInt (Edit1->Text);
     //m = ListBox1->Items->Count;
     StatusBar1->SimpleText=(m);
	//X=new double [m];
	//Y=new double [m];
     //}
     for (int i=0;i<m;i++)
          {
          a=atof(ListBox1->Items->Strings[i].c_str());
          b=atof(ListBox2->Items->Strings[i].c_str());
          Node *Item = PushBack(Record,CreateItem(a,b,i+1));
          Node *Itemn = PushBack(NotOptimal,CreateItem(a,b,i+1));
          
          if(Record == NULL)
               Record=Item;
          if (NotOptimal == NULL)
               NotOptimal=Itemn;
          }

     Optimal=CreateItem(0,0,0);

     for (int i=0;i<m-1;i++)
     {     
          min[0]=Record->A;
          min[1]=Record->B;
          minimal[0]=Record;
          minimal[1]=Record;
          Node *Item1=Record;
          while(Item1->Next != NULL)  //Цикл ищет минимальные элементы
          {
               Item1 = Item1->Next;
               if (Item1->A<min[0])
               {
                    min[0]=Item1->A;
                    minimal[0]=Item1;
               }
               if (Item1->B<min[1])
               {
                    min[1]=Item1->B;
                    minimal[1]=Item1;
               }
          }

          if (min[0]<=min[1]) //Собственно ядро алгоритма Джонсона
          {
               if (minimal[0]==Record)
                    Record=Record->Next;
               concatenate(minimal[0]->Prev,minimal[0]->Next);
               concatenate(Optimal->Prev,minimal[0]);
               concatenate(minimal[0],Optimal);
          }
          else
          {
               if (minimal[1]==Record)
                    Record=Record->Next;
               concatenate(minimal[1]->Prev,minimal[1]->Next);
               concatenate(minimal[1],Optimal->Next);
               concatenate(Optimal,minimal[1]);
          }

     }
     Optimal->A=Record->A;
     Optimal->B=Record->B;
     Optimal->n=Record->n;
     while(Optimal->Prev != NULL)
          Optimal=Optimal->Prev;
     Memo1->Lines->Add("Оптимальная последовательность запуска деталей:");
     print(Optimal);
     graphik = true;
     PaintGant();
}

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
//Сюда могут помещатся объявления типов, переменных, функций
//которые не включаются в класс формы

float future;
float doublekill(int a)
{
     Form1->Memo1->Lines->Add(a);
     return a+future;
}

class PetrovSokol
{
public:
int n,m;
int **M;

void runclick()
{
     n=4;
     for(int i =1;i<Form1->StringGrid1->RowCount;i++)
     {
          Form1->StringGrid1->Cells[i][0]=i;//"Станок №"+i;
     }
     for(int i =1;i<Form1->StringGrid1->ColCount;i++)
     {
          Form1->StringGrid1->Cells[0][i]=i;//"Станок №"+i;
     }
     Form1->Memo1->Lines->Add("RowCount="+IntToStr(Form1->StringGrid1->RowCount));
     Form1->Memo1->Lines->Add("ColCount="+IntToStr(Form1->StringGrid1->ColCount));
}
};
#endif
