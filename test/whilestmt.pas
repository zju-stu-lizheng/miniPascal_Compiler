program whilestmt;
var 
	array_a : array[0 .. 625] of integer;
    i : Integer;
    sum : Integer;
begin
    while i<10 do begin
        sum:=sum+i;
        i:=i+1;
    end;
end.