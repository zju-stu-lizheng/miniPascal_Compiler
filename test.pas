
Program quicksort;

Var 
    a :   array[0 .. 625] Of integer;
    s :   integer;

Procedure qsort(first,last:integer);

Var 
    temp :   Integer;
    pivot :   Integer;
    i :   Integer;
    j :   Integer;
Begin
    If first < last Then
        Begin
            i := first;
            j := last;
            pivot := first;
            //select first element be the pivot
            temp := a[pivot];
            While i<=j Do
                Begin
                    While (a[i] < temp) Do
                        i := i+1;
                    // find the first one bigger than a[pivot]
                    While (a[j] > temp) Do
                        j := j-1;
                    // find the last one smaller than a[pivot]
                    If i<=j Then // swap a[i],a[j]
                        Begin
                            temp := a[i];
                            a[i] := a[j];
                            a[j] := temp;
							i := i+1;
							j := j+1;
                        End;
                End;
			if first < j then qsort(first,j);
            if i < last then qsort(i,last);
        End;
End;

Begin
    For s:=0 To 10 Do
        a[s] := 2+s*s*s-7*s*s+5*s;
    For s:=0 To 10 Do
        Write(a[s],' ');
    WriteLn;
    qsort(0,10);
    For s:=0 To 10 Do
        Write(a[s],' ');
    WriteLn;
End.
