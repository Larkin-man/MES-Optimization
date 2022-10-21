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

TBaseForm *BaseForm;
//---------------------------------------------------------------------------
__fastcall TBaseForm::TBaseForm(TComponent* Owner)
     : TForm(Owner)
{    //��� ��������� �����
     Output->Clear();
     scale = 18;
     M=0;
     N=0;
     Label1->Caption="";
     NViewOne->Checked=true;
     Output->SetBounds(464,64,418,337);
     graphik=false;
     ultima=false;
     Run->Enabled=false;
     Optimization->Enabled=false;
     GantDiagram->Enabled=false;
     Report->Enabled=false;
     FileSave->Enabled=false;
     NTranspon->Enabled=false;
     //ReportBtn->Enabled=false;
     FileOpen->Dialog->InitialDir=GetCurrentDir();
     FileSave->Dialog->InitialDir=GetCurrentDir();
     Label1->Canvas->Pen->Color=clHotLight;
     BaseForm->Table->RowHeights[0]=26;
     BaseForm->Table->ColWidths[0]=82;
     BaseForm->Table->Cells[0][0]="    ������:";
     view();
     //������ - ������ ������� - ������
     for (int i=1;i<Table->RowCount;i++)
          BaseForm->Table->Cells[0][i]="������ " + IntToStr(i)+":";
     for (int j=1;j<Table->ColCount;j++)
          BaseForm->Table->Cells[j][0]=j;//"������ �"+i;
          //Output->Lines->Add("ColCount="+IntToStr(Table->ColCount));
     //Form1->SetFocus();
      Gant = NULL;
      gantshow = false;
      Label1->Align=alClient;
      for (int i=0;i<4;i++)
          TimeCycle[i] = 0;
}
//---------------------------------------------------------------------------
//�������
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
          for(int i=0; i < pStrings->Count; i++) //���� �� �������
          {
               char *s = pStrings->Strings[i].c_str();
               int column = 1; //�������
               for (int j =0;j < pStrings->Strings[i].Length();j++) //���� �� ��������
               {
                    if (s[j]== ' ')
                    {
                         column++;
                         //Table->Cells[row][i+1]="";  //clear
                         if (BaseForm->Table->ColCount <= column)   //�������� ������� � �������
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
               Table->Cells[0][i+1]="������ " + IntToStr(i+1)+":";
          }    
          M = pStrings->Count;
          delete pStrings;
     Ready();
}
//---------------------------------------------------------------------------
//���������
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
//� ���������
void __fastcall TBaseForm::NAboutClick(TObject *Sender)
{
     Application->CreateForm( __classid(TAboutBox1),&AboutBox1);
     AboutBox1->ShowModal();
     AboutBox1->Free();
}
//---------------------------------------------------------------------------
//�������
void __fastcall TBaseForm::RunExecute(TObject *Sender)
{
     if ((M <= 1)||(N <= 1))
     {
          //MessageDlg("������ �� �������", mtError,TMsgDlgButtons () << mbOK, 0);
          Application->MessageBox ("������ �� �������", "������" , MB_ICONSTOP) ;
          return;
     }

     delete Optimizer;   //TODO: ����� � ������ ?
     Optimizer = new MachineOptimizer;  //��������� ������, ����������� ��� ������. �������� � ���������� OptimizationMtds.h
     delete Gant;
     Gant = new Graphics::TBitmap;

     int *T = new int[N];
     for (int i = 1;i<M+1;i++)
     {
          for (int j = 1;j<N+1;j++)
          {
               T[j-1]=atof(Table->Cells[j][i].c_str());
          }
          Optimizer->add(N,T);
     }
     Output->Lines->Add("�������� �������:");
     PrintMatrix(Optimizer->InitBegin,N,false,false);
     TimeCycle[0]=ProductionCycle();
     StatusBar1->Panels->Items[3]->Text=("������������ ����������������� �����: "+IntToStr(TimeCycle[0]));
     Output->Lines->Add("������������ ����������������� �����: "+IntToStr(TimeCycle[0]));
     Output->Lines->Add("");
     Output->Lines->Add("");
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
          default:
               return;
     }
     Output->Lines->Add("");
     Output->Lines->Add("----------------------------------------");
     Output->Lines->Add("");
     Optimization->Enabled=true;
     GantDiagram->Enabled=true;
     Report->Enabled=true;
}
//---------------------------------------------------------------------------
//������� ���
void __fastcall TBaseForm::NViewOneClick(TObject *Sender)
{
     BaseForm->Height=480;
     BaseForm->Width=896;
     NViewOne->Checked=true;
     NViewTwo->Checked=false;
     Table->SetBounds(8,168,450,232);
     Output->SetBounds(464,64,417,336);
     Output->Anchors=Panel1->Anchors;
     view();
}
//---------------------------------------------------------------------------
//����������
void __fastcall TBaseForm::NViewTwoClick(TObject *Sender)
{
     Panel1->Visible=false;
     BaseForm->Height=480;
     BaseForm->Width=896;
     NViewTwo->Checked=true;
     NViewOne->Checked=false;
     Table->SetBounds(272,64,187,336);
     Output->SetBounds(8,168,257,232);
     Panel1->SetBounds(464,64,417,336);
     //Output->Anchors=akLeft,akTop,akRight,akBottom;
     Output->Anchors=Table->Anchors;
     view();
}
//---------------------------------------------------------------------------
//��������� �����
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
     //Box = new TColor[BaseForm->M];
     //for (int i=0;i<BaseForm->M;i++)
     //     Box[i]=TColor(random(16000000));
}
//---------------------------------------------------------------------------
//��������(����)
void __fastcall TBaseForm::N12Click(TObject *Sender)
{
     Output->Clear();
}
//---------------------------------------------------------------------------
//������������ / OnPaint
void __fastcall TBaseForm::RepaintExecute(TObject *Sender)
{
     if (graphik)
          Label1->Canvas->CopyRect(Rect(0,0,600,400),Gant->Canvas,Rect(0,0,600,400));
}
//---------------------------------------------------------------------------
//����� ���������
void __fastcall TBaseForm::NGantFontClick(TObject *Sender)
{
     if (FontDialog2->Execute())  /* TODO 2 : ������� ��� ������� */
     {
          Label1->Font=FontDialog2->Font;
     }
     PaintGant();
}
//---------------------------------------------------------------------------
//���� ���������
void __fastcall TBaseForm::NGantColorClick(TObject *Sender)
{
     if (GantPenColor->Execute())
     {
          Gant->Canvas->Pen->Color=GantPenColor->Color;
     }
     PaintGant();
}
//---------------------------------------------------------------------------
//��������� �������� ���������
void __fastcall TBaseForm::TrackBar1Change(TObject *Sender)
{
     scale=(TrackBar1->Position)+14;
     PaintGant();
}
//---------------------------------------------------------------------------
//������� �����
void __fastcall TBaseForm::FormClose(TObject *Sender, TCloseAction &Action)
{
     //ShowMessage("close form");
     delete Optimizer;
}
//---------------------------------------------------------------------------
//�����
void __fastcall TBaseForm::FileNewExecute(TObject *Sender)
{
     Output->Clear();
     graphik = false;
     delete Optimizer;
     Optimizer = NULL;
     delete Gant;
     Gant = NULL;
     for (int i=1;i<Table->RowCount;i++)
          Table->Cells[0][i]="������ " + IntToStr(i)+":";
     for (int j=1;j<Table->ColCount;j++)
          Table->Cells[j][0]=j;
     FileSave->Enabled=false;
     Optimization->Enabled=false;
     GantDiagram->Enabled=false;
     Report->Enabled=false;
     GantBtn->Down=false;
     GraphicForm->Close();

     /*
     int red,green,blue;
     srand(time(NULL));
     red=rand()%256;
     green=(rand()%255)*256+256;
     blue=(rand()%255)*256*256+256*256;
     ToolBar1->Color=TColor(red);
     GroupBox1->Color=TColor(green);
     RadioGroup1->Color=TColor(blue);
     Table->Color=TColor(blue+green+red);         */
}
//---------------------------------------------------------------------------
//����������� - ���������� ���������
void __fastcall TBaseForm::OptimizationExecute(TObject *Sender)
{
     ultima=true;
}
//---------------------------------------------------------------------------
//���� �� ����������� ������
void __fastcall TBaseForm::N1Click(TObject *Sender)
{
     Output->Lines->Add("������� ������� L T H W");
     Output->Lines->Add(Table->Left);
     Output->Lines->Add(Table->Top);
     Output->Lines->Add(Table->Height);
     Output->Lines->Add(Table->Width);
     //Optimizer->MethodBHt(Form1->Output);
     //Table->Cols[2]->Delete(4);   //I dont understand
     for (MachineOptimizer::Link *Item =Optimizer->InitBegin;Item != NULL;Item = Item->next)
          for (int s = 0 ; s < N; s++)
               Table->Cells[s+1][Item->curr->m+4]=Item->curr->T[s];
     for (MachineOptimizer::Link *Item =Optimizer->OptimalDJ;Item != NULL;Item = Item->next)
          for (int s = 0 ; s < N; s++)
               Table->Cells[s+4][Item->curr->m+4]=Item->curr->T[s];

}
//---------------------------------------------------------------------------
//�������� �������
void __fastcall TBaseForm::N2Click(TObject *Sender)
{
     for (int i=1;i<Table->RowCount;i++)
          for (int j=1;j<Table->ColCount;j++)
               Table->Cells[j][i]="";
}
//---------------------------------------------------------------------------
//���������������
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
     StatusBar1->Panels->Items[1]->Text=("�������: "+IntToStr(N));
     StatusBar1->Panels->Items[2]->Text=("�������: "+IntToStr(M));
}
//---------------------------------------------------------------------------
//�����
void __fastcall TBaseForm::NOptionsClick(TObject *Sender)
{
     OptionsForm->Caption=("���������");
     OptionsForm->Position=poMainFormCenter;
     if(OptionsForm->ShowModal()==IDOK)
     {

     }
}
//---------------------------------------------------------------------------
//�����
void __fastcall TBaseForm::ReportExecute(TObject *Sender)
{
     OpenBtn->Enabled=!OpenBtn->Enabled;
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
     // strcpy(temp.city,Form2->Edit1->Text.c_str());
     // AddA(temp);
     EnterDataForm->Free();

}
//---------------------------------------------------------------------------
//���������� ���������� �������
void __fastcall TBaseForm::Pf1Click(TObject *Sender)
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
//�����
void __fastcall TBaseForm::NFontClick(TObject *Sender)
{
     if (FontDialog1->Execute())
     {
          Output->Font=FontDialog1->Font;
     }
}
//---------------------------------------------------------------------------
//����������
void __fastcall TBaseForm::N15Click(TObject *Sender)
{
     Output->CopyToClipboard();
     ShowMessage("������ ���������� ��� CTRL+C!");
     NViewTwoClick(Sender);
}
//---------------------------------------------------------------------------
//�������� ����� ������
void __fastcall TBaseForm::NGantTimeClick(TObject *Sender)
{
     NGantTime->Checked=true;
     if (OptionsForm->WorkTimeOut->Checked == false)
          OptionsForm->WorkTimeOutClick(NULL);
     OptionsForm->WorkTimeOut->Checked == true;
}
//---------------------------------------------------------------------------

