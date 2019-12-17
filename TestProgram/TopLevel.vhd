library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity TopLevel is
    Port ( Reset    : in   STD_LOGIC;
           debugLed : out  STD_LOGIC);
end TopLevel;

architecture Behavioral of TopLevel is

begin
   
   debugLed <= Reset;

end Behavioral;

