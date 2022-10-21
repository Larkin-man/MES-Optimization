
#ifndef OptimizationMtdsH
#define OptimizationMtdsH

class MachineOptimizer
{
public:
     MachineOptimizer()
     {
     N=0;
     Record=NULL;
     Optimal=NULL;
     InitBegin=NULL;
     InitEnd=NULL;
     DJBegin=NULL;
     DJEnd=NULL;
     Linker=NULL;
     }

     struct Node    //Cписок деталей
     {
     int n;         //Номер детали
     double A;      //Длительность обработки на первом станке
     double B;      //Длительность обработки на втором станке
     double *T;     //Массив длительностей обработки деталей
     //Node *Next;    //Следующая деталь
     //Node *Prev;    //Предыдущая деталь
     //Node *nextDj;  //Следующая деталь по Джонсону
     //Node *prevDj;  //Предыдущая деталь по Джонсону
     }
     *Record,       //Исходный список
     *Optimal,      //Список по Джонсону
     *NotOptimal,
     *End,          //Конец списка
     *EndDj;        //Конец списка по Джонсону


     struct Link
     {
     Link *next;
     Node *curr;
     Link *prev;
     }
     *InitBegin,    //Начало списка иходных деталей
     *InitEnd,      //Конец списка иходных деталей
     *DJBegin,      //Начало списка деталей по Джонсону
     *DJEnd,        //Конец списка detals по Джонсону
     *Linker,       //Temp
     *minimal[2];   //Минимальный на первом станке 0, на втором 1


     void add(int m,double *time)  //Добавление станка
     {
          M=m;
          N++;
          Node *pItem = new Node;
          pItem->T = new double[m];
          for (int i=0;i<m;i++)
          {
          pItem->T[i]=time[i];
          }
          pItem->n=N;
          pItem->A=time[0];
          pItem->B=time[1];
          //pItem->Next=NULL;
          //pItem->Prev=NULL;
          //Node *Item = PushBack(Record,pItem);
          //Node *Itemn = PushBack(NotOptimal,pItem);
          //if(Record == NULL)
          //     Record=Item;
          //if (NotOptimal == NULL)
            //   NotOptimal=Itemn;

          //По новому образу
          Link *pLink = new Link;
          pLink->next=NULL; //ok
          pLink->curr=pItem;
          pLink->prev=InitEnd;
          if (InitBegin == NULL)
               InitBegin = pLink;  //set the begin of initial list
          else
              InitEnd->next=pLink;
          InitEnd = pLink;         //The end is always equal to a new item (Insert in the end of list)
          //pLink->prev->next=pLink;

     }


 void DjonsonRun()
{
     Linker = InitBegin;

     Node *pItem = new Node;   //ecaeae create item
     pItem->A=0;
     pItem->B=0;
     pItem->n=0;
     //pItem->Next=NULL;
     //pItem->Prev=NULL;
     Optimal=pItem;
     Link *pLink = new Link;
     pLink->next=NULL;
     pLink->prev=NULL;
     pLink->curr=pItem;
     DJBegin=pLink;

     Link *LinkRun = InitBegin;
     for (int i=0;i<N-1;i++)
     {
          min[0]=LinkRun->curr->A;
          min[1]=LinkRun->curr->B;
          minimal[0]=LinkRun;
          minimal[1]=LinkRun;
          Link *Item1=LinkRun;
          while(Item1->next != NULL)  //Oeee euao ieieiaeuiua yeaiaiou
          {
               Item1 = Item1->next;
               if (Item1->curr->A<min[0])
               {
                    min[0]=Item1->curr->A;
                    minimal[0]=Item1;
               }
               if (Item1->curr->B<min[1])
               {
                    min[1]=Item1->curr->B;
                    minimal[1]=Item1;
               }
          }


          if (min[0]<=min[1]) //Nianoaaiii ya?i aeai?eoia A?iiniia
          {
               if (minimal[0]==LinkRun)
                    LinkRun=LinkRun->next;
               concatenate(minimal[0]->prev,minimal[0]->next);
               concatenate(DJBegin->prev,minimal[0]);
               concatenate(minimal[0],DJBegin);
          }
          else
          {
               if (minimal[1]==LinkRun)
                    LinkRun=LinkRun->next;
               concatenate(minimal[1]->prev,minimal[1]->next);
               concatenate(minimal[1],DJBegin->next);
               concatenate(DJBegin,minimal[1]);
          }

     }
     DJBegin->curr->A=LinkRun->curr->A;
     DJBegin->curr->B=LinkRun->curr->B;
     DJBegin->curr->n=LinkRun->curr->n;
     while(DJBegin->prev != NULL)
          DJBegin=DJBegin->prev;
}


private:

     int
     N,   //Количество станков
     M;   //Количество деталей
     double min[2];





Node *CreateItem (double A, double B, int i)
{                //Функция создает новый элемент
   Node *pItem = new Node;
   pItem->A=A;
   pItem->B=B;
   pItem->n=i;
  // pItem->Next=NULL;
   //pItem->Prev=NULL;
   return pItem;
}

Node *InsertAfter (Node *parent, Node *Item)
{                 //Функция связывает два элемента
   if (parent != NULL)
   {
      //Item->Next=parent->Next;
    //  parent->Next=Item;
    //  Item->Prev=parent;
   }
   return Item;
}
   /*
void concatenateold(Node *parent, Node *Item)
{              //Функция соединяет два элемента
     if (parent != NULL)
          parent->Next=Item;
     if (Item!=NULL)
          Item->Prev=parent;
}                                    */

void concatenate(Link *parent, Link *Item)
{              //Функция соединяет два элемента
     if (parent != NULL)
          parent->next=Item;
     if (Item!=NULL)
          Item->prev=parent;
}
                /*
Node *getTail (Node *head)
{             //Функция поиска последного элемента ы списке
   if(head == NULL)
      return NULL;
   Node *Item=head;
   while(Item->Next != NULL)
      Item = Item->Next;
   return Item;
}                          */
                          /*
Node *PushBack (Node *head, Node *Item)
{              //Функция вставляет элемент в конец списка
   Node *tail = getTail(head);
   return InsertAfter (tail, Item);
}                                      */
            /*
void DeleteList (Node *Item)
{               //Функция удаляет список
   if (Item->Next != NULL)
   {
      DeleteList (Item->Next);
   }
   delete Item;
   Item = NULL;
}
                                   */




};
#endif
