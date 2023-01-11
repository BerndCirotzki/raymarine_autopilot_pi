Plugin for OpenCPN to control a Raymarine Seatalk 1 Autopilot

the Plugin receives data from NMEA0183 serialport in OpenCPN

the receiving an sending must have this Formt:
- Translated data from Autopilot 
$STALK,84,B6,A5,88,40,00,FE,02,06*62

- Sentence send from Plugin that mus be translated to Seatalk 1
$STALK,86,21,01,FE*4E


