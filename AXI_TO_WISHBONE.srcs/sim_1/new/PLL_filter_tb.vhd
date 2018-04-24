library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity PLL_filter_tb is
end;

architecture bench of PLL_filter_tb is

  component PLL_filter
      Port ( clk : in std_logic;
             res : in std_logic;
             start : in std_logic;
             err : in signed(31 downto 0);
             x0 : in signed(31 downto 0);
             x1 : in signed(31 downto 0);
             freq : out std_logic_vector(31 downto 0)
             );
  end component;

  signal clk: std_logic;
  signal res: std_logic;
  signal start: std_logic;
  signal err: signed(31 downto 0);
  signal x0: signed(31 downto 0);
  signal x1: signed(31 downto 0);
  signal freq: std_logic_vector(31 downto 0) ;

  constant clk_period: time := 10 ns;

begin

  uut: PLL_filter port map ( clk   => clk,
                             res   => res,
                             start => start,
                             err   => err,
                             x0    => x0,
                             x1    => x1,
                             freq  => freq );

 clocking: process
  begin
      clk <= '0'; wait for clk_period/2;
      clk <= '1'; wait for clk_period/2;
  end process;
  
  
  stimulus: process
  begin
  
  res <= '0';
  start <= '0';
  wait for clk_period;
  res <= '1';
  x1<=X"11800000";
  x0<=X"01054000";
  err <= "00000000000000000010101010000000";
  start <= '1';
  wait for clk_period;
  start <= '0';
wait for clk_period*4;
      start <= '1';
wait for clk_period;
start <= '0';
wait for clk_period*4;
         
    start <= '1';
wait for clk_period;
start <= '0';
wait for clk_period*4;
         
    start <= '1';
wait for clk_period;
start <= '0';
wait for clk_period*4;
         
    start <= '1';
wait for clk_period;
start <= '0';
wait for clk_period*4;
         
         
    
  wait for 1000 ns;
    
    assert false severity failure;

  end process;

 

end;