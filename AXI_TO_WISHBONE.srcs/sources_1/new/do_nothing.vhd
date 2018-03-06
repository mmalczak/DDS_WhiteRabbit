library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity do_nothing is
    Port ( s_lvds : in std_logic_vector(17 downto 0);
           s_mo : in std_logic_vector(39 downto 0);
           s_out : out std_logic_vector(57 downto 0)
    );
end do_nothing;

architecture Behavioral of do_nothing is

begin

    s_out<=s_lvds & s_mo;  

end Behavioral;
