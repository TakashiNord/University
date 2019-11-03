unit about;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Buttons, ExtCtrls, ComCtrls;

type
  TForm2 = class(TForm)
    Bevel1: TBevel;
    Image1: TImage;
    BitBtn1: TBitBtn;
    Image2: TImage;
    StaticText1: TStaticText;
    RichEdit1: TRichEdit;
    Label1: TLabel;
    Label4: TLabel;
    Label6: TLabel;
    Label3: TLabel;
    procedure BitBtn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form2: TForm2;

implementation

{$R *.dfm}

procedure TForm2.BitBtn1Click(Sender: TObject);
begin
  Form2.Close ;
end;

end.
