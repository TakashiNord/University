// ObjectWindows - (C) Copyright 1992 by Borland International

#include <stdio.h>
#include <dir.h>
#include <string.h>
#include <owl.h>
#include <window.h>
#include "Filelib.h"

//#define _EXPORT huge

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

//*extern "C" {  int far GaussCalcDll(char  *FileIn,char  *FileOut); } */
//extern int GaussCalc(char *,char *); // #include "Gauss.cpp"

void TTestWindow::CMTest(RTMessage)
{

char szBuf[255],strEdit[80]; int i=-1;i++;

Yield();//function stops the current task and starts any waiting task.

HINSTANCE hinstTool;  int (FAR *lpfn);

/*Turn off the "File not found" error box.*/ 
SetErrorMode(SEM_NOOPENFILEERRORBOX);
/*Load the Gaussdll.DLL library module.*/
szBuf[0]='\0';strcpy(szBuf,buffilepath);strcat(szBuf,"\\gaussdll.dll\0");
hinstTool = LoadLibrary("gaussdll.dll");//hinstTool = LoadLibrary("gaussdll.dll");//gaussdll.dll
MessageBox(HWindow,szBuf,"Метод Гаусса",MB_OK);
HMODULE hModule=GetModuleHandle("GAUSSDLL");//szBuf
if ( hModule==NULL)  MessageBox(HWindow,"Error","GetModuleHandle",MB_OK);
szBuf[0]='\0';

char szModuleName[255];
GetModuleFileName(GetApplication()->hInstance, szModuleName, sizeof(szModuleName)); 
MessageBox(NULL, szModuleName, "Module", MB_ICONINFORMATION);

if (hinstTool > HINSTANCE_ERROR) {    /* loaded successfully */

    (FARPROC) lpfn =  GetProcAddress(hinstTool, "GaussCalcDll");

    if (lpfn!= NULL) { /* Call the GaussCalcDll function. */
MessageBox(HWindow,"Решение системы уравнений\n\tметодом Гаусса.\nТип Вычисления:Фоновый режим\nCopyright(c) 2000","Метод Гаусса",MB_OK);

//i=GaussCalcDll("__m.dat","__outg.prn");

MessageBox(HWindow,"FINISH","Метод Гаусса",MB_OK|MB_ICONSTOP);
//        } else strcpy(szBuf,"GaussCalcDll failed");
    } else strcpy(szBuf, "GetProcAddress failed");

/* Free the GaussCalcDll.DLL library module. */  FreeLibrary(hinstTool);
 } else  strcpy(szBuf, "LoadLibrary failed"); 

if ((UINT) hinstTool > 32)  FreeLibrary(hinstTool);

strEdit[0]='\0';
wsprintf(strEdit,"\n%d",hinstTool);_fstrcat(szBuf,strEdit);
MessageBox(NULL, (LPCSTR)szBuf, "Library Functions", MB_ICONHAND);

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

/*char szBuf[255],strEdit[80]; int i=-1;i++; int len;
BYTE bTempDrive; DWORD dwVersion;  
dwVersion = GetVersion();
len = sprintf(szBuf, "Windows version %d.%d\n",LOBYTE(LOWORD(dwVersion)),  HIBYTE(LOWORD(dwVersion)));
sprintf(szBuf + len, "MS-DOS version %d.%d\n",HIBYTE(HIWORD(dwVersion)), LOBYTE(HIWORD(dwVersion)));
bTempDrive = GetTempDrive(0);
sprintf(strEdit, "GetTempDrive: %c \n", bTempDrive);
strcat(szBuf,strEdit);strEdit[0]='\0';MessageBox(NULL, szBuf, "GetVersion", MB_ICONINFORMATION);
*/

