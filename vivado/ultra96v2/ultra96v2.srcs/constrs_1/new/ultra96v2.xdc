set_property IOSTANDARD LVCMOS18 [get_ports BT*]

#BT_HCI_RTS on FPGA / emio_uart0_ctsn
set_property PACKAGE_PIN B7 [get_ports BT_ctsn]
#BT_HCI_CTS on FPGA / emio_uart0_rtsn
set_property PACKAGE_PIN B5 [get_ports BT_rtsn]

set_property PACKAGE_PIN F8 [get_ports can_phy_tx_0]
set_property IOSTANDARD LVCMOS18 [get_ports can_phy_tx_0]
set_property IOSTANDARD LVCMOS18 [get_ports can_phy_rx_0]

set_property PACKAGE_PIN G7 [get_ports can_phy_rx_0]
