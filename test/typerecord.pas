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
end.