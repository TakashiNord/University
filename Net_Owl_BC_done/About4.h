
// Version 2
// ObjectWindows - (C) Copyright 2000 by International

#include <stdio.h>
#include <dir.h>
#include <string.h>
#include <math.h>

#include <groupbox.h>
#include <listbox.h>
#include <edit.h>
#include <button.h>
#include <combobox.h>
#include <static.h>

#include <owl.h>
#include <window.h>

#include "sysinfo.cpp"

#include "arty.cpp"
#include "line.cpp"

/*********************************/
void ChildTimers( Pvoid P, Pvoid)
{
  ((PTLineWindow)P)->TimerTick();
};
/*********************************/

/******************************************************************/
const WORD  ID_GROUPBOX0ABOUT=1100;
const WORD  ID_BUTTON1ABOUT=1101;
const WORD  ID_BUTTON2ABOUT=1102;
const WORD  ID_EDIT1ABOUT=1103;
const WORD  ID_EDIT_ABOUT=1104;
const WORD  ID_BUTTON_ABOUT=1105;
const WORD  ID_LISTBOX_ABOUT=1106;

_CLASSDEF(THelpWindow)
class _EXPORT THelpWindow : public TWindow
{ 
private:
          PTLineWindow LineWindow;
          PTArtyWindow ArtyWindow;
          LOGFONT  MainFontRec;
public:
  PTListBox ListBox;  PTEdit Edit,Edit0; TGroupBox *GroupBox0;
  THelpWindow(PTWindowsObject AParent);
  virtual void SetupWindow();
  virtual LPSTR GetClassName() {  return "THelpWindow";  };
  virtual void GetWindowClass(WNDCLASS& );
  virtual void HandleListBoxMsg(RTMessage Msg) = [ID_FIRST + ID_LISTBOX_ABOUT];
  virtual void HandleButton1Msg(RTMessage Msg) = [ID_FIRST + ID_BUTTON_ABOUT];
  virtual void HandleButton2Msg(RTMessage Msg) = [ID_FIRST + ID_BUTTON1ABOUT];
  virtual void HandleButton3Msg(RTMessage Msg) = [ID_FIRST + ID_BUTTON2ABOUT];
  virtual void FillEdit(Pchar SelString);
  virtual void WMControlColor(TMessage& Msg) = [WM_FIRST + WM_CTLCOLOR];
 /*TimerTick is a trivial method that gets called  whenever application receives a WM_Timer.
  Descendants will override this procedure if they need timer messages.*/
  virtual void TimerTick();
  virtual void WMSize( TMessage& Msg ) = [ WM_FIRST + WM_SIZE ];
  virtual void WMTimer( TMessage& )          = [WM_FIRST + WM_TIMER];
  virtual void WMDestroy( TMessage& )        = [WM_FIRST + WM_DESTROY];
  virtual void Paint( HDC PaintDC, PAINTSTRUCT& PaintInfo);
 virtual void WMGetMinMaxInfo( TMessage& ) = [WM_FIRST + WM_GETMINMAXINFO];

};

/*****************************************************/
void THelpWindow::WMTimer( TMessage& )
{
  ForEach(ChildTimers, NULL);
};

void THelpWindow::WMDestroy( TMessage& Msg )
{
  KillTimer(HWindow, 0);
  TWindow::WMDestroy(Msg);
};

void THelpWindow::TimerTick() { ; }

void THelpWindow::WMSize( TMessage& Msg )
{
 TWindow::WMSize(Msg);
 if ((Msg.WParam == SIZENORMAL) || (Msg.WParam == SIZEFULLSCREEN))
   { ; };
//  RECT R;  GetClientRect(GetFocus(), &R); HWindow
  MoveWindow(LineWindow->HWindow,10,10,50,50,TRUE);
  MoveWindow(ArtyWindow->HWindow,330,10,50,50,TRUE);
};

void THelpWindow::Paint( HDC PaintDC, PAINTSTRUCT& PaintInfo)
{RECT R;
  LOGFONT  MainFontRec; 
  MainFontRec.lfHeight = 11;   MainFontRec.lfWidth = 8;
  MainFontRec.lfEscapement = 0;    MainFontRec.lfOrientation = 0;
  MainFontRec.lfWeight = FW_BOLD;  MainFontRec.lfItalic = 0; 
  MainFontRec.lfUnderline = 0;   MainFontRec.lfStrikeOut = 0;
  MainFontRec.lfCharSet = ANSI_CHARSET ;//| SYMBOL_CHARSET;
  MainFontRec.lfOutPrecision =OUT_TT_PRECIS | OUT_DEFAULT_PRECIS;
  MainFontRec.lfClipPrecision = CLIP_DEFAULT_PRECIS;
  MainFontRec.lfQuality = PROOF_QUALITY;
  MainFontRec.lfPitchAndFamily = VARIABLE_PITCH | FF_ROMAN;
  strcpy(MainFontRec.lfFaceName,"Arial");
 //strcpy(MainFontRec.lfFaceName,"Courier New"); 
 //strcpy(MainFontRec.lfFaceName,"Times New Roman");
  
 TWindow::Paint(PaintDC, PaintInfo);
BeginPaint(HWindow, &PaintInfo);
PaintDC=GetDC(HWindow);//SaveDC(PaintDC);

HPEN hpen;
hpen = CreatePen(PS_SOLID, 6, RGB(0, 0, 255));
SelectObject(PaintDC, hpen);
Rectangle(PaintDC, 74, 6, 320, 100);
DeleteObject(hpen);
hpen = CreatePen(PS_SOLID, 4, RGB(222, 23, 26));
SelectObject(PaintDC, hpen);
Rectangle(PaintDC, 74+2, 6+2, 320-2, 100-2);
DeleteObject(hpen);
//hpen = CreatePen(PS_DOT, 1, RGB(126, 168, 31));
//SelectObject(PaintDC, hpen);
//RoundRect(PaintDC, 85, 15, 120, 50, 20, 80);
//DeleteObject(hpen);

HDC hdcMemory;    HBITMAP hbmpMyBitmap, hbmpOld;    BITMAP bm;
hbmpMyBitmap = LoadBitmap(GetApplication()->hInstance, "R_bmp");
GetObject(hbmpMyBitmap, sizeof(BITMAP), &bm);
hdcMemory = CreateCompatibleDC(PaintDC);
hbmpOld =(HBITMAP) SelectObject(hdcMemory, hbmpMyBitmap);
BitBlt(PaintDC, 85, 15, bm.bmWidth, bm.bmHeight, hdcMemory, 0, 0, SRCCOPY);
SelectObject(hdcMemory, hbmpOld);
DeleteDC(hdcMemory);

hbmpMyBitmap = LoadBitmap(GetApplication()->hInstance, "RFoto");
GetObject(hbmpMyBitmap, sizeof(BITMAP), &bm);
hdcMemory = CreateCompatibleDC(PaintDC);
hbmpOld =(HBITMAP) SelectObject(hdcMemory, hbmpMyBitmap);
BitBlt(PaintDC, 10, 110, bm.bmWidth, bm.bmHeight, hdcMemory, 0, 0, SRCCOPY);
SelectObject(hdcMemory, hbmpOld);
DeleteDC(hdcMemory);

ReleaseDC(HWindow, PaintDC);

  HBRUSH OldBrush;      HPEN OldPen;
  OldBrush = (HBRUSH)SelectObject(PaintDC, CreateSolidBrush(RGB(0,114,55)));
  hpen = (HPEN)SelectObject(PaintDC, GetStockObject(NULL_PEN));
  GetClientRect(HWindow, &R);
// R.bottom = R.right;
//  OffsetRect(&R, -R.right/4, -R.right/4);
// Ellipse(PaintDC.hdc, R.left, R.top, R.right, R.bottom);
  Ellipse(PaintDC, 270, 17,295, 40);
  SelectObject(PaintDC, hpen);
  DeleteObject(SelectObject(PaintDC, OldBrush));

  OldBrush = (HBRUSH)SelectObject(PaintDC, CreateSolidBrush(RGB(30,26,112)));
  hpen = (HPEN)SelectObject(PaintDC, GetStockObject(NULL_PEN));
  Ellipse(PaintDC, 285, 25,305, 45);
  SelectObject(PaintDC, hpen);
  DeleteObject(SelectObject(PaintDC, OldBrush));

  OldBrush = (HBRUSH)SelectObject(PaintDC, CreateSolidBrush(RGB(96,0,83)));
  hpen = (HPEN)SelectObject(PaintDC, GetStockObject(NULL_PEN));
  Ellipse(PaintDC, 287, 19,310, 37);
  SelectObject(PaintDC, hpen);
  DeleteObject(SelectObject(PaintDC, OldBrush));

  SetBkMode(PaintDC, TRANSPARENT);
  SetTextColor(PaintDC, RGB(128,128,128));
  MainFontRec.lfHeight = MainFontRec.lfHeight*2;
  MainFontRec.lfWidth = floor(MainFontRec.lfWidth * 1);
  SelectObject(PaintDC, CreateFontIndirect(&MainFontRec));
  SetTextColor(PaintDC, RGB(0,0,255));
  TextOut(PaintDC, 152,10, "Net 1.0(TM)", strlen("Net 1.0(TM)"));
  SetTextColor(PaintDC, RGB(0,0,0));
  TextOut(PaintDC, 135, 30,"Version 1.0.2950", strlen("Version 1.0.2950"));
  SetTextColor(PaintDC, RGB(0,87,0));
  TextOut(PaintDC, 90, 50,"Copyright © 2000,RSG Corp.", strlen("Copyright © 2000,R&R Corp."));
  SetTextColor(PaintDC, RGB(255,25,75));
  TextOut(PaintDC, 130, 70,"All right reserved", strlen("All right reserved"));

// GetClientRect(HWindow, &R);
 SelectObject(PaintDC, GetStockObject(NULL_BRUSH));
 SetWindowText(HWindow,"О ПРОГРАММЕ . . . NET.");
 DeleteObject(SelectObject(PaintDC, GetStockObject(SYSTEM_FONT)));

 ReleaseDC(HWindow,PaintDC);// RestoreDC(PaintDC, -1);
 EndPaint(HWindow, &PaintInfo);

};

THelpWindow::THelpWindow(PTWindowsObject AParent) :
   TWindow(AParent, "О ПРОГРАММЕ . .")
{
  DisableAutoCreate();

 Attr.Style |= WS_POPUPWINDOW |WS_SYSMENU | WS_CAPTION |
                  WS_THICKFRAME |WS_DLGFRAME;
 Attr.X = 50;    Attr.Y = 50;     Attr.W = 500;      Attr.H = 360;

 LineWindow=new TLineWindow(this);
 ArtyWindow=new TArtyWindow(this);

//version 1.1
/* new TStatic(this, -1, "Сеть 1.0(TM)", 185, 10,165, 16, 0);
// new TStatic(this, -1, "Версия 1.0.2950", 170, 30, 135, 16, 0);
// new TStatic(this, -1, "Copyright © 2000,&RSG Corporation", 130, 50, 230, 16, 0);
// new TStatic(this, -1, "Все права защищены", 165, 70, 150, 16, 0);
*/  //version 1.2
/* new TStatic(this, -1, "Сеть 1.0(TM)", 155, 10,165, 16, 0);
 new TStatic(this, -1, "Версия 1.0.2950", 135, 30, 135, 16, 0);
 new TStatic(this, -1, "Copyright © 2000,&RSG Corporation", 95, 50, 230, 16, 0);
 new TStatic(this, -1, "Все права защищены", 130, 70, 150, 16, 0);
*/
new TButton(this, ID_BUTTON1ABOUT, "Закрыть", 400,10, 80, 30, TRUE);
new TButton(this, ID_BUTTON2ABOUT, "Сведения", 400, 55, 80, 30, FALSE);

Pchar Edit0Str; Edit0Str=
 "     Авторы:\r\n\t  Родионова Е.,  Гордина Н.,  Свириденко О.\r\n" 
 " Идея \r\n\t - Зверева Т.В.(кафедра ПМИ).\r\n"
 " Технический Дизайн и поддержка \r\n\t - фирма  jCH77(681000,КнААПО).\r\n"
 "                        Огромное спасибо!\r\n-Завозину Ж.Г.- за  внимательность, '5' и заботу;\r\n"
  "-Зверевой Т.В. - за творческую поддержку над дипломом;\r\n"
  "-моим подружкам, парням и друзьям -в КнАГТУ\r\n"
  "                                и всем ,всем,всем.........ПОКА!!!.\r\n"
  "\r\n\t\t Москва, Россия. (8/11/2000)\r\n";
//version 2.1
 Edit0 = new TEdit(this,ID_EDIT1ABOUT, Edit0Str, 105, 110,  375, 128,255,TRUE);
//version 2.2
// new TStatic(this,-1,Edit0Str, 35, 110, 425, 128,0);

 GroupBox0 = new TGroupBox(this, ID_GROUPBOX0ABOUT, "Регистрация",
    105,250, 375, 70);

 new TStatic(this, -1, "Лицензией на данный продукт обладает :..", 115, 270, 363, 16, 0);
 new TStatic(this, -1, "Серийный номер............................02067988.01971-21", 115, 290, 363, 16, 0);
 
  ListBox = new TListBox(this, ID_LISTBOX_ABOUT, 20, Attr.H+20, 180, 80);
  new TButton(this, ID_BUTTON_ABOUT, "Имена", 220, Attr.H+20, 60, 30, TRUE);

  new TStatic(this, -1, "Буквы Вашего Имени", 220, Attr.H+55, 160, 20, 0);
  Edit = new TEdit(this, ID_EDIT_ABOUT, "", 220, Attr.H+75, 260, 90, 40, TRUE);
 
  EnableKBHandler();

 }

void  THelpWindow::WMGetMinMaxInfo( TMessage& Msg )
{
  // Limit the minimum size of the window to 500x360, so the Win don't   get too small 
  ((POINT far *)Msg.LParam)[3].x = 500; ((POINT far *)Msg.LParam)[3].y = 360;
  ((POINT far *)Msg.LParam)[4].x = 500;  ((POINT far *)Msg.LParam)[4].y = 555;
};

void THelpWindow::HandleButton2Msg(RTMessage )
 {  CloseWindow(); }

void THelpWindow::HandleButton3Msg(RTMessage)
 { GetApplication()->MakeWindow(new TSysInfoWindow(this,"SysInfo"));  }

/*********************************************/
void THelpWindow::GetWindowClass(WNDCLASS& vrWndClass)
{
  TWindow::GetWindowClass(vrWndClass);
  vrWndClass.style = CS_NOCLOSE;
  vrWndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
  vrWndClass.hIcon = LoadIcon(GetApplication()->hInstance, "MFileApp");
}

/* Colorize:Allows background to show through corners of  buttons, uses .... text
   on ....background in the display, and sets  the dialog background to... . */
void THelpWindow::WMControlColor(TMessage& Msg)
{  
  switch (Msg.LP.Hi) {
    case CTLCOLOR_BTN:
      Msg.Result = (LRESULT)GetStockObject(NULL_BRUSH);
      break;
    case CTLCOLOR_STATIC:
      SetTextColor((HDC)Msg.WParam,RGB(0, 0, 0) );
      SetBkMode((HDC)Msg.WParam, TRANSPARENT);
      Msg.Result = (LRESULT)GetStockObject(GRAY_BRUSH);
      break;
    case CTLCOLOR_DLG:
      SetBkMode((HDC)Msg.WParam, TRANSPARENT);
      Msg.Result = (LRESULT)GetStockObject(GRAY_BRUSH);
      break;
    default: DefWndProc(Msg);
  }
}


void THelpWindow::SetupWindow()
{
  TWindow::SetupWindow();
 
  int Result;  Result = IDRETRY;
  while ((SetTimer(HWindow, 0, 50, NULL) == 0) && (Result == IDRETRY)) {
    Result = MessageBox(GetFocus(),"Could not Create Timer", "Help About", MB_RETRYCANCEL);
  };
  if (Result == IDCANCEL)  PostQuitMessage(0);

  ListBox->AddString("Е");
  ListBox->AddString("Л");
  ListBox->AddString("Н");
  ListBox->AddString("А");
  ListBox->AddString("Ж");
  ListBox->AddString("И");
  ListBox->AddString("T");
  ListBox->AddString("В");
  ListBox->AddString("Ю");
  ListBox->SetSelIndex(0);

};

void THelpWindow::HandleListBoxMsg(RTMessage Msg)
{  char SelString[25];
  if ( Msg.LP.Hi == LBN_DBLCLK )
  {   ListBox->GetSelString(SelString, sizeof(SelString));
       FillEdit(SelString);
    }
}

void THelpWindow::HandleButton1Msg(RTMessage)
{   char SelString[25];
  ListBox->GetSelString(SelString, sizeof(SelString));
  FillEdit(SelString);
}

void THelpWindow::FillEdit(Pchar SelString)
{
  Pchar HelpStr;

  if ( strcmp(SelString, "Е") == 0 )
  {  HelpStr =
       "Стремление к самовыражению ,\r\n"
       "потребность к взаимному обмену\r\n"
       "обмену идеями , склонность к роли\r\n"
       "посредника в конфликтных\r\n"
       "ситуациях ,проницательность ,\r\n"
       "иногда болтливость.\r\n"
       "   ";
  };
  if ( strcmp(SelString, "Л") == 0 )
  {  HelpStr =
       "Утонченное понимание прекрасного,\r\n"
       "незаурядные артистические и \r\n"
       "художественные способности,\r\n"
       "желание поделиться знаниями\r\n"
       "и ощущениями с партнером,\r\n"
       "предупреждение о недопустимости\r\n"
       "прожигания жизни в пустую.\r\n"
       "  ";
  }
  if ( strcmp(SelString, "Н") == 0 )
  {  HelpStr =
       "Знак протеста , неприятие всего\r\n"
       "подряд без разбора ,внутренная\r\n"
       "сила, острый критический ум,\r\n"
       "стремление к духовному и физическому\r\n"
       "здоровью, старательность и\r\n"
       "усердие в работе.";
  };
  if ( strcmp(SelString, "А") == 0 )
  {  HelpStr =
       "Символ начала, сила и желание\r\n"
       "что-то начать и осуществить, \r\n"
       "стремление к духовному и \r\n"
       "физическому комфортному\r\n"
       "состоянию.";
  };
  if ( strcmp(SelString, "Ж") == 0 )
  {  HelpStr =
       "Богатый внутренний мир,\r\n"
       "некоторая скрытность,\r\n"
       "желание как импульс\r\n"
       "к действию .\r\n"
       " ";
  };
  if ( strcmp(SelString, "И") == 0 )
  {  HelpStr =
       "-утонченность, чувствительность,\r\n"
       "доброта, устремленность к\r\n"
       "гармонии с окружающим\r\n"
       "миром, романтическая\r\n"
       "мягкая натура.\r\n"
       " ";
  };
  if (strcmp(SelString, "T") == 0 )
  {  HelpStr =
       "Творческая личность, чувствительная\r\n"
       "натура, склонность к интуиции, стремление\r\n"
       "к постоянному поиску правды, желания\r\n"
       "не всегда соизмеряются с возможностями,\r\n"
       "символ креста напоминает о быстротечности\r\n"
       "жизни, и поэтому не следует откладывать дела.\r\n"
       " ";
    };
  if ( strcmp(SelString, "В") == 0 )
  {  HelpStr =
       "легкость в общении,\r\n"
       "умение быстро установить\r\n"
       "контакт, реальное восприятие\r\n"
       "действительности, единение\r\n"
       "с природой, творческий\r\n"
       "характер личности.\r\n"
       " ";
  };
  if ( strcmp(SelString, "Ю") == 0 )
  {  HelpStr =
       "Склонность к идеалам\r\n"
       "всеобщего равенства, и\r\n"
       "братства, стремление к\r\n"
       "истине, способность к\r\n"
       "самопожертвованию\r\n"
       " и , одновременно, к\r\n"
       "жестоким поступкам.\r\n"
       " ";
  };
  Edit->SetText(HelpStr);
}






