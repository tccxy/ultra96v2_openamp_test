// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.2 (lin64) Build 2258646 Thu Jun 14 20:02:38 MDT 2018
// Date        : Tue Aug 20 14:03:32 2019
// Host        : zw-pc running 64-bit Ubuntu 16.04.3 LTS
// Command     : write_verilog -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ ultra96v2_zynq_ultra_ps_e_0_0_stub.v
// Design      : ultra96v2_zynq_ultra_ps_e_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu3eg-sbva484-1-e
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "zynq_ultra_ps_e_v3_2_1_zynq_ultra_ps_e,Vivado 2018.2" *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix(emio_uart0_ctsn, emio_uart0_rtsn, 
  emio_uart0_dsrn, emio_uart0_dcdn, emio_uart0_rin, emio_uart0_dtrn, pl_ps_irq0, pl_ps_irq1, 
  pl_resetn0, pl_clk0)
/* synthesis syn_black_box black_box_pad_pin="emio_uart0_ctsn,emio_uart0_rtsn,emio_uart0_dsrn,emio_uart0_dcdn,emio_uart0_rin,emio_uart0_dtrn,pl_ps_irq0[0:0],pl_ps_irq1[0:0],pl_resetn0,pl_clk0" */;
  input emio_uart0_ctsn;
  output emio_uart0_rtsn;
  input emio_uart0_dsrn;
  input emio_uart0_dcdn;
  input emio_uart0_rin;
  output emio_uart0_dtrn;
  input [0:0]pl_ps_irq0;
  input [0:0]pl_ps_irq1;
  output pl_resetn0;
  output pl_clk0;
endmodule
