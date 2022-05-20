program test;
var 
    i : integer;
begin
    for i:=2 to 10 do begin 
        if i > 5 then Break;
        WriteLn(i);
    end;
end.