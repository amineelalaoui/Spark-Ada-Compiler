with Ada.Text_IO, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;

procedure Proced2 is

   N : INTEGER:=27;
   N5 : INTEGER;
   N2 : INTEGER;
   	
   procedure TwoFive(A: in Integer; B,C: out Integer) is
	tempA:Integer:=A;
   begin
	   B:=0;
	   C:=0;
	   while tempA-5>=0
	   loop
		tempA:=tempA-5;
		B:=B+1;
	   end loop;
	   if tempA=0
		then C:=0;
	   end if;
	   if tempA>0 and tempA<=2
		then C:=1;
	   end if;
	   if tempA>2 and tempA<=4
		then C:=2;
	   end if;
	   Print_Newline(1);
   end TwoFive;

begin

   TwoFive(N,N5,N2);
   Print_Newline(1);
   Print(N);
   Print_Newline(1);
   Print(N5);
   Print_Char(',');
   Print(N2);

end Proced2;