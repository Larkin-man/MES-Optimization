

class Detal
{
public:
     Detal();
     double A;
     double B;
     Detal *Next;
     Detal *Prev;
     float fpub(int a)
     {
          test++;
          return ((float) a+test/10);
     }
private:
     int n;
     float test;
     float fpri(int a)
     {
          return (test);
     }
};

Detal::Detal():
     A(0)
{
     B=0;
}

 