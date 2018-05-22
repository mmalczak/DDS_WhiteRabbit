library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VComponents.all;

entity pll_inst is
  Port (
	clk_out1 : out std_logic;
	clk_in1 : in std_logic  
   );
end pll_inst;

architecture Behavioral of pll_inst is

signal clk_in1_design_1_clk_wiz_0_0 : std_logic;
signal clk_in2_design_1_clk_wiz_0_0 : std_logic;
    signal clk_out1_design_1_clk_wiz_0_0 : std_logic;
  signal clk_out2_design_1_clk_wiz_0_0 : std_logic;
  signal clk_out3_design_1_clk_wiz_0_0 : std_logic;
  signal clk_out4_design_1_clk_wiz_0_0 : std_logic;
  signal clk_out5_design_1_clk_wiz_0_0 : std_logic;
  signal clk_out6_design_1_clk_wiz_0_0 : std_logic;
  signal clk_out7_design_1_clk_wiz_0_0 : std_logic;

  signal do_unused : std_logic_vector(15 downto 0);
  signal drdy_unused : std_logic;
  signal psdone_unused : std_logic;
  signal locked_int : std_logic;
  signal clkfbout_design_1_clk_wiz_0_0 : std_logic;
  signal clkfbout_buf_design_1_clk_wiz_0_0 : std_logic;
  signal clkfboutb_unused : std_logic;
   signal clkout1_unused : std_logic;
   signal clkout2_unused : std_logic;
   signal clkout3_unused : std_logic;
   signal clkout4_unused : std_logic;
  signal        clkout5_unused : std_logic;
  signal        clkout6_unused : std_logic;
  signal        clkfbstopped_unused : std_logic;
  signal        clkinstopped_unused : std_logic;



begin

 clkin1_ibufg : IBUF
   port map(
	O => clk_in1_design_1_clk_wiz_0_0,
    	I => clk_in1
	);

PLLE2_ADV_inst : PLLE2_ADV
generic map (
	BANDWIDTH => "optimized",
	COMPENSATION => "ZHOLD",
	STARTUP_WAIT => "FALSE",
	DIVCLK_DIVIDE => 2,
	CLKFBOUT_MULT => 33,
	CLKFBOUT_PHASE => 0.000,
	CLKOUT0_DIVIDE => 66,
	CLKOUT0_PHASE => 0.000,
	CLKOUT0_DUTY_CYCLE => 0.500,
	CLKIN1_PERIOD =>20.000)
   port map(
    CLKFBOUT            => clkfbout_design_1_clk_wiz_0_0,
    CLKOUT0             => clk_out1_design_1_clk_wiz_0_0,
    CLKOUT1             => clkout1_unused,
    CLKOUT2             => clkout2_unused,
    CLKOUT3             => clkout3_unused,
    CLKOUT4             => clkout4_unused,
    CLKOUT5             => clkout5_unused,
    -- Input clock control
    CLKFBIN             => clkfbout_buf_design_1_clk_wiz_0_0,
    CLKIN1              => clk_in1_design_1_clk_wiz_0_0,
    CLKIN2              => '0',
    -- Tied to always select the primary input clock
    CLKINSEL            => '1',
    -- Ports for dynamic reconfiguration
    DADDR               => "0000000",
    DCLK                => '0',
    DEN                 => '0',
    DI                  => X"0000",
    DO                  => do_unused,
    DRDY                => drdy_unused,
    DWE                 => '0',
    -- Other control and status signals
    LOCKED              => locked_int,
    PWRDWN              => '0',
    RST                 => '0'
);

  clkf_buf : BUFG 
   port map (
	    O => clkfbout_buf_design_1_clk_wiz_0_0,
        I => clkfbout_design_1_clk_wiz_0_0
	);



  clkout1_buf : BUFG
   port map(
	O => clk_out1,
   	I => clk_out1_design_1_clk_wiz_0_0
	);






end Behavioral;
