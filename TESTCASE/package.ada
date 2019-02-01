-- package Person is

   -- type EMPLOYEE is tagged private;

   -- procedure Display(Person_In : EMPLOYEE);

-- private

   -- type EMPLOYEE is tagged
      -- record
         -- Name        : STRING(1..25);
         -- Name_Length : INTEGER;
         -- Salary      : INTEGER;
      -- end record;

-- end Person;
package body Person is
procedure Swap(A, B, C : in Integer; D,E: out Integer) is
   Temp : Integer:=A;
   begin
   A := B;
   B := Temp;
   C:=120;
   D:=A-B;
   E:=D*A;
   Print(A,B,C,D,E);
   end Swap;
end Person;

with Person; 
procedure Proced2 is

   Counter : INTEGER:=5;
   Counter2 : INTEGER:=3;
   Counter3 : INTEGER:=9;
   Counter4: INTEGER:=10;
   Counter5 : INTEGER:=12;
begin
   Counter := Counter +1 ;
   Swap(Counter,Counter2,Counter3,Counter4,Counter5);
   Print_Newline(1);
   Print(Counter,Counter2,Counter3,Counter4,Counter5);

end Proced2;
