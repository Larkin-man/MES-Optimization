
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
     struct Node    //C����� �������
     {
     int n;         //����� ������
     double A;      //������������ ��������� �� ������ ������
     double B;      //������������ ��������� �� ������ ������
     double *T;     //������ ������������� ��������� �������
     Node *Next;    //��������� ������
     Node *Prev;    //���������� ������
     }
     *Record,       //�������� ������
     *Optimal,      //������ �� ��������
     *minimal[2],   //����������� �� ������ ������ 0, �� ������ 1
     *NotOptimal;
     
     int n;

Node *CreateItem (double A, double B, int i)
{                //������� ������� ����� �������
   Node *pItem = new Node;
   pItem->A=A;
   pItem->B=B;
   pItem->n=i;
   pItem->Next=NULL;
   pItem->Prev=NULL;
   return pItem;
}

Node *InsertAfter (Node *parent, Node *Item)
{                 //������� ��������� ��� ��������
   if (parent != NULL)
   {
      //Item->Next=parent->Next;
      parent->Next=Item;
      Item->Prev=parent;
   }
   return Item;
}

void concatenate(Node *parent, Node *Item)
{              //������� ��������� ��� ��������
     if (parent != NULL)
          parent->Next=Item;
     if (Item!=NULL)
          Item->Prev=parent;
}


Node *getTail (Node *head)
{             //������� ������ ���������� �������� � ������
   if(head == NULL)
      return NULL;
   Node *Item=head;
   while(Item->Next != NULL)
      Item = Item->Next;
   return Item;
}

Node *PushBack (Node *head, Node *Item)
{              //������� ��������� ������� � ����� ������
   Node *tail = getTail(head);
   return InsertAfter (tail, Item);
}

void DeleteList (Node *Item)
{               //������� ������� ������
   if (Item->Next != NULL)
   {
      DeleteList (Item->Next);
   }
   delete Item;
   Item = NULL;
}





};
#endif
