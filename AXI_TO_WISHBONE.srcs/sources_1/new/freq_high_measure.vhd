library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity freq_high_measure is
    Port ( clk : in STD_LOGIC;
           dac_meas : in STD_LOGIC;
           pll_meas : in STD_LOGIC;
           counts : out STD_LOGIC_VECTOR (31 downto 0));
end freq_high_measure;

architecture Behavioral of freq_high_measure is

signal counter : std_logic_vector(15 downto 0);

signal dac_meas_s : std_logic;
signal pll_meas_s : std_logic;

signal counts_dac : std_logic_vector(15 downto 0);
signal counts_pll : std_logic_vector(15 downto 0);

begin

process(clk)
begin
    if(clk'event and clk='1')then
        counter <= counter+1;
        dac_meas_s <= dac_meas;
        pll_meas_s <= pll_meas;
       
        if(counter="1111111111111111")then
            counts(15 downto 0)<=counts_pll;
            counts(31 downto 16)<=counts_dac;
            counts_dac <= (others=>'0');
            counts_pll <= (others=>'0');
        else
        
            if((dac_meas_s xor dac_meas) = '1')then
                 counts_dac <= counts_dac+1;
            end if;
    
            if((pll_meas_s xor pll_meas) = '1')then
                 counts_pll <= counts_pll+1;
            end if;
        end if;
    end if;    

end process;


end Behavioral;
