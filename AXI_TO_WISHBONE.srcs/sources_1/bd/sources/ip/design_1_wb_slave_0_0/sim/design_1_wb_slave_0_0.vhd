-- (c) Copyright 1995-2018 Xilinx, Inc. All rights reserved.
-- 
-- This file contains confidential and proprietary information
-- of Xilinx, Inc. and is protected under U.S. and
-- international copyright and other intellectual property
-- laws.
-- 
-- DISCLAIMER
-- This disclaimer is not a license and does not grant any
-- rights to the materials distributed herewith. Except as
-- otherwise provided in a valid license issued to you by
-- Xilinx, and to the maximum extent permitted by applicable
-- law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
-- WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
-- AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
-- BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
-- INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
-- (2) Xilinx shall not be liable (whether in contract or tort,
-- including negligence, or under any other theory of
-- liability) for any loss or damage of any kind or nature
-- related to, arising under or in connection with these
-- materials, including for any direct, or any indirect,
-- special, incidental, or consequential loss or damage
-- (including loss of data, profits, goodwill, or any type of
-- loss or damage suffered as a result of any action brought
-- by a third party) even if such damage or loss was
-- reasonably foreseeable or Xilinx had been advised of the
-- possibility of the same.
-- 
-- CRITICAL APPLICATIONS
-- Xilinx products are not designed or intended to be fail-
-- safe, or for use in any application requiring fail-safe
-- performance, such as life-support or safety devices or
-- systems, Class III medical devices, nuclear facilities,
-- applications related to the deployment of airbags, or any
-- other applications that could lead to death, personal
-- injury, or severe property or environmental damage
-- (individually and collectively, "Critical
-- Applications"). Customer assumes the sole risk and
-- liability of any use of Xilinx products in Critical
-- Applications, subject only to applicable laws and
-- regulations governing limitations on product liability.
-- 
-- THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
-- PART OF THIS FILE AT ALL TIMES.
-- 
-- DO NOT MODIFY THIS FILE.

-- IP VLNV: user.org:module_ref:wb_slave:1.0
-- IP Revision: 1

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY design_1_wb_slave_0_0 IS
  PORT (
    rst_n_i : IN STD_LOGIC;
    clk_sys_i : IN STD_LOGIC;
    wb_adr_i : IN STD_LOGIC_VECTOR(4 DOWNTO 0);
    wb_dat_i : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    wb_dat_o : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    wb_cyc_i : IN STD_LOGIC;
    wb_sel_i : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    wb_stb_i : IN STD_LOGIC;
    wb_we_i : IN STD_LOGIC;
    wb_ack_o : OUT STD_LOGIC;
    wb_stall_o : OUT STD_LOGIC;
    wbs_led_o : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    wbs_pll1_syncb_o : OUT STD_LOGIC;
    wbs_pll_freq_i : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    wbs_dds_freq_i : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    wbs_cnt_mask_o : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    wbs_spi_start_o : OUT STD_LOGIC;
    wbs_spi_cpol_o : OUT STD_LOGIC;
    wbs_spi_cs_ad9516_o : OUT STD_LOGIC;
    wbs_spi_cs_ad9510_o : OUT STD_LOGIC;
    wbs_spi_data_o : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
    wbs_adf4002_le_o : OUT STD_LOGIC;
    wbs_pll2_reset_n_o : OUT STD_LOGIC;
    wbs_spi_data_in_i : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
    wbs_x0_o : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    wbs_x1_o : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    wbs_adc_offset_o : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);
    wbs_loop_timer_o : OUT STD_LOGIC_VECTOR(15 DOWNTO 0)
  );
END design_1_wb_slave_0_0;

ARCHITECTURE design_1_wb_slave_0_0_arch OF design_1_wb_slave_0_0 IS
  ATTRIBUTE DowngradeIPIdentifiedWarnings : STRING;
  ATTRIBUTE DowngradeIPIdentifiedWarnings OF design_1_wb_slave_0_0_arch: ARCHITECTURE IS "yes";
  COMPONENT wb_slave IS
    PORT (
      rst_n_i : IN STD_LOGIC;
      clk_sys_i : IN STD_LOGIC;
      wb_adr_i : IN STD_LOGIC_VECTOR(4 DOWNTO 0);
      wb_dat_i : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
      wb_dat_o : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
      wb_cyc_i : IN STD_LOGIC;
      wb_sel_i : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
      wb_stb_i : IN STD_LOGIC;
      wb_we_i : IN STD_LOGIC;
      wb_ack_o : OUT STD_LOGIC;
      wb_stall_o : OUT STD_LOGIC;
      wbs_led_o : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      wbs_pll1_syncb_o : OUT STD_LOGIC;
      wbs_pll_freq_i : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
      wbs_dds_freq_i : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
      wbs_cnt_mask_o : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
      wbs_spi_start_o : OUT STD_LOGIC;
      wbs_spi_cpol_o : OUT STD_LOGIC;
      wbs_spi_cs_ad9516_o : OUT STD_LOGIC;
      wbs_spi_cs_ad9510_o : OUT STD_LOGIC;
      wbs_spi_data_o : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
      wbs_adf4002_le_o : OUT STD_LOGIC;
      wbs_pll2_reset_n_o : OUT STD_LOGIC;
      wbs_spi_data_in_i : IN STD_LOGIC_VECTOR(7 DOWNTO 0);
      wbs_x0_o : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
      wbs_x1_o : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
      wbs_adc_offset_o : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);
      wbs_loop_timer_o : OUT STD_LOGIC_VECTOR(15 DOWNTO 0)
    );
  END COMPONENT wb_slave;
BEGIN
  U0 : wb_slave
    PORT MAP (
      rst_n_i => rst_n_i,
      clk_sys_i => clk_sys_i,
      wb_adr_i => wb_adr_i,
      wb_dat_i => wb_dat_i,
      wb_dat_o => wb_dat_o,
      wb_cyc_i => wb_cyc_i,
      wb_sel_i => wb_sel_i,
      wb_stb_i => wb_stb_i,
      wb_we_i => wb_we_i,
      wb_ack_o => wb_ack_o,
      wb_stall_o => wb_stall_o,
      wbs_led_o => wbs_led_o,
      wbs_pll1_syncb_o => wbs_pll1_syncb_o,
      wbs_pll_freq_i => wbs_pll_freq_i,
      wbs_dds_freq_i => wbs_dds_freq_i,
      wbs_cnt_mask_o => wbs_cnt_mask_o,
      wbs_spi_start_o => wbs_spi_start_o,
      wbs_spi_cpol_o => wbs_spi_cpol_o,
      wbs_spi_cs_ad9516_o => wbs_spi_cs_ad9516_o,
      wbs_spi_cs_ad9510_o => wbs_spi_cs_ad9510_o,
      wbs_spi_data_o => wbs_spi_data_o,
      wbs_adf4002_le_o => wbs_adf4002_le_o,
      wbs_pll2_reset_n_o => wbs_pll2_reset_n_o,
      wbs_spi_data_in_i => wbs_spi_data_in_i,
      wbs_x0_o => wbs_x0_o,
      wbs_x1_o => wbs_x1_o,
      wbs_adc_offset_o => wbs_adc_offset_o,
      wbs_loop_timer_o => wbs_loop_timer_o
    );
END design_1_wb_slave_0_0_arch;
