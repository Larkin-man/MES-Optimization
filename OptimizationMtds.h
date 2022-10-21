/****************************************************************/
/*******Optimization metods h - library version 2.0**************/
/*******Aleksey Aponasenko ©   **********************************/
/*******2012 All Rights Reserved ®*******************************/
/*******The author is not responsible for any mistakes,**********/
/*******found in this program************************************/
/*******or for inapropriate use of it or any of its parts.*******/
/****************************************************************/

#ifndef OptimizationMtdsH
#define OptimizationMtdsH

class MachineOptimizer
{
public:

MachineOptimizer()
{
     N=0;
     M=100; //max
     InitBegin=NULL;
     InitEnd=NULL;
     Optimal=NULL;
     OptimalEnd=NULL;
     Linker=NULL;
     PSBegin=NULL;
     PSEnd=NULL;
     SortBegin=NULL;
     SortEnd=NULL;
}

     struct Node    //Станок
     {
     int n;         //Номер детали
     int *T;        //Массив длительностей обработки деталей
     };

     struct Link    //Cписок деталей
     {
     Link *next;
     Node *curr;
     Link *prev;
     }
     *InitBegin,    //Начало списка иходных деталей
     *InitEnd,      //Конец списка иходных деталей
     *Optimal,      //Начало списка деталей по Джонсону
     *OptimalEnd,   //Конец списка detals по Джонсону
     *PSBegin,      //Начало списка деталей по Петрову-Соколицину
     *PSEnd,        //Конец списка detals по Петрову-Соколицину
     *Linker,       //Temp
     *SortBegin,
     *SortEnd;

~MachineOptimizer()
{
     if (N==0) return;
     for (Link *Item = InitBegin;Item!=NULL;Item=Item->next)
          delete Item->curr;

     if (Optimal != NULL)
          DeleteList(Optimal);
     if (PSBegin != NULL)
          DeleteList(PSBegin);
     //ShowMessage("Данные удалены!");
     DeleteList(InitBegin);
}


void add(int m,int *time)  //Добавление станка
{
     if (m<M)
          M=m;
     N++;
     Node *Item = CreateItem(m,N,time);
     //InitEnd = CreateLink(InitBegin,Item,InitEnd);
     //Ii iiaiio ia?aco
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

void DjonsonRun()      //For two machines
{
     for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next) 
     {                                    //TODO: to issue as function!bleat'
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
     Node *Item = CreateItem(2,0,NULL);    //TODO: found them and delete
     Link *pLink = new Link;
     pLink->next=NULL;
     pLink->prev=NULL;                     
     pLink->curr=Item;
     Optimal=pLink;
     Link *minimal[2];
     minimal[0]=NULL;
     minimal[1]=NULL;
     //Link *Linker = InitBegin;
     for (int i=0;i<N-1;i++)  //Цикл по всем станкам
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
     Optimal->curr->n=Linker->curr->n;
     //delete Linker->curr;
     //delete Linker;
     while(Optimal->prev != NULL)
          Optimal=Optimal->prev;
}

void PetrovSokolRun()
{
     //TODO: To paste here copying of 'link'
     int S[3];
     for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next)
     {
          S[0]=0;
          S[1]=0;
          S[2]=0;
          for (int i=0;i<M;i++)
          {
               if (i!=(M-1))
                    S[0]+=Linker->curr->T[i];
               if (i!=0)
                    S[1]+=Linker->curr->T[i];
          }
          S[2]=S[1]-S[0];
          Node *Item = CreateItem(3,Linker->curr->n,S);
          Link *pLink = new Link;       //TODO: to issue as function
          pLink->next=NULL;
          pLink->curr=Item;
          pLink->prev=Linker;  //un-dilon us-tilan
          if (PSBegin == NULL)
               PSBegin = pLink;  //set the begin of initial list
          else
               PSEnd->next=pLink;
          PSEnd = pLink;         //The end is always equal to a new item (Insert in the end of list)
          //pLink->prev->next=pLink;       */
     }

     Link *minimal;
     Link *PetrovSokol = PSBegin;
     //SortBegin=PSBegin;
     Link *Temp = new Link;
     for (int i=0;i<N;i++)  //Oeee ii anai noaieai
     {
          minimal=PetrovSokol;
          for (Linker = PetrovSokol->next;Linker!=NULL;Linker=Linker->next)
          {
               if (Linker->curr->T[0] == minimal->curr->T[0])
               {
                    //ShowMessage("Равны: "+IntToStr(minimal->curr->n)+" и "+IntToStr(Linker->curr->n));
                    if (Linker->curr->n > minimal->curr->n)
                         continue;
               }   //*/

               if (Linker->curr->T[0] <= minimal->curr->T[0])
               {
                    //if (Linker->curr->n > minimal->curr->n)
                         minimal=Linker;
               }
          }

          if (PetrovSokol !=minimal)
          {
               //ShowMessage("Меняем: "+IntToStr(minimal->curr->T[0])+" и "+IntToStr(PetrovSokol->curr->T[0]));
               Temp->curr=minimal->curr;
               Temp->prev=minimal->prev;
               minimal->curr=PetrovSokol->curr;
               minimal->prev=PetrovSokol->prev;
               PetrovSokol->curr=Temp->curr;
               PetrovSokol->prev=Temp->prev;
          }

          PetrovSokol=PetrovSokol->next;
     } 

}

protected:

     int
     N,   //Количество станков
     M;   //Количество деталей
     int min[2];
 
//Node *CreateItem (int,int,int *time =NULL);

Node *CreateItem (int m,int N,int *time)
{                //Функция создает новый элемент
     Node *pItem = new Node;
     pItem->T = new int[m];
     pItem->n=N;
     if (time ==NULL) return pItem;
     for (int i=0;i<m;i++)
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
          return End;
     return NULL;
}


void concatenate(Link *parent, Link *Item)  //REMARKABLE!
{              //Функция соединяет два элемента
     if (parent != NULL)
          parent->next=Item;
     if (Item!=NULL)
          Item->prev=parent;
}

void DeleteList (Link *Item)
{               //Функция удаляет список
   if (Item->next != NULL)
   {
      DeleteList (Item->next);
   }
   delete Item;
}

};
#endif
