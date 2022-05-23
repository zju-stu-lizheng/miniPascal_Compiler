program loopstmt;
var 
	array_a : array[0 .. 625] of integer;
    i : Integer;
    sum : Integer;
begin
    WriteLn('test for for');
    for i:=2 to 10 do array_a[i]:=i;
    for i:=2 to 10 do WriteLn(array_a[i]);
    WriteLn('test for while: 1+...10');
    i:=0;
    while i<10 do begin
        sum:=sum+i;
        i:=i+1;
    end;
    Writeln(sum);
end.