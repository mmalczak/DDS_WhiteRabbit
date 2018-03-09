library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity freq_measure is
    Port ( clk : in STD_LOGIC;
           dac_meas : in STD_LOGIC;
           pll_meas : in STD_LOGIC;
           counts : out STD_LOGIC_VECTOR (15 downto 0));
end freq_measure;

architecture Behavioral of freq_measure is

signal counts_dac : std_logic_vector(7 downto 0);
signal counts_pll : std_logic_vector(7 downto 0);

begin

process(clk)
begin
    if(clk'event and clk='1')then
        if(dac_meas='1')then
            counts_dac<=counts_dac+1;
        else
            if(counts_dac/="00000000")then
                counts(15 downto 8)<=counts_dac;
                counts_dac<=(others=>'0');
            end if;
        end if;
    end if;    

end process;

process(clk)
begin
    if(clk'event and clk='1')then
        if(pll_meas='1')then
            counts_pll<=counts_pll+1;
        else
            if(counts_pll/="00000000")then
                counts(7 downto 0)<=counts_pll;
                counts_pll<=(others=>'0');
            end if;            
        end if;
    end if;    

end process;

end Behavioral;
