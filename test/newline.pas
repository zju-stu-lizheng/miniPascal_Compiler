program test;
var 
	r : array[0 .. 100] of char;
    i : integer;
begin
    r[0] := 'z';
    r[1] := '\n';
    Read(r[2]);
    r[3] := 'a';
    r[4] := 'b';
    for i:=0 to 4 do Write(r[i]);
    if  r[2] = '\n' then
        WriteLn('正确读入');
    
end.