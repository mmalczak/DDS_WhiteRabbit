library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity spi_master_tb is
end;

architecture bench of spi_master_tb is

  component spi_master
    generic(
      g_div_ratio_log2 : integer := 4;
      g_num_data_bits  : integer := 8);
    port (
      clk_sys_i : in std_logic;
      rst_n_i   : in std_logic;
      start_i : in std_logic;
      cpol_i : in std_logic;
      data_i : in std_logic_vector(8 - 1 downto 0);
      drdy_o : out std_logic;
      ready_o : out std_logic;
      data_o : out std_logic_vector(8 - 1 downto 0);
      spi_cs_n_o : out std_logic;
      spi_sclk_o : out std_logic;
      spi_mosi_o : out std_logic;
      spi_miso_i : in  std_logic
      );
  end component;

  signal clk_sys_i: std_logic;
  signal rst_n_i: std_logic;
  signal start_i: std_logic;
  signal cpol_i: std_logic;
  signal data_i: std_logic_vector(8 - 1 downto 0);
  signal drdy_o: std_logic;
  signal ready_o: std_logic;
  signal data_o: std_logic_vector(8 - 1 downto 0);
  signal spi_cs_n_o: std_logic;
  signal spi_sclk_o: std_logic;
  signal spi_mosi_o: std_logic;
  signal spi_miso_i: std_logic ;

  constant clk_period: time := 20 ns;

begin

  -- Insert values for generic parameters !!
  uut: spi_master generic map ( g_div_ratio_log2 => 0,
                                g_num_data_bits  =>  8)
                     port map ( clk_sys_i        => clk_sys_i,
                                rst_n_i          => rst_n_i,
                                start_i          => start_i,
                                cpol_i           => cpol_i,
                                data_i           => data_i,
                                drdy_o           => drdy_o,
                                ready_o          => ready_o,
                                data_o           => data_o,
                                spi_cs_n_o       => spi_cs_n_o,
                                spi_sclk_o       => spi_sclk_o,
                                spi_mosi_o       => spi_mosi_o,
                                spi_miso_i       => spi_miso_i );

  clocking: process
  begin
      clk_sys_i <= '0'; wait for clk_period/2;
      clk_sys_i <= '1'; wait for clk_period/2;
  end process;
  
  
  stimulus: process
  begin
  rst_n_i <= '0';
  start_i <= '0';
  cpol_i <= '1';
  data_i <= "00000000";
  spi_miso_i <= '0';
  wait for clk_period*10;
  rst_n_i <= '1';
  wait for clk_period;
  start_i <= '1';
  wait for clk_period;
  start_i <= '0';
  wait for clk_period*100;
  
  
  assert false severity failure;
  end process;



end;
  

