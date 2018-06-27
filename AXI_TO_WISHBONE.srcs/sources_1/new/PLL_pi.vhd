library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity PLL_pi is
    Port ( clk : in std_logic;
           res : in std_logic;
           start : in std_logic;
           err : in signed(15 downto 0);
           x0 : in signed(31 downto 0);
           x1 : in signed(31 downto 0);
           freq_accum_on : in std_logic;
           adc_offset : in signed(15 downto 0);
           freq : out signed(31 downto 0)
           );
end PLL_pi;

architecture Behavioral of PLL_pi is

signal clk_s : std_logic;

signal err_test : signed(15 downto 0);
signal err_s : signed(16 downto 0);
signal err_pr : signed(16 downto 0);
signal freq_s : signed(31 downto 0);

signal freq_out_s : signed(31 downto 0);


signal result_1 : signed(48 downto 0);
signal result_2 : signed(48 downto 0);

signal p_const : signed(31 downto 0);
signal i_const : signed(31 downto 0);

signal accum : signed(31 downto 0);
signal tune : signed(64 downto 0);

type   t_state is (IDLE, READ, FILTER0, FILTER1, FILTER2, FILTER3, FILTER4);
signal state : t_state;


constant F0 : signed(31 downto 0):=X"017D12B0";

begin

p_const<=x0;
i_const<=x1;
err_test <= err;
clk_s <= clk;

process(clk)
begin
    if(clk'event and clk='1')then
        if(res = '0') then 
                state <= IDLE;
                err_s <= (others => '0');
                tune <= (others => '0');
                freq_s <= X"017D7840";
                result_1 <= (others => '0');
                result_2 <= (others => '0');
                accum <= (others => '0');
        else 
            case state is
                when IDLE =>
                    if(start='1')then
                        state <= READ;
                    else
                        state <= IDLE;
                    end if;
                when READ =>
                    err_s <= signed('0'&err) - signed('0'&adc_offset);
                    state <= FILTER0;
               when FILTER0 =>
                    accum <= accum + err_s ;
                    state <= FILTER1; 
               when FILTER1 =>
                    tune <= accum * signed('0' & i_const) + err_s * signed('0' & p_const);
                    state <= FILTER2;                
               when FILTER2 =>
                    --współczynniki filtru 24 bity po przecinku
                    --  freq_s <= freq_s - tune(47 downto 16);
                    --freq_s <= tune(55 downto 24)*128;
                    freq_s <= tune(55 downto 24);
                    state <= FILTER3;
               when FILTER3 =>
                    freq_s <= F0 + freq_s;
                    -- VCO 21.67MHz + err(26000Hz/V)*128 => 3.33MHz/V
                    state <= FILTER4; 
               when FILTER4 =>
                     if(freq_s > X"05F5E100")then
                         freq_out_s <= X"05F5E100";  --100MHz
                     elsif(freq_s < X"000493E0")then
                         freq_out_s <= X"000493E0";  --300kHz
                     else 
                         freq_out_s <= freq_s;
                     end if;
                     state <= IDLE;                  

            end case;
        end if;
    end if;
end process;

freq <= freq_out_s;

end Behavioral;
