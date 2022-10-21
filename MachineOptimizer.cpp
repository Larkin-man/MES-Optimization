//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("About.cpp", AboutBox1);
USEFORM("MainSource.cpp", Form1);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
     try
     {
           Application->Initialize();
           Application->Title = "(@)^(@)";
           Application->CreateForm(__classid(TForm1), &Form1);
           Application->Run();
     }
     catch (Exception &exception)
     {
           Application->ShowException(&exception);
     }
     catch (...)
     {
           try
           {
                throw Exception("");
           }
           catch (Exception &exception)
           {
                Application->ShowException(&exception);
           }
     }
     return 0;
}
//---------------------------------------------------------------------------
