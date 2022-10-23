/*************************************************************\
*      Optimization metods h - library version 3.0            *
*      Aleksey Aponasenko �                                   *
*      2013 All Rights Reserved �                             *
*      The author is not responsible for any mistakes,        *
*      found in this program                                  *
*      or for inapropriate use of it or any of its parts.     *
\*************************************************************/

#ifndef OptimizationMtdsH
#define OptimizationMtdsH
//#define max(A,B) (A>B ? A : B)
#define JohnsonAlgoritm 1
#define PSMethod 2
#define BranchesAndHordes 3

class MachineOptimizer
{
public:

     struct Detal    //��������!
     {
          int m;         //����� ������
          int *T;        //������ ������������� ��������� �� ������ ������
     };

     struct Link    //C����� �������
     {
          Link *next;    //��������� �������
          Detal *curr;    //������� ������
          Link *down;    //���� �� ������
     }
     *InitBegin,    //������ �������� �������
     *OptimalDJ,    //������ ������� �� ��������
     *OptimalPS,    //������ ������� �� �������-���������� (->down)
     *OptimalBH,    //������� � ��� ������ ������ � ������
     *PSBegin[4],   //������ ������ ������� �� �������-����������
     *OptimalNew;
     int *OutSequence,   //����������� ������������������ ��������� ������� ��� �������� � ��
          **OutMatrix;   //����������� ������������������ ��������� ������� ��� ���
     int StackOfCalls[4]; //���� �������� �������
     TStrings *Report;    //����� ���������� ����������
     bool output;
     bool debugging;

     MachineOptimizer();
     ~MachineOptimizer();         
     void add(int time[], int n);  //���������� ������
     bool ClearData(char MethodID); //������� ������� ������
     int DjonsonRun(); //������ ��������� ��������
     int PetrovSokolRun(); //������ ������ �������-����������
     int MethodBHRun (char version, bool idleall, TStaticText *out); //Method  of branches and hordes
     int GetN() {return N;}
     int NewMethodRun();

     /* TODO : ��������� �� ��������� ������ ���� ����� */

protected:

     int
     N,   //���������� �������
     M;   //���������� �������
     Link
     *InitEnd,      //����� ������ ������� �������
     *OptimalEnd,   //����� ������ detals �� ��������
     *PSEnd[4],     //����� ������ detals �� �������-����������
     *Cend,         //end of OptimalBH matrix
     *Linker,       //Temp
     **Cdos,
     **CdosEnd,     //End of Matrix OptimalBH(do,s)
     *OptimalNewEnd;
     int max;
               
     Detal* CreateItem (const int &n,const int &M,int *time);
     void CreateLink (Link **Begin, Detal **Item, Link **End, Link **Down = NULL);
     void concatenate(Link *parent, Link *Item);
     bool Sort(int &linker, int &min,const int &J);
     void DeleteLinks (Link *Item);
     void DeleteList (Link *Item);
     bool rowind(int *D, int &d);
     int ProductionCycle(Link *Matrix,bool down = false);

};

MachineOptimizer::MachineOptimizer()
{
     M=0;
     N=0;
     InitBegin=NULL;
     InitEnd=NULL;
     OptimalDJ=NULL;
     OptimalEnd=NULL;
     OptimalPS=NULL;
     Linker=NULL;
     OptimalBH=NULL,
     Cend=NULL;
     max=30000;     /* TODO : ������������ ������ ���������� � sizeof */
     output = true;
     debugging = false;

     for (int i=0;i<4;i++)
          {
               PSBegin[i]=NULL;
               PSEnd[i]=NULL;
          }
     Report = new TStringList;
     OutSequence = NULL;
     OutMatrix=NULL;
     OptimalNew=NULL;
     OptimalNewEnd=NULL;
}

MachineOptimizer::~MachineOptimizer()
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

     if (Report != NULL)
          delete Report;
     Report = NULL;
     if (OutSequence != NULL)
          delete [] OutSequence;
     OutSequence = NULL;
     if (OutMatrix != NULL)
          for (int i=0;i<M;i++)
               delete [] OutMatrix[i];
     OutMatrix = NULL;

     //ShowMessage("������ �������!");
}

void MachineOptimizer::add(int time[], int n)  //���������� ������
{
     N=n;
     M++;
     Detal *Item = CreateItem(n,M,time);
     CreateLink(&InitBegin,&Item,&InitEnd);      //DONE: to issue as function
}

bool MachineOptimizer::ClearData(char MethodID) //������� ������� ������
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

MachineOptimizer::Detal *MachineOptimizer::CreateItem (const int &n,const int &M,int *time)
{                //������� ������� ����� ������
     Detal *pItem = new Detal;
     pItem->T = new int[n];
     pItem->m=M;
     if (time == NULL) return pItem;
     for (int i=0;i<n;i++)
     {
          pItem->T[i]=time[i];
     }
     return pItem;
}

void MachineOptimizer::CreateLink (Link **Begin, Detal **Item, Link **End, Link **Down)
{    //��������� ������� � ����� (End) ������ Begin
     Link *pLink = new Link;
     pLink->next=NULL;
     pLink->curr=*Item;
     if (Down == NULL)
          pLink->down=*End;  //������� ���������� ������
     else
          pLink->down=*Down; //������
     if (*Begin == NULL)
          *Begin = pLink;  //set the begin of initial list
     else
          (*End)->next=pLink;
     *End=pLink;   //The end is always equal to a new item (Insert in the end of list)
}

void MachineOptimizer::concatenate(Link *parent, Link *Item)  //REMARKABLE!
{              //������� ��������� ��� ��������
     if (parent != NULL)
          parent->next=Item;
     if (Item!=NULL)
          Item->down=parent;
}

bool MachineOptimizer::Sort(int &linker, int &min,const int &J)
{              //������� ���������� ��� ����� - ����� ��� ���������� �� ��
     if (J == 1)
     {
          return linker <= min;  //Sorting according increase
     }
     return linker >= min;       //Sorting according decrease
}

void MachineOptimizer::DeleteList (Link *Item)
{
     if (Item == NULL) return;
     for (;Item!=NULL;Item=Item->next)
     {
          delete [] Item->curr->T;
          delete Item->curr;
     }
}

void MachineOptimizer::DeleteLinks (Link *Item)
{               //������� ������� ������
   if (Item->next != NULL)
   {
      DeleteLinks (Item->next);
   }
   delete Item;
   Item=NULL;
}
                                          
bool MachineOptimizer::rowind(int *D, int &d) //�������� ���������� ������ d � ������ D
{
     for (int i = 1;i<D[0]+2;i++)
          if (d == D[i])
               return false; //������ ����
          return true;       //������ ���
}

int MachineOptimizer::ProductionCycle(Link *Matrix,bool downed) //������� ������������ ����������������� ����� ��� ������� �
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
               if (downed)
                    top[i]+=Matrix->down->curr->T[i];  //����������� ���� �� ������
               else
                    top[i]+=Matrix->curr->T[i]; 
               left = top[i];
          }
     }

     delete []top;
     return left;
}


int MachineOptimizer::DjonsonRun() //������ ��������� ��������
{
     int min[2];
     for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next)
          CreateLink(&OptimalDJ,&Linker->curr,&OptimalEnd);
               //DONE: to issue as function!

     Linker = OptimalDJ;          //
     Detal *Item = CreateItem(N,0,NULL);    //TODO: found them and delete ?
     Link *pLink = new Link;
     pLink->next=NULL;
     pLink->down=NULL;
     pLink->curr=Item;
     OptimalDJ=pLink;    //������ � ��� createlink ��-�� ���� �������
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
     while(OptimalDJ->down != NULL)
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

int MachineOptimizer::PetrovSokolRun() //������ ������ �������-����������
{
     int S[3];
     int TimeCycle=max;
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
               Detal *Item = CreateItem(3,Linker->curr->m,S);     //TODO : To remove from cycle!
               CreateLink(&PSBegin[i],&Item,&PSEnd[i],&Linker);
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
          if (OutSequence[1] < TimeCycle)
          {
               TimeCycle=OutSequence[1];
               OutSequence[0]=j;
          }    //OutSequence[0]=j - ��� ����� ������ PSBegin
          //output->Lines->Add("������������: "+IntToStr(TimeCyclePS[j-1]));
     }//for j
     OptimalPS=PSBegin[OutSequence[0]];
     int i=0;
     for (Linker = PSBegin[OutSequence[0]];Linker!=NULL;Linker=Linker->next, i++)
          OutSequence[i]=Linker->curr->m;
     delete Temp;
     return TimeCycle;
}

int MachineOptimizer::MethodBHRun (char version = 0, bool idleall = false, TStaticText *out = NULL) //Method  of branches and hordes
{
     //ShowMessage("version="+IntToStr(version)+" bool1="+IntToStr(idleclean)+" bool1="+IntToStr(idleall));
     if (out != NULL)
              out->Caption=1;
     int
          s,   //������� ������
          d,   //������� ������
          o;   //������� �����������
     //�������� �������� �������
     Report->Clear();
     Report->Add("�����");
     AnsiString Added;
     OutMatrix = new int *[M];
     for (int i=0;i<M;i++)
          OutMatrix[i] = new int[N];
     for(int i = 0; i<M; i++)
          for(int j = 0; j<N; j++)
               OutMatrix[i][j]=0;    //�������� ������� ��������� ������

     if (output == false)
          debugging = false;  //NO OUTPUT
     int *D = new int [M+1];  //DONE: ���� ��� �������
     int *E = new int [M+1];
     int *Fi = new int[M+1];
     CdosEnd = new Link* [M+1];


     //�������� ������� �
     for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next)
     {
          // 1) ������������ ������� �
          Detal *pItem = new Detal;
          pItem->T = new int[N];
          pItem->m=Linker->curr->m;
          int summ=0;
          for (int i = 0 ;i<N;i++)
          {
               summ+=Linker->curr->T[i];  //����� �� �������
               pItem->T[i]=summ;
          }
          CreateLink(&OptimalBH,&pItem,&Cend,&Linker);
          //������� ������ OptimalBH, � down, ����������� �� InitBegin
     }

/*S*/for (s = 1;s<N+1;s++)   // 2. ���� �� �������!
     {
          if (out != NULL)
               out->Caption="������: "+IntToStr(s);
          int k = 0;
          if (output)
          {
               Report->Add("������� �");
               for (Linker = OptimalBH;Linker!=NULL;Linker=Linker->next)
               {    //������� ������� �� �����
                    Added+=IntToStr(Linker->curr->m)+"  |  ";
                    for (int i = 0;i<N;i++)
                         Added+=IntToStr(Linker->curr->T[i])+"  ";
                    Report->Add(Added);
                    Added="";
               }
               Report->Add("");
               Report->Add("������ � "+IntToStr(s));
           }

/***O***/ for(o = 1;o<M+1;o++)   //��� ������ �����������       // 3.
          {
               if (output)
               {
                    Report->Add("");
                    Report->Add("�����������: "+IntToStr(o));
               }

               // 4) �������� ��������� �� ������ s
               //� D ���������� ����� ������ �� � � � � �� �
               //��� ���� ���� �� ������ �� ������� ������ ���
               for (Linker = OptimalBH;Linker!=NULL;Linker=Linker->next)
               {
                    Detal *init = Linker->down->curr;  //��������� �� ������ �� ������ �
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
               if (output)
               {
                    Report->Add("�����������: "+IntToStr(E[0]));
                    Report->Add("H������������: "+IntToStr(D[0]));
               }
               if (debugging)
               {
                    Added+=("�����������:");
                    for (int i = 1;i<E[0]+1;i++)
                         Added+=(" "+IntToStr(E[i]));
                    Report->Add(Added);
                    Added="";
               }

               if (E[0] == 0)
               {
                    if (debugging)
                         Report->Add("�������� ���������� ��������������!");
                    break;   //��� � ��������� �����������

               }

               //-----����� ������ ���� ����� ������������
               //����� ������������� ������, ������� ��� ��� � ���������
               //�������� ����
               Cdos = new Link* [E[0]+1];

               for (int i = 0;i<E[0]+1;i++)
               {
                    Cdos[i] = NULL;
                    CdosEnd[i] = NULL;
               }

               //����������� ���� �� ����������� �������
/*****D*****/  for (int det = 1;det < E[0]+1;det++)
               {
                    d=E[det];
                    if (output)
                         Report->Add("������ � "+IntToStr(d));

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
                    //Report->Add("R="+IntToStr(R));
                    //������������ ����
                    for (Linker = OptimalBH;Linker!=NULL;Linker=Linker->next)
                    {
                         //output->Lines->Add("Linker "+IntToStr(Linker));
                         CreateLink(&Cdos[det],&Linker->curr,&CdosEnd[det],&Linker);
                         //������� ������ Cdos, � �������� down -> OptimalBH

                         if (rowind(D,Linker->curr->m))
                         {   //���� ���������� ������ �� �� ��������� �����
                              Detal *pItem = new Detal;
                              pItem->T = new int[N];
                              pItem->m=Linker->curr->m;
                              CdosEnd[det]->curr=pItem;
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
                    }
                    
                    if (output)
                    {
                         //Report->Add("CDOS");
                         for (Linker = Cdos[det];Linker!=NULL;Linker=Linker->next)
                         {    //������� ������� �� �����
                              //output->Lines->Add(IntToStr(Linker->curr->m)+"  |  ");
                              for (int i = 0;i<N;i++)
                                   Added+=IntToStr(Linker->curr->T[i])+"  ";
                              Report->Add(Added);
                              Added="";
                         }
                    }
                    if (debugging)
                         Report->Add("R="+IntToStr(R));

                    if (debugging)
                    {
                         Added="D: ";
                         for (int i = 0;i<M+1;i++)
                              Added+=IntToStr(D[i])+"  ";
                         Report->Add(Added);
                              Added="";
                         Added="E: ";
                         for (int i = 0;i<M+1;i++)
                              Added+=IntToStr(E[i])+"  ";
                         Report->Add(Added);
                              Added="";
                         Report->Add("det="+IntToStr(det));
                         Report->Add("k="+IntToStr(k));
                         if (rowind(D,det))
                              Report->Add("rowind(D,det) is TRUE");
                         //else
                         //     Report->Add("rowind(D,det) is FALSE");
                    }



                    int vers=int(version);
                     switch (vers)
                     {
                        case 1:
                        //{
                           Fi[det]=0;
                           for (Linker = Cdos[det];Linker!=NULL;Linker=Linker->next)
                           {
                              if (Linker->curr->T[N-1] > Fi[det])
                                 Fi[det] = Linker->curr->T[N-1];
                           }
                           break;
                        //}
                        case 2:
                        //{
                           Fi[det]=ProductionCycle(Cdos[det]);
                           break;
                        //}
                        case 3:
                        {
                           Fi[det]=0;
                           int *Duration = new int [N];
                           for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next)
                           {
                                 if (Linker->curr->m == E[det])
                                 {
                                    for (int j=0;j<N;j++)
                                    {
                                        Duration[j]=Linker->curr->T[j];
                                    }
                                    break;
                                 }
                           }

                           for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next)
                           {
                              if(rowind(D,Linker->curr->m))
                              {
                                   //������ � ��� � �
                                   //Report->Add("for "+IntToStr(Linker->curr->m));
                                   int ts=Duration[s-1];
                                   int st=Duration[s-1];
                                   for (int j=1;j<N;j++)
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
                           //        Fi[det]=Fi[det]+(Duration[i]*(N-i-1));
                           //}

                           delete []Duration;
                           break;
                        }
                        case 4:
                        {
                           ///////////////////////////////

                           Fi[det]=0;
                           int *top;
                           top = new int [N];
                           int left=0;
                           for (int i=0;i<N;i++)
                              top[i]=Cdos[det]->curr->T[i];
                           for (Linker = Cdos[det]->next;Linker!=NULL;Linker=Linker->next)
                           {
                              left=0;
                              bool netu;
                              if (rowind(D,Linker->curr->m))
                                   {
                                        if (debugging)
                                             Report->Add("Detali netu "+IntToStr(Linker->curr->m));
                                        netu=true;

                                   }
                                   else
                                   {
                                        if (debugging)
                                             Report->Add("Detal est "+IntToStr(Linker->curr->m));
                                        netu=false;

                                   }
                               for (int i=s-1;i<N;i++)
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
                        //{
                           // 7) ������ ����� ����������� � ���������� �� �������������� ������ ��� ���������� ��
                           int T = 0;   // 8) T
                           Link *minimal=Cdos[det];          //����������� = ������
                           int min;//=Cdos[det]->curr->T[s-1];  //int min=Cdos[det]->curr->T[N-2];
                           for (int i=0;i<M;i++)  //���� ���� ��� ���������� �
                           {
                              min=max;
                              for (Linker = Cdos[det];Linker!=NULL;Linker=Linker->next) //��� ������ ������������
                              {
                                 if ((Linker->curr->T[N-2] < min) && (Linker->curr->m >=0))    //(Linker->curr->T[N-2] < min)    (Linker->curr->T[s-1] < min)
                                 {
                                   minimal=Linker;
                                   min=Linker->curr->T[N-2];             //min=Linker->curr->T[N-2];     min=Linker->curr->T[s-1];
                                 }
                              }

                              //����������� ������
                              minimal->curr->m=-minimal->curr->m; //������� ����������� (-)
                              //������ � ������� if (T <= minimal->curr->T[s-1])   ��  T = minimal->curr->T[s];
                              if (T <= minimal->curr->T[N-2])   // 9) ���������� � � �(fq,n-1)   // (T <= minimal->curr->T[N-2])
                                 T = minimal->curr->T[N-1];                                    //T = minimal->curr->T[N-1];
                              else
                                 T+=minimal->down->down->curr->T[N-1];                    //T+=minimal->down->down->curr->T[N-1];
                              //Report->Add("i = "+IntToStr(i)+" T= "+IntToStr(T)+" min m= "+IntToStr(minimal->curr->m));
                           }
                           Fi[det]=T;   //11
                        //}
                     } //switch version
                     //Fi ������

                    for (int i=0;i<M;i++)   //�� �������� �������
                         if (d == OutMatrix[i][s-1])
                         {
                              if (debugging)
                                   Report->Add("������������� ������ "+IntToStr(d)+" � ������ ��� "+IntToStr(det));
                              //Fi[det]+=1000;
                              Fi[det]=max;
                         }
                    if (output)
                         Report->Add("Fi["+IntToStr(det)+"] = "+IntToStr(Fi[det]));

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
               if (output)
                    Report->Add("������: "+IntToStr(k)+" �� ������: "+IntToStr(s)+" ����� �������������: "+IntToStr(o)+" �� �����.");

               OutMatrix[o-1][s-1]=k;

               for (int i = 1;i<E[0]+1;i++) //���� ��� �������� Cdos
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
                              delete Linker->curr;  //�������� ��������
                              Linker->curr = NULL;
                         }
                    }
                    //delyal there
                    DeleteLinks(Cdos[i]);  //��������� ������
               }  //��� Cdos� �������

          } ///�������� ���� ������������
          if (idleall)
          {
               if (s>1)
               {
                    //�������� ���� �������� ������� ����� ������� ����� �������� � �������
                    //� ������� ���
                    int z;
                    Link *minimal=OptimalBH;          //����������� = ������
                    int min;//=Cdos[det]->curr->T[s-1];  //int min=Cdos[det]->curr->T[N-2];

                    for (int i=0;i<M;i++)  
                    {    //
                         min=max;
                         for (Linker = OptimalBH;Linker!=NULL;Linker=Linker->next) //��� ������ ������������
                         {
                              if ((Linker->curr->T[s-1] < min) && (Linker->curr->m >=0))    
                              {
                                   minimal=Linker;
                                   min=Linker->curr->T[s-1];
                              }    //���� ������� ������������ ����. ��������� ����� ���� ������� �� ������ s-1

                         }

                         //����������� ������
                         Added+=IntToStr(minimal->curr->m)+"  ";
                         minimal->curr->m=-minimal->curr->m; //������� ����������� (-)
                         //������ � ������� if (T <= minimal->curr->T[s-1])   ��  T = minimal->curr->T[s];
                         if (i==0)
                              z=minimal->curr->T[s-1];
                         //z - ����� ��������� ��������� ���������� ������
                         else
                         {
                              int A = (minimal->curr->T[s-1])-(minimal->down->curr->T[s-1]);
                              //� - ����� ������ ��������� ��������� ������
                              if (A != z)
                              {
                                   if(A != (minimal->curr->T[s-2]))
                                   {
                                        minimal->curr->T[s-1] = (z > (minimal->curr->T[s-2]))? z : (minimal->curr->T[s-2]);
                                        (minimal->curr->T[s-1])+=(minimal->down->curr->T[s-1]);
                                        if (debugging)
                                             Report->Add("����� ������� ������ "+IntToStr(-minimal->curr->m));
                                   }
                         }
                         z = minimal->curr->T[s-1];
                         }
                         //����� ������, ����� z � � ���� ���� �������, �� ����� ���������

                    } //���������� ���� �� ���� �������

                    for (Linker = OptimalBH;Linker!=NULL;Linker=Linker->next)  //������ ������
                         if (Linker->curr->m < 0)
                              Linker->curr->m=-Linker->curr->m;
                    
                    if (debugging)
                    {
                         Report->Add("��������������� ������ � OptimalBH");
                         Report->Add(Added);
                    }
                    Added="";
               }
          }//����������� ��������� �������� �� ������� ������

          //��� �������� �������� �������
          int max=0;
          for (Linker = OptimalBH;Linker!=NULL;Linker=Linker->next)
          {
               D[Linker->curr->m]=Linker->curr->T[s-1];
               if (D[Linker->curr->m]>max)
                    max=D[Linker->curr->m];
          }                                                    
          for (int i=0;i<M;i++)
               OutMatrix[i][s-1]=i+1;
          for (int i=0;i<M;i++)
          {
               D[0] = max+1;
               int min;
               for (int j=1;j<M+1;j++)
               {
                    if ((D[j]<D[0]) && (D[j]>=0))
                    {
                         D[0] = D[j];
                         min=j;
                    }
               }
               //����������� ������ D[0]
               D[min]=-D[min];
               OutMatrix[i][s-1]=min;
          }
          //�������� ������� ���������

          if (debugging)
          {
          Report->Add("�������� ������������������ ��������� �������");
          for (int i=0;i<M;i++)
          {
               for (int j=0;j<N;j++)
               {
                    Added+=IntToStr(OutMatrix[i][j])+"  ";
               }
               Report->Add(Added);
               Added="";
          }
          }

     } //�������� ���� �� �������
     
     //d=ProductionCycle(OptimalBH,output);
     //������ ������������ ����������������� �����
     int TimeCycle=OptimalBH->curr->T[N-1];
     for (Linker = OptimalBH->next;Linker!=NULL;Linker=Linker->next)
          if (Linker->curr->T[N-1]>TimeCycle)
               TimeCycle=Linker->curr->T[N-1];
     if (output)
          Report->Add("������������="+IntToStr(TimeCycle));
     //�������� ����������
     delete [] D;
     delete [] E;
     delete [] Fi;
     for (int i = 0;i<M+1;i++)
     {
          //DeleteLinks(Cdos[i]);   
     }
     delete [] CdosEnd;
     return TimeCycle;
}

int MachineOptimizer::NewMethodRun()
{
     //�������� �������� �������
     Report->Clear();
     Report->Add("�����");
     AnsiString Added;
     //Report->Strings[0].SetLength(80);
     OutMatrix = new int *[M];
     for (int i=0;i<M;i++)
          OutMatrix[i] = new int[N];
     for(int i = 0; i<M; i++)
          for(int j = 0; j<N; j++)
               OutMatrix[i][j]=0;
     int *Operative = new int[M+1];
     for (int i=0;i<M+1;i++)
          Operative[i]=0;

     for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next)   //�������� ����� ������
          CreateLink(&OptimalNew,&Linker->curr,&OptimalNewEnd);


     int max=0;
     for (Linker = InitBegin;Linker!=NULL;Linker=Linker->next) //��� ������ ������������
     {
          for (int i=0;i<N-1;i++)
               Operative[Linker->curr->m]+=(Linker->curr->T[i]*(N-i-1));
          if (max<Operative[Linker->curr->m])
               max=Operative[Linker->curr->m];
     }
     int min=1;
     int max2=max;


     Link* Linker2=NULL;
     for (Linker = OptimalNew;Linker!=NULL;Linker=Linker->next)
     //���� ��� �������������� �� �����������
     {
          max2=max+1;
          for (int i=1;i<M+1;i++) //���� ������ ����������� �������
          {
               if ((Operative[i]<max2)&&(Operative[i]>=0))
               {
                    max2=Operative[i];
                    min=i;     /* TODO 1 : ����� ����������� ������������� ���������� */
               }
          }   //i - ����� ������ � ����������� Operative

          Operative[min]*=(-1);
          for (Linker2 = InitBegin;Linker2!=NULL;Linker2=Linker2->next)
          {
               if (Linker2->curr->m == min)
               {
                    Linker->curr=Linker2->curr;
                    break;
               }
          }
     }
     return ProductionCycle(OptimalNew);
}

#endif
