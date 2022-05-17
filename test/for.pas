program typearray;
var 
	r : array[1 .. 100] of integer;
    s : integer;
    i : integer;
begin
    s:=0;
    for i:=2 to 10 do r[0]:=r[0]+1;
    for i:=2 to 10 do r[1]:=r[1]+1;
    //writeln(r[0]);
    //writeln(s);
end.