program declfunc;
const 
    CurTerm1 = 3;
var
    CurTerm2 : integer;
function myLine(a : integer): integer;
begin
	myLine := 2 + 2;
end;
begin
    CurTerm2 := myLine(CurTerm1);
end.