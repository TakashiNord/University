
_CLASSDEF(TMDIFileApp)

// Declare TMDIFileApp, a TApplication descendant
class _CLASSTYPE TMDIFileApp : public TApplication {
public:
    TMDIFileApp(LPSTR name, HINSTANCE hInstance,HINSTANCE hPrevInstance, LPSTR lpCmd,int nCmdShow)
	        : TApplication(name, hInstance,hPrevInstance, lpCmd, nCmdShow) {};
    virtual void InitMainWindow();
    virtual void InitInstance();
    virtual BOOL ProcessAppMsg(LPMSG AMessage);

};
/* This is one of the few places where the order of processing of
  messages is important.  The usual order, ProcessDlgMsg,
  ProcessMDIAccels, ProcessAccels, allows an application to define
  accelerators which will not break the keyboard handling in
  child dialogs.  In this case, the dialog is the application.
  If we used the default ProcessAppMsg, then the keyboard
  handler, ProcessDlgMsg, would return TRUE and accelerators
  would not be processed.  In this case, what we are doing is safe
  because we are not defining any accelerators which conflict
  with the Window's keyboard handling for dialogs.  Making this
  change allows us to use keyboard input for the calculator.  Also,
  because this is our app, we know that it is not an MDI app,
  therefore we do not need to call ProcessMDIAccels (although it
  would not hurt to do so).
 ��� - ���� �� ���������� ���� ��� ������� ��������� ��������� ������. 
 ������� �������, ProcessDlgMsg, ProcessMDIAccels, ProcessAccels, ��������� 
���������� ���������� ������������, ������� �� ������� ����������, 
���������������� � �������� �������.  � ���� ������, ������ ��������
 �����������.
  ���� �� ������������ ������������ ProcessAppMsg, ����� ������������ 
���������, ProcessDlgMsg, ������ ���������� ����� � ������������ �� ������
 ���� ����������.  � ���� ������, ��� �� - ������� �������� ���� ��-�� ����, ���
 �� �� ���������� ����� ������������, ������� ������������ � �����������
 ����, ���������������� ��� ��������.  ��������� ����� ��������� ��������� 
��� ������������ ���� ������ � ���������� ��� ������������.  �����, ��-�� ����,
 ��� ��� - ���� ���, �� �����, ���, ��� �� ��� MDI, ������������� ��� �� �����
 �������� ProcessMDIAccels (���� ��� �� ������ ������, ����� ������� ���).
 */

BOOL TMDIFileApp::ProcessAppMsg(LPMSG Message)
{
  return (ProcessAccels(Message) || ProcessDlgMsg(Message) || ProcessMDIAccels(Message));
}

