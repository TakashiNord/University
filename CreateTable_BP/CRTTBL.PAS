
Program CreateTableMin(input,output);
Uses Crt,Dos;
const
m=10;  {�᫮ 㧫��(���設)}
nameOut='netlen.prn'; {��室��� 䠩� ����⠭��� ������}
FlagInteger=2;{Number signs before points}
FlagReal=0;{Number signs after points}

Var
  i,j,n:integer;  Pr:real;  rf:text; {�����⥫� �� 䠩�}

begin {�᭮���� ����}

ClrScr;
Write('Size Matrix m=',m,'    Input (n>0) n:= ');Readln(n);
Writeln('���� ����..');

{$I-} Assign(rf,nameOut);Rewrite(rf);{$I+}
if(IOResult<>0) then
begin Writeln('Cannot creat out file=',nameOut); exit; end;i:=IOResult;

{ �뢮� १���⮢ }
 Writeln(rf,' ');
 for i:=1 to m do
  begin
   Writeln(rf,' ');
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
     Write(rf,' ',Pr:FlagInteger:FlagReal)

    end;
   end;

 Close(rf);Writeln(' File created .Press 2-any key for exit.');
 ReadKey;repeat until KeyPressed;ClrScr;

end.

{��㯯�: 5��-1  �९�����⥫� : ���ॢ� �.�.(��䥤� ����)
 ����� �஥�� ��㤥���: C��ਤ���� �.�., ��������� �.�.
 ��� 2000}

