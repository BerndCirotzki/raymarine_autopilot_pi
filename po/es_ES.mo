��    "      ,  /   <      �     �  	     /     �  O          7     M  o   _  P   �  0      f   Q  <   �  9   �     /     E  C   W  q   �  K     c   Y  j   �  .   (	  I   W	  I   �	     �	  8   �	  S   1
  %   �
     �
     �
  >   �
  8   �
     4  d   9  @  �  '   �       C   %  �  i  -   M  "   {     �  �   �  g   H  H   �  r   �  B   l  @   �     �       E   +  �   q  j   �  l   a  t   �  7   C  P   {  P   �       A   +  c   m  E   �            9   2  @   l     �  z   �                                                 
                               	                     "                                    !                     Allow use AUTO-COG function Autopilot Autopilot Control display zoom factor           Autopilot Control for Raymarine Smartpilot and Raymarine EVO
Simulates a Remote Control (Commandos from ST600x), by sending Seatalk(1) or SeatalkNG
Data. Requires Seatalk <-> NMEA Converter. The Sentences must be in the format
$SENTENCENAME,Seatalkbytes in Hex. ( $STALK,84,36,9D,88,40,00,FF,02,06*02 )
send to the NMEA Output Port. $SENTENCENAME named in the Preferences.
Or Send N2k Data to Raymarine EVO over NMEA2000 Connector mounted to OpenCPN. Autopilot Parameters changeable Autopilot Preferences Autopilot Type  : Change course value back to the last Compass course value, the Course Computer
had, before the Auto Signal lost Counter for Autopilot is in Standby Mode, but without "Standby" Command received Debug all "$STALK" Messages into OPENCPN Logfile Modify RMC Sentence as "$ECRMC" and replace or fill with Variationfield with the value from WMM Plugin NMEA Sentencename from  Seatalk bus converted by SeatalkLink NMEA Sentencename to Seatalk bus converted by SeatalkLink No Parameter selected No Value selected Raymarine Autopilot Control for Raymarine Smartpilot and EVO Pilots Send "Track" automatic when Autopilot has new Waypoint. Be careful with this normaly you have to accept yourself. Send PGN 126720 (keystroke) instead of PGN 126208 (set heading) in AutoMode Send new "Auto" Command, when No Standby-Information is received from other Instrument or from here Send new "Auto" or "Auto-Wind" Command, when "Standby" is not send from here, but the "Auto" was from here Send new "Auto-Wind" Command when "Wind Shift" Send variation PGN 127258 to N2K/SeatalkNG with the value from WMM Plugin Send variation PNG 127258 to N2K/SeatalkNG with the value from WMM Plugin Sensibility  Time in seconds to wait before sending "Track" sentence. Value, for maximum  "Not recived Standby Commands" not sending "Auto" Command again Write Message Info to OPENCPN Logfile fast is set to   maximum difference between COG and magnetic heading in degrees minimun speed in nodes (SOG) for using AUTO-COG function slow the autopilot controller will get new +1 or -1 keystroke information to hold the Course Over Ground. Project-Id-Version: raymarine_autopilot_pi 1.0.2.0
Report-Msgid-Bugs-To: 
PO-Revision-Date: 2023-11-14 13:08+0100
Last-Translator: 
Language-Team: 
Language: es
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n != 1);
X-Generator: Poedit 3.2.2
 Permitir el uso de la función AUTO-COG Control de piloto automático Factor de zoom de la pantalla de control del piloto automático     Control de piloto automático para Raymarine Smartpilot y Raymarine EVO
Simula un Control Remoto (Comandos desde ST600x), enviando Seatalk(1) o SeatalkNG
Datos. Requiere convertidor Seatalk <-> NMEA. Las oraciones deben tener el formato
$SENTENCENAME,Setalkbytes en hexadecimal. ( $STALK,84,36,9D,88,40,00,FF,02,06*02 )
enviar al puerto de salida NMEA. $SENTENCENAME nombrado en las Preferencias.
O envíe datos N2k a Raymarine EVO a través del conector NMEA2000 montado en OpenCPN. Parámetros del piloto automático cambiables Preferencias de piloto automático Tipo de piloto automático : Cambie el valor del rumbo al último valor del rumbo de Compass, la computadora de rumbo
tenía, antes de que la señal automática perdiera El contador del piloto automático está en modo de espera, pero no se ha recibido el comando "Standby" Depurar todos los mensajes "$STALK" en el archivo de registro de OPENCPN Modifique la oración RMC como "$ECRMC" y reemplace o rellene el campo Variación con el valor del complemento WMM NMEA Sentencename del bus Seatalk convertido por Seatalktranslater Bus NMEA Sentencename a Seatalk convertido por Seatalktranslator Ningún parámetro seleccionado Ningún valor seleccionado Control de piloto automático para pilotos Raymarine Smartpilot y EVO Envía "Track" automáticamente cuando Autopilot tiene un nuevo Waypoint. Ojo con esto normalmente te tienes que aceptar a ti mismo. Envíe PGN 126720 (pulsación de tecla) en lugar de PGN 126208 (establezca encabezado) en modo automático Envíe un nuevo comando "Auto", cuando no se reciba información de espera de otro instrumento o desde aquí Envíe un nuevo comando "Auto" o "Auto-Wind", cuando "Standby" no se envíe desde aquí, pero "Auto" fue desde aquí Envía un nuevo comando "Auto-Wind" cuando "Wind Shift" Envíe la variación PGN 127258 a N2K/SeatalkNG con el valor del complemento WMM Envíe la variación PGN 127258 a N2K/SeatalkNG con el valor del complemento WMM Sensibilidad  Iempo en segundos de espera antes de enviar la sentencia "Track". Valor, para un máximo de "Comandos de espera no recibidos" sin enviar el comando "Auto" nuevamente Escribir información de mensaje en el archivo de registro de OPENCPN rápido se establece en    diferencia máxima entre COG y rumbo magnético en grados velocidad mínima en nodos (SOG) para usar la función AUTO-COG. lento el piloto automático obtendrá nueva información de pulsación de tecla +1 o -1 para mantener el rumbo sobre el terreno. 