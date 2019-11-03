unit crtpas;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Grids, Spin,
  seefile, Buttons;

type
  TForm3 = class(TForm)
    Edit1: TEdit;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    CheckBox1: TCheckBox;
    StringGrid1: TStringGrid;
    Label1: TLabel;
    SpinEdit1: TSpinEdit;
    SpinEdit2: TSpinEdit;
    Label2: TLabel;
    Label3: TLabel;
    SaveDialog1: TSaveDialog;
    CheckBox2: TCheckBox;
    Label4: TLabel;
    BitBtn1: TBitBtn;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure CheckBox1Click(Sender: TObject);
    procedure FormActivate(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form3: TForm3;

implementation

{$R *.dfm}

procedure TForm3.Button1Click(Sender: TObject);
const
m=10;  {зЁб«® г§«®ў(ўҐаиЁ­)}
Var
  FlagInteger,FlagReal: integer;
  i,j,Code:integer;  Pr,n:real;
  S: string[45];
begin
  n:=0.0;
 { Get text from TEdit control }
  Val(Edit1.Text, Pr, Code);
 { Error during conversion to integer? }
  if Code = 0 then n:=Pr;
  {Number signs before points}
  FlagInteger:=SpinEdit1.Value;
  {Number signs after points}
  FlagReal:=SpinEdit2.Value;

with StringGrid1 do
 for i:=1 to m do
  begin
   for j:=1 to m do
    begin
     Pr:=0;
     if ((i=1)and(j=2)) then Pr:=10+n;
     if ((i=1)and(j=3)) then Pr:=6+n/3;
     if ((i=1)and(j=4)) then Pr:=6+n/3;
     if ((i=2)and(j=4)) then Pr:=2+n/2;     if ((i=2)and(j=5)) then Pr:=9+n;
     if ((i=3)and(j=4)) then Pr:=7+n/3;     if ((i=3)and(j=6)) then Pr:=8+n;
     if ((i=4)and(j=5)) then Pr:=3+n/2;if ((i=4)and(j=6)) then Pr:=10+n/3;
     if ((i=4)and(j=7)) then Pr:=4+n;
     if ((i=5)and(j=7)) then Pr:=n+n/2;     if ((i=5)and(j=8)) then Pr:=5+n/3;
     if ((i=6)and(j=7)) then Pr:=9+n;       if ((i=6)and(j=9)) then Pr:=7+n/2;
     if ((i=7)and(j=8)) then Pr:=12+n/3;if ((i=7)and(j=9)) then Pr:=6+n;
     if ((i=7)and(j=10)) then Pr:=8+n/2;
     if ((i=8)and(j=10)) then Pr:=9+n/3;
     if ((i=9)and(j=10)) then Pr:=11+n/2;
     Str(Pr:FlagInteger:FlagReal, S);
     Cells[j,i] := S;
    end;
   end;

end;

procedure TForm3.Button2Click(Sender: TObject);
var i,j :integer;
begin
with StringGrid1 do
  begin
    Cells[0,0] := '№ ';
    for i:=1 to 10 do
       Cells[i,0] := 'Column '+IntToStr(i);
    for i:=1 to 10 do
       Cells[0,i] := 'Row '+IntToStr(i);
    for i:=1 to 10 do
     for j:=1 to 10 do
       Cells[i,j] := IntToStr(0);
  end;
end;

procedure TForm3.CheckBox1Click(Sender: TObject);
begin
 if (Form3.CheckBox1.Checked=False) then
    StringGrid1.Options:=[goFixedVertLine,goFixedHorzLine,goVertLine,goHorzLine,goRangeSelect,goRowSizing,goColSizing,goRowMoving,goColMoving,goEditing,goTabs,goAlwaysShowEditor]
  else
    StringGrid1.Options:=[goFixedVertLine,goFixedHorzLine,goVertLine,goHorzLine,goTabs];
end;

procedure TForm3.FormActivate(Sender: TObject);
var i,j :integer;
begin
with StringGrid1 do
  begin
    Cells[0,0] := '№ ';
    for i:=1 to 10 do
       Cells[i,0] := 'Column '+IntToStr(i);
    for i:=1 to 10 do
       Cells[0,i] := 'Row '+IntToStr(i);
    for i:=1 to 10 do
     for j:=1 to 10 do
       Cells[i,j] := IntToStr(0);
  end;
   if (Form3.CheckBox1.Checked=False) then
    StringGrid1.Options:=[goFixedVertLine,goFixedHorzLine,goVertLine,goHorzLine,goRangeSelect,goRowSizing,goColSizing,goRowMoving,goColMoving,goEditing,goTabs,goAlwaysShowEditor]
  else
    StringGrid1.Options:=[goFixedVertLine,goFixedHorzLine,goVertLine,goHorzLine,goTabs];
end;

procedure TForm3.Button3Click(Sender: TObject);
const
m=10;  {зЁб«® г§«®ў(ўҐаиЁ­)}
Var
  FlagInteger,FlagReal: integer;
  i,j,Code:integer;  Pr:real;
  S: string[45];
  nameOut:string[255];
  rf:TextFile;
begin

SaveDialog1.DefaultExt := 'prn';
SaveDialog1.Options := [ofOverwritePrompt];
SaveDialog1.FilterIndex := 1; { start the dialog showing all files }
SaveDialog1.Filter := 'Text files (*.txt)|*.TXT|Mathcad files (*.prn)|*.prn|Data files (*.dat)|*.dat|All files (*.*)|*.*';
if SaveDialog1.Execute then
 begin
  nameOut := SaveDialog1.FileName;
  if nameOut='' then Exit ;
  Form3.Label4.Caption:=nameOut;
 end else Exit;

{$I-} AssignFile(rf,nameOut);Rewrite(rf);{$I+}
if(IOResult<>0) then
begin
 MessageDlg('Cannot creat out file='+nameOut, mtWarning, [mbOk], 0);
 i:=IOResult;
end
else
 begin
 i:=IOResult;

 FlagInteger:=SpinEdit1.Value;  {Number signs before points}
 FlagReal:=SpinEdit2.Value;  {Number signs after points}

with StringGrid1 do
 begin
 Writeln(rf,' ');
 for i:=1 to m do
  begin
   Writeln(rf,' ');
   for j:=1 to m do
    begin
     S:=Cells[j,i];
     Val(S, Pr, Code);
      if Code = 0 then Str(Pr:FlagInteger:FlagReal, S)
       else
	begin
         MessageDlg('Ошибка преобразования: '+ IntToStr(Code)+Chr(13)+' В таблице имеются не числовые символы'+Chr(13)+'Сохранение прервано', mtWarning, [mbOk], 0);
         CloseFile(rf);  Exit ;
	 end;
     Write(rf,' ',Pr:FlagInteger:FlagReal)
    end;
   end;
  end;
 end;
 CloseFile(rf);

 if (Form3.CheckBox2.Checked=True) then Form4.ShowModal;

end;

procedure TForm3.BitBtn1Click(Sender: TObject);
begin
 Form3.Close;
end;


end.
