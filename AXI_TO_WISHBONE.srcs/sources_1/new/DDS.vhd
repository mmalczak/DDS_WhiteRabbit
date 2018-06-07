library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity DDS is
    Port ( 
	clk : in std_logic;
	freq : in std_logic_vector(27 downto 0);
	douta : out std_logic_vector(13 downto 0)

);
end DDS;

architecture Behavioral of DDS is

signal clk_s : std_logic;

signal step_s : std_logic_vector(27 downto 0);
--signal dac_sierra_s : std_logic_vector(9 downto 0);

signal addra_s : std_logic_vector(9 downto 0);
signal douta_s : std_logic_vector(13 downto 0);
signal douta_mem_s : std_logic_vector(13 downto 0);


component counter_DAC is
    Port ( clk : in STD_LOGIC;
           step : in std_logic_vector(27 downto 0);
           dac_sierra : out std_logic_vector(9 downto 0)
    );
end component;

component blk_mem_gen_0 IS
  PORT (
    clka : IN STD_LOGIC;
    addra : IN STD_LOGIC_VECTOR(9 DOWNTO 0);
    douta : OUT STD_LOGIC_VECTOR(13 DOWNTO 0)
  );
end component;

begin

counter : counter_DAC
port map(
    clk => clk_s,
    step => step_s,
--    step => "0001000000000000000000000000",
    dac_sierra => addra_s 
);

memory : blk_mem_gen_0 
port map(
    clka => clk_s,
    addra => addra_s,
    douta => douta_mem_s
);

-- entity inputs
clk_s <= clk;
step_s <= freq; --freq is almost the same as the step
--entity outputs

process(clk)
begin
    if(clk'event and clk='1')then
        douta_s <= douta_mem_s;
        douta <= douta_s;
    end if;
end process;

end Behavioral;
