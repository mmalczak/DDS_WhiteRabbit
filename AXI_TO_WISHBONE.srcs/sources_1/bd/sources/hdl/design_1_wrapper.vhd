--Copyright 1986-2017 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2017.1 (lin64) Build 1846317 Fri Apr 14 18:54:47 MDT 2017
--Date        : Wed May 16 16:47:05 2018
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
    PD_CLK : out STD_LOGIC;
    PD_DATA : out STD_LOGIC;
    PLL1_SYNCB : out STD_LOGIC_VECTOR ( 0 to 0 );
    led : out STD_LOGIC;
    przycisk : in STD_LOGIC;
    save : in STD_LOGIC_VECTOR ( 39 downto 0 );
    spi_miso_i : in STD_LOGIC;
    spi_miso_i_1 : in STD_LOGIC;
    spi_mosi_ad95xx_o : out STD_LOGIC;
    spi_sclk_ad95xx_o : out STD_LOGIC;
    spi_sclk_o : out STD_LOGIC;
    wbt_adf4002_le_o : out STD_LOGIC;
    wbt_led_o : out STD_LOGIC_VECTOR ( 1 downto 0 );
    wbt_pll2_reset_n_o : out STD_LOGIC;
    wbt_spi_adc_cnv_o : out STD_LOGIC;
    wbt_spi_adc_sdi_o : out STD_LOGIC;
    wbt_spi_cs_ad9510_o : out STD_LOGIC;
    wbt_spi_cs_ad9516_o : out STD_LOGIC
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
    PLL1_SYNCB : out STD_LOGIC_VECTOR ( 0 to 0 );
    przycisk : in STD_LOGIC;
    led : out STD_LOGIC;
    spi_sclk_ad95xx_o : out STD_LOGIC;
    PD_CLK : out STD_LOGIC;
    spi_mosi_ad95xx_o : out STD_LOGIC;
    PD_DATA : out STD_LOGIC;
    spi_miso_i_1 : in STD_LOGIC;
    wbt_spi_cs_ad9516_o : out STD_LOGIC;
    wbt_spi_cs_ad9510_o : out STD_LOGIC;
    wbt_adf4002_le_o : out STD_LOGIC;
    wbt_pll2_reset_n_o : out STD_LOGIC;
    spi_miso_i : in STD_LOGIC;
    wbt_spi_adc_cnv_o : out STD_LOGIC;
    wbt_spi_adc_sdi_o : out STD_LOGIC;
    spi_sclk_o : out STD_LOGIC
  );
  end component design_1;
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
      PD_CLK => PD_CLK,
      PD_DATA => PD_DATA,
      PLL1_SYNCB(0) => PLL1_SYNCB(0),
      led => led,
      przycisk => przycisk,
      save(39 downto 0) => save(39 downto 0),
      spi_miso_i => spi_miso_i,
      spi_miso_i_1 => spi_miso_i_1,
      spi_mosi_ad95xx_o => spi_mosi_ad95xx_o,
      spi_sclk_ad95xx_o => spi_sclk_ad95xx_o,
      spi_sclk_o => spi_sclk_o,
      wbt_adf4002_le_o => wbt_adf4002_le_o,
      wbt_led_o(1 downto 0) => wbt_led_o(1 downto 0),
      wbt_pll2_reset_n_o => wbt_pll2_reset_n_o,
      wbt_spi_adc_cnv_o => wbt_spi_adc_cnv_o,
      wbt_spi_adc_sdi_o => wbt_spi_adc_sdi_o,
      wbt_spi_cs_ad9510_o => wbt_spi_cs_ad9510_o,
      wbt_spi_cs_ad9516_o => wbt_spi_cs_ad9516_o
    );
end STRUCTURE;
