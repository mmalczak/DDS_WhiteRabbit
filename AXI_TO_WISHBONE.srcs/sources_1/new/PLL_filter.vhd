library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity PLL_filter is
    Port ( clk : in std_logic;
           res : in std_logic;
           start : in std_logic;
           err : in signed(15 downto 0);
           x0 : in signed(31 downto 0);
           x1 : in signed(31 downto 0);
           adc_offset : in signed(15 downto 0);
--           err_s_test : out signed(16 downto 0);
--           err_pr_test : out signed(16 downto 0);
--           result_1_test : out signed(24 downto 0);
--           result_2_test : out signed(24 downto 0);
           freq : out signed(31 downto 0)
           );
end PLL_filter;

architecture Behavioral of PLL_filter is

signal err_s : signed(16 downto 0);
signal err_pr : signed(16 downto 0);
signal freq_s : signed(31 downto 0);

signal result_1 : signed(48 downto 0);
signal result_2 : signed(48 downto 0);


type   t_state is (IDLE, READ, FILTER0, FILTER1);
signal state : t_state;

begin

process(clk)
begin
    if(res = '0') then 
        state <= IDLE;
        err_s <= (others => '0');
        err_pr <= (others => '0');
        freq_s <= X"017D7840";
        result_1 <= (others => '0');
        result_2 <= (others => '0');
    elsif(clk'event and clk='1')then
        case state is
            when IDLE =>
                if(start='1')then
                    state <= READ;
                else
                    state <= IDLE;
                end if;
            when READ =>
                err_pr <= err_s;
                err_s <= signed('0'&err) - signed('0'&adc_offset);
                state <= FILTER0;
           when FILTER0 =>
                result_1 <= err_s * x0;
                result_2 <= err_pr*x1;
                state <= FILTER1; 
           when FILTER1 =>
                --współczynniki filtru 24 bity po przecinku
                 freq_s <= freq_s - (result_1(48 downto 24))- (result_2(48 downto 24));
                 state <= IDLE;
        end case;
    end if;
end process;

freq <= freq_s;
--err_s_test <= err_s;
--err_pr_test <= err_pr;
--result_1_test <= result_1(48 downto 24);
--result_2_test <= result_2(48 downto 24);
--
end Behavioral;
