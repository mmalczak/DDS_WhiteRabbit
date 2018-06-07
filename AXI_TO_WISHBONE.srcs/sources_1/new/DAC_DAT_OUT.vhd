LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;
Library UNISIM;
use UNISIM.vcomponents.all;

ENTITY DAC_DAT_OUT IS
  PORT (
    OBUF_IN : IN STD_LOGIC_VECTOR(13 DOWNTO 0);
    OBUF_DS_P : OUT STD_LOGIC_VECTOR(13 DOWNTO 0);
    OBUF_DS_N : OUT STD_LOGIC_VECTOR(13 DOWNTO 0)
  );
END DAC_DAT_OUT;

ARCHITECTURE behavioral OF DAC_DAT_OUT IS

signal dac_in : std_logic_vector(13 downto 0);
signal dac_out_N : std_logic_vector(13 downto 0);
signal dac_out_P : std_logic_vector(13 downto 0); 

BEGIN



GEN_REG:
for J in 0 to 13 generate
	OBUFDS_inst : OBUFDS
	generic map(
		IOSTANDARD=>"DEFAULT",--SpecifytheoutputI/Ostandard
		SLEW=>"SLOW")
	port map(
		O=>dac_out_P(J),--Diff_p output
		OB=>dac_out_N(J),--Diff_n output
		I=>dac_in(J)--Bufferinput
	);
end generate GEN_REG;

dac_in <= OBUF_IN;
OBUF_DS_N <= dac_out_N;
OBUF_DS_P <= dac_out_P;


END behavioral;
