program typerecord;
type
  InfoType = record
    MyName : String;
    Age : integer;
    City, State : integer;
  end;
var
  Book1, Book2: InfoType;
begin
  Book1.MyName := 'AI';
  Book1.Age := 2;
  Book1.City := 4;
  Book1.State := 5;
  Writeln(Book1.MyName,' ',Book1.Age,' ',Book1.City,' ',Book1.State);
  Book2.MyName := 'CS';
  Book2.Age := 3;
  Book2.City := 41;
  Book2.State := 52;
  Writeln(Book2.MyName,' ',Book2.Age,' ',Book2.City,' ',Book2.State);
end.