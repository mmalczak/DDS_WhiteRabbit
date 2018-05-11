library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNIMACRO;
use unimacro.Vcomponents.all;

entity block_ram_sinus is
    Port ( clk : in std_logic;
           addra : in std_logic_vector(9 downto 0);
           douta : out std_logic_vector(13 downto 0)
           );
end block_ram_sinus;

architecture Behavioral of block_ram_sinus is

signal clka_s : std_logic;
signal addra_s : std_logic_vector(9 downto 0);
signal douta_s : std_logic_vector(13 downto 0);



begin

 BRAM_SINGLE_MACRO_inst : BRAM_SINGLE_MACRO
    GENERIC MAP (
	BRAM_SIZE=>"18Kb",
	DEVICE=>"7SERIES",
	DO_REG=>0,--Optionaloutputregister(0or1)
	INIT=>(others=>'0'),--Initialvaluesonoutputport
	INIT_FILE=>"sinus2.coe",
	WRITE_WIDTH=>14,--Validvaluesare1-72(37-72onlyvalidwhenBRAM_SIZE="36Kb")
	READ_WIDTH=>14,--Validvaluesare1-72(37-72onlyvalidwhenBRAM_SIZE="36Kb")
	SRVAL=>X"000000000000000000",--Set/Resetvalueforportoutput
	WRITE_MODE=>"NO_CHANGE"
    )
    PORT MAP (
	DO => douta_s,
	ADDR => addra_s,
	CLK => clka_s,
	DI => (others=>'0'),
	EN => '1',
	REGCE => '0',
	RST => '1',
	WE => "00"
    );


end Behavioral;
