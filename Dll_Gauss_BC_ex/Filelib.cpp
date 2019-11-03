// ObjectWindows - (C) Copyright 2000 by Borland International

#include <stdio.h>
#include <dir.h>
#include <string.h>
#include <owl.h>
#include <window.h>
#include "Filelib.h"

#include "gauss.h"

char buffilepath[MAXPATH];

class TTestApp : public TApplication
{
public:
  TTestApp(LPSTR AName, HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
    : TApplication(AName, hInstance, hPrevInstance, lpCmdLine, nCmdShow) {};
  virtual void InitMainWindow();
};

class TTestWindow : public TWindow
{
public:
  TTestWindow(PTWindowsObject AParent, LPSTR ATitle);
  virtual void GetWindowClass( WNDCLASS& );
  virtual void CMTest(RTMessage Msg) = [CM_FIRST + CM_TEST];
};

//extern int GaussCalc(char *,char *); // #include "Gauss.cpp"

void TTestWindow::CMTest(RTMessage)
{
char strEdit[128]; int i=-1;i++;

Yield();//function stops the current task and starts any waiting task.

/* Call the GaussCalcDll function. */
MessageBox(HWindow,"Решение системы уравнений\n\tметодом Гаусса.\nТип Вычисления:Фоновый режим\nCopyright(c) 2000","Метод Гаусса",MB_OK);
i=GaussCalcDll("__m.dat","__outg.prn");
wsprintf(strEdit,"\n%d\n",i);_fstrcat(strEdit,"FINISH");
MessageBox(NULL, (LPCSTR)strEdit, "Library Functions", MB_ICONHAND);
strEdit[0]='\0';
}

/******************************************************************/
TTestWindow::TTestWindow(PTWindowsObject AParent, LPSTR ATitle)
  : TWindow(AParent, ATitle)
{  AssignMenu("COMMANDS");  getcwd(buffilepath, MAXPATH); }

/*Icon window*/
void TTestWindow::GetWindowClass( WNDCLASS& WndClass )
{
  TWindow::GetWindowClass(WndClass);
  WndClass.hbrBackground = (HBRUSH)COLOR_HIGHLIGHT;//COLOR_APPWORKSPACE + 1;
  WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); 
  WndClass.hIcon = LoadIcon(GetApplication()->hInstance, "PaintIcon");
};

void TTestApp::InitMainWindow() 
{  MainWindow = new TTestWindow(NULL, Name); }

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
HINSTANCE hinstTool;

char szModuleName[255];
GetModuleFileName(hInstance, szModuleName, sizeof(szModuleName)); 
MessageBox(NULL, szModuleName, "Module_WinMain", MB_ICONINFORMATION);

 hinstTool = LoadLibrary("gaussdll.dll");
 if((int) hinstTool <= 32)
   MessageBox(NULL, "Unable to load library Borland", "System Error", MB_OK | MB_ICONHAND);

 TTestApp TestApp("Test", hInstance, hPrevInstance, lpCmdLine, nCmdShow);
 TestApp.Run();

if ((UINT) hinstTool > 32)  FreeLibrary(hinstTool);

  return TestApp.Status;
}


