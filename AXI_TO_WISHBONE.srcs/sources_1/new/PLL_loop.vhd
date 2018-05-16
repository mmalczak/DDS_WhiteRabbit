library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.all;
Library UNISIM;
use UNISIM.vcomponents.all;

entity PLL_loop is
  Port (   	 
		clk_50 : in std_logic;
		clk_dds : in std_logic;
		res : in std_logic;
		x0 : in std_logic_vector(31 downto 0);
		x1 : in std_logic_vector(31 downto 0);
		spi_miso_i : in std_logic;
		adc_offset : in std_logic_vector(15 downto 0);
		timer : in unsigned(15 downto 0);

--		freq : out std_logic_vector(31 downto 0);
		cnv : out std_logic;
		sdi : out std_logic;
--		err_s_test : out std_logic_vector(16 downto 0);
--		err_pr_test : out std_logic_vector(16 downto 0);
--		result_1_test : out std_logic_vector(24 downto 0);
--		result_2_test : out std_logic_vector(24 downto 0); 
--		err_test : out std_logic_vector(15 downto 0);
		spi_sclk_o : out std_logic;
		dout_dds_P : out std_logic_vector(13 downto 0);
		dout_dds_N : out std_logic_vector(13 downto 0)
	 );
end PLL_loop;

architecture Behavioral of PLL_loop is

--component ila_0
--PORT (
--	clk : IN STD_LOGIC;
--	probe0 : IN STD_LOGIC_VECTOR(16 DOWNTO 0)
--);
--end component;


component DDS is
    Port(
	clk : in std_logic;
	freq : in std_logic_vector(27 downto 0);
	douta : out std_logic_vector(13 downto 0)
	);
end component;

component pll_inst is
    port(
	clk_out1 : out std_logic;
	clk_in1 : in std_logic
);
end component;

component PLL_filter is
    Port ( clk : in std_logic;
           res : in std_logic;
           start : in std_logic;
           err : in std_logic_vector(15 downto 0);
           x0 : in std_logic_vector(31 downto 0);
           x1 : in std_logic_vector(31 downto 0);
           adc_offset : in std_logic_vector(15 downto 0);
--           err_s_test : out std_logic_vector(16 downto 0);
--           err_pr_test : out std_logic_vector(16 downto 0);
--           result_1_test : out std_logic_vector(24 downto 0);
--           result_2_test : out std_logic_vector(24 downto 0);
           freq : out std_logic_vector(31 downto 0)
           );
end component;

component spi_adc is
  port (
    clk_sys_i : in std_logic;
    rst_n_i   : in std_logic;
    start_i : in std_logic;
    data_o : out std_logic_vector(15 downto 0);
    data_ready : out std_logic;
    cnv : out std_logic;
    sdi : out std_logic;
    spi_sclk_o : out std_logic;
    spi_miso_i : in  std_logic
    );

end component;

--DDS signals
signal clk_dds_s : std_logic;
signal dout_dds_s : std_logic_vector(13 downto 0);

signal dout_dds_N_s : std_logic_vector(13 downto 0);
signal dout_dds_P_s : std_logic_vector(13 downto 0); 



signal clk_50_s : std_logic;
signal clk_12_5_s : std_logic;
signal res_s : std_logic;
signal x0_s : std_logic_vector(31 downto 0);
signal x1_s : std_logic_vector(31 downto 0);
signal adc_offset_s :  std_logic_vector(15 downto 0);
signal adc_start_i_s : std_logic;
signal spi_miso_i_s : std_logic;


signal freq_s : std_logic_vector(31 downto 0);
signal cnv_s : std_logic;
signal sdi_s : std_logic;
signal spi_sclk_o_s : std_logic;


signal data_o_to_err_s : std_logic_vector(15 downto 0);
signal data_ready_to_start_s : std_logic;

signal counter : unsigned(15 downto 0);

--signal err_s_test_s : std_logic_vector(16 downto 0);
--signal err_pr_test_s : std_logic_vector(16 downto 0);
--signal result_1_test_s: std_logic_vector(24 downto 0);
--signal result_2_test_s: std_logic_vector(24 downto 0);

begin

	I1: PLL_filter port map (
		clk => clk_50_s,
		res => res_s,
		start => data_ready_to_start_s,
		err => data_o_to_err_s,
		x0 => x0_s,
		x1 => x1_s,
		adc_offset => adc_offset_s,
--		err_s_test => err_s_test_s,
--		err_pr_test => err_pr_test_s,
--		result_1_test => result_1_test_s,
--		result_2_test => result_2_test_s,
		freq => freq_s
	);
	
	I2: spi_adc port map(
		clk_sys_i => clk_12_5_s,
		rst_n_i => res_s,
		start_i => adc_start_i_s,
		data_o => data_o_to_err_s,
		data_ready => data_ready_to_start_s,
	  	cnv => cnv_s, 
		sdi => sdi_s,
		spi_sclk_o => spi_sclk_o_s,
		spi_miso_i => spi_miso_i_s	
	);
	PLL : pll_inst port map(
		clk_out1 => clk_12_5_s,
		clk_in1 => clk_50_s
	);

	DDS_inst : DDS port map(
		clk => clk_dds_s,
		freq => freq_s(27 downto 0),  --should modify this
		douta => dout_dds_s 
	);

	DDS_out_port_gen:
	for J in 0 to 13 generate
	OBUFDS_inst : OBUFDS
	generic map(
		IOSTANDARD=>"DEFAULT",--SpecifytheoutputI/Ostandard
		SLEW=>"SLOW")
	port map(
		O=>dout_dds_P_s(J), --Diff_p output
		OB=>dout_dds_N_s(J), --Diff_n output
		I=>dout_dds_s(J) --Buffer input
	);
	end generate DDS_out_port_gen;


--	PROBE : ila_0
--	port map(
--		clk => clk_50_s,
--		probe0 => err_s_test_s
--	);


process(clk_50)
begin
    if(clk_50'event and clk_50 = '1')then
        if(res = '0') then
            counter <= (others => '0');
            adc_start_i_s <= '0';
        else
            if(counter = timer) then
                counter <= (others=>'0');
                adc_start_i_s <= '1';
            elsif(counter=X"0004")then
                counter <= counter + 1;
                adc_start_i_s <= '0';
            else
                counter <= counter + 1;
            end if;
        end if;
    end if;
end process;

--dds
clk_dds_s <= clk_dds;
dout_dds_P <= dout_dds_P_s;
dout_dds_N <= dout_dds_N_s;

clk_50_s <= clk_50;
res_s <= res;
x0_s <= x0;
x1_s <= x1;
adc_offset_s <= adc_offset;
spi_miso_i_s <= spi_miso_i;
cnv <= cnv_s;
sdi <= sdi_s;
spi_sclk_o <= spi_sclk_o_s;

end Behavioral;
