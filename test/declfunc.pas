program declfunc;
const 
    CurTerm1 = 3;
var
    CurTerm2 : integer;
function myLine(a : integer): integer;
begin
	myLine := a + a;
end;
begin
    CurTerm2 := myLine(CurTerm1);
    WriteLn(CurTerm2);
end.