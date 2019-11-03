program net_delphi;

{%File 'd4\Debug\d4.lib'}

uses
  Forms,
  main_unit in 'main_unit.pas' {Form1},
  about in 'about.pas' {Form2},
  crtpas in 'crtpas.pas' {Form3},
  seefile in 'seefile.pas' {Form4},
  templatetable in 'templatetable.pas' {Form5};

{$R *.res}

begin
  Application.Initialize;
  Application.Title := 'Net for Delphi (сборка 20.12.489)';
  Application.CreateForm(TForm1, Form1);
  Application.CreateForm(TForm2, Form2);
  Application.CreateForm(TForm3, Form3);
  Application.CreateForm(TForm4, Form4);
  Application.CreateForm(TForm5, Form5);
  Application.Run;
end.
