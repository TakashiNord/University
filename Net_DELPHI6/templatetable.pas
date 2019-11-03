unit templatetable;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, ExtCtrls, Grids, Spin;

type
  TForm5 = class(TForm)
    Bevel1: TBevel;
    BitBtn2: TBitBtn;
    BitBtn1: TBitBtn;
    Edit1: TEdit;
    SaveDialog1: TSaveDialog;
    StringGrid1: TStringGrid;
    Label1: TLabel;
    SpinEdit1: TSpinEdit;
    Label2: TLabel;
    SpinEdit2: TSpinEdit;
    procedure BitBtn1Click(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure FormActivate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form5: TForm5;

implementation

uses main_unit;

{$R *.dfm}

procedure TForm5.BitBtn1Click(Sender: TObject);
begin
  Form5.Close;
end;

procedure TForm5.BitBtn2Click(Sender: TObject);
Var
  FlagInteger,FlagReal: integer;
  i,j,Code:integer;  Pr:real;
  namefile:string[255];
  S: string[45];
  rf:TextFile;
begin
SaveDialog1.DefaultExt := 'prn';
SaveDialog1.Options := [ofOverwritePrompt];
SaveDialog1.FilterIndex := 1; { start the dialog showing all files }
SaveDialog1.Filter := 'Text files (*.txt)|*.TXT|Mathcad files (*.prn)|*.prn|Data files (*.dat)|*.dat|All files (*.*)|*.*';
if SaveDialog1.Execute then
 begin
  if ''=SaveDialog1.FileName then Exit ;
{  Form4.Memo1.Lines.SaveToFile(SaveDialog1.FileName);}
  Form5.Edit1.Text:='Файл:'+SaveDialog1.FileName;
  namefile:=SaveDialog1.FileName;
 end else Exit;

 {$I-} AssignFile(rf,namefile);Rewrite(rf);{$I+}
if(IOResult<>0) then
begin
 MessageDlg('Cannot creat out file='+namefile, mtWarning, [mbOk], 0);
 i:=IOResult;
end
else
 begin
 i:=IOResult;

 FlagInteger:=SpinEdit1.Value;  {Number signs before points}
 FlagReal:=SpinEdit2.Value;  {Number signs after points}

with Form5.StringGrid1 do
 begin
 Writeln(rf,' ');
 for i:=1 to Form5.StringGrid1.ColCount do
  begin
   Writeln(rf,' ');
   for j:=1 to Form5.StringGrid1.RowCount do
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
 CloseFile(rf);
 end;

end;

procedure TForm5.FormActivate(Sender: TObject);
var i,j :integer;
begin
 Form5.StringGrid1.RowCount:=Form1.SpinEdit1.Value+1;
 Form5.StringGrid1.ColCount:=Form1.SpinEdit1.Value+1;
 Form5.StringGrid1.FixedCols:=1;
 Form5.StringGrid1.FixedRows:=1;
 Form5.StringGrid1.FixedColor:=clBtnFace;
 Form5.StringGrid1.Options:=[goFixedVertLine,goFixedHorzLine,goVertLine,goHorzLine,goRangeSelect,goDrawFocusSelected,goRowSizing,goColSizing,goRowMoving,goColMoving,goEditing,goTabs,goAlwaysShowEditor];
 Form5.StringGrid1.ScrollBars:=ssBoth;
 with Form5.StringGrid1 do
  begin
    Cells[0,0] := '№ ';
    for i:=1 to (Form1.SpinEdit1.Value+1) do
       Cells[i,0] := 'Column '+IntToStr(i);
    for i:=1 to (Form1.SpinEdit1.Value+1) do
       Cells[0,i] := 'Row '+IntToStr(i);
    for i:=1 to (Form1.SpinEdit1.Value+1) do
     for j:=1 to (Form1.SpinEdit1.Value+1) do
       Cells[i,j] := IntToStr(0);
  end;
end;

end.
