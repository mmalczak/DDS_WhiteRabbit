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
  
  res <= '1';
  x1<=X"00000000";
  x0<=X"00000001";
  start <= '1';
  wait for clk_period;
  start <= '0';
  err <= X"00000001";
  wait for 100000 ns;
    
    assert false severity failure;

  end process;

 

end;