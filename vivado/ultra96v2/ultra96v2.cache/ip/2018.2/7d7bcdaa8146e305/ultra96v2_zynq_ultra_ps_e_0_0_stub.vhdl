-- Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2018.2 (lin64) Build 2258646 Thu Jun 14 20:02:38 MDT 2018
-- Date        : Tue Aug 20 14:03:32 2019
-- Host        : zw-pc running 64-bit Ubuntu 16.04.3 LTS
-- Command     : write_vhdl -force -mode synth_stub -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
--               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ ultra96v2_zynq_ultra_ps_e_0_0_stub.vhdl
-- Design      : ultra96v2_zynq_ultra_ps_e_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu3eg-sbva484-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
  Port ( 
    emio_uart0_ctsn : in STD_LOGIC;
    emio_uart0_rtsn : out STD_LOGIC;
    emio_uart0_dsrn : in STD_LOGIC;
    emio_uart0_dcdn : in STD_LOGIC;
    emio_uart0_rin : in STD_LOGIC;
    emio_uart0_dtrn : out STD_LOGIC;
    pl_ps_irq0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    pl_ps_irq1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    pl_resetn0 : out STD_LOGIC;
    pl_clk0 : out STD_LOGIC
  );

end decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix;

architecture stub of decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "emio_uart0_ctsn,emio_uart0_rtsn,emio_uart0_dsrn,emio_uart0_dcdn,emio_uart0_rin,emio_uart0_dtrn,pl_ps_irq0[0:0],pl_ps_irq1[0:0],pl_resetn0,pl_clk0";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "zynq_ultra_ps_e_v3_2_1_zynq_ultra_ps_e,Vivado 2018.2";
begin
end;
