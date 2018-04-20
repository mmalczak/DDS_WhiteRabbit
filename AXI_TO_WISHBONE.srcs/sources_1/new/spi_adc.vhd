library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity spi_adc is
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

end spi_adc;

architecture behavioral of spi_adc is

  signal rx_sreg : std_logic_vector(15 downto 0);

  type   t_state is (IDLE, CONV, TRANS_0, TRANS_1, FIN);
  signal state : t_state;
  signal sclk  : std_logic;
  signal counter : unsigned(5 downto 0);

begin  -- rtl


  -- Main state machine. Executes SPI transfers
  p_main_fsm : process(clk_sys_i)
  begin
    if rising_edge(clk_sys_i) then
      if rst_n_i = '0' then
        state      <= IDLE;
        sclk       <= '0';
        rx_sreg    <= (others => '0');
        counter    <= (others => '0');
        cnv <= '0';
        sdi <= '1';
      else
        case state is
          -- Waits for start of transfer command
          when IDLE =>
            sclk    <= '0';
            counter <= (others => '0');
            if(start_i = '1') then
              state      <= CONV;
              cnv <= '1';
            end if;
          when CONV => 
            sdi <= '0';
            counter <= counter+1;
            if(counter = "101000") then           
              state <= TRANS_0;
              counter <= (others => '0');
            end if;
          when TRANS_0 =>
            sclk <= '1';
            state <= TRANS_1;
          when TRANS_1 => 
            counter <= counter +1;
            rx_sreg <= rx_sreg(14 downto 0) & spi_miso_i;
            if(counter = "1111") then
                state <= FIN;
                sdi <= '1';
            end if;
          when FIN =>
            sclk <= '0';
            cnv <= '0';
            data_o <= rx_sreg;
            state <= IDLE;
        end case;
      end if;
    end if;
  end process;

  spi_sclk_o <= (clk_sys_i) and sclk;
  
end behavioral;
