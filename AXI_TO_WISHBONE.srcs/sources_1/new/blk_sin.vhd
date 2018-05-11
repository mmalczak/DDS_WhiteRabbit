library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

--library UNISIM;
--use UNISIM.VComponents.all;
ENTITY blk_sin IS
  PORT (
    clka : IN STD_LOGIC;
    addra : IN STD_LOGIC_VECTOR(9 DOWNTO 0);
    douta : OUT STD_LOGIC_VECTOR(13 DOWNTO 0)
  );
END blk_sin;


architecture Behavioral of blk_sin is

component blk_mem_gen_0 IS
  PORT (
    clka : IN STD_LOGIC;
    addra : IN STD_LOGIC_VECTOR(9 DOWNTO 0);
    douta : OUT STD_LOGIC_VECTOR(13 DOWNTO 0)
  );
END component;

signal clka_s : std_logic;
signal addra_s : std_logic_vector(9 downto 0);
signal douta_s : std_logic_vector(13 downto 0);


begin

blk_1 : blk_mem_gen_0
port map
(
	clka => clka_s,
	addra => addra_s,
	douta => douta_s
);

clka_s <= clka;
addra_s <= addra;
douta <= douta_s;


end Behavioral;
