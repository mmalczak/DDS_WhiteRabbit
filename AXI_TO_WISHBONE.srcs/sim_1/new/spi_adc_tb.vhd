library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity spi_adc_tb is
end;

architecture bench of spi_adc_tb is

component spi_adc is
  port (
    clk_sys_i : in std_logic;
    rst_n_i   : in std_logic;

    start_i : in std_logic;

    -- data read from selected slave, valid when ready_o == 1.
    data_o : out std_logic_vector(15 downto 0);

    -- these are obvious
    cnv : out std_logic;
    sdi : out std_logic;
    spi_sclk_o : out std_logic;
    spi_miso_i : in  std_logic
    );

end component;

  signal clk_sys_i: std_logic;
  signal rst_n_i: std_logic;
  signal start_i: std_logic;
  signal data_o: std_logic_vector(15 downto 0);
  signal cnv: std_logic;
  signal sdi: std_logic;
  signal spi_sclk_o: std_logic;
  signal spi_miso_i: std_logic ;

  constant clk_period: time := 20 ns;

begin

  uut: spi_adc port map ( clk_sys_i  => clk_sys_i,
                          rst_n_i    => rst_n_i,
                          start_i    => start_i,
                          data_o     => data_o,
                          cnv        => cnv,
                          sdi        => sdi,
                          spi_sclk_o => spi_sclk_o,
                          spi_miso_i => spi_miso_i );


 clocking: process
  begin
      clk_sys_i <= '0'; wait for clk_period/2;
      clk_sys_i <= '1'; wait for clk_period/2;
  end process;
  
  

  stimulus: process
  begin
    
        rst_n_i <= '0'; 
        start_i <= '0';
        spi_miso_i <= '1';
        wait for 4* clk_period;
        rst_n_i <= '1'; wait for clk_period;
        
        start_i <= '1';wait for clk_period;
        start_i <= '0';
        
        
        wait for clk_period*80;
  
      assert false severity failure;
  end process;


end;