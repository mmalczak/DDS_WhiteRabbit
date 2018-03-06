library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity counter_DAC is
    Port ( clk : in STD_LOGIC;
           dac_sierra : out std_logic_vector(9 downto 0)
    );
end counter_DAC;

architecture Behavioral of counter_DAC is


signal counter : std_logic_vector(9 downto 0);

begin
    process(clk)
    begin
        if(clk'event and clk='1')then
            counter<=counter+1;
        end if;
    end process;
   dac_sierra <= counter(9 downto 0);

end Behavioral;
