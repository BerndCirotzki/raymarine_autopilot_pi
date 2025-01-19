Plugin for OpenCPN to control a Raymarine Autopilots
----------------------------------------------------
for Raymarine Seatalk1 (S1,S2,S3 ...)
and NEW for Raymarine EVO Autopilots  ( OpenCPN now can NMEA2000 ) 

this Version 2.x works only since OpenCPN Version 5.8.x and up. (NMEA2000 is needed.)

The Type of Autopilot can be selected in the preferences.

The Raymarine EVO Pilot must be connected over NMEA2000 (SeatalkNG) to OpenCPN or, new in this Version 2.2.x.x
it could also be connected over NMEA0183 using the Seasmart protocol. ($PCDIN......)
(When using Seasmart over NMEA0183 Serial, there is also the problem with the mirroring of the NMEA $PCDIN Sentence on the Serial Port. see below)

when a new NMEA2000 Connection is activated in the Option Connections, OpenCPN must be restated once.
- The Track function can be activated, but OpenCPN is not sending out NMEA2000 messages when a route is activ. So I think it will not work at the moment.

Also New in this version is the "AUTOCOG" function
-----------------------------------------------
- the Use can be activated in the preferences
- COG and SOG will be needed fom a GPS connected to OPENCPN, over NMEA0183, or NMEA2000.
when ist activated, "AUTOCOG" can be started with pushing "AUTO(COG)-Button" again and will be
deactivated also with pushing AUTOCOG Button again. (a toggle modus) 
It can also be use from an other Terminal (for example ST600x)

- Wenn is is Aktiv, the plugin sends new set heading Information to the Raymarine Autopilot-computer to set the heading fit to selected COG.
- The Set-COG Value can be changed with the normal buttons (+1,-1 ...)
- the sensebilty can be changed in the preferences.
- Also min SOG and max difference between COG and HDM can be set in the preferences.


Seatalk 1 Autopilots
---------------------
the Plugin receives data from NMEA0183 serialport in OpenCPN for Seatalk 1 Autopilots.
the receiving an sending must have this Formt:

Example for Translated data from Seatalk 1 Autopilot :
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
	

