//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("MainSource.cpp", Form1);
USEFORM("About.cpp", AboutBox1);
USEFORM("Graphic.cpp", Form3);
USEFORM("EnterData.cpp", Form2);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
     try
     {
           Application->Initialize();
           Application->Title = "(@)^(@)";
           Application->CreateForm(__classid(TForm1), &Form1);
           Application->CreateForm(__classid(TForm3), &Form3);
           Application->CreateForm(__classid(TForm2), &Form2);
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
