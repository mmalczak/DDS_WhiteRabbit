library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;

entity DDS is
    Port ( 
	clk : in std_logic;
	freq : in std_logic_vector(27 downto 0);
	douta : out std_logic_vector(13 downto 0)

);
end DDS;

architecture Behavioral of DDS is

signal clk_s : std_logic;

signal step_s : std_logic_vector(63 downto 0);
signal step2_s : std_logic_vector(63 downto 0);
signal step3_s : std_logic_vector(63 downto 0);

signal freq_s : unsigned(27 downto 0);

--signal dac_sierra_s : std_logic_vector(9 downto 0);

signal addra_s : std_logic_vector(9 downto 0);
signal douta_s : std_logic_vector(13 downto 0);
signal douta_mem_s : std_logic_vector(13 downto 0);

constant freq_to_step : unsigned(35 downto 0):=X"112E0BE80";

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
    step => step3_s(59 downto 32),
--    step => "0001000000000000000000000000",
    dac_sierra => addra_s 
);

memory : blk_mem_gen_0 
port map(
    clka => clk_s,
    addra => addra_s,
    douta => douta_mem_s
);

clk_s <= clk;

process(clk)
begin
    if(clk'event and clk='1')then
        freq_s <= unsigned(freq);
        step_s <= std_logic_vector(freq_s*freq_to_step); --freq is almost the same as the step
        step2_s <= step_s;
        step3_s <= step2_s;
    end if;
end process;

process(clk)
begin
    if(clk'event and clk='1')then
        douta_s <= douta_mem_s;
        douta <= douta_s;
    end if;
end process;

end Behavioral;
