-- Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2018.2 (lin64) Build 2258646 Thu Jun 14 20:02:38 MDT 2018
-- Date        : Tue Aug 20 14:03:18 2019
-- Host        : zw-pc running 64-bit Ubuntu 16.04.3 LTS
-- Command     : write_vhdl -force -mode synth_stub
--               /home/zw/swap/share/ultra96/SDSoC-Ultra96-V2/vivado/ultra96v2/ultra96v2.srcs/sources_1/bd/ultra96v2/ip/ultra96v2_xlconcat_1_0_2/ultra96v2_xlconcat_1_0_stub.vhdl
-- Design      : ultra96v2_xlconcat_1_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu3eg-sbva484-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ultra96v2_xlconcat_1_0 is
  Port ( 
    In0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    dout : out STD_LOGIC_VECTOR ( 0 to 0 )
  );

end ultra96v2_xlconcat_1_0;

architecture stub of ultra96v2_xlconcat_1_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "In0[0:0],dout[0:0]";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "xlconcat_v2_1_1_xlconcat,Vivado 2018.2";
begin
end;
