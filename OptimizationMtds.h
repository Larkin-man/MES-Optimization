/*************************************************************\
*	Optimization metods h - library version 3.8		*
*	Aleksey Aponasenko ©							*
*	2023 All Rights Reserved ®						*
*	The author is not responsible for any mistakes,	*
*	found in this program							*
*	or for inapropriate use of it or any of its parts.	*
\*************************************************************/

#ifndef OptimizationMtdsH
#define OptimizationMtdsH
//#define max(A,B) (A>B ? A : B)
#define MDJ 0
#define MPS 1
#define MVG 2
#define MVGM 3
#define MNEW 4
#define METCOUNT 5

class MachineOptimizer
{
public:

	struct Detal	//Деталька!
	{
		int m;		//Номер детали
		int *T;	//Массив длительностей обработки на каждом станке
	};

	struct Link	//Cписок деталей
	{
		Link *next;	//Следующий элемент
		Detal *curr;	//Текущая деталь
		Link *down;	//Вниз по дереву
	}
	*InitBegin,	//Список исходных деталей
	*OptimalDJ,	//Список деталей по Джонсону
	*OptimalPS,	//Список деталей по Петрову-Соколицину (->down)
	*OptimalBH,	//Матрица С для метода ветвей и границ
	*PSBegin[4],   //Начало списка деталей по Петрову-Соколицину
	*OptimalNew;
	int *OutSequence,   //Оптимальная последовательность обработки деталей для Джонсона и ПС
		**OutMatrix;   //Оптимальная последовательность обработки деталей для МВГ
	int StackOfCalls[4]; //Стек запусков методов
	TStrings *Report;	//Отчет содержащий вычисления
	bool output;
	bool debugging;

	MachineOptimizer();
	~MachineOptimizer();
	void add(int time[], int n);  //Добавление ДЕТАЛИ
	void ClearData(int MethodID); //Функция очищает память, отрицательное число - полностью
	int DjonsonRun(); //Запуск алгоритма Джонсона
	int PetrovSokolRun(); //Запуск метода Петрова-Соколицина
	int MethodBHRun (int version = 0, TStaticText *out = NULL); //Method  of branches and hordes
	int GetN() {return N;}
	int NewMethodRun();

protected:

	int
	N,   //Количество станков
	M;   //Количество деталей
	Link
	*InitEnd,	//Конец списка иходных деталей
	*OptimalEnd,   //Конец списка detals по Джонсону
	*PSEnd[4],	//Конец списка detals по Петрову-Соколицину
	*Cend,		//end of OptimalBH matrix
	*Linker,	//Temp
	**Cdos,
	**CdosEnd,	//End of Matrix OptimalBH(do,s)
	*OptimalNewEnd;
	int max;

	Detal* CreateItem (const int &n, const int &M, int *time);
	void CreateLink (Link **Begin, Detal **Item, Link **End, Link **Down = NULL);
	void concatenate(Link *parent, Link *Item);
	void DeleteLinks (Link *Item);
	void DeleteList (Link *Item);
	bool rowind(int *D, int &d);
	int ProductionCycle(Link *Matrix, bool down = false);
	int i, j;
};

MachineOptimizer::MachineOptimizer()
{
	M = 0;
	N = 0;
	InitBegin = NULL;
	InitEnd = NULL;
	OptimalDJ = NULL;
	OptimalEnd = NULL;
	OptimalPS = NULL;
	Linker = NULL;
	OptimalBH = NULL,
	Cend = NULL;
	max = 2000000000;   /* TODO : максимальный должен вычислятся с sizeof */
	//max = ((2<<(sizeof(int)) * 8 - 2))-1;
	output = true;
	debugging = false;
	for (i=0; i<4; i++)
	{
		PSBegin[i] = NULL;
		PSEnd[i] = NULL;
	}
	Report = NULL;
	OutSequence = NULL;
	OutMatrix = NULL;
	OptimalNew = NULL;
	OptimalNewEnd = NULL;
}

void MachineOptimizer::add(int time[], int n)  //Добавление ДЕТАЛИ
{
	N = n;
	M++;
	Detal *Item = CreateItem(n, M, time);
	CreateLink(&InitBegin, &Item, &InitEnd);	//DONE: to issue as function
}

MachineOptimizer::~MachineOptimizer()   //Деструктор - Удаление всех списков
{
	ClearData(-1);
}

void MachineOptimizer::ClearData(int MethodID) //Функция очищает память
{
	/*MDJ 0 MPS 1 MVG 2  MVGM 3 MNEW 4			*/
	if ((MethodID == MDJ ) || (MethodID < 0))	//Алгоритм Джонсона
	{
		if (OptimalDJ != NULL)
			DeleteLinks(OptimalDJ);
		if (OutSequence != NULL)
			delete [] OutSequence;
		OutSequence = NULL;
	}
	if ((MethodID < 0)||(MethodID == MPS ))	//Метод ПС
	{
		for (i = 0;i < 4; i++)
			DeleteList(PSBegin[i]);
		for (i = 0;i < 4; i++)
			if (PSBegin[i] != NULL)
				DeleteLinks(PSBegin[i]);
		if (OutSequence != NULL)
			delete [] OutSequence;
		OutSequence = NULL;
	}
	if ((MethodID < 0)||(MethodID == MNEW ))	//Новый метод
	{
		if (OptimalNew != NULL)
			DeleteLinks(OptimalNew);
		if (OutMatrix != NULL)
			for (i=0; i<M; i++)
				delete [] OutMatrix[i];
	}
	if ((MethodID < 0)||(MethodID == MVG )||(MethodID == MVGM ))  //Метод ВГ и мод
	{
		if (Report != NULL)
			delete Report;
		Report = NULL;
		DeleteList(OptimalBH);   //Испортит входные данные!!! Поэтому нельзя запускать
		MethodID = -1;
		if (OptimalBH != NULL)
			DeleteLinks(OptimalBH);
		if (OutMatrix != NULL)
		{
			for (i=0; i<M; i++)
				delete [] OutMatrix[i];
			delete [] OutMatrix;
		}
		OutMatrix = NULL;
	}

	if ((MethodID < 0)||(MethodID > MNEW )) //Если большое то удаляем входные
	{
		DeleteList(InitBegin);
		if (InitBegin != NULL)
			DeleteLinks(InitBegin);
		M = 0;
		N = 0;
	}
}

MachineOptimizer::Detal *MachineOptimizer::CreateItem (const int &n,const int &M,int *time)
{			//Функция создает новую деталь
	Detal *pItem = new Detal;
	pItem->T = new int[n];
	pItem->m = M;
	if (time == NULL) return pItem;
	for (int i=0; i<n; i++)
	{
		pItem->T[i]=time[i];
	}
	return pItem;
}

void MachineOptimizer::CreateLink (Link **Begin, Detal **Item, Link **End, Link **Down)
{	//Добавляет элемент в конец (End) списка Begin
	Link *pLink = new Link;
	pLink->next = NULL;
	pLink->curr = *Item;
	if (Down == NULL)
		pLink->down = *End;  //Обычный двусвязный список
	else
		pLink->down = *Down; //Дерево
	if (*Begin == NULL)
		*Begin = pLink;  //set the begin of initial list
	else
		(*End)->next = pLink;
	*End = pLink;   //The end is always equal to a new item (Insert in the end of list)
}

void MachineOptimizer::concatenate(Link *parent, Link *Item)  //REMARKABLE!
{			//Функция соединяет два элемента
	if (parent != NULL)
		parent->next = Item;
	if (Item != NULL)
		Item->down = parent;
}

void MachineOptimizer::DeleteList (Link *Item)
{
	if (Item == NULL) return;
	for ( ;Item != NULL; Item = Item->next)
	{
		if (Item->curr != NULL)
		{
			delete [] Item->curr->T;
			Item->curr->T = NULL;
		}
		delete Item->curr;
		Item->curr = NULL;
	}
}

void MachineOptimizer::DeleteLinks (Link *Item)
{			//Функция удаляет список
	if (Item->next != NULL)
	{
		DeleteLinks (Item->next);
	}
	delete Item;
	Item = NULL;
}

bool MachineOptimizer::rowind(int *D, int &d) //проверка отсутствия детали d в списке D
{
	for (int ii = 1; ii<D[0]+2; ii++)
		if (d == D[ii])
			return false; //Деталь есть
		return true;		//Детали нет
}

int MachineOptimizer::ProductionCycle(Link *Matrix, bool downed) //Находит длительность производственного цикла для матрицы В
{
	int *top = new int[N];
	int left;
	for (i=0; i<N; i++)
		top[i] = 0;
	for ( ;Matrix != NULL; Matrix = Matrix->next)
	{
		left = 0;
		for (i=0; i<N; i++)
		{
			top[i] = top[i]>left? top[i] : left;
			if (downed)
				top[i] += Matrix->down->curr->T[i];  //спустившись вниз по дереву
			else
				top[i] += Matrix->curr->T[i];
			left = top[i];
		}
	}
	delete []top;
	return left;
}


int MachineOptimizer::DjonsonRun() //Запуск алгоритма Джонсона
{
	int min[2];
	for (Linker = InitBegin; Linker != NULL; Linker = Linker->next)
		CreateLink(&OptimalDJ, &Linker->curr, &OptimalEnd);
			//DONE: to issue as function!

	Linker = OptimalDJ;		//
	Detal *Item = CreateItem(N, 0, NULL);	//TODO: found them and delete ?
	Link *pLink = new Link;
	pLink->next = NULL;
	pLink->down = NULL;
	pLink->curr = Item;
	OptimalDJ = pLink;	//нельзя с пом createlink из-за этой команды
	Link *minimal[2];
	minimal[0] = NULL;
	minimal[1] = NULL;
	//Linker = InitBegin;
	for (i=0; i < M-1; i++)  //Цикл по всем деталям
	{
		min[0] = Linker->curr->T[0];   // ! minimal = first
		min[1] = Linker->curr->T[N-1];
		minimal[0] = Linker;	//for one
		minimal[1] = Linker;	//for two
		Link *Item1 = Linker;
		while(Item1->next != NULL)  //The cycle searches for the minimal element
		{
			Item1 = Item1->next;
			if (Item1->curr->T[0] < min[0])
			{
				min[0] = Item1->curr->T[0];
				minimal[0] = Item1;
			}
			if (Item1->curr->T[N-1] < min[1])
			{
				min[1] = Item1->curr->T[N-1];
				minimal[1] = Item1;
			}
		}
		if (min[0] <= min[1]) //Собственно ядро алгоритма Джонсона
		{				//Paste in begin
			if (minimal[0] == Linker)
				Linker = Linker->next;
			concatenate(minimal[0]->down, minimal[0]->next);
			concatenate(OptimalDJ->down, minimal[0]);
			concatenate(minimal[0], OptimalDJ);
		}
		else
		{				//Paste in end
			if (minimal[1] == Linker)
				Linker = Linker->next;
			concatenate(minimal[1]->down, minimal[1]->next);
			concatenate(minimal[1], OptimalDJ->next);
			concatenate(OptimalDJ, minimal[1]);
		}
	}
	OptimalDJ->curr->m = Linker->curr->m;
	for (i=0; i<N; i++)
		OptimalDJ->curr->T[i] = Linker->curr->T[i];

	//delete Linker->curr;
	//delete Linker;
	while(OptimalDJ->down != NULL)
		OptimalDJ = OptimalDJ->down;
	OutSequence = new int[M];
	i=0;
	for (Linker = OptimalDJ; Linker!=NULL; Linker=Linker->next)
	{
		OutSequence[i] = Linker->curr->m;
		i++;
	}
	return ProductionCycle(OptimalDJ, false);
}

int MachineOptimizer::PetrovSokolRun() //Запуск метода Петрова-Соколицина
{
	int S[3];
	int TimeCycle = max;
	OutSequence = new int[M];
	for (Linker = InitBegin; Linker != NULL; Linker = Linker->next)
	{		//Формирование матрицы сумм
		S[0] = 0;  //Первый столбец - Сумма кроме первого станка
		S[1] = 0;  //Второй столбец - Сумма кроме последнего станка
		S[2] = 0;  //Третий столбец - Разность первого и второго
		for (i=0; i<N; i++)
		{
			if (i != (N-1))
				S[1] += Linker->curr->T[i];
			if (i != 0)
				S[0] += Linker->curr->T[i];
		}
		S[2] = S[0] - S[1];
		//Создаем четыре одинаковых PSBegin
		for (i=0; i<4; i++)
		{
			Detal *Item = CreateItem(3, Linker->curr->m, S);	//TODO : To remove from cycle!
			CreateLink(&PSBegin[i], &Item, &PSEnd[i], &Linker);
		}
	}

	Link *Temp = new Link;
	for (j = 1; j<4; j++)
	{
		Link *minimal;
		Link *PetrovSokol = PSBegin[j];
		for (i=0; i<M; i++)  //Cycle on all detals
		{
			minimal=PetrovSokol;
			for (Linker = PetrovSokol->next; Linker!=NULL; Linker=Linker->next)
			{
				if (Linker->curr->T[j-1] == minimal->curr->T[j-1])
				{
					//Если минимальных два - предпочтение станку с меньшим номером
					if (Linker->curr->m > minimal->curr->m)
						continue;
				}   //*/

				if (j == 2)
				{
					if ((Linker->curr->T[j-1]) <= (minimal->curr->T[j-1]))
					minimal = Linker;
				}
				else if ((Linker->curr->T[j-1]) >= (minimal->curr->T[j-1]))
					minimal = Linker;
			}

			if (PetrovSokol != minimal)
			{
				//Меняем местами указатели
				//ShowMessage("Меняем: "+IntToStr(minimal->curr->m)+" и "+IntToStr(PetrovSokol->curr->m));
				Temp->curr = minimal->curr;
				Temp->down = minimal->down;
				minimal->curr = PetrovSokol->curr;
				minimal->down = PetrovSokol->down;
				PetrovSokol->curr = Temp->curr;
				PetrovSokol->down = Temp->down;
			}
			PetrovSokol = PetrovSokol->next;
		}
		OutSequence[1] = ProductionCycle(PSBegin[j], true);
		if (OutSequence[1] < TimeCycle)
		{
			TimeCycle = OutSequence[1];
			OutSequence[0] = j;
		}	//OutSequence[0]=j - там номер нужной PSBegin
	}//for j:(1,2,3)
	OptimalPS = PSBegin[OutSequence[0]];
	i = 0;
	for (Linker = PSBegin[OutSequence[0]]; Linker!=NULL; Linker=Linker->next, i++)
		OutSequence[i] = Linker->curr->m;
	delete Temp;
	return TimeCycle;
}

// version: 0 - оригинальный
int MachineOptimizer::MethodBHRun (int version, TStaticText *out) //Method  of branches and hordes
{
	//ShowMessage("version="+IntToStr(version)+" bool1="+IntToStr(idleclean)+" bool1="+IntToStr(idleall));
	if (out != NULL)
			out->Caption=1;
	int
		s,   //Текущий станок
		d,   //Текущая деталь
		o;   //Текущая очередность
	//Создание выходной матрицы
	Report = new TStringList;
	Report->Clear();
	Report->Add("Отчет");
	AnsiString Added;
	OutMatrix = new int *[M];
	for (i=0; i<M; i++)
		OutMatrix[i] = new int[N];
	for(i = 0; i<M; i++)
		for(j = 0; j<N; j++)
			OutMatrix[i][j]=0;	//выходная матрица заполнена нулями

	if (output == false)
		debugging = false;  //NO OUTPUT
	int *D = new int [M+1];  //DONE: Один раз создать
	int *E = new int [M+1];
	int *Fi = new int[M+1];
	Cdos = new Link* [M+1];	//Из кода сюда
	CdosEnd = new Link* [M+1];


	//Создание матрицы С
	for (Linker = InitBegin; Linker!=NULL; Linker=Linker->next)
	{
		// 1) Формирование матрицы С
		Detal *pItem = new Detal;
		pItem->T = new int[N];
		pItem->m=Linker->curr->m;
		int summ=0;
		for (i = 0; i<N; i++)
		{
			summ+=Linker->curr->T[i];  //Сумма по строкам
			pItem->T[i]=summ;
		}
		CreateLink(&OptimalBH,&pItem,&Cend,&Linker);
		//Создает дерево OptimalBH, с down, указывающим на InitBegin
	}

/*S*/for (s = 1; s<N+1; s++)   // 2. Цикл по станкам!
	{
		if (out != NULL)
			out->Caption="Станок: "+IntToStr(s);
		int k = 0;
		if (output)
		{
			Report->Add("Матрица С");
			for (Linker = OptimalBH; Linker!=NULL; Linker=Linker->next)
			{	//Вывести матрицу на экран
				Added+=IntToStr(Linker->curr->m)+"  |  ";
				for (i = 0; i<N; i++)
					Added+=IntToStr(Linker->curr->T[i])+"  ";
				Report->Add(Added);
				Added="";
			}
			Report->Add("");
			Report->Add("Станок № "+IntToStr(s));
		}

/***O***/ for(o = 1; o<M+1; o++)   //для каждой очередности	// 3.
		{
			if (output)
			{
				Report->Add("");
				Report->Add("Очередность: "+IntToStr(o));
			}

			// 4) Проверка конфликта на станке s
			//В D изначально лежат детали из В а в Е из С
			//Для того чтоб не бегать по спискам лишний раз
			for (Linker = OptimalBH; Linker!=NULL; Linker=Linker->next)
			{
				Detal *init = Linker->down->curr;  //Указатель на деталь из списка В
				D[init->m]=init->T[s-1];
				E[init->m]=Linker->curr->T[s-1];
			}

			for (i = 1; i<M; i++) //Поиск конфликтных деталей
			{
				for (j=i+1; j<M+1; j++)
				{
					if ((E[i] > E[j]-abs(D[j])) && (E[j] > E[i]-abs(D[i])))
					{	//Сравниваем каждую с каждой
						if (D[i] > 0)
							D[i]=-D[i];   //Помечаем конфликтные знаком (-)
						if (D[j] > 0)
							D[j]=-D[j];
					}
				}
			}

			D[0]=0;  //Кол-во неконфликтных
			E[0]=0;  //Кол-во конфликтных
			int Dpos=1,Epos=1;
			for (i = 1; i<M+1; i++)	//Отбираем конфликтные
			{
				if (D[i]<0)	//Конфликтная
				{
					E[Epos]=i;
					Epos++;
					E[0]++;
				}
				else		//Неконфликтная
				{
					D[Dpos]=i;
					Dpos++;
					D[0]++;
				}
			}
			if (output)
			{
				Report->Add("Конфликтных: "+IntToStr(E[0]));
				Report->Add("Hеконфликтных: "+IntToStr(D[0]));
			}
			if ((debugging) && (E[0] != 0))
			{
				Added+=("Конфликтуют:");
				for (i = 1; i<E[0]+1; i++)
					Added+=(" "+IntToStr(E[i]));
				Report->Add(Added);
				Added="";
			}

			if (E[0] == 0)
			{
				if (debugging)
					Report->Add("Конфликт разрешился преждевременно!");
				break;   //Это к следующей очередности

			}

			//-----сдесь должен быть отбор блокированых
			//Нужно заблокировать детали, которые уже иду в обработку
			//Создание Сдос
//Cdos = new Link* [E[0]+1];		//Убрал из всех циклов

			for (i = 0; i<E[0]+1; i++)
			{
				Cdos[i] = NULL;
				CdosEnd[i] = NULL;
			}

			//Центральный цикл по конфликтным деталям
/*****D*****/  for (int det = 1; det < E[0]+1; det++)
			{
				d=E[det];
				if (output)
					Report->Add("Деталь № "+IntToStr(d));

				D[D[0]+1]=d;	// 5) Добавить d в D

				// 6) Календарное расписание
				int R=0;
				for (Linker = OptimalBH; Linker!=NULL; Linker=Linker->next)
				{
					if (Linker->curr->m == d)
					{
						R += Linker->curr->T[s-1];  //Найдем С(d,s)
						if (s > 1)
							break;
					}

					if ((s == 1) && (Linker->curr->m == k))
						R -= Linker->curr->T[s-1];  //Найдем С(k,s) //для о != 1

				}
				// minimal->curr->m=-minimal->curr->m; //пометим минимальный (-)
				//output->Lines->Add("minimal="+IntToStr(minimal.next->curr->m));
				//Report->Add("R="+IntToStr(R));
				//Формирование Сдос
				for (Linker = OptimalBH; Linker!=NULL; Linker=Linker->next)
				{
					//output->Lines->Add("Linker "+IntToStr(Linker));
					CreateLink(&Cdos[det],&Linker->curr,&CdosEnd[det],&Linker);
					//Создает дерево Cdos, у которого down -> OptimalBH

					if (rowind(D,Linker->curr->m))
					{   //Если одинаковые данные то не создавать копию
						Detal *pItem = new Detal;
						pItem->T = new int[N];
						pItem->m=Linker->curr->m;
						CdosEnd[det]->curr=pItem;
						for (i=0; i<N; i++)
						{
							if (i < s-1)
								pItem->T[i]=Linker->curr->T[i];
							else
							{
								pItem->T[i]=Linker->curr->T[i]+R;
								if (s>1)
									pItem->T[i]-=Linker->curr->T[s-2];
								if (pItem->T[i] < Linker->curr->T[i])
									pItem->T[i]= Linker->curr->T[i];
							}
						}
					}
				}

				if (output)
				{
					//Report->Add("CDOS");
					for (Linker = Cdos[det];Linker!=NULL;Linker=Linker->next)
					{	//Вывести матрицу на экран
						//output->Lines->Add(IntToStr(Linker->curr->m)+"  |  ");
						for (i = 0; i<N; i++)
							Added+=IntToStr(Linker->curr->T[i])+"  ";
						Report->Add(Added);
						Added="";
					}
				}
				if (debugging)
					Report->Add("R = "+IntToStr(R));

				if (debugging)
				{
					Added="D = { ";
					for (i = 1; i<D[0]+1; i++)
						Added+=IntToStr(D[i])+"  ";
					Report->Add(Added + "}");
					Added="";
					Added="E = { ";
					for (i = 1; i<E[0]+1; i++)
						Added+=IntToStr(E[i])+"  ";
					Report->Add(Added + "}");
					Added="";
					Report->Add("det="+IntToStr(det));
					Report->Add("k="+IntToStr(k));
					//if (rowind(D,det))
					//	Report->Add("rowind(D,det) is TRUE");
					//else
					//	Report->Add("rowind(D,det) is FALSE");
				}
				switch (version)
				{
					case 2: //1 Максимальный на посл станке Мин. время обработки на посл. станке
					//{
					Fi[det]=0;
					for (Linker = Cdos[det];Linker!=NULL;Linker=Linker->next)
					{
						if (Linker->curr->T[N-1] > Fi[det])
						Fi[det] = Linker->curr->T[N-1];
					}
					break;
					//}
					case 3: //2 Как у ПС  Мин. время ожидания поступления
					//{
					Fi[det]=ProductionCycle(Cdos[det]);
					break;
					//}
					case 4: //3 Минимизация предп простоя
					{
					Fi[det]=0;
					int *Duration = new int [N];
					for (Linker = InitBegin; Linker!=NULL; Linker=Linker->next)
					{
						if (Linker->curr->m == E[det])
						{
							for (j=0; j<N; j++)
								Duration[j]=Linker->curr->T[j];
							break;
						}
					}

					for (Linker = InitBegin; Linker!=NULL; Linker=Linker->next)
					{
						if(rowind(D,Linker->curr->m))
						{
							//Детали м нет в Д
							//Report->Add("for "+IntToStr(Linker->curr->m));
							int ts=Duration[s-1];
							int st=Duration[s-1];
							for (j=1; j<N; j++)
							{
								if (st < ts)
									st = ts;
								ts+=Duration[j];
								st+=Linker->curr->T[j-1];

								if (st>ts)
								{
									Fi[det]+=(st-ts);
								}
								//if (debugging)
								//   Report->Add("ts="+IntToStr(ts)+"st="+IntToStr(st)+"fi="+IntToStr(Fi[det]));
							}
						}
					}
					//if ((s == 1)&&(o == 1))
					//{
					//   for (int i=0;i<(N-1);i++)
					//	Fi[det]=Fi[det]+(Duration[i]*(N-i-1));
					//}

					delete []Duration;
					break;
					}
					case 5: //4 ДПЦ Мин. время поступления на посл. станок
					{
					///////////////////////////////

					Fi[det]=0;
					int *top;
					top = new int [N];
					int left=0;
					for (i=0; i<N; i++)
						top[i]=Cdos[det]->curr->T[i];
					for (Linker = Cdos[det]->next; Linker!=NULL; Linker=Linker->next)
					{
						left=0;
						bool netu;
						if (rowind(D, Linker->curr->m))
							{
								if (debugging)
									Report->Add("Детали №"+IntToStr(Linker->curr->m)+" нету в D");
								netu=true;
							}
							else
							{
								if (debugging)
									Report->Add("Деталь №"+IntToStr(Linker->curr->m)+" есть в D");
								netu=false;
							}
						for (i=s-1; i<N; i++)
						{
						top[i]=(top[i]>left)? top[i] : left;
						if (netu)
							netu = false;
						else
							top[i]+=Linker->down->down->curr->T[i];
						left=top[i];
						}
						if (debugging)
						Report->Add("topN="+IntToStr(top[N-1]));
					}
					Fi[det]=top[N-1];
					delete top;

					break;
					}
					default:
					//{ version 0 and 1   Мин. длительность производств. цикла
					// 7) Начнем поиск минимальных и сортировку по предпоследнему станку для нахождения фи
					int T = 0;   // 8) T
					Link *minimal=Cdos[det];		//минимальный = первый
					int min;//=Cdos[det]->curr->T[s-1];  //int min=Cdos[det]->curr->T[N-2];
					for (i=0; i<M; i++)  //Этот цикл для накопления Т
					{
						min=max;
						for (Linker = Cdos[det]; Linker!=NULL; Linker=Linker->next) //Для поиска минимального
						{
							if ((Linker->curr->T[N-2] < min) && (Linker->curr->m >=0))	//(Linker->curr->T[N-2] < min)	(Linker->curr->T[s-1] < min)
						{
							minimal=Linker;
							min=Linker->curr->T[N-2];		//min=Linker->curr->T[N-2];	min=Linker->curr->T[s-1];
							}
						}

						//минимальный найден
						minimal->curr->m=-minimal->curr->m; //пометим минимальный (-)
						//Почему я написал if (T <= minimal->curr->T[s-1])   то  T = minimal->curr->T[s];
						if (T <= minimal->curr->T[N-2])   // 9) Сравниваем Т и С(fq,n-1)   // (T <= minimal->curr->T[N-2])
						T = minimal->curr->T[N-1];							//T = minimal->curr->T[N-1];
						else
						T+=minimal->down->down->curr->T[N-1];				//T+=minimal->down->down->curr->T[N-1];
						//Report->Add("i = "+IntToStr(i)+" T= "+IntToStr(T)+" min m= "+IntToStr(minimal->curr->m));
					}
					Fi[det]=T;   //11
					//}
				} //switch version
				//Fi найден

				for (i=0; i<M; i++)   //по выходной матрице
					if (d == OutMatrix[i][s-1])
					{
						if (debugging)
							Report->Add("Заблокировать деталь "+IntToStr(d)+" в списке она "+IntToStr(det));
						//Fi[det]+=1000;
						Fi[det]=max;
					}
				if (output)
					Report->Add("Fi["+IntToStr(det)+"] = "+IntToStr(Fi[det]));

				for (Linker = Cdos[det]; Linker!=NULL; Linker=Linker->next)  //Уберем минусы
					if (Linker->curr->m < 0)
						Linker->curr->m=-Linker->curr->m;

				// 12) убрать d из D
				D[D[0]+1]=-d;
			}	// 13) закрылся цикл  по деталям
			// 14) Находим минимальное Фи

			k=1;
			for (i = 2; i<E[0]+1; i++)
			{
				if (Fi[i] < Fi[k])
					k = i;
			}
			k=E[k];
			// С = С(ko,s)
			//ShowMessage("Деталь: "+IntToStr(k)+" на станке: "+IntToStr(s)+" будет обрабатыватся: "+IntToStr(o)+" по счету.");
			if (output)
				Report->Add("Деталь №"+IntToStr(k)+" на станке №"+IntToStr(s)+" будет обрабатываться "+IntToStr(o)+"й по счету.");

			OutMatrix[o-1][s-1]=k;

			for (i = 1; i<E[0]+1; i++) //Цикл для удаления Cdos
			{
				for (Linker = Cdos[i]; Linker!=NULL; Linker=Linker->next)
				{
					if (Linker->curr != Linker->down->curr)
					{
						if (E[i] == k)
							//ShowMessage("удален Linker->curr->m:"+IntToStr(Linker->curr->m));
							for (j =0; j<N; j++)
								Linker->down->curr->T[j]=Linker->curr->T[j];
							//Linker->curr->m -=100;
						delete Linker->curr;  //Удаление элемента
						Linker->curr = NULL;
					}
				}
				//delyal there
				DeleteLinks(Cdos[i]);  //Стираниие списка
			}  //Все Cdosы удалены

		} ///Закрылся цикл очередностей
		//Для создания Выходной матрицы
		int max=0;
		for (Linker = OptimalBH; Linker!=NULL; Linker=Linker->next)
		{
			D[Linker->curr->m]=Linker->curr->T[s-1];
			if (D[Linker->curr->m]>max)
				max=D[Linker->curr->m];
		}
		for (i=0; i<M; i++)
			OutMatrix[i][s-1]=i+1;
		for (i=0; i<M; i++)
		{
			D[0] = max+1;
			int min;
			for (j=1; j<M+1; j++)
			{
				if ((D[j]<D[0]) && (D[j]>=0))
				{
					D[0] = D[j];
					min=j;
				}
			}
			//Минимальный найден D[0]
			D[min]=-D[min];
			OutMatrix[i][s-1]=min;
		}
		//Выходная матрица заполнена

		if (debugging)
		{
			Report->Add("Выходная последовательность обработки деталей");
			for (i=0; i<M; i++)
			{
				Added=IntToStr(i+1)+") ";
				for (j=0; j<N; j++)
				{
					Added+=IntToStr(OutMatrix[i][j])+"  ";
				}
				Report->Add(Added);
			}
			Added="";
		}

	} //Закрылся цикл по станкам
	//Алгоритм ищет ненужный простой между каждыми двумя деталями в очереди
	//И убирает его
	if ( version > 0 )
	{
		for (s = 2; s<N+1; s++)   // 2. Цикл по станкам!
		{
			int z; //z - Время окончания обработки предыдущей детали
			Link *minimal=OptimalBH;		//минимальный = первый
			int min;//=Cdos[det]->curr->T[s-1];  //int min=Cdos[det]->curr->T[N-2];

			for (i=0; i<M; i++)
			{	//
				min=max;
				for (Linker = OptimalBH; Linker!=NULL; Linker=Linker->next) //Для поиска минимального
				{
					//Report->Add("curr="+IntToStr(Linker->curr->T[s-1]));
					if ((Linker->curr->T[s-1] < min) && (Linker->curr->m >=0))
					{
						minimal=Linker;
						min=Linker->curr->T[s-1];
					}	//Цикл находит минимальнуую длит. обработки среди всех деталей на станке s-1

				}
				//минимальный найден
				Added+=IntToStr(minimal->curr->m)+"  ";
				minimal->curr->m=-minimal->curr->m; //пометим минимальный (-)
				//Почему я написал if (T <= minimal->curr->T[s-1])	то  T = minimal->curr->T[s];
				if (i==0)
				{
					z=minimal->curr->T[s-1];
				}
				else
				{
					int A = (minimal->curr->T[s-1])-(minimal->down->curr->T[s-1]);
					//А - время начала обработки следующей детали

					if (A != z)
					{
						if(A != (minimal->curr->T[s-2]))
						{
							minimal->curr->T[s-1] = (z > (minimal->curr->T[s-2]))? z : (minimal->curr->T[s-2]);
							(minimal->curr->T[s-1])+=(minimal->down->curr->T[s-1]);
							if (debugging)
								Report->Add("Убран простой детали "+IntToStr(-minimal->curr->m));
						}
					}
					z = minimal->curr->T[s-1];
				}
				//Грубо говоря, между z и А если есть простой, он будет уничтожен

			} //Закончился цикл по всем деталям

			for (Linker = OptimalBH; Linker!=NULL; Linker=Linker->next)  //Уберем минусы
				if (Linker->curr->m < 0)
					Linker->curr->m=-Linker->curr->m;
			if (debugging)
			{
				Report->Add("Отсортированные детали в OptimalBH");
				Report->Add(Added);
			}
			Added="";
		}
	} //Закончилась обработка простоев на текущем станке

	//d=ProductionCycle(OptimalBH,output);
	//Расчет длительности производственного цикла
	int TimeCycle=OptimalBH->curr->T[N-1];
	for (Linker = OptimalBH->next; Linker!=NULL; Linker=Linker->next)
		if (Linker->curr->T[N-1]>TimeCycle)
			TimeCycle=Linker->curr->T[N-1];
	if (output)
		Report->Add("Длительность="+IntToStr(TimeCycle));
	//Удаление переменных
	delete [] D;
	delete [] E;
	delete [] Fi;
	//for (i = 0; i<M+1; i++)	{	//DeleteLinks(Cdos[i]);	}
	delete [] CdosEnd;
	return TimeCycle;
}

int MachineOptimizer::NewMethodRun()
{
	//Создание выходной матрицы
	Report = new TStringList;
	Report->Clear();
	Report->Add("Отчет");
	AnsiString Added;
	//Report->Strings[0].SetLength(80);
	OutMatrix = new int *[M];
	for (i=0; i<M; i++)
		OutMatrix[i] = new int[N];
	for(i = 0; i<M; i++)
		for(j = 0; j<N; j++)
			OutMatrix[i][j]=0;
	int *Operative = new int[M+1];
	for (i=0; i<M+1; i++)
		Operative[i] = 0;

	for (Linker = InitBegin; Linker!=NULL; Linker=Linker->next)   //Создание копии списка
		CreateLink(&OptimalNew, &Linker->curr, &OptimalNewEnd);


	int max = 0;
	for (Linker = InitBegin; Linker!=NULL; Linker=Linker->next) //Для поиска минимального
	{
		for (i=0; i<N-1; i++)
			Operative[Linker->curr->m] += (Linker->curr->T[i] * (N-i-1));
		if (max < Operative[Linker->curr->m])
			max = Operative[Linker->curr->m];
	}
	int min = 1;
	int max2 = max;


	Link* Linker2 = NULL;
	for (Linker = OptimalNew; Linker!=NULL; Linker=Linker->next)
	//Цикл для упорядочивания по возрастанию
	{
		max2 = max + 1;
		for (i=1; i<M+1; i++) //Цикл найдет минимальный элемент
		{
			if ((Operative[i] < max2)&&(Operative[i] >= 0))
			{
				max2 = Operative[i];
				min = i;	/* TODO 1 : Нужно обязательно предусмотреть одинаковые */
			}
		}   //i - номер детали с минимальным Operative

		Operative[min] *= (-1);
		for (Linker2 = InitBegin; Linker2!=NULL; Linker2=Linker2->next)
		{
			if (Linker2->curr->m == min)
			{
				Linker->curr = Linker2->curr;
				break;
			}
		}
	}
	delete Operative;
	Operative = NULL;
	return ProductionCycle(OptimalNew);
}

#endif
