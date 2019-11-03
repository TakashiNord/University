
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
 Ёто - одно из нескольких мест где пор€док обработки сообщений важный. 
 ќбычный пор€док, ProcessDlgMsg, ProcessMDIAccels, ProcessAccels, позвол€ет 
приложению определ€ть акселераторы, которые не прервут клавиатуру, 
обрабатывающуюс€ в диалогах ребенка.  ¬ этом случае, диалог €вл€етс€
 приложением.
  ≈сли мы использовали невыполнение ProcessAppMsg, затем клавиатурный 
вручитель, ProcessDlgMsg, должен возвращать ¬≈–Ќќ и акселераторы не должны
 быть обработаны.  ¬ этом случае, что мы - зан€тие €вл€етс€ сейф из-за того, что
 мы не определ€ем любые акселераторы, которые противоречат с клавиатурой
 ќкна, обрабатывающейс€ дл€ диалогов.  ѕолучение этого изменени€ позвол€ет 
нам использовать ввод данных с клавиатуры дл€ калькул€тора.  “акже, из-за того,
 что это - наше апп, мы знаем, что, это не апп MDI, следовательно нам не нужно
 вызывать ProcessMDIAccels (хот€ это не должно ранить, чтобы сделать так).
 */

BOOL TMDIFileApp::ProcessAppMsg(LPMSG Message)
{
  return (ProcessAccels(Message) || ProcessDlgMsg(Message) || ProcessMDIAccels(Message));
}

