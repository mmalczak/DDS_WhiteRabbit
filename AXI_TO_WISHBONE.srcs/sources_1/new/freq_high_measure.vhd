library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

entity freq_high_measure is
    Port ( 
	       clk : in STD_LOGIC;
    	   res : in std_logic;
           pll_meas : in STD_LOGIC;
           counter_mask : in std_logic_vector(31 downto 0);
           counts_pll : out STD_LOGIC_VECTOR (31 downto 0)
           );
end freq_high_measure;

architecture Behavioral of freq_high_measure is

--component ila_0
--PORT (
--	clk : IN STD_LOGIC;
--	probe0 : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
--	probe1 : IN STD_LOGIC_VECTOR(31 DOWNTO 0)
--);
--end component;
--signal probe0_s : std_logic_vector(31 downto 0);
--signal probe1_s : std_logic_vector(31 downto 0);
--signal clk_s : std_logic;


signal counter : std_logic_vector(31 downto 0);
signal counts_pll_s : std_logic_vector(31 downto 0);
signal counts_pll_trans_s : std_logic_vector(31 downto 0);
signal sync : std_logic;
signal res_pll : std_logic;
signal res_pll_sync : std_logic_vector(2 downto 0);
type   t_state is (IDLE, COUNT_IDLE, COUNT_PLL);
signal state : t_state;


begin

--ILA : ila_0 
--port map(
--		clk => clk_s,
--		probe0 => probe0_s,
--		probe1 => probe1_s
--);
	
process(clk)
begin
	if(clk'event and clk='1')then
        if(res = '0') then 
                state <= IDLE;
        else
            case state is
                when IDLE =>
                    res_pll<='0';
                    counter <= (others => '0');
                    state <= COUNT_IDLE;
                when COUNT_IDLE =>
                    if(counter = "10000000")then
                        counter <= (others => '0');
                        state <= COUNT_PLL;
                        res_pll <= '1';
                        counts_pll <= counts_pll_trans_s;
                    else 
                        counter <= counter+1;
                    end if;
                when COUNT_PLL =>
                        if(counter=counter_mask)then
                        counter <= (others => '0');
                        state <= IDLE;
                    else
                        counter <= counter+1;
                    end if;
            end case;
        end if;
     end if;		
end process;

process(pll_meas)
begin
    if(pll_meas'event and pll_meas='1')then
        res_pll_sync(2 downto 0) <= res_pll_sync(1 downto 0) & res_pll;
    end if;
end process;

process(pll_meas)
begin
	if(pll_meas'event and pll_meas = '1')then
		if(res_pll_sync(2) = '0')then
			if(sync='1')then
			     counts_pll_trans_s <= counts_pll_s;  
                 sync <= '0';
            end if;            
			counts_pll_s <= (others=>'0');
		else
		    sync <= '1';
			counts_pll_s <= counts_pll_s + 1; 		
		end if;
	end if;
end process;
--clk_s <= clk;
--probe0_s <= counter;
--probe1_s <= counts_pll_s;

end Behavioral;
