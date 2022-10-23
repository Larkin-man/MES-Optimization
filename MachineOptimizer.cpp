//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("MainSource.cpp", BaseForm);
USEFORM("About.cpp", AboutBox1);
USEFORM("Graphic.cpp", GraphicForm);
USEFORM("EnterData.cpp", EnterDataForm);
USEFORM("Options.cpp", OptionsForm);            
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
     try
     {
           Application->Initialize();
           Application->Title = "(@)^(@)";
           Application->HelpFile = "C:\\Documents and Settings\\Алекс\\Мои документы\\Билдер\\Оптимизация\\HELPMOISOUP.HLP";
           Application->CreateForm(__classid(TBaseForm), &BaseForm);
           Application->CreateForm(__classid(TGraphicForm), &GraphicForm);
           Application->CreateForm(__classid(TOptionsForm), &OptionsForm);
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
