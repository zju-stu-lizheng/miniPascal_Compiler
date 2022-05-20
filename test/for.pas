program typearray;
var 
	r : array[1 .. 100] of integer;
    s : integer;
    i : integer;
begin
    s:=0;
    for i:=2 to 10 do r[i]:=i;
    for i:=2 to 10 do WriteLn(r[i]);
end.