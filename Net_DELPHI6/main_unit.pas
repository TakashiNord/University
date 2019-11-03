unit main_unit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, ComCtrls, TabNotBk, Menus,
  about,crtpas, Tabs, StdCtrls, Spin,templatetable,
  seefile,Math, Buttons;

type
  TForm1 = class(TForm)
    MainMenu1: TMainMenu;
    A1: TMenuItem;
    N1: TMenuItem;
    N2: TMenuItem;
    N3: TMenuItem;
    N5: TMenuItem;
    N8: TMenuItem;
    OpenDialog1: TOpenDialog;
    TabbedNotebook1: TTabbedNotebook;
    SaveDialog1: TSaveDialog;
    Panel1: TPanel;
    GroupBox1: TGroupBox;
    Button2: TButton;
    Edit1: TEdit;
    RadioGroup1: TRadioGroup;
    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    Button3: TButton;
    GroupBox2: TGroupBox;
    Label1: TLabel;
    Button4: TButton;
    SpinEdit1: TSpinEdit;
    BitBtn1: TBitBtn;
    StaticText1: TStaticText;
    procedure N8Click(Sender: TObject);
    procedure N1Click(Sender: TObject);
    procedure N5Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
 private
    { Private declarations }
  public
    { Public declarations }
  end;
 
var
  Form1: TForm1;

  implementation
{$R *.dfm}

procedure TForm1.N8Click(Sender: TObject);
begin
     Form2.ShowModal;
end;

procedure TForm1.N1Click(Sender: TObject);
begin
     Application.Terminate ;
end;

procedure TForm1.N5Click(Sender: TObject);
begin
     Form3.ShowModal;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
    Form3.ShowModal;
end;

procedure TForm1.Button2Click(Sender: TObject);
var
 nameOut:string[255];
begin
OpenDialog1.DefaultExt := 'prn';
OpenDialog1.FilterIndex := 1; { start the dialog showing all files }
OpenDialog1.Filter := 'Text files (*.txt)|*.TXT|Mathcad files (*.prn)|*.prn|Data files (*.dat)|*.dat|All files (*.*)|*.*';
if OpenDialog1.Execute then
 begin
  nameOut := OpenDialog1.FileName;
  if nameOut='' then Exit ;
  Edit1.Text:=nameOut;
 end else Exit;
end;

procedure TForm1.Button3Click(Sender: TObject);
var
 FlagMinMax:integer; {1-Min,2-Max}
 i:WORD;
 nameOut:string[255]; {‚ле®¤­®© д ©« а ббзЁв ­­ле ¤ ­­ле x[i,j]}
 lpCmdLine:PChar; errtext:string[255];
 j,k,p,l,fl:integer;
begin {Основной блок}

 if Edit1.Text='' then
  begin
  MessageDlg('Пустое имя файла с таблицей'+Chr(13)+'Обработка прервана', mtWarning, [mbOk], 0);
  Exit;
  end;

{FlagInteger:=SpinEdit2.Value;  {Number signs before points}
{ FlagReal:=SpinEdit3.Value;  {Number signs after points}

 FlagMinMax:=1;
 if (Form1.RadioButton1.Checked=True) then  FlagMinMax:=1;
 if (Form1.RadioButton2.Checked=True) then  FlagMinMax:=2;

SaveDialog1.DefaultExt := 'prn';
SaveDialog1.FilterIndex := 1; { start the dialog showing all files }
SaveDialog1.Filter := 'Text files (*.txt)|*.TXT|Mathcad files (*.prn)|*.prn|Data files (*.dat)|*.dat|All files (*.*)|*.*';
if SaveDialog1.Execute then
 begin
  nameOut := SaveDialog1.FileName;
  if nameOut='' then Exit ;
 end else Exit;

// address of command line
GetMem(lpCmdLine,Length(Edit1.Text) + Length(nameOut) + 1+ 27);
StrCopy(lpCmdLine, 'minmaxWin32.exe "'); {Рабочий Проект :RGZ (Сетевая задача:Задача о пути)'}
StrCat(lpCmdLine, PChar(Edit1.Text));
StrCat(lpCmdLine, '"  "');
StrCat(lpCmdLine, PChar(SaveDialog1.FileName));
StrCat(lpCmdLine, '"  "');
StrCat(lpCmdLine, PChar(IntToStr(FlagMinMax)));
StrCat(lpCmdLine, '"');

{MessageDlg(lpCmdLine, mtInformation,[mbYes], 0);}
i:=WinExec(lpCmdLine, 0 );
FreeMem(lpCmdLine);
if (i<=31) then
 begin
   case i of
    0 : errtext:='The system is out of memory or resources.';
    ERROR_BAD_FORMAT : errtext:='The .EXE file is invalid (non-Win32 .EXE or error in .EXE image).';
    ERROR_FILE_NOT_FOUND : errtext:='The specified file (minmax.exe) was not found.';
    ERROR_PATH_NOT_FOUND : errtext:='The specified path (\minmax.exe) was not found.';
    end;
  MessageDlg(errtext, mtInformation,[mbYes], 0);
  Exit;
 end;

{ if MessageDlg('Файл '+#13#10+nameOut+Chr(13)+'создан'+Chr(13)+'Открыть его для просмотра результатов ?', mtInformation, [mbYes,mbNo], 0)=mrYes  then
  begin
  Form3.Label4.Caption:=nameOut;
  Form4.ShowModal ;
  end;}

end;

procedure TForm1.Button4Click(Sender: TObject);
begin
    Form5.ShowModal;
end;

procedure TForm1.BitBtn1Click(Sender: TObject);
begin
    Form3.ShowModal;
end;

end.
