// minmaxWin32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#include <commdlg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include <alloc.h>
#include <string.h>

#define OPENFBUTTON    110
#define EDITFBUTTON    120
#define CALCULATING    130
#define MAXCHECK       140
#define MINCHECK       150

#define MAX_LOADSTRING 100

// Global Variables:
HWND hWndBut,hWndB1,hWndB2,hWndCal;
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
HBITMAP hbmpMyBitmap;
char FileNameText[255];
char FileName[255];

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    LenaDlg(HWND , UINT, WPARAM , LPARAM );
int openFileDlg(HWND);
int saveFileDlg(HWND);
int mainMinMaxCalc(LPSTR lpCmdLineProc);
int MinMaxCalc(char  FileIn[255],char  FileOut[255],int FlagMinMax);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	int i;char StrName[300];
//MessageBox(NULL,lpCmdLine,"Message",0);
if (0!=strcmp(lpCmdLine,"")) 
{
	i=mainMinMaxCalc(lpCmdLine);
    if (i==IDYES) {
	  StrName[0]='\0';strcpy(StrName,"explorer \"");strcat(StrName,FileNameText);strcat(StrName,"\"");
      i=WinExec(StrName,SW_SHOW); 
      if (i < 32) { MessageBox(GetFocus(), "WinExec failed", "Error", MB_ICONSTOP);}
	}
	PostQuitMessage(0);
	return FALSE;
}

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MINMAXWIN32, szWindowClass, MAX_LOADSTRING);
    hbmpMyBitmap = LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP2));

	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

 	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_MINMAXWIN32);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if ((!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))||(!IsDialogMessage(msg.hwnd, &msg)))  
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_MINMAXWIN32);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
	wcex.lpszMenuName	= (LPCSTR)IDC_MINMAXWIN32;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   //CW_USEDEFAULT, 0,
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPED|WS_SYSMENU,
      CW_USEDEFAULT, 0, 360, 150, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   //|WS_TABSTOP
   CreateWindow("static","Выберите файл с таблицей..", WS_VISIBLE|WS_CHILD,
	      42, 15, 200, 20, hWnd, (HMENU)-1, hInstance, NULL);
hWndBut=CreateWindow("button", "Открыть..", WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON|WS_TABSTOP|WS_GROUP,
				250, 13, 100, 25, hWnd, HMENU(OPENFBUTTON), hInstance, NULL);
CreateWindow("static","FILE:", WS_VISIBLE|WS_CHILD,
	      2, 40, 40, 20, hWnd, (HMENU)-1, hInstance, NULL);
   CreateWindow("edit","", WS_VISIBLE|ES_AUTOHSCROLL|WS_CHILD|ES_READONLY|WS_TABSTOP|WS_GROUP|WS_BORDER,
	             42, 40, 310, 20, hWnd, HMENU(EDITFBUTTON), hInstance, NULL);
   CreateWindow("BUTTON","Type", WS_VISIBLE|WS_CHILD|BS_GROUPBOX,
	              42, 64, 200, 36, hWnd, (HMENU)-1, hInstance, NULL);
hWndB1=CreateWindow("BUTTON","min", WS_VISIBLE|WS_CHILD|BS_AUTORADIOBUTTON|WS_TABSTOP|WS_GROUP,
					 95, 78, 50, 15, hWnd, HMENU(MINCHECK), hInstance, NULL);
hWndB2=CreateWindow("BUTTON","max", WS_VISIBLE|WS_CHILD|BS_AUTORADIOBUTTON, 
					   155, 78, 50, 15, hWnd, HMENU(MAXCHECK), hInstance, NULL);
hWndCal=CreateWindow("button", "Вычислить..", WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON|WS_TABSTOP|WS_GROUP, 
					      250, 72, 100, 25, hWnd, HMENU(CALCULATING), hInstance, NULL);

		    SendDlgItemMessage(hWnd,MINCHECK,BM_SETCHECK,1,0L);
			SetFocus(hWndBut);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char StrName[550];int i;char buf[5];
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				case OPENFBUTTON:
				   openFileDlg(hWnd);
				   break;
				case CALCULATING:
				   if (0==saveFileDlg(hWnd))
				   { GetWindowText(GetDlgItem(hWnd,EDITFBUTTON),FileName,255);
	               	
				   if ((!strcmp(FileNameText,FileName))||(!strcmp(FileName,"")))
					{
	                   MessageBox(GetFocus(),"Внимание:\n Имя: исходного файла и файла с результатами совпадают \n Вычисления прерваны. ","Предупреждение",MB_OK|MB_ICONSTOP); 
					} else {
						StrName[0]='\0';
						strcpy(StrName,"\"");strcat(StrName,FileName);
						strcat(StrName,"\" \"");
						strcat(StrName,FileNameText);strcat(StrName,"\" \"");
                        i=(0==IsDlgButtonChecked(hWnd, MINCHECK))?2:1;
						sprintf(buf,"%d",i);
						strcat(StrName,buf);strcat(StrName,"\"");
						i=mainMinMaxCalc(StrName);
					    if (i==IDYES) {
						  StrName[0]='\0';strcpy(StrName,"explorer \"");strcat(StrName,FileNameText);strcat(StrName,"\"");
                          i=WinExec(StrName,SW_SHOW); 
                          if (i < 32) { MessageBox(hWnd, "WinExec failed", "Error", MB_ICONSTOP);}
						}
					}
				   }
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
HDC hdcMemory; 
HBITMAP hbmpOld;
BITMAP bm;
GetObject(hbmpMyBitmap, sizeof(BITMAP), &bm);
hdcMemory = CreateCompatibleDC(hdc);
hbmpOld =(HBITMAP) SelectObject(hdcMemory, hbmpMyBitmap);
BitBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcMemory, 0, 0, SRCCOPY);
SelectObject(hdcMemory, hbmpOld);
DeleteDC(hdcMemory);
//			RECT rt;
//			GetClientRect(hWnd, &rt);
//          SetTextColor(hdc, RGB(0,87,0));
//			DrawText(hdc, szHello, strlen(szHello), &rt, DT_RIGHT);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent; int i=0;
	switch (message)
	{
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDC_CHECK1:
				   i=IsDlgButtonChecked(hDlg, IDC_CHECK1);
				   if (i==1) DialogBox(hInst, (LPCTSTR)IDD_DLGA, hDlg, (DLGPROC)LenaDlg);
				   CheckDlgButton(hDlg, IDC_CHECK1, 0);
				   break;
				case IDOK:case IDCANCEL:
				   EndDialog(hDlg, LOWORD(wParam));
				   return TRUE;
			       break;
			}
			break;
	}
    return FALSE;
}

LRESULT CALLBACK LenaDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}


int openFileDlg(HWND hd)
{
OPENFILENAME ofnTemp;
DWORD Errval;/* Error value*/
char buf[5];	/* Error buffer*/
char szTemp[] = "All Files (*.*)\0*.*\0Text Files (*.txt)\0*.txt\0Data Files (*.dat)\0*.dat\0MathCad Files (*.prn)\0*.prn\0";
char ErrText[255];

FileName[0]='\0';ErrText[0]='\0';
	ofnTemp.lStructSize = sizeof( OPENFILENAME );
    ofnTemp.hwndOwner = hd; 
	ofnTemp.hInstance = 0;
	ofnTemp.lpstrFilter = (LPSTR)szTemp;	
	ofnTemp.lpstrCustomFilter = NULL;
	ofnTemp.nMaxCustFilter = 0;
	ofnTemp.nFilterIndex = 1;
	ofnTemp.lpstrFile = (LPSTR)FileName;/* Stores the result in this variable*/
	ofnTemp.nMaxFile = sizeof( FileName );
	ofnTemp.lpstrFileTitle = NULL;
	ofnTemp.nMaxFileTitle = 0;
	ofnTemp.lpstrInitialDir = NULL;
	ofnTemp.lpstrTitle = "Открыть Файл";	/* Title for dialog*/
	ofnTemp.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	ofnTemp.nFileOffset = 0;
	ofnTemp.nFileExtension = 0;
	ofnTemp.lpstrDefExt = "*";
	ofnTemp.lCustData = NULL;
	ofnTemp.lpfnHook = NULL;
	ofnTemp.lpTemplateName = NULL;
	if(GetOpenFileName( &ofnTemp ) != TRUE)
	{ Errval=CommDlgExtendedError();
	  if(Errval!=0)	/* 0 value means user selected Cancel*/
	  { sprintf(buf,"%ld",Errval);
        strcpy(ErrText,"GetOpenFileName returned Error #"); 
        strcat(ErrText,buf);
        MessageBox(GetFocus(),ErrText,"WARNING",MB_OK|MB_ICONSTOP); 
      }
	}
if (Errval!=0)
{  
	 SendDlgItemMessage(hd,EDITFBUTTON,WM_SETTEXT,0,long(FileName)); 
}

return 0 ;
}


int saveFileDlg(HWND hd)
{
OPENFILENAME ofnTemp;
DWORD Errval;/* Error value*/
char buf[5];	/* Error buffer*/
char szTemp[] = "All Files (*.*)\0*.*\0Text Files (*.txt)\0*.txt\0Data Files (*.dat)\0*.dat\0MathCad Files (*.prn)\0*.prn\0";
char ErrText[255];

FileName[0]='\0';ErrText[0]='\0';
	ofnTemp.lStructSize = sizeof( OPENFILENAME );
    ofnTemp.hwndOwner = hd; 
	ofnTemp.hInstance = 0;
	ofnTemp.lpstrFilter = (LPSTR)szTemp;	
	ofnTemp.lpstrCustomFilter = NULL;
	ofnTemp.nMaxCustFilter = 0;
	ofnTemp.nFilterIndex = 1;
	ofnTemp.lpstrFile = (LPSTR)FileName;/* Stores the result in this variable*/
	ofnTemp.nMaxFile = sizeof( FileName );
	ofnTemp.lpstrFileTitle = NULL;
	ofnTemp.nMaxFileTitle = 0;
	ofnTemp.lpstrInitialDir = NULL;
	ofnTemp.lpstrTitle = "Сохранить результаты как....";	/* Title for dialog*/
	ofnTemp.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST|OFN_OVERWRITEPROMPT;
	ofnTemp.nFileOffset = 0;
	ofnTemp.nFileExtension = 0;
	ofnTemp.lpstrDefExt = "*";
	ofnTemp.lCustData = NULL;
	ofnTemp.lpfnHook = NULL;
	ofnTemp.lpTemplateName = NULL;
	if(GetSaveFileName( &ofnTemp ) != TRUE)
	{ Errval=CommDlgExtendedError();
	  if(Errval!=0)	/* 0 value means user selected Cancel*/
	  { sprintf(buf,"%ld",Errval);
        strcpy(ErrText,"GetSaveFileName returned Error #"); 
        strcat(ErrText,buf);
        MessageBox(GetFocus(),ErrText,"WARNING",MB_OK|MB_ICONSTOP); 
      }
	}
if (Errval!=0)
{  
	FileNameText[0]='\0';
	strcpy(FileNameText,FileName);
	return 0;
}

 return -2;
}




//
//-------------------------------------------------------------------
int mainMinMaxCalc(LPSTR lpCmdLineProc)
{
  int argc,loop,j,fl,error=0;
  char  filenameIn[255], filenameOut[255],OutFlagMinMax[20],mesText[500];int FlagMinMax;

 /* check for only one command-line parameter */
  filenameIn[0]='\0';filenameOut[0]='\0';OutFlagMinMax[0]='\0';argc=0;
  FlagMinMax=1;
  loop=0;j=0;fl=0;
  while(lpCmdLineProc[loop]!='\0')
  {
  if (lpCmdLineProc[loop]=='"') { if (fl==0) {fl=1;loop++;argc++;j=0;} else fl=0; }
  if (fl==1) {
    if (argc==1) { filenameIn[j]=lpCmdLineProc[loop];j++;filenameIn[j]='\0'; }
    if (argc==2) { filenameOut[j]=lpCmdLineProc[loop];j++; filenameOut[j]='\0';}
    if (argc==3) { OutFlagMinMax[j]=lpCmdLineProc[loop];j++; OutFlagMinMax[j]='\0';}
  }
	loop++;
  }
  //argc=sscanf(lpCmdLineProc,"%s %s %d",filenameIn,filenameOut,&FlagMinMax);
  if (argc <2) {  
	mesText[0]='\0';
	strcpy(mesText,"Very small args\nFormat: filename \"fileIn\" \"fileOut\" \"1 (def) ||2\"");
	MessageBox(NULL,(LPCTSTR)mesText,"Error",0);
    return 0;
  }

 if (argc>=2)
  {
	j=sscanf(OutFlagMinMax,"%d",&FlagMinMax);
	if (j!=1) FlagMinMax=1;
    if ((FlagMinMax!=1) && (FlagMinMax!=2))  FlagMinMax =1;
     error=MinMaxCalc(filenameIn,filenameOut,FlagMinMax);
	 MessageBeep(0);
  }

//mesText[0]='\0';
//sprintf(mesText,"%s \n %s \n %d",filenameIn,filenameOut,FlagMinMax);
//MessageBox(NULL,(LPCTSTR)mesText,"Error",0);

//mesText[0]='\0';
//sprintf(mesText,"\n%d",error);
//MessageBox(NULL,(LPCTSTR)mesText,"Error",0);

 mesText[0]='\0';j=MB_ICONSTOP|MB_OK ;
 switch (error) {
  case -1: strcpy(mesText,"Cannot read data file: \n"); strcat(mesText,filenameIn); break;
  case -2: strcpy(mesText,"Cannot creat out file");strcat(mesText,filenameOut);break;
  case -3: strcpy(mesText,"Table is not Matrix(n x n) \n Unknow Format date;");break;
  case 0: strcpy(mesText,"Table is created \n Is file open ?"); j=MB_YESNO|MB_DEFBUTTON1|MB_ICONINFORMATION;
	      FileNameText[0]='\0';strcpy(FileNameText,filenameOut);
	      break;
  default : strcpy(mesText,"Unknow Error"); break;
 }
 
 fl=MessageBox(GetFocus(),(LPCTSTR)mesText,"Message",j);

 return (error+fl);
}

int MinMaxCalc(char  FileIn[255],char  FileOut[255],int FlagMinMax)
/*FlagMinMax=1-min ;2-max*/
/*-1:Cannot read data file;
  -2 :Cannot creat out file;
  -3:Table is not Matrix(n x n) Unknow Format date;
   0  :all normal   */
{

FILE *rf;FILE *hf;  /*double*/float Pr; int fl_Count;
int Count ;  /*Счетчик*/

if((hf = fopen(FileIn, "r"))==NULL) return(-1);

Count = 0; fl_Count=0;
while (fl_Count==0)  if (1== fscanf(hf, "%f",&Pr)) Count++;  else fl_Count=1;
if (Count>3)
{ Pr=sqrt((double)Count);
   if ((Pr!=floor(Pr)) || (Pr!=ceil(Pr)) || (floor(Pr)!=ceil(Pr))) { fclose(hf);return(-3);  }
  }
 else { fclose(hf);return(-3);  }

 if((rf=fopen(FileOut,"w"))==NULL) { fclose(hf);return(-2);  }

   int n; n=(int)Pr;  //n=14,  число узлов(вершин) /*зЁб«® г§«®ў(ўҐаиЁ­)*/

/* allocate memory for the far pointer */
float *X;    //X[n][n+1];
X = (float *) malloc(n*(n+1)*sizeof(float));
float *R;    //float R[n][n] весовая матрица
R = (float *) malloc(n*n*sizeof(float));

 int  i,j,k,p,fl; float VarMinMax;

/*Reading table..*/ rewind(hf); //fclose(hf);if((hf = fopen(FileIn, "r"))==NULL) {  fclose(rf);return(-1);}
if(FlagMinMax==1) VarMinMax=1e37; else VarMinMax=-1e37;
for(i=0;i<n;i++)
{ /*fprintf(rf,"\n");*/
  for(j=0;j<n;j++)
  { fscanf(hf,"%f",&Pr);
    if (Pr==0.00000000) R[i*n+j]=VarMinMax; else R[i*n+j]=Pr;
    /*fprintf(rf," %8.3f ",Pr);*/ }
 }
fclose(hf);

fprintf(rf,"\nФайл Исходных Данных= %s \nТип задачи=%s \n",FileIn,((FlagMinMax==1)?"min":"max"));

for(i=0;i<(n*(n+1));i++) X[i]=0.0; //ЋЎ­г«Ґ­ЁҐ

/*Ќ з «м­л© */ X[0*n+0]=0.0;for(i=n+1;i<(n*n);i+=(n+1)) X[i]=VarMinMax;

 /*Ќ е®¦¤Ґ­ЁҐ ®ЇвЁ¬ «м­®Ј® ЇгвЁ*/
for(k=0;k<n;k++)
 for(i=0;i<n;i++)
  switch(FlagMinMax)
   { case 1:{
      p=0;
      for(j=1;j<n;j++) if((X[j*(n+1)+k]+R[j*n+i])<(X[p*(n+1)+k]+R[p*n+i])) p=j;
      X[i*(n+1)+k+1]=X[p*(n+1)+k]+R[p*n+i];
      if (i==0) if(0.00000000<X[i*(n+1)+k+1]) X[i*(n+1)+k+1]=0.0;
      } break;
   case 2:{
      p=0;
      for(j=1;j<n;j++) if((X[j*(n+1)+k]+R[j*n+i])>(X[p*(n+1)+k]+R[p*n+i])) p=j;
      X[i*(n+1)+k+1]=X[p*(n+1)+k]+R[p*n+i];
      if (i==0) if(0.00000000>X[i*(n+1)+k+1]) X[i*(n+1)+k+1]=0.0;
      } break;
    }

/*Ќ е®¦¤Ґ­ЁҐ ўҐаиЁ­ ®ЇвЁ¬ «м­®Ј® ЇгвЁ Ё Ёе ўлў®¤*/
if (X[n*(n+1)-1]==X[n*(n+1)-2])
 {
 k=n;
 while (X[n*n+k-1]==X[n*n+k-2])  k--;
 k++;
 fprintf(rf,"\nОптимальное суммарное значение:=% 8.3g\nЧисло дуг:=%d\nНомера вершин=|%d",X[n*(n+1)-2],k,n);
 i=n-1;
 while (i!=-1)
  {
   fl=0;
   switch (FlagMinMax)
  { case 1:{
       p=0;
       for(j=1;j<n;j++) if ((X[j*(n+1)+k-1]+R[j*n+i])<(X[p*(n+1)+k-1]+R[p*n+i])) { p=j;fl=1; }
       } break;
  case  2:{
       p=0;
       for(j=1;j<n;j++) if ((X[j*(n+1)+k-1]+R[j*n+i])>(X[p*(n+1)+k-1]+R[p*n+i])) { p=j;fl=1; }
       } break;
     }
   if (fl!=0) fprintf(rf,"<-%d",p+1);
   if (i==p) i--; else i=p;
   }
   fprintf(rf,"<-1|.");
} else {  fprintf(rf,"\nОптимальное суммарное значение:=NULL\nЧисло дуг:=NULL\nНомера вершин=|NULL"); } 

/* ‚лў®¤ аҐ§г«мв в®ў */
 fprintf(rf,"\nTable of way:\n");
 for(i=0;i<n;i++)
{ fprintf(rf,"\n");
   for(j=0;j<(n+1);j++)  fprintf(rf," % 8.3g ",((X[i*(n+1)+j]==VarMinMax)?0.0:X[i*(n+1)+j]));
  }

 fclose(rf);
 return(0);
}