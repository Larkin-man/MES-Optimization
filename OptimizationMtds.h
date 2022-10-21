/*************************************************************\
*      Optimization metods h - library version 3.0            *
*      Aleksey Aponasenko ©                                   *
*      2012 All Rights Reserved ®                             *
*      The author is not responsible for any mistakes,        *
*      found in this program                                  *
*      or for inapropriate use of it or any of its parts.     *
\*************************************************************/

#ifndef OptimizationMtdsH
#define OptimizationMtdsH

class MachineOptimizer
{
public:

MachineOptimizer()
{
     M=0;
     N=100; //max
     InitBegin=NULL;
     InitEnd=NULL;
     Optimal=NULL;
     OptimalEnd=NULL;
     Linker=NULL;
     C=NULL,
     Cend=NULL;

     for (int i=0;i<4;i++)
          {
               PSBegin[i]=NULL;
               PSEnd[i]=NULL;
          }
}

     struct Node    //Деталь
     {
     int m;         //Номер детали
     int *T;        //Массив длительностей обработки деталей
     };

     struct Link    //Cписок деталей
     {
     Link *next;    //Следующий элемент
     Node *curr;    //Текущая деталь
     Link *down;    //Вниз по дереву
     }
     *InitBegin,    //Начало списка иходных деталей
     *Optimal,      //Начало списка деталей по Джонсону
     *PSBegin[4],   //Начало списка деталей по Петрову-Соколицину
     *C,            //Матрица С для метода ветвей и границ
     **Cdos;        //Arari asimpaspari parire pararu parrapupa ta ta ta ua

~MachineOptimizer()
{
     //ShowMessage("Деструктор запущен");
     //Удаление всех списков
     DeleteList(InitBegin);
     for (int i = 0;i < 4; i++)
          DeleteList(PSBegin[i]);

     for (int i = 0;i < 4; i++)
          if (PSBegin[i] != NULL)
               DeleteLinks(PSBegin[i]);
     if (Optimal != NULL)
          DeleteLinks(Optimal);

     if (InitBegin != NULL)
          DeleteLinks(InitBegin);
     //for (int i = 0;i < M+1; i++)
     //     if (Cdos[i] != NULL)
     //          DeleteLinks(Cdos[i]);

     //ShowMessage("Данные удалены!");
}

void add(int n,int *time)  //Добавление ДЕТАЛИ
{
     if (n<N)
          N=n;
     M++;
     Node *Item = CreateItem(n,M,time);
     //InitEnd = CreateLink(InitBegin,Item,InitEnd);
     Link *pLink = new Link;       //TODO: to issue as function
     pLink->next=NULL;
     pLink->curr=Item;
     pLink->down=InitEnd;
     if (InitBegin == NULL)
          InitBegin = pLink;  //set the begin of initial list
     else
          InitEnd->next=pLink;
     InitEnd = pLink;         //The end is always equal to a new item (Insert in the end of list)
          //pLink->down->next=pLink;       */
}

void DjonsonRun()      //For two machines  Fortune havor!
{
     for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next) 
     {                                    //TODO: to issue as function!
          Link *pLink = new Link;
          pLink->next=NULL;
          pLink->curr=Linker->curr;  //But not to copy of NODE ! only Link
          pLink->down=OptimalEnd;     
          if (Optimal == NULL)
               Optimal = pLink;  //set the begin of initial list
          else
              OptimalEnd->next=pLink;
          OptimalEnd = pLink;
     }

     //CreateLink(InitBegin,Linker->curr,InitEnd);
     Linker = Optimal;          //
     Node *Item = CreateItem(2,0,NULL);    //TODO: found them and delete ?
     Link *pLink = new Link;
     pLink->next=NULL;
     pLink->down=NULL;                     
     pLink->curr=Item;
     Optimal=pLink;
     Link *minimal[2];
     minimal[0]=NULL;
     minimal[1]=NULL;
     //Link *Linker = InitBegin;
     for (int i=0;i<M-1;i++)  //Цикл по всем станкам
     {
          min[0]=Linker->curr->T[0];   // ! minimal = first
          min[1]=Linker->curr->T[1];
          minimal[0]=Linker;       //for one
          minimal[1]=Linker;       //for two
          Link *Item1=Linker;
          while(Item1->next != NULL)  //The cycle searches for the minimal element
          {
               Item1 = Item1->next;
               if (Item1->curr->T[0]<min[0])
               {
                    min[0]=Item1->curr->T[0];
                    minimal[0]=Item1;
               }
               if (Item1->curr->T[1]<min[1])
               {
                    min[1]=Item1->curr->T[1];
                    minimal[1]=Item1;
               }
          }


          if (min[0]<=min[1]) //Собственно ядро алгоритма Джонсона
          {                   //Paste in begin
               if (minimal[0]==Linker)
                    Linker=Linker->next;
               concatenate(minimal[0]->down,minimal[0]->next);
               concatenate(Optimal->down,minimal[0]);
               concatenate(minimal[0],Optimal);
          }
          else
          {                   //Paste in end
               if (minimal[1]==Linker)
                    Linker=Linker->next;
               concatenate(minimal[1]->down,minimal[1]->next);
               concatenate(minimal[1],Optimal->next);
               concatenate(Optimal,minimal[1]);
          }
     }
     Optimal->curr->T[0]=Linker->curr->T[0];
     Optimal->curr->T[1]=Linker->curr->T[1];
     Optimal->curr->m=Linker->curr->m;
     //delete Linker->curr;
     //delete Linker;
     while(Optimal->down != NULL)
          Optimal=Optimal->down;
}

void PetrovSokolRun()
{
     int S[3];
     for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next)
     {             //Формирование матрицы сумм
          S[0]=0;  //Первый столбец - Сумма кроме последнего станка
          S[1]=0;  //Второй столбец - Сумма кроме первого станка
          S[2]=0;  //Третий столбец - Разность второго и первого
          for (int i=0;i<N;i++)
          {
               if (i!=(N-1))
                    S[0]+=Linker->curr->T[i];
               if (i!=0)
                    S[1]+=Linker->curr->T[i];
          }
          S[2]=S[1]-S[0];
          for (int i=0;i<4;i++)
          {
               Node *Item = CreateItem(3,Linker->curr->m,S);     //TODO : To remove from cycle!
               Link *pLink = new Link;       //TODO: to issue as function
               pLink->next=NULL;
               pLink->curr=Item;
               pLink->down=Linker;  //
               if (PSBegin[i] == NULL)
                    PSBegin[i] = pLink;  //set the begin of initial list
               else
                    PSEnd[i]->next=pLink;
               PSEnd[i] = pLink;         //The end is always equal to a new item (Insert in the end of list)
          }
     }

     Link *Temp = new Link;
     for (int j = 1;j<4;j++)
     {
          Link *minimal;
          Link *PetrovSokol = PSBegin[j];
          for (int i=0;i<M;i++)  //Cycle on all detals
          {
               minimal=PetrovSokol;
               for (Linker = PetrovSokol->next;Linker!=NULL;Linker=Linker->next)
               {
                    if (Linker->curr->T[j-1] == minimal->curr->T[j-1])
                    {
                         //Если минимальных два - предпочтение станку с меньшим номером
                         if (Linker->curr->m > minimal->curr->m)
                              continue;
                    }   //*/

                    if (YANISH(Linker->curr->T[j-1],minimal->curr->T[j-1],j))
                    {
                              minimal=Linker;
                    }
               }

               if (PetrovSokol != minimal)
               {
                    //Меняем местами указатели
                    //ShowMessage("Меняем: "+IntToStr(minimal->curr->T[0])+" и "+IntToStr(PetrovSokol->curr->T[0]));
                    Temp->curr=minimal->curr;
                    Temp->down=minimal->down;
                    minimal->curr=PetrovSokol->curr;
                    minimal->down=PetrovSokol->down;
                    PetrovSokol->curr=Temp->curr;
                    PetrovSokol->down=Temp->down;
               }

               PetrovSokol=PetrovSokol->next;
          }
     }//for j
     delete Temp;
}

void MethodBHRun (TMemo *output = NULL) //Method  of branches and hordes
{
     int
          s,   //Текущий станок
          d,   //Текущая деталь
          o;   //Текущая очередность
     for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next)
     {
          Link *pLink = new Link;
          pLink->next=NULL;
          // 1) Формирование матрицы С
          Node *pItem = new Node;
          pItem->T = new int[N];
          pItem->m=Linker->curr->m;
          int summ=0;
          for (int i = 0 ;i<N;i++)
          {
               summ+=Linker->curr->T[i];
               pItem->T[i]=summ;
          }
          pLink->curr=pItem;
          pLink->down=Linker; //pLink->down=Cend;
          if (C == NULL)
               C = pLink;
          else
              Cend->next=pLink;
          Cend = pLink;
     }
     s=1; // 2.
     o=1; // 3.
     // 4) Проверка конфликта на станке s
     int *D = new int [M+1];
     int *E = new int [M+1];

     for (Linker = C;Linker!=NULL;Linker=Linker->next)
     {
          Node *init = Linker->down->curr;  //Указатель на деталь из списка В
          D[init->m]=init->T[s-1];
          E[init->m]=Linker->curr->T[s-1];
     }

     for (int i = 1;i<M;i++) //Поиск конфликтных деталей
     {
          //if (D[i]<0) continue;  //возможно
          for (int j=i+1;j<M+1;j++)
          {
               if ((E[i] > E[j]-abs(D[j])) && (E[j] > E[i]-abs(D[i])))
               {    //Сравниваем каждую с каждой
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
     for (int i = 1;i<M+1;i++)      //Отбираем конфликтные
     {
          if (D[i]<0)
          {
               E[Epos]=i;
               Epos++;
               E[0]++;    
          }
          else
          {
               D[Dpos]=i;
               Dpos++;
               D[0]++;
          }
     }
     output->Lines->Add("Конфликтных: "+IntToStr(E[0]));
     output->Lines->Add("Hеконфликтных: "+IntToStr(D[0]));

     Cdos = new Link* [E[0]+1];
     CdosEnd = new Link* [E[0]+1];
     int *Fi = new int[M+1];
     int k = 0;
     //*Cdos = new Link [E[0]];
     for (int i = 0;i<E[0]+1;i++)
     {
          Cdos[i] = NULL;
          CdosEnd[i] = NULL;
     }

  for (int det = 1;det < E[0]+1;det++)
  {
     d=E[det];
     //--------------------------//

     D[D[0]+1]=d;      // 5) Добавить d в D

     // 6) Календарное расписание
     int Cds=0,R;
     int max=0;
     for (Linker = C;Linker!=NULL;Linker=Linker->next)
     {
          if (Linker->curr->m == d)
               Cds += Linker->curr->T[s-1];  //Найдем С(d,s)
          if (Linker->curr->m == k)
               Cds -= Linker->curr->T[s-1];  //Найдем С(k,s) //для о != 1
         /* if (Linker->curr->T[N-2] < min)                  //Заодно найдем минимальный
          {
               min = Linker->curr->T[N-2]; //это не надо
               minimal=Linker;
          }                            */
          max+=Linker->curr->T[N-2];
     }
    // minimal->curr->m=-minimal->curr->m; //пометим минимальный (-)
     //output->Lines->Add("minimal="+IntToStr(minimal.next->curr->m));

     if (s == 1)
          R = Cds;

     output->Lines->Add("Cds="+IntToStr(Cds));
     output->Lines->Add("R="+IntToStr(R));
     output->Lines->Add("d="+IntToStr(d));
     output->Lines->Add("s="+IntToStr(s));

     for (Linker = C;Linker!=NULL;Linker=Linker->next)
     {
          //output->Lines->Add("Linker "+IntToStr(Linker));
          Link *pLink = new Link;
          pLink->next=NULL;
          pLink->down=Linker;
          pLink->curr=Linker->curr;
          if (rowind(D,Linker->curr->m,output))
          {
               Node *pItem = new Node;
               pItem->T = new int[N];
               pItem->m=Linker->curr->m;
               pLink->curr=pItem;
               for (int i=0;i<N;i++)
               {
                    if (i < s-1)
                         pItem->T[i]=Linker->curr->T[i];
                    else
                         pItem->T[i]=Linker->curr->T[i]+R;
               }                
          }
          if (Cdos[d] == NULL)
               Cdos[d] = pLink;
          else
              CdosEnd[d]->next=pLink;
          CdosEnd[d] = pLink;     //*/
     }

     // 7) Начнем поиск минимальных и сортировку по предпоследнему станку для нахождения фи
     int T = 0;   // 8) T
     Link *minimal=Cdos[d];          //минимальный = первый
     int min=Cdos[d]->curr->T[N-2];
     for (int i=0;i<M;i++)
     {
          min=max;         
          for (Linker = Cdos[d];Linker!=NULL;Linker=Linker->next)
          {
               if ((Linker->curr->T[N-2] < min) && (Linker->curr->m >=0))
               {
                    minimal=Linker;
                    min=Linker->curr->T[N-2];

               }
          }
          //минимальный найден
          minimal->curr->m=-minimal->curr->m; //пометим минимальный (-)
          //output->Lines->Add("Заход "+IntToStr(i)+": "+IntToStr(min));
          if (T <= minimal->curr->T[N-2])   // 9) Сравниваем Т и С(fq,n)
               T = minimal->curr->T[N-1];
          else
               T+=minimal->down->down->curr->T[N-1];
     }
     Fi[d]=T;   //11
     output->Lines->Add("FI="+IntToStr(Fi[d]));
     for (Linker = Cdos[d];Linker!=NULL;Linker=Linker->next)  //Уберем минусы
          Linker->curr->m=-Linker->curr->m;

     // 12) убрать d из D
     D[D[0]+1]=-d;
  }      // 13) повторяем для следующей d
     // 14) Находим минимальное Фи
     k=1;
     for (int i = 2;i<M+1;i++)
          if (Fi[i] < Fi[k])
               k = i;
     // С = С(ko,s)
     ShowMessage("Деталь: "+IntToStr(k)+" на станке: "+IntToStr(s)+" будет обрабатыватся: "+IntToStr(o)+" по счету.");
     for (int i = 1;i<E[0]+1;i++)
     {
          for (Linker = Cdos[i];Linker!=NULL;Linker=Linker->next)
          {
                    if (Linker->curr != Linker->down->curr)
                    {
                         if (i == k)
                         //ShowMessage("удален Linker->curr->m:"+IntToStr(Linker->curr->m));
                              for (int i =0;i<N;i++)
                                   Linker->down->curr->T[i]=Linker->curr->T[i];
                         delete Linker->curr;
                    }
          }
          DeleteLinks(Cdos[i]);
     }



     // delete D;
     //  delete E;

}

protected:

     int
     N,   //Количество станков
     M;   //Количество деталей
     int min[2];
     Link           //TODO: надо чета делать с этими концами
     *InitEnd,      //Конец списка иходных деталей
     *OptimalEnd,   //Конец списка detals по Джонсону
     *PSEnd[4],     //Конец списка detals по Петрову-Соколицину
     *Cend,         //end of C matrix
     *Linker,       //Temp
     **CdosEnd;     //End of Matrix C(do,s)
 
//Node *CreateItem (int,int,int *time =NULL);

Node *CreateItem (int n,int M,int *time)
{                //Функция создает новый элемент
     Node *pItem = new Node;
     pItem->T = new int[n];
     pItem->m=M;
     if (time == NULL) return pItem;
     for (int i=0;i<n;i++)
     {
          pItem->T[i]=time[i];
     }
     return pItem;
}

Link *CreateLink (Link *Begin, Node *Item, Link *End)
{
     Link *pLink = new Link;
     pLink->next=NULL; //ok
     pLink->curr=Item;
     pLink->down=End;
     if (Begin == NULL)
          Begin = pLink;  //set the begin of initial list
     else
          return End;    //Ниполучается у Меня хоть тресни работать с указателем на указатель
     return NULL;
}


void concatenate(Link *parent, Link *Item)  //REMARKABLE!
{              //Функция соединяет два элемента
     if (parent != NULL)
          parent->next=Item;
     if (Item!=NULL)
          Item->down=parent;
}

bool YANISH(int linker, int min,int J)
{              //Функция сравнивает два числа - нужна для сортировки по ПС
     if (J == 1)
     {
          return linker <= min;  //Sorting according increase
     }
     return linker >= min;       //Sorting according decrease
}

void DeleteLinks (Link *Item)
{               //Функция удаляет список
   if (Item->next != NULL)
   {
      DeleteLinks (Item->next);
   }
   delete Item;
}
void DeleteList (Link *Item)
{
     if (Item == NULL) return;
     for (;Item!=NULL;Item=Item->next)
          delete Item->curr;
}

bool rowind(int *D, int d,TMemo *out) //проверка наличия детали d в списке D
{
     //out->Lines->Add("d="+IntToStr(d));
     //out->Lines->Add("Massiv D");
     //for (int i=0;i<M+1;i++)
     //          out->Lines->Add(IntToStr(D[i]));
     for (int i = 1;i<D[0]+2;i++)
          if (d == D[i])
               return false;
          //ShowMessage("true");
          return true;

}

};
#endif
