
// ObjectWindows - (C) Copyright 2000  by jCH77

#include <owl.h>
#include <windowsx.h>
#include <string.h>
#include <listbox.h>
#include <edit.h>
#include <button.h>
#include <checkbox.h>
#include <radiobut.h>
#include <groupbox.h>
#include <combobox.h>
#include <dir.h>

extern int NetFileCalc(char *,char *,char *,int );
extern int NetFileTest(char *,int ,int * );
//extern int NetCalc(char *,char *,char *,char *,int ,int ,int ,int ,int ,int );
//#include "Net.cpp"

const WORD ID_EDIT1NET=1001;
const WORD ID_EDIT2NET=1002;
const WORD ID_EDIT3NET=1003;
const WORD ID_BUTTON1NET = 1010;
const WORD ID_BUTTON2NET = 1011;
const WORD ID_BUTTON3NET = 1012;
const WORD ID_BUTTON4NET = 1013;
const WORD ID_BUTTON5NET = 1014;
const WORD ID_BUTTON6NET = 1015;
const WORD ID_BUTTON7NET = 1016;
const WORD ID_RBUTTON1NET = 1021;
const WORD ID_RBUTTON2NET = 1022;
const WORD ID_RBUTTON3NET = 1023;
const WORD ID_RBUTTON4NET = 1024;
const WORD ID_RBUTTON5NET = 1025;
const WORD ID_RBUTTON6NET = 1026;
const WORD ID_RBUTTON7NET = 1027;
const WORD ID_CHECKBOX1 = 1040;
const WORD ID_GROUPBOX0NET=1050;
const WORD ID_GROUPBOX1NET = 1051;
const WORD ID_GROUPBOX2NET = 1052;
const WORD ID_GROUPBOX3NET = 1053;
const WORD ID_GROUPBOX4NET=1054;
const WORD ID_COMBO1NET = 1060;

char nameLength[255],namePrice[255],nameIntense[255];
int FlagMinMax, FlagCase, FlagSpot, FlagCalc, MaxStep;

class TNetWindow : public TWindow
{ HBRUSH BlueBrush;char strEdit[255];
public:
  PTStatic Static1,Static2,Static3, Static4; 
  PTEdit Edit1,Edit2,Edit3;
  TRadioButton *RTButton1, *RTButton2,*RTButton3,*RTButton4,*RTButton5,*RTButton6,*RTButton7;
  TCheckBox *CheckBox1;
  TGroupBox *GroupBox0,*GroupBox1, *GroupBox2, *GroupBox3,*GroupBox4;
  TComboBox *Combo1;
  TNetWindow(PTWindowsObject AParent);
  virtual TNetWindow:: ~TNetWindow() { DeleteObject(BlueBrush); ; };
  virtual  void SetupWindow();
  virtual LPSTR GetClassName() {  return "TNetWindow";  };
  virtual void GetWindowClass(WNDCLASS&);
  virtual void HandleButtonMsg1(RTMessage Msg)= [ID_FIRST + ID_BUTTON1NET];
  virtual void HandleButtonMsg2(RTMessage Msg,HWND HWindow)= [ID_FIRST + ID_BUTTON2NET];
  virtual void HandleButtonMsg3(RTMessage Msg)= [ID_FIRST + ID_BUTTON3NET];  
  virtual void HandleButtonMsg4(RTMessage Msg)= [ID_FIRST + ID_BUTTON4NET]; 
  virtual void HandleButtonMsg5(RTMessage Msg)= [ID_FIRST + ID_BUTTON5NET]; 
  virtual void HandleButtonMsg6(RTMessage Msg)= [ID_FIRST + ID_BUTTON6NET]; 
  virtual void HandleButtonMsg7(RTMessage Msg)= [ID_FIRST + ID_BUTTON7NET]; 
//  virtual void HandleGroupBoxMsg(RTMessage Msg)=[ID_FIRST + ID_GROUPBOX1NET];

 virtual void WMControlColor(TMessage& Msg) = [WM_FIRST + WM_CTLCOLOR];
 virtual void WMPaint(TMessage& Msg)  = [WM_FIRST + WM_PAINT];
 virtual void WMGetMinMaxInfo( TMessage& ) = [WM_FIRST + WM_GETMINMAXINFO];
 virtual void WMSize( TMessage& ) = [WM_FIRST + WM_SIZE];

 virtual int NetCalc(char *,char *,char *,char *,int ,int ,int ,int ,int ,int ,RTMessage );

};

void  TNetWindow::HandleButtonMsg1(RTMessage)
{
  DeleteObject(BlueBrush);     CloseWindow();
}

#include "NetObj.cpp"

void  TNetWindow::HandleButtonMsg2(RTMessage Msg,HWND )
{
char nameMatrixNet[255]; int FlagNet=-1000;strEdit[0]='\0';

int  n,FlagMinMax ,FlagCase,FlagSpot, FlagCalc,  MaxStep;

  if ( CheckBox1->GetCheck()== BF_CHECKED )  FlagCalc=1;else  FlagCalc=0;
  if (RTButton1->GetCheck()== BF_CHECKED) FlagMinMax=1;else FlagMinMax=2;
  if(RTButton3->GetCheck()== BF_CHECKED)  FlagSpot=1; else FlagSpot=2;
  if (RTButton5->GetCheck()== BF_CHECKED ) FlagCase=1;
  if(RTButton6->GetCheck()== BF_CHECKED)  FlagCase=2; 
  if(RTButton7->GetCheck()== BF_CHECKED)  FlagCase=3;
  Combo1->GetText((LPSTR)strEdit,10 ); MaxStep=atoi(strEdit);
  Static4->SetText((LPSTR)":0");  

nameLength[0]='\0';Edit1->GetLine((LPSTR) nameLength,255, -1);
namePrice[0]='\0';Edit2->GetText((LPSTR) namePrice, 255);
nameIntense[0]='\0';Edit3->GetText((LPSTR) nameIntense, 255);

if ((nameLength[0]!='\0')&&(namePrice[0]!='\0')&&(nameIntense[0]!='\0')) 
{ 
strEdit[0]='\0';
 n=NetFileCalc(nameLength,namePrice,nameIntense,FlagMinMax );
switch(n)
{  case -1: _fstrcat(strEdit,"�� ���� ������� ���� ������\n");_fstrcat(strEdit,nameLength);break;
    case -11:_fstrcat(strEdit,"������� �� ������� ��������(n x n)\n����������� ������ ������\n����=");_fstrcat(strEdit,nameLength); break;
    case -2:_fstrcat(strEdit,"�� ���� ������� ���� ������\n");_fstrcat(strEdit,namePrice);break;
    case -22: _fstrcat(strEdit,"������� �� ������� ��������(n x n)\n����������� ������ ������\n����=");_fstrcat(strEdit,namePrice);break;
    case -23:_fstrcat(strEdit,"!������ ������������ ������:\n��������� ������ ����\nC[i,j]>=0 (������-> MIN )!\nC[i,j]<=0 (������-> MAX )!");break;
    case -3:_fstrcat(strEdit,"�� ���� ������� ���� ������\n");_fstrcat(strEdit,nameIntense);break;
    case -33:_fstrcat(strEdit,"������� �� ������� ��������(n x 1)\n����������� ������ ������\n����=");_fstrcat(strEdit,nameIntense);break;
    case   -4: _fstrcat(strEdit,"������ ������������ ������\n������� �� ������� �������� -->\n���������� ����������� ��� [(n x n)],\n��������� [(n x n)],\n������������� [(n x 1)],\n����������� ������ ������");break;
default :
   if(n>0)
   {  strEdit[0]='\0';_fstrcat(strEdit,buffilepath);_fstrcat(strEdit,"\\_Mnet.prn\0");
       nameMatrixNet[0]='\0'; _fstrcat(nameMatrixNet,strEdit);
       FlagNet=NetCalc(nameLength,namePrice,nameIntense,
                     nameMatrixNet,n, FlagMinMax ,FlagCase,FlagSpot, FlagCalc, MaxStep,Msg);
       strEdit[0]='\0';  
       switch(FlagNet)
       { case  0: _fstrcat(strEdit,"������� ������� ������\nStatus:������\n����=");_fstrcat(strEdit,nameMatrixNet);break; 
          case -1:_fstrcat(strEdit,"�� ���� ������� ����� ������\n����������� ������ ������");break;
          case -2:_fstrcat(strEdit,"�� ���� ������� �������� ���� ������\n����=");_fstrcat(strEdit,nameMatrixNet);break;
          case -3:_fstrcat(strEdit,"���� ������\n");break;
         }
      }  
   break;
  }
  if (FlagNet!=-23) MessageBox(GetFocus(),strEdit,"������� ������",MB_OK|MB_ICONEXCLAMATION); 
  if(FlagNet==0) 
  {  //CloseWindow();                                                       //this    HWindow
      GetApplication()->MakeWindow(new TFileWindow(Parent,"NET",nameMatrixNet));
     }
 
 }
strEdit[0]='\0';
}

void  TNetWindow::HandleButtonMsg3(RTMessage)
{ //(BF_CHECKED, BF_UNCHECKED, or BF_GRAYED).  
  if ( CheckBox1->GetCheck() != BF_CHECKED )  CheckBox1-> SetCheck((WORD)BF_CHECKED);
//  RTButton1->SetCheck((WORD)BF_CHECKED); RTButton2->SetCheck((WORD) BF_UNCHECKED);
  RTButton3->SetCheck((WORD)BF_CHECKED);//FlagSpot
  RTButton4->SetCheck((WORD) BF_UNCHECKED);
  RTButton5->SetCheck((WORD) BF_UNCHECKED);
  RTButton6->SetCheck((WORD)BF_CHECKED);// FlagCase=2;
  RTButton7->SetCheck((WORD) BF_UNCHECKED);
  Combo1->SetText((LPSTR)"500"); 
  Static4->SetText((LPSTR)":0");  
}

void  TNetWindow::HandleButtonMsg4(RTMessage)
{  /* Perform file operations. */ int i;strEdit[0]='\0';int NumP;
 if ( GetApplication()->ExecDialog(new TFileDialog(this, SD_FILEOPEN,
                             _fstrcpy(nameLength, "*.prn"))) == IDOK )
 {  /*Handle notification messages from button*/
     Edit1->DeleteLine(-1); Edit1->Insert((LPSTR)nameLength);
    i=NetFileTest(nameLength,1,&NumP);
    switch(i)
    { case -1:_fstrcat(strEdit,"St:don't exist");break;
       case -2: sprintf( strEdit,"St:no M[n x n] Num=%d ",NumP);break;
        default :sprintf( strEdit,"St:[%d x %d]",i,i); break;
       }
    Static1->SetText((LPSTR)strEdit);   
 }  else  {/* Edit1->DeleteLine(-1);  nameLength[0]='\0';*/ ;}
strEdit[0]='\0';
}

void  TNetWindow::HandleButtonMsg5(RTMessage)
{  int i;strEdit[0]='\0';int NumP;
 if ( GetApplication()->ExecDialog(new TFileDialog(this, SD_FILEOPEN,
                             _fstrcpy(namePrice, "*.prn"))) == IDOK )
 { Edit2->DeleteLine(-1); Edit2->Insert((LPSTR)namePrice); 
    i= NetFileTest(namePrice,1,&NumP );
    switch(i)
    { case -1:_fstrcat(strEdit,"St:don't exist");break;
       case -2: sprintf( strEdit,"St:no M[n x n] Num=%d ",NumP);break;
        default :sprintf( strEdit,"St:[%d x %d]",i,i); break;
       }
     Static2->SetText((LPSTR)strEdit);   
  }  else { ;}
strEdit[0]='\0';
}
void  TNetWindow::HandleButtonMsg6(RTMessage)
{  int i;strEdit[0]='\0';int NumP;
 if ( GetApplication()->ExecDialog(new TFileDialog(this, SD_FILEOPEN,
                             _fstrcpy(nameIntense, "*.prn"))) == IDOK )
 {  Edit3->DeleteLine(-1); Edit3->Insert((LPSTR)nameIntense);
     i=NetFileTest(nameIntense,2,&NumP);
     switch(i)
     { case -1:_fstrcat(strEdit,"St:don't exist");break;
        case -2: sprintf( strEdit,"St:no M[n x 1] Num=0");break;
         default :sprintf( strEdit,"St:[%d x 1]",i); break;
       }
     Static3->SetText((LPSTR)strEdit);   
   }  else{ ; }
strEdit[0]='\0';
}

void  TNetWindow::HandleButtonMsg7(RTMessage) 
{  WinHelp( GetFocus(), "MNETAPP.HLP",HELP_CONTEXT , ID_Topic_LineNetBase);
}

/*void  TNetWindow::HandleGroupBoxMsg(RTMessage)
{ char TextBuff[20];
  if ( RTButton1->GetCheck() == BF_CHECKED ) GetWindowText(RTButton1->HWindow, TextBuff, sizeof(TextBuff));
  else  GetWindowText(RTButton2->HWindow, TextBuff, sizeof(TextBuff));
  MessageBox(HWindow, TextBuff, "You have selected:", MB_OK);
}*/

void TNetWindow::GetWindowClass(WNDCLASS& varWndClass)
{
  TWindow::GetWindowClass(varWndClass);
  varWndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
  varWndClass.hIcon = 0;  // we'll paint our own icon when minimized, thank you.
}

void TNetWindow::SetupWindow()
{
  TWindow::SetupWindow();

  int Result;  Result = IDRETRY;
  while ((SetTimer(HWindow, 0, 50, NULL) == 0) && (Result == IDRETRY)) {
    Result = MessageBox(GetFocus(),"Could not Create Timer", " ? NET", MB_RETRYCANCEL);
  };
  if (Result == IDCANCEL)  PostQuitMessage(0);

  Combo1->AddString("9999");  Combo1->AddString("5000");
  Combo1->AddString("1000");  Combo1->AddString("500");
  Combo1->AddString("250");    Combo1->AddString("50");
  Combo1->SetText((LPSTR)"500"); 
  CheckBox1-> SetCheck((WORD)BF_CHECKED);
  RTButton1->SetCheck((WORD)BF_CHECKED);
  RTButton3->SetCheck((WORD)BF_CHECKED);//FlagSpot
  RTButton6->SetCheck((WORD)BF_CHECKED);//FlagCase=2;
  Static4->SetText((LPSTR)":0");  
}

 TNetWindow:: TNetWindow(PTWindowsObject AParent) :
  TWindow(AParent, "������� ������ [���������]")
{
  DisableAutoCreate();

  Attr.Style |= WS_POPUPWINDOW | WS_CAPTION| WS_DLGFRAME;
  Attr.X = 50;    Attr.Y = 50;     Attr.W = 655;      Attr.H = 330;
 
 GroupBox0 = new TGroupBox(this, ID_GROUPBOX0NET, "����� ������",
    20,20, 610, 130);

new TStatic(this, -1, "���������� ����������� ���->", 25, 40,130, 30, 0);
Edit1 = new TEdit(this,ID_EDIT1NET, "", 160, 40, 300, 30,255,FALSE);
new TButton(this, ID_BUTTON4NET, "...->",461, 40,50, 30, TRUE);
new TStatic(this, -1, "����->", 25, 75, 130, 30, 0);
Edit2 = new TEdit(this,ID_EDIT2NET, "", 160, 75,300, 30,255,FALSE);
new TButton(this, ID_BUTTON5NET, "...->",461, 75, 50, 30, TRUE);
new TStatic(this, -1, "�������������->", 25, 110, 130, 30, 0);
Edit3 = new TEdit(this,ID_EDIT3NET, "", 160, 110,300, 30,255, FALSE);
new TButton(this, ID_BUTTON6NET, "...->",461, 110, 50, 30,TRUE);

Static1=new TStatic(this,-1, "St:0", 512, 40, 113, 30, 0);
Static2=new TStatic(this, -1, "St:0",512, 75, 113, 30, 0);
Static3=new TStatic(this,-1, "St:0", 512, 110, 113, 30, 0);

GroupBox4 = new TGroupBox(this, ID_GROUPBOX4NET, "", 20,145,500, 145);

  GroupBox1 = new TGroupBox(this, ID_GROUPBOX1NET, "��� ������",30,160, 110, 80);
  RTButton1 = new TRadioButton(this, ID_RBUTTON1NET, "min", 40, 185, 80, 10, GroupBox1);
  RTButton2 = new TRadioButton(this, ID_RBUTTON2NET, "max", 40, 215, 80, 10, GroupBox1);

  GroupBox2 = new TGroupBox(this, ID_GROUPBOX2NET, "����������� �������",
   150, 160, 160, 80);
  RTButton3 = new TRadioButton(this, ID_RBUTTON3NET, "� ������",
    160, 180, 80, 24, GroupBox2);
  RTButton4 = new TRadioButton(this, ID_RBUTTON4NET, "� �����",
    160, 210, 80, 24, GroupBox2);

  GroupBox3 = new TGroupBox(this, ID_GROUPBOX3NET, "����� �������",
    320, 160, 190, 80);
  RTButton5 = new TRadioButton(this, ID_RBUTTON5NET, "� ������� �����������",
    330, 180, 175, 16, GroupBox3);
  RTButton6 = new TRadioButton(this, ID_RBUTTON6NET, "� ������� ��������",
    330, 200, 175, 16, GroupBox3);
 RTButton7 = new TRadioButton(this, ID_RBUTTON7NET, "��. �������",
    330, 220, 175, 16, GroupBox3);

 Combo1 = new TComboBox(this, ID_COMBO1NET, 30 ,250,60, 100, CBS_DROPDOWNLIST, 0);
 new TStatic(this, -1, " ��������->STOP ", 90,250,125,16, 0);

  CheckBox1 = new TCheckBox(this, ID_CHECKBOX1, "���������� ������",
    225,250, 150, 26, NULL);
  
 new TButton(this, ID_BUTTON3NET, "�� ���������..",385,250,120, 30, FALSE);

 new TButton(this, ID_BUTTON7NET, "�������...",530,155,100, 30, FALSE);
 Static4=new TStatic(this,-1, ":0", 530, 199,100, 20, 0);
 new TButton(this, ID_BUTTON2NET, "����������...",530,220,100, 30, FALSE);
 new TButton(this, ID_BUTTON1NET, "������",530, 260, 100, 30, TRUE);

 EnableKBHandler();

}

void  TNetWindow::WMGetMinMaxInfo( TMessage& Msg )
{// Limit the minimum size of the window to [width x heigth], so the Win don't   get too small 
  ((POINT far *)Msg.LParam)[3].x = 655;  ((POINT far *)Msg.LParam)[3].y = 330;
  ((POINT far *)Msg.LParam)[4].x = 655;  ((POINT far *)Msg.LParam)[4].y = 330;
};

void TNetWindow::WMSize( TMessage& Msg )
{
 TWindow::WMSize(Msg);
 if ((Msg.WParam == SIZENORMAL) || (Msg.WParam == SIZEFULLSCREEN))
   { ; };
};

void  TNetWindow::WMControlColor(TMessage& Msg)
{
  switch (Msg.LP.Hi) {
    case CTLCOLOR_BTN:
      Msg.Result = (LRESULT)GetStockObject(NULL_BRUSH);
      break;
    case CTLCOLOR_STATIC:
	SetTextColor((HDC)Msg.WParam,RGB(252, 245, 56) );
	SetBkMode((HDC)Msg.WParam, TRANSPARENT);
	Msg.Result = (LRESULT)GetStockObject(BLACK_BRUSH);//BLACK_BRUSH
      break;
    case CTLCOLOR_DLG:
	SetBkMode((HDC)Msg.WParam, TRANSPARENT);
	Msg.Result = (LRESULT)BlueBrush;
      break;
    default: DefWndProc(Msg);
  }
}
 
void   TNetWindow::WMPaint(TMessage&)
{      //COLORREF RGB(cRed, cGreen, cBlue)
  HBRUSH OldBrush;      HPEN OldPen;   RECT R;    PAINTSTRUCT PS;

  BeginPaint(HWindow, &PS);
  OldBrush = (HBRUSH)SelectObject(PS.hdc, CreateSolidBrush(RGB(10, 250,120)));//RGB_RED
  OldPen = (HPEN)SelectObject(PS.hdc, GetStockObject(NULL_PEN));

 GetClientRect(HWindow, &R);
  R.top = R.left;
  OffsetRect(&R, -R.left/3, -R.left/3);
  OldBrush = (HBRUSH)SelectObject(PS.hdc, CreateSolidBrush(RGB(255, 130,255)));
  Ellipse(PS.hdc, R.left, R.top, R.right, R.bottom);

  SelectObject(PS.hdc, OldPen);
  DeleteObject(SelectObject(PS.hdc, OldBrush));
  EndPaint(HWindow, &PS);

}

