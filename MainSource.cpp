//------------���� ����������---------------------------------------------------------------

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
#define Stupenki 4

TBaseForm *BaseForm;
//---------------------------------------------------------------------------
__fastcall TBaseForm::TBaseForm(TComponent* Owner) : TForm(Owner)
{    //��� ��������� �����
     Output->Clear();
     M=0;
     N=0;
     FileOpen->Dialog->InitialDir=GetCurrentDir();
     FileSave->Dialog->InitialDir=GetCurrentDir();
     BaseForm->Table->RowHeights[0]=26;
     TableRefresh();
     Gant = NULL;
     gantshow = false;
     for (int i=0;i<4;i++)
          TimeCycle[i] = 0;
     multicoloured=true;
     StatusBar1->Panels->Items[0]->Width=450;
     StatusBar1->Panels->Items[0]->Text=("��� ������ ������ ����� ������� ������ (.txt) ��� ��������� �������� (Ctrl + R)");
     FontEdit->Dialog->Font=Table->Font;
     scale = 18;
     BH=30;
     BI=10;
     Brightness = 25;
     NTranspon->Enabled=false;
     Ready(false);

     NManualModeClick(NULL);
     ManualTable->ColWidths[0]=64;
}
//---------------------------------------------------------------------------
//�������
void __fastcall TBaseForm::FileOpenAccept(TObject *Sender)
{
      TStringList *pStrings = new TStringList;
      pStrings->LoadFromFile(FileOpen->Dialog->FileName);
      char *s;
      int nC=0,nS=0;
      for(int i = 0; i < pStrings->Count; i++) //���� �� �������
      {
          s = pStrings->Strings[i].c_str();
          for (int j = 0;j < pStrings->Strings[i].Length();j++) //���� �� �������� ��� ������ ����
               if ((s[j] >= '0') && (s[j] <= '9'))
                    nC++;
               else
                    if (s[j]!= ' ')
                         nS++;
      }
      //ShowMessage("���� "+IntToStr(nC)+" ���� "+IntToStr(nS));
      if (nS*OptionsForm->OpenCheck->Value > nC)
      {
          Application->MessageBox (
               "�������� ������. ���� ������ ��������� ������� ������������� ���������",
               "������ �������� �����",
               MB_OK + MB_ICONSTOP);
          StatusBar1->Panels->Items[0]->Text="������ �������� ����� "+FileOpen->Dialog->FileName;
          delete pStrings;
          return;
      }

      StatusBar1->Panels->Items[0]->Text=FileOpen->Dialog->FileName;
      for (int i=1;i<Table->RowCount;i++)
          for (int j=1;j<Table->ColCount;j++)
               Table->Cells[j][i]="";
      N=0;
      Table->RowCount = pStrings->Count+1;

      AnsiString Tx; //��� �������� ������� ������
      int delrow=0;  //��������� �����
      for(int i=0; i < pStrings->Count; i++) //���� �� �������
      {
          char *s = pStrings->Strings[i].c_str();
          bool deletestring = true;
          for (int j =0;j < pStrings->Strings[i].Length();j++) //���� �� �������� ��� ������ ����
          {
               if ((s[j] >= '0') && (s[j] <= '9'))
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
          int column = 1; //�������
          for (int j = 0;j < pStrings->Strings[i].Length();j++) //���� �� ��������
          {
               if ((s[j] >= '0') && (s[j] <= '9'))
                    Table->Cells[column][i-delrow+1]=Table->Cells[column][i-delrow+1]+s[j];
               else
               {
                    if (BaseForm->Table->Cells[column][i-delrow+1]!="")
                         column++;
                    if (BaseForm->Table->ColCount <= column)   //�������� ������� � �������
                    {                                   
                         for (int k=1;k<Table->RowCount;k++)
                              Table->Cells[column][k]="";
                         BaseForm->Table->ColCount++;
                         //BaseForm->Table->Cells[column][0]=column; //detal
                    }
                    Tx+=s[j];
               }
          }
          if (BaseForm->Table->Cells[column][i-delrow+1]=="")
               column--;
          if (N < column)
               N = column;
          //Table->Cells[0][i-delrow+1]="������ " + IntToStr(i-delrow+1)+":";
     }
     if (delrow > 0)
     {
          Table->RowCount = pStrings->Count+1-delrow;
          Output->Lines->Add("������� �����: "+IntToStr(delrow));
     }
     if (N+1 < Table->ColCount)
          Table->ColCount=N+1;
     Output->Text=Output->Text+Tx;
     Output->Lines->Add("");
     M = (pStrings->Count)-delrow;
     TableRefresh();
     delete pStrings;
     Swapf();
}
//---------------------------------------------------------------------------
//���������
void __fastcall TBaseForm::FileSaveAccept(TObject *Sender)
{
     if (BaseForm->ActiveControl == Table)
     {
          TStringList *pStrings = new TStringList;
          AnsiString Added;
          for (int  i=1;i<M+1;i++)
          {
               Added="";
               for (int  j=1;j<N+1;j++)
                    Added+=(Table->Cells[j][i]+" ");
               pStrings->Add(Added);       
          }
          FileSave->Dialog->FileName="input *";
          pStrings->SaveToFile(FileSave->Dialog->FileName);
     }
     else
     {
          //Application->MessageBox ("���������", "����������" , MB_ICONSTOP) ;
          FileSave->Dialog->FileName="report *";
          Output->Lines->SaveToFile(FileSave->Dialog->FileName);
          StatusBar1->Panels->Items[0]->Text=FileSave->Dialog->FileName;
     }
}
//---------------------------------------------------------------------------
//�������
void __fastcall TBaseForm::RunExecute(TObject *Sender)
{
     if ((M <= 1)||(N <= 1))
     {    
          Application->MessageBox ("�� ������ ���������� ������� � �������", "������" , MB_ICONSTOP) ;
          StatusBar1->Panels->Items[1]->Text=("�������: ?");
          StatusBar1->Panels->Items[2]->Text=("�������: ?");
          return;
     }

     delete Optimizer;   //TODO: ����� � ������ ?
     Optimizer = new MachineOptimizer;  //��������� ������, ����������� ��� ������. �������� � ���������� OptimizationMtds.h
     delete ColorBox;           /* TODO : � ���� �� ��������� */
     ColorBox = new TColor[M];
     ColorPit();
     //Optimizer->output=!(OptionsForm->NoOut->Checked);  //� ��� ����� � ��� �� ����� ����� ��� 5 �������� ���� ����� �����
     Optimizer->output=OptionsForm->Debug->Checked;
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
          Optimizer->add(T, N);
     }
     delete [] T;
     if (!(OptionsForm->NoOut->Checked))
     {
          Output->Lines->Add("�������� �������:");
          PrintMatrix(Optimizer->InitBegin,N,false,false);
     }
     TimeCycle[0]=ProductionCycle();
     StatusBar1->Panels->Items[3]->Text=("������������ ����������������� �����: "+IntToStr(TimeCycle[0]));
     Output->Lines->Add("������������ ����������������� �����: "+IntToStr(TimeCycle[0]));
     Output->Lines->Add("");
     Output->Lines->Add("");
     Tick = ::GetTickCount();
     switch (RadioGroup1->ItemIndex)
     {
          case Djohnson:
               Output->Lines->Add("�������� ��������");
               Output->Lines->Add("");
               DjonsonAlgorithm();
               break;
          case PetrovSokol:
               Output->Lines->Add("����� �������-����������");
               Output->Lines->Add("");
               PetrovSokolMethod();
               break;
          case MethodVG:
               Output->Lines->Add("����� ������ � ������");
               Output->Lines->Add("");
               MethodBH ();
               break;
          case MethodVGModify:
               Output->Lines->Add("����� ������ � ������ (���������������)");
               Output->Lines->Add("");
               MethodBH (true);
               break;
          case Stupenki: 
               Output->Lines->Add("����� �����!");
               Output->Lines->Add("");
               NewMethod();
               break;
          default:
               ShowMessage("������ ���������� ������");
               return;
     }
     Output->Lines->Add("����� �������: "+FloatToStr(Tick)+" ��������.");
     Output->Lines->Add("");
     Output->Lines->Add("----------------------------------------");
     Output->Lines->Add("");
     GraphicForm->ScrollBar1->Position=0;
     GraphicForm->ScrollBar2->Position=0;
     PaintGant();  
     Ready(true);
}
//---------------------------------------------------------------------------
//��������� �����
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
//��������(����)
void __fastcall TBaseForm::NClear1Click(TObject *Sender)
{
     FileSave->Enabled=false;
     Output->Clear();
}
//������� �����
void __fastcall TBaseForm::FormClose(TObject *Sender, TCloseAction &Action)
{
     delete Optimizer;
}
//---------------------------------------------------------------------------
//�����
void __fastcall TBaseForm::FileNewExecute(TObject *Sender)
{
     Output->Clear();
     delete Optimizer;
     Optimizer = NULL;
     delete Gant;
     Gant = NULL;
     TableRefresh();
     Ready(false);
     GantBtn->Down=false;
     GraphicForm->Close();
     StatusBar1->Panels->Items[0]->Text=("");
     if (NManualMode->Checked)
          NManualModeClick(Sender);

}
//---------------------------------------------------------------------------
//�����������
void __fastcall TBaseForm::OptimizationExecute(TObject *Sender)
{
     OptionsForm->Caption=("�����������");
     OptionsForm->ShowOptimization(true);
     OptionsForm->Position=poMainFormCenter;
     if(OptionsForm->ShowModal())
     OptionsForm->PageControl->TabIndex=0;    
}
//---------------------------------------------------------------------------
//���� �� ����������� ������
void __fastcall TBaseForm::NTestClick(TObject *Sender)
{
     Output->Lines->Add("������� ���� L T H W");
     Output->Lines->Add(Output->Left);
     Output->Lines->Add(Output->Top);
     Output->Lines->Add(Output->Height);
     Output->Lines->Add(Output->Width);
     //Optimizer->MethodBHt(Form1->Output);
     //Table->Cols[2]->Delete(4);   //I dont understand
      //ColorPit();
     //for (int i = 0;i<M;i++)     {       Output->Lines->Add(ColorBox[i]);      }
     try
          {
               float f = atof("gug");
               Output->Lines->Add(f);
          }                  
          catch (EConvertError&)
          {
               //ShowMessage("�� ����� ��������� �����");
               OpenBtn->Enabled=!OpenBtn->Enabled;
          }
     GraphicForm->ScrollBar1->Max=55;      
}
//---------------------------------------------------------------------------
//�������� �������
void __fastcall TBaseForm::NClear2Click(TObject *Sender)
{
     for (int i=1;i<Table->RowCount;i++)
          for (int j=1;j<Table->ColCount;j++)
               Table->Cells[j][i]="";
     N=0;
     M=0;
     NTranspon->Enabled=false;
}
//---------------------------------------------------------------------------
//���������������
void __fastcall TBaseForm::NTransponClick(TObject *Sender)
{
     int tempmax = (N > M)? N : M;
     tempmax++;
     if (Table->RowCount < tempmax)
          Table->RowCount = tempmax;
     if (Table->ColCount < tempmax)
          Table->ColCount = tempmax;
     int temp;
     for (int i = 1;i<tempmax;i++)
          for (int j=i+1;j<tempmax;j++)
          {
               temp=atoi(Table->Cells[i][j].c_str());
               Table->Cells[i][j]=Table->Cells[j][i];
               Table->Cells[j][i]=temp;
          }
     temp=N;
     N=M;
     M=temp;
     Swapf(); //�������� ���
     TableRefresh();
     //StatusBar1->Panels->Items[1]->Text=("�������: "+IntToStr(N));
     //StatusBar1->Panels->Items[2]->Text=("�������: "+IntToStr(M));
}
//---------------------------------------------------------------------------
//�����
void __fastcall TBaseForm::NOptionsClick(TObject *Sender)
{
     OptionsForm->Caption=("���������");
     OptionsForm->Position=poMainFormCenter;
     if(OptionsForm->ShowModal()==IDOK)
     {
          multicoloured=OptionsForm->ColorOptions->ItemIndex;
          CountScale(GraphicForm->TrackBar1->Position);
          GraphicForm->N2->Checked=OptionsForm->WorkTimeOut->Checked;
          GraphicForm->N4->Checked=OptionsForm->ColorOptions->ItemIndex;
          if ((Brightness != OptionsForm->SpinBrightness->Value) || (OptionsForm->Contrast->Checked))
          {
               Brightness = OptionsForm->SpinBrightness->Value;
               ColorPit();
          }
          PaintGant();
     }
}
//---------------------------------------------------------------------------
//�����
void __fastcall TBaseForm::ReportExecute(TObject *Sender)
{
     //OpenBtn->Enabled=!OpenBtn->Enabled;
     Spinner->Visible=!Spinner->Visible;     
}
//---------------------------------------------------------------------------
//�������� ������ �������
void __fastcall TBaseForm::ResizeTableExecute(TObject *Sender)
{
     Application->CreateForm( __classid(TEnterDataForm),&EnterDataForm);
     EnterDataForm->Caption=("��������� ������� �������");
     EnterDataForm->BitBtnOkRandom->Visible=false;
     EnterDataForm->BitBtnOkResize->Visible=true;
     EnterDataForm->Position=poMainFormCenter;
     EnterDataForm->ShowModal();
     EnterDataForm->Free();  
}
//---------------------------------------------------------------------------
//���������� ���������� �������
void __fastcall TBaseForm::RandomExecute(TObject *Sender)
{
     Application->CreateForm( __classid(TEnterDataForm),&EnterDataForm);
     EnterDataForm->Caption=("���������� ���������� �������");
     EnterDataForm->BitBtnOkRandom->Visible=true;
     EnterDataForm->BitBtnOkResize->Visible=false;
     EnterDataForm->Position=poMainFormCenter;
     EnterDataForm->ShowModal();
     EnterDataForm->Free();
}
//---------------------------------------------------------------------------
//����������
void __fastcall TBaseForm::NCopyClick(TObject *Sender)
{
     Output->CopyToClipboard();
     ShowMessage("������ ���������� ��� CTRL+C!");
}
//�����
void __fastcall TBaseForm::FontEditAccept(TObject *Sender)
{
     //TWinControl* Fonted = BaseForm->ActiveControl;
     ((TMemo*)BaseForm->ActiveControl)->Font=FontEdit->Dialog->Font;
     //ShowMessage("��������� ������� � ���������� " + ((TComponent *)BaseForm->ActiveControl)->Name);
     //BaseForm->ActiveControl->cla
     //Output->Font=FontEdit->Dialog->Font;
}
//---------------------------------------------------------------------------
//����������� ����� � ��������
void __fastcall TBaseForm::TableColumnMoved(TObject *Sender, int FromIndex, int ToIndex)
{    TableRefresh();     }
void __fastcall TBaseForm::TableRowMoved(TObject *Sender, int FromIndex, int ToIndex)
{    TableRefresh();     }
//---------------------------------------------------------------------------
//������� �� ��������� �����
void __fastcall TBaseForm::GoGantBtnClick(TObject *Sender)
{
     GraphicForm->BringToFront();
     GraphicForm->SetFocus();
}
//---------------------------------------------------------------------------
//� ���������
void __fastcall TBaseForm::NAboutClick(TObject *Sender)
{
     Application->CreateForm( __classid(TAboutBox1),&AboutBox1);
     AboutBox1->ShowModal();
     AboutBox1->Free();
}
//---------------------------------------------------------------------------
//������� ���� � ����������
void __fastcall TBaseForm::StatusBar1DblClick(TObject *Sender)
{
     TPoint mouse;
     GetCursorPos(&mouse);
     int x=mouse.x-StatusBar1->Left;
     int y=mouse.y-StatusBar1->Top;
     ShowMessage("DblClick in ("+IntToStr(x)+", "+IntToStr(y)+")");
}
//---------------------------------------------------------------------------
//���������� ������ ������
void __fastcall TBaseForm::FontEditBeforeExecute(TObject *Sender)
{
     if(((TComponent *)BaseForm->ActiveControl)->Name == "Table")
          FontEdit->Dialog->MaxFontSize=14;
     else
          FontEdit->Dialog->MaxFontSize=36;
}
//---------------------------------------------------------------------------
//������ ������� ������� �������
void __fastcall TBaseForm::NManualModeClick(TObject *Sender)
{
     BaseForm->Height=576;
     BaseForm->Width=832;
     Panel1->Visible=!NManualMode->Checked;
     if(NManualMode->Checked)
     {
          NManualMode->Checked=false;
          Output->SetBounds(284,64,533,432);
          Output->Anchors=Panel1->Anchors;
     }
     else
     {
          NManualMode->Checked=true;
          Output->SetBounds(284,64,256,432);
          Output->Anchors=Table->Anchors;
          ManualTableRefresh(true);
     }


}
//---------------------------------------------------------------------------
//����� ������ � ������� ������� �������
void __fastcall TBaseForm::ManualTableSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
     Spinner->Visible=true;
     Spinner->Left=37*ACol+597;   //37 - DefaultRowWidth + GridLineWidth
     Spinner->Top=27*ARow+67;

}
//---------------------------------------------------------------------------
//������� ���� �� ��������
void __fastcall TBaseForm::SpinnerDownClick(TObject *Sender)
{
     //ShowMessage("Col Row ("+IntToStr(ManualTable->Col)+", "+IntToStr(ManualTable->Row)+")");
     if (ManualTable->Row != M)
     {
          int c = StrToInt(ManualTable->Cells[ManualTable->Col][ManualTable->Row]);
          ManualTable->Cells[ManualTable->Col][ManualTable->Row]=ManualTable->Cells[ManualTable->Col][ManualTable->Row+1];
          ManualTable->Cells[ManualTable->Col][ManualTable->Row+1]=c;
     }
}
//---------------------------------------------------------------------------
//������� ����� �� ��������
void __fastcall TBaseForm::SpinnerUpClick(TObject *Sender)
{
     if (ManualTable->Row != 1)
     {
          int c = StrToInt(ManualTable->Cells[ManualTable->Col][ManualTable->Row]);
          ManualTable->Cells[ManualTable->Col][ManualTable->Row]=ManualTable->Cells[ManualTable->Col][ManualTable->Row-1];
          ManualTable->Cells[ManualTable->Col][ManualTable->Row-1]=c;
     }
}
//---------------------------------------------------------------------------
//������ ������ ��������
void __fastcall TBaseForm::ManualTableExit(TObject *Sender)
{
     Spinner->Visible=false;     
}
//---------------------------------------------------------------------------
//������� �� �������� ������������ ����������������� �����
void __fastcall TBaseForm::ProdBtnClick(TObject *Sender)
{
     Label2->Caption=ProductionCycle2();     
}
//---------------------------------------------------------------------------
//����������� �����
void __fastcall TBaseForm::ManualTableRowMoved(TObject *Sender,
      int FromIndex, int ToIndex)
{
     ManualTableRefresh(false);     
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::FileSaveBeforeExecute(TObject *Sender)
{
     if (BaseForm->ActiveControl == Table)
          FileSave->Dialog->FileName="input *";
     else
          FileSave->Dialog->FileName="report *";
}
//---------------------------------------------------------------------------

