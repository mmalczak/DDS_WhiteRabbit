library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity PLL_pi_tb is
end;

architecture bench of PLL_pi_tb is

  component PLL_pi
      Port ( clk : in std_logic;
             res : in std_logic;
             start : in std_logic;
             err : in signed(15 downto 0);
             x0 : in signed(31 downto 0);
             x1 : in signed(31 downto 0);
             freq_accum_on : in std_logic;
             adc_offset : in signed(15 downto 0);
             freq : out signed(31 downto 0)
             );
  end component;

  signal clk: std_logic;
  signal res: std_logic;
  signal start: std_logic;
  signal err: signed(15 downto 0);
  signal x0: signed(31 downto 0);
  signal x1: signed(31 downto 0);
  signal freq_accum_on: std_logic;
  signal adc_offset: signed(15 downto 0);
  signal freq: signed(31 downto 0) ;

  constant clk_period: time := 20 ns;

begin

  clocking: process
  begin
      clk <= '0'; wait for clk_period/2;
      clk <= '1';wait for clk_period / 2;
  end process;

  uut: PLL_pi port map ( clk           => clk,
                         res           => res,
                         start         => start,
                         err           => err,
                         x0            => x0,
                         x1            => x1,
                         freq_accum_on => freq_accum_on,
                         adc_offset    => adc_offset,
                         freq          => freq );

  stimulus: process
  begin
  
   res <= '0';
   start <= '0';
   freq_accum_on <= '0';
   x1 <= X"00080000";
   x0<=X"00000000";
   adc_offset <= "1000000000000000";
   wait for clk_period;
   res <= '1';
   
   
   
   err <= "0000111111111111";
   start <= '1';
   wait for clk_period;
   start <= '0';
   wait for clk_period*5;
   
   start <= '1';
   wait for clk_period;
   start <= '0';
   wait for clk_period*5;
 
   err <= "0000000000001000";         
   start <= '1';
   wait for clk_period;
   start <= '0';
   wait for clk_period*5;
          
   err <= "1000000000000000";
   start <= '1';
   wait for clk_period;
   start <= '0';
   wait for clk_period*5;
           
   err <= "1100000000000100";
   start <= '1';
   wait for clk_period;
   start <= '0';
   wait for clk_period*5;
 
  wait for clk_period*10;
  assert false severity failure;
  end process;



end;
  