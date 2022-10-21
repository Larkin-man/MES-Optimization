
#ifndef OptimizationMtdsH
#define OptimizationMtdsH

class MachineOptimizer
{
public:
     MachineOptimizer()
     {
     N=0;
     InitBegin=NULL;
     InitEnd=NULL;
     Optimal=NULL;
     Linker=NULL;
     }

     struct Node    //������
     {
     int n;         //����� ������
     double A;      //������������ ��������� �� ������ ������
     double B;      //������������ ��������� �� ������ ������
     double *T;     //������ ������������� ��������� �������
     };

     struct Link    //������ �������
     {
     Link *next;
     Node *curr;
     Link *prev;
     }
     *InitBegin,    //������ ������ ������� �������
     *InitEnd,      //����� ������ ������� �������
     *Optimal,      //������ ������ ������� �� ��������
     *Linker,       //Temp
     *minimal[2];   //����������� �� ������ ������ 0, �� ������ 1


     void add(int m,double *time)  //���������� ������
     {
          M=m;
          N++;
          Node *Item = CreateItem(m,N,time);

          //�� ������ ������
          Link *pLink = new Link;
          pLink->next=NULL; //ok
          pLink->curr=Item;
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
     //Node *Item = CreateItem(2,-1,NULL);

     Node *pItem = new Node;   //ecaeae create item
     pItem->A=0;
     pItem->B=0;
     pItem->n=0;
     Link *pLink = new Link;
     pLink->next=NULL;
     pLink->prev=NULL;
     pLink->curr=pItem;
     Optimal=pLink;

     Link *LinkRun = InitBegin;
     for (int i=0;i<N-1;i++)
     {
          min[0]=LinkRun->curr->A;
          min[1]=LinkRun->curr->B;
          minimal[0]=LinkRun;
          minimal[1]=LinkRun;
          Link *Item1=LinkRun;
          while(Item1->next != NULL)  //���� ���� ����������� ��������
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


          if (min[0]<=min[1]) //���������� ���� ��������� ��������
          {
               if (minimal[0]==LinkRun)
                    LinkRun=LinkRun->next;
               concatenate(minimal[0]->prev,minimal[0]->next);
               concatenate(Optimal->prev,minimal[0]);
               concatenate(minimal[0],Optimal);
          }
          else
          {
               if (minimal[1]==LinkRun)
                    LinkRun=LinkRun->next;
               concatenate(minimal[1]->prev,minimal[1]->next);
               concatenate(minimal[1],Optimal->next);
               concatenate(Optimal,minimal[1]);
          }

     }
     Optimal->curr->A=LinkRun->curr->A;
     Optimal->curr->B=LinkRun->curr->B;
     Optimal->curr->n=LinkRun->curr->n;
     while(Optimal->prev != NULL)
          Optimal=Optimal->prev;
}


private:

     int
     N,   //���������� �������
     M;   //���������� �������
     double min[2];
 
//Node *CreateItem (int,int,double *time =NULL);

Node *CreateItem (int m,int N,double *time)
{                //������� ������� ����� �������
     Node *pItem = new Node;
     pItem->T = new double[m];
     for (int i=0;i<m;i++)
     {
          pItem->T[i]=time[i];
     }
     pItem->n=N;
     pItem->A=time[0];
     pItem->B=time[1];
   return pItem;
}


void concatenate(Link *parent, Link *Item)
{              //������� ��������� ��� ��������
     if (parent != NULL)
          parent->next=Item;
     if (Item!=NULL)
          Item->prev=parent;
}

};
#endif
