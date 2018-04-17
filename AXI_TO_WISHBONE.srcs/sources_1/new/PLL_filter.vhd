library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity PLL_filter is
    Port ( clk : in std_logic;
           res : in std_logic;
           start : in std_logic;
           err : in signed(31 downto 0);
           x0 : in signed(31 downto 0);
           x1 : in signed(31 downto 0);
           freq : out std_logic_vector(31 downto 0)
           );
end PLL_filter;

architecture Behavioral of PLL_filter is

signal err_s : signed(31 downto 0);
signal err_pr : signed(31 downto 0);
signal freq_s : signed(31 downto 0);

signal result_1 : signed(63 downto 0);
signal result_2 : signed(63 downto 0);

signal result_11 : signed(31 downto 0);
signal result_22 : signed(31 downto 0);

type   t_state is (IDLE, READ, FILTER);
signal state : t_state;


begin


process(clk)
begin
    if(res = '0') then 
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
                err_s <= err - "01000000000000000";
                state <= FILTER;
           when FILTER =>

                result_1 <= err_s * x0;
                result_2 <= err_pr*x1;
                result_11 <= result_1(63) & result_1(54 downto 24);
                result_22 <= result_2(63) & result_2(54 downto 24);
                freq_s <= freq_s - result_11;
                freq_s <= freq_s - result_22;
                state <= IDLE;
        end case;
    end if;
end process;

freq <= std_logic_vector(freq_s);

end Behavioral;
