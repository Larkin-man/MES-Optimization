//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EnterData.h"
//---------------------------------------------------------------------------
#include "MainSource.h"
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TEnterDataForm *EnterDataForm;
//---------------------------------------------------------------------------
__fastcall TEnterDataForm::TEnterDataForm(TComponent* Owner) : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//ÏÎÊÀÇÀÒÜ ÔÎÐÌÓ
void __fastcall TEnterDataForm::FormShow(TObject *Sender)
{	Field1->SetFocus();	 }
//---------------------------------------------------------------------------
//Ïðîâåðêà ââåäåííûõ ñèìâîëîâ â ïîëÿ 1 è 2
void __fastcall TEnterDataForm::Field1Exit(TObject *Sender)
{	CheckConvert((TLabeledEdit*)Sender);	}
void __fastcall TEnterDataForm::Field2Exit(TObject *Sender)
{	CheckConvert((TLabeledEdit*)Sender);	}
//---------------------------------------------------------------------------
//Çàêðûòü ôîðìó
void __fastcall TEnterDataForm::BitBtnCancelClick(TObject *Sender)
{	Close();	}
//---------------------------------------------------------------------------
//Ïðîâåðêà îòñóòñòâèÿ ñèìâîëîâ â ïîëÿõ 1 è 2
void __fastcall TEnterDataForm::Field1Change(TObject *Sender)
{	if (Result == random)
		BitBtnOk->Enabled=!((Field1->Text=="") && (Field2->Text==""));
}
void __fastcall TEnterDataForm::Field2Change(TObject *Sender)
{	if (Result == random)
		BitBtnOk->Enabled=!((Field1->Text=="") && (Field2->Text==""));
}
//---------------------------------------------------------------------------
//Êíîïêà ÎÊ
void __fastcall TEnterDataForm::BitBtnOkClick(TObject *Sender)
{
//ÈÇÌÅÍÅÍÈÅ ÐÀÇÌÅÐÀ ÒÀÁËÈÖÛ
if (Result == resize)
{
	if (Field1->Text.operator!=(""))
		BaseForm->Table->RowCount=(StrToInt(EnterDataForm->Field1->Text)+1);
	if (Field2->Text != "")
		BaseForm->Table->ColCount=StrToInt(EnterDataForm->Field2->Text)+1;
	BaseForm->TableRefresh();
	bool NMchange=false;
	if ((BaseForm->Table->RowCount-1) < (BaseForm->M))
	{
		BaseForm->M = BaseForm->Table->RowCount-1;
		NMchange=true;
	}
	if ((BaseForm->Table->ColCount-1) < (BaseForm->N))
	{
		BaseForm->N = BaseForm->Table->ColCount-1;
		NMchange=true;
	}
	if (NMchange)
		BaseForm->Swapf();
	Close();
}

//ÇÀÏÎËÍÅÍÈÅ ÑËÓ×ÀÉÍÛÌÈ ×ÈÑËÀÌÈ
if (Result == random)
{
	CheckConvert(Field1);
	CheckConvert(Field2);
	if ((Field1->Text=="") && (Field2->Text==""))
		return;
	for (int i=1;i<BaseForm->Table->RowCount;i++)
		for (int j=1;j<BaseForm->Table->ColCount;j++)
			BaseForm->Table->Cells[j][i]="";

	if (Field1->Text != "")
		BaseForm->M=StrToInt(EnterDataForm->Field1->Text);
	if (Field2->Text != "")
		BaseForm->N=StrToInt(EnterDataForm->Field2->Text);

	if (BaseForm->Table->RowCount < BaseForm->M+1)
		BaseForm->Table->RowCount = BaseForm->M+1;
	if (BaseForm->Table->ColCount < BaseForm->N+1)
		BaseForm->Table->ColCount = BaseForm->N+1;
	BaseForm->TableRefresh();
	srand(time(NULL));
	int max=OptionsForm->RandomTo->Value;
	int min=OptionsForm->RandomFrom->Value;
	if (OptionsForm->NoMiddle->Checked)
	{
		int Mid = (min + max) / 2;
		int Count = max - min + 1;
		int Size = Count / 5;
		int Add = Count / 3;
		int MidPsize = Mid + Size;
		int MidDsize = Mid - Size;
		int Rand;
		for (int i = 1; i < BaseForm->M+1; i++)
		for (int j = 1; j < BaseForm->N+1; j++)
		{
			Rand = rand() % (max-min+1) + min;  //From min to max
			if ( (Rand < Mid)&&(Rand > MidDsize) )
				Rand -= Add;
			else if ( (Rand < MidPsize) && (Rand > Mid ) )
				Rand += Add;
			else if (Rand == Mid)
				Rand = min;
			BaseForm->Table->Cells[j][i] = Rand;
		}
	}
	else
	{
		for (int i = 1; i < BaseForm->M+1; i++)
		for (int j = 1; j < BaseForm->N+1; j++)
			BaseForm->Table->Cells[j][i] = rand() % (max-min+1) + min;  //From min to max
	 }
	BaseForm->StatusBar1->Panels->Items[0]->Text=("Çàïîëíåíî ñëó÷àéíûìè ÷èñëàìè");
	BaseForm->Swapf();
	BaseForm->Output->Lines->Add("Çàïîëíåíî ñëó÷àéíûìè ÷èñëàìè. Ñòàíêîâ: "+IntToStr(BaseForm->N)+" Äåòàëåé: "+IntToStr(BaseForm->M));
	BaseForm->Output->Lines->Add("Äëèòåëüíîñòü ïðîèçâîäñòâåííîãî öèêëà: "+IntToStr(BaseForm->CurrentCycle));
	for (int i=0; i<METCOUNT; i++)
		BaseForm->TimeCycleMethod[i] = 0;
	BaseForm->Report->Enabled = false;
	Close();
}

//ÓÑÒÀÍÎÂÈÒÜ ÖÂÅÒ ÄÅÒÀËÈ
if (Result == color)
{
	CheckConvert(Field1);
	if (Field1->Text=="")
		return;
	int det = StrToInt(Field1->Text);
	if (det <= BaseForm->ColorSave)
	{
		BaseForm->ColorBox[det-1]=Field2->Color;
		BaseForm->PaintGant();
	}
	Field2->Color=clWindow;
	Field2->Cursor=crDefault;
	Close();
}
}
//---------------------------------------------------------------------------
//Âûáîð öâåòà
void __fastcall TEnterDataForm::Field2Click(TObject *Sender)
{
	if (Result == color)
	{
		Field2->OnExit(NULL);
		ColorDialog1->Execute();
		Field2->Color=ColorDialog1->Color;
		Field2->Text="";
		Field1->SetFocus();
	}
}
//---------------------------------------------------------------------------

