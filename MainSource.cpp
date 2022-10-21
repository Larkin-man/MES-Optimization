//------------���� ����������---------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "MainSource.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
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
     Label2->Caption="";
     NViewOne->Checked=true;
     Output->SetBounds(464,64,418,337);
     graphik=false;
     ultima=false;
     RunBtn->Enabled=false;
     OptimizationBtn->Enabled=false;
     GantBtn->Enabled=false;
     NSave->Enabled=false;
     NTranspon->Enabled=false;
     ReportBtn->Enabled=false;
     OpenDialog1->InitialDir=GetCurrentDir();
     SaveDialog1->InitialDir=GetCurrentDir();
     Label2->Canvas->Pen->Color=clHotLight;
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
      Gant = new Graphics::TBitmap;

}
//---------------------------------------------------------------------------
//�������
void __fastcall TBaseForm::NOpenClick(TObject *Sender)
{
     if(OpenDialog1->Execute()==IDOK)
     {
          StatusBar1->Panels->Items[0]->Text=OpenDialog1->FileName;
          for (int i=1;i<Table->RowCount;i++)
               for (int j=1;j<Table->ColCount;j++)
                    Table->Cells[j][i]="";

          TStringList *pStrings = new TStringList;
          pStrings->LoadFromFile(OpenDialog1->FileName);
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
          //Form1->Output->Text=atof(Table->Cells[5][1].c_str());         
          StatusBar1->Panels->Items[1]->Text=("�������: "+IntToStr(N));
          StatusBar1->Panels->Items[2]->Text=("�������: "+IntToStr(M));
          if (OptionsForm->RadioGroupTime->ItemIndex != 2)
               StatusBar1->Panels->Items[3]->Text=("������������ ����������������� �����: "+IntToStr(ProductionCycle()));
          delete pStrings;
          NSave->Enabled=true;
          NTranspon->Enabled=true;
     }
}
//---------------------------------------------------------------------------
//���������
void __fastcall TBaseForm::NSaveClick(TObject *Sender)
{
     if(SaveDialog1->Execute()==IDOK)
     {
          Output->Lines->SaveToFile(SaveDialog1->FileName);
          StatusBar1->Panels->Items[0]->Text=SaveDialog1->FileName;
     }
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
//� ���������
void __fastcall TBaseForm::NAboutClick(TObject *Sender)
{
     Application->CreateForm( __classid(TAboutBox1),&AboutBox1);
     AboutBox1->ShowModal();
     AboutBox1->Free();
}
//---------------------------------------------------------------------------
//�������
void __fastcall TBaseForm::RunBtnClick(TObject *Sender)
{
     if ((M <= 1)||(N <= 1))
     {
          //MessageDlg("������ �� �������", mtError,TMsgDlgButtons () << mbOK, 0);
          Application->MessageBox ("������ �� �������", "������" , MB_ICONSTOP) ;
          return;
     }

     delete Optimizer;   //TODO: ����� � ������ ?
     Optimizer = new MachineOptimizer;  //��������� ������, ����������� ��� ������. �������� � ���������� OptimizationMtds.h
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
     Output->Lines->Add("������������ ����������������� �����: "+IntToStr(ProductionCycle()));
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
     OptimizationBtn->Enabled=true;
     GantBtn->Enabled=true;
     ReportBtn->Enabled=true;
}
//---------------------------------------------------------------------------
//������� ���
void __fastcall TBaseForm::NViewOneClick(TObject *Sender)
{
     BaseForm->Height=480;
     BaseForm->Width=896;
     NViewOne->Checked=true;
     NViewTwo->Checked=false;
     view();
     Table->SetBounds(8,164,450,237);
     Output->SetBounds(464,64,418,337);
}
//---------------------------------------------------------------------------
//����������
void __fastcall TBaseForm::NViewTwoClick(TObject *Sender)
{
     BaseForm->Height=480;
     BaseForm->Width=896;
     NViewTwo->Checked=true;
     NViewOne->Checked=false;
     Table->SetBounds(277,64,188,339);
     Output->SetBounds(8,176,265,224);
     view();
}
//---------------------------------------------------------------------------
//��������(����)
void __fastcall TBaseForm::N12Click(TObject *Sender)
{
     Output->Clear();
}
//---------------------------------------------------------------------------
//�� �����
void __fastcall TBaseForm::FormPaint(TObject *Sender)
{
     if (graphik)
          PaintGant();
}
//---------------------------------------------------------------------------
//������������
void __fastcall TBaseForm::NGantRepaintClick(TObject *Sender)
{
     if (graphik)
          PaintGant();
}
//---------------------------------------------------------------------------
//����� ���������
void __fastcall TBaseForm::NGantFontClick(TObject *Sender)
{
     if (FontDialog2->Execute())
     {
          Label2->Font=FontDialog2->Font;
     }
     PaintGant();
}
//---------------------------------------------------------------------------
//���� ���������
void __fastcall TBaseForm::NGantColorClick(TObject *Sender)
{
     if (ColorDialog1->Execute())
     {
          Label2->Canvas->Pen->Color=ColorDialog1->Color;
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
//����������� - ���������� ���������
void __fastcall TBaseForm::NOptSwitchClick(TObject *Sender)
{
     ultima=true;
}
//---------------------------------------------------------------------------
//����� ���������
void __fastcall TBaseForm::RadioGroup1Click(TObject *Sender)
{    
     view();
}
//---------------------------------------------------------------------------
//�������
void __fastcall TBaseForm::NExitClick(TObject *Sender)
{
     //ShowMessage("close click");
     //delete Optimizer;
     Close();
     //Form1->Close();
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
void __fastcall TBaseForm::NewBtnClick(TObject *Sender)
{
     Output->Clear();
     graphik = false;
     delete Optimizer;
     Optimizer = NULL;
     for (int i=1;i<Table->RowCount;i++)
          Table->Cells[0][i]="������ " + IntToStr(i)+":";
     for (int j=1;j<Table->ColCount;j++)
          Table->Cells[j][0]=j;


}
//---------------------------------------------------------------------------
//��������� �����
void __fastcall TBaseForm::ReportBtnClick(TObject *Sender)
{
     if (GantBtn->Down)
     {
          GraphicForm->Show();
          BaseForm->BringToFront();
     }
     else
     {
          GraphicForm->Close();
     }
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
//�������� ������ �������
void __fastcall TBaseForm::NSizeClick(TObject *Sender)
{
     EnterDataForm->Caption=("��������� ������� �������");
     EnterDataForm->Position=poMainFormCenter;
     EnterDataForm->ShowModal();
     // strcpy(temp.city,Form2->Edit1->Text.c_str());
     // AddA(temp);
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
     //Form4->ShowModal();
     if(OptionsForm->ShowModal()==IDOK)
     {

     }
}
//---------------------------------------------------------------------------
void __fastcall TBaseForm::TableRowMoved(TObject *Sender, int FromIndex,
      int ToIndex)
{
     for (int i=1;i<Table->RowCount;i++)
          Table->Cells[0][i]="������ " + IntToStr(i)+":";
     for (int j=1;j<Table->ColCount;j++)
          Table->Cells[j][0]=j;
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::TableColumnMoved(TObject *Sender, int FromIndex,
      int ToIndex)
{
     for (int i=1;i<Table->RowCount;i++)
          Table->Cells[0][i]="������ " + IntToStr(i)+":";
     for (int j=1;j<Table->ColCount;j++)
          Table->Cells[j][0]=j;     
}
//---------------------------------------------------------------------------




