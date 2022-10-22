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
__fastcall TBaseForm::TBaseForm(TComponent* Owner)
     : TForm(Owner)
{    //при созданиии формы
     Output->Clear();
     scale = 18;
     M=0;
     N=0;
     NViewOneClick(NULL);
     ultima=false;
     Run->Enabled=false;
     Optimization->Enabled=false;
     GantDiagram->Enabled=false;
     Report->Enabled=false;
     FileSave->Enabled=false;
     NTranspon->Enabled=false;
     FileOpen->Dialog->InitialDir=GetCurrentDir();
     FileSave->Dialog->InitialDir=GetCurrentDir();
     Image1->Canvas->Pen->Color=clHotLight;
     BaseForm->Table->RowHeights[0]=26;
     BaseForm->Table->ColWidths[0]=82;
     TableRefresh();
     Gant = NULL;
     gantshow = false;
     //Image1->Align=alClient;
     for (int i=0;i<4;i++)
          TimeCycle[i] = 0;
     Image1->Width=Panel1->Width;
     Image1->Height=Panel1->Height;
     delet =0;
     multicoloured=true;
}
//---------------------------------------------------------------------------
//ОТКРЫТЬ
void __fastcall TBaseForm::FileOpenAccept(TObject *Sender)
{         
      StatusBar1->Panels->Items[0]->Text=FileOpen->Dialog->FileName;
          for (int i=1;i<Table->RowCount;i++)
               for (int j=1;j<Table->ColCount;j++)
                    Table->Cells[j][i]="";

          TStringList *pStrings = new TStringList;
          pStrings->LoadFromFile(FileOpen->Dialog->FileName);
          if (pStrings->Count >= Table->RowCount)
               Table->RowCount = pStrings->Count+1;
          for(int i=0; i < pStrings->Count; i++) //Цикл по строкам
          {
               char *s = pStrings->Strings[i].c_str();
               int column = 1; //Столбец
               for (int j =0;j < pStrings->Strings[i].Length();j++) //Цикл по символам
               {
                    if (s[j]== ' ')
                    {
                         column++;
                         //Table->Cells[row][i+1]="";  //clear
                         if (BaseForm->Table->ColCount <= column)   //Добавить столбец в таблицу
                                {
                                        for (int k=1;k<Table->RowCount;k++)
                                                Table->Cells[column][k]="";
                                        BaseForm->Table->ColCount++;
                                        BaseForm->Table->Cells[column][0]=column;
                                }
                    }
                    else
                    {
                         Table->Cells[column][i+1]=Table->Cells[column][i+1]+s[j];
                    }
               }                                      
               N=column;
               //Table->Cells[0][i+1]=i+1;
               Table->Cells[0][i+1]="Деталь " + IntToStr(i+1)+":";
          }    
          M = pStrings->Count;
          delete pStrings;
     Ready();
}
//---------------------------------------------------------------------------
//СОХРАНИТЬ
void __fastcall TBaseForm::FileSaveAccept(TObject *Sender)
{
     Output->Lines->SaveToFile(FileSave->Dialog->FileName);
     StatusBar1->Panels->Items[0]->Text=FileSave->Dialog->FileName;
     /*
     Graphics::TBitmap *sky = new Graphics::TBitmap();
     sky->Height=400;
     sky->Width=500;
     sky->Canvas->Pen->Color=clRed;
     sky->Canvas->Brush->Color=clBlue;
     sky->Canvas->TextOutA(1,1,"TSCHK");
     sky->Canvas->Rectangle(3,30,50,70);
     sky->Canvas->Pixels[0][0]=clYellow;
     sky->SaveToFile ("TESCHK.bmp") ;         */
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
//РАССЧЕТ
void __fastcall TBaseForm::RunExecute(TObject *Sender)
{
     if ((M <= 1)||(N <= 1))
     {
          //MessageDlg("Данные не введены", mtError,TMsgDlgButtons () << mbOK, 0);
          Application->MessageBox ("Данные не введены", "Ошибка" , MB_ICONSTOP) ;
          return;
     }

     delete Optimizer;   //TODO: Зачем Я удаляю ?
     Optimizer = new MachineOptimizer;  //Экземпляр класса, необходимый для работы. Объявлен в библиотеке OptimizationMtds.h
     delete Gant;
     Gant = new Graphics::TBitmap;
     delete ColorBox;
     ColorBox = new TColor[M];
     ColorPit();

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
     BaseForm->Width=896;
     NViewOne->Checked=true;
     NViewTwo->Checked=false;
     Output->SetBounds(268,64,613,432);
     Output->Anchors=Panel1->Anchors;
     view();
}
//---------------------------------------------------------------------------
//КОМПАКТНЫЙ
void __fastcall TBaseForm::NViewTwoClick(TObject *Sender)
{
     BaseForm->Height=576;
     BaseForm->Width=896;
     NViewTwo->Checked=true;
     NViewOne->Checked=false;
     Output->SetBounds(268,64,192,433);
     Panel1->SetBounds(464,64,417,433);
     Output->Anchors=Table->Anchors;
     view();
}
//---------------------------------------------------------------------------
//ДИАГРАММА ГАНТА
void __fastcall TBaseForm::GantDiagramExecute(TObject *Sender)
{
     if (gantshow == false) //Show the gant diagram
     {
          GantBtn->Down=true;
          GraphicForm->Show();
          GraphicForm->gant->Canvas->CopyRect(Rect(0,0,GantW,GantH),Gant->Canvas,Rect(0,0,GantW,GantH));
          BaseForm->BringToFront();
          gantshow=true;
     }
     else
     {
          GantBtn->Down=false;
          GraphicForm->Close();
     }
}
//---------------------------------------------------------------------------
//ОЧИСТИТЬ(МЕМО)
void __fastcall TBaseForm::N12Click(TObject *Sender)
{
     Output->Clear();
}
//---------------------------------------------------------------------------
//ШРИФТ ДИАГРАММЫ
void __fastcall TBaseForm::NGantFontClick(TObject *Sender)
{
     if (FontEdit->Dialog->Execute())  /* TODO 2 : Сделать для сендера */
     {
          //Image1->Font=FontEdit->Dialog->Font;
     }
     PaintGant();
}
//---------------------------------------------------------------------------
//ЦВЕТ ДИАГРАММЫ
void __fastcall TBaseForm::NGantColorClick(TObject *Sender)
{
     if (GantPenColor->Execute())
     {
          Gant->Canvas->Pen->Color=GantPenColor->Color;
     }
     PaintGant();
}
//---------------------------------------------------------------------------
//ИЗМЕНЕНИЕ МАСШТАБА ПОЛЗУНКОМ
void __fastcall TBaseForm::TrackBar1Change(TObject *Sender)
{
     //Image1->~TImage();
     //Gant->FreeImage();
     delete Gant;
     Gant = new Graphics::TBitmap;
     scale=(TrackBar1->Position)+14;
     PaintGant();
}
//---------------------------------------------------------------------------
//ЗАКРЫТЬ ФОРМУ
void __fastcall TBaseForm::FormClose(TObject *Sender, TCloseAction &Action)
{
     //ShowMessage("close form");
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
     Image1->Width=Panel1->Width;
     Image1->Height=Panel1->Height;
     //ColorPit();
     for (int i = 0;i<M;i++)
     {
     Output->Lines->Add(ColorBox[i]);
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
          if (OptionsForm->Cvetpit != OptionsForm->ColorOptions->ItemIndex)
          {
               //ShowMessage("cv"+IntToStr(OptionsForm->Cvetpit)+" ite="+IntToStr(OptionsForm->ColorOptions->ItemIndex));
               OptionsForm->Cvetpit=OptionsForm->ColorOptions->ItemIndex;
               multicoloured=OptionsForm->Cvetpit;
               PaintGant();
          }
     }
}
//---------------------------------------------------------------------------
//ОТЧЕТ
void __fastcall TBaseForm::ReportExecute(TObject *Sender)
{
     OpenBtn->Enabled=!OpenBtn->Enabled;
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
     // strcpy(temp.city,Form2->Edit1->Text.c_str());
     // AddA(temp);
     EnterDataForm->Free();  
}
//---------------------------------------------------------------------------
//ЗАПОЛНЕНИЕ СЛУЧАЙНЫМИ ЧИСЛАМИ
void __fastcall TBaseForm::Pf1Click(TObject *Sender)
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
     NViewTwoClick(Sender);
}
//---------------------------------------------------------------------------
//Выводить время работы
void __fastcall TBaseForm::NGantTimeClick(TObject *Sender)
{
     if (OptionsForm->WorkTimeOut->Checked == false)
          OptionsForm->WorkTimeOutClick(NULL);
     NGantTime->Checked=OptionsForm->WorkTimeOut->Checked;
}
//---------------------------------------------------------------------------
//ШРИФТ
void __fastcall TBaseForm::FontEditAccept(TObject *Sender)
{
          Output->Font=FontEdit->Dialog->Font;
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::TableColumnMoved(TObject *Sender, int FromIndex,
      int ToIndex)
{
     TableRefresh();     
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::TableRowMoved(TObject *Sender, int FromIndex,
      int ToIndex)
{
     TableRefresh();     
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::SpeedButton1Click(TObject *Sender)
{
     GraphicForm->BringToFront();
     GraphicForm->SetFocus();
}
//---------------------------------------------------------------------------

