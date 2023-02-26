Plugin for OpenCPN to control a Raymarine Seatalk 1 Autopilot

the Plugin receives data from NMEA0183 serialport in OpenCPN

the receiving an sending must have this Formt:

Example for Translated data from Autopilot :
$STALK,84,26,A2,88,40,00,FE,02,06*15

Needed Seatalk Command translated from Autopilot-Computer or other st600x Instruments : 0x84,0x86,0x87,0x91
(http://www.thomasknauf.de/rap/seatalk2.htm)

Example Sentence sending from Plugin that must be translated to Seatalk 1
$STALK,86,21,01,FE*4E

For using the Tracking Feature, the RMB and APB Sentence from Opencpn must be send to NMEA input from Autopilot Computer,
or the NMEA <-> Seatalk translater must translate the RMB an APB Sentences to Seatalk.

The Plugin now also is able to instert the Variation from the WMM-Plugin into a RMC Message from GPS an send out the modifyed sentence.
so all Raymarine Instrument getting the Variation from the WMM-Plugin.
( RMC Message translated to Seatalk Command necessary or RMC to NMEA input from Autopilot-Computer)

Because of the receive and the send sentence is the same "$STALK", OPENCPN mirrors the input sentence on an Serial output port.
If you don't want that, build your own OPENCPN and change the following line in the OPENCPN file "muliplexer.cpp"

if (params.Type == SERIAL || driver->iface != source_iface) {
  ... change to    
if (driver->iface != source_iface) {

I added some translations for Spanish, Dutch and French. .... but I think it's not perfekt.
If anyone likes to make a better One this will be OK. It's not my mother tongue.

Windows users can use the Installer :
raymarine_autopilot_pi-1.0.2.1-msvc-x86_64-O_5.6.x.exe for Opencpn up to Version 5.6.2
raymarine_autopilot_pi-1.0.2.1-msvc-x86_64-O_5.8.x.exe for Opencpn from Version 5.8.x
	

