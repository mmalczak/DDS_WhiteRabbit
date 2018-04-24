--library IEEE;
--use IEEE.STD_LOGIC_1164.ALL;
--use ieee.numeric_std.all;

--entity PLL_filter is
--    Port ( clk : in std_logic;
--           res : in std_logic;
--           start : in std_logic;
--           err : in signed(31 downto 0);
--           x0 : in signed(31 downto 0);
--           x1 : in signed(31 downto 0);
--           freq : out std_logic_vector(31 downto 0)
--           );
--end PLL_filter;

--architecture Behavioral of PLL_filter is

--signal err_s : signed(31 downto 0);
--signal err_pr : signed(31 downto 0);
--signal freq_s : signed(31 downto 0);

--signal result_1 : signed(63 downto 0);
--signal result_2 : signed(63 downto 0);


--type   t_state is (IDLE, READ, FILTER0, FILTER1);
--signal state : t_state;


--begin


--process(clk)
--begin
--    if(res = '0') then 
--        state <= IDLE;
--        err_s <= (others => '0');
--        err_pr <= (others => '0');
--        freq_s <= X"017D7840";
--        result_1 <= (others => '0');
--        result_2 <= (others => '0');
--    elsif(clk'event and clk='1')then
--        case state is
--            when IDLE =>
--                if(start='1')then
--                    state <= READ;
--                else
--                    state <= IDLE;
--                end if;
--            when READ =>
--                err_pr <= err_s;
--                err_s <= err - "01000000000000000";
--                state <= FILTER0;
--           when FILTER0 =>
--                result_1 <= err_s * x0;
--                result_2 <= err_pr*x1;
--                state <= FILTER1; 
--           when FILTER1 =>
--                freq_s <= freq_s - (result_1(63) & result_1(54 downto 24)) - (result_2(63) & result_2(54 downto 24));
--                state <= IDLE;
--        end case;
--    end if;
--end process;

--freq <= std_logic_vector(freq_s);

--end Behavioral;

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


signal err_s2 : signed(15 downto 0);
signal err_pr2 : signed(15 downto 0);
signal freq_s2 : signed(31 downto 0);

signal result_12 : signed(47 downto 0);
signal result_22 : signed(47 downto 0);



type   t_state is (IDLE, READ, FILTER0, FILTER1);
signal state : t_state;


begin


process(clk)
begin
    if(res = '0') then 
        state <= IDLE;
        err_s <= (others => '0');
        err_s2 <= (others => '0');
        err_pr <= (others => '0');
        freq_s <= X"017D7840";
        freq_s2 <= X"017D7840";
        result_1 <= (others => '0');
        result_2 <= (others => '0');
        result_12 <= (others => '0');
        result_22 <= (others => '0');
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
                err_pr2 <= err_s2;
                err_s2 <= err(15 downto 0) - "1000000000000000";
                state <= FILTER0;
           when FILTER0 =>
                result_1 <= err_s * x0;
                result_2 <= err_pr*x1;
                result_12 <= err_s2 * x0;
                result_22 <= err_pr2*x1;
                state <= FILTER1; 
           when FILTER1 =>
                freq_s <= freq_s - (result_1(63) & result_1(54 downto 24)) - (result_2(63) & result_2(54 downto 24));
                freq_s2 <= freq_s2 - (result_1(47 downto 24)) - (result_2(47 downto 24));
                state <= IDLE;
        end case;
    end if;
end process;

freq <= std_logic_vector(freq_s);

end Behavioral;

