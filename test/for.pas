program typearray;
var 
	r : array[1 .. 100] of integer;
    i : integer;
begin
    for i:=2 to 10 do r[i]:=i;
    for i:=2 to 10 do WriteLn(r[i]);
end.