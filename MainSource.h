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
#include "cspin.h"
#include <System.Actions.hpp>

const AnsiString Method[] = {			//[]
	"�������� ��������",				//0
	"����� �������-����������",			//1
	"����� ������ � ������",			//2
	"���������������� ����� ������ � ������",//3
	"����� �����" };					//4
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
	TRadioGroup *Methods;
	TMenuItem *NMenuRun;
	TMenuItem *NOptSwitch;
	TMenuItem *NRun;
	TMenuItem *N9;
	TPopupMenu *PopupMenuGrid;
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
	TSpeedButton *GoGantBtn;
	TMenuItem *NRandom;
	TAction *Random;
	TMenuItem *NFont2;
	TStringGrid *Table;
	TMenuItem *NManualMode;
	TPanel *Panel1;
	TStringGrid *ManualTable;
	TSpeedButton *AddToGantBtn;
	TLabel *LabelPsd;
	TCSpinButton *Spinner;
	TSpeedButton *ProdBtn;
	TStaticText *ProgressText;
	TMenuItem *NHelp;
	TAction *ConstructC;
	TMenuItem *NCMatBuilt;
	TMenuItem *NCMatrix;
	TLabel *PsdOut;
	TStaticText *StaticText1;
	void __fastcall NCopyClick(TObject *Sender);
	void __fastcall NAboutClick(TObject *Sender);
	void __fastcall NClear1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall NClear2Click(TObject *Sender);
	void __fastcall NTransponClick(TObject *Sender);
	void __fastcall NOptionsClick(TObject *Sender);
	void __fastcall FileOpenAccept(TObject *Sender);
	void __fastcall FileNewExecute(TObject *Sender);
	void __fastcall FileSaveAccept(TObject *Sender);
	void __fastcall RunExecute(TObject *Sender);
	void __fastcall OptimizationExecute(TObject *Sender);
	void __fastcall GantDiagramExecute(TObject *Sender);
	void __fastcall ResizeTableExecute(TObject *Sender);
	void __fastcall FontEditAccept(TObject *Sender);
	void __fastcall TableColumnMoved(TObject *Sender, int FromIndex, int ToIndex);
	void __fastcall TableRowMoved(TObject *Sender, int FromIndex, int ToIndex);
	void __fastcall GoGantBtnClick(TObject *Sender);
	void __fastcall RandomExecute(TObject *Sender);
	void __fastcall FontEditBeforeExecute(TObject *Sender);
	void __fastcall NManualModeClick(TObject *Sender);
	void __fastcall ManualTableSelectCell(TObject *Sender, int ACol,
		int ARow, bool &CanSelect);
	void __fastcall SpinnerDownClick(TObject *Sender);
	void __fastcall SpinnerUpClick(TObject *Sender);
	void __fastcall ManualTableExit(TObject *Sender);
	void __fastcall ProdBtnClick(TObject *Sender);
	void __fastcall ManualTableRowMoved(TObject *Sender, int FromIndex, int ToIndex);
	void __fastcall FileSaveBeforeExecute(TObject *Sender);
   void __fastcall NHelpClick(TObject *Sender);
   void __fastcall TableSetEditText(TObject *Sender, int ACol, int ARow,
		const AnsiString Value);
   void __fastcall ConstructCExecute(TObject *Sender);
	void __fastcall ReportExecute(TObject *Sender);
private:	// User declarations
//������ � �������� ������� ������

public:		// User declarations
	__fastcall TBaseForm(TComponent* Owner);  //���������� ������������
	MachineOptimizer *Optimizer;
	Graphics::TBitmap *Gant;
	int vertix,scale,i,j;
	int  BH,  //Block Height = 30 (�� ������ 14!)
		BI,  //Block Interval = 10
		TX,  //Text Out X = 5
		TY,  //Text Out Y = 8
		GantH,    //Gant Height
		GantW,   //Gant Weight
		Edge,	//���� ��� �������� ������� = 60
		ColorSave; //���������� ����������� ������

	int M,N; //N - ������, M - ������
	int TimeCycleMethod[5];
	bool gantshow;
	TColor *ColorBox;   //�������� ��� ������������ �������� ������
	int Brightness;	//�������
	bool multicoloured, out;
	DWORD Tick;	
	int CurrentCycle;
	int MVGTimeCycle;

void Ready(bool Access); //���������� � ������� �������
void Swapf();
void TableRefresh(); //�������� �������
void ColorPit(); //��������� ��������� ������
//������� ������� �������. down - � ��������� ���� �� ������; subtractb - � ���������� ������� �������������
void PrintMatrix(const MachineOptimizer::Link *list, int n, bool down, bool subtractb);
//������� ���� ������������ ����������������� �����
int __fastcall ProductionCycle();
//������� ������ ��������� ����� c ������� ������� ������������� ���������
void DrawDiagramFromDurationMatrix(const MachineOptimizer::Link *List, bool down);
//������� ������ ��������� ����� c ������� ������� ��������� ��������� (�)
void DrawDiagramFromEndingMatrix(const MachineOptimizer::Link *Item);
void PaintGant(); //�������� ��������� ����� � ���������� � ���������
void CountScale(int Scroller = 5); //����������� ������� ���������
int DjonsonAlgorithm();
int PetrovSokolMethod();
int MethodBH (bool Modifycations); //Method  of branches and hordes
int NewMethod();
void ManualTableRefresh(bool full); //�������� �������
int ProductionCycle2(); //���������� ������������ ����������������� �����
   int *top;
void PrintMatrixPS(const MachineOptimizer::Link *list,int n,int one,int left);

};
//---------------------------------------------------------------------------
extern PACKAGE TBaseForm *BaseForm;
//---------------------------------------------------------------------------
//���������� � ������� �������
void TBaseForm :: Ready(bool Access)
{
	FileSave->Enabled=Access;
	Optimization->Enabled=Access;
	GantDiagram->Enabled=Access;
	Report->Enabled=Access;
	NManualMode->Enabled=Access;
}
//---------------------------------------------------------------------------
//���������� ���
void TBaseForm ::Swapf()
{
	 MVGTimeCycle = 100000;
	StatusBar1->Panels->Items[0]->Width=400;
	StatusBar1->Panels->Items[1]->Text=("�������: "+IntToStr(N));
	StatusBar1->Panels->Items[2]->Text=("�������: "+IntToStr(M));
	if ((M == 0) || (N == 0))
		StatusBar1->Panels->Items[3]->Text="";
	else
	{
		CurrentCycle = ProductionCycle();
		StatusBar1->Panels->Items[3]->Text=("������������ ����������������� �����: "+IntToStr(CurrentCycle));
	}
	NTranspon->Enabled=true;
	if (NManualMode->Checked)
		ManualTableRefresh(true);
}
//---------------------------------------------------------------------------
//�������� �������
void TBaseForm :: TableRefresh()
{
	Table->Cells[0][0]="    ������:";
	//������ - ������ ������� - ������
	for (int i=1;i<Table->RowCount;i++)
		Table->Cells[0][i]="������ " + IntToStr(i)+":";
	for (int j=1;j<Table->ColCount;j++)
		Table->Cells[j][0]=j;//"������ �"+i;
	if (Table->RowCount <= 10)
		Table->ColWidths[0]=82;
	else if (Table->RowCount <= 100)
		Table->ColWidths[0]=88;
	else
		Table->ColWidths[0]=96;
	ManualTable->ColWidths[0] = Table->ColWidths[0];
}
//---------------------------------------------------------------------------
//��������� ��������� ������
void TBaseForm :: ColorPit()
{
	TColor red,green,blue;
	srand(time(NULL));
	for (int i = 0; i<M; i++)
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
	//ToolBar1->Color=red; RadioGroup1->Color=green; Table->Color=blue;
}
//---------------------------------------------------------------------------
//������� ������� �������. down - � ��������� ���� �� ������; subtractb - � ���������� ������� �������������
void TBaseForm :: PrintMatrix(const MachineOptimizer::Link *list, int n, bool down, bool subtractb)
{
	//ShowMessage("n="+IntToStr(n));
	AnsiString row;
	if (!subtractb)
	{
		MachineOptimizer::Detal *Item;
		for (;list != NULL;list = list->next)
		{
			if (down)
				Item = list->down->curr;	 //��������� ���� �� ������
			else
				Item = list->curr;
			row="";
			row+=(IntToStr(Item->m)+"  |  ");
			for (int i = 0;i<n;i++)
				row+=(IntToStr(Item->T[i])+"  ");
			Output->Lines->Append(row);
		}
	}
	else		
	{
		j=0;
		for (;list != NULL;list = list->next)
		{
			j++;
			row="";
			row+=(IntToStr(list->curr->m)+"  |  ");
			for (int i = 0;i<n;i++)
				row+=(IntToStr(list->curr->T[i]-atoi(Table->Cells[i+1][j].c_str()))+"  ");
			Output->Lines->Append(row);
		}
	}
}
//---------------------------------------------------------------------------
//������� ���� ������������ ����������������� �����
int __fastcall TBaseForm :: ProductionCycle()
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
//---------------------------------------------------------------------------
//������� ������ ��������� ����� c ������� ������� ������������� ���������
void TBaseForm :: DrawDiagramFromDurationMatrix(const MachineOptimizer::Link *List, bool down)
{
	vertix+=BH;
	int N = Optimizer->GetN();
	int *SX = new int[N+1];
		for (int o = 0 ; o < N+1; o++)
			SX[o]=0;
	MachineOptimizer::Detal *Item;
	if (Edge < 20)
		Edge = 0;
	if (Edge >= 20)
		for (int s = 0 ; s < N; s++)	  //�������� �������
			Gant->Canvas->TextOut(TX,vertix+(BH+BI)*s+TY,""+IntToStr(s+1)+":");

	for (;List != NULL;List = List->next)   //�� �������
	{
		if (down)
			Item=List->down->curr;
		else
			Item=List->curr;
		if (multicoloured)
			Gant->Canvas->Brush->Color=ColorBox[Item->m-1];
		else
			Gant->Canvas->Brush->Color=GraphicForm->GantBrushColor->Color;
		for (int s = 0 ; s < N; s++)	  //�� �������
		{
			SX[s+1] = (SX[s] >= SX[s+1])? SX[s]+Item->T[s] : SX[s+1]+Item->T[s];
			Gant->Canvas->Rectangle((SX[s+1]-Item->T[s])*scale+Edge, vertix+(BH+BI)*s,
					SX[s+1]*scale+Edge, vertix+(BH+BI)*s+BH);
			if (OptionsForm->WorkTimeOut->Checked)
				Gant->Canvas->TextOut((SX[s+1]-Item->T[s])*scale+1+Edge,vertix+(BH+BI)*s+TY,IntToStr(Item->m)+" ("+IntToStr(Item->T[s])+")");
			else
				Gant->Canvas->TextOut((SX[s+1]-Item->T[s])*scale+TX+Edge,vertix+(BH+BI)*s+TY,Item->m);
		}
	}
	Gant->Canvas->Brush->Color=GraphicForm->ColorBox1->Selected;
	Gant->Canvas->TextOut(TX,vertix+(BH+BI)*N-BI+TY,"������������ ����������������� �����: "+FloatToStr(SX[N]));
	vertix=vertix+(BH+BI)*N-BI+BH;
	delete [] SX;
}
//---------------------------------------------------------------------------
//������� ������ ��������� ����� c ������� ������� ��������� ��������� (�)
void TBaseForm :: DrawDiagramFromEndingMatrix(const MachineOptimizer::Link *Item)
{
	vertix+=BH;
	int N = Optimizer->GetN();
	if (Edge < 20)
		Edge = 0;
	if (Edge >= 20)
		for (int s = 0 ; s < N; s++)	  //�������� �������
			Gant->Canvas->TextOut(TX,vertix+(BH+BI)*s+TY,""+IntToStr(s+1)+":");

	for (;Item != NULL;Item = Item->next)   //�� �������
		{
		if (multicoloured)
			Gant->Canvas->Brush->Color=ColorBox[Item->curr->m-1];
		else
			Gant->Canvas->Brush->Color=GraphicForm->GantBrushColor->Color;
			for (int s = 0 ; s < N; s++)	  //�� �������
			{
				Gant->Canvas->Rectangle(((Item->curr->T[s])-(Item->down->curr->T[s]))*scale+Edge, vertix+(BH+BI)*s,
						(Item->curr->T[s])*scale+Edge, vertix+(BH+BI)*s+BH);
				if (OptionsForm->WorkTimeOut->Checked)
					Gant->Canvas->TextOut(((Item->curr->T[s])-(Item->down->curr->T[s]))*scale+1+Edge, vertix+(BH+BI)*s+TY, IntToStr(Item->curr->m)+" ("+IntToStr(Item->down->curr->T[s])+")");
				else
					Gant->Canvas->TextOut(((Item->curr->T[s])-(Item->down->curr->T[s]))*scale+TX+Edge, vertix+(BH+BI)*s+TY, Item->curr->m);
			}
		}
	Gant->Canvas->Brush->Color=GraphicForm->ColorBox1->Selected;
	Gant->Canvas->TextOut(TX,vertix+(BH+BI)*N-BI+TY,"������������ ����������������� �����: "+FloatToStr(MVGTimeCycle));
	vertix=vertix+(BH+BI)*N-BI+BH;
}
//---------------------------------------------------------------------------
//�������� ��������� ����� � ���������� � ���������
void TBaseForm :: PaintGant()
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
	GantW = CurrentCycle;
	if ( TimeCycleMethod[Methods->ItemIndex] > GantW )
		GantW = TimeCycleMethod[Methods->ItemIndex];
	/*for (int i=0; i<5; i++)
		if (TimeCycleMethod[i] > GantW)
			GantW=TimeCycleMethod[i];	  */
	//ShowMessage("Gant weight="+IntToStr(GantW));
	GantW=GantW*scale+2+Edge;
	GantH=(BH+BI)*(N-1)*2+BH*6;
	Gant->Width=GantW;  ///////////////////////
	Gant->Height=GantH;  /* TODO : ������������� ����������� �������� */
	Gant->Canvas->Pen->Color=clBlack;
	Gant->Canvas->Pen->Width=1;
	Gant->Canvas->Brush->Color=GraphicForm->ColorBox1->Selected;
	Gant->Canvas->FillRect(Rect(0,0,GantW,GantH));
	//Gant->Canvas->Rectangle(0,0,Gant->Width,Gant->Height);
	Gant->Canvas->TextOut(TX,TY,"�������� ������:");
	DrawDiagramFromDurationMatrix(Optimizer->InitBegin,false);
	Gant->Canvas->CopyMode=cmSrcCopy;
	if ((Methods->ItemIndex == 0) && (Optimizer->OptimalDJ != NULL))    //TODO: switch case
	{
		Gant->Canvas->TextOut(TX,vertix+TY,"����������� �� ��������� ��������:");
		DrawDiagramFromDurationMatrix(Optimizer->OptimalDJ,false);
	}
	if ((Methods->ItemIndex == 1) && (Optimizer->PSBegin[1] != NULL))
	{
		Gant->Canvas->TextOut(TX,vertix+TY,"����������� �� ������ �������-����������:");
		DrawDiagramFromDurationMatrix(Optimizer->OptimalPS,true);
	}
	if ((Methods->ItemIndex == 2) && (Optimizer->OptimalBH != NULL))
	{
		Gant->Canvas->TextOut(TX,vertix+TY,"����������� �� ������ ������ � ������:");
		DrawDiagramFromEndingMatrix(Optimizer->OptimalBH);
	}
	if ((Methods->ItemIndex == 3) && (Optimizer->OptimalBH != NULL))
	{
		Gant->Canvas->TextOut(TX,vertix+TY,"����������� �� ���������������� ������ ������ � ������:");
		DrawDiagramFromEndingMatrix(Optimizer->OptimalBH);
	}
	if ((Methods->ItemIndex == 4) && (Optimizer->OptimalNew != NULL))
	{
		//ShowMessage("IHHA");
		Gant->Canvas->TextOut(TX,vertix+TY,"����������� �� ������ ������:");
		 DrawDiagramFromDurationMatrix(Optimizer->OptimalNew,false);
	}

	GraphicForm->ClearGantField();
	if (gantshow)
		GraphicForm->DrawGant(GraphicForm->ScrollBarHorz->Position,GraphicForm->ScrollBarVert->Position);

}
//---------------------------------------------------------------------------
//����������� ������� ���������
void TBaseForm :: CountScale(int Scroller)
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
//---------------------------------------------------------------------------
//������ ��������� ��������
int TBaseForm :: DjonsonAlgorithm()
{
	//StatusBar1->Panels->Items[0]->Text=("�������� �������� ��� ���� �������");
	TimeCycleMethod[MDJ] = Optimizer->DjonsonRun();   //������ ��������� �������-����������
	if (out)
	{
		Output->Lines->Add("����������� ������������������ ������� �������:");
		int *data = Optimizer->OutSequence;
		for (int i=0;i<M;i++)
			Output->Text=Output->Text+IntToStr(data[i])+" ";
	}
	return TimeCycleMethod[MDJ];
}
//---------------------------------------------------------------------------
//������ ������ ������� - ����������
int TBaseForm :: PetrovSokolMethod()
{
	//StatusBar1->Panels->Items[0]->Text=("����� �������-����������");
	TimeCycleMethod[MPS] = Optimizer->PetrovSokolRun();   //������ ��������� �������-����������
	top = new int[N];
	if (OptionsForm->Debug->Checked)
	{
		Output->Lines->Add("������� ����:");
		PrintMatrix(Optimizer->PSBegin[0],3,false,false);
		Output->Lines->Add(" ");

		Output->Lines->Add("���������� �� �������� ������ �����:");
		PrintMatrix(Optimizer->PSBegin[1],N,true,false);
		Output->Lines->Add(" ");

		for (int i=0;i<N;i++)
			top[i]=0;

		Output->Lines->Add("������� 1 ����� ���������:");
		PrintMatrixPS(Optimizer->PSBegin[1],N,0,0);
		Output->Lines->Add(" ");

		Output->Lines->Add("���������� �� ����������� ������ �����:");
		PrintMatrix(Optimizer->PSBegin[2],N,true,false);
		Output->Lines->Add(" ");

		for (int i=0;i<N;i++)
			top[i]=0;

		Output->Lines->Add("������� 2 ����� ���������:");
		PrintMatrixPS(Optimizer->PSBegin[2],N,0,0);
		Output->Lines->Add(" ");

		Output->Lines->Add("���������� �� �������� ��������:");
		PrintMatrix(Optimizer->PSBegin[3],N,true,false);
		Output->Lines->Add(" ");

		for (int i=0;i<N;i++)
			top[i]=0;

		Output->Lines->Add("������� 3 ����� ���������:");
		PrintMatrixPS(Optimizer->PSBegin[3],N,0,0);
		Output->Lines->Add("");
		Output->Lines->Add("");
	}
	if (out)
	{	
		Output->Lines->Add("����������� ������������������ ������� �������: ");
		int *data = Optimizer->OutSequence;
		for (int i=0;i<M;i++)
			Output->Text=Output->Text+IntToStr(data[i])+" ";
	}
	delete [] top;
	return TimeCycleMethod[MPS];
}
//---------------------------------------------------------------------------
//������ ������ ������ � ������ � ����������������� ���
int TBaseForm :: MethodBH (bool Modifycations) //Method  of branches and hordes
{
	int version = 0;
	ProgressText->Visible=true;
	if (Modifycations)
	{
		version = (OptionsForm->MVGModify->ItemIndex + 1);
		TimeCycleMethod[MVGM]=Optimizer->MethodBHRun(version, ProgressText);
		MVGTimeCycle = TimeCycleMethod[MVGM];
		if ( (OptionsForm->MvgMore->Checked) && (TimeCycleMethod[MVGM] > TimeCycleMethod[MVG]) )//���� �������� ��� ���� �������������
		 {
			 //Output->Lines->Add("����");
			 if (version == 1 )
				 version = 3;
			 else
				 version = 1;
			 Output->Lines->Add("��������� ������ � ������ ��������� �������������");
			 //Optimizer->ClearData(MVG);
			 delete Optimizer;
			 Optimizer = new MachineOptimizer;  //��������� ������, ����������� ��� ������. �������� � ���������� OptimizationMtds.h
			//Optimizer->output=!(OptionsForm->NoOut->Checked);  //� ��� ����� � ��� �� ����� ����� ��� 5 �������� ���� ����� �����
			out=!(OptionsForm->NoOut->Checked);
			Optimizer->output=OptionsForm->Debug->Checked;
			Optimizer->debugging=OptionsForm->Debug->Checked;
			 int *T = new int[N];   //�������� �� ������ ������� ������� ������
			 for (int i = 1;i<M+1;i++)
			 {
				  for (int j = 1;j<N+1;j++)
					 T[j-1]=StrToFloat(Table->Cells[j][i]);
				   Optimizer->add(T, N);
			 }
			 delete [] T;
			 TimeCycleMethod[MVGM]=Optimizer->MethodBHRun(version, ProgressText);
		 }
		 else
		 {
			switch (version)
			{
				case 1 : Output->Lines->Add("�������� ����������� ���"); break;
				case 2 : Output->Lines->Add("�������� ����������� ������� ��������� �� ��������� ������"); break;
				case 3 : Output->Lines->Add("�������� ����������� �������  ������� ��� �������� �����������"); break;
				case 4 : Output->Lines->Add("�������� ����������� ��������������� �������"); break;
				case 5 : Output->Lines->Add("�������� ����������� ������� ����������� �� ��������� ������"); break;
			}
		 }
	}
	else //������������ ���
	{
		TimeCycleMethod[MVG] = Optimizer->MethodBHRun(0, ProgressText);
		MVGTimeCycle = TimeCycleMethod[MVG];
	}

	ProgressText->Caption="Ok";
	//����� ������ - ����� �������� �����
	if (out)
	{
		int podric=250;
		for (int i= 1;i<Optimizer->Report->Count;i++)
		{
			Output->Lines->Add(Optimizer->Report->Strings[i]);
			if (i == podric)
				if (Application->MessageBox ("����������?", "����� ������" , MB_YESNO + MB_ICONQUESTION) == IDNO)
				{
					podric=podric*2+50;
					Application->ProcessMessages();
					continue;
				}
				else
					break;

		}
		Application->ProcessMessages();
		Output->Lines->Add("������� �:");
		PrintMatrix(Optimizer->OptimalBH,N,false,false);
		Output->Lines->Add(" ");
		Output->Lines->Add("������� A:");
		PrintMatrix(Optimizer->OptimalBH,N,false,true);
		Output->Lines->Add(" ");
	}
	return MVGTimeCycle;
}
//---------------------------------------------------------------------------
//������ ������ ������
int TBaseForm :: NewMethod()
{
	//StatusBar1->Panels->Items[0]->Text=("����� ����� �������");
	TimeCycleMethod[MNEW] = Optimizer->NewMethodRun();
	return TimeCycleMethod[MNEW];
}
//---------------------------------------------------------------------------
//�������� ������� ������� ����������
void TBaseForm :: ManualTableRefresh(bool full)
{
	if (full)
	{
		ManualTable->RowCount=M+1;
		ManualTable->ColCount=N+1;
		for (int i=1;i<N+1;i++)
			for (int j=1;j<M+1;j++)
			{
				ManualTable->Cells[i][j]=j;
			}
		PsdOut->Caption=IntToStr(ProductionCycle2());
	}

	ManualTable->Cells[0][0]="������:";
	for (int i=1;i<ManualTable->RowCount;i++)
		ManualTable->Cells[0][i]="������ " + IntToStr(i)+":";
	for (int j=1;j<ManualTable->ColCount;j++)
		ManualTable->Cells[j][0]=j;
}
//---------------------------------------------------------------------------
//���������� ������������ ����������������� �����
int TBaseForm :: ProductionCycle2()
{
	float *top = new float[M+1];
	float left=0;
	int det;

	for (int i=1;i<M+1;i++)
	{
		det=StrToInt(ManualTable->Cells[1][i]);
		left+=atof(Table->Cells[1][det].c_str());
		top[det]=left;
	}

	for (int i=2;i<N+1;i++)
	{
		left=0;
		for (int j=1;j<M+1;j++)
		{
			det=StrToInt(ManualTable->Cells[i][j]);	
			top[det]=max(top[det],left);
			top[det]+=atof(Table->Cells[i][det].c_str());
			left = top[det];
		}
	}
	delete [] top;
	return left;
}
//---------------------------------------------------------------------------
//
void TBaseForm :: PrintMatrixPS(const MachineOptimizer::Link *list,int n,int one,int left)
{
	if (list != NULL)   //TODO: ������ ��� �������
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
//---------------------------------------------------------------------------
#endif
