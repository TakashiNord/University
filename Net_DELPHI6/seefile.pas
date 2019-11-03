unit seefile;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, ExtCtrls;

type
  TForm4 = class(TForm)
    Memo1: TMemo;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    SaveDialog1: TSaveDialog;
    Bevel1: TBevel;
    Edit1: TEdit;
    procedure FormActivate(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form4: TForm4;

implementation

uses crtpas;

{$R *.dfm}

procedure TForm4.FormActivate(Sender: TObject);
begin
 if Form3.Label4.Caption='NULL' then  Form4.Close ;
 Form4.Memo1.Lines.LoadFromFile(Form3.Label4.Caption);
 Form4.Edit1.Text:='Τΰιλ:'+Form3.Label4.Caption;
end;

procedure TForm4.BitBtn2Click(Sender: TObject);
begin
SaveDialog1.DefaultExt := 'prn';
SaveDialog1.Options := [ofOverwritePrompt];
SaveDialog1.FilterIndex := 1; { start the dialog showing all files }
SaveDialog1.Filter := 'Text files (*.txt)|*.TXT|Mathcad files (*.prn)|*.prn|Data files (*.dat)|*.dat|All files (*.*)|*.*';
if SaveDialog1.Execute then
 begin
  if ''=SaveDialog1.FileName then Exit ;
  Form4.Memo1.Lines.SaveToFile(SaveDialog1.FileName);
  Form4.Edit1.Text:='Τΰιλ:'+SaveDialog1.FileName;
 end else Exit;

end;

procedure TForm4.BitBtn1Click(Sender: TObject);
begin
   Form4.Close;
end;

end.
