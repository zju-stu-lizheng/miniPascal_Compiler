
Program quicksort;

Var 
    a :   array[1 .. 10001] Of integer;
    s :   integer;
    num :   Integer;
    flag : Integer;
    s1 : Integer;

Procedure qsort(first,last:integer);

Var 
    temp :   Integer;
    mid : Integer;
    pivot :   Integer;
    i :   Integer;
    j :   Integer;
Begin
    i := first;
    j := last;
    pivot := (first+last) div 2;
    //select first element be the pivot
    mid := a[pivot];
    While i<=j Do
        Begin
            While a[i] < mid Do begin i := i+1; end;
            // find the first one bigger than a[pivot]
            While a[j] > mid Do begin j := j-1; end;
            // find the last one smaller than a[pivot]
            If i<=j Then // swap a[i],a[j]
                Begin
                    temp := a[i];
                    a[i] := a[j];
                    a[j] := temp;
                    i := i+1;
                    j := j-1;
                End;
        End;
    If first < j Then qsort(first,j);
    If i < last Then qsort(i,last);
End;

Begin
    Read(num);
    // num := num -1;
    For s:=1 To num Do
        Read(a[s]);
    qsort(1,num);
    For s:=1 To num Do
        Writeln(a[s]);
End.
