-- Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2018.2 (lin64) Build 2258646 Thu Jun 14 20:02:38 MDT 2018
-- Date        : Tue Aug 20 14:03:19 2019
-- Host        : zw-pc running 64-bit Ubuntu 16.04.3 LTS
-- Command     : write_vhdl -force -mode funcsim
--               /home/zw/swap/share/ultra96/SDSoC-Ultra96-V2/vivado/ultra96v2/ultra96v2.srcs/sources_1/bd/ultra96v2/ip/ultra96v2_xlconcat_1_0_2/ultra96v2_xlconcat_1_0_sim_netlist.vhdl
-- Design      : ultra96v2_xlconcat_1_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu3eg-sbva484-1-e
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity ultra96v2_xlconcat_1_0 is
  port (
    In0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    dout : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of ultra96v2_xlconcat_1_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of ultra96v2_xlconcat_1_0 : entity is "ultra96v2_xlconcat_1_0,xlconcat_v2_1_1_xlconcat,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of ultra96v2_xlconcat_1_0 : entity is "yes";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of ultra96v2_xlconcat_1_0 : entity is "xlconcat_v2_1_1_xlconcat,Vivado 2018.2";
end ultra96v2_xlconcat_1_0;

architecture STRUCTURE of ultra96v2_xlconcat_1_0 is
  signal \^in0\ : STD_LOGIC_VECTOR ( 0 to 0 );
begin
  \^in0\(0) <= In0(0);
  dout(0) <= \^in0\(0);
end STRUCTURE;
