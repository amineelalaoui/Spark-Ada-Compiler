                                      -- Chapter 8 - Program 2
with Ada.Text_IO, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;

procedure Proced2 is

   Counter : INTEGER:=1;
   Counter2 : INTEGER:=3;
   Counter3 : INTEGER:=9;
   x : INTEGER :=0;

begin
	for x in 1..4
		loop
			Print(x);
		end loop;
	--Print(Counter,Counter2,Counter3);
end Proced2;
