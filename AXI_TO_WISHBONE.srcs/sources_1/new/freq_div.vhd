library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity freq_div is
    Port ( clk : in STD_LOGIC;
           clk_div : out STD_LOGIC);
end freq_div;

architecture Behavioral of freq_div is

signal counter : std_logic_vector(27 downto 0);

begin
    process(clk)
    begin
        if(clk'event and clk='1')then
            counter<=counter+1;
        end if;
    end process;
    
clk_div <= counter(25);

end Behavioral;
