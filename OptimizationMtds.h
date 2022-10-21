/*************************************************************\
*      Optimization metods h - library version 3.0            *
*      Aleksey Aponasenko �                                   *
*      2012 All Rights Reserved �                             *
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

     struct Node    //������
     {
     int m;         //����� ������
     int *T;        //������ ������������� ��������� �������
     };

     struct Link    //C����� �������
     {
     Link *next;    //��������� �������
     Node *curr;    //������� ������
     Link *prev;    //���������� �������
     }
     *InitBegin,    //������ ������ ������� �������
     *InitEnd,      //����� ������ ������� �������
     *Optimal,      //������ ������ ������� �� ��������
     *OptimalEnd,   //����� ������ detals �� ��������
     *PSBegin[4],   //������ ������ ������� �� �������-����������
     *PSEnd[4],     //����� ������ detals �� �������-����������
     *Linker,       //Temp
     *C,            //������� � ��� ������ ������ � ������
     *Cend;         //end of C matrix

~MachineOptimizer()
{
     //ShowMessage("���������� �������");
     //�������� ���� �������
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
     //ShowMessage("������ �������!");
}


void add(int n,int *time)  //���������� ������
{
     if (n<N)
          N=n;
     M++;
     Node *Item = CreateItem(n,M,time);
     //InitEnd = CreateLink(InitBegin,Item,InitEnd);
     Link *pLink = new Link;       //TODO: to issue as function
     pLink->next=NULL;
     pLink->curr=Item;
     pLink->prev=InitEnd;
     if (InitBegin == NULL)
          InitBegin = pLink;  //set the begin of initial list
     else
          InitEnd->next=pLink;
     InitEnd = pLink;         //The end is always equal to a new item (Insert in the end of list)
          //pLink->prev->next=pLink;       */
}

void DjonsonRun()      //For two machines  Fortune havor!
{
     for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next) 
     {                                    //TODO: to issue as function!
          Link *pLink = new Link;
          pLink->next=NULL;
          pLink->curr=Linker->curr;  //But not to copy of NODE ! only Link
          pLink->prev=OptimalEnd;     
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
     pLink->prev=NULL;                     
     pLink->curr=Item;
     Optimal=pLink;
     Link *minimal[2];
     minimal[0]=NULL;
     minimal[1]=NULL;
     //Link *Linker = InitBegin;
     for (int i=0;i<M-1;i++)  //���� �� ���� �������
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


          if (min[0]<=min[1]) //���������� ���� ��������� ��������
          {                   //Paste in begin
               if (minimal[0]==Linker)
                    Linker=Linker->next;
               concatenate(minimal[0]->prev,minimal[0]->next);
               concatenate(Optimal->prev,minimal[0]);
               concatenate(minimal[0],Optimal);
          }
          else
          {                   //Paste in end
               if (minimal[1]==Linker)
                    Linker=Linker->next;
               concatenate(minimal[1]->prev,minimal[1]->next);
               concatenate(minimal[1],Optimal->next);
               concatenate(Optimal,minimal[1]);
          }
     }
     Optimal->curr->T[0]=Linker->curr->T[0];
     Optimal->curr->T[1]=Linker->curr->T[1];
     Optimal->curr->m=Linker->curr->m;
     //delete Linker->curr;
     //delete Linker;
     while(Optimal->prev != NULL)
          Optimal=Optimal->prev;
}

void PetrovSokolRun()
{
     int S[3];
     for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next)
     {             //������������ ������� ����
          S[0]=0;  //������ ������� - ����� ����� ���������� ������
          S[1]=0;  //������ ������� - ����� ����� ������� ������
          S[2]=0;  //������ ������� - �������� ������� � �������
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
               pLink->prev=Linker;  //
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
                         //���� ����������� ��� - ������������ ������ � ������� �������
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
                    //������ ������� ���������
                    //ShowMessage("������: "+IntToStr(minimal->curr->T[0])+" � "+IntToStr(PetrovSokol->curr->T[0]));
                    Temp->curr=minimal->curr;
                    Temp->prev=minimal->prev;
                    minimal->curr=PetrovSokol->curr;
                    minimal->prev=PetrovSokol->prev;
                    PetrovSokol->curr=Temp->curr;
                    PetrovSokol->prev=Temp->prev;
               }

               PetrovSokol=PetrovSokol->next;
          }
     }//for j
     delete Temp;
}

void MethodBHRun () //Method  of branches and hordes
{
     int
          s,   //������� ������
          d,   //������� ������
          o;   //������� �����������
     for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next)
     {
          Link *pLink = new Link;
          pLink->next=NULL;
          // 1) ������������ ������� �
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
          pLink->prev=Cend;
          if (C == NULL)
               C = pLink;
          else
              Cend->next=pLink;
          Cend = pLink;        
     }
     s=1; // 2.
     o=1; // 3.
     



}

protected:

     int
     N,   //���������� �������
     M;   //���������� �������
     int min[2];
 
//Node *CreateItem (int,int,int *time =NULL);

Node *CreateItem (int n,int M,int *time)
{                //������� ������� ����� �������
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
     pLink->prev=End;
     if (Begin == NULL)
          Begin = pLink;  //set the begin of initial list
     else
          return End;    //������������ � ���� ���� ������ �������� � ���������� �� ���������
     return NULL;
}


void concatenate(Link *parent, Link *Item)  //REMARKABLE!
{              //������� ��������� ��� ��������
     if (parent != NULL)
          parent->next=Item;
     if (Item!=NULL)
          Item->prev=parent;
}

bool YANISH(int linker, int min,int J)
{              //������� ���������� ��� ����� - ����� ��� ���������� �� ��
     if (J == 1)
     {
          return linker <= min;  //Sorting according increase
     }
     return linker >= min;       //Sorting according decrease
}

void DeleteLinks (Link *Item)
{               //������� ������� ������
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

};
#endif
