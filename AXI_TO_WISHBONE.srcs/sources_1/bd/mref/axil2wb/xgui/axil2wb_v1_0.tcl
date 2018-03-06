# Definitional proc to organize widgets for parameters.
proc init_gui { IPINST } {
  ipgui::add_param $IPINST -name "Component_Name"
  #Adding Page
  set Page_0 [ipgui::add_page $IPINST -name "Page 0"]
  ipgui::add_param $IPINST -name "ADRWIDTH" -parent ${Page_0}
  ipgui::add_param $IPINST -name "DATAWIDTH" -parent ${Page_0}


}

proc update_PARAM_VALUE.ADRWIDTH { PARAM_VALUE.ADRWIDTH } {
	# Procedure called to update ADRWIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.ADRWIDTH { PARAM_VALUE.ADRWIDTH } {
	# Procedure called to validate ADRWIDTH
	return true
}

proc update_PARAM_VALUE.DATAWIDTH { PARAM_VALUE.DATAWIDTH } {
	# Procedure called to update DATAWIDTH when any of the dependent parameters in the arguments change
}

proc validate_PARAM_VALUE.DATAWIDTH { PARAM_VALUE.DATAWIDTH } {
	# Procedure called to validate DATAWIDTH
	return true
}


proc update_MODELPARAM_VALUE.ADRWIDTH { MODELPARAM_VALUE.ADRWIDTH PARAM_VALUE.ADRWIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.ADRWIDTH}] ${MODELPARAM_VALUE.ADRWIDTH}
}

proc update_MODELPARAM_VALUE.DATAWIDTH { MODELPARAM_VALUE.DATAWIDTH PARAM_VALUE.DATAWIDTH } {
	# Procedure called to set VHDL generic/Verilog parameter value(s) based on TCL parameter value
	set_property value [get_property value ${PARAM_VALUE.DATAWIDTH}] ${MODELPARAM_VALUE.DATAWIDTH}
}

