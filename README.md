Plugin for OpenCPN to control a Raymarine Seatalk 1 Autopilot

the Plugin receives data from NMEA0183 serialport in OpenCPN

the receiving an sending must have this Formt:

Example for Translated data from Autopilot :
$STALK,84,26,A2,88,40,00,FE,02,06*15

Needed Seatalk Command translated from Autopilot-Computer or other st600x Instruments : 0x84,0x86,0x87,0x91
(http://www.thomasknauf.de/rap/seatalk2.htm)

Example Sentence sending from Plugin that mus be translated to Seatalk 1
$STALK,86,21,01,FE*4E

For using the Tracking Feature, the RMB and APB Sentence from Opencpn must be send to NMEA input from Autopilot Computer,
or the NMEA <-> Seatalk translater must translate the RMB an APB Sentences to Seatalk.

The Plugin now also is able to instert the Variation from the WMM-Plugin into a RMC Message from GPS an send out the modifyed sentence.
so all Raymarine Instrument getting the Variation from the WMM-Plugin.
( RMC Message translated to Seatalk Command necessary or RMC to NMEA input from Autopilot-Computer)



