/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  autopilot Plugin
 * Author:   Dipl-Ing. Bernd Cirotzki
 *
 ***************************************************************************
 *   Copyright (C) 2017 by Bernd Cirotzki                                  *
 *                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 ***************************************************************************
 */

#ifndef _CALCULATOR_PI_H_
#define _CALCULATOR_PI_H_

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
  #include <wx/glcanvas.h>
#endif //precompiled headers

#include <wx/fileconf.h>

#include "ocpn_plugin.h" //Required for OCPN plugin functions
#include "autopilotgui_impl.h"
#include "Seasmart.h"

#include "wx/jsonreader.h"
#include "wx/jsonwriter.h"

#include "nmea0183.h"
// #include <N2kMessages.h>
#include "N2KParser.h"
#include "version.h"

#define AUTO		1
#define STANDBY		2
#define AUTOWIND	3
#define TRACK		4
#define	WINDSHIFT	5
#define AUTOTRACK	6
#define OFFCOURSE	7
#define AUTOTURNWP  12
#define UNKNOWN		0
#define IncrementOne 8
#define IncrementTen 9
#define DecrementOne 10
#define DecrementTen 11
#define Nothing     0
#define SMARTPILOT  0
#define EVO         1
#define EVOSEASMART 2
#define MAX_NMEA0183_MSG_LEN 81  // According to NMEA 3.01

class Dlg;
class localTimer;
class N2kContainer;
class AutoCogTimer;
class GPSTimer;

// forgotten to define in N2KParser.h
extern tN2kMsg MakeN2kMsg(std::vector<unsigned char>& v);
//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

#define CALCULATOR_TOOL_POSITION    -1          // Request default positioning of toolbar tool

class raymarine_autopilot_pi : public wxEvtHandler, public opencpn_plugin_118
{
	
public:
      raymarine_autopilot_pi(void *ppimgr);
	   ~raymarine_autopilot_pi(void);
	  void SendNMEASentence(wxString sentence);

	  wxString ComputeChecksum(wxString sentence);
//    The required PlugIn Methods
      int Init(void);
      bool DeInit(void);

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();
      int GetPlugInVersionPatch();
      int GetPlugInVersionPost();
      wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();
	  void SetNMEASentence(wxString &sentence_incomming);
	  void SetPluginMessage(wxString &message_id, wxString &message_body);

//    The required override PlugIn Methods
      int GetToolbarToolCount(void);
	  void ShowPreferencesDialog(wxWindow* parent);
      void OnToolbarToolCallback(int id);

//    Optional plugin overrides
      //void SetColorScheme(PI_ColorScheme cs);


//    The override PlugIn Methods

//    Other public methods
      void SetCalculatorDialogX         (int x){ m_route_dialog_x = x;};
      void SetCalculatorDialogY         (int x){ m_route_dialog_y = x;};
      void SetCalculatorDialogWidth     (int x){ m_route_dialog_width = x;};
      void SetCalculatorDialogHeight    (int x){ m_route_dialog_height = x;};
      void SetAutopilotparametersChangeable();
	  void OnautopilotDialogClose();
	  void AddVariationToRMCanSendOut(wxString &sentence_incomming);
      void ActivateAutoCOG();
      void DeActivateAutoCOG();
      void ResetAUTOCOGValues();
      // pushed Buttons
      void SendGotoAuto();
      void SendGotoStandby();
      void SendGotoAutoWind();
      void SendGotoAutoTrack();
      void SendIncrementOne();
      void SendIncrementTen();
      void SendDecrementOne();
      void SendDecrementTen();
      bool EnableEVOEvents();
      void DisableEVOEvents();

      wxTimer          *p_GPSTimer;
      uint8_t          AutoPilotType;
	  int			   Autopilot_Status;
	  int			   Autopilot_Status_Before;
	  int			   DisplayShow; // Anzahl ser $STALK,84, ... Sequenzen, bis wieder Werte anzezeigt werden.
	  bool			   ShowParameters;
	  bool			   NewAutoWindCommand;
	  bool			   NewAutoOnStandby;
	  bool			   ChangeValueToLast;
	  bool			   SendTrack;
	  int			   TimeToSendNewWaypiont;
	  int		       GoneTimeToSendNewWaypoint;
	  bool			   WriteMessages;
	  bool			   WriteDebug;
	  bool			   ModyfyRMC;
      int			   LastCompassCourse;
	  bool             NewStandbyNoStandbyReceived;
      bool             m_bShowautopilot;
	  wxString	       STALKSendName;
	  wxString		   STALKReceiveName;
	  bool			   StandbySelfPressed;
	  bool             Standbycommandreceived;
	  bool			   NeedCompassCorrection;
	  int			   CounterStandbySentencesReceived;
	  int			   NoStandbyCounter;
	  int			   SelectCounterStandby;
	  int			   IS_standby;
	  int			   ResponseLevel;
	  int              RudderLevel;
	  double           BoatVariation;
      double           Skalefaktor;
	  Dlg			   *m_pDialog;
	  wxString		   WayPointBearing;
      int              MAGcourse;
      uint8_t          MyLastSend;
      // AUTO-COG
      bool             AutoCOGStatus;
      bool             allowautocog;
      int              cogsensibility;
      int              maxdegreediff;
      double           minspeedcog;
      int              maxchangehdg;
      int              SOG_counter;
      int              COG_counter;
      int              SOG_valid;
      int              COG_valid;
      double           SOGA[3];
      double           SOG;
      int              COGA[30];
      int              COG;
      int              COGCourse;
      int8_t           LastChange;
      double           EVOLockeHeading;
      bool             Received_65379;
      bool             GetHeadingFromSeatalkNG;
      bool             Received_Heading_126208;
      bool             Received_AUTO_126208;
      bool             Received_LockedHeading_inStandby;
      int              AutoCOGHeadingChange;
      // Dialog Style
      int              m_route_dialog_x, m_route_dialog_y;
      long             DialogStyle;

private:
      
	  int GetAutopilotMode(wxString &sentence);
	  bool ConfirmNextWaypoint(const wxString &sentence);
	  void GetWaypointBearing(const wxString &sentence);
	  wxString GetAutopilotCompassCourse(wxString &sentence);
	  wxString GetAutopilotMAGCourse(wxString &sentence);
	  wxString GetAutopilotCompassDifferenz(wxString &sentence);
	  char GetHexValue(char AsChar);	  
      void ActualisateCOGSOG(wxString &sentence);
      void WriteCOGStatus();
      void MakeCOGSOG(double SpeedOverGroundKnots, int TrackMadeGoodDegreesTrue);
      void SendBoatVariationToN2k();
      void SendN2kMessage(tN2kMsg N2kMsg);
      void ToUpdateAutoPilotControlDisplay(wxString sentence = "EVO");
      void CheckSeasartSentence(wxString sentence);
	  raymarine_autopilot_pi *plugin;

      // Thanks for that from AutoTrackRaymarine Plugin !
      void HandleN2K_65360(ObservedEvt ev); // Pilot heading
      void HandleN2K_126208(ObservedEvt ev); // Set Set pilot heading or set auto/standby
      void HandleN2K_126720(ObservedEvt ev); // From EV1 indicating auto or standby state  ... and more !!!
      void HandleN2K_65379(ObservedEvt ev); // Pilot State
      void HandleN2K_65288(ObservedEvt ev); // Pilot Alarm
      void HandleN2K_65359(ObservedEvt ev); // Vessel heading, proprietary
      void HandleN2K_127250(ObservedEvt ev); // Vessel heading, standerd NMEA2000 
      void HandleN2K_129026(ObservedEvt ev); // COG SOG for AutoCOG 
      void HandleN2K_126992(ObservedEvt ev); // SystemTime
      void HandleN2K_129029(ObservedEvt ev); // Position

      std::shared_ptr<ObservableListener> listener_65360;  // Autopilot heading if auto
      std::shared_ptr<ObservableListener> listener_126208; // Set pilot heading or set auto/standby
      std::shared_ptr<ObservableListener> listener_126720; // From EV1 indicating auto or standby state  ... and more !!
      std::shared_ptr<ObservableListener> listener_65379;  // Pilot State
      std::shared_ptr<ObservableListener> listener_65288;  // Pilot Alarm
      std::shared_ptr<ObservableListener> listener_65359;  // Vessel heading
      std::shared_ptr<ObservableListener> listener_127250; // Vessel heading
      std::shared_ptr<ObservableListener> listener_129026; // COG SOG for AutoCOG
      std::shared_ptr<ObservableListener> listener_126992; // SystemTime
      std::shared_ptr<ObservableListener> listener_129029; // Position

      void HandleN2kMsg_65360(tN2kMsg N2kMsg); // Pilot heading
      void HandleN2kMsg_126208(tN2kMsg N2kMsg); // Set Set pilot heading or set auto/standby
      void HandleN2kMsg_126720(tN2kMsg N2kMsg); // From EV1 indicating auto or standby state  ... and more !!!
      void HandleN2kMsg_65379(tN2kMsg N2kMsg); // Pilot State
      void HandleN2kMsg_65288(tN2kMsg N2kMsg); // Pilot Alarm
      void HandleN2kMsg_65359(tN2kMsg N2kMsg); // Vessel heading, proprietary
      void HandleN2kMsg_127250(tN2kMsg N2kMsg); // Vessel heading, standerd NMEA2000 
      void HandleN2kMsg_129026(tN2kMsg N2kMsg); // COG SOG for AutoCOG 
      void HandleN2kMsg_126992(tN2kMsg N2kMsg); // SystemTime
      void HandleN2kMsg_129029(tN2kMsg N2kMsg); // Position

	  wxLog				*pLogger;
	  wxFileConfig      *m_pconfig;
      wxWindow          *m_parent_window;
      bool              LoadConfig(void);
      bool              SaveConfig(void);      
      int               m_route_dialog_width,m_route_dialog_height;
      int               m_display_width, m_display_height;      
      int               m_leftclick_tool_id;
      bool              m_ShowHelp,m_bCaptureCursor,m_bCaptureShip;
      double			m_ship_lon,m_ship_lat,m_cursor_lon,m_cursor_lat;
	  bool              m_bautopilotShowIcon;
	  wxTimer		   *p_Resettimer;
      wxTimer          *p_AutoCogTimer;	  
      int               WMM_receive_count;
      N2kContainer*     pHandleN2k;
      uint16_t          DaysSince1970;      
};

class N2kContainer
{
public :
    N2kContainer(DriverHandle Handler) { pNext = NULL; HandleN2k = Handler; };
    ~N2kContainer() { if (pNext != NULL) delete pNext; };
    DriverHandle  HandleN2k;
    N2kContainer *pNext;
};

class localTimer :public wxTimer
{
public:
	localTimer(raymarine_autopilot_pi *pAuto);
	~localTimer(){};
	void Notify();
private:
		raymarine_autopilot_pi *pAutopilot;
};

class AutoCogTimer :public wxTimer
{
public:
    AutoCogTimer(raymarine_autopilot_pi* pAuto) { pAutopilot = pAuto; };
    ~AutoCogTimer() {};
    void Notify();
private:
    raymarine_autopilot_pi* pAutopilot;
};

class GPSTimer :public wxTimer
{
public:
    GPSTimer(raymarine_autopilot_pi* pAuto) { pAutopilot = pAuto; };
    ~GPSTimer() {};
    void Notify() { pAutopilot->ResetAUTOCOGValues(); };
private:
    raymarine_autopilot_pi* pAutopilot;
};

// N2k
void SetN2kPGN126208(tN2kMsg& N2kMsg, uint8_t mode, uint8_t PilotSourceAddress);
void SetRaymarineLockedHeadingN2kPGN126208(tN2kMsg& N2kMsg, double Heading);
void SetRaymarineKeyCommandPGN126720(tN2kMsg& N2kMsg, uint8_t destinationAddress, uint16_t command);
bool ParseN2kPGN65360(const tN2kMsg& N2kMsg, double& HeadingTrue, double& HeadingMagnetic);
bool ParseN2kPGN65379(const tN2kMsg& N2kMsg, unsigned char& Mode, unsigned char& Submode);
bool ParseN2kPGN65288(const tN2kMsg& N2kMsg, unsigned char& AlarmStatus, unsigned char& AlarmCode, unsigned char& AlarmGroup);
bool ParseN2kPGN126208(const tN2kMsg& N2kMsg, uint8_t& CommandMode, double& Value);
bool ParseN2kPGN126720(const tN2kMsg& N2kMsg, uint8_t& Mode, uint8_t& SubMode, uint16_t& commandValues);
bool ParseN2kPGN65359(const tN2kMsg& N2kMsg, double& HeadingTrue, double& HeadingMagnetic);

#endif
