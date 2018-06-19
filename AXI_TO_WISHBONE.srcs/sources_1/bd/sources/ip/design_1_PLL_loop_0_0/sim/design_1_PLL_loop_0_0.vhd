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

-- IP VLNV: user.org:module_ref:PLL_loop:1.0
-- IP Revision: 1

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY design_1_PLL_loop_0_0 IS
  PORT (
    clk_50 : IN STD_LOGIC;
    clk_dds : IN STD_LOGIC;
    res : IN STD_LOGIC;
    res_soft : IN STD_LOGIC;
    x0 : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    x1 : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    freq_accum_on : IN STD_LOGIC;
    spi_miso_i : IN STD_LOGIC;
    adc_offset : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
    timer : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
    cnv : OUT STD_LOGIC;
    sdi : OUT STD_LOGIC;
    spi_sclk_o : OUT STD_LOGIC;
    dout_dds_P : OUT STD_LOGIC_VECTOR(13 DOWNTO 0);
    dout_dds_N : OUT STD_LOGIC_VECTOR(13 DOWNTO 0)
  );
END design_1_PLL_loop_0_0;

ARCHITECTURE design_1_PLL_loop_0_0_arch OF design_1_PLL_loop_0_0 IS
  ATTRIBUTE DowngradeIPIdentifiedWarnings : STRING;
  ATTRIBUTE DowngradeIPIdentifiedWarnings OF design_1_PLL_loop_0_0_arch: ARCHITECTURE IS "yes";
  COMPONENT PLL_loop IS
    PORT (
      clk_50 : IN STD_LOGIC;
      clk_dds : IN STD_LOGIC;
      res : IN STD_LOGIC;
      res_soft : IN STD_LOGIC;
      x0 : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
      x1 : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
      freq_accum_on : IN STD_LOGIC;
      spi_miso_i : IN STD_LOGIC;
      adc_offset : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
      timer : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
      cnv : OUT STD_LOGIC;
      sdi : OUT STD_LOGIC;
      spi_sclk_o : OUT STD_LOGIC;
      dout_dds_P : OUT STD_LOGIC_VECTOR(13 DOWNTO 0);
      dout_dds_N : OUT STD_LOGIC_VECTOR(13 DOWNTO 0)
    );
  END COMPONENT PLL_loop;
BEGIN
  U0 : PLL_loop
    PORT MAP (
      clk_50 => clk_50,
      clk_dds => clk_dds,
      res => res,
      res_soft => res_soft,
      x0 => x0,
      x1 => x1,
      freq_accum_on => freq_accum_on,
      spi_miso_i => spi_miso_i,
      adc_offset => adc_offset,
      timer => timer,
      cnv => cnv,
      sdi => sdi,
      spi_sclk_o => spi_sclk_o,
      dout_dds_P => dout_dds_P,
      dout_dds_N => dout_dds_N
    );
END design_1_PLL_loop_0_0_arch;
