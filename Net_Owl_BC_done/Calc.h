

// ObjectWindows - (C) Copyright 2001 by 

/* Simple four function calculator */

#include <dialog.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <string.h>

/* Number of digits in calculator display */  const int DisplayDigits = 15;
/* Calculator state */  enum TCalcState {CS_FIRST, CS_VALID, CS_ERROR};
/* Control ID of display static text */ const int ID_DISPLAY = 400;

/* Calculator dialog window object */
class TCalc : public TDialog {
private:

public:
/* Calculator constructor.Create blue brush for calculator background,and do a clear command. */
    TCalc(PTWindowsObject AParent,LPSTR ATitle): TDialog(AParent,ATitle)
      { BlueBrush = CreateSolidBrush(RGB(0,0,255));  //const long RGB_BLUE   = 0x00FF0000L;
         Clear();
          EnableKBHandler();
       };

    TCalcState CalcStatus;    char Number[DisplayDigits + 1];
    BOOL Negative;   char Operator;    double Operand;    HBRUSH BlueBrush;
/* Calculator destructor.  Delete the background brush. */
    virtual ~TCalc() { DeleteObject(BlueBrush); } ;
/* We're changing the window class so we must supply a new class name.*/
    virtual LPSTR GetClassName() {  return "TCalc";  };
    virtual void GetWindowClass(WNDCLASS&);
    virtual void WMControlColor(TMessage& Msg) = [WM_FIRST + WM_CTLCOLOR];
    virtual void WMPaint(TMessage& Msg)  = [WM_FIRST + WM_PAINT];
    virtual void DefChildProc(TMessage& Msg);
    virtual void DefCommandProc(TMessage& Msg);
    void FlashButton(char Key);       void Error();
    void SetDisplay(double R);        void GetDisplay(double& R);
    void CheckFirst();                void InsertKey(char Key);
    void CalcKey(char Key); //char
    void Clear();
    virtual void UpdateDisplay();

};

/* The calculator has its own icon which is installed here. */
void TCalc::GetWindowClass(WNDCLASS& AWndClass)
{
  TDialog::GetWindowClass(AWndClass);
  AWndClass.cbWndExtra= DLGWINDOWEXTRA;
  AWndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
  AWndClass.hIcon = 0;  // we'll paint our own icon when minimized, thank you.
}

/* Flash a button with the value of Key.Looks exactly like a click of the button with the mouse. */
void TCalc::FlashButton(char Key)
{
  HWND Button;    int Delay; 

  if ( Key == 0x0D) Key = '=';  // Treat Enter like '='
  Button = GetDlgItem(HWindow, toupper(Key));
  if ( Button )
  { SendMessage(Button, BM_SETSTATE, 1, 0);
     for (Delay = 1; Delay <= 30000; ++Delay) {  ;  }
    SendMessage(Button, BM_SETSTATE, 0, 0);
  }
}

/* Rather than handle each button individually with child ID  response methods,
 it is possible to handle them all at once with the default child procedure. */
void TCalc::DefChildProc(TMessage& Msg)
{ 
  if ( (Msg.WP.Hi == 0) && (Msg.LP.Hi == BN_CLICKED) )  CalcKey(Msg.WP.Lo);
  TDialog::DefChildProc(Msg);
}

/* Rather than handle each accelerator individually with  command ID response methods,
 it is possible to handle them  all at once with the default command procedure. */
void TCalc::DefCommandProc(TMessage& Msg)
{
  if ( Msg.WP.Hi == 0 )
  {   
    if  (Msg.WP.Lo==0x02)  { FlashButton('C');CalcKey('C');  }       //VK_ESCAPE
    else { 
        FlashButton(Msg.WP.Lo); /* flash button as if it were pushed */
        CalcKey(Msg.WP.Lo);
              }
  }
  TDialog::DefCommandProc(Msg);
}

/* Set Display text to the current value. */
void TCalc::UpdateDisplay()
{ char S[DisplayDigits + 2];
  if ( Negative )   strcpy(S, "-");      else  S[0] = '\0';
  SetWindowText(GetDlgItem(HWindow, ID_DISPLAY), strcat(S, Number));
}

/* Clear the calculator. */
void TCalc::Clear()
{
  CalcStatus = CS_FIRST;  _fstrcpy(Number, "0");  Negative = FALSE;  Operator = '=';
}

void TCalc::Error()
{
  CalcStatus = CS_ERROR;  _fstrcpy(Number, "Error");   Negative = FALSE;
}

void TCalc::SetDisplay(double R)
{
  LPSTR First, Last;        int CharsToCopy;       char S[64];

// limit results of calculations to 7 digits to the right of the decimal point
  R = (floor(R * 10000000L + .5))/10000000L ;

  sprintf(S, "%0.10f", R);
  First = S;
  Negative = FALSE;
  if ( S[0] == '-' )  {    ++First;    Negative = TRUE;  }
  if ( _fstrlen(First) > DisplayDigits + 1 + 10 )     Error();
  else
  {
    Last = _fstrchr(First, 0);
    while ( Last[-1] == '0' )     --Last;
    if ( Last[-1] == '.' )    --Last;
    CharsToCopy =((DisplayDigits + 1)<((int)(Last - First)))?(DisplayDigits + 1):((int)(Last - First));
    _fstrncpy(Number, First, CharsToCopy);
    Number[CharsToCopy] = '\0';
  }
}

void TCalc::GetDisplay(double& R)
{
  R = atof(Number);    if ( Negative )    R = -R;
}

void TCalc::CheckFirst()
{
  if ( CalcStatus == CS_FIRST ) {CalcStatus = CS_VALID;    _fstrcpy(Number, "0");     Negative = FALSE;   }
}

void TCalc::InsertKey(char Key)
{
  int L;    L = _fstrlen(Number);
  if ( L < DisplayDigits )  {    Number[L] = Key;    Number[L + 1] = '\0';   }
}


/* Process calculator key. */
void TCalc::CalcKey(char Key) //char
{
  double R; //char buf;

 Key = toupper(Key);
//char Help[30];sprintf(Help,"%c\n%x ",Key,Key); MessageBox(HWindow,Help,"CalcKey",MB_OK);
//  if ( (CalcStatus == CS_ERROR) && (Key != 0x43) )    Key = ' ';
  if ( (CalcStatus == CS_ERROR) && ((Key != 'C')||(Key != 'c') ) )   Key = ' '; 
//  if ( Key >= '0' && Key <= '9' )
if ( (  Key == 0x30  || Key == 0x31  || Key == 0x32  || Key == 0x33  || Key == 0x34 ||
        Key == 0x35  || Key == 0x36  || Key == 0x37  || Key == 0x38  || Key == 0x39) 
  ||  (  Key == 0x60  || Key == 0x61  || Key == 0x62  || Key == 0x63  || Key == 0x64 ||
       Key == 0x65  || Key == 0x66  || Key == 0x67  || Key == 0x68  || Key == 0x69) )
  {  CheckFirst();
    if ( _fstrcmp(Number, "0") == 0 )      Number[0] = '\0';
    InsertKey(Key);
  }
  else
    if ( Key == '+' || Key == '-' || Key == '*' ||
         Key == '/' || Key == '=' || Key == '%' || Key == 0x0D )
    {
      if ( CalcStatus == CS_VALID )
      {
        CalcStatus = CS_FIRST;
        GetDisplay(R);
        if ( Key == '%' )
          if ( Operator == '+' || Operator == '-' )      R = Operand * R / 100;
          else
            if ( Operator == '*' || Operator == '/' )     R = R / 100;
        switch ( Operator ) {
          case '+': SetDisplay(Operand + R);                    break;
          case '-': SetDisplay(Operand - R);                  break;
          case '*': SetDisplay(Operand * R);                  break;
          case '/': if ( R == 0 ) Error();else SetDisplay(Operand / R);break;
        }
      }
      Operator = Key;
      GetDisplay(Operand);
    }
    else
      switch ( Key ) {
        case '.': CheckFirst(); if ( _fstrchr(Number, '.') == NULL ) InsertKey(Key); break;
        case 0x08: CheckFirst();
                  if ( _fstrlen(Number) == 1 )   _fstrcpy(Number, "0");
	          else   Number[_fstrlen(Number) - 1] = '\0';
                  break;
        case '_': Negative = !Negative;    break;
        case 'C': Clear();    break;
      }
  UpdateDisplay();
}

/* Colorize the calculator. Allows background to show through corners of  buttons, uses 
    yellow text on black background in the display, and sets the dialog background to blue. */
void TCalc::WMControlColor(TMessage& Msg)
{
  switch (Msg.LP.Hi) {
    case CTLCOLOR_BTN:
      Msg.Result = (LRESULT)GetStockObject(NULL_BRUSH);
      break;
    case CTLCOLOR_STATIC:
	SetTextColor((HDC)Msg.WParam, RGB(255,237,0));// const long RGB_YELLOW = 0x0000FFFFL;
	SetBkMode((HDC)Msg.WParam, TRANSPARENT);
	Msg.Result = (LRESULT)GetStockObject(BLACK_BRUSH);
      break;
    case CTLCOLOR_DLG:
	SetBkMode((HDC)Msg.WParam, TRANSPARENT);
	Msg.Result = (LRESULT)BlueBrush;
      break;
    default: DefWndProc(Msg);
  }
}

/* Even dialogs can have their backgrounds painted on.  This creates a red ellipse over the blue background. */
void TCalc::WMPaint(TMessage&)
{
  HBRUSH OldBrush;      HPEN OldPen;   RECT R;    PAINTSTRUCT PS;

  BeginPaint(HWindow, &PS);
  OldBrush = (HBRUSH)SelectObject(PS.hdc, CreateSolidBrush(RGB(255,0,0)));// const long RGB_RED    = 0x000000FFL;
  OldPen = (HPEN)SelectObject(PS.hdc, GetStockObject(NULL_PEN));
  GetClientRect(HWindow, &R);
  R.bottom = R.right;
  OffsetRect(&R, -R.right/4, -R.right/4);
  Ellipse(PS.hdc, R.left, R.top, R.right, R.bottom);
  SelectObject(PS.hdc, OldPen);
  DeleteObject(SelectObject(PS.hdc, OldBrush));
  EndPaint(HWindow, &PS);
}


