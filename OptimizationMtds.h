
#ifndef OptimizationMtdsH
#define OptimizationMtdsH

class MachineOptimizer
{
public:
     MachineOptimizer()
     {
     n=0;
     }

     void add(int m,int *time)
     {
          n++;
          Node *pItem = new Node;
          pItem->T = new double[m];
          for (int i=0;i<m;i++)
          {
          pItem->T[i]=time[i];
          }
          pItem->n=n;
          pItem->Next=NULL;
          pItem->Prev=NULL;
          Node *Item = PushBack(Record,pItem);
          Node *Itemn = PushBack(NotOptimal,pItem);
          if(Record == NULL)
               Record=Item;
          if (NotOptimal == NULL)
               NotOptimal=Itemn;
     }


private:
     struct Node    //Cписок деталей
     {
     int n;         //Номер детали
     double A;      //Длительность обработки на первом станке
     double B;      //Длительность обработки на втором станке
     double *T;     //Массив длительностей обработки деталей
     Node *Next;    //Следующая деталь
     Node *Prev;    //Предыдущая деталь
     }
     *Record,       //Исходный список
     *Optimal,      //Список по Джонсону
     *minimal[2],   //Минимальный на первом станке 0, на втором 1
     *NotOptimal;
     
     int n;

Node *CreateItem (double A, double B, int i)
{                //Функция создает новый элемент
   Node *pItem = new Node;
   pItem->A=A;
   pItem->B=B;
   pItem->n=i;
   pItem->Next=NULL;
   pItem->Prev=NULL;
   return pItem;
}

Node *InsertAfter (Node *parent, Node *Item)
{                 //Функция связывает два элемента
   if (parent != NULL)
   {
      //Item->Next=parent->Next;
      parent->Next=Item;
      Item->Prev=parent;
   }
   return Item;
}

void concatenate(Node *parent, Node *Item)
{              //Функция соединяет два элемента
     if (parent != NULL)
          parent->Next=Item;
     if (Item!=NULL)
          Item->Prev=parent;
}


Node *getTail (Node *head)
{             //Функция поиска последного элемента ы списке
   if(head == NULL)
      return NULL;
   Node *Item=head;
   while(Item->Next != NULL)
      Item = Item->Next;
   return Item;
}

Node *PushBack (Node *head, Node *Item)
{              //Функция вставляет элемент в конец списка
   Node *tail = getTail(head);
   return InsertAfter (tail, Item);
}

void DeleteList (Node *Item)
{               //Функция удаляет список
   if (Item->Next != NULL)
   {
      DeleteList (Item->Next);
   }
   delete Item;
   Item = NULL;
}





};
#endif
