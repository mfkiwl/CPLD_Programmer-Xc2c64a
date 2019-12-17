library IEEE;
use IEEE.std_logic_1164.ALL;

use IEEE.NUMERIC_STD.ALL;

entity CPLD_Tester is
    Port ( clock : in   std_logic;
           leds  : out  std_logic_vector (31 downto 0));
end CPLD_Tester;

architecture Behavioral of CPLD_Tester is

signal toggle         : std_logic;
signal counter        : integer range 0 to 100;
signal value          : std_logic_vector (31 downto 0);

begin

   counter <= counter + 1 when rising_edge(clock);
   
   toggle <= not toggle when rising_edge(clock) and (counter = 0);

   leds <= value when rising_edge(clock);
   
   process(counter) 
   begin
   -- Stagger LED output changes to avoid noise problems (Vdd ?)
   case counter is
      when 1 =>
         value(31 downto 25) <= (others=>toggle);
      when 2 =>
         value(24 downto 15) <= (others=>toggle);
      when 3 =>
         value(16 downto 9)  <= (others=>toggle);
      when 4 =>
         value(8 downto 0)   <= (others=>toggle);
      when others =>
         null;
   end case;
   end process;
   
end Behavioral;

