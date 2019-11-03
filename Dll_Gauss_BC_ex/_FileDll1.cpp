//*extern "C" {  int far GaussCalcDll(char  *FileIn,char  *FileOut); } */
//extern int GaussCalc(char *,char *); // #include "Gauss.cpp"

void TTestWindow::CMTest(RTMessage)
{
char szBuf[255],strEdit[80]; int i=-1;i++; int len;

DWORD dwVersion;  dwVersion = GetVersion();
len = sprintf(szBuf, "Windows version %d.%d\n",LOBYTE(LOWORD(dwVersion)),  HIBYTE(LOWORD(dwVersion)));
sprintf(szBuf + len, "MS-DOS version %d.%d",HIBYTE(HIWORD(dwVersion)), LOBYTE(HIWORD(dwVersion)));
MessageBox(NULL, szBuf, "GetVersion", MB_ICONINFORMATION);

 Yield();//function stops the current task and starts any waiting task.

char szMsg[80];BYTE bTempDrive;
bTempDrive = GetTempDrive(0);sprintf(szMsg, "temporary drive: %c", bTempDrive);
MessageBox(GetFocus(), szMsg, "GetTempDrive", MB_OK);


HINSTANCE hinstTool;  int (FAR *lpfn);

/*Turn off the "File not found" error box.*/ 
SetErrorMode(SEM_NOOPENFILEERRORBOX);
/*Load the Gaussdll.DLL library module.*/
szBuf[0]='\0';strcpy(szBuf,buffilepath);strcat(szBuf,"\\gaussdll.dll\0");
hinstTool = LoadLibrary("gaussdll.dll");
MessageBox(HWindow,szBuf,"Метод Гаусса",MB_OK);
szBuf[0]='\0';

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
strEdit[0]='\0';
wsprintf(strEdit,"\n%d",hinstTool);_fstrcat(szBuf,strEdit);
MessageBox(NULL, (LPCSTR)szBuf, "Library Functions", MB_ICONHAND);


}
