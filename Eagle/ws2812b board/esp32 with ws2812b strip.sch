<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.3.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="ESP32-DEVKITV1">
<packages>
<package name="ESP32-DEVKITV1">
<pad name="1" x="-22.87" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="2" x="-20.33" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="3" x="-17.79" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="4" x="-15.25" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="5" x="-12.71" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="6" x="-10.17" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="7" x="-7.63" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="8" x="-5.09" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="9" x="-2.55" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="10" x="-0.01" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="11" x="2.53" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="12" x="5.07" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="13" x="7.61" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="14" x="10.15" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="15" x="12.69" y="-13.54" drill="1" diameter="1.9304"/>
<pad name="30" x="-22.87" y="11.23" drill="1" diameter="1.9304"/>
<pad name="29" x="-20.33" y="11.23" drill="1" diameter="1.9304"/>
<pad name="28" x="-17.79" y="11.23" drill="1" diameter="1.9304"/>
<pad name="27" x="-15.25" y="11.23" drill="1" diameter="1.9304"/>
<pad name="26" x="-12.71" y="11.23" drill="1" diameter="1.9304"/>
<pad name="25" x="-10.17" y="11.23" drill="1" diameter="1.9304"/>
<pad name="24" x="-7.63" y="11.23" drill="1" diameter="1.9304"/>
<pad name="23" x="-5.09" y="11.23" drill="1" diameter="1.9304"/>
<pad name="22" x="-2.55" y="11.23" drill="1" diameter="1.9304"/>
<pad name="21" x="-0.01" y="11.23" drill="1" diameter="1.9304"/>
<pad name="20" x="2.53" y="11.23" drill="1" diameter="1.9304"/>
<pad name="19" x="5.07" y="11.23" drill="1" diameter="1.9304"/>
<pad name="18" x="7.61" y="11.23" drill="1" diameter="1.9304"/>
<pad name="17" x="10.15" y="11.23" drill="1" diameter="1.9304"/>
<pad name="16" x="12.69" y="11.23" drill="1" diameter="1.9304"/>
<text x="-22.21" y="-11.2" size="1.016" layer="21" rot="R90">3V3</text>
<text x="-19.67" y="-11.2" size="1.016" layer="21" rot="R90">GND</text>
<text x="-17.13" y="-11.2" size="1.016" layer="21" rot="R90">IO15</text>
<text x="-14.59" y="-11.2" size="1.016" layer="21" rot="R90">IO2</text>
<text x="-12.05" y="-11.2" size="1.016" layer="21" rot="R90">IO4</text>
<text x="-9.51" y="-11.2" size="1.016" layer="21" rot="R90">IO16</text>
<text x="-6.97" y="-11.2" size="1.016" layer="21" rot="R90">IO17</text>
<text x="-4.43" y="-11.2" size="1.016" layer="21" rot="R90">IO5</text>
<text x="-1.89" y="-11.2" size="1.016" layer="21" rot="R90">IO18</text>
<text x="0.65" y="-11.2" size="1.016" layer="21" rot="R90">IO19</text>
<text x="3.19" y="-11.2" size="1.016" layer="21" rot="R90">IO21</text>
<text x="5.73" y="-11.2" size="1.016" layer="21" rot="R90">IO3</text>
<text x="8.27" y="-11.2" size="1.016" layer="21" rot="R90">IO1</text>
<text x="10.81" y="-11.2" size="1.016" layer="21" rot="R90">IO22</text>
<text x="13.35" y="-11.2" size="1.016" layer="21" rot="R90">IO23</text>
<text x="-22.19" y="6.52" size="1.016" layer="21" rot="R90">VIN</text>
<text x="-19.65" y="6.52" size="1.016" layer="21" rot="R90">GND</text>
<text x="-17.11" y="6.52" size="1.016" layer="21" rot="R90">IO13</text>
<text x="-14.57" y="6.52" size="1.016" layer="21" rot="R90">IO12</text>
<text x="-12.03" y="6.52" size="1.016" layer="21" rot="R90">IO14</text>
<text x="-9.49" y="6.52" size="1.016" layer="21" rot="R90">IO27</text>
<text x="-6.95" y="6.52" size="1.016" layer="21" rot="R90">IO26</text>
<text x="-4.41" y="6.52" size="1.016" layer="21" rot="R90">IO25</text>
<text x="-1.87" y="6.52" size="1.016" layer="21" rot="R90">IO33</text>
<text x="0.67" y="6.52" size="1.016" layer="21" rot="R90">IO32</text>
<text x="3.21" y="6.52" size="1.016" layer="21" rot="R90">IO35</text>
<text x="5.75" y="6.52" size="1.016" layer="21" rot="R90">IO34</text>
<text x="8.29" y="6.52" size="1.016" layer="21" rot="R90">VN</text>
<text x="10.83" y="6.52" size="1.016" layer="21" rot="R90">VP</text>
<text x="13.37" y="6.52" size="1.016" layer="21" rot="R90">EN</text>
<text x="-4.93" y="-3.18" size="1.9304" layer="21">ESP32-Devkit V1</text>
<wire x1="-33" y1="12.7" x2="19" y2="12.7" width="0.254" layer="21"/>
<wire x1="19" y1="12.7" x2="19" y2="-15.2" width="0.254" layer="21"/>
<wire x1="19" y1="-15.2" x2="-33" y2="-15.2" width="0.254" layer="21"/>
<wire x1="-33" y1="-15.2" x2="-33" y2="12.7" width="0.254" layer="21"/>
<text x="-24.13" y="13.97" size="1.27" layer="21">&gt;NAME</text>
<text x="5" y="-17.24" size="1.27" layer="27">ESP32-DEVKITV1</text>
</package>
</packages>
<symbols>
<symbol name="ESP32-DEVKITV1">
<wire x1="-25.4" y1="-12.7" x2="-25.4" y2="12.7" width="0.254" layer="94"/>
<wire x1="-25.4" y1="12.7" x2="16" y2="12.7" width="0.254" layer="94"/>
<wire x1="16" y1="12.7" x2="16" y2="-12.7" width="0.254" layer="94"/>
<wire x1="16" y1="-12.7" x2="-25.4" y2="-12.7" width="0.254" layer="94"/>
<pin name="3V3" x="-22.86" y="-17.78" length="middle" rot="R90"/>
<pin name="GND" x="-20.32" y="-17.78" length="middle" rot="R90"/>
<pin name="IO15" x="-17.78" y="-17.78" length="middle" rot="R90"/>
<pin name="IO2" x="-15.24" y="-17.78" length="middle" rot="R90"/>
<pin name="IO4" x="-12.7" y="-17.78" length="middle" rot="R90"/>
<pin name="IO16" x="-10.16" y="-17.78" length="middle" rot="R90"/>
<pin name="IO17" x="-7.62" y="-17.78" length="middle" rot="R90"/>
<pin name="IO5" x="-5.08" y="-17.78" length="middle" rot="R90"/>
<pin name="IO18" x="-2.54" y="-17.78" length="middle" rot="R90"/>
<pin name="IO19" x="0" y="-17.78" length="middle" rot="R90"/>
<pin name="IO21" x="2.54" y="-17.78" length="middle" rot="R90"/>
<pin name="IO3" x="5.08" y="-17.78" length="middle" rot="R90"/>
<pin name="IO1" x="7.62" y="-17.78" length="middle" rot="R90"/>
<pin name="IO22" x="10.16" y="-17.78" length="middle" rot="R90"/>
<pin name="IO23" x="12.7" y="-17.78" length="middle" rot="R90"/>
<pin name="EN" x="12.7" y="17.78" length="middle" rot="R270"/>
<pin name="VP" x="10.16" y="17.78" length="middle" rot="R270"/>
<pin name="VN" x="7.62" y="17.78" length="middle" rot="R270"/>
<pin name="IO34" x="5.08" y="17.78" length="middle" rot="R270"/>
<pin name="IO35" x="2.54" y="17.78" length="middle" rot="R270"/>
<pin name="IO32" x="0" y="17.78" length="middle" rot="R270"/>
<pin name="IO33" x="-2.54" y="17.78" length="middle" rot="R270"/>
<pin name="IO25" x="-5.08" y="17.78" length="middle" rot="R270"/>
<pin name="IO26" x="-7.62" y="17.78" length="middle" rot="R270"/>
<pin name="IO27" x="-10.16" y="17.78" length="middle" rot="R270"/>
<pin name="IO14" x="-12.7" y="17.78" length="middle" rot="R270"/>
<pin name="IO12" x="-15.24" y="17.78" length="middle" rot="R270"/>
<pin name="IO13" x="-17.78" y="17.78" length="middle" rot="R270"/>
<pin name="GND1" x="-20.32" y="17.78" length="middle" rot="R270"/>
<pin name="VIN" x="-22.86" y="17.78" length="middle" rot="R270"/>
<text x="-26.67" y="5.08" size="1.27" layer="95" rot="R90">&gt;NAME</text>
<text x="18.4" y="-12.7" size="1.27" layer="96" rot="R90">ESP32-DEVKITV1</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="ESP32DEVKITV1">
<gates>
<gate name="G$1" symbol="ESP32-DEVKITV1" x="0" y="0"/>
</gates>
<devices>
<device name="" package="ESP32-DEVKITV1">
<connects>
<connect gate="G$1" pin="3V3" pad="1"/>
<connect gate="G$1" pin="EN" pad="16"/>
<connect gate="G$1" pin="GND" pad="2"/>
<connect gate="G$1" pin="GND1" pad="28"/>
<connect gate="G$1" pin="IO1" pad="13"/>
<connect gate="G$1" pin="IO12" pad="27"/>
<connect gate="G$1" pin="IO13" pad="28"/>
<connect gate="G$1" pin="IO14" pad="26"/>
<connect gate="G$1" pin="IO15" pad="3"/>
<connect gate="G$1" pin="IO16" pad="6"/>
<connect gate="G$1" pin="IO17" pad="7"/>
<connect gate="G$1" pin="IO18" pad="9"/>
<connect gate="G$1" pin="IO19" pad="10"/>
<connect gate="G$1" pin="IO2" pad="4"/>
<connect gate="G$1" pin="IO21" pad="11"/>
<connect gate="G$1" pin="IO22" pad="14"/>
<connect gate="G$1" pin="IO23" pad="15"/>
<connect gate="G$1" pin="IO25" pad="23"/>
<connect gate="G$1" pin="IO26" pad="24"/>
<connect gate="G$1" pin="IO27" pad="24"/>
<connect gate="G$1" pin="IO3" pad="12"/>
<connect gate="G$1" pin="IO32" pad="21"/>
<connect gate="G$1" pin="IO33" pad="22"/>
<connect gate="G$1" pin="IO34" pad="19"/>
<connect gate="G$1" pin="IO35" pad="20"/>
<connect gate="G$1" pin="IO4" pad="5"/>
<connect gate="G$1" pin="IO5" pad="8"/>
<connect gate="G$1" pin="VIN" pad="30"/>
<connect gate="G$1" pin="VN" pad="18"/>
<connect gate="G$1" pin="VP" pad="17"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="ws2812b">
<packages>
<package name="SINGLESTRIP">
<wire x1="0" y1="0" x2="15.24" y2="0" width="0.127" layer="21"/>
<wire x1="15.24" y1="0" x2="15.24" y2="10.16" width="0.127" layer="21"/>
<wire x1="15.24" y1="10.16" x2="0" y2="10.16" width="0.127" layer="21"/>
<wire x1="0" y1="10.16" x2="0" y2="0" width="0.127" layer="21"/>
<circle x="7.62" y="5.08" radius="2.83980625" width="0.127" layer="21"/>
<wire x1="10.16" y1="1.27" x2="3.81" y2="1.27" width="0.127" layer="21"/>
<smd name="5VOUT" x="-0.635" y="8.255" dx="2" dy="1.5" layer="1"/>
<smd name="GNDOUT" x="-0.635" y="1.905" dx="2" dy="1.5" layer="1"/>
<smd name="5VIN" x="15.875" y="8.255" dx="2" dy="1.5" layer="1"/>
<smd name="DATAIN#" x="15.875" y="5.08" dx="2" dy="1.5" layer="1"/>
<smd name="GNDIN" x="15.875" y="1.905" dx="2" dy="1.5" layer="1"/>
<smd name="DATAOUT" x="-0.635" y="5.08" dx="2" dy="1.5" layer="1"/>
<wire x1="3.81" y1="1.27" x2="4.445" y2="1.905" width="0.127" layer="21"/>
<wire x1="3.81" y1="1.27" x2="4.445" y2="0.635" width="0.127" layer="21"/>
<text x="4.445" y="10.795" size="1.27" layer="25">&gt;NAME</text>
<wire x1="-0.635" y1="8.255" x2="15.875" y2="8.255" width="0.6096" layer="1"/>
<wire x1="-0.635" y1="1.905" x2="15.875" y2="1.905" width="0.6096" layer="1"/>
</package>
</packages>
<symbols>
<symbol name="SINGLESTRIP">
<pin name="5VOUT" x="-15.24" y="5.08" length="middle" direction="pwr"/>
<pin name="DATAOUT" x="-15.24" y="0" length="middle" direction="out"/>
<pin name="GNDOUT" x="-15.24" y="-5.08" length="middle" direction="pwr"/>
<pin name="5VIN" x="17.78" y="5.08" length="middle" direction="pwr" rot="R180"/>
<pin name="DATAIN" x="17.78" y="0" length="middle" direction="in" rot="R180"/>
<pin name="GNDIN" x="17.78" y="-5.08" length="middle" direction="pwr" rot="R180"/>
<wire x1="-10.16" y1="-7.62" x2="-10.16" y2="7.62" width="0.254" layer="94"/>
<wire x1="-10.16" y1="7.62" x2="12.7" y2="7.62" width="0.254" layer="94"/>
<wire x1="12.7" y1="7.62" x2="12.7" y2="-7.62" width="0.254" layer="94"/>
<wire x1="12.7" y1="-7.62" x2="-10.16" y2="-7.62" width="0.254" layer="94"/>
<text x="-2.54" y="10.16" size="1.778" layer="95">&gt;Name</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="SINGLESTRIP" prefix="LED">
<gates>
<gate name="G$1" symbol="SINGLESTRIP" x="33.02" y="-10.16"/>
</gates>
<devices>
<device name="" package="SINGLESTRIP">
<connects>
<connect gate="G$1" pin="5VIN" pad="5VIN"/>
<connect gate="G$1" pin="5VOUT" pad="5VOUT"/>
<connect gate="G$1" pin="DATAIN" pad="DATAIN#"/>
<connect gate="G$1" pin="DATAOUT" pad="DATAOUT"/>
<connect gate="G$1" pin="GNDIN" pad="GNDIN"/>
<connect gate="G$1" pin="GNDOUT" pad="GNDOUT"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="pinhead" urn="urn:adsk.eagle:library:325">
<description>&lt;b&gt;Pin Header Connectors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="1X04" urn="urn:adsk.eagle:footprint:22258/1" library_version="3">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="0" y1="0.635" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-3.175" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="-1.27" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-4.445" y1="1.27" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="-0.635" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-3.175" y1="-1.27" x2="-4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="4.445" y2="1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="1.27" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="5.08" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-0.635" x2="4.445" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="3.175" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="4.445" y1="-1.27" x2="3.175" y2="-1.27" width="0.1524" layer="21"/>
<pad name="1" x="-3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="3.81" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-5.1562" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-5.08" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="-4.064" y1="-0.254" x2="-3.556" y2="0.254" layer="51"/>
<rectangle x1="3.556" y1="-0.254" x2="4.064" y2="0.254" layer="51"/>
</package>
<package name="1X04/90" urn="urn:adsk.eagle:footprint:22259/1" library_version="3">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-5.08" y1="-1.905" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-5.08" y1="0.635" x2="-5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-3.81" y1="6.985" x2="-3.81" y2="1.27" width="0.762" layer="21"/>
<wire x1="-2.54" y1="-1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="6.985" x2="-1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="6.985" x2="1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="5.08" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="5.08" y1="-1.905" x2="5.08" y2="0.635" width="0.1524" layer="21"/>
<wire x1="5.08" y1="0.635" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="3.81" y1="6.985" x2="3.81" y2="1.27" width="0.762" layer="21"/>
<pad name="1" x="-3.81" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="-1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="3" x="1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="4" x="3.81" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<text x="-5.715" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="6.985" y="-4.445" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-4.191" y1="0.635" x2="-3.429" y2="1.143" layer="21"/>
<rectangle x1="-1.651" y1="0.635" x2="-0.889" y2="1.143" layer="21"/>
<rectangle x1="0.889" y1="0.635" x2="1.651" y2="1.143" layer="21"/>
<rectangle x1="3.429" y1="0.635" x2="4.191" y2="1.143" layer="21"/>
<rectangle x1="-4.191" y1="-2.921" x2="-3.429" y2="-1.905" layer="21"/>
<rectangle x1="-1.651" y1="-2.921" x2="-0.889" y2="-1.905" layer="21"/>
<rectangle x1="0.889" y1="-2.921" x2="1.651" y2="-1.905" layer="21"/>
<rectangle x1="3.429" y1="-2.921" x2="4.191" y2="-1.905" layer="21"/>
</package>
<package name="1X02" urn="urn:adsk.eagle:footprint:22309/1" library_version="3">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-1.905" y1="1.27" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-2.6162" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
</package>
<package name="1X02/90" urn="urn:adsk.eagle:footprint:22310/1" library_version="3">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-2.54" y1="-1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="6.985" x2="-1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="6.985" x2="1.27" y2="1.27" width="0.762" layer="21"/>
<pad name="1" x="-1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<text x="-3.175" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.445" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-1.651" y1="0.635" x2="-0.889" y2="1.143" layer="21"/>
<rectangle x1="0.889" y1="0.635" x2="1.651" y2="1.143" layer="21"/>
<rectangle x1="-1.651" y1="-2.921" x2="-0.889" y2="-1.905" layer="21"/>
<rectangle x1="0.889" y1="-2.921" x2="1.651" y2="-1.905" layer="21"/>
</package>
</packages>
<packages3d>
<package3d name="1X04" urn="urn:adsk.eagle:package:22407/2" type="model" library_version="3">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X04"/>
</packageinstances>
</package3d>
<package3d name="1X04/90" urn="urn:adsk.eagle:package:22404/2" type="model" library_version="3">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X04/90"/>
</packageinstances>
</package3d>
<package3d name="1X02" urn="urn:adsk.eagle:package:22435/2" type="model" library_version="3">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X02"/>
</packageinstances>
</package3d>
<package3d name="1X02/90" urn="urn:adsk.eagle:package:22437/2" type="model" library_version="3">
<description>PIN HEADER</description>
<packageinstances>
<packageinstance name="1X02/90"/>
</packageinstances>
</package3d>
</packages3d>
<symbols>
<symbol name="PINHD4" urn="urn:adsk.eagle:symbol:22257/1" library_version="3">
<wire x1="-6.35" y1="-5.08" x2="1.27" y2="-5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-5.08" x2="1.27" y2="7.62" width="0.4064" layer="94"/>
<wire x1="1.27" y1="7.62" x2="-6.35" y2="7.62" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="7.62" x2="-6.35" y2="-5.08" width="0.4064" layer="94"/>
<text x="-6.35" y="8.255" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-7.62" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="5.08" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="3" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="4" x="-2.54" y="-2.54" visible="pad" length="short" direction="pas" function="dot"/>
</symbol>
<symbol name="PINHD2" urn="urn:adsk.eagle:symbol:22308/1" library_version="3">
<wire x1="-6.35" y1="-2.54" x2="1.27" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="1.27" y2="5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="5.08" x2="-6.35" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="5.08" x2="-6.35" y2="-2.54" width="0.4064" layer="94"/>
<text x="-6.35" y="5.715" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="PINHD-1X4" urn="urn:adsk.eagle:component:22499/4" prefix="JP" uservalue="yes" library_version="3">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="A" symbol="PINHD4" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1X04">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22407/2"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="/90" package="1X04/90">
<connects>
<connect gate="A" pin="1" pad="1"/>
<connect gate="A" pin="2" pad="2"/>
<connect gate="A" pin="3" pad="3"/>
<connect gate="A" pin="4" pad="4"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22404/2"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PINHD-1X2" urn="urn:adsk.eagle:component:22516/3" prefix="JP" uservalue="yes" library_version="3">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="PINHD2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1X02">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22435/2"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="/90" package="1X02/90">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<package3dinstances>
<package3dinstance package3d_urn="urn:adsk.eagle:package:22437/2"/>
</package3dinstances>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="ESP32-DEVKITV1" deviceset="ESP32DEVKITV1" device=""/>
<part name="LED1" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED2" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED3" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED4" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED5" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED6" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED7" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED8" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED9" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED10" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED11" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED12" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED13" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED14" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED15" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED16" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED17" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED18" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED19" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED20" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED21" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED22" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED23" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED24" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED25" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED26" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED27" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED28" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED29" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED30" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED31" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED32" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED33" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED34" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED35" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED36" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED37" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED38" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED39" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED40" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED41" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED42" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED43" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED44" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED45" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED46" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED47" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED48" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED49" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED50" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED51" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED52" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED53" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED54" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED55" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED56" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED57" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED58" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED59" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED60" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED61" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED62" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED63" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED64" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED65" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED66" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED67" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED68" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED69" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED70" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED71" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED72" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED73" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED74" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED75" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED76" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED77" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED78" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED79" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED80" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED81" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED82" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED83" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED84" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED85" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED86" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED87" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED88" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED89" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED90" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED91" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED92" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED93" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED94" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED95" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED96" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED97" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED98" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED99" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED100" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED101" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED102" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED103" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED104" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED105" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED106" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED107" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED108" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED109" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED110" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED111" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED112" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED113" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="LED114" library="ws2812b" deviceset="SINGLESTRIP" device=""/>
<part name="USBIN" library="pinhead" library_urn="urn:adsk.eagle:library:325" deviceset="PINHD-1X4" device="" package3d_urn="urn:adsk.eagle:package:22407/2"/>
<part name="USBOUT" library="pinhead" library_urn="urn:adsk.eagle:library:325" deviceset="PINHD-1X4" device="" package3d_urn="urn:adsk.eagle:package:22407/2"/>
<part name="BUTTON" library="pinhead" library_urn="urn:adsk.eagle:library:325" deviceset="PINHD-1X2" device="" package3d_urn="urn:adsk.eagle:package:22435/2"/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="276.86" y="167.64" smashed="yes" rot="R90">
<attribute name="NAME" x="271.78" y="140.97" size="1.27" layer="95" rot="R180"/>
</instance>
<instance part="LED1" gate="G$1" x="200.66" y="142.24" smashed="yes">
<attribute name="NAME" x="198.12" y="152.4" size="1.778" layer="95"/>
</instance>
<instance part="LED2" gate="G$1" x="167.64" y="142.24" smashed="yes">
<attribute name="NAME" x="165.1" y="152.4" size="1.778" layer="95"/>
</instance>
<instance part="LED3" gate="G$1" x="134.62" y="142.24" smashed="yes">
<attribute name="NAME" x="132.08" y="152.4" size="1.778" layer="95"/>
</instance>
<instance part="LED4" gate="G$1" x="101.6" y="142.24" smashed="yes">
<attribute name="NAME" x="99.06" y="152.4" size="1.778" layer="95"/>
</instance>
<instance part="LED5" gate="G$1" x="68.58" y="142.24" smashed="yes">
<attribute name="NAME" x="66.04" y="152.4" size="1.778" layer="95"/>
</instance>
<instance part="LED6" gate="G$1" x="35.56" y="142.24" smashed="yes">
<attribute name="NAME" x="33.02" y="152.4" size="1.778" layer="95"/>
</instance>
<instance part="LED7" gate="G$1" x="2.54" y="142.24" smashed="yes">
<attribute name="NAME" x="0" y="152.4" size="1.778" layer="95"/>
</instance>
<instance part="LED8" gate="G$1" x="-30.48" y="142.24" smashed="yes">
<attribute name="NAME" x="-33.02" y="152.4" size="1.778" layer="95"/>
</instance>
<instance part="LED9" gate="G$1" x="-63.5" y="142.24" smashed="yes">
<attribute name="NAME" x="-66.04" y="152.4" size="1.778" layer="95"/>
</instance>
<instance part="LED10" gate="G$1" x="-96.52" y="142.24" smashed="yes">
<attribute name="NAME" x="-99.06" y="152.4" size="1.778" layer="95"/>
</instance>
<instance part="LED11" gate="G$1" x="-93.98" y="124.46" smashed="yes" rot="R180">
<attribute name="NAME" x="-91.44" y="114.3" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED12" gate="G$1" x="-60.96" y="124.46" smashed="yes" rot="R180">
<attribute name="NAME" x="-58.42" y="114.3" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED13" gate="G$1" x="-27.94" y="124.46" smashed="yes" rot="R180">
<attribute name="NAME" x="-25.4" y="114.3" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED14" gate="G$1" x="5.08" y="124.46" smashed="yes" rot="R180">
<attribute name="NAME" x="7.62" y="114.3" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED15" gate="G$1" x="38.1" y="124.46" smashed="yes" rot="R180">
<attribute name="NAME" x="40.64" y="114.3" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED16" gate="G$1" x="71.12" y="124.46" smashed="yes" rot="R180">
<attribute name="NAME" x="73.66" y="114.3" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED17" gate="G$1" x="104.14" y="124.46" smashed="yes" rot="R180">
<attribute name="NAME" x="106.68" y="114.3" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED18" gate="G$1" x="137.16" y="124.46" smashed="yes" rot="R180">
<attribute name="NAME" x="139.7" y="114.3" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED19" gate="G$1" x="170.18" y="124.46" smashed="yes" rot="R180">
<attribute name="NAME" x="172.72" y="114.3" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED20" gate="G$1" x="203.2" y="124.46" smashed="yes" rot="R180">
<attribute name="NAME" x="205.74" y="114.3" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED21" gate="G$1" x="200.66" y="96.52" smashed="yes">
<attribute name="NAME" x="198.12" y="106.68" size="1.778" layer="95"/>
</instance>
<instance part="LED22" gate="G$1" x="167.64" y="96.52" smashed="yes">
<attribute name="NAME" x="165.1" y="106.68" size="1.778" layer="95"/>
</instance>
<instance part="LED23" gate="G$1" x="134.62" y="96.52" smashed="yes">
<attribute name="NAME" x="132.08" y="106.68" size="1.778" layer="95"/>
</instance>
<instance part="LED24" gate="G$1" x="101.6" y="96.52" smashed="yes">
<attribute name="NAME" x="99.06" y="106.68" size="1.778" layer="95"/>
</instance>
<instance part="LED25" gate="G$1" x="68.58" y="96.52" smashed="yes">
<attribute name="NAME" x="66.04" y="106.68" size="1.778" layer="95"/>
</instance>
<instance part="LED26" gate="G$1" x="35.56" y="96.52" smashed="yes">
<attribute name="NAME" x="33.02" y="106.68" size="1.778" layer="95"/>
</instance>
<instance part="LED27" gate="G$1" x="2.54" y="96.52" smashed="yes">
<attribute name="NAME" x="0" y="106.68" size="1.778" layer="95"/>
</instance>
<instance part="LED28" gate="G$1" x="-30.48" y="96.52" smashed="yes">
<attribute name="NAME" x="-33.02" y="106.68" size="1.778" layer="95"/>
</instance>
<instance part="LED29" gate="G$1" x="-63.5" y="96.52" smashed="yes">
<attribute name="NAME" x="-66.04" y="106.68" size="1.778" layer="95"/>
</instance>
<instance part="LED30" gate="G$1" x="-96.52" y="96.52" smashed="yes">
<attribute name="NAME" x="-99.06" y="106.68" size="1.778" layer="95"/>
</instance>
<instance part="LED31" gate="G$1" x="-93.98" y="78.74" smashed="yes" rot="R180">
<attribute name="NAME" x="-91.44" y="68.58" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED32" gate="G$1" x="-60.96" y="78.74" smashed="yes" rot="R180">
<attribute name="NAME" x="-58.42" y="68.58" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED33" gate="G$1" x="-27.94" y="78.74" smashed="yes" rot="R180">
<attribute name="NAME" x="-25.4" y="68.58" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED34" gate="G$1" x="5.08" y="78.74" smashed="yes" rot="R180">
<attribute name="NAME" x="7.62" y="68.58" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED35" gate="G$1" x="38.1" y="78.74" smashed="yes" rot="R180">
<attribute name="NAME" x="40.64" y="68.58" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED36" gate="G$1" x="71.12" y="78.74" smashed="yes" rot="R180">
<attribute name="NAME" x="73.66" y="68.58" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED37" gate="G$1" x="104.14" y="78.74" smashed="yes" rot="R180">
<attribute name="NAME" x="106.68" y="68.58" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED38" gate="G$1" x="137.16" y="78.74" smashed="yes" rot="R180">
<attribute name="NAME" x="139.7" y="68.58" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED39" gate="G$1" x="170.18" y="78.74" smashed="yes" rot="R180">
<attribute name="NAME" x="172.72" y="68.58" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED40" gate="G$1" x="203.2" y="78.74" smashed="yes" rot="R180">
<attribute name="NAME" x="205.74" y="68.58" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED41" gate="G$1" x="200.66" y="53.34" smashed="yes">
<attribute name="NAME" x="198.12" y="63.5" size="1.778" layer="95"/>
</instance>
<instance part="LED42" gate="G$1" x="167.64" y="53.34" smashed="yes">
<attribute name="NAME" x="165.1" y="63.5" size="1.778" layer="95"/>
</instance>
<instance part="LED43" gate="G$1" x="134.62" y="53.34" smashed="yes">
<attribute name="NAME" x="132.08" y="63.5" size="1.778" layer="95"/>
</instance>
<instance part="LED44" gate="G$1" x="101.6" y="53.34" smashed="yes">
<attribute name="NAME" x="99.06" y="63.5" size="1.778" layer="95"/>
</instance>
<instance part="LED45" gate="G$1" x="68.58" y="53.34" smashed="yes">
<attribute name="NAME" x="66.04" y="63.5" size="1.778" layer="95"/>
</instance>
<instance part="LED46" gate="G$1" x="35.56" y="53.34" smashed="yes">
<attribute name="NAME" x="33.02" y="63.5" size="1.778" layer="95"/>
</instance>
<instance part="LED47" gate="G$1" x="2.54" y="53.34" smashed="yes">
<attribute name="NAME" x="0" y="63.5" size="1.778" layer="95"/>
</instance>
<instance part="LED48" gate="G$1" x="-30.48" y="53.34" smashed="yes">
<attribute name="NAME" x="-33.02" y="63.5" size="1.778" layer="95"/>
</instance>
<instance part="LED49" gate="G$1" x="-63.5" y="53.34" smashed="yes">
<attribute name="NAME" x="-66.04" y="63.5" size="1.778" layer="95"/>
</instance>
<instance part="LED50" gate="G$1" x="-96.52" y="53.34" smashed="yes">
<attribute name="NAME" x="-99.06" y="63.5" size="1.778" layer="95"/>
</instance>
<instance part="LED51" gate="G$1" x="-93.98" y="35.56" smashed="yes" rot="R180">
<attribute name="NAME" x="-91.44" y="25.4" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED52" gate="G$1" x="-60.96" y="35.56" smashed="yes" rot="R180">
<attribute name="NAME" x="-58.42" y="25.4" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED53" gate="G$1" x="-27.94" y="35.56" smashed="yes" rot="R180">
<attribute name="NAME" x="-25.4" y="25.4" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED54" gate="G$1" x="5.08" y="35.56" smashed="yes" rot="R180">
<attribute name="NAME" x="7.62" y="25.4" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED55" gate="G$1" x="38.1" y="35.56" smashed="yes" rot="R180">
<attribute name="NAME" x="40.64" y="25.4" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED56" gate="G$1" x="71.12" y="35.56" smashed="yes" rot="R180">
<attribute name="NAME" x="73.66" y="25.4" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED57" gate="G$1" x="104.14" y="35.56" smashed="yes" rot="R180">
<attribute name="NAME" x="106.68" y="25.4" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED58" gate="G$1" x="137.16" y="35.56" smashed="yes" rot="R180">
<attribute name="NAME" x="139.7" y="25.4" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED59" gate="G$1" x="170.18" y="35.56" smashed="yes" rot="R180">
<attribute name="NAME" x="172.72" y="25.4" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED60" gate="G$1" x="203.2" y="35.56" smashed="yes" rot="R180">
<attribute name="NAME" x="205.74" y="25.4" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED61" gate="G$1" x="200.66" y="7.62" smashed="yes">
<attribute name="NAME" x="198.12" y="17.78" size="1.778" layer="95"/>
</instance>
<instance part="LED62" gate="G$1" x="167.64" y="7.62" smashed="yes">
<attribute name="NAME" x="165.1" y="17.78" size="1.778" layer="95"/>
</instance>
<instance part="LED63" gate="G$1" x="134.62" y="7.62" smashed="yes">
<attribute name="NAME" x="132.08" y="17.78" size="1.778" layer="95"/>
</instance>
<instance part="LED64" gate="G$1" x="101.6" y="7.62" smashed="yes">
<attribute name="NAME" x="99.06" y="17.78" size="1.778" layer="95"/>
</instance>
<instance part="LED65" gate="G$1" x="68.58" y="7.62" smashed="yes">
<attribute name="NAME" x="66.04" y="17.78" size="1.778" layer="95"/>
</instance>
<instance part="LED66" gate="G$1" x="35.56" y="7.62" smashed="yes">
<attribute name="NAME" x="33.02" y="17.78" size="1.778" layer="95"/>
</instance>
<instance part="LED67" gate="G$1" x="2.54" y="7.62" smashed="yes">
<attribute name="NAME" x="0" y="17.78" size="1.778" layer="95"/>
</instance>
<instance part="LED68" gate="G$1" x="-30.48" y="7.62" smashed="yes">
<attribute name="NAME" x="-33.02" y="17.78" size="1.778" layer="95"/>
</instance>
<instance part="LED69" gate="G$1" x="-63.5" y="7.62" smashed="yes">
<attribute name="NAME" x="-66.04" y="17.78" size="1.778" layer="95"/>
</instance>
<instance part="LED70" gate="G$1" x="-96.52" y="7.62" smashed="yes">
<attribute name="NAME" x="-99.06" y="17.78" size="1.778" layer="95"/>
</instance>
<instance part="LED71" gate="G$1" x="-93.98" y="-10.16" smashed="yes" rot="R180">
<attribute name="NAME" x="-91.44" y="-20.32" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED72" gate="G$1" x="-60.96" y="-10.16" smashed="yes" rot="R180">
<attribute name="NAME" x="-58.42" y="-20.32" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED73" gate="G$1" x="-27.94" y="-10.16" smashed="yes" rot="R180">
<attribute name="NAME" x="-25.4" y="-20.32" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED74" gate="G$1" x="5.08" y="-10.16" smashed="yes" rot="R180">
<attribute name="NAME" x="7.62" y="-20.32" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED75" gate="G$1" x="38.1" y="-10.16" smashed="yes" rot="R180">
<attribute name="NAME" x="40.64" y="-20.32" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED76" gate="G$1" x="71.12" y="-10.16" smashed="yes" rot="R180">
<attribute name="NAME" x="73.66" y="-20.32" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED77" gate="G$1" x="104.14" y="-10.16" smashed="yes" rot="R180">
<attribute name="NAME" x="106.68" y="-20.32" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED78" gate="G$1" x="137.16" y="-10.16" smashed="yes" rot="R180">
<attribute name="NAME" x="139.7" y="-20.32" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED79" gate="G$1" x="170.18" y="-10.16" smashed="yes" rot="R180">
<attribute name="NAME" x="172.72" y="-20.32" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED80" gate="G$1" x="203.2" y="-10.16" smashed="yes" rot="R180">
<attribute name="NAME" x="205.74" y="-20.32" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED81" gate="G$1" x="200.66" y="-35.56" smashed="yes">
<attribute name="NAME" x="198.12" y="-25.4" size="1.778" layer="95"/>
</instance>
<instance part="LED82" gate="G$1" x="167.64" y="-35.56" smashed="yes">
<attribute name="NAME" x="165.1" y="-25.4" size="1.778" layer="95"/>
</instance>
<instance part="LED83" gate="G$1" x="134.62" y="-35.56" smashed="yes">
<attribute name="NAME" x="132.08" y="-25.4" size="1.778" layer="95"/>
</instance>
<instance part="LED84" gate="G$1" x="101.6" y="-35.56" smashed="yes">
<attribute name="NAME" x="99.06" y="-25.4" size="1.778" layer="95"/>
</instance>
<instance part="LED85" gate="G$1" x="68.58" y="-35.56" smashed="yes">
<attribute name="NAME" x="66.04" y="-25.4" size="1.778" layer="95"/>
</instance>
<instance part="LED86" gate="G$1" x="35.56" y="-35.56" smashed="yes">
<attribute name="NAME" x="33.02" y="-25.4" size="1.778" layer="95"/>
</instance>
<instance part="LED87" gate="G$1" x="2.54" y="-35.56" smashed="yes">
<attribute name="NAME" x="0" y="-25.4" size="1.778" layer="95"/>
</instance>
<instance part="LED88" gate="G$1" x="-30.48" y="-35.56" smashed="yes">
<attribute name="NAME" x="-33.02" y="-25.4" size="1.778" layer="95"/>
</instance>
<instance part="LED89" gate="G$1" x="-63.5" y="-35.56" smashed="yes">
<attribute name="NAME" x="-66.04" y="-25.4" size="1.778" layer="95"/>
</instance>
<instance part="LED90" gate="G$1" x="-96.52" y="-35.56" smashed="yes">
<attribute name="NAME" x="-99.06" y="-25.4" size="1.778" layer="95"/>
</instance>
<instance part="LED91" gate="G$1" x="-93.98" y="-53.34" smashed="yes" rot="R180">
<attribute name="NAME" x="-91.44" y="-63.5" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED92" gate="G$1" x="-60.96" y="-53.34" smashed="yes" rot="R180">
<attribute name="NAME" x="-58.42" y="-63.5" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED93" gate="G$1" x="-27.94" y="-53.34" smashed="yes" rot="R180">
<attribute name="NAME" x="-25.4" y="-63.5" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED94" gate="G$1" x="5.08" y="-53.34" smashed="yes" rot="R180">
<attribute name="NAME" x="7.62" y="-63.5" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED95" gate="G$1" x="38.1" y="-53.34" smashed="yes" rot="R180">
<attribute name="NAME" x="40.64" y="-63.5" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED96" gate="G$1" x="71.12" y="-53.34" smashed="yes" rot="R180">
<attribute name="NAME" x="73.66" y="-63.5" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED97" gate="G$1" x="104.14" y="-53.34" smashed="yes" rot="R180">
<attribute name="NAME" x="106.68" y="-63.5" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED98" gate="G$1" x="137.16" y="-53.34" smashed="yes" rot="R180">
<attribute name="NAME" x="139.7" y="-63.5" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED99" gate="G$1" x="170.18" y="-53.34" smashed="yes" rot="R180">
<attribute name="NAME" x="172.72" y="-63.5" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED100" gate="G$1" x="203.2" y="-53.34" smashed="yes" rot="R180">
<attribute name="NAME" x="205.74" y="-63.5" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED101" gate="G$1" x="200.66" y="-81.28" smashed="yes">
<attribute name="NAME" x="198.12" y="-71.12" size="1.778" layer="95"/>
</instance>
<instance part="LED102" gate="G$1" x="167.64" y="-81.28" smashed="yes">
<attribute name="NAME" x="165.1" y="-71.12" size="1.778" layer="95"/>
</instance>
<instance part="LED103" gate="G$1" x="134.62" y="-81.28" smashed="yes">
<attribute name="NAME" x="132.08" y="-71.12" size="1.778" layer="95"/>
</instance>
<instance part="LED104" gate="G$1" x="101.6" y="-81.28" smashed="yes">
<attribute name="NAME" x="99.06" y="-71.12" size="1.778" layer="95"/>
</instance>
<instance part="LED105" gate="G$1" x="68.58" y="-81.28" smashed="yes">
<attribute name="NAME" x="66.04" y="-71.12" size="1.778" layer="95"/>
</instance>
<instance part="LED106" gate="G$1" x="35.56" y="-81.28" smashed="yes">
<attribute name="NAME" x="33.02" y="-71.12" size="1.778" layer="95"/>
</instance>
<instance part="LED107" gate="G$1" x="2.54" y="-81.28" smashed="yes">
<attribute name="NAME" x="0" y="-71.12" size="1.778" layer="95"/>
</instance>
<instance part="LED108" gate="G$1" x="-30.48" y="-81.28" smashed="yes">
<attribute name="NAME" x="-33.02" y="-71.12" size="1.778" layer="95"/>
</instance>
<instance part="LED109" gate="G$1" x="-63.5" y="-81.28" smashed="yes">
<attribute name="NAME" x="-66.04" y="-71.12" size="1.778" layer="95"/>
</instance>
<instance part="LED110" gate="G$1" x="-96.52" y="-81.28" smashed="yes">
<attribute name="NAME" x="-99.06" y="-71.12" size="1.778" layer="95"/>
</instance>
<instance part="LED111" gate="G$1" x="-93.98" y="-99.06" smashed="yes" rot="R180">
<attribute name="NAME" x="-91.44" y="-109.22" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED112" gate="G$1" x="-60.96" y="-99.06" smashed="yes" rot="R180">
<attribute name="NAME" x="-58.42" y="-109.22" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED113" gate="G$1" x="-27.94" y="-99.06" smashed="yes" rot="R180">
<attribute name="NAME" x="-25.4" y="-109.22" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="LED114" gate="G$1" x="5.08" y="-99.06" smashed="yes" rot="R180">
<attribute name="NAME" x="7.62" y="-109.22" size="1.778" layer="95" rot="R180"/>
</instance>
<instance part="USBIN" gate="A" x="218.44" y="200.66" smashed="yes" rot="R180">
<attribute name="NAME" x="224.79" y="192.405" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="224.79" y="208.28" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="USBOUT" gate="A" x="251.46" y="200.66" smashed="yes" rot="R180">
<attribute name="NAME" x="257.81" y="192.405" size="1.778" layer="95" rot="R180"/>
<attribute name="VALUE" x="257.81" y="208.28" size="1.778" layer="96" rot="R180"/>
</instance>
<instance part="BUTTON" gate="G$1" x="317.5" y="165.1" smashed="yes">
<attribute name="NAME" x="311.15" y="170.815" size="1.778" layer="95"/>
<attribute name="VALUE" x="311.15" y="160.02" size="1.778" layer="96"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="N$2" class="0">
<segment>
<pinref part="LED1" gate="G$1" pin="DATAOUT"/>
<pinref part="LED2" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="LED1" gate="G$1" pin="GNDOUT"/>
<pinref part="LED2" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="LED2" gate="G$1" pin="5VOUT"/>
<pinref part="LED3" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="LED2" gate="G$1" pin="DATAOUT"/>
<pinref part="LED3" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="LED2" gate="G$1" pin="GNDOUT"/>
<pinref part="LED3" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="LED3" gate="G$1" pin="5VOUT"/>
<pinref part="LED4" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="LED3" gate="G$1" pin="DATAOUT"/>
<pinref part="LED4" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="LED3" gate="G$1" pin="GNDOUT"/>
<pinref part="LED4" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="LED4" gate="G$1" pin="5VOUT"/>
<pinref part="LED5" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="LED4" gate="G$1" pin="DATAOUT"/>
<pinref part="LED5" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<pinref part="LED4" gate="G$1" pin="GNDOUT"/>
<pinref part="LED5" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="LED5" gate="G$1" pin="5VOUT"/>
<pinref part="LED6" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="LED5" gate="G$1" pin="DATAOUT"/>
<pinref part="LED6" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="LED5" gate="G$1" pin="GNDOUT"/>
<pinref part="LED6" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<pinref part="LED6" gate="G$1" pin="5VOUT"/>
<pinref part="LED7" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="LED6" gate="G$1" pin="DATAOUT"/>
<pinref part="LED7" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="LED6" gate="G$1" pin="GNDOUT"/>
<pinref part="LED7" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="LED7" gate="G$1" pin="5VOUT"/>
<pinref part="LED8" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="LED7" gate="G$1" pin="DATAOUT"/>
<pinref part="LED8" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<pinref part="LED7" gate="G$1" pin="GNDOUT"/>
<pinref part="LED8" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$22" class="0">
<segment>
<pinref part="LED8" gate="G$1" pin="5VOUT"/>
<pinref part="LED9" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$23" class="0">
<segment>
<pinref part="LED8" gate="G$1" pin="DATAOUT"/>
<pinref part="LED9" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$24" class="0">
<segment>
<pinref part="LED8" gate="G$1" pin="GNDOUT"/>
<pinref part="LED9" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$25" class="0">
<segment>
<pinref part="LED9" gate="G$1" pin="5VOUT"/>
<pinref part="LED10" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$26" class="0">
<segment>
<pinref part="LED9" gate="G$1" pin="DATAOUT"/>
<pinref part="LED10" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$27" class="0">
<segment>
<pinref part="LED9" gate="G$1" pin="GNDOUT"/>
<pinref part="LED10" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$28" class="0">
<segment>
<pinref part="LED11" gate="G$1" pin="5VOUT"/>
<pinref part="LED12" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$29" class="0">
<segment>
<pinref part="LED11" gate="G$1" pin="DATAOUT"/>
<pinref part="LED12" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$30" class="0">
<segment>
<pinref part="LED11" gate="G$1" pin="GNDOUT"/>
<pinref part="LED12" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$31" class="0">
<segment>
<pinref part="LED12" gate="G$1" pin="5VOUT"/>
<pinref part="LED13" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$32" class="0">
<segment>
<pinref part="LED12" gate="G$1" pin="DATAOUT"/>
<pinref part="LED13" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$34" class="0">
<segment>
<pinref part="LED13" gate="G$1" pin="5VOUT"/>
<pinref part="LED14" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$35" class="0">
<segment>
<pinref part="LED13" gate="G$1" pin="DATAOUT"/>
<pinref part="LED14" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$36" class="0">
<segment>
<pinref part="LED13" gate="G$1" pin="GNDOUT"/>
<pinref part="LED14" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$37" class="0">
<segment>
<pinref part="LED14" gate="G$1" pin="5VOUT"/>
<pinref part="LED15" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$38" class="0">
<segment>
<pinref part="LED14" gate="G$1" pin="DATAOUT"/>
<pinref part="LED15" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$39" class="0">
<segment>
<pinref part="LED14" gate="G$1" pin="GNDOUT"/>
<pinref part="LED15" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$40" class="0">
<segment>
<pinref part="LED15" gate="G$1" pin="5VOUT"/>
<pinref part="LED16" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$41" class="0">
<segment>
<pinref part="LED15" gate="G$1" pin="DATAOUT"/>
<pinref part="LED16" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$42" class="0">
<segment>
<pinref part="LED15" gate="G$1" pin="GNDOUT"/>
<pinref part="LED16" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$43" class="0">
<segment>
<pinref part="LED16" gate="G$1" pin="5VOUT"/>
<pinref part="LED17" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$44" class="0">
<segment>
<pinref part="LED16" gate="G$1" pin="DATAOUT"/>
<pinref part="LED17" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$45" class="0">
<segment>
<pinref part="LED16" gate="G$1" pin="GNDOUT"/>
<pinref part="LED17" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$46" class="0">
<segment>
<pinref part="LED17" gate="G$1" pin="5VOUT"/>
<pinref part="LED18" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$47" class="0">
<segment>
<pinref part="LED17" gate="G$1" pin="DATAOUT"/>
<pinref part="LED18" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$48" class="0">
<segment>
<pinref part="LED17" gate="G$1" pin="GNDOUT"/>
<pinref part="LED18" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$49" class="0">
<segment>
<pinref part="LED18" gate="G$1" pin="5VOUT"/>
<pinref part="LED19" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$50" class="0">
<segment>
<pinref part="LED18" gate="G$1" pin="DATAOUT"/>
<pinref part="LED19" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$51" class="0">
<segment>
<pinref part="LED18" gate="G$1" pin="GNDOUT"/>
<pinref part="LED19" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$52" class="0">
<segment>
<pinref part="LED19" gate="G$1" pin="5VOUT"/>
<pinref part="LED20" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$53" class="0">
<segment>
<pinref part="LED19" gate="G$1" pin="DATAOUT"/>
<pinref part="LED20" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$54" class="0">
<segment>
<pinref part="LED19" gate="G$1" pin="GNDOUT"/>
<pinref part="LED20" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$55" class="0">
<segment>
<pinref part="LED10" gate="G$1" pin="GNDOUT"/>
<wire x1="-111.76" y1="137.16" x2="-116.84" y2="137.16" width="0.1524" layer="91"/>
<wire x1="-116.84" y1="137.16" x2="-116.84" y2="129.54" width="0.1524" layer="91"/>
<pinref part="LED11" gate="G$1" pin="GNDIN"/>
<wire x1="-116.84" y1="129.54" x2="-111.76" y2="129.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$56" class="0">
<segment>
<pinref part="LED10" gate="G$1" pin="DATAOUT"/>
<wire x1="-111.76" y1="142.24" x2="-119.38" y2="142.24" width="0.1524" layer="91"/>
<pinref part="LED11" gate="G$1" pin="DATAIN"/>
<wire x1="-119.38" y1="142.24" x2="-119.38" y2="124.46" width="0.1524" layer="91"/>
<wire x1="-119.38" y1="124.46" x2="-111.76" y2="124.46" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$57" class="0">
<segment>
<pinref part="LED11" gate="G$1" pin="5VIN"/>
<wire x1="-111.76" y1="119.38" x2="-121.92" y2="119.38" width="0.1524" layer="91"/>
<pinref part="LED10" gate="G$1" pin="5VOUT"/>
<wire x1="-121.92" y1="119.38" x2="-121.92" y2="147.32" width="0.1524" layer="91"/>
<wire x1="-121.92" y1="147.32" x2="-111.76" y2="147.32" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$58" class="0">
<segment>
<pinref part="LED21" gate="G$1" pin="5VOUT"/>
<pinref part="LED22" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$59" class="0">
<segment>
<pinref part="LED21" gate="G$1" pin="DATAOUT"/>
<pinref part="LED22" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$60" class="0">
<segment>
<pinref part="LED21" gate="G$1" pin="GNDOUT"/>
<pinref part="LED22" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$62" class="0">
<segment>
<pinref part="LED22" gate="G$1" pin="DATAOUT"/>
<pinref part="LED23" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$63" class="0">
<segment>
<pinref part="LED22" gate="G$1" pin="GNDOUT"/>
<pinref part="LED23" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$64" class="0">
<segment>
<pinref part="LED23" gate="G$1" pin="5VOUT"/>
<pinref part="LED24" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$65" class="0">
<segment>
<pinref part="LED23" gate="G$1" pin="DATAOUT"/>
<pinref part="LED24" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$66" class="0">
<segment>
<pinref part="LED23" gate="G$1" pin="GNDOUT"/>
<pinref part="LED24" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$67" class="0">
<segment>
<pinref part="LED24" gate="G$1" pin="5VOUT"/>
<pinref part="LED25" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$68" class="0">
<segment>
<pinref part="LED24" gate="G$1" pin="DATAOUT"/>
<pinref part="LED25" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$69" class="0">
<segment>
<pinref part="LED24" gate="G$1" pin="GNDOUT"/>
<pinref part="LED25" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$70" class="0">
<segment>
<pinref part="LED25" gate="G$1" pin="5VOUT"/>
<pinref part="LED26" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$71" class="0">
<segment>
<pinref part="LED25" gate="G$1" pin="DATAOUT"/>
<pinref part="LED26" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$72" class="0">
<segment>
<pinref part="LED25" gate="G$1" pin="GNDOUT"/>
<pinref part="LED26" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$73" class="0">
<segment>
<pinref part="LED26" gate="G$1" pin="5VOUT"/>
<pinref part="LED27" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$74" class="0">
<segment>
<pinref part="LED26" gate="G$1" pin="DATAOUT"/>
<pinref part="LED27" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$75" class="0">
<segment>
<pinref part="LED26" gate="G$1" pin="GNDOUT"/>
<pinref part="LED27" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$76" class="0">
<segment>
<pinref part="LED27" gate="G$1" pin="5VOUT"/>
<pinref part="LED28" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$77" class="0">
<segment>
<pinref part="LED27" gate="G$1" pin="DATAOUT"/>
<pinref part="LED28" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$78" class="0">
<segment>
<pinref part="LED27" gate="G$1" pin="GNDOUT"/>
<pinref part="LED28" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$79" class="0">
<segment>
<pinref part="LED28" gate="G$1" pin="5VOUT"/>
<pinref part="LED29" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$80" class="0">
<segment>
<pinref part="LED28" gate="G$1" pin="DATAOUT"/>
<pinref part="LED29" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$81" class="0">
<segment>
<pinref part="LED28" gate="G$1" pin="GNDOUT"/>
<pinref part="LED29" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$82" class="0">
<segment>
<pinref part="LED29" gate="G$1" pin="5VOUT"/>
<pinref part="LED30" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$83" class="0">
<segment>
<pinref part="LED29" gate="G$1" pin="DATAOUT"/>
<pinref part="LED30" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$84" class="0">
<segment>
<pinref part="LED29" gate="G$1" pin="GNDOUT"/>
<pinref part="LED30" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$85" class="0">
<segment>
<pinref part="LED31" gate="G$1" pin="5VOUT"/>
<pinref part="LED32" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$86" class="0">
<segment>
<pinref part="LED31" gate="G$1" pin="DATAOUT"/>
<pinref part="LED32" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$87" class="0">
<segment>
<pinref part="LED31" gate="G$1" pin="GNDOUT"/>
<pinref part="LED32" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$88" class="0">
<segment>
<pinref part="LED32" gate="G$1" pin="5VOUT"/>
<pinref part="LED33" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$89" class="0">
<segment>
<pinref part="LED32" gate="G$1" pin="DATAOUT"/>
<pinref part="LED33" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$91" class="0">
<segment>
<pinref part="LED33" gate="G$1" pin="5VOUT"/>
<pinref part="LED34" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$92" class="0">
<segment>
<pinref part="LED33" gate="G$1" pin="DATAOUT"/>
<pinref part="LED34" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$93" class="0">
<segment>
<pinref part="LED33" gate="G$1" pin="GNDOUT"/>
<pinref part="LED34" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$94" class="0">
<segment>
<pinref part="LED34" gate="G$1" pin="5VOUT"/>
<pinref part="LED35" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$95" class="0">
<segment>
<pinref part="LED34" gate="G$1" pin="DATAOUT"/>
<pinref part="LED35" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$96" class="0">
<segment>
<pinref part="LED34" gate="G$1" pin="GNDOUT"/>
<pinref part="LED35" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$97" class="0">
<segment>
<pinref part="LED35" gate="G$1" pin="5VOUT"/>
<pinref part="LED36" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$98" class="0">
<segment>
<pinref part="LED35" gate="G$1" pin="DATAOUT"/>
<pinref part="LED36" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$99" class="0">
<segment>
<pinref part="LED35" gate="G$1" pin="GNDOUT"/>
<pinref part="LED36" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$100" class="0">
<segment>
<pinref part="LED36" gate="G$1" pin="5VOUT"/>
<pinref part="LED37" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$101" class="0">
<segment>
<pinref part="LED36" gate="G$1" pin="DATAOUT"/>
<pinref part="LED37" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$102" class="0">
<segment>
<pinref part="LED36" gate="G$1" pin="GNDOUT"/>
<pinref part="LED37" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$103" class="0">
<segment>
<pinref part="LED37" gate="G$1" pin="5VOUT"/>
<pinref part="LED38" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$104" class="0">
<segment>
<pinref part="LED37" gate="G$1" pin="DATAOUT"/>
<pinref part="LED38" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$105" class="0">
<segment>
<pinref part="LED37" gate="G$1" pin="GNDOUT"/>
<pinref part="LED38" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$106" class="0">
<segment>
<pinref part="LED38" gate="G$1" pin="5VOUT"/>
<pinref part="LED39" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$107" class="0">
<segment>
<pinref part="LED38" gate="G$1" pin="DATAOUT"/>
<pinref part="LED39" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$108" class="0">
<segment>
<pinref part="LED38" gate="G$1" pin="GNDOUT"/>
<pinref part="LED39" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$109" class="0">
<segment>
<pinref part="LED39" gate="G$1" pin="5VOUT"/>
<pinref part="LED40" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$110" class="0">
<segment>
<pinref part="LED39" gate="G$1" pin="DATAOUT"/>
<pinref part="LED40" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$111" class="0">
<segment>
<pinref part="LED39" gate="G$1" pin="GNDOUT"/>
<pinref part="LED40" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$112" class="0">
<segment>
<pinref part="LED30" gate="G$1" pin="GNDOUT"/>
<wire x1="-111.76" y1="91.44" x2="-116.84" y2="91.44" width="0.1524" layer="91"/>
<wire x1="-116.84" y1="91.44" x2="-116.84" y2="83.82" width="0.1524" layer="91"/>
<pinref part="LED31" gate="G$1" pin="GNDIN"/>
<wire x1="-116.84" y1="83.82" x2="-111.76" y2="83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$113" class="0">
<segment>
<pinref part="LED30" gate="G$1" pin="DATAOUT"/>
<wire x1="-111.76" y1="96.52" x2="-119.38" y2="96.52" width="0.1524" layer="91"/>
<pinref part="LED31" gate="G$1" pin="DATAIN"/>
<wire x1="-119.38" y1="96.52" x2="-119.38" y2="78.74" width="0.1524" layer="91"/>
<wire x1="-119.38" y1="78.74" x2="-111.76" y2="78.74" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$114" class="0">
<segment>
<pinref part="LED31" gate="G$1" pin="5VIN"/>
<wire x1="-111.76" y1="73.66" x2="-121.92" y2="73.66" width="0.1524" layer="91"/>
<pinref part="LED30" gate="G$1" pin="5VOUT"/>
<wire x1="-121.92" y1="73.66" x2="-121.92" y2="101.6" width="0.1524" layer="91"/>
<wire x1="-121.92" y1="101.6" x2="-111.76" y2="101.6" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$115" class="0">
<segment>
<pinref part="LED20" gate="G$1" pin="5VOUT"/>
<wire x1="218.44" y1="119.38" x2="220.98" y2="119.38" width="0.1524" layer="91"/>
<pinref part="LED21" gate="G$1" pin="5VIN"/>
<wire x1="220.98" y1="119.38" x2="220.98" y2="101.6" width="0.1524" layer="91"/>
<wire x1="220.98" y1="101.6" x2="218.44" y2="101.6" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$116" class="0">
<segment>
<pinref part="LED20" gate="G$1" pin="DATAOUT"/>
<wire x1="218.44" y1="124.46" x2="223.52" y2="124.46" width="0.1524" layer="91"/>
<pinref part="LED21" gate="G$1" pin="DATAIN"/>
<wire x1="223.52" y1="124.46" x2="223.52" y2="96.52" width="0.1524" layer="91"/>
<wire x1="223.52" y1="96.52" x2="218.44" y2="96.52" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$117" class="0">
<segment>
<pinref part="LED21" gate="G$1" pin="GNDIN"/>
<wire x1="218.44" y1="91.44" x2="226.06" y2="91.44" width="0.1524" layer="91"/>
<pinref part="LED20" gate="G$1" pin="GNDOUT"/>
<wire x1="226.06" y1="91.44" x2="226.06" y2="129.54" width="0.1524" layer="91"/>
<wire x1="226.06" y1="129.54" x2="218.44" y2="129.54" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$118" class="0">
<segment>
<pinref part="LED41" gate="G$1" pin="5VOUT"/>
<pinref part="LED42" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$119" class="0">
<segment>
<pinref part="LED41" gate="G$1" pin="DATAOUT"/>
<pinref part="LED42" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$120" class="0">
<segment>
<pinref part="LED41" gate="G$1" pin="GNDOUT"/>
<pinref part="LED42" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$122" class="0">
<segment>
<pinref part="LED42" gate="G$1" pin="DATAOUT"/>
<pinref part="LED43" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$123" class="0">
<segment>
<pinref part="LED42" gate="G$1" pin="GNDOUT"/>
<pinref part="LED43" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$124" class="0">
<segment>
<pinref part="LED43" gate="G$1" pin="5VOUT"/>
<pinref part="LED44" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$125" class="0">
<segment>
<pinref part="LED43" gate="G$1" pin="DATAOUT"/>
<pinref part="LED44" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$126" class="0">
<segment>
<pinref part="LED43" gate="G$1" pin="GNDOUT"/>
<pinref part="LED44" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$127" class="0">
<segment>
<pinref part="LED44" gate="G$1" pin="5VOUT"/>
<pinref part="LED45" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$128" class="0">
<segment>
<pinref part="LED44" gate="G$1" pin="DATAOUT"/>
<pinref part="LED45" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$129" class="0">
<segment>
<pinref part="LED44" gate="G$1" pin="GNDOUT"/>
<pinref part="LED45" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$130" class="0">
<segment>
<pinref part="LED45" gate="G$1" pin="5VOUT"/>
<pinref part="LED46" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$131" class="0">
<segment>
<pinref part="LED45" gate="G$1" pin="DATAOUT"/>
<pinref part="LED46" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$132" class="0">
<segment>
<pinref part="LED45" gate="G$1" pin="GNDOUT"/>
<pinref part="LED46" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$133" class="0">
<segment>
<pinref part="LED46" gate="G$1" pin="5VOUT"/>
<pinref part="LED47" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$134" class="0">
<segment>
<pinref part="LED46" gate="G$1" pin="DATAOUT"/>
<pinref part="LED47" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$135" class="0">
<segment>
<pinref part="LED46" gate="G$1" pin="GNDOUT"/>
<pinref part="LED47" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$136" class="0">
<segment>
<pinref part="LED47" gate="G$1" pin="5VOUT"/>
<pinref part="LED48" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$137" class="0">
<segment>
<pinref part="LED47" gate="G$1" pin="DATAOUT"/>
<pinref part="LED48" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$138" class="0">
<segment>
<pinref part="LED47" gate="G$1" pin="GNDOUT"/>
<pinref part="LED48" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$139" class="0">
<segment>
<pinref part="LED48" gate="G$1" pin="5VOUT"/>
<pinref part="LED49" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$140" class="0">
<segment>
<pinref part="LED48" gate="G$1" pin="DATAOUT"/>
<pinref part="LED49" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$141" class="0">
<segment>
<pinref part="LED48" gate="G$1" pin="GNDOUT"/>
<pinref part="LED49" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$142" class="0">
<segment>
<pinref part="LED49" gate="G$1" pin="5VOUT"/>
<pinref part="LED50" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$143" class="0">
<segment>
<pinref part="LED49" gate="G$1" pin="DATAOUT"/>
<pinref part="LED50" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$144" class="0">
<segment>
<pinref part="LED49" gate="G$1" pin="GNDOUT"/>
<pinref part="LED50" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$145" class="0">
<segment>
<pinref part="LED51" gate="G$1" pin="5VOUT"/>
<pinref part="LED52" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$146" class="0">
<segment>
<pinref part="LED51" gate="G$1" pin="DATAOUT"/>
<pinref part="LED52" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$147" class="0">
<segment>
<pinref part="LED51" gate="G$1" pin="GNDOUT"/>
<pinref part="LED52" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$148" class="0">
<segment>
<pinref part="LED52" gate="G$1" pin="5VOUT"/>
<pinref part="LED53" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$149" class="0">
<segment>
<pinref part="LED52" gate="G$1" pin="DATAOUT"/>
<pinref part="LED53" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$151" class="0">
<segment>
<pinref part="LED53" gate="G$1" pin="5VOUT"/>
<pinref part="LED54" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$152" class="0">
<segment>
<pinref part="LED53" gate="G$1" pin="DATAOUT"/>
<pinref part="LED54" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$153" class="0">
<segment>
<pinref part="LED53" gate="G$1" pin="GNDOUT"/>
<pinref part="LED54" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$154" class="0">
<segment>
<pinref part="LED54" gate="G$1" pin="5VOUT"/>
<pinref part="LED55" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$155" class="0">
<segment>
<pinref part="LED54" gate="G$1" pin="DATAOUT"/>
<pinref part="LED55" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$156" class="0">
<segment>
<pinref part="LED54" gate="G$1" pin="GNDOUT"/>
<pinref part="LED55" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$157" class="0">
<segment>
<pinref part="LED55" gate="G$1" pin="5VOUT"/>
<pinref part="LED56" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$158" class="0">
<segment>
<pinref part="LED55" gate="G$1" pin="DATAOUT"/>
<pinref part="LED56" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$159" class="0">
<segment>
<pinref part="LED55" gate="G$1" pin="GNDOUT"/>
<pinref part="LED56" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$160" class="0">
<segment>
<pinref part="LED56" gate="G$1" pin="5VOUT"/>
<pinref part="LED57" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$161" class="0">
<segment>
<pinref part="LED56" gate="G$1" pin="DATAOUT"/>
<pinref part="LED57" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$162" class="0">
<segment>
<pinref part="LED56" gate="G$1" pin="GNDOUT"/>
<pinref part="LED57" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$163" class="0">
<segment>
<pinref part="LED57" gate="G$1" pin="5VOUT"/>
<pinref part="LED58" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$164" class="0">
<segment>
<pinref part="LED57" gate="G$1" pin="DATAOUT"/>
<pinref part="LED58" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$165" class="0">
<segment>
<pinref part="LED57" gate="G$1" pin="GNDOUT"/>
<pinref part="LED58" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$166" class="0">
<segment>
<pinref part="LED58" gate="G$1" pin="5VOUT"/>
<pinref part="LED59" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$167" class="0">
<segment>
<pinref part="LED58" gate="G$1" pin="DATAOUT"/>
<pinref part="LED59" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$168" class="0">
<segment>
<pinref part="LED58" gate="G$1" pin="GNDOUT"/>
<pinref part="LED59" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$169" class="0">
<segment>
<pinref part="LED59" gate="G$1" pin="5VOUT"/>
<pinref part="LED60" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$170" class="0">
<segment>
<pinref part="LED59" gate="G$1" pin="DATAOUT"/>
<pinref part="LED60" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$171" class="0">
<segment>
<pinref part="LED59" gate="G$1" pin="GNDOUT"/>
<pinref part="LED60" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$172" class="0">
<segment>
<pinref part="LED50" gate="G$1" pin="GNDOUT"/>
<wire x1="-111.76" y1="48.26" x2="-116.84" y2="48.26" width="0.1524" layer="91"/>
<wire x1="-116.84" y1="48.26" x2="-116.84" y2="40.64" width="0.1524" layer="91"/>
<pinref part="LED51" gate="G$1" pin="GNDIN"/>
<wire x1="-116.84" y1="40.64" x2="-111.76" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$173" class="0">
<segment>
<pinref part="LED50" gate="G$1" pin="DATAOUT"/>
<wire x1="-111.76" y1="53.34" x2="-119.38" y2="53.34" width="0.1524" layer="91"/>
<pinref part="LED51" gate="G$1" pin="DATAIN"/>
<wire x1="-119.38" y1="53.34" x2="-119.38" y2="35.56" width="0.1524" layer="91"/>
<wire x1="-119.38" y1="35.56" x2="-111.76" y2="35.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$174" class="0">
<segment>
<pinref part="LED51" gate="G$1" pin="5VIN"/>
<wire x1="-111.76" y1="30.48" x2="-121.92" y2="30.48" width="0.1524" layer="91"/>
<pinref part="LED50" gate="G$1" pin="5VOUT"/>
<wire x1="-121.92" y1="30.48" x2="-121.92" y2="58.42" width="0.1524" layer="91"/>
<wire x1="-121.92" y1="58.42" x2="-111.76" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$175" class="0">
<segment>
<pinref part="LED61" gate="G$1" pin="5VOUT"/>
<pinref part="LED62" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$176" class="0">
<segment>
<pinref part="LED61" gate="G$1" pin="DATAOUT"/>
<pinref part="LED62" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$177" class="0">
<segment>
<pinref part="LED61" gate="G$1" pin="GNDOUT"/>
<pinref part="LED62" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$179" class="0">
<segment>
<pinref part="LED62" gate="G$1" pin="DATAOUT"/>
<pinref part="LED63" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$180" class="0">
<segment>
<pinref part="LED62" gate="G$1" pin="GNDOUT"/>
<pinref part="LED63" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$181" class="0">
<segment>
<pinref part="LED63" gate="G$1" pin="5VOUT"/>
<pinref part="LED64" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$182" class="0">
<segment>
<pinref part="LED63" gate="G$1" pin="DATAOUT"/>
<pinref part="LED64" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$183" class="0">
<segment>
<pinref part="LED63" gate="G$1" pin="GNDOUT"/>
<pinref part="LED64" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$184" class="0">
<segment>
<pinref part="LED64" gate="G$1" pin="5VOUT"/>
<pinref part="LED65" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$185" class="0">
<segment>
<pinref part="LED64" gate="G$1" pin="DATAOUT"/>
<pinref part="LED65" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$186" class="0">
<segment>
<pinref part="LED64" gate="G$1" pin="GNDOUT"/>
<pinref part="LED65" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$187" class="0">
<segment>
<pinref part="LED65" gate="G$1" pin="5VOUT"/>
<pinref part="LED66" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$188" class="0">
<segment>
<pinref part="LED65" gate="G$1" pin="DATAOUT"/>
<pinref part="LED66" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$189" class="0">
<segment>
<pinref part="LED65" gate="G$1" pin="GNDOUT"/>
<pinref part="LED66" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$190" class="0">
<segment>
<pinref part="LED66" gate="G$1" pin="5VOUT"/>
<pinref part="LED67" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$191" class="0">
<segment>
<pinref part="LED66" gate="G$1" pin="DATAOUT"/>
<pinref part="LED67" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$192" class="0">
<segment>
<pinref part="LED66" gate="G$1" pin="GNDOUT"/>
<pinref part="LED67" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$193" class="0">
<segment>
<pinref part="LED67" gate="G$1" pin="5VOUT"/>
<pinref part="LED68" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$194" class="0">
<segment>
<pinref part="LED67" gate="G$1" pin="DATAOUT"/>
<pinref part="LED68" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$195" class="0">
<segment>
<pinref part="LED67" gate="G$1" pin="GNDOUT"/>
<pinref part="LED68" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$196" class="0">
<segment>
<pinref part="LED68" gate="G$1" pin="5VOUT"/>
<pinref part="LED69" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$197" class="0">
<segment>
<pinref part="LED68" gate="G$1" pin="DATAOUT"/>
<pinref part="LED69" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$198" class="0">
<segment>
<pinref part="LED68" gate="G$1" pin="GNDOUT"/>
<pinref part="LED69" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$199" class="0">
<segment>
<pinref part="LED69" gate="G$1" pin="5VOUT"/>
<pinref part="LED70" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$200" class="0">
<segment>
<pinref part="LED69" gate="G$1" pin="DATAOUT"/>
<pinref part="LED70" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$201" class="0">
<segment>
<pinref part="LED69" gate="G$1" pin="GNDOUT"/>
<pinref part="LED70" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$202" class="0">
<segment>
<pinref part="LED71" gate="G$1" pin="5VOUT"/>
<pinref part="LED72" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$203" class="0">
<segment>
<pinref part="LED71" gate="G$1" pin="DATAOUT"/>
<pinref part="LED72" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$204" class="0">
<segment>
<pinref part="LED71" gate="G$1" pin="GNDOUT"/>
<pinref part="LED72" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$205" class="0">
<segment>
<pinref part="LED72" gate="G$1" pin="5VOUT"/>
<pinref part="LED73" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$206" class="0">
<segment>
<pinref part="LED72" gate="G$1" pin="DATAOUT"/>
<pinref part="LED73" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$208" class="0">
<segment>
<pinref part="LED73" gate="G$1" pin="5VOUT"/>
<pinref part="LED74" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$209" class="0">
<segment>
<pinref part="LED73" gate="G$1" pin="DATAOUT"/>
<pinref part="LED74" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$210" class="0">
<segment>
<pinref part="LED73" gate="G$1" pin="GNDOUT"/>
<pinref part="LED74" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$211" class="0">
<segment>
<pinref part="LED74" gate="G$1" pin="5VOUT"/>
<pinref part="LED75" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$212" class="0">
<segment>
<pinref part="LED74" gate="G$1" pin="DATAOUT"/>
<pinref part="LED75" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$213" class="0">
<segment>
<pinref part="LED74" gate="G$1" pin="GNDOUT"/>
<pinref part="LED75" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$214" class="0">
<segment>
<pinref part="LED75" gate="G$1" pin="5VOUT"/>
<pinref part="LED76" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$215" class="0">
<segment>
<pinref part="LED75" gate="G$1" pin="DATAOUT"/>
<pinref part="LED76" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$216" class="0">
<segment>
<pinref part="LED75" gate="G$1" pin="GNDOUT"/>
<pinref part="LED76" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$217" class="0">
<segment>
<pinref part="LED76" gate="G$1" pin="5VOUT"/>
<pinref part="LED77" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$218" class="0">
<segment>
<pinref part="LED76" gate="G$1" pin="DATAOUT"/>
<pinref part="LED77" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$219" class="0">
<segment>
<pinref part="LED76" gate="G$1" pin="GNDOUT"/>
<pinref part="LED77" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$220" class="0">
<segment>
<pinref part="LED77" gate="G$1" pin="5VOUT"/>
<pinref part="LED78" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$221" class="0">
<segment>
<pinref part="LED77" gate="G$1" pin="DATAOUT"/>
<pinref part="LED78" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$222" class="0">
<segment>
<pinref part="LED77" gate="G$1" pin="GNDOUT"/>
<pinref part="LED78" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$223" class="0">
<segment>
<pinref part="LED78" gate="G$1" pin="5VOUT"/>
<pinref part="LED79" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$224" class="0">
<segment>
<pinref part="LED78" gate="G$1" pin="DATAOUT"/>
<pinref part="LED79" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$225" class="0">
<segment>
<pinref part="LED78" gate="G$1" pin="GNDOUT"/>
<pinref part="LED79" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$226" class="0">
<segment>
<pinref part="LED79" gate="G$1" pin="5VOUT"/>
<pinref part="LED80" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$227" class="0">
<segment>
<pinref part="LED79" gate="G$1" pin="DATAOUT"/>
<pinref part="LED80" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$228" class="0">
<segment>
<pinref part="LED79" gate="G$1" pin="GNDOUT"/>
<pinref part="LED80" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$229" class="0">
<segment>
<pinref part="LED70" gate="G$1" pin="GNDOUT"/>
<wire x1="-111.76" y1="2.54" x2="-116.84" y2="2.54" width="0.1524" layer="91"/>
<wire x1="-116.84" y1="2.54" x2="-116.84" y2="-5.08" width="0.1524" layer="91"/>
<pinref part="LED71" gate="G$1" pin="GNDIN"/>
<wire x1="-116.84" y1="-5.08" x2="-111.76" y2="-5.08" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$230" class="0">
<segment>
<pinref part="LED70" gate="G$1" pin="DATAOUT"/>
<wire x1="-111.76" y1="7.62" x2="-119.38" y2="7.62" width="0.1524" layer="91"/>
<pinref part="LED71" gate="G$1" pin="DATAIN"/>
<wire x1="-119.38" y1="7.62" x2="-119.38" y2="-10.16" width="0.1524" layer="91"/>
<wire x1="-119.38" y1="-10.16" x2="-111.76" y2="-10.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$231" class="0">
<segment>
<pinref part="LED71" gate="G$1" pin="5VIN"/>
<wire x1="-111.76" y1="-15.24" x2="-121.92" y2="-15.24" width="0.1524" layer="91"/>
<pinref part="LED70" gate="G$1" pin="5VOUT"/>
<wire x1="-121.92" y1="-15.24" x2="-121.92" y2="12.7" width="0.1524" layer="91"/>
<wire x1="-121.92" y1="12.7" x2="-111.76" y2="12.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$232" class="0">
<segment>
<pinref part="LED60" gate="G$1" pin="5VOUT"/>
<wire x1="218.44" y1="30.48" x2="220.98" y2="30.48" width="0.1524" layer="91"/>
<pinref part="LED61" gate="G$1" pin="5VIN"/>
<wire x1="220.98" y1="30.48" x2="220.98" y2="12.7" width="0.1524" layer="91"/>
<wire x1="220.98" y1="12.7" x2="218.44" y2="12.7" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$233" class="0">
<segment>
<pinref part="LED60" gate="G$1" pin="DATAOUT"/>
<wire x1="218.44" y1="35.56" x2="223.52" y2="35.56" width="0.1524" layer="91"/>
<pinref part="LED61" gate="G$1" pin="DATAIN"/>
<wire x1="223.52" y1="35.56" x2="223.52" y2="7.62" width="0.1524" layer="91"/>
<wire x1="223.52" y1="7.62" x2="218.44" y2="7.62" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$234" class="0">
<segment>
<pinref part="LED61" gate="G$1" pin="GNDIN"/>
<wire x1="218.44" y1="2.54" x2="226.06" y2="2.54" width="0.1524" layer="91"/>
<pinref part="LED60" gate="G$1" pin="GNDOUT"/>
<wire x1="226.06" y1="2.54" x2="226.06" y2="40.64" width="0.1524" layer="91"/>
<wire x1="226.06" y1="40.64" x2="218.44" y2="40.64" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$235" class="0">
<segment>
<pinref part="LED41" gate="G$1" pin="5VIN"/>
<wire x1="218.44" y1="58.42" x2="223.52" y2="58.42" width="0.1524" layer="91"/>
<pinref part="LED40" gate="G$1" pin="5VOUT"/>
<wire x1="223.52" y1="58.42" x2="223.52" y2="73.66" width="0.1524" layer="91"/>
<wire x1="223.52" y1="73.66" x2="218.44" y2="73.66" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$236" class="0">
<segment>
<pinref part="LED40" gate="G$1" pin="DATAOUT"/>
<wire x1="218.44" y1="78.74" x2="226.06" y2="78.74" width="0.1524" layer="91"/>
<pinref part="LED41" gate="G$1" pin="DATAIN"/>
<wire x1="226.06" y1="78.74" x2="226.06" y2="53.34" width="0.1524" layer="91"/>
<wire x1="226.06" y1="53.34" x2="218.44" y2="53.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$237" class="0">
<segment>
<pinref part="LED41" gate="G$1" pin="GNDIN"/>
<wire x1="218.44" y1="48.26" x2="228.6" y2="48.26" width="0.1524" layer="91"/>
<pinref part="LED40" gate="G$1" pin="GNDOUT"/>
<wire x1="228.6" y1="48.26" x2="228.6" y2="83.82" width="0.1524" layer="91"/>
<wire x1="228.6" y1="83.82" x2="218.44" y2="83.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$238" class="0">
<segment>
<pinref part="LED81" gate="G$1" pin="5VOUT"/>
<pinref part="LED82" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$239" class="0">
<segment>
<pinref part="LED81" gate="G$1" pin="DATAOUT"/>
<pinref part="LED82" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$240" class="0">
<segment>
<pinref part="LED81" gate="G$1" pin="GNDOUT"/>
<pinref part="LED82" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$242" class="0">
<segment>
<pinref part="LED82" gate="G$1" pin="DATAOUT"/>
<pinref part="LED83" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$243" class="0">
<segment>
<pinref part="LED82" gate="G$1" pin="GNDOUT"/>
<pinref part="LED83" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$244" class="0">
<segment>
<pinref part="LED83" gate="G$1" pin="5VOUT"/>
<pinref part="LED84" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$245" class="0">
<segment>
<pinref part="LED83" gate="G$1" pin="DATAOUT"/>
<pinref part="LED84" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$246" class="0">
<segment>
<pinref part="LED83" gate="G$1" pin="GNDOUT"/>
<pinref part="LED84" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$247" class="0">
<segment>
<pinref part="LED84" gate="G$1" pin="5VOUT"/>
<pinref part="LED85" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$248" class="0">
<segment>
<pinref part="LED84" gate="G$1" pin="DATAOUT"/>
<pinref part="LED85" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$249" class="0">
<segment>
<pinref part="LED84" gate="G$1" pin="GNDOUT"/>
<pinref part="LED85" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$250" class="0">
<segment>
<pinref part="LED85" gate="G$1" pin="5VOUT"/>
<pinref part="LED86" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$251" class="0">
<segment>
<pinref part="LED85" gate="G$1" pin="DATAOUT"/>
<pinref part="LED86" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$252" class="0">
<segment>
<pinref part="LED85" gate="G$1" pin="GNDOUT"/>
<pinref part="LED86" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$253" class="0">
<segment>
<pinref part="LED86" gate="G$1" pin="5VOUT"/>
<pinref part="LED87" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$254" class="0">
<segment>
<pinref part="LED86" gate="G$1" pin="DATAOUT"/>
<pinref part="LED87" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$255" class="0">
<segment>
<pinref part="LED86" gate="G$1" pin="GNDOUT"/>
<pinref part="LED87" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$256" class="0">
<segment>
<pinref part="LED87" gate="G$1" pin="5VOUT"/>
<pinref part="LED88" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$257" class="0">
<segment>
<pinref part="LED87" gate="G$1" pin="DATAOUT"/>
<pinref part="LED88" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$259" class="0">
<segment>
<pinref part="LED88" gate="G$1" pin="5VOUT"/>
<pinref part="LED89" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$260" class="0">
<segment>
<pinref part="LED88" gate="G$1" pin="DATAOUT"/>
<pinref part="LED89" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$261" class="0">
<segment>
<pinref part="LED88" gate="G$1" pin="GNDOUT"/>
<pinref part="LED89" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$262" class="0">
<segment>
<pinref part="LED89" gate="G$1" pin="5VOUT"/>
<pinref part="LED90" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$263" class="0">
<segment>
<pinref part="LED89" gate="G$1" pin="DATAOUT"/>
<pinref part="LED90" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$264" class="0">
<segment>
<pinref part="LED89" gate="G$1" pin="GNDOUT"/>
<pinref part="LED90" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$265" class="0">
<segment>
<pinref part="LED91" gate="G$1" pin="5VOUT"/>
<pinref part="LED92" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$266" class="0">
<segment>
<pinref part="LED91" gate="G$1" pin="DATAOUT"/>
<pinref part="LED92" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$267" class="0">
<segment>
<pinref part="LED91" gate="G$1" pin="GNDOUT"/>
<pinref part="LED92" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$268" class="0">
<segment>
<pinref part="LED92" gate="G$1" pin="5VOUT"/>
<pinref part="LED93" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$269" class="0">
<segment>
<pinref part="LED92" gate="G$1" pin="DATAOUT"/>
<pinref part="LED93" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$271" class="0">
<segment>
<pinref part="LED93" gate="G$1" pin="5VOUT"/>
<pinref part="LED94" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$272" class="0">
<segment>
<pinref part="LED93" gate="G$1" pin="DATAOUT"/>
<pinref part="LED94" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$273" class="0">
<segment>
<pinref part="LED93" gate="G$1" pin="GNDOUT"/>
<pinref part="LED94" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$274" class="0">
<segment>
<pinref part="LED94" gate="G$1" pin="5VOUT"/>
<pinref part="LED95" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$275" class="0">
<segment>
<pinref part="LED94" gate="G$1" pin="DATAOUT"/>
<pinref part="LED95" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$276" class="0">
<segment>
<pinref part="LED94" gate="G$1" pin="GNDOUT"/>
<pinref part="LED95" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$277" class="0">
<segment>
<pinref part="LED95" gate="G$1" pin="5VOUT"/>
<pinref part="LED96" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$278" class="0">
<segment>
<pinref part="LED95" gate="G$1" pin="DATAOUT"/>
<pinref part="LED96" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$279" class="0">
<segment>
<pinref part="LED95" gate="G$1" pin="GNDOUT"/>
<pinref part="LED96" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$280" class="0">
<segment>
<pinref part="LED96" gate="G$1" pin="5VOUT"/>
<pinref part="LED97" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$281" class="0">
<segment>
<pinref part="LED96" gate="G$1" pin="DATAOUT"/>
<pinref part="LED97" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$282" class="0">
<segment>
<pinref part="LED96" gate="G$1" pin="GNDOUT"/>
<pinref part="LED97" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$283" class="0">
<segment>
<pinref part="LED97" gate="G$1" pin="5VOUT"/>
<pinref part="LED98" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$284" class="0">
<segment>
<pinref part="LED97" gate="G$1" pin="DATAOUT"/>
<pinref part="LED98" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$285" class="0">
<segment>
<pinref part="LED97" gate="G$1" pin="GNDOUT"/>
<pinref part="LED98" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$286" class="0">
<segment>
<pinref part="LED98" gate="G$1" pin="5VOUT"/>
<pinref part="LED99" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$287" class="0">
<segment>
<pinref part="LED98" gate="G$1" pin="DATAOUT"/>
<pinref part="LED99" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$288" class="0">
<segment>
<pinref part="LED98" gate="G$1" pin="GNDOUT"/>
<pinref part="LED99" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$289" class="0">
<segment>
<pinref part="LED99" gate="G$1" pin="5VOUT"/>
<pinref part="LED100" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$290" class="0">
<segment>
<pinref part="LED99" gate="G$1" pin="DATAOUT"/>
<pinref part="LED100" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$291" class="0">
<segment>
<pinref part="LED99" gate="G$1" pin="GNDOUT"/>
<pinref part="LED100" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$292" class="0">
<segment>
<pinref part="LED90" gate="G$1" pin="GNDOUT"/>
<wire x1="-111.76" y1="-40.64" x2="-116.84" y2="-40.64" width="0.1524" layer="91"/>
<wire x1="-116.84" y1="-40.64" x2="-116.84" y2="-48.26" width="0.1524" layer="91"/>
<pinref part="LED91" gate="G$1" pin="GNDIN"/>
<wire x1="-116.84" y1="-48.26" x2="-111.76" y2="-48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$293" class="0">
<segment>
<pinref part="LED90" gate="G$1" pin="DATAOUT"/>
<wire x1="-111.76" y1="-35.56" x2="-119.38" y2="-35.56" width="0.1524" layer="91"/>
<pinref part="LED91" gate="G$1" pin="DATAIN"/>
<wire x1="-119.38" y1="-35.56" x2="-119.38" y2="-53.34" width="0.1524" layer="91"/>
<wire x1="-119.38" y1="-53.34" x2="-111.76" y2="-53.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$294" class="0">
<segment>
<pinref part="LED91" gate="G$1" pin="5VIN"/>
<wire x1="-111.76" y1="-58.42" x2="-121.92" y2="-58.42" width="0.1524" layer="91"/>
<pinref part="LED90" gate="G$1" pin="5VOUT"/>
<wire x1="-121.92" y1="-58.42" x2="-121.92" y2="-30.48" width="0.1524" layer="91"/>
<wire x1="-121.92" y1="-30.48" x2="-111.76" y2="-30.48" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$295" class="0">
<segment>
<pinref part="LED101" gate="G$1" pin="5VOUT"/>
<pinref part="LED102" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$296" class="0">
<segment>
<pinref part="LED101" gate="G$1" pin="DATAOUT"/>
<pinref part="LED102" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$297" class="0">
<segment>
<pinref part="LED101" gate="G$1" pin="GNDOUT"/>
<pinref part="LED102" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$299" class="0">
<segment>
<pinref part="LED102" gate="G$1" pin="DATAOUT"/>
<pinref part="LED103" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$300" class="0">
<segment>
<pinref part="LED102" gate="G$1" pin="GNDOUT"/>
<pinref part="LED103" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$301" class="0">
<segment>
<pinref part="LED102" gate="G$1" pin="5VOUT"/>
<pinref part="LED103" gate="G$1" pin="5VIN"/>
<pinref part="LED82" gate="G$1" pin="5VOUT"/>
<pinref part="LED83" gate="G$1" pin="5VIN"/>
<wire x1="152.4" y1="-76.2" x2="152.4" y2="-30.48" width="0.1524" layer="91"/>
<junction x="152.4" y="-76.2"/>
<junction x="152.4" y="-30.48"/>
<pinref part="LED62" gate="G$1" pin="5VOUT"/>
<pinref part="LED63" gate="G$1" pin="5VIN"/>
<wire x1="152.4" y1="-30.48" x2="152.4" y2="12.7" width="0.1524" layer="91"/>
<junction x="152.4" y="12.7"/>
<pinref part="LED42" gate="G$1" pin="5VOUT"/>
<pinref part="LED43" gate="G$1" pin="5VIN"/>
<wire x1="152.4" y1="12.7" x2="152.4" y2="58.42" width="0.1524" layer="91"/>
<junction x="152.4" y="58.42"/>
<pinref part="LED22" gate="G$1" pin="5VOUT"/>
<pinref part="LED23" gate="G$1" pin="5VIN"/>
<wire x1="152.4" y1="58.42" x2="152.4" y2="101.6" width="0.1524" layer="91"/>
<junction x="152.4" y="101.6"/>
<wire x1="152.4" y1="101.6" x2="152.4" y2="111.76" width="0.1524" layer="91"/>
<wire x1="152.4" y1="111.76" x2="185.42" y2="111.76" width="0.1524" layer="91"/>
<pinref part="LED1" gate="G$1" pin="5VOUT"/>
<pinref part="LED2" gate="G$1" pin="5VIN"/>
<wire x1="185.42" y1="111.76" x2="185.42" y2="147.32" width="0.1524" layer="91"/>
<junction x="185.42" y="147.32"/>
</segment>
</net>
<net name="N$302" class="0">
<segment>
<pinref part="LED103" gate="G$1" pin="DATAOUT"/>
<pinref part="LED104" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$303" class="0">
<segment>
<pinref part="LED103" gate="G$1" pin="GNDOUT"/>
<pinref part="LED104" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$304" class="0">
<segment>
<pinref part="LED104" gate="G$1" pin="5VOUT"/>
<pinref part="LED105" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$305" class="0">
<segment>
<pinref part="LED104" gate="G$1" pin="DATAOUT"/>
<pinref part="LED105" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$306" class="0">
<segment>
<pinref part="LED104" gate="G$1" pin="GNDOUT"/>
<pinref part="LED105" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$307" class="0">
<segment>
<pinref part="LED105" gate="G$1" pin="5VOUT"/>
<pinref part="LED106" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$308" class="0">
<segment>
<pinref part="LED105" gate="G$1" pin="DATAOUT"/>
<pinref part="LED106" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$309" class="0">
<segment>
<pinref part="LED105" gate="G$1" pin="GNDOUT"/>
<pinref part="LED106" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$310" class="0">
<segment>
<pinref part="LED106" gate="G$1" pin="5VOUT"/>
<pinref part="LED107" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$311" class="0">
<segment>
<pinref part="LED106" gate="G$1" pin="DATAOUT"/>
<pinref part="LED107" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$312" class="0">
<segment>
<pinref part="LED106" gate="G$1" pin="GNDOUT"/>
<pinref part="LED107" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$313" class="0">
<segment>
<pinref part="LED107" gate="G$1" pin="5VOUT"/>
<pinref part="LED108" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$314" class="0">
<segment>
<pinref part="LED107" gate="G$1" pin="DATAOUT"/>
<pinref part="LED108" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$315" class="0">
<segment>
<pinref part="LED107" gate="G$1" pin="GNDOUT"/>
<pinref part="LED108" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$316" class="0">
<segment>
<pinref part="LED108" gate="G$1" pin="5VOUT"/>
<pinref part="LED109" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$317" class="0">
<segment>
<pinref part="LED108" gate="G$1" pin="DATAOUT"/>
<pinref part="LED109" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$318" class="0">
<segment>
<pinref part="LED108" gate="G$1" pin="GNDOUT"/>
<pinref part="LED109" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$319" class="0">
<segment>
<pinref part="LED109" gate="G$1" pin="5VOUT"/>
<pinref part="LED110" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$320" class="0">
<segment>
<pinref part="LED109" gate="G$1" pin="DATAOUT"/>
<pinref part="LED110" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$321" class="0">
<segment>
<pinref part="LED109" gate="G$1" pin="GNDOUT"/>
<pinref part="LED110" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$322" class="0">
<segment>
<pinref part="LED111" gate="G$1" pin="5VOUT"/>
<pinref part="LED112" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$323" class="0">
<segment>
<pinref part="LED111" gate="G$1" pin="DATAOUT"/>
<pinref part="LED112" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$324" class="0">
<segment>
<pinref part="LED111" gate="G$1" pin="GNDOUT"/>
<pinref part="LED112" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$325" class="0">
<segment>
<pinref part="LED112" gate="G$1" pin="5VOUT"/>
<pinref part="LED113" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$326" class="0">
<segment>
<pinref part="LED112" gate="G$1" pin="DATAOUT"/>
<pinref part="LED113" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$327" class="0">
<segment>
<pinref part="LED112" gate="G$1" pin="GNDOUT"/>
<pinref part="LED113" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$328" class="0">
<segment>
<pinref part="LED113" gate="G$1" pin="5VOUT"/>
<pinref part="LED114" gate="G$1" pin="5VIN"/>
</segment>
</net>
<net name="N$329" class="0">
<segment>
<pinref part="LED113" gate="G$1" pin="DATAOUT"/>
<pinref part="LED114" gate="G$1" pin="DATAIN"/>
</segment>
</net>
<net name="N$330" class="0">
<segment>
<pinref part="LED113" gate="G$1" pin="GNDOUT"/>
<pinref part="LED114" gate="G$1" pin="GNDIN"/>
<pinref part="LED92" gate="G$1" pin="GNDOUT"/>
<pinref part="LED93" gate="G$1" pin="GNDIN"/>
<wire x1="-12.7" y1="-93.98" x2="-45.72" y2="-93.98" width="0.1524" layer="91"/>
<wire x1="-45.72" y1="-93.98" x2="-45.72" y2="-48.26" width="0.1524" layer="91"/>
<junction x="-12.7" y="-93.98"/>
<junction x="-45.72" y="-48.26"/>
<pinref part="LED72" gate="G$1" pin="GNDOUT"/>
<pinref part="LED73" gate="G$1" pin="GNDIN"/>
<wire x1="-45.72" y1="-48.26" x2="-45.72" y2="-5.08" width="0.1524" layer="91"/>
<junction x="-45.72" y="-5.08"/>
<pinref part="LED52" gate="G$1" pin="GNDOUT"/>
<pinref part="LED53" gate="G$1" pin="GNDIN"/>
<wire x1="-45.72" y1="-5.08" x2="-45.72" y2="40.64" width="0.1524" layer="91"/>
<junction x="-45.72" y="40.64"/>
<pinref part="LED32" gate="G$1" pin="GNDOUT"/>
<pinref part="LED33" gate="G$1" pin="GNDIN"/>
<wire x1="-45.72" y1="40.64" x2="-45.72" y2="83.82" width="0.1524" layer="91"/>
<junction x="-45.72" y="83.82"/>
<pinref part="LED12" gate="G$1" pin="GNDOUT"/>
<pinref part="LED13" gate="G$1" pin="GNDIN"/>
<wire x1="-45.72" y1="83.82" x2="-45.72" y2="129.54" width="0.1524" layer="91"/>
<junction x="-45.72" y="129.54"/>
</segment>
</net>
<net name="N$349" class="0">
<segment>
<pinref part="LED110" gate="G$1" pin="GNDOUT"/>
<wire x1="-111.76" y1="-86.36" x2="-116.84" y2="-86.36" width="0.1524" layer="91"/>
<wire x1="-116.84" y1="-86.36" x2="-116.84" y2="-93.98" width="0.1524" layer="91"/>
<pinref part="LED111" gate="G$1" pin="GNDIN"/>
<wire x1="-116.84" y1="-93.98" x2="-111.76" y2="-93.98" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$350" class="0">
<segment>
<pinref part="LED110" gate="G$1" pin="DATAOUT"/>
<wire x1="-111.76" y1="-81.28" x2="-119.38" y2="-81.28" width="0.1524" layer="91"/>
<pinref part="LED111" gate="G$1" pin="DATAIN"/>
<wire x1="-119.38" y1="-81.28" x2="-119.38" y2="-99.06" width="0.1524" layer="91"/>
<wire x1="-119.38" y1="-99.06" x2="-111.76" y2="-99.06" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$351" class="0">
<segment>
<pinref part="LED111" gate="G$1" pin="5VIN"/>
<wire x1="-111.76" y1="-104.14" x2="-121.92" y2="-104.14" width="0.1524" layer="91"/>
<pinref part="LED110" gate="G$1" pin="5VOUT"/>
<wire x1="-121.92" y1="-104.14" x2="-121.92" y2="-76.2" width="0.1524" layer="91"/>
<wire x1="-121.92" y1="-76.2" x2="-111.76" y2="-76.2" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$352" class="0">
<segment>
<pinref part="LED100" gate="G$1" pin="5VOUT"/>
<wire x1="218.44" y1="-58.42" x2="220.98" y2="-58.42" width="0.1524" layer="91"/>
<pinref part="LED101" gate="G$1" pin="5VIN"/>
<wire x1="220.98" y1="-58.42" x2="220.98" y2="-76.2" width="0.1524" layer="91"/>
<wire x1="220.98" y1="-76.2" x2="218.44" y2="-76.2" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$353" class="0">
<segment>
<pinref part="LED100" gate="G$1" pin="DATAOUT"/>
<wire x1="218.44" y1="-53.34" x2="223.52" y2="-53.34" width="0.1524" layer="91"/>
<pinref part="LED101" gate="G$1" pin="DATAIN"/>
<wire x1="223.52" y1="-53.34" x2="223.52" y2="-81.28" width="0.1524" layer="91"/>
<wire x1="223.52" y1="-81.28" x2="218.44" y2="-81.28" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$354" class="0">
<segment>
<pinref part="LED101" gate="G$1" pin="GNDIN"/>
<wire x1="218.44" y1="-86.36" x2="226.06" y2="-86.36" width="0.1524" layer="91"/>
<pinref part="LED100" gate="G$1" pin="GNDOUT"/>
<wire x1="226.06" y1="-86.36" x2="226.06" y2="-48.26" width="0.1524" layer="91"/>
<wire x1="226.06" y1="-48.26" x2="218.44" y2="-48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$331" class="0">
<segment>
<pinref part="LED81" gate="G$1" pin="5VIN"/>
<wire x1="218.44" y1="-30.48" x2="223.52" y2="-30.48" width="0.1524" layer="91"/>
<wire x1="223.52" y1="-30.48" x2="223.52" y2="-15.24" width="0.1524" layer="91"/>
<pinref part="LED80" gate="G$1" pin="5VOUT"/>
<wire x1="223.52" y1="-15.24" x2="218.44" y2="-15.24" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$332" class="0">
<segment>
<pinref part="LED81" gate="G$1" pin="DATAIN"/>
<wire x1="218.44" y1="-35.56" x2="226.06" y2="-35.56" width="0.1524" layer="91"/>
<pinref part="LED80" gate="G$1" pin="DATAOUT"/>
<wire x1="226.06" y1="-35.56" x2="226.06" y2="-10.16" width="0.1524" layer="91"/>
<wire x1="226.06" y1="-10.16" x2="218.44" y2="-10.16" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$333" class="0">
<segment>
<pinref part="LED81" gate="G$1" pin="GNDIN"/>
<wire x1="218.44" y1="-40.64" x2="231.14" y2="-40.64" width="0.1524" layer="91"/>
<wire x1="231.14" y1="-40.64" x2="231.14" y2="-5.08" width="0.1524" layer="91"/>
<wire x1="231.14" y1="-5.08" x2="218.44" y2="-5.08" width="0.1524" layer="91"/>
<pinref part="LED80" gate="G$1" pin="GNDOUT"/>
</segment>
</net>
<net name="N$334" class="0">
<segment>
<pinref part="LED1" gate="G$1" pin="GNDIN"/>
<wire x1="218.44" y1="137.16" x2="299.72" y2="137.16" width="0.1524" layer="91"/>
<wire x1="299.72" y1="137.16" x2="299.72" y2="147.32" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="GND"/>
<wire x1="299.72" y1="147.32" x2="294.64" y2="147.32" width="0.1524" layer="91"/>
<pinref part="USBOUT" gate="A" pin="4"/>
<wire x1="254" y1="203.2" x2="299.72" y2="203.2" width="0.1524" layer="91"/>
<wire x1="299.72" y1="203.2" x2="299.72" y2="147.32" width="0.1524" layer="91"/>
<junction x="299.72" y="147.32"/>
<pinref part="USBIN" gate="A" pin="4"/>
<wire x1="220.98" y1="203.2" x2="254" y2="203.2" width="0.1524" layer="91"/>
<junction x="254" y="203.2"/>
</segment>
</net>
<net name="N$335" class="0">
<segment>
<pinref part="LED1" gate="G$1" pin="5VIN"/>
<wire x1="218.44" y1="147.32" x2="238.76" y2="147.32" width="0.1524" layer="91"/>
<wire x1="238.76" y1="147.32" x2="248.92" y2="147.32" width="0.1524" layer="91"/>
<wire x1="248.92" y1="147.32" x2="248.92" y2="144.78" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="VIN"/>
<wire x1="248.92" y1="144.78" x2="259.08" y2="144.78" width="0.1524" layer="91"/>
<pinref part="USBOUT" gate="A" pin="1"/>
<wire x1="254" y1="195.58" x2="254" y2="160.02" width="0.1524" layer="91"/>
<wire x1="254" y1="160.02" x2="238.76" y2="160.02" width="0.1524" layer="91"/>
<wire x1="238.76" y1="160.02" x2="238.76" y2="147.32" width="0.1524" layer="91"/>
<junction x="238.76" y="147.32"/>
<pinref part="USBIN" gate="A" pin="1"/>
<wire x1="220.98" y1="195.58" x2="254" y2="195.58" width="0.1524" layer="91"/>
<junction x="254" y="195.58"/>
<wire x1="254" y1="195.58" x2="304.8" y2="195.58" width="0.1524" layer="91"/>
<wire x1="304.8" y1="195.58" x2="304.8" y2="165.1" width="0.1524" layer="91"/>
<pinref part="BUTTON" gate="G$1" pin="2"/>
<wire x1="304.8" y1="165.1" x2="314.96" y2="165.1" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$336" class="0">
<segment>
<pinref part="LED1" gate="G$1" pin="DATAIN"/>
<wire x1="218.44" y1="142.24" x2="243.84" y2="142.24" width="0.1524" layer="91"/>
<wire x1="243.84" y1="142.24" x2="243.84" y2="149.86" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="IO13"/>
<wire x1="243.84" y1="149.86" x2="259.08" y2="149.86" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$338" class="0">
<segment>
<pinref part="USBIN" gate="A" pin="3"/>
<pinref part="USBOUT" gate="A" pin="3"/>
<wire x1="220.98" y1="200.66" x2="254" y2="200.66" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$339" class="0">
<segment>
<pinref part="USBIN" gate="A" pin="2"/>
<pinref part="USBOUT" gate="A" pin="2"/>
<wire x1="220.98" y1="198.12" x2="254" y2="198.12" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$337" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="IO19"/>
<wire x1="294.64" y1="167.64" x2="314.96" y2="167.64" width="0.1524" layer="91"/>
<pinref part="BUTTON" gate="G$1" pin="1"/>
</segment>
</net>
<net name="N$258" class="0">
<segment>
<pinref part="LED87" gate="G$1" pin="GNDOUT"/>
<pinref part="LED88" gate="G$1" pin="GNDIN"/>
</segment>
</net>
<net name="N$33" class="0">
<segment>
<pinref part="LED103" gate="G$1" pin="5VOUT"/>
<pinref part="LED104" gate="G$1" pin="5VIN"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="8.2" severity="warning">
Since Version 8.2, EAGLE supports online libraries. The ids
of those online libraries will not be understood (or retained)
with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports URNs for individual library
assets (packages, symbols, and devices). The URNs of those assets
will not be understood (or retained) with this version.
</note>
<note version="8.3" severity="warning">
Since Version 8.3, EAGLE supports the association of 3D packages
with devices in libraries, schematics, and board files. Those 3D
packages will not be understood (or retained) with this version.
</note>
</compatibility>
</eagle>
