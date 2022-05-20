program arraymul;
var 
	r : array[0 .. 100] of integer;
    m : integer;
    n : integer;
    s : integer;
    i : integer;
begin
    ReadLn(m,n);
    WriteLn('m=',m,',n=',n);
    i:=0;
    for i:=2 to 10 do r[i]:=i;
    for i:=2 to 10 do WriteLn(r[i]);
end.