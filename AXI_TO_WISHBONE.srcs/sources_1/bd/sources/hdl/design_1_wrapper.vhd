--Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2017.1 (lin64) Build 1846317 Fri Apr 14 18:54:47 MDT 2017
--Date        : Mon Mar 12 15:17:37 2018
--Host        : milosz-System-Product-Name running 64-bit Linux Mint 18.2 Sonya
--Command     : generate_target design_1_wrapper.bd
--Design      : design_1_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity design_1_wrapper is
  port (
    CLK0_OUT_N : in STD_LOGIC_VECTOR ( 0 to 0 );
    CLK0_OUT_P : in STD_LOGIC_VECTOR ( 0 to 0 );
    CLK1_OUT_N : in STD_LOGIC_VECTOR ( 0 to 0 );
    CLK1_OUT_P : in STD_LOGIC_VECTOR ( 0 to 0 );
    CLK2_OUT_N : in STD_LOGIC_VECTOR ( 0 to 0 );
    CLK2_OUT_P : in STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_DAT_N : out STD_LOGIC_VECTOR ( 13 downto 0 );
    DAC_DAT_P : out STD_LOGIC_VECTOR ( 13 downto 0 );
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_cas_n : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    IBUF_DS_N : in STD_LOGIC_VECTOR ( 17 downto 0 );
    IBUF_DS_P : in STD_LOGIC_VECTOR ( 17 downto 0 );
    PLL1_SYNCB : out STD_LOGIC;
    STATUS_PIN : in STD_LOGIC;
    led : out STD_LOGIC;
    przycisk : in STD_LOGIC;
    save : in STD_LOGIC_VECTOR ( 39 downto 0 );
    spi_0_io0_io : inout STD_LOGIC;
    spi_0_io1_io : inout STD_LOGIC;
    spi_0_sck_io : inout STD_LOGIC;
    spi_0_ss_io : inout STD_LOGIC_VECTOR ( 1 downto 0 );
    wbt_led_o : out STD_LOGIC_VECTOR ( 1 downto 0 )
  );
end design_1_wrapper;

architecture STRUCTURE of design_1_wrapper is
  component design_1 is
  port (
    DDR_cas_n : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    SPI_0_io0_i : in STD_LOGIC;
    SPI_0_io0_o : out STD_LOGIC;
    SPI_0_io0_t : out STD_LOGIC;
    SPI_0_io1_i : in STD_LOGIC;
    SPI_0_io1_o : out STD_LOGIC;
    SPI_0_io1_t : out STD_LOGIC;
    SPI_0_sck_i : in STD_LOGIC;
    SPI_0_sck_o : out STD_LOGIC;
    SPI_0_sck_t : out STD_LOGIC;
    SPI_0_ss_i : in STD_LOGIC_VECTOR ( 1 downto 0 );
    SPI_0_ss_o : out STD_LOGIC_VECTOR ( 1 downto 0 );
    SPI_0_ss_t : out STD_LOGIC;
    STATUS_PIN : in STD_LOGIC;
    IBUF_DS_P : in STD_LOGIC_VECTOR ( 17 downto 0 );
    IBUF_DS_N : in STD_LOGIC_VECTOR ( 17 downto 0 );
    save : in STD_LOGIC_VECTOR ( 39 downto 0 );
    CLK1_OUT_P : in STD_LOGIC_VECTOR ( 0 to 0 );
    CLK1_OUT_N : in STD_LOGIC_VECTOR ( 0 to 0 );
    DAC_DAT_P : out STD_LOGIC_VECTOR ( 13 downto 0 );
    DAC_DAT_N : out STD_LOGIC_VECTOR ( 13 downto 0 );
    wbt_led_o : out STD_LOGIC_VECTOR ( 1 downto 0 );
    CLK0_OUT_P : in STD_LOGIC_VECTOR ( 0 to 0 );
    CLK0_OUT_N : in STD_LOGIC_VECTOR ( 0 to 0 );
    CLK2_OUT_P : in STD_LOGIC_VECTOR ( 0 to 0 );
    CLK2_OUT_N : in STD_LOGIC_VECTOR ( 0 to 0 );
    PLL1_SYNCB : out STD_LOGIC;
    przycisk : in STD_LOGIC;
    led : out STD_LOGIC
  );
  end component design_1;
  component IOBUF is
  port (
    I : in STD_LOGIC;
    O : out STD_LOGIC;
    T : in STD_LOGIC;
    IO : inout STD_LOGIC
  );
  end component IOBUF;
  signal spi_0_io0_i : STD_LOGIC;
  signal spi_0_io0_o : STD_LOGIC;
  signal spi_0_io0_t : STD_LOGIC;
  signal spi_0_io1_i : STD_LOGIC;
  signal spi_0_io1_o : STD_LOGIC;
  signal spi_0_io1_t : STD_LOGIC;
  signal spi_0_sck_i : STD_LOGIC;
  signal spi_0_sck_o : STD_LOGIC;
  signal spi_0_sck_t : STD_LOGIC;
  signal spi_0_ss_i_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal spi_0_ss_i_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal spi_0_ss_io_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal spi_0_ss_io_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal spi_0_ss_o_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal spi_0_ss_o_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal spi_0_ss_t : STD_LOGIC;
begin
design_1_i: component design_1
     port map (
      CLK0_OUT_N(0) => CLK0_OUT_N(0),
      CLK0_OUT_P(0) => CLK0_OUT_P(0),
      CLK1_OUT_N(0) => CLK1_OUT_N(0),
      CLK1_OUT_P(0) => CLK1_OUT_P(0),
      CLK2_OUT_N(0) => CLK2_OUT_N(0),
      CLK2_OUT_P(0) => CLK2_OUT_P(0),
      DAC_DAT_N(13 downto 0) => DAC_DAT_N(13 downto 0),
      DAC_DAT_P(13 downto 0) => DAC_DAT_P(13 downto 0),
      DDR_addr(14 downto 0) => DDR_addr(14 downto 0),
      DDR_ba(2 downto 0) => DDR_ba(2 downto 0),
      DDR_cas_n => DDR_cas_n,
      DDR_ck_n => DDR_ck_n,
      DDR_ck_p => DDR_ck_p,
      DDR_cke => DDR_cke,
      DDR_cs_n => DDR_cs_n,
      DDR_dm(3 downto 0) => DDR_dm(3 downto 0),
      DDR_dq(31 downto 0) => DDR_dq(31 downto 0),
      DDR_dqs_n(3 downto 0) => DDR_dqs_n(3 downto 0),
      DDR_dqs_p(3 downto 0) => DDR_dqs_p(3 downto 0),
      DDR_odt => DDR_odt,
      DDR_ras_n => DDR_ras_n,
      DDR_reset_n => DDR_reset_n,
      DDR_we_n => DDR_we_n,
      FIXED_IO_ddr_vrn => FIXED_IO_ddr_vrn,
      FIXED_IO_ddr_vrp => FIXED_IO_ddr_vrp,
      FIXED_IO_mio(53 downto 0) => FIXED_IO_mio(53 downto 0),
      FIXED_IO_ps_clk => FIXED_IO_ps_clk,
      FIXED_IO_ps_porb => FIXED_IO_ps_porb,
      FIXED_IO_ps_srstb => FIXED_IO_ps_srstb,
      IBUF_DS_N(17 downto 0) => IBUF_DS_N(17 downto 0),
      IBUF_DS_P(17 downto 0) => IBUF_DS_P(17 downto 0),
      PLL1_SYNCB => PLL1_SYNCB,
      SPI_0_io0_i => spi_0_io0_i,
      SPI_0_io0_o => spi_0_io0_o,
      SPI_0_io0_t => spi_0_io0_t,
      SPI_0_io1_i => spi_0_io1_i,
      SPI_0_io1_o => spi_0_io1_o,
      SPI_0_io1_t => spi_0_io1_t,
      SPI_0_sck_i => spi_0_sck_i,
      SPI_0_sck_o => spi_0_sck_o,
      SPI_0_sck_t => spi_0_sck_t,
      SPI_0_ss_i(1) => spi_0_ss_i_1(1),
      SPI_0_ss_i(0) => spi_0_ss_i_0(0),
      SPI_0_ss_o(1) => spi_0_ss_o_1(1),
      SPI_0_ss_o(0) => spi_0_ss_o_0(0),
      SPI_0_ss_t => spi_0_ss_t,
      STATUS_PIN => STATUS_PIN,
      led => led,
      przycisk => przycisk,
      save(39 downto 0) => save(39 downto 0),
      wbt_led_o(1 downto 0) => wbt_led_o(1 downto 0)
    );
spi_0_io0_iobuf: component IOBUF
     port map (
      I => spi_0_io0_o,
      IO => spi_0_io0_io,
      O => spi_0_io0_i,
      T => spi_0_io0_t
    );
spi_0_io1_iobuf: component IOBUF
     port map (
      I => spi_0_io1_o,
      IO => spi_0_io1_io,
      O => spi_0_io1_i,
      T => spi_0_io1_t
    );
spi_0_sck_iobuf: component IOBUF
     port map (
      I => spi_0_sck_o,
      IO => spi_0_sck_io,
      O => spi_0_sck_i,
      T => spi_0_sck_t
    );
spi_0_ss_iobuf_0: component IOBUF
     port map (
      I => spi_0_ss_o_0(0),
      IO => spi_0_ss_io(0),
      O => spi_0_ss_i_0(0),
      T => spi_0_ss_t
    );
spi_0_ss_iobuf_1: component IOBUF
     port map (
      I => spi_0_ss_o_1(1),
      IO => spi_0_ss_io(1),
      O => spi_0_ss_i_1(1),
      T => spi_0_ss_t
    );
end STRUCTURE;
