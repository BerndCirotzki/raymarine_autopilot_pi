��    %      D  5   l      @     A  	   ]     g  /   y  �  �     q     �     �  o   �  P   )  0   z  f   �  <     9   O     �     �  C   �  q   �  K   g  c   �  l   	  j   �	  .   �	  I   
  I   h
     �
     �
  8   �
  S   �
  %   P     v     {  >   �  8   �     �  d     D  i  /   �     �     �  H     �  N  -   H  #   v     �  �   �  d   ]  F   �  p   	  9   z  >   �     �       K   /  �   {  U     u   b     �     X  S   �  M   ,  M   z     �     �  @   �  i     C   �     �     �  B   �  C   (     l  o   q            	           "   
          !                                 #              %                                                                                         $       Allow use AUTO-COG function Autopilot Autopilot Control Autopilot Control display zoom factor           Autopilot Control for Raymarine Smartpilot and Raymarine EVO
Simulates a Remote Control (Commandos from ST600x), by sending Seatalk(1) or SeatalkNG
Data. Requires Seatalk <-> NMEA Converter. The Sentences must be in the format
$SENTENCENAME,Seatalkbytes in Hex. ( $STALK,84,36,9D,88,40,00,FF,02,06*02 )
send to the NMEA Output Port. $SENTENCENAME named in the Preferences.
Or Send N2k Data to Raymarine EVO over NMEA2000 Connector mounted to OpenCPN. Autopilot Parameters changeable Autopilot Preferences Autopilot Type  : Change course value back to the last Compass course value, the Course Computer
had, before the Auto Signal lost Counter for Autopilot is in Standby Mode, but without "Standby" Command received Debug all "$STALK" Messages into OPENCPN Logfile Modify RMC Sentence as "$ECRMC" and replace or fill with Variationfield with the value from WMM Plugin NMEA Sentencename from  Seatalk bus converted by SeatalkLink NMEA Sentencename to Seatalk bus converted by SeatalkLink No Parameter selected No Value selected Raymarine Autopilot Control for Raymarine Smartpilot and EVO Pilots Send "Track" automatic when Autopilot has new Waypoint. Be careful with this normaly you have to accept yourself. Send PGN 126720 (keystroke) instead of PGN 126208 (set heading) in AutoMode Send new "Auto" Command, when No Standby-Information is received from other Instrument or from here Send new "Auto" or "Auto - Wind" Command, when "Standby" is not send from here, but the "Auto" was from here Send new "Auto" or "Auto-Wind" Command, when "Standby" is not send from here, but the "Auto" was from here Send new "Auto-Wind" Command when "Wind Shift" Send variation PGN 127258 to N2K/SeatalkNG with the value from WMM Plugin Send variation PNG 127258 to N2K/SeatalkNG with the value from WMM Plugin Sensibility  Set Time in seconds to wait before sending "Track" sentence. Value, for maximum  "Not recived Standby Commands" not sending "Auto" Command again Write Message Info to OPENCPN Logfile fast is set to   maximum difference between COG and magnetic heading in degrees minimun speed in nodes (SOG) for using AUTO-COG function slow the autopilot controller will get new +1 or -1 keystroke information to hold the Course Over Ground. Project-Id-Version: raymarine_autopilot_pi 1.0.000.0
Report-Msgid-Bugs-To: 
PO-Revision-Date: 2023-11-14 13:09+0100
Last-Translator: 
Language-Team: 
Language: fr_FR
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=2; plural=(n > 1);
X-Generator: Poedit 3.2.2
 Autoriser l'utilisation de la fonction AUTO-COG Raymarine Autopilot Pilote automatique Facteur de zoom de l'écran de contrôle du pilote automatique           Contrôle du pilote automatique pour Raymarine Smartpilot et Raymarine EVO
Simule une télécommande (Commandos du ST600x), en envoyant Seatalk(1) ou SeatalkNG
Données. Nécessite le convertisseur Seatalk <-> NMEA. Les phrases doivent être au format
$SENTENCENAME,Seatalkbytes en hexadécimal. ( $STALK,84,36,9D,88,40,00,FF,02,06*02 )
envoyer au port de sortie NMEA. $SENTENCENAME nommé dans les Préférences.
Ou envoyez des données N2k à Raymarine EVO via le connecteur NMEA2000 monté sur OpenCPN. Paramètres du pilote automatique modifiables Préférences du pilote automatique Type de pilote automatique : Changer la valeur de la trajectoire pour revenir à la dernière valeur de la trajectoire du compas, que le calculateur de route
avant la perte du signal automatique Le compteur du pilote automatique est en mode veille, mais sans que la commande "veille" soit reçue Déboguer tous les messages "$STALK" dans le fichier journal d'OPENCPN Modifiez la phrase RMC comme "$ECRMC" et remplacez ou remplissez le champ Variation avec la valeur du plugin WMM NMEA Sentencename du bus Seatalk converti par SeatalkLink Conversion de NMEA Sentencename en bus Seatalk par SeatalkLink Aucun paramètre sélectionné Aucune valeur sélectionnée Commande de pilote automatique pour les pilotes Raymarine Smartpilot et EVO Envoyer un "Track" automatique quand le pilote automatique a un nouveau waypoint. Soyez prudent avec ceci, vous devez normalement vous accepter. Envoyez le PGN 126720 (frappe) au lieu du PGN 126208 (définir le titre) en mode Auto Envoyer une nouvelle commande "Auto", lorsqu'aucune information de veille n'est reçue d'un autre instrument ou d'ici Envoyer une nouvelle commande "Auto" ou "Auto-Wind", lorsque "Standby" n'est pas envoyé d'ici, mais que "Auto" l'a été d'ici Envoyer une nouvelle commande "Auto" ou "Auto-Wind", lorsque "Standby" n'est pas envoyé d'ici, mais que "Auto" l'a été d'ici Envoyer une nouvelle commande "Auto-Wind" lorsque "Wind Shift" (changement de vent) Envoyer la variante PGN 127258 à N2K/SeatalkNG avec la valeur du plug-in WMM Envoyer la variante PGN 127258 à N2K/SeatalkNG avec la valeur du plug-in WMM Sensibilité  Mettre Temps en secondes à attendre avant d'envoyer la phrase "Track". Valeur, pour le maximum de "Commandes de veille non reçues" ne pas envoyer à nouveau la commande "Auto" Écrire les informations du message dans le fichier journal OPENCPN rapide est réglé sur   différence maximale entre le COG et le cap magnétique en degrés vitesse minimale en nœuds (SOG) pour utiliser la fonction AUTO-COG lent le contrôleur du pilote obtiendra de nouvelles informations de frappe +1 ou -1 pour maintenir la route au sol. 