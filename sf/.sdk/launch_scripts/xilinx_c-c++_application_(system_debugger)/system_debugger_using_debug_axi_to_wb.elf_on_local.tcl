connect -url tcp:127.0.0.1:3121
source /home/milosz/Desktop/Xilinx/Vivado/projects/DDS_WhiteRabbit/sf/design_1_wrapper_hw_platform_0/ps7_init.tcl
targets -set -nocase -filter {name =~"APU*" && jtag_cable_name =~ "Digilent JTAG-SMT2 210251838770"} -index 0
stop
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent JTAG-SMT2 210251838770"} -index 0
rst -processor
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent JTAG-SMT2 210251838770"} -index 0
dow /home/milosz/Desktop/Xilinx/Vivado/projects/DDS_WhiteRabbit/sf/axi_to_wb/Debug/axi_to_wb.elf
targets -set -nocase -filter {name =~ "ARM*#0" && jtag_cable_name =~ "Digilent JTAG-SMT2 210251838770"} -index 0
con
