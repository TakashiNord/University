
// ObjectWindows - (C) Copyright 2001 
/*********************************************************************
This program has code that makes use of the Common Dialogs
available in Windows 3.1.  It is meant to be a simple example using the
C programming language.

The main window will have menu selections for opening a file,  When a file is
selected the name will be displayed on the client area of the window.

The files needed to build this program are . . .

mfileapp.h	Header file for application
mfileapp.h      Header file for application and resources
mfileapp.cpp	Source file for application
mfileapp.rc     Resource file for application
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dir.h>
#include <string.h>
#include <time.h>

// #define __LARGE__
// #define WIN31
// #define STRICT

#include <owl.h>

#include <mdi.h>
#include <io.h>
#include <commdlg.h>
#include <filewnd.h>
#include <iomanip.h>

#include <bwcc.h>

#include "mfhelp.h"

#include "Mfileapp.h"
//#include "Calc.h"

#include "About4.h"

#include "classapp.h"

class TTransferDialog : public TDialog {
public:
  TTransferDialog(PTWindowsObject AParent, int ResourceId);
};

const MAXNAMELEN=26;

char buffilepath[MAXPATH];
const char DskFile[] = "MNETAPP.SAV";

_CLASSDEF(TMDIFileWindow)
// Declare TMDIFileWindow, a TMDIFrame descendant
class _CLASSTYPE TMDIFileWindow : public TMDIFrame {
public:
    friend TFileWindow;
    WORD ChildNum;
   
    TMDIFileWindow(LPSTR ATitle, LPSTR MenuName);

  char NameEdit[MAXNAMELEN];
  TTransferWindow(PTWindowsObject AParent, LPSTR ATitle);

    virtual void GetWindowClass( WNDCLASS& WndClass );//Icon

    virtual void /*PTWindowsObject*/ NewFile(RTMessage Msg) =  [CM_FIRST + CM_MDIFILENEW];
    virtual void OpenFile(HWND HWindow) =  [CM_FIRST + CM_MDIFILEOPEN];
    virtual void SaveState(RTMessage Msg) = [CM_FIRST + CM_SAVESTATE];
    virtual void RestoreState(RTMessage Msg) = [CM_FIRST + CM_RESTORESTATE];

    virtual void CMUHelpHelp( RTMessage Msg) =[CM_FIRST + CM_U_HELPHELP] { WinHelp( HWindow, "WINHELP.HLP", HELP_HELPONHELP, 0L ); }
    virtual void CMHelp(RTMessage Msg)= [CM_FIRST + CM_U_HELPINDEX] { WinHelp( HWindow, "MNETAPP.HLP", HELP_INDEX, 0L );  }
    virtual void CMAbout(RTMessage Msg)= [CM_FIRST + CM_ABOUT]
     {  /*About dialog box*/
/*1*/
  FILE *rf; if ((rf=fopen("bwcc.dll","r"))!=NULL)
  { fclose(rf); GetApplication()->ExecDialog(new TDialog(this, "ABOUT1")); 
 //    BWCCMessageBox(HWindow,"Автор программы:Родионова E.A.\nГруппа :5ПМ1\nГод окончания :2000\nПреподаватели:Завозин Ж.Г.,Зверева T.В.\nCopyright(c) 2000 Комсомольск-на-Амуре","О ПРОГРАММЕ.2...",MB_OK|MB_ICONASTERISK);  
   } 
 else { /*2*/  MessageBox(HWindow,"Автор программы:Родионова E.A.\nГруппа :5ПМ1\nГод окончания :2000\nПреподаватели:Завозин Ж.Г.,Зверева T.В.\nCopyright(c) 2000 Комсомольск-на-Амуре","О ПРОГРАММЕ.2...",MB_OK|MB_ICONASTERISK); ; }
/*3*/  GetApplication()->ExecDialog(new TDialog(this, "ABOUT3"));
/*4*/
  PTWindow HelpWindow;
  HelpWindow = new THelpWindow(this);
  GetApplication()->MakeWindow(HelpWindow);

   }

    char nameMatrix[255],strEdit[255];
    void BaseRUN(int BaseFun );
    virtual void CMRUN1(RTMessage Msg)= [CM_FIRST + CM_RUN1];//Stream
    virtual void CMRUN2(RTMessage Msg)= [CM_FIRST + CM_RUN2];//Net
    virtual void CMRUN3(RTMessage Msg)= [CM_FIRST + CM_RUN3];//create table
    virtual void CMRUN4(RTMessage Msg)= [CM_FIRST + CM_RUN4];//Min
    virtual void CMRUN5(RTMessage Msg)= [CM_FIRST + CM_RUN5];//Max
    virtual void CMRUN6(RTMessage Msg)= [CM_FIRST + CM_RUN6];//Gauss

  //  virtual void CMCALC(RTMessage Msg)= [CM_FIRST + CM_CALC]
  //  { /* Create calculator as the application's main window. */
    /* GetModule()->ExecDialog(new TDialog(this,"ID_CALC"));*/
  //   GetApplication()->MakeWindow(new TCalc(this,"ID_CALC"));
  //  }

};

void CountChild(void *, void *CountPtr) {  ++*(int *)CountPtr; }

extern int StreamCalc(char *,char *);/* #include "Stream.cpp"*/
extern int MinMaxCalc(char *,char *,int );/* #include "Minmax.cpp"*/
/*extern "C" {  int far GaussCalcDll(char  *FileIn,char  *FileOut); } */
extern int GaussCalc(char *,char *); // #include "Gauss.cpp"

void TMDIFileWindow ::BaseRUN(int BaseFun )
{ 
char strTitle[80];   strTitle[0]='\0';strEdit[0]='\0';nameMatrix[0]='\0';

/*wsprintf(strEdit,"%li\n\n%d",ActiveChild,Count);_fstrcat(strEdit,"\0");*/
/*MessageBox(HWindow,(LPCSTR)strEdit,"RUN_1",MB_OK);*/

/*the number of children*/ int Count = 0; /* return a count of the MDI children*/  ForEach(CountChild, &Count);

switch(BaseFun)
{
case 1:_fstrcat(strEdit, "Получение Наибольшего Потока\nТип вычисления:Фоновый режим\nCopyright(c) 2000 Комсомольск-на-Амуре");
    _fstrcat(strTitle,"Наибольший Поток");
break;
case  2:
break;
case 3:
break;
case  4:_fstrcat(strEdit, "Получение Наименьшего Пути [Min].\nТип Вычисления:Фоновый режим\n");
    _fstrcat(strTitle,"Наименьший Путь [Min]");
break;
case  5: _fstrcat(strEdit, "Получение Наибольшего Пути [Max].\nТип Вычисления:Фоновый режим");
    _fstrcat(strTitle,"Наибольший Путь [Max]");
break;
case  6:_fstrcat(strEdit, "Решение системы уравнений\n\tметодом Гаусса.\nТип Вычисления:Фоновый режим\nCopyright(c) 2000");
    _fstrcat(strTitle,"Метод Гаусса");
break;
}

int FlagStream;LPSTR AFileNameStr;char FileNameStr[255]="";
if ( Count!=0 )
{  

MessageBox(GetFocus(),strEdit,strTitle,MB_OK);

   FlagStream=((PTFileWindow) ActiveChild)->TFileWindow::Save();
   AFileNameStr=((PTFileWindow) ActiveChild)->TFileWindow::FileName;

     /*((PTFileWindow) ActiveChild)->TFileWindow::SetFileName((LPSTR)"_bnv.dat" ); ((PTFileWindow) ActiveChild)->TFileWindow::Write();*/
     //if (((PTFileWindow) ActiveChild)->TFileWindow::CanClose()) ((PTFileWindow) ActiveChild)->TFileWindow::~TFileWindow();
     //((PTFileWindow) ActiveChild)->TFileWindow::ReplaceWith((LPSTR) "_bnv.dat");

   wsprintf(FileNameStr,"%s",AFileNameStr);_fstrcat(FileNameStr,"\0");
   if (FileNameStr[0]!='\0')
   { /* Perform file operations. */
nameMatrix[0]='\0';getcwd(nameMatrix, MAXPATH);

switch(BaseFun)
{
case  1: _fstrcat(nameMatrix,"\\_Mstream.prn\0");   
    FlagStream=StreamCalc(FileNameStr,nameMatrix);
break;
case  2:
break;
case  3:
break;
case  4:_fstrcat(nameMatrix,"\\_Mmin.prn\0");   
      FlagStream=MinMaxCalc(FileNameStr,nameMatrix,1);
break;
case  5: _fstrcat(nameMatrix,"\\_Mmax.prn\0");
    FlagStream=MinMaxCalc(FileNameStr,nameMatrix,2);
break;
case  6:  _fstrcat(nameMatrix,"\\_Mgauss.prn\0");
     FlagStream=GaussCalc(FileNameStr,nameMatrix);
break;
}

strEdit[0]='\0';
switch(FlagStream)
{case -1:_fstrcat(strEdit,"Невозможно открыть файл данных\nФайл=");_fstrcat(strEdit,FileNameStr);break;
  case -2:_fstrcat(strEdit,"Невозможно создать выходной файл данных\nФайл=");_fstrcat(strEdit,nameMatrix);break;
  case -3:
              if (BaseFun==6) _fstrcat(strEdit,"Таблица не матрица размером [(n x n)  (n x 1)]\nНеизвестный Формат Данных\nФайл=");
              else _fstrcat(strEdit,"Таблица не матрица размером(n x n)\nНеизвестный Формат Данных\nФайл=");
              _fstrcat(strEdit,FileNameStr);break;
   case -4:_fstrcat(strEdit,"Мало Памяти!");break;
   case 0:
             _fstrcat(strEdit,"<Решение>\nStatus : Готово\nФайл=");_fstrcat(strEdit,nameMatrix);
              GetApplication()->MakeWindow(new TFileWindow(this, strTitle ,nameMatrix));
              break;
default : break;
   }
MessageBox(HWindow,strEdit,strTitle,MB_OK|MB_ICONASTERISK);
 } 
}
else {MessageBox(GetFocus(),"Откройте или Создайте\nв Программе ->[Окно]\nс исходными данными",strTitle,MB_OK|MB_ICONSTOP);  }

}

void TMDIFileWindow ::CMRUN1(RTMessage )
{ 
BaseRUN(1);
}

 #include "Netwin.cpp"
/***********************----------------------------*****************************/
void TMDIFileWindow ::CMRUN2(RTMessage )
{ 
  PTWindow NetWindow;

  NetWindow = new TNetWindow(this);
  NetWindow->Attr.Style |= WS_POPUPWINDOW | WS_CAPTION;
//  NetWindow->Attr.X = 50;NetWindow->Attr.Y = 50;NetWindow->Attr.W = 550;NetWindow->Attr.H = 400;
  GetApplication()->MakeWindow(NetWindow);

}

void TMDIFileWindow ::CMRUN3(RTMessage)
{
int  i,j;  double  Pr=0.0;   const m=10;     double n=-1.0;

strEdit[0]='\0';char *endptr;
if ( GetModule()->ExecDialog(new TTransferDialog(this, ID_DIALOGNumber)) == IDOK )
 {  n = strtod(NameEdit, &endptr);
    if (n==0.0)
     { strcpy(strEdit, " Число  N!=");strcat(strEdit,NameEdit); strcat(strEdit, "\nЧисло  N=0");
       MessageBox(HWindow, strEdit, "Ошибка Ввода", MB_OK|MB_ICONSTOP);
     }

nameMatrix[0]='\0';_fstrcat(nameMatrix,buffilepath);_fstrcat(nameMatrix,"\\_Mtable.prn\0"); 
fstream os(nameMatrix,ios::out|ios::trunc);

os.fill(' ');os.width(8);os.precision(3);
 for(i=0;i<m;i++)
 { os<< "\n";
   for(j=0;j<m;j++)
   { Pr=0;  strEdit[0]='\0';
     if ((i==0)&&(j==1)) Pr=10+n; if ((i==0)&&(j==2)) Pr=6+n/3; if ((i==0)&&(j==3)) Pr=6+n/3;
     if ((i==1)&&(j==3)) Pr=2+n/2;     if ((i==1)&&(j==4)) Pr=9+n;
     if ((i==2)&&(j==3)) Pr=7+n/3;     if ((i==2)&&(j==5)) Pr=8+n;
     if ((i==3)&&(j==4)) Pr=3+n/2;if ((i==3)&&(j==5)) Pr=10+n/3; if ((i==3)&&(j==6)) Pr=4+n;
     if ((i==4)&&(j==6)) Pr=n+n/2;     if ((i==4)&&(j==7)) Pr=5+n/3;
     if ((i==5)&&(j==6)) Pr=9+n;       if ((i==5)&&(j==8)) Pr=7+n/2;
     if ((i==6)&&(j==7)) Pr=12+n/3;if ((i==6)&&(j==8)) Pr=6+n; if ((i==6)&&(j==9)) Pr=8+n/2;
     if ((i==7)&&(j==9)) Pr=9+n/3;
     if ((i==8)&&(j==9)) Pr=11+n/2;

     os<<"  "<<setiosflags( ios::right)<<Pr;
     if (!os.good())
     { os.clear();
      if (EOF==sprintf(strEdit," % g",Pr))  gcvt(Pr,4,strEdit); else _fstrcat(strEdit,"\0");
      os<<"  "<<strEdit;
     }
   }             
  }
os.close();
if (os.bad()){ unlink(nameMatrix); MessageBox(HWindow,"Невозможно создать [Файл таблицу]","Ошибка",MB_OK | MB_ICONEXCLAMATION);  }
  else  GetApplication()->MakeWindow(new TFileWindow(this, "TABLE",nameMatrix));
  }
}

TTransferDialog::TTransferDialog(PTWindowsObject AParent, int ResourceId) : TDialog(AParent, ResourceId)
{
  new TEdit(this, ID_NAMEEDIT,sizeof(((TMDIFileWindow *)Parent)->NameEdit));
  TransferBuffer = (void far*)&(((TMDIFileWindow *)Parent)->NameEdit);//TransferStruct);
}

void TMDIFileWindow ::CMRUN4(RTMessage )
{ 
BaseRUN(4);
}

void TMDIFileWindow ::CMRUN5(RTMessage )
{ 
BaseRUN(5);
}

void TMDIFileWindow ::CMRUN6(RTMessage)//Gauss method
{
BaseRUN(6);
}

/****************************************************************/
TMDIFileWindow::TMDIFileWindow(LPSTR ATitle, LPSTR MenuName): TMDIFrame(ATitle, MenuName)
{ 
  ChildNum = 1;
  getcwd(buffilepath, MAXPATH);
}

//void TMDIFileWindow::InitMenu( RTMessage Msg, int FlagMenu )
//{
//    HMENU hmTemp;
/* This trick is used to automatically update the status of the various menu 
    choices just before it is displayed.  */
//    hmTemp = GetMenu(HWindow);//(HMENU)Msg.WParam;

/*    EnableMenuItem( hmTemp, CM_RUN1, (FlagMenu==0)?MF_GRAYED:MF_ENABLED);
    EnableMenuItem( hmTemp, CM_RUN2,(FlagMenu==0)?MF_GRAYED:MF_ENABLED );//MF_DISABLED
    EnableMenuItem( hmTemp, CM_RUN3,(FlagMenu==0)?MF_GRAYED:MF_ENABLED);
    EnableMenuItem( hmTemp,CM_RUN4, (FlagMenu==0)?MF_GRAYED:MF_ENABLED );
    EnableMenuItem( hmTemp, CM_RUN5, (FlagMenu==0)?MF_GRAYED:MF_ENABLED);
    EnableMenuItem( hmTemp, CM_RUN6,  (FlagMenu==0)?MF_GRAYED:MF_ENABLED);
    EnableMenuItem( hmTemp, CM_ABOUT, (FlagMenu==0)?MF_GRAYED:MF_ENABLED);
*/
 //   CheckMenuItem( hmTemp, CM_RUN6, MF_BYCOMMAND | (MF_CHECKED : MF_UNCHECKED ));
//    DrawMenuBar( HWindow );
//}

/* Respond to "New" command by constructing, creating, and setting up a new TFileWindow MDI child */
void /*PTWindowsObject*/ TMDIFileWindow::NewFile(RTMessage)
{ char ChildName[14];
  wsprintf(ChildName,"LineNet %d", ChildNum++);
  GetApplication()->MakeWindow(new TFileWindow(this, ChildName,""));//TFileWindow TWindowMDIChild
}

/* Respond to "Open" command by constructing, creating, and setting up a new TFileWindow MDI child */
void TMDIFileWindow::OpenFile(HWND)//RTMessage
{
//old construction
    char ChildName[14];
 // wsprintf(ChildName,"LineNet %d", ChildNum++);
/*  char FileName[MAXPATH];
 if ( GetApplication()->ExecDialog(new TFileDialog(this, SD_FILEOPEN,
                             _fstrcpy(FileName, "*.*"))) == IDOK )
	GetApplication()->MakeWindow(new TFileWindow(this, ChildName, FileName));
*/
//end old construction

/*  Global Variables  */ strEdit[0]='\0';nameMatrix[0]='\0';
/*********************************************************************
Using the OPENFILENAME structure and the Windows 3.1 API call
GetOpenFileName() eases the selection of files for the programmer and for
the user.  The WINHELP.EXE help file WIN31WH.HLP The Flags field of the structure is particularly
useful when custimization is required.
**********************************************************************/
OPENFILENAME ofnTemp;
DWORD Errval;/* Error value*/         char buf[5];	/* Error buffer*/
char szTemp[] = "Files (*.prn)\0*.prn\0All Files (*.*)\0*.*\0Text Files (*.txt)\0*.txt\0Files (*.dat)\0*.dat\0";
/* Note the initialization method of the above string.  The GetOpenFileName()
function expects to find a string in the OPENFILENAME structure that has
a '\0' terminator between strings and an extra '\0' that terminates the
entire filter data set.  Using the technique shown below will fail because
"X" is really 'X' '\0' '\0' '\0' in memory.  */
/*Some Windows structures require the size of themselves in an effort to
provide backward compatibility with future versions of Windows.  If the
lStructSize member is not set the call to GetOpenFileName() will fail. */

	ofnTemp.lStructSize = sizeof( OPENFILENAME );
        ofnTemp.hwndOwner = HWindow;	/* An invalid HWindow causes non-modality*/
	ofnTemp.hInstance = 0;
	ofnTemp.lpstrFilter = (LPSTR)szTemp;	/* See previous note concerning string */
	ofnTemp.lpstrCustomFilter = NULL;
	ofnTemp.nMaxCustFilter = 0;
	ofnTemp.nFilterIndex = 1;
	ofnTemp.lpstrFile = (LPSTR)strEdit;/* Stores the result in this variable*/
	ofnTemp.nMaxFile = sizeof( strEdit );
	ofnTemp.lpstrFileTitle = NULL;
	ofnTemp.nMaxFileTitle = 0;
	ofnTemp.lpstrInitialDir = NULL;
	ofnTemp.lpstrTitle = "OPEN FILE";	/* Title for dialog*/
	ofnTemp.Flags = OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;
	ofnTemp.nFileOffset = 0;
	ofnTemp.nFileExtension = 0;
	ofnTemp.lpstrDefExt = "*";
	ofnTemp.lCustData = NULL;
	ofnTemp.lpfnHook = NULL;
	ofnTemp.lpTemplateName = NULL;
/* If the call to GetOpenFileName() fails you can call CommDlgExtendedError()
   to retrieve the type of error that occured.*/
	if(GetOpenFileName( &ofnTemp ) != TRUE)
                   { Errval=CommDlgExtendedError();
	  if(Errval!=0)	/* 0 value means user selected Cancel*/
	  { sprintf(buf,"%ld",Errval);
                        strcpy(nameMatrix,"GetOpenFileName returned Error #"); 
                        strcat(nameMatrix,buf);
                        MessageBox(HWindow,nameMatrix,"WARNING",MB_OK|MB_ICONSTOP); 
                      }
                    }
 // InvalidateRect(HWindow, NULL, TRUE );	// Repaint to display the new name
if (Errval!=0)
 { wsprintf(ChildName,"LineNet %d", ChildNum++);
   GetApplication()->MakeWindow(new TFileWindow(this, ChildName, strEdit));
  }
strEdit[0]='\0';nameMatrix[0]='\0';

}


/* Save the the position and contents of the windows to the  "desk top" file. */
void TMDIFileWindow::SaveState(RTMessage)
{    ofpstream os(DskFile); PutChildren(os);  os.close();
 if ( os.bad() )
  { unlink(DskFile);MessageBox(HWindow, "Unable to write desktop file.", "Disk error", MB_OK | MB_ICONEXCLAMATION);
  }
}

void DoCreateChild(Pvoid P, Pvoid)
{
 if ( ((PTWindowsObject)P)->IsFlagSet(WB_AUTOCREATE) ) ((PTWindowsObject)P)->Create();
}

/* Read windows positions and contents from the "desk top" file. */
void TMDIFileWindow::RestoreState(RTMessage)
{
  LPSTR ErrorMsg = NULL;
  
  ifpstream is(DskFile);
  if ( is.bad() ) ErrorMsg = _fstrdup("Unable to open desktop file.");
  else
  {
    if ( CloseChildren() )
    { GetChildren(is);
      if ( is.bad() )  ErrorMsg = _fstrdup("Error reading desktop file.");
      if ( GetApplication()->LowMemory() ) { CloseChildren(); ErrorMsg = _fstrdup("Not enough memory to open file."); }
       else  ForEach(DoCreateChild, NULL);
    }
  }
  if ( ErrorMsg ) MessageBox(HWindow, ErrorMsg, "Disk error", MB_OK | MB_ICONEXCLAMATION);
}

/*Icon window*/
void TMDIFileWindow::GetWindowClass( WNDCLASS& WndClass )
{
  TWindow::GetWindowClass(WndClass);
  WndClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE + 1;
  WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); 
  WndClass.hIcon = LoadIcon(GetApplication()->hInstance, "PaintIcon");
};


/* Construct the TMDIFileApp's MainWindow of type TMDIFileWindow, loading its menu */
void TMDIFileApp::InitMainWindow()
{
  MainWindow = new TMDIFileWindow("Сетевая задача", "Commands");
  ((PTMDIFileWindow)MainWindow)->ChildMenuPos = 4;
}

/* Initialize each MS-Windows application instance, loading an accelerator table */
void TMDIFileApp::InitInstance()
{
  TApplication::InitInstance();
  if ( Status == 0 )
   { HAccTable = LoadAccelerators(hInstance, "FileCommands");
   //HAccTable  = LoadAccelerators(GetApplication()->hInstance, MAKEINTRESOURCE("CALCCommands"));
     if ( HAccTable == 0 )   Status = EM_INVALIDWINDOW;

time_t t; srand((unsigned) time(&t));
int i;i=random(10)+1; //rand() % 10 +1;
switch(i)
{
case 1:MessageBox(GetFocus(),"Специальность: Прикладная Математика\n\tНеобходимо закрыть!\nВыпускники 1999,2000,2001 и т.д.\n(КнАГТУ),Комсомольск-на-Амуре","[ 1 ] Вечный Совет Дня",MB_OK|MB_ICONINFORMATION);
break;
case  2:MessageBox(GetFocus(),"Вы не любите кошек ?\nДа, Вы их, просто не умеете готовить\n\n\tВечно голодные студенты","[ 2 ] Вечный Совет Дня",MB_OK|MB_ICONINFORMATION);
break;
case 3:MessageBox(GetFocus(),"\tЗавозин Ж.Г.\n- наш любимый преподаватель","[ 3 ] Вечный Совет Дня",MB_OK|MB_ICONINFORMATION);
break;
case  4:MessageBox(GetFocus(),"Автор программы:Родионова E.A.\nГруппа :5ПМ1\nГод окончания :2000\nПреподаватели:Завозин Ж.Г.,Зверева T.В.\nCopyright(c) 2000 Комсомольск-на-Амуре","[ 4 ] Вечный Совет Дня",MB_OK|MB_ICONASTERISK); 
break;
case  5:MessageBox(GetFocus(),"\tЗверева Т.В.\n- и Экономика пойдет в рост","[ 5 ] Вечный Совет Дня",MB_OK|MB_ICONINFORMATION);
break;
case  6:MessageBox(GetFocus(),"Сейчас, у Вас, откроется \n второе дыхание","[ 6 ] Вечный Совет Дня",MB_OK|MB_ICONINFORMATION);
break;
default : break;
}


    }

}

// Run the MDIFileApp
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmd, int nCmdShow)
{
 TMDIFileApp MDIFileApp("Сетевая задача", hInstance, hPrevInstance,lpCmd, nCmdShow);
 MDIFileApp.Run();
 return MDIFileApp.Status;
}

/*ѓагЇЇ : 5ЏЊ-1  ЏаҐЇ®¤ ў вҐ«м : ‡ўҐаҐў  ’.‚.(Є дҐ¤а  ЏЊЁ€)
 Ђўв®ал Їа®ҐЄв  ‘вг¤Ґ­вл: CўЁаЁ¤Ґ­Є® Ћ.‚., ђ®¤Ё®­®ў  ….Ђ.
 ѓ®¤ 2000*/


/*

*/