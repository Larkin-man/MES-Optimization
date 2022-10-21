//------------���� ����������---------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "MainSource.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "EnterData.h"

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
     : TForm(Owner)
{    //��� ��������� �����
     Output->Text="";
     scale = 18;

     M=0;
     N=0;
     Label2->Caption="";
     NViewOne->Checked=true;
     view();
     Output->SetBounds(464,64,418,306);
     graphik=false;
     ultima=false;
     RunBtn->Enabled=false;
     OptimizationBtn->Enabled=false;
     GantBtn->Enabled=false;
     NSave->Enabled=false;
     OpenDialog1->InitialDir=GetCurrentDir();
     SaveDialog1->InitialDir=GetCurrentDir();
     Label2->Canvas->Pen->Color=clHotLight;
     Form1->Table->RowHeights[0]=26;
     Form1->Table->ColWidths[0]=88;
     Form1->Table->Cells[0][0]="    ������:";
     //������ - ������ ������� - ������
     for (int i=1;i<Table->RowCount;i++)
          Form1->Table->Cells[0][i]="������ " + IntToStr(i)+":";
     for (int j=1;j<Table->ColCount;j++)
          Form1->Table->Cells[j][0]=j;//"������ �"+i;
          //Output->Lines->Add("ColCount="+IntToStr(Table->ColCount));
}
//---------------------------------------------------------------------------
//�������
void __fastcall TForm1::NExitClick(TObject *Sender)
{
     delete Optimizer;
     Close();
     //Form1->Close();
}
//---------------------------------------------------------------------------
//�������
void __fastcall TForm1::NOpenClick(TObject *Sender)
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
                         if (Form1->Table->ColCount <= column)   //�������� ������� � �������
                                {
                                        for (int k=1;k<Table->RowCount;k++)
                                                Table->Cells[column][k]="";
                                        Form1->Table->ColCount++;
                                        Form1->Table->Cells[column][0]=column;
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
          delete pStrings;
          NSave->Enabled=true;
     }
}
//---------------------------------------------------------------------------
//���������
void __fastcall TForm1::NSaveClick(TObject *Sender)
{
     if(SaveDialog1->Execute()==IDOK)
     {
          Output->Lines->SaveToFile(SaveDialog1->FileName);
          StatusBar1->Panels->Items[0]->Text=SaveDialog1->FileName;
     }

}
//---------------------------------------------------------------------------
//�����
void __fastcall TForm1::NFontClick(TObject *Sender)
{
     if (FontDialog1->Execute())
     {
          Output->Font=FontDialog1->Font;
     }

}
//---------------------------------------------------------------------------
//����������
void __fastcall TForm1::N15Click(TObject *Sender)
{
     Output->CopyToClipboard();
     ShowMessage("������ ���������� ��� CTRL+C!");
     NViewTwoClick(Sender);
}
//---------------------------------------------------------------------------
//� ���������
void __fastcall TForm1::NAboutClick(TObject *Sender)
{
     Application->CreateForm( __classid(TAboutBox1),&AboutBox1);
     AboutBox1->ShowModal();
     AboutBox1->Free();
}
//---------------------------------------------------------------------------
//��������
void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
     char str[50], *vx;
     //strcpy(str, Edit3->Text.c_str());
     vx = strchr(str,',');              //������ ������� �� �����
     if (vx)
          str[vx-str]='.';
     //ListBox1->Items->Add(str);
     StatusBar1->SimpleText=("");
}
//---------------------------------------------------------------------------
//�������
void __fastcall TForm1::RunBtnClick(TObject *Sender)
{
     if ((M <= 1)||(N <= 1))
     {
          //MessageDlg("������ �� �������", mtError,TMsgDlgButtons () << mbOK, 0);
          Application->MessageBox ("������ �� �������", "������" , MB_ICONSTOP) ;
          return;
     }
     switch (RadioGroup1->ItemIndex)
     {
          case 0:
               Output->Lines->Add("�������� ��������");
               DjonsonAlgorithm();
               break;
          case 1:
               Output->Lines->Add("����� �������-����������");
               PetrovSokolMethod();
               break;
          case 2:
               Output->Lines->Add("����� ������ � ������");
               MethodBH ();
               break;
          default:
               return;
     }
     Output->Lines->Add("");
     OptimizationBtn->Enabled=true;
     GantBtn->Enabled=true;
}
//---------------------------------------------------------------------------
//������� ���
void __fastcall TForm1::NViewOneClick(TObject *Sender)
{
     Form1->Height=448;
     Form1->Width=896;
     NViewOne->Checked=true;
     NViewTwo->Checked=false;
     view();
     Table->SetBounds(8,164,450,206);
     Output->SetBounds(464,64,418,306);
}
//---------------------------------------------------------------------------
//����������
void __fastcall TForm1::NViewTwoClick(TObject *Sender)
{
     Form1->Height=448;
     Form1->Width=896;
     NViewTwo->Checked=true;
     NViewOne->Checked=false;
     Table->SetBounds(277,64,188,308);
     //Table->ColWidths=2;
     Output->SetBounds(8,176,265,193);
     view();
}
//---------------------------------------------------------------------------
//��������(����)
void __fastcall TForm1::N12Click(TObject *Sender)
{
     Output->Clear();
}
//---------------------------------------------------------------------------
//�� �����
void __fastcall TForm1::FormPaint(TObject *Sender)
{
     if (graphik)
          PaintGant();
}
//---------------------------------------------------------------------------
//������������
void __fastcall TForm1::NGantRepaintClick(TObject *Sender)
{
     if (graphik)
          PaintGant();
}
//---------------------------------------------------------------------------
//����� ���������
void __fastcall TForm1::NGantFontClick(TObject *Sender)
{
     if (FontDialog2->Execute())
     {
          Label2->Font=FontDialog2->Font;
     }
     PaintGant();
}
//---------------------------------------------------------------------------
//���� ���������
void __fastcall TForm1::NGantColorClick(TObject *Sender)
{
     if (ColorDialog1->Execute())
     {
          Label2->Canvas->Pen->Color=ColorDialog1->Color;
     }
     PaintGant();
}
//---------------------------------------------------------------------------
//��������� �������� ���������
void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
     scale=(TrackBar1->Position)+14;
     PaintGant();
}
//---------------------------------------------------------------------------
//����������� - ���������� ���������
void __fastcall TForm1::NOptSwitchClick(TObject *Sender)
{
     ultima=true;
}
//---------------------------------------------------------------------------
//����� ���������
void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
     view();
}
//---------------------------------------------------------------------------
//������� �����
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
     delete Optimizer;
}
//---------------------------------------------------------------------------
//�����
void __fastcall TForm1::NewBtnClick(TObject *Sender)
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
void __fastcall TForm1::GantBtnClick(TObject *Sender)
{
     if (GantBtn->Down)
     {
          Form3->Show();
          Form1->BringToFront();
     }
     else
     {
          Form3->Close();
     }
}
//---------------------------------------------------------------------------
//���� �� ����������� ������
void __fastcall TForm1::N1Click(TObject *Sender)
{
     Output->Lines->Add("������� ������� L T H W");
     Output->Lines->Add(Table->Left);
     Output->Lines->Add(Table->Top);
     Output->Lines->Add(Table->Height);
     Output->Lines->Add(Table->Width);
     //Table->Cols[2]->Delete(4);   //I dont understand
}
//---------------------------------------------------------------------------
//�������� �������
void __fastcall TForm1::N2Click(TObject *Sender)
{
     for (int i=1;i<Table->RowCount;i++)
          for (int j=1;j<Table->ColCount;j++)
               Table->Cells[j][i]="";
}
//---------------------------------------------------------------------------
//�������� ������ �������
void __fastcall TForm1::N3Click(TObject *Sender)
{
//port temp;
Form2->Caption=("��������� ������� �������");
Form2->Position=poMainFormCenter;
Form2->ShowModal();       
//if (CheckBox1->Checked)
// {
// strcpy(temp.city,Form2->Edit1->Text.c_str());
// AddA(temp);
// PrintListA();
// }
}
//---------------------------------------------------------------------------
                  
