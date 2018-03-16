# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "g_div_ratio_log2" -parent ${Page_0}
  ipgui::add_param $IPINST -name "g_num_data_bits" -parent ${Page_0}


}

proc update_PARAM_VALUE.g_div_ratio_log2 { PARAM_VALUE.g_div_ratio_log2 } {
	# Procedure called to update g_div_ratio_log2 when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.g_div_ratio_log2 { PARAM_VALUE.g_div_ratio_log2 } {
	# Procedure called to validate g_div_ratio_log2
	return true
}

proc update_PARAM_VALUE.g_num_data_bits { PARAM_VALUE.g_num_data_bits } {
	# Procedure called to update g_num_data_bits when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.g_num_data_bits { PARAM_VALUE.g_num_data_bits } {
	# Procedure called to validate g_num_data_bits
	return true
}


proc update_MODELPARAM_VALUE.g_div_ratio_log2 { MODELPARAM_VALUE.g_div_ratio_log2 PARAM_VALUE.g_div_ratio_log2 } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.g_div_ratio_log2}] ${MODELPARAM_VALUE.g_div_ratio_log2}
}

proc update_MODELPARAM_VALUE.g_num_data_bits { MODELPARAM_VALUE.g_num_data_bits PARAM_VALUE.g_num_data_bits } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.g_num_data_bits}] ${MODELPARAM_VALUE.g_num_data_bits}
}

