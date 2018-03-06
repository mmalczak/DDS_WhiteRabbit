################################################################################

# This XDC is used only for OOC mode of synthesis, implementation
# This constraints file contains default clock frequencies to be used during
# out-of-context flows such as OOC Synthesis and Hierarchical Designs.
# This constraints file is not used in normal top-down synthesis (default flow
# of Vivado)
################################################################################
create_clock -name IBUF_DS_P -period 10 [get_ports IBUF_DS_P]
create_clock -name IBUF_DS_N -period 10 [get_ports IBUF_DS_N]
create_clock -name CLK1_OUT_P -period 10 [get_ports CLK1_OUT_P]
create_clock -name CLK1_OUT_N -period 10 [get_ports CLK1_OUT_N]
create_clock -name CLK0_OUT_P -period 10 [get_ports CLK0_OUT_P]
create_clock -name CLK0_OUT_N -period 10 [get_ports CLK0_OUT_N]
create_clock -name CLK2_OUT_P -period 10 [get_ports CLK2_OUT_P]
create_clock -name CLK2_OUT_N -period 10 [get_ports CLK2_OUT_N]
create_clock -name processing_system7_0_FCLK_CLK0 -period 20 [get_pins processing_system7_0/FCLK_CLK0]

################################################################################