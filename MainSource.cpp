//------------файл реализации---------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "MainSource.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGRID"
#pragma resource "*.dfm"
#include "EnterData.h"
#define Djohnson 0
#define PetrovSokol 1
#define MethodVG 2
#define MethodVGModify 3

TBaseForm *BaseForm;
//---------------------------------------------------------------------------
__fastcall TBaseForm::TBaseForm(TComponent* Owner) : TForm(Owner)
{    //при созданиии формы
     Output->Clear();
     scale = 18;
     M=0;
     N=0;
     NViewOneClick(NULL);
     Optimization->Enabled=false;
     GantDiagram->Enabled=false;
     Report->Enabled=false;
     FileSave->Enabled=false;
     NTranspon->Enabled=false;
     FileOpen->Dialog->InitialDir=GetCurrentDir();
     FileSave->Dialog->InitialDir=GetCurrentDir();
     BaseForm->Table->RowHeights[0]=26;
     TableRefresh();
     Gant = NULL;
     gantshow = false;
     //Image1->Align=alClient;
     for (int i=0;i<4;i++)
          TimeCycle[i] = 0;
     multicoloured=true;
     StatusBar1->Panels->Items[0]->Width=450;
     StatusBar1->Panels->Items[0]->Text=("Для начала работы нужно открыть данные (.txt) или заполнить случайно (Ctrl + R)");
     FontEdit->Dialog->Font=Table->Font;
     BH=30;
     BI=10;
}
//---------------------------------------------------------------------------
//ОТКРЫТЬ
void __fastcall TBaseForm::FileOpenAccept(TObject *Sender)
{
      StatusBar1->Panels->Items[0]->Text=FileOpen->Dialog->FileName;
      for (int i=1;i<Table->RowCount;i++)
          for (int j=1;j<Table->ColCount;j++)
               Table->Cells[j][i]="";

      N=0;
      TStringList *pStrings = new TStringList;
      pStrings->LoadFromFile(FileOpen->Dialog->FileName);
      if (pStrings->Count >= Table->RowCount)
          Table->RowCount = pStrings->Count+1;

      AnsiString Tx; //Для хранения лишнего текста
      Tx+=' ';
      Tx+='\n';
      int delrow=0;  //Удаленных строк
      for(int i=0; i < pStrings->Count; i++) //Цикл по строкам
      {
          char *s = pStrings->Strings[i].c_str();
          bool deletestring = true;
          for (int j =0;j < pStrings->Strings[i].Length();j++) //Цикл по символам для поиска цифр
          {
               if ((s[j] >= 48) && (s[j] <= 57))
               {
                    deletestring = false;
                    break;
               }
          }
          if (deletestring)
          {
               delrow++;
               Tx+=pStrings->Strings[i];
               Tx+='\n';
               continue;
          }
          int column = 1; //Столбец
          for (int j = 0;j < pStrings->Strings[i].Length();j++) //Цикл по символам
          {
               if (s[j]== ' ')
               {
                    //if (BaseForm->Table->Cells[column-1][i+1]!="")
                         column++;
                    //Table->Cells[row][i+1]="";  //clear
                    if (BaseForm->Table->ColCount <= column)   //Добавить столбец в таблицу
                    {
                         for (int k=1;k<Table->RowCount;k++)
                              Table->Cells[column][k]="";
                         BaseForm->Table->ColCount++;
                         BaseForm->Table->Cells[column][0]=column;
                    }
                    if (Tx[Tx.Length()] != ' ' )
                    Tx+=' ';
               }
               else
               {
                    //Output->Lines->Add(s[j]);
                    if ((s[j] >= 48) && (s[j] <= 57))   //int 48 = char 0, 57 - 9
                         Table->Cells[column][i-delrow+1]=Table->Cells[column][i-delrow+1]+s[j];
                    else
                         Tx+=s[j];
               }
          }
          if (N < column)
               N = column;
          //Table->Cells[0][i+1]=i+1;
          Table->Cells[0][i-delrow+1]="Деталь " + IntToStr(i-delrow+1)+":";
          Tx+='\n';
     }
     if (delrow > 0)
          Output->Lines->Add("Удалено строк: "+IntToStr(delrow));
     Output->Text=Output->Text+Tx;
     Output->Lines->Add("");
     M = (pStrings->Count)-delrow;
     delete pStrings;
     Ready();
}
//---------------------------------------------------------------------------
//СОХРАНИТЬ
void __fastcall TBaseForm::FileSaveAccept(TObject *Sender)
{
     Output->Lines->SaveToFile(FileSave->Dialog->FileName);
     StatusBar1->Panels->Items[0]->Text=FileSave->Dialog->FileName;
}
//---------------------------------------------------------------------------
//РАССЧЕТ
void __fastcall TBaseForm::RunExecute(TObject *Sender)
{
     if ((M <= 1)||(N <= 1))
     {
          Application->MessageBox ("Не задано количество станков и деталей", "Ошибка" , MB_ICONSTOP) ;
          StatusBar1->Panels->Items[1]->Text=("Станков: ?");
          StatusBar1->Panels->Items[2]->Text=("Деталей: ?");
          return;
     }

     delete Optimizer;   //TODO: Зачем Я удаляю ?
     Optimizer = new MachineOptimizer;  //Экземпляр класса, необходимый для работы. Объявлен в библиотеке OptimizationMtds.h
     delete ColorBox;
     ColorBox = new TColor[M];
     ColorPit();
     Optimizer->debugging=OptionsForm->Debug->Checked;
     int *T = new int[N];
     for (int i = 1;i<M+1;i++)
     {
          for (int j = 1;j<N+1;j++)
          {
               try
               {
               //T[j-1]=atof(Table->Cells[j][i].c_str());
               T[j-1]=StrToFloat(Table->Cells[j][i]);
               }
               catch(EConvertError&)
               {
                    Table->Cells[j][i]=0;
                    T[j-1]=0;
               }
               if (T[j-1]<0)
               {
                    Table->Cells[j][i]=abs(T[j-1]);
                    T[j-1]=abs(T[j-1]);
               }
          }
          Optimizer->add(N,T);
     }
     Output->Lines->Add("Исходная матрица:");
     PrintMatrix(Optimizer->InitBegin,N,false,false);
     TimeCycle[0]=ProductionCycle();
     StatusBar1->Panels->Items[3]->Text=("Длительность производственного цикла: "+IntToStr(TimeCycle[0]));
     Output->Lines->Add("Длительность производственного цикла: "+IntToStr(TimeCycle[0]));
     Output->Lines->Add("");
     Output->Lines->Add("");
     switch (RadioGroup1->ItemIndex)
     {
          case Djohnson:
               Output->Lines->Add("Алгоритм Джонсона");
               Output->Lines->Add("");
               DjonsonAlgorithm();
               break;
          case PetrovSokol:
               Output->Lines->Add("Метод Петрова-Соколицина");
               Output->Lines->Add("");
               PetrovSokolMethod();
               break;
          case MethodVG:
               Output->Lines->Add("Метод ветвей и границ");
               Output->Lines->Add("");
               MethodBH ();
               break;
          case MethodVGModify:
               Output->Lines->Add("Метод ветвей и границ (Модифицированый)");
               Output->Lines->Add("");
               MethodBH (true);
               break;
          default:
               return;
     }
     Output->Lines->Add("");
     Output->Lines->Add("----------------------------------------");
     Output->Lines->Add("");
     PaintGant();
     FileSave->Enabled=true;
     Optimization->Enabled=true;
     GantDiagram->Enabled=true;
     Report->Enabled=true;
}
//---------------------------------------------------------------------------
//ОБЫЧНЫЙ ВИД
void __fastcall TBaseForm::NViewOneClick(TObject *Sender)
{
     BaseForm->Height=576;
     BaseForm->Width=832;
     Output->SetBounds(284,64,533,432);
     //Output->Anchors=Panel1->Anchors;
}
//---------------------------------------------------------------------------
//КОМПАКТНЫЙ
void __fastcall TBaseForm::NViewTwoClick(TObject *Sender)
{
     BaseForm->Height=576;
     BaseForm->Width=768;
     Output->SetBounds(268,64,192,433);
     //Panel1->SetBounds(464,64,417,433);
     Output->Anchors=Table->Anchors;
}
//---------------------------------------------------------------------------
//ДИАГРАММА ГАНТА
void __fastcall TBaseForm::GantDiagramExecute(TObject *Sender)
{
     if (gantshow == false) //Show the gant diagram
     {
          GantBtn->Down=true;
          gantshow=true;
          PaintGant();
          GraphicForm->Show();
          GraphicForm->gant->Canvas->CopyRect(Rect(0,0,GantW,GantH),Gant->Canvas,Rect(0,0,GantW,GantH));
          if (BaseForm->WindowState == wsNormal)
               BaseForm->BringToFront();

     }
     else
     {
          GantBtn->Down=false;
          gantshow=false;
          GraphicForm->Close();
     }
}
//---------------------------------------------------------------------------
//ОЧИСТИТЬ(МЕМО)
void __fastcall TBaseForm::N12Click(TObject *Sender)
{
     Output->Clear();
}
//ЗАКРЫТЬ ФОРМУ
void __fastcall TBaseForm::FormClose(TObject *Sender, TCloseAction &Action)
{
     delete Optimizer;
}
//---------------------------------------------------------------------------
//НОВЫЙ
void __fastcall TBaseForm::FileNewExecute(TObject *Sender)
{
     Output->Clear();
     delete Optimizer;
     Optimizer = NULL;
     delete Gant;
     Gant = NULL;
     TableRefresh();
     FileSave->Enabled=false;
     Optimization->Enabled=false;
     GantDiagram->Enabled=false;
     Report->Enabled=false;
     GantBtn->Down=false;
     GraphicForm->Close();
     StatusBar1->Panels->Items[0]->Text=("");

}
//---------------------------------------------------------------------------
//ОПТИМИЗАЦИЯ
void __fastcall TBaseForm::OptimizationExecute(TObject *Sender)
{
     OptionsForm->Caption=("Оптимизация");
     OptionsForm->ShowOptimization(true);
     OptionsForm->Position=poMainFormCenter;
     if(OptionsForm->ShowModal()==IDOK)
     {          
     }
}
//---------------------------------------------------------------------------
//ТЕСТ ИЗ ВЫПАДАЮЩЕГО СПИСКА
void __fastcall TBaseForm::N1Click(TObject *Sender)
{
     Output->Lines->Add("Размеры поля L T H W");
     Output->Lines->Add(Output->Left);
     Output->Lines->Add(Output->Top);
     Output->Lines->Add(Output->Height);
     Output->Lines->Add(Output->Width);
     //Optimizer->MethodBHt(Form1->Output);
     //Table->Cols[2]->Delete(4);   //I dont understand
     /*for (MachineOptimizer::Link *Item =Optimizer->InitBegin;Item != NULL;Item = Item->next)
          for (int s = 0 ; s < N; s++)
               Table->Cells[s+1][Item->curr->m+4]=Item->curr->T[s];   //*/
     //ColorPit();
     for (int i = 0;i<M;i++)
     {
     Output->Lines->Add(ColorBox[i]);
     }
     try
          {
               float f = atof("gug");
               Output->Lines->Add(f);
          }                  
          catch (EConvertError&)
          {
               //ShowMessage("Вы ввели ошибочное число");
               OpenBtn->Enabled=!OpenBtn->Enabled;
          }

}
//---------------------------------------------------------------------------
//ОЧИСТИТЬ ТАБЛИЦУ
void __fastcall TBaseForm::N2Click(TObject *Sender)
{
     for (int i=1;i<Table->RowCount;i++)
          for (int j=1;j<Table->ColCount;j++)
               Table->Cells[j][i]="";
}
//---------------------------------------------------------------------------
//ТРАНСПОНИРОВАТЬ
void __fastcall TBaseForm::NTransponClick(TObject *Sender)
{
     if ((Table->RowCount+1) < N)
          Table->RowCount = N+1;
     if ((Table->ColCount+1) < M)
          Table->ColCount = M+1;
     int tempmax = (N > M)? N : M;
     int temp;
     for (int i = 1;i<tempmax+1;i++)
          for (int j=i+1;j<tempmax+1;j++)
          {
               temp=atoi(Table->Cells[i][j].c_str());
               Table->Cells[i][j]=Table->Cells[j][i];
               Table->Cells[j][i]=temp;
          }
     temp=N;
     N=M;
     M=temp;
     StatusBar1->Panels->Items[1]->Text=("Станков: "+IntToStr(N));
     StatusBar1->Panels->Items[2]->Text=("Деталей: "+IntToStr(M));
}
//---------------------------------------------------------------------------
//ОПЦИИ
void __fastcall TBaseForm::NOptionsClick(TObject *Sender)
{
     OptionsForm->Caption=("Настройки");
     OptionsForm->Position=poMainFormCenter;
     if(OptionsForm->ShowModal()==IDOK)
     {
          multicoloured=OptionsForm->ColorOptions->ItemIndex;
          CountScale(GraphicForm->TrackBar1->Position);
          PaintGant();
          GraphicForm->N2->Checked=OptionsForm->WorkTimeOut->Checked;
          GraphicForm->N4->Checked=OptionsForm->ColorOptions->ItemIndex;
     }
}
//---------------------------------------------------------------------------
//ОТЧЕТ
void __fastcall TBaseForm::ReportExecute(TObject *Sender)
{
     //OpenBtn->Enabled=!OpenBtn->Enabled;
}
//---------------------------------------------------------------------------
//ИЗМЕНИТЬ РАЗМЕР ТАБЛИЦЫ
void __fastcall TBaseForm::ResizeTableExecute(TObject *Sender)
{
     Application->CreateForm( __classid(TEnterDataForm),&EnterDataForm);
     EnterDataForm->Caption=("Изменение размера таблицы");
     EnterDataForm->BitBtnOkRandom->Visible=false;
     EnterDataForm->BitBtnOkResize->Visible=true;
     EnterDataForm->Position=poMainFormCenter;
     EnterDataForm->ShowModal();
     EnterDataForm->Free();  
}
//---------------------------------------------------------------------------
 //ЗАПОЛНЕНИЕ СЛУЧАЙНЫМИ ЧИСЛАМИ
void __fastcall TBaseForm::RandomExecute(TObject *Sender)
{
     Application->CreateForm( __classid(TEnterDataForm),&EnterDataForm);
     EnterDataForm->Caption=("Заполнение случайными числами");
     EnterDataForm->BitBtnOkRandom->Visible=true;
     EnterDataForm->BitBtnOkResize->Visible=false;
     EnterDataForm->Position=poMainFormCenter;
     EnterDataForm->ShowModal();
     EnterDataForm->Free();
}
//---------------------------------------------------------------------------
//КОПИРОВАТЬ
void __fastcall TBaseForm::N15Click(TObject *Sender)
{
     Output->CopyToClipboard();
     ShowMessage("Хочешь копировать жми CTRL+C!");
    // NViewTwoClick(Sender);
}

//ШРИФТ
void __fastcall TBaseForm::FontEditAccept(TObject *Sender)
{
     //TWinControl* Fonted = BaseForm->ActiveControl;
     ((TMemo*)BaseForm->ActiveControl)->Font=FontEdit->Dialog->Font;
     //ShowMessage("Произошло событие в компоненте " + ((TComponent *)BaseForm->ActiveControl)->Name);
     //BaseForm->ActiveControl->cla
     //Output->Font=FontEdit->Dialog->Font;
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::TableColumnMoved(TObject *Sender, int FromIndex, int ToIndex)
{
     TableRefresh();     
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::TableRowMoved(TObject *Sender, int FromIndex, int ToIndex)
{
     TableRefresh();     
}
//---------------------------------------------------------------------------
//Перейти на диаграмму Ганта
void __fastcall TBaseForm::SpeedButton1Click(TObject *Sender)
{
     GraphicForm->BringToFront();
     GraphicForm->SetFocus();
}
//---------------------------------------------------------------------------
//О ПРОГРАММЕ
void __fastcall TBaseForm::NAboutClick(TObject *Sender)
{
     Application->CreateForm( __classid(TAboutBox1),&AboutBox1);
     AboutBox1->ShowModal();
     AboutBox1->Free();
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::StatusBar1DblClick(TObject *Sender)
{
     TPoint mouse;
     GetCursorPos(&mouse);
     int x=mouse.x-StatusBar1->Left;
     int y=mouse.y-StatusBar1->Top;
     ShowMessage("DblClick in ("+IntToStr(x)+", "+IntToStr(y)+")");
}
//---------------------------------------------------------------------------
//Ограничить размер шрифта
void __fastcall TBaseForm::FontEditBeforeExecute(TObject *Sender)
{
     if(((TComponent *)BaseForm->ActiveControl)->Name == "Table")
          FontEdit->Dialog->MaxFontSize=14;
     else
          FontEdit->Dialog->MaxFontSize=36;
}
//---------------------------------------------------------------------------



