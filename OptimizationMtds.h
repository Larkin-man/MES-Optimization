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
#define max(A,B) (A>B ? A : B)
#define JohnsonAlgoritm 1
#define PSMethod 2
#define BranchesAndHordes 3

class MachineOptimizer
{
public:

     struct Node    //������
     {
          int m;         //����� ������
          int *T;        //������ ������������� ��������� �������
     };

     struct Link    //C����� �������
     {
          Link *next;    //��������� �������
          Node *curr;    //������� ������
          Link *down;    //���� �� ������
     }
     *InitBegin,    //������ ������ ������� �������
     *OptimalDJ,      //������ ������ ������� �� ��������
     *OptimalPS,
     *PSBegin[4],   //������ ������ ������� �� �������-����������
     *OptimalBH,            //������� � ��� ������ ������ � ������
     **Cdos;        //Arari asimpaspari parire pararu parrapupa ta ta ta ua
     int *OutSequence,   //����������� ������������������ ��������� ������� ��� �������� � ��
          **OutMatrix;   //����������� ������������������ ��������� ������� ��� ���
     int StackOfCalls[4]; //���� �������� �������

MachineOptimizer()
{
     M=0;
     N=100; //max
     InitBegin=NULL;
     InitEnd=NULL;
     OptimalDJ=NULL;
     OptimalEnd=NULL;
     OptimalPS=NULL;
     Linker=NULL;
     OptimalBH=NULL,
     Cend=NULL;
     OutMatrix = NULL;
     max=30000;
     //debugging = true;

     for (int i=0;i<4;i++)
          {
               PSBegin[i]=NULL;
               PSEnd[i]=NULL;
          }
}

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
     if (OptimalDJ != NULL)
          DeleteLinks(OptimalDJ);

     if (InitBegin != NULL)
          DeleteLinks(InitBegin);
     //for (int i = 0;i < M+1; i++)
     //     if (Cdos[i] != NULL)
     //          DeleteLinks(Cdos[i]);

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
     pLink->down=InitEnd;
     if (InitBegin == NULL)
          InitBegin = pLink;  //set the begin of initial list
     else
          InitEnd->next=pLink;
     InitEnd = pLink;         //The end is always equal to a new item (Insert in the end of list)
          //pLink->down->next=pLink;       */
}

void SetDebugging(bool Debugging)
{
     debugging = Debugging;
}

bool ClearData(int MethodID) //������� ������� ������ 
{                            //1 - ��������� ��������
     switch(MethodID)
     {
          case 0:
               break;
          case 1:
               if (OptimalDJ != NULL)
               {
                    DeleteLinks(OptimalDJ);
                    OptimalDJ = NULL;
               }
               break;
          case 2:
               break;
          default:
               return false;
     }
     return false;
}

int DjonsonRun()      //For two machines  Fortune havor!
{
     for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next)
     {                                    //TODO: to issue as function!
          Link *pLink = new Link;
          pLink->next=NULL;
          pLink->curr=Linker->curr;  //But not to copy of NODE ! only Link
          pLink->down=OptimalEnd;
          if (OptimalDJ == NULL)
               OptimalDJ = pLink;  //set the begin of initial list
          else
              OptimalEnd->next=pLink;
          OptimalEnd = pLink;
     }
     //CreateLink(InitBegin,Linker->curr,InitEnd);
     Linker = OptimalDJ;          //
     Node *Item = CreateItem(N,0,NULL);    //TODO: found them and delete ?
     Link *pLink = new Link;
     pLink->next=NULL;
     pLink->down=NULL;
     pLink->curr=Item;
     OptimalDJ=pLink;
     Link *minimal[2];
     minimal[0]=NULL;
     minimal[1]=NULL;
     //Linker = InitBegin;
     for (int i=0;i<M-1;i++)  //���� �� ���� �������
     {
          min[0]=Linker->curr->T[0];   // ! minimal = first
          min[1]=Linker->curr->T[N-1];
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
               if (Item1->curr->T[N-1]<min[1])
               {
                    min[1]=Item1->curr->T[N-1];
                    minimal[1]=Item1;
               }
          }


          if (min[0]<=min[1]) //���������� ���� ��������� ��������
          {                   //Paste in begin
               if (minimal[0]==Linker)
                    Linker=Linker->next;
               concatenate(minimal[0]->down,minimal[0]->next);
               concatenate(OptimalDJ->down,minimal[0]);
               concatenate(minimal[0],OptimalDJ);
          }
          else
          {                   //Paste in end
               if (minimal[1]==Linker)
                    Linker=Linker->next;
               concatenate(minimal[1]->down,minimal[1]->next);
               concatenate(minimal[1],OptimalDJ->next);
               concatenate(OptimalDJ,minimal[1]);
          }
     }
     OptimalDJ->curr->m=Linker->curr->m;
     for (int i=0;i<N;i++)
          OptimalDJ->curr->T[i]=Linker->curr->T[i];

     //delete Linker->curr;
     //delete Linker;
     while(OptimalDJ->down != NULL)     //todo: ����� ���������� �� ����. ������ ��� ���������
          OptimalDJ=OptimalDJ->down;
     OutSequence = new int[M];
     int i=0;
     for (Linker = OptimalDJ;Linker!=NULL;Linker=Linker->next)
     {
          OutSequence[i]=Linker->curr->m;
          i++;
     }
     return ProductionCycle(OptimalDJ,false);
}

int PetrovSokolRun(TMemo *output = NULL)
{
     int S[3];
     int Time=max;
     OutSequence = new int[M];
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
          //������� ������ ���������� PSBegin
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
                         //���� ����������� ��� - ������������ ������ � ������� �������
                         if (Linker->curr->m > minimal->curr->m)
                              continue;
                    }   //*/

                    if (Sort(Linker->curr->T[j-1],minimal->curr->T[j-1],j))
                    {
                              minimal=Linker;
                    }
               }

               if (PetrovSokol != minimal)
               {
                    //������ ������� ���������
                    //ShowMessage("������: "+IntToStr(minimal->curr->m)+" � "+IntToStr(PetrovSokol->curr->m));
                    Temp->curr=minimal->curr;
                    Temp->down=minimal->down;
                    minimal->curr=PetrovSokol->curr;
                    minimal->down=PetrovSokol->down;
                    PetrovSokol->curr=Temp->curr;
                    PetrovSokol->down=Temp->down;
               }
               PetrovSokol=PetrovSokol->next;
          }
          //TimeCyclePS[j-1]=PSEnd[j]->down->curr->T[N-1];
          OutSequence[1]=ProductionCycle(PSBegin[j],true);
          if (OutSequence[1]<Time)
          {
               Time=OutSequence[1];
               OutSequence[0]=j;
          }    //OutSequence[0]=j - ��� ����� ������ PSBegin
          //output->Lines->Add("������������: "+IntToStr(TimeCyclePS[j-1]));
     }//for j
     OptimalPS=PSBegin[OutSequence[0]];
     int i=0;
     for (Linker = PSBegin[OutSequence[0]];Linker!=NULL;Linker=Linker->next)
     {
          OutSequence[i]=Linker->curr->m;
          i++;
     }
     return Time;
}

int MethodBHRun (TMemo *output = NULL) //Method  of branches and hordes
{
     int
          s,   //������� ������
          d,   //������� ������
          o;   //������� �����������
     //�������� �������� �������
     OutMatrix = new int *[M];
     for (int i=0;i<M;i++)
          OutMatrix[i] = new int[N];
     for(int i = 0; i<M; i++)
          for(int j = 0; j<N; j++)
               OutMatrix[i][j]=0;

     if (output == NULL)
          debugging = false;  //NO OUTPUT

     //�������� ������� �
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
               summ+=Linker->curr->T[i];  //����� �� �������
               pItem->T[i]=summ;
          }
          pLink->curr=pItem;
          pLink->down=Linker; //pLink->down=Cend;
          if (OptimalBH == NULL)
               OptimalBH = pLink;
          else
              Cend->next=pLink;
          Cend = pLink;
     }

     for (s = 1;s<N+1;s++)   // 2.
     {
          int k = 0;
          if (output != NULL)
          {
               output->Lines->Add("������� �");
               for (Linker = OptimalBH;Linker!=NULL;Linker=Linker->next)
               {    //������� ������� �� �����
                    output->Lines->Add(IntToStr(Linker->curr->m)+"  |  ");
                    for (int i = 0;i<N;i++)
                    output->Text=output->Text+IntToStr(Linker->curr->T[i])+"  ";
               }
               output->Lines->Add("");
               output->Lines->Add("");
               output->Lines->Add("������ � "+IntToStr(s));
          }

          for(o = 1;o<M+1;o++)   //��� ������� �����������       // 3.
          {
               if (output != NULL)
                    output->Lines->Add("�����������: "+IntToStr(o));
               // 4) �������� ��������� �� ������ s
               int *D = new int [M+1];
               int *E = new int [M+1];

               //� D ���������� ����� ������ �� � � � � �� �
               //��� ���� ���� �� ������ �� ������� ������ ���
               for (Linker = OptimalBH;Linker!=NULL;Linker=Linker->next)
               {
                    Node *init = Linker->down->curr;  //��������� �� ������ �� ������ �
                    D[init->m]=init->T[s-1];
                    E[init->m]=Linker->curr->T[s-1];
               }

               for (int i = 1;i<M;i++) //����� ����������� �������
               {
                    for (int j=i+1;j<M+1;j++)
                    {
                         if ((E[i] > E[j]-abs(D[j])) && (E[j] > E[i]-abs(D[i])))
                         {    //���������� ������ � ������
                              if (D[i] > 0)
                                   D[i]=-D[i];   //�������� ����������� ������ (-)
                              if (D[j] > 0)
                                   D[j]=-D[j];
                         }               
                    }
               }    

               D[0]=0;  //���-�� �������������
               E[0]=0;  //���-�� �����������
               int Dpos=1,Epos=1;
               for (int i = 1;i<M+1;i++)      //�������� �����������
               {
                    if (D[i]<0)    //�����������
                    {
                         E[Epos]=i;
                         Epos++;
                         E[0]++;
                    }
                    else           //�������������
                    {
                         D[Dpos]=i;
                         Dpos++;
                         D[0]++;
                    }
               }
               if (output != NULL)
               {
                    output->Lines->Add("�����������: "+IntToStr(E[0]));
                    output->Lines->Add("H������������: "+IntToStr(D[0]));
               }
               if (debugging)
               {
                    output->Lines->Add("�����������:");
                    for (int i = 1;i<E[0]+1;i++)
                         output->Lines->Add(E[i]);
               }

               if (E[0] == 0)
               {
               if (debugging)
                    output->Lines->Add("BREAK");
               break;

               }

               //-------------����� ������ ���� ����� ������������
               //����� ������������� ������, ������� ��� ��� � ���������
               /*   for (int i=1;i<E[0]+1;i++)  //�� ������� ������ D
               for (int j=0;j<M;j++)   //�� �������� �������
                    if ((E[i]>0) && (D[i] == OutMatrix[j][s-1]))
                    {
                         ShowMessage("������������� ������ "+IntToStr(E[i]));
                         Fi[i]+=1000;
                    }         */

               //�������� ����
               Cdos = new Link* [E[0]+1];
               CdosEnd = new Link* [E[0]+1];
               int *Fi = new int[E[0]+1];
               //*Cdos = new Link [E[0]];
               for (int i = 0;i<E[0]+1;i++)
               {
                    Cdos[i] = NULL;
                    CdosEnd[i] = NULL;
               }

               //����������� ���� �� ����������� �������
               for (int det = 1;det < E[0]+1;det++)
               {
                    d=E[det];
                    if (output != NULL)
                         output->Lines->Append("������ � "+IntToStr(d));


                    D[D[0]+1]=d;      // 5) �������� d � D

                    // 6) ����������� ����������
                    int R=0;
                    for (Linker = OptimalBH;Linker!=NULL;Linker=Linker->next)
                    {
                         if (Linker->curr->m == d)
                         {
                              R += Linker->curr->T[s-1];  //������ �(d,s)
                              if (s > 1)
                                   break;
                         }

                         if ((s == 1) && (Linker->curr->m == k))
                              R -= Linker->curr->T[s-1];  //������ �(k,s) //��� � != 1

                    }
                    // minimal->curr->m=-minimal->curr->m; //������� ����������� (-)
                    //output->Lines->Add("minimal="+IntToStr(minimal.next->curr->m));
                    if (debugging)
                         output->Lines->Add("R="+IntToStr(R));
                    //������������ ����
                    for (Linker = OptimalBH;Linker!=NULL;Linker=Linker->next)
                    {
                         //output->Lines->Add("Linker "+IntToStr(Linker));
                         Link *pLink = new Link;
                         pLink->next=NULL;
                         pLink->down=Linker;
                         pLink->curr=Linker->curr;
                         if (rowind(D,Linker->curr->m,output))
                         {   //���� ���������� ������ �� �� ��������� �����
                              Node *pItem = new Node;
                              pItem->T = new int[N];
                              pItem->m=Linker->curr->m;
                              pLink->curr=pItem;
                              for (int i=0;i<N;i++)
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
                         if (Cdos[det] == NULL)
                              Cdos[det] = pLink;
                         else
                              CdosEnd[det]->next=pLink;
                         CdosEnd[det] = pLink;     //*/
                    }
                    if (output != NULL)
                    {
                         for (Linker = Cdos[det];Linker!=NULL;Linker=Linker->next)
                         {    //������� ������� �� �����
                              output->Lines->Append("");
                              //output->Lines->Add(IntToStr(Linker->curr->m)+"  |  ");
                              for (int i = 0;i<N;i++)
                              output->Text=output->Text+IntToStr(Linker->curr->T[i])+"  ";
                         }
                    }

                    // 7) ������ ����� ����������� � ���������� �� �������������� ������ ��� ���������� ��
                    int T = 0;   // 8) T
                    Link *minimal=Cdos[det];          //����������� = ������
                    int min=Cdos[det]->curr->T[N-2];
                    for (int i=0;i<M;i++)
                    {
                         min=max;
                         for (Linker = Cdos[det];Linker!=NULL;Linker=Linker->next)
                         {
                              if ((Linker->curr->T[N-2] < min) && (Linker->curr->m >=0))
                              {
                                   minimal=Linker;
                                   min=Linker->curr->T[N-2];
                              }
                         }

                         //����������� ������
                         minimal->curr->m=-minimal->curr->m; //������� ����������� (-)
                         if (T <= minimal->curr->T[N-2])   // 9) ���������� � � �(fq,n)
                              T = minimal->curr->T[N-1];
                         else
                              T+=minimal->down->down->curr->T[N-1];
                    }

                    Fi[det]=T;   //11
                    for (int i=0;i<M;i++)   //�� �������� �������
                         if (d == OutMatrix[i][s-1])
                         {
                              if (debugging)
                                   output->Lines->Add("������������� ������ "+IntToStr(d)+" � ������ ��� "+IntToStr(det));
                              Fi[det]+=1000;
                         }
                    if (output != NULL)
                         output->Lines->Add("F�="+IntToStr(Fi[det]));
                    for (Linker = Cdos[det];Linker!=NULL;Linker=Linker->next)  //������ ������
                         if (Linker->curr->m < 0)
                              Linker->curr->m=-Linker->curr->m;

                    // 12) ������ d �� D
                    D[D[0]+1]=-d;
               }      // 13) �������� ����  �� �������
               // 14) ������� ����������� ��

               k=1;
               for (int i = 2;i<E[0]+1;i++)
               {
                    if (Fi[i] < Fi[k])
                         k = i;
               }
               k=E[k];
               // � = �(ko,s)
               //ShowMessage("������: "+IntToStr(k)+" �� ������: "+IntToStr(s)+" ����� �������������: "+IntToStr(o)+" �� �����.");
               if (output != NULL)
                    output->Lines->Add("������: "+IntToStr(k)+" �� ������: "+IntToStr(s)+" ����� �������������: "+IntToStr(o)+" �� �����.");
               OutMatrix[o-1][s-1]=k;
               for (int i = 1;i<E[0]+1;i++)
               {
                    for (Linker = Cdos[i];Linker!=NULL;Linker=Linker->next)
                    {
                         if (Linker->curr != Linker->down->curr)
                         {
                              if (E[i] == k)
                                   //ShowMessage("������ Linker->curr->m:"+IntToStr(Linker->curr->m));
                                   for (int i =0;i<N;i++)
                                        Linker->down->curr->T[i]=Linker->curr->T[i];
                                   //Linker->curr->m -=100;
                              delete Linker->curr;
                              Linker->curr = NULL;
                         }
                    }
                    DeleteLinks(Cdos[i]);
               }
               delete D;
               delete E;
               delete Fi;
          } ///�������� ���� ������������
     }
     //d=ProductionCycle(OptimalBH,output);
     d=OptimalBH->curr->T[N-1];
     for (Linker = OptimalBH->next;Linker!=NULL;Linker=Linker->next)
          if (Linker->curr->T[N-1]>d)
               d=Linker->curr->T[N-1];
     if (output != NULL)
          output->Lines->Add("������������="+IntToStr(d));
     return d; 
}

protected:

     int
     N,   //���������� �������
     M;   //���������� �������
     int min[2];
     Link           //TODO: ���� ���� ������ � ����� �������
     *InitEnd,      //����� ������ ������� �������
     *OptimalEnd,   //����� ������ detals �� ��������
     *PSEnd[4],     //����� ������ detals �� �������-����������
     *Cend,         //end of OptimalBH matrix
     *Linker,       //Temp
     **CdosEnd;     //End of Matrix OptimalBH(do,s)
     bool debugging;
     int max;

 
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
     pLink->down=End;
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
          Item->down=parent;
}

bool Sort(int linker, int min,int J)
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
                                          
bool rowind(int *D, int d,TMemo *out) //�������� ������� ������ d � ������ D
{
     //out->Lines->Add("d="+IntToStr(d));
     //out->Lines->Add("Massiv D");
     //for (int i=0;i<M+1;i++)
     //out->Lines->Add(IntToStr(D[i]));
     for (int i = 1;i<D[0]+2;i++)
          if (d == D[i])
               return false;
          //ShowMessage("true");
          return true;
}

int ProductionCycle(Link *Matrix,bool down = false) //������� ������������ ����������������� ����� ��� ������� �
{
     int *top = new int[N];
     int left;
     for (int i=0;i<N;i++)
          top[i]=0;
     for (;Matrix!=NULL;Matrix=Matrix->next)
     {
          left=0;
          for (int i=0;i<N;i++)
          {
               top[i]=top[i]>left? top[i] : left;
               if (down)
                    top[i]+=Matrix->down->curr->T[i];  //������ ����������� ���� �� ������
               else
                    top[i]+=Matrix->curr->T[i];  //������ ����������� ���� �� ������
               left = top[i];
          }
     }

     delete top;
     return left;
}                  

};
#endif
