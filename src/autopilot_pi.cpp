/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  autopilot Plugin
 * Author:   Dipl.Ing. Bernd Cirotzki
 *
 ***************************************************************************
 *   Copyright (C) 2017 by Bernd Cirotzki                                  *
 *   eMail : Bernd.Cirotzki@t-online.de                                    *
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
 ***************************************************************************
 */
// See build wxWidgets https://docs.wxwidgets.org/latest/plat_msw_install.html

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include <wx/event.h>
#include "autopilot_pi.h"
#include "autopilotgui_impl.h"
#include "autopilotgui.h"

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new raymarine_autopilot_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}

//---------------------------------------------------------------------------------------------------------
//
//    autopilot PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

#include "icons.h"

//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

raymarine_autopilot_pi::raymarine_autopilot_pi(void *ppimgr) :opencpn_plugin_118(ppimgr)
{
      // Create the PlugIn icons
      initialize_images();
	  m_bShowautopilot = false;
	  Autopilot_Status = UNKNOWN;
	  StandbySelfPressed = FALSE;
	  LastCompassCourse = -1; // Nicht g?ltig
	  NeedCompassCorrection = false;
	  wxLogMessage(("    Creating Raymarine Autopilot Plugin"));
}

raymarine_autopilot_pi::~raymarine_autopilot_pi(void)
{
     delete _img_autopilot_pi;
     _img_autopilot_pi = NULL;
     delete _img_autopilot;
     _img_autopilot = NULL;
	 wxLogMessage(("    Deleting Raymarine Autopilot Plugin"));
}

int raymarine_autopilot_pi::Init(void)
{
      AddLocaleCatalog( _T("opencpn-raymarine_autopilot_pi") );

      // Set some default private member parameters
      m_route_dialog_x = 0;
      m_route_dialog_y = 0;
      ::wxDisplaySize(&m_display_width, &m_display_height);

      //    Get a pointer to the opencpn display canvas, to use as a parent for the POI Manager dialog
      m_parent_window = GetOCPNCanvasWindow();

      //    Get a pointer to the opencpn configuration object
      m_pconfig = GetOCPNConfigObject();

	  // Standardparameter settings
	  ShowParameters = TRUE;
	  NewAutoWindCommand = FALSE;
	  NewAutoOnStandby = FALSE;
	  SendTrack = FALSE;
	  GoneTimeToSendNewWaypoint = 0;
	  TimeToSendNewWaypiont = 10; // Default 10 Sekunden.
	  WriteMessages = FALSE;
	  WriteDebug = FALSE;
	  ModyfyRMC = FALSE;
	  STALKSendName = "STALK";
	  STALKReceiveName = "STALK";
	  p_Resettimer = NULL;
	  StandbySelfPressed = FALSE;
	  Autopilot_Status_Before = UNKNOWN;
	  NoStandbyCounter = 0;
	  ResponseLevel = 0; // Unbekannter Responselevel.
	  RudderLevel = 0; // Unbekannt
	  Standbycommandreceived = TRUE;
	  CounterStandbySentencesReceived = 0;
      Skalefaktor = 1;
	  IS_standby = 0;
	  BoatVariation = 0x01FF;  // Not Avalibal
      WMM_receive_count = 60; // set to No Information from WMM
	  WayPointBearing = "unknown";
      // AUTO-COG
      AutoCOGStatus = false;
      allowautocog = true; 
      cogsensibility = 15;
      maxdegreediff = 45;
      minspeedcog = 1.5;
      maxchangehdg = 20;
      p_AutoCogTimer = NULL;
      p_GPSTimer = NULL;
      MAGcourse = -1;
      MyLastSend = Nothing;
      AutoPilotType = SMARTPILOT;
      DaysSince1970 = N2kUInt16NA;
      EVOLockeHeading = N2kDoubleNA;
      AutoCOGHeadingChange = 0;
      DialogStyle = wxDEFAULT_DIALOG_STYLE;
      //    And load the configuration items
      LoadConfig();
	  if (Skalefaktor < 1 || Skalefaktor > 2.1)
		  Skalefaktor = 1;
	  //    This PlugIn needs a toolbar icon, so request its insertion
	  if(m_bautopilotShowIcon)
		m_leftclick_tool_id  = InsertPlugInTool(_T(""), _img_autopilot, _img_autopilot, wxITEM_CHECK,
            _("Raymarine Autopilot"), _T(""), NULL,
             CALCULATOR_TOOL_POSITION, 0, this);

      m_pDialog = NULL;
	  DisplayShow = 0;
	  m_pDialog = new Dlg(m_parent_window, Skalefaktor, DialogStyle);
	  m_pDialog->plugin = this;
	  m_pDialog->Move(wxPoint(m_route_dialog_x, m_route_dialog_y));
      ResetAUTOCOGValues();
	  if (m_bShowautopilot) {
		  m_pDialog->Show();
		  if (NoStandbyCounter != 0)
		  {
			  m_pDialog->SetBgTextStatusColor(wxColour(255, 128, 128));
			  m_pDialog->SetBgTextCompassColor(wxColour(255, 128, 128));
		  }
		  SetAutopilotparametersChangeable();
		  // 
		  if (NULL == p_Resettimer)
		  {
			  p_Resettimer = new localTimer(this);
			  p_Resettimer->StartOnce(12000);
		  }		  
	  }
	  else
	  {
		  m_pDialog->Hide();
		  if (NULL != p_Resettimer)
		  {
			  p_Resettimer->Stop();
			  delete p_Resettimer;
			  p_Resettimer = NULL;
		  }
	  }

      // initialize NavMsg listeners
      //-----------------------------
      Received_65379 = false;
      Received_Heading_126208 = false;
      GetHeadingFromSeatalkNG = false;
      Received_AUTO_126208 = false;
      Received_LockedHeading_inStandby = false;
      pHandleN2k = NULL;
      N2kContainer** ppN2kContainer = &pHandleN2k;

      for (const auto& Handler : GetActiveDrivers()) {
          const auto& attributes = GetAttributes(Handler);
          if (attributes.find("protocol") == attributes.end())
              continue;
          if (attributes.at("protocol") == "nmea2000") { // could be more than one NMEA2000 Port.
              if (*ppN2kContainer == NULL) {
                  *ppN2kContainer = new N2kContainer(Handler);
                  ppN2kContainer = &(*ppN2kContainer)->pNext;
              }
          }
      } 

      if (pHandleN2k != NULL) // NMEA2000 Connection is avalibal
      {
          // COG SOG rapid   PGN 129026
          wxDEFINE_EVENT(EVT_N2K_129026, ObservedEvt);
          NMEA2000Id id_129026 = NMEA2000Id(129026);
          listener_129026 = std::move(GetListener(id_129026, EVT_N2K_129026, this));
          Bind(EVT_N2K_129026, [&](ObservedEvt ev) { HandleN2K_129026(ev); });

          // Heading PGN 127250
          wxDEFINE_EVENT(EVT_N2K_127250, ObservedEvt);
          NMEA2000Id id_127250 = NMEA2000Id(127250);
          listener_127250 = std::move(GetListener(id_127250, EVT_N2K_127250, this));
          Bind(EVT_N2K_127250, [&](ObservedEvt ev) { HandleN2K_127250(ev); });

          // SystemTime
          wxDEFINE_EVENT(EVT_N2K_126992, ObservedEvt);
          NMEA2000Id id_126992 = NMEA2000Id(126992);
          listener_126992 = std::move(GetListener(id_126992, EVT_N2K_126992, this));
          Bind(EVT_N2K_126992, [&](ObservedEvt ev) { HandleN2K_126992(ev); });

          // Position
          wxDEFINE_EVENT(EVT_N2K_129029, ObservedEvt);
          NMEA2000Id id_129029 = NMEA2000Id(129029);
          listener_129029 = std::move(GetListener(id_129029, EVT_N2K_129029, this));
          Bind(EVT_N2K_129029, [&](ObservedEvt ev) { HandleN2K_129029(ev); });

          std::vector<int> pgn_list = { 127258, 126208, 126720 };

          N2kContainer* pH = pHandleN2k;
          while (pH != NULL)
          {
              RegisterTXPGNs(pH->HandleN2k, pgn_list);
              pH = pH->pNext;
          }          
      }
      if (AutoPilotType == EVO)
          EnableEVOEvents();
      
      return (WANTS_PREFERENCES |
		      WANTS_TOOLBAR_CALLBACK |
		      WANTS_NMEA_EVENTS |
			  WANTS_NMEA_SENTENCES |
			  WANTS_PLUGIN_MESSAGING);
	
	  /*
	  return (WANTS_OVERLAY_CALLBACK |
		  WANTS_OPENGL_OVERLAY_CALLBACK |
		  WANTS_CURSOR_LATLON |
		  WANTS_TOOLBAR_CALLBACK |
		  INSTALLS_TOOLBAR_TOOL |
		  WANTS_NMEA_EVENTS |
		  WANTS_NMEA_SENTENCES |
		  WANTS_PREFERENCES |
		  WANTS_CONFIG |
		  WANTS_PLUGIN_MESSAGING);
        */ 
}


bool raymarine_autopilot_pi::EnableEVOEvents()
{
    if (pHandleN2k == NULL) // No NMEA2000 Connection in OpenCPN defined
    {
        AutoPilotType = SMARTPILOT;
        wxMessageBox(_("For use EVO Pilot, define NMEA2000/SeatalkNG connection and restart OpenCPN"));
        return false;
    }

    // Pilot heading
    wxDEFINE_EVENT(EVT_N2K_65360, ObservedEvt);
    NMEA2000Id id_65360 = NMEA2000Id(65360);
    listener_65360 = std::move(GetListener(id_65360, EVT_N2K_65360, this));
    Bind(EVT_N2K_65360, [&](ObservedEvt ev) { HandleN2K_65360(ev); });

    // Set Set pilot heading or set auto/standby
    wxDEFINE_EVENT(EVT_N2K_126208, ObservedEvt);
    NMEA2000Id id_126208 = NMEA2000Id(126208);
    listener_126208 = std::move(GetListener(id_126208, EVT_N2K_126208, this));
    Bind(EVT_N2K_126208, [&](ObservedEvt ev) { HandleN2K_126208(ev); });

    // From EV1 indicating auto or standby state ... Is this only from Seatlak SeatalkNG translaterfrom Raymarine ???
    wxDEFINE_EVENT(EVT_N2K_126720, ObservedEvt);
    NMEA2000Id id_126720 = NMEA2000Id(126720);
    listener_126720 = std::move(GetListener(id_126720, EVT_N2K_126720, this));
    Bind(EVT_N2K_126720, [&](ObservedEvt ev) { HandleN2K_126720(ev); });

    // From EV1 Pilotstate
    wxDEFINE_EVENT(EVT_N2K_65379, ObservedEvt);
    NMEA2000Id id_65379 = NMEA2000Id(65379);
    listener_65379 = std::move(GetListener(id_65379, EVT_N2K_65379, this));
    Bind(EVT_N2K_65379, [&](ObservedEvt ev) { HandleN2K_65379(ev); });

    // From EV1 PilotAlarm
    wxDEFINE_EVENT(EVT_N2K_65288, ObservedEvt);
    NMEA2000Id id_65288 = NMEA2000Id(65288);
    listener_65288 = std::move(GetListener(id_65288, EVT_N2K_65288, this));
    Bind(EVT_N2K_65288, [&](ObservedEvt ev) { HandleN2K_65288(ev); });

    // Vessel heading, proprietary
    wxDEFINE_EVENT(EVT_N2K_65359, ObservedEvt);
    NMEA2000Id id_65359 = NMEA2000Id(65359);
    listener_65359 = std::move(GetListener(id_65359, EVT_N2K_65359, this));
    Bind(EVT_N2K_65359, [&](ObservedEvt ev) { HandleN2K_65359(ev); });
    return true;
}

bool raymarine_autopilot_pi::DeInit(void)
{
      //    Record the dialog position
      if (NULL != m_pDialog)
      {
            //Capture dialog position
            wxPoint p = m_pDialog->GetPosition();
            SetCalculatorDialogX(p.x);
            SetCalculatorDialogY(p.y);
            m_pDialog->Close();
            delete m_pDialog;
            m_pDialog = NULL;
			// m_bShowautopilot = false;
			SetToolbarItemState( m_leftclick_tool_id, m_bShowautopilot );
      }      
	  if (NULL != p_Resettimer)
	  {
		  p_Resettimer->Stop();
		  delete p_Resettimer;
		  p_Resettimer = NULL;
	  }
      if (NULL != p_GPSTimer)
      {
          p_GPSTimer->Stop();
          delete p_GPSTimer;
          p_GPSTimer = NULL;
      }
      if (NULL != p_AutoCogTimer)
      {
          p_AutoCogTimer->Stop();
          delete p_AutoCogTimer;
          p_AutoCogTimer = NULL;
      }
      if (pHandleN2k != NULL)
      {
          delete pHandleN2k;
          pHandleN2k = NULL;
      }
      if (AutoPilotType == EVO)
        DisableEVOEvents();
    SaveConfig();
    RequestRefresh(m_parent_window); // refresh mainn window 
    return true;
}

void raymarine_autopilot_pi::DisableEVOEvents()
{
    if (pHandleN2k == NULL) // No NMEA2000 Connection in OpenCPN defined
        return;

    // Pilot heading
    wxDEFINE_EVENT(EVT_N2K_65360, ObservedEvt);    
    Unbind(EVT_N2K_65360, [&](ObservedEvt ev) { HandleN2K_65360(ev); });

    // Set Set pilot heading or set auto/standby
    wxDEFINE_EVENT(EVT_N2K_126208, ObservedEvt);    
    Unbind(EVT_N2K_126208, [&](ObservedEvt ev) { HandleN2K_126208(ev); });

    // From EV1 indicating auto or standby state ... Is this only from Seatlak SeatalkNG translaterfrom Raymarine ???
    wxDEFINE_EVENT(EVT_N2K_126720, ObservedEvt);    
    Unbind(EVT_N2K_126720, [&](ObservedEvt ev) { HandleN2K_126720(ev); });

    // From EV1 Pilotstate
    wxDEFINE_EVENT(EVT_N2K_65379, ObservedEvt);    
    Unbind(EVT_N2K_65379, [&](ObservedEvt ev) { HandleN2K_65379(ev); });

    // From EV1 PilotAlarm
    wxDEFINE_EVENT(EVT_N2K_65288, ObservedEvt);    
    Unbind(EVT_N2K_65288, [&](ObservedEvt ev) { HandleN2K_65288(ev); });

    // Vessel heading, proprietary
    wxDEFINE_EVENT(EVT_N2K_65359, ObservedEvt);    
    Unbind(EVT_N2K_65359, [&](ObservedEvt ev) { HandleN2K_65359(ev); });
}


int raymarine_autopilot_pi::GetAPIVersionMajor()
{
      return OCPN_API_VERSION_MAJOR;
}

int raymarine_autopilot_pi::GetAPIVersionMinor()
{
      return OCPN_API_VERSION_MINOR;
}

int raymarine_autopilot_pi::GetPlugInVersionMajor()
{
      return PLUGIN_VERSION_MAJOR;
}

int raymarine_autopilot_pi::GetPlugInVersionMinor()
{
      return PLUGIN_VERSION_MINOR;
}

int raymarine_autopilot_pi::GetPlugInVersionPatch()
{
      return PLUGIN_VERSION_PATCH;
}

int raymarine_autopilot_pi::GetPlugInVersionPost()
{
      return PLUGIN_VERSION_TWEAK;
}

wxBitmap *raymarine_autopilot_pi::GetPlugInBitmap()
{
      return _img_autopilot_pi;
}

wxString raymarine_autopilot_pi::GetCommonName()
{
      return PLUGIN_COMMON_NAME;
}


wxString raymarine_autopilot_pi::GetShortDescription()
{
      return _("Raymarine Autopilot Control for Raymarine Smartpilot and EVO Pilots");
}

wxString raymarine_autopilot_pi::GetLongDescription()
{
      return _("Autopilot Control for Raymarine Smartpilot and Raymarine EVO\r\n\
Simulates a Remote Control (Commandos from ST600x), by sending Seatalk(1) or SeatalkNG\r\n\
Data. Requires Seatalk <-> NMEA Converter. The Sentences must be in the format\r\n\
$SENTENCENAME,Seatalkbytes in Hex. ( $STALK,84,36,9D,88,40,00,FF,02,06*02 )\r\n\
send to the NMEA Output Port. $SENTENCENAME named in the Preferences.\r\n\
Or Send N2k Data to Raymarine EVO over NMEA2000 Connector mounted to OpenCPN.");
}

int raymarine_autopilot_pi::GetToolbarToolCount(void)
{
      return 1;
}

void raymarine_autopilot_pi::OnToolbarToolCallback(int id)
{
      if(NULL == m_pDialog)
      {
            m_pDialog = new Dlg(m_parent_window, Skalefaktor, DialogStyle);
            m_pDialog->plugin = this;
			m_pDialog->Move(wxPoint(m_route_dialog_x, m_route_dialog_y));
      }
	  else
	  {		  
		  if (NoStandbyCounter != 0)
		  {
			  m_pDialog->SetBgTextStatusColor(wxColour(255, 128, 128));
			  m_pDialog->SetBgTextCompassColor(wxColour(255, 128, 128));
		  }
	  }
	  m_pDialog->Fit();
	  //Toggle 
	  m_bShowautopilot = !m_pDialog->IsShown();
      //    Toggle dialog? 
      if(m_bShowautopilot) {
          m_pDialog->Show();
		  if (NoStandbyCounter != 0)
		  {
			  m_pDialog->SetBgTextStatusColor(wxColour(255, 128, 128));
			  m_pDialog->SetBgTextCompassColor(wxColour(255, 128, 128));
		  }
		  SetAutopilotparametersChangeable();
		  // 
		  if (NULL == p_Resettimer)
		  {
			  p_Resettimer = new localTimer(this);
			  p_Resettimer->StartOnce(12000);
		  }
	  }
	  else
	  {
		  m_pDialog->Hide();
		  if (NULL != p_Resettimer)
		  {
			  p_Resettimer->Stop();
			  delete p_Resettimer;
			  p_Resettimer = NULL;
		  }
	  }
      // Toggle is handled by the toolbar but we must keep plugin manager b_toggle updated
      // to actual status to ensure correct status upon toolbar rebuild
      SetToolbarItemState( m_leftclick_tool_id, m_bShowautopilot );

      RequestRefresh(m_parent_window); // refresh main window
}

bool raymarine_autopilot_pi::LoadConfig(void)
{
      wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

      if(pConf)
      {
            pConf->SetPath ( _T( "/Settings/raymarine_autopilot_pi" ) );
			pConf->Read ( _T( "ShowautopilotIcon" ), &m_bautopilotShowIcon, 1 );
			pConf->Read(_T("Showautopilot"), &m_bShowautopilot, 1 );
            m_route_dialog_x =  pConf->Read ( _T ( "DialogPosX" ), 20L );
            m_route_dialog_y =  pConf->Read ( _T ( "DialogPosY" ), 20L );

            AutoPilotType = pConf->Read(_T("AutoPilotType"), AutoPilotType);
			ShowParameters = (bool) pConf->Read(_T("ShowParameters"), ShowParameters);
			NewAutoWindCommand = (bool) pConf->Read(_T("NewAutoWindCommand"), NewAutoWindCommand);
			NewAutoOnStandby = (bool) pConf->Read(_T("NewAutoOnStandby"), NewAutoOnStandby);
			SendTrack = (bool)pConf->Read(_T("SendTrack"), SendTrack);
			TimeToSendNewWaypiont= pConf->Read(_T("TimeToSendNewWaypiont"), TimeToSendNewWaypiont);
			STALKSendName = pConf->Read(_T("STALKSendName"), STALKSendName);
			STALKReceiveName = pConf->Read(_T("STALKReceiveName"), STALKReceiveName);
			NewStandbyNoStandbyReceived = (bool) pConf->Read(_T("NewStandbyNoStandbyReceived"), NewStandbyNoStandbyReceived);
			ChangeValueToLast = (bool)pConf->Read(_T("ChangeValueToLast"), ChangeValueToLast);
			// will be set to 0 when plugin starts
			// NoStandbyCounter = pConf->Read(_T("NoStandbyCounter"), NoStandbyCounter);
			SelectCounterStandby = pConf->Read(_T("SelectCounterStandby"), SelectCounterStandby);
            Skalefaktor = ((double)pConf->Read(_T("Skalefaktor"), Skalefaktor)) / 10;
			WriteMessages = (bool)pConf->Read(_T("WriteMessages"), WriteMessages);
			WriteDebug = (bool)pConf->Read(_T("WriteDebug"), WriteDebug);
			ModyfyRMC = (bool)pConf->Read(_T("ModyfyRMC"), ModyfyRMC);
            allowautocog = (bool)pConf->Read(_T("allowautocog"), allowautocog);
            cogsensibility = pConf->Read(_T("cogsensibility"), cogsensibility);
            maxdegreediff = pConf->Read(_T("maxdegreediff"), maxdegreediff);
            minspeedcog = ((double)pConf->Read(_T("minspeedcog"), minspeedcog)) / 10;
            maxchangehdg = pConf->Read(_T("maxchangehdg"), maxchangehdg);
            DialogStyle = pConf->Read(_T("Style"), DialogStyle);
            return true;
      }
      else
            return false;
}

bool raymarine_autopilot_pi::SaveConfig(void)
{
      wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

      if(pConf)
      {
            pConf->SetPath ( _T ( "/Settings/raymarine_autopilot_pi" ) );
			pConf->Write ( _T ( "ShowautopilotIcon" ), m_bautopilotShowIcon );
			pConf->Write(_T("Showautopilot"), m_bShowautopilot);
            pConf->Write ( _T ( "DialogPosX" ),   m_route_dialog_x );
            pConf->Write ( _T ( "DialogPosY" ),   m_route_dialog_y );
            pConf->Write(_T("AutoPilotType"), AutoPilotType);
			pConf->Write(_T("ShowParameters"), ShowParameters);
			pConf->Write(_T("NewAutoWindCommand"), NewAutoWindCommand);
			pConf->Write(_T("NewAutoOnStandby"), NewAutoOnStandby);
			pConf->Write(_T("SendTrack"), SendTrack);
			pConf->Write(_T("TimeToSendNewWaypiont"), TimeToSendNewWaypiont);
			pConf->Write(_T("STALKSendName"), STALKSendName);
			pConf->Write(_T("STALKReceiveName"), STALKReceiveName);
			pConf->Write(_T("NewStandbyNoStandbyReceived"), NewStandbyNoStandbyReceived);
			pConf->Write(_T("ChangeValueToLast"), ChangeValueToLast);
			// will be set to 0 when plugin starts
			//pConf->Write(_T("NoStandbyCounter"), NoStandbyCounter);
			pConf->Write(_T("SelectCounterStandby"), SelectCounterStandby);
            pConf->Write(_T("Skalefaktor"), (int)(Skalefaktor * 10));
			pConf->Write(_T("WriteMessages"), WriteMessages);
			pConf->Write(_T("WriteDebug"), WriteDebug);
			pConf->Write(_T("ModyfyRMC"), ModyfyRMC);
            pConf->Write(_T("allowautocog"), allowautocog);
            pConf->Write(_T("cogsensibility"), cogsensibility);
            pConf->Write(_T("maxdegreediff"), maxdegreediff);
            pConf->Write(_T("minspeedcog"), (int)(minspeedcog * 10));
            pConf->Write(_T("maxchangehdg"), maxchangehdg);
            pConf->Write(_T("Style"), DialogStyle);
            return true;
      }
      else
            return false;
}

void raymarine_autopilot_pi::ShowPreferencesDialog(wxWindow* parent)
{
    int x, y;
	ParameterDialog *dialog = new ParameterDialog(this, parent, wxID_ANY, _("Autopilot Preferences"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE);

	dialog->Fit();
    dialog->GetPosition(&x, &y);
    if (y >= 200)
        dialog->Move(wxPoint(x, y-200));
	DimeWindow(dialog);
    dialog->m_AutopilotType->SetSelection(AutoPilotType);
    if (AutoPilotType != SMARTPILOT)
    {        
        dialog->m_checkParameters->Enable(false);
        dialog->m_SendNewAutoonStandby->SetLabel(_("Send PGN 126720 (keystroke) instead of PGN 126208 (set heading) in AutoMode"));
        dialog->m_ChangeValueToLast->Enable(false);
        dialog->m_SendTrack->Enable(false);
        dialog->m_TimeToSendNewWaypiont->Enable(false);
        dialog->m_NewStandbyNoStandbyReceived->Enable(false);
        dialog->m_NoStandbyCounter->Enable(false);
        dialog->m_NoStandbyCounterValueText->Enable(false);
        dialog->m_SelectCounterStandby->Enable(false);
        dialog->m_ResetStandbyCounter->Enable(false);
        dialog->m_SelectCounterStandby->Enable(false);
        dialog->m_Text->Enable(false);
        dialog->m_STALKreceivename->Enable(false);
        dialog->m_staticText11->Enable(false);
        dialog->m_STALKsendname->Enable(false);
        dialog->m_staticText21->Enable(false);
        dialog->m_Text1->Enable(false);
        dialog->m_NoStandbyCounterValueText1->Enable(false);
        dialog->m_ModyfyRMC->SetLabel(_("Send variation PGN 127258 to N2K/SeatalkNG with the value from WMM Plugin"));
    }
    else
    {
        dialog->m_ModyfyRMC->SetLabel(_("Modify RMC Sentence as \"$ECRMC\" and replace or fill with Variationfield with the value from WMM Plugin"));
        dialog->m_SendNewAutoonStandby->SetLabel(_("Send new \"Auto\" or \"Auto - Wind\" Command, when \"Standby\" is not send from here, but the \"Auto\" was from here"));
    }
	dialog->m_checkParameters->SetValue(ShowParameters);
	dialog->m_SendNewAutoWind->SetValue(NewAutoWindCommand);
	dialog->m_SendNewAutoonStandby->SetValue(NewAutoOnStandby);
	dialog->m_ChangeValueToLast->SetValue(ChangeValueToLast);
	dialog->m_SendTrack->SetValue(SendTrack);
	dialog->m_TimeToSendNewWaypiont->SetValue(wxString::Format(wxT("%i"), TimeToSendNewWaypiont));
	dialog->m_WriteMessages->SetValue(WriteMessages);
	dialog->m_WriteDebug->SetValue(WriteDebug);
	dialog->m_ModyfyRMC->SetValue(ModyfyRMC);
	dialog->m_STALKsendname->SetValue(STALKSendName);
	dialog->m_STALKreceivename->SetValue(STALKReceiveName);
    dialog->m_Skalefaktor->SetValue(round((Skalefaktor - 1) * 10));
	if (NewAutoOnStandby == TRUE)
	{
		dialog->m_NewStandbyNoStandbyReceived->Enable(false);
		dialog->m_NoStandbyCounter->Enable(false);
		dialog->m_NoStandbyCounterValueText->Enable(false);
		dialog->m_SelectCounterStandby->Enable(false);
		dialog->m_ResetStandbyCounter->Enable(false);
		dialog->m_SelectCounterStandby->Enable(false);
		dialog->m_Text->Enable(false);
		NewStandbyNoStandbyReceived = FALSE;
	}
	dialog->m_NewStandbyNoStandbyReceived->SetValue(NewStandbyNoStandbyReceived);
	dialog->m_NoStandbyCounter->SetValue(wxString::Format(wxT("%i"), NoStandbyCounter));
	dialog->m_SelectCounterStandby->SetSelection(SelectCounterStandby);
    // Paramters Auto-COG
    dialog->m_allowautocog->SetValue(allowautocog);
    dialog->m_cogsensibility->SetValue(cogsensibility);
    dialog->m_maxdegreediff->SetValue(wxString::Format(wxT("%i"), maxdegreediff));
    dialog->m_minspeedcog->SetValue(wxString::Format(wxT("%.1f"), minspeedcog));
    dialog->m_maxchangehdg->SetValue(wxString::Format(wxT("%i"), maxchangehdg));
    if (allowautocog == false)
    {
        dialog->m_sensebilitytext->Enable(false);
        dialog->m_cogsensibility->Enable(false);
        dialog->m_slowtext->Enable(false);
        dialog->m_fast->Enable(false);
        dialog->m_maxdegreediff->Enable(false);
        dialog->m_maxdegtext->Enable(false);
        dialog->m_minspeedcog->Enable(false);
        dialog->m_minspeed->Enable(false);
        dialog->m_maxchangehdg->Enable(false);
        dialog->m_maxchangehdgtext->Enable(false);
    }
	if (dialog->ShowModal() == wxID_OK)
	{
        int OldAutoPilotType = AutoPilotType;
        AutoPilotType = dialog->m_AutopilotType->GetSelection();
        if (OldAutoPilotType != AutoPilotType)
        {
            if (AutoPilotType == EVO)
                EnableEVOEvents();            
            else
                DisableEVOEvents();
        }
        ShowParameters = dialog->m_checkParameters->GetValue();        
		NewAutoWindCommand = dialog->m_SendNewAutoWind->GetValue();
		NewAutoOnStandby = dialog->m_SendNewAutoonStandby->GetValue();
		ChangeValueToLast = dialog->m_ChangeValueToLast->GetValue();
		SendTrack = dialog->m_SendTrack->GetValue();
		TimeToSendNewWaypiont = atoi(dialog->m_TimeToSendNewWaypiont->GetValue());
		WriteMessages = dialog->m_WriteMessages->GetValue();
		WriteDebug = dialog->m_WriteDebug->GetValue();
		ModyfyRMC = dialog->m_ModyfyRMC->GetValue();
		STALKSendName = dialog->m_STALKsendname->GetValue();
		STALKReceiveName = dialog->m_STALKreceivename->GetValue();
		NewStandbyNoStandbyReceived = dialog->m_NewStandbyNoStandbyReceived->GetValue();
		NoStandbyCounter = atoi(dialog->m_NoStandbyCounter->GetValue());
		SelectCounterStandby = dialog->m_SelectCounterStandby->GetSelection();
        Skalefaktor = 1 + (double)((double)dialog->m_Skalefaktor->GetValue() / 10);
        if (AutoPilotType != SMARTPILOT)
        {
            ShowParameters = false;
            SendTrack = false;
            NewStandbyNoStandbyReceived = FALSE;
        }
        // Paramters Auto-COG
        allowautocog = dialog->m_allowautocog->GetValue();
        cogsensibility = dialog->m_cogsensibility->GetValue();
        maxdegreediff = atoi(dialog->m_maxdegreediff->GetValue());
        minspeedcog = atof(dialog->m_minspeedcog->GetValue());
        maxchangehdg = atoi(dialog->m_maxchangehdg->GetValue());
        ResetAUTOCOGValues();
		if (NULL != m_pDialog)
		{
			wxPoint p = m_pDialog->GetPosition();
			SetCalculatorDialogX(p.x);
			SetCalculatorDialogY(p.y);
			m_pDialog->Close();
            delete m_pDialog;
			m_pDialog = new Dlg(m_parent_window,Skalefaktor, DialogStyle);
			m_pDialog->plugin = this;
			m_pDialog->Move(wxPoint(m_route_dialog_x, m_route_dialog_y));
            if (Autopilot_Status == AUTO && allowautocog == true && AutoCOGStatus == false)
            {
                m_pDialog->buttonAuto->SetLabel("AutoCOG");
                m_pDialog->buttonAuto->SetBackgroundColour(wxColour(148, 88, 167));
            }
			if (m_bShowautopilot)
				m_pDialog->Show();
			SetAutopilotparametersChangeable();
		}
		SaveConfig();
	}

	delete dialog;
}

void raymarine_autopilot_pi::SetAutopilotparametersChangeable()
{
	// Parameterbar visible or not
    int xSize;
    int ySize;

	if (ShowParameters)
	{
		// Visible
        ySize = 220;
        xSize = 158;
        if (!DialogStyle) // Without caption and docked
        {
            ySize -= 36;
            xSize -= 13;
            m_pDialog->SetBackgroundColour(wxColour(224, 224, 224));
        }
        else
            m_pDialog->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
		m_pDialog->ParameterChoise->Show();
		m_pDialog->ParameterValue->Show();
		m_pDialog->buttonSet->Show();
		m_pDialog->StaticLine3->Show();
		m_pDialog->SetMaxSize(Skalefaktor * m_pDialog->FromDIP(wxSize(xSize, ySize)));
		m_pDialog->SetSize(Skalefaktor * m_pDialog->FromDIP(wxSize(xSize, ySize)));
		m_pDialog->SetMinSize(Skalefaktor * m_pDialog->FromDIP(wxSize(xSize, ySize)));
	}
	else
	{
        ySize = 194;
        xSize = 155;
        if (!DialogStyle) // Without caption and docked
        {
            ySize -= 36;
            xSize -= 13;
            m_pDialog->SetBackgroundColour(wxColour(224, 224, 224));
        }
        else
            m_pDialog->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
		m_pDialog->ParameterChoise->Show(FALSE);
		m_pDialog->ParameterValue->Show(FALSE);
		m_pDialog->buttonSet->Show(FALSE);
		m_pDialog->StaticLine3->Show(FALSE);
		m_pDialog->SetSize(Skalefaktor * m_pDialog->FromDIP(wxSize(xSize, ySize)));
		m_pDialog->SetMinSize(Skalefaktor * m_pDialog->FromDIP(wxSize(xSize, ySize)));
		m_pDialog->SetMaxSize(Skalefaktor * m_pDialog->FromDIP(wxSize(xSize, ySize)));
	}

}

void raymarine_autopilot_pi::OnautopilotDialogClose()
{
    //m_bShowautopilot = false;
    SetToolbarItemState( m_leftclick_tool_id, m_bShowautopilot );
    m_pDialog->Hide();
	SaveConfig();
    RequestRefresh(m_parent_window); // refresh main window
}

//Demo implementation of response mechanism

void raymarine_autopilot_pi::SetPluginMessage(wxString &message_id, wxString &message_body)
{
    if ((WMM_receive_count < 30 && BoatVariation != 0x01FF && AutoPilotType == SMARTPILOT) || !ModyfyRMC)  // Do not need so often.
        return;
	if (message_id == _T("WMM_VARIATION_BOAT"))
	{
		wxJSONReader r;
		wxJSONValue v;
		r.Parse(message_body, &v);
		BoatVariation = v[_T("Decl")].AsDouble();
        WMM_receive_count = 0;
        if (AutoPilotType != SMARTPILOT)
            SendBoatVariationToN2k();
	}	
}

void raymarine_autopilot_pi::SetNMEASentence(wxString& sentence_incomming)
{
    // SS & 0x80 : Displays "Auto Rel" on 600R  this is Next Waypoint ist Bearing !!!
    // 
    wxString sentence = sentence_incomming;

    sentence.Trim(); // entferne Spaces
    if (m_pDialog == NULL)
        return;
    if (sentence.Mid(3, 3) == "RMB")
    {
        GetWaypointBearing(sentence);
        return;
    }
    if (sentence.Mid(3, 3) == "RMC")
    {
        if (sentence_incomming.GetChar(1) == 'E' && sentence_incomming.GetChar(2) == 'C')
            return; // is My sentence
        if (allowautocog)
        {
            ActualisateCOGSOG(sentence);
        }
        if (ModyfyRMC)
        {
            if (BoatVariation != 0x01FF) // Variation is valid from WMM
            {
                WMM_receive_count++;
                if (WMM_receive_count > 60) // 60 RMC Information
                    BoatVariation = 0x01FF; // set Variation to not avalibal
            }
            AddVariationToRMCanSendOut(sentence);
            return;
        }
    }
    if (AutoPilotType == EVOSEASMART)
    {
        if (sentence.Mid(1, 5) == "PCDIN")
        {
            CheckSeasartSentence(sentence);
        }
        return;
    }
    if (AutoPilotType != SMARTPILOT)
        return;
    wxString Lsentence = "$" + STALKReceiveName + ",84",
        Lsentence_Command = "$" + STALKReceiveName + ",86",
        Lsentence_Response = "$" + STALKReceiveName + ",87",
        Lsentence_Rudder = "$" + STALKReceiveName + ",91";

    if (STALKSendName != STALKReceiveName)
        MyLastSend = Nothing;
    if (sentence.Left(9) == Lsentence_Response)
    {
        if (WriteDebug) wxLogInfo(("Response %s"), sentence);
        // Response Ermittlung.
        m_pDialog->SetCopmpassTextColor(wxColour(0, 0, 64));
        m_pDialog->SetTextStatusColor(wxColour(0, 0, 128));
        m_pDialog->SetStatusText("Response");
        m_pDialog->SetCompassText(sentence.Mid(13, 2));
        ResponseLevel = atoi(sentence.Mid(13, 2));
        m_pDialog->ParameterChoise->SetSelection(1);
        m_pDialog->ParameterValue->SetSelection(ResponseLevel);
        if (WriteMessages) wxLogMessage(("Get Responce"));
        return;
    }
    if (sentence.Left(9) == Lsentence_Rudder)
    {
        if (WriteDebug) wxLogInfo(("Rudder %s"), sentence);
        // Rudder Ermittlung. 
        m_pDialog->SetCopmpassTextColor(wxColour(0, 0, 64));
        m_pDialog->SetTextStatusColor(wxColour(0, 0, 128));
        m_pDialog->SetStatusText("Rudder");
        m_pDialog->SetCompassText(sentence.Mid(13, 2));
        RudderLevel = atoi(sentence.Mid(13, 2));
        m_pDialog->ParameterChoise->SetSelection(3);
        m_pDialog->ParameterValue->SetSelection(RudderLevel);
        if (WriteMessages) wxLogMessage((" Get Rudder Gain"));
        return;
    }
    if (sentence.Left(9) == Lsentence_Command)
    {
        if (WriteDebug) wxLogInfo(("Keystroke %s"), sentence);
        // Commandos von anderem St6002 erkennen
        if (sentence.Mid(11, 7) == "1,02,FD" ||   // Standby pressed
            sentence.Mid(11, 7) == "1,42,BD")    // Standby pressed longer ab Version 0.4
        {
            if (MyLastSend != STANDBY)
            {
                Standbycommandreceived = TRUE;
                if (WriteMessages) wxLogMessage(("Received Standby Pressed from ST6001 %s"), sentence);
                NeedCompassCorrection = false;
            }
            else
            {
                // My Own mirred Sentence
                NeedCompassCorrection = false;
            }
            MyLastSend = Nothing;
            return;
        }
        if (Autopilot_Status == AUTO && allowautocog)
        {
            if (sentence.Mid(11, 7) == "1,01,FE" && MyLastSend != AUTO) // Auto
            {
                ActivateAutoCOG();
                if (WriteMessages) wxLogMessage(("Received Auto pressed in Auto Mode from ST6001 %s"), sentence);
                MyLastSend = Nothing;
                return;
            }
        }
        if (AutoCOGStatus == false)
        {
            MyLastSend = Nothing;
            return;
        }
        if (sentence.Mid(11, 7) == "1,07,F8" && MyLastSend != IncrementOne) // +1
        {
            COGCourse++;
            AutoCOGHeadingChange = 0;
            if (WriteMessages) wxLogMessage(("Received +1 pressed in AutoCOG Mode from ST6001 %s"), sentence);
        }
        if (sentence.Mid(11, 7) == "1,08,F7" && MyLastSend != IncrementTen) // +10
        {
            COGCourse += 10;
            AutoCOGHeadingChange = 0;
            if (WriteMessages) wxLogMessage(("Received +10 pressed in AutoCOG Mode from ST6001 %s"), sentence);
        }
        if (sentence.Mid(11, 7) == "1,05,FA" && MyLastSend != DecrementOne) // -1
        {
            COGCourse--;
            AutoCOGHeadingChange = 0;
            if (WriteMessages) wxLogMessage(("Received -1 pressed in AutoCOG Mode from ST6001 %s"), sentence);
        }
        if (sentence.Mid(11, 7) == "1,06,F9" && MyLastSend != DecrementTen) // -10
        {
            COGCourse -= 10;
            AutoCOGHeadingChange = 0;
            if (WriteMessages) wxLogMessage(("Received -10 pressed in AutoCOG Mode from ST6001 %s"), sentence);
        }
        if (COGCourse < 0) COGCourse += 360;
        if (COGCourse >= 360) COGCourse -= 360;
        MyLastSend = Nothing;
        return;
    }
    if (sentence.Left(9) != Lsentence) // Comes in 1 Second delay
        return;
    MyLastSend = Nothing;
    if (CounterStandbySentencesReceived == 0) // falls noch kein Kommando gekommen ist, bleibt der alte Status.
        Autopilot_Status_Before = Autopilot_Status;
    ToUpdateAutoPilotControlDisplay(sentence);
}

void raymarine_autopilot_pi::ToUpdateAutoPilotControlDisplay(wxString sentence)
{
    int tmp;

	if (NULL != p_Resettimer)
	{
		p_Resettimer->Stop();
		p_Resettimer->Start(12000);
	}
	if (DisplayShow > 0)
	{
		DisplayShow--;
		//return;
	}	
	m_pDialog->SetCopmpassTextColor(wxColour(0, 0, 64));
	m_pDialog->SetTextStatusColor(wxColour(0, 0, 128));
	Autopilot_Status = GetAutopilotMode(sentence);
	switch (Autopilot_Status)
	{
		case	AUTO:
			if (WriteDebug) wxLogInfo(("Received Auto %s"), sentence);
			if (Autopilot_Status_Before != Autopilot_Status)
			{
				// Nur f?r Logging
				if (WriteMessages) wxLogMessage("Auto-Status changed to AUTO");
                if (allowautocog)
                {
                    m_pDialog->buttonAuto->SetLabel("AutoCOG");
                    m_pDialog->buttonAuto->SetFont(wxFont(Skalefaktor * 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
                    m_pDialog->buttonAuto->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
                    m_pDialog->buttonAuto->SetBackgroundColour(wxColour(148, 88, 167));
                    if (WriteMessages) wxLogMessage("Auto-Status changed to AUTOCOG");
                }
			}
			if (StandbySelfPressed == TRUE)
			{
				if (WriteMessages) wxLogMessage(("Standby self Pressed detected in Auto Mode %s"), sentence);
				NeedCompassCorrection = false;
				// Soll nach Standby gehen ist aber noch in Auto mode.
				DisplayShow = 2; // 2 Sequenzen abwarten
				if (IS_standby < 2)
				{
					IS_standby++;
					break;
				}
			} else
			if (Standbycommandreceived == TRUE && Autopilot_Status_Before != UNKNOWN)
			{
				// Warten ob Der Autopilot noch in Standbymode geht, falls Dieses "Auto" Signal kurz hinter dem
				// Dr?cken der Standbytaste noch kam, und dadurch den "Standbycommandreceived Status wieder nach
				// FALSE setzt.
				// Zwei Sequenzen abwarten.
				if (WriteMessages) wxLogMessage(("Standby from St6001 detected in Auto Mode %s"), sentence);
				NeedCompassCorrection = false;
				if (IS_standby < 2)
				{
					IS_standby++;
					break;
				}
			}
			if (NeedCompassCorrection == true)
			{
				// Es wurde Automodus durch fehler aktivert, und es muss der Curse auf den alen gesetzt werden.
				// Sende so lange Signale, bis der alte Compasskurs wider eingestellt ist.
				if (LastCompassCourse < 0 || LastCompassCourse > 360)
				{
					// Noch nicht gesetzt
					if (WriteMessages) wxLogMessage("No Last Compass Course");
					NeedCompassCorrection = false;
					break;
				}
				if (atoi(GetAutopilotCompassCourse(sentence)) == LastCompassCourse)
				{
					// Der alte Kurs ist eingestellt.
					if (WriteMessages) wxLogMessage("Correct Compass ready");
					NeedCompassCorrection = false;
				}
				else
				{
					// Korrectur durchf?hren
					// -------------------------------
					tmp = atoi(GetAutopilotCompassCourse(sentence));
					if (tmp < 0 || tmp > 360)
					{
						//Fehler
						if (WriteMessages) wxLogMessage("Compass Error");
						NeedCompassCorrection = false;
						break;
					}
					if (180 > abs(tmp - LastCompassCourse) &&  30 < abs(tmp - LastCompassCourse))
					{
						// Nicht mehr als 30 Grad ?nderung !!
						if (WriteMessages) wxLogMessage("No Correction more than 30 degree");
						NeedCompassCorrection = false;
						break;
					}
					if (WriteMessages) wxLogMessage(("Correct Compass course from %i to %i"),tmp, LastCompassCourse);
					if (180 < abs(tmp - LastCompassCourse))
					{
						// ?ber Nodern ?ndern
						if (tmp > LastCompassCourse)
						{
							// Compasskurs muss ?ber Norden mit PLus ver?ndert werden. (bis 0 Grad.)
							if ((tmp - LastCompassCourse) >= 10)
							{
								// Mehr als 10 Grad differenz !! also +10 Grad ?ndern.
								if (WriteMessages) wxLogMessage("Over North + 10");
                                SendIncrementTen();
							}
							else
							{
								// Weniger als 10 Grad ?ndern.
								if (WriteMessages) wxLogMessage("Over North + 1");
                                SendIncrementOne();
							}
						}
						else
						{
							// Compasskurs von z.B. 5 nach 340 ... ?ndern mit Minus
							if ((LastCompassCourse - tmp) >= 10)
							{
								// Mehr als 10 Grad differenz !! also +10 Grad ?ndern.
								if (WriteMessages) wxLogMessage("Over North - 10");
                                SendDecrementTen();
							}
							else
							{
								// Weniger als 10 Grad ?ndern.
								if (WriteMessages) wxLogMessage("Over North - 1");
                                SendDecrementOne();
							}
						}
					}
					else
					{
						// Normale ?nderung nicht ?ber Norden.
						if (tmp > LastCompassCourse)
						{
							// Der Neue Compasskurs ist gr?sser als der alte also Verkleineren.
							if ((tmp - LastCompassCourse) >= 10)
							{
								// Mehr als 10 Grad differenz !! also +10 Grad ?ndern.
								if (WriteMessages) wxLogMessage("Korrectur - 10");
                                SendDecrementTen();
							}
							else
							{
								// Weniger als 10 Grad ?ndern.
								if (WriteMessages) wxLogMessage("Korrectur - 1");
                                SendDecrementOne();
							}
						}
						else
						{
							// Der neue Compass kurs ist kleiner als der alte. also Vergr?ssern.
							if ((LastCompassCourse - tmp) >= 10)
							{
								// Mehr als 10 Grad differenz !! also +10 Grad ?ndern.
								if (WriteMessages) wxLogMessage("Korrectur + 10");
                                SendIncrementTen();
							}
							else
							{
								// Weniger als 10 Grad ?ndern.
								if (WriteMessages) wxLogMessage("Korrectur + 1");
                                SendIncrementOne();
							}
						}
					}
				}
				if (m_pDialog != NULL && DisplayShow == 0)
				{
					m_pDialog->SetStatusText("Auto Correct");
					m_pDialog->SetCompassText(GetAutopilotCompassCourse(sentence) + " ( " + GetAutopilotCompassDifferenz(sentence) + " )");
				}
			}
			else
			{
				LastCompassCourse = atoi(GetAutopilotCompassCourse(sentence));
				if (m_pDialog != NULL && DisplayShow == 0)
				{
					if (ConfirmNextWaypoint(sentence) == false) // Check if Print "NextWaypoint + Bearing"
					{
                        if (AutoCOGStatus == true)
                        {
                            GetAutopilotMAGCourse(sentence); // Only to fill MAGCOG.
                            WriteCOGStatus();
                        }
                        else
                        {
                            m_pDialog->SetStatusText("Auto");
                            m_pDialog->SetCompassText(GetAutopilotCompassCourse(sentence) + " ( " + GetAutopilotCompassDifferenz(sentence) + " )");
                        }
					}
				}
			}            
			if (IS_standby != 0)
				if (WriteMessages) wxLogMessage(("No Standby Message comming don't know why. Say in Auto Mode. Sentence %s"), sentence);
			IS_standby = 0;
			Standbycommandreceived = FALSE;
			StandbySelfPressed = FALSE;
			CounterStandbySentencesReceived = 0;
			break;
		case AUTOTRACK :
			if (WriteDebug) wxLogInfo(("Received Auto-Track %s"), sentence);
			if (Autopilot_Status_Before != Autopilot_Status)
			{
				// Nur für Logging
				if (WriteMessages) wxLogMessage("Auto-Status changed to AUTO-TRACK");
                if (allowautocog)
                {
                    m_pDialog->buttonAuto->SetLabel("Auto");
                    m_pDialog->buttonAuto->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
                    m_pDialog->buttonAuto->SetBackgroundColour(wxColour(255, 0, 0));
                    DeActivateAutoCOG();
                }
			}
			if (StandbySelfPressed == TRUE)
			{
				if (WriteMessages) wxLogMessage(("Standby self Pressed detected in Auto-Track Mode %s"), sentence);
				// Soll nach Standby gehen ist aber noch in Auto mode.
				DisplayShow = 2; // 2 Sequenzen abwarten
				if (IS_standby < 2)
				{
					IS_standby++;
					break;
				}
			} else
			if (Standbycommandreceived == TRUE && Autopilot_Status_Before != UNKNOWN)
			{
				// Warten ob Der Autopilot noch in Standbymode geht, falls Dieses "Auto" Signal kurz hinter dem
				// Dr?cken der Standbytaste noch kam, und dadurch den "Standbycommandreceived Status wieder nach
				// FALSE setzt.
				// Zwei Sequenzen abwarten.
				if (WriteMessages) wxLogMessage(("Standby from St6001 detected in Auto-Track Mode %s"), sentence);
				if (IS_standby < 2)
				{
					IS_standby++;
					break;
				}
			}
			if (IS_standby != 0)
				if (WriteMessages) wxLogMessage(("No Standby Message comming don't know why. Say in Auto-Track Mode. Sentence %s"), sentence);
			IS_standby = 0;
			Standbycommandreceived = FALSE;
			StandbySelfPressed = FALSE;
			CounterStandbySentencesReceived = 0;
			if (m_pDialog != NULL && DisplayShow == 0)
			{
				if (ConfirmNextWaypoint(sentence) == false) // Check if Print "NextWaypoint + Bearing"
				{
					m_pDialog->SetStatusText("Auto-Track");
					m_pDialog->SetCompassText(GetAutopilotCompassCourse(sentence) + " ( " + GetAutopilotCompassDifferenz(sentence) + " )");
				}
			}
			break;
		case	AUTOWIND:
			if (WriteDebug) wxLogInfo(("Received Auto-Wind %s"), sentence);
			if (Autopilot_Status_Before != Autopilot_Status)
			{
				// Nur f?r Logging
				if (WriteMessages) wxLogMessage("Auto-Status changed to AUTO-WIND");
                if (allowautocog)
                {
                    m_pDialog->buttonAuto->SetLabel("Auto");
                    m_pDialog->buttonAuto->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
                    m_pDialog->buttonAuto->SetBackgroundColour(wxColour(255, 0, 0));
                    DeActivateAutoCOG();
                }
			}
			if (StandbySelfPressed == TRUE)
			{
				if (WriteMessages) wxLogMessage(("Standby self Pressed detected in Auto-Wind Mode %s"), sentence);
				// Soll nach Standby gehen ist aber noch in Auto mode.
				DisplayShow = 2; // 2 Sequenzen abwarten
				if (IS_standby < 2)
				{
					IS_standby++;
					break;
				}
			} else
			if (Standbycommandreceived == TRUE && Autopilot_Status_Before != UNKNOWN)
			{
				// Warten ob Der Autopilot noch in Standbymode geht, falls Dieses "Auto" Signal kurz hinter dem
				// Dr?cken der Standbytaste noch kam, und dadurch den "Standbycommandreceived Status wieder nach
				// FALSE setzt.
				// Zwei Sequenzen abwarten.
				if (WriteMessages) wxLogMessage(("Standby from St6001 detected in Auto-Wind Mode %s"), sentence);
				if (IS_standby < 2)
				{
					IS_standby++;
					break;
				}
			}
			if (IS_standby != 0)
				if (WriteMessages) wxLogMessage(("No Standby Message comming don't know why. Say in Auto-Wind Mode. Sentence %s"), sentence);
			IS_standby = 0;
			Standbycommandreceived = FALSE;
			StandbySelfPressed = FALSE;
			CounterStandbySentencesReceived = 0;
			if (m_pDialog != NULL && DisplayShow == 0)
			{
				m_pDialog->SetStatusText("Auto-Wind");
				m_pDialog->SetCompassText(GetAutopilotCompassCourse(sentence) + " ( " + GetAutopilotCompassDifferenz(sentence) + " )");
			}
			break;
		case	WINDSHIFT:
			if (WriteDebug) wxLogInfo(("Received Windshift %s"), sentence);
			if (Autopilot_Status_Before != Autopilot_Status)
			{
				// Nur f?r Logging
				if (WriteMessages) wxLogMessage("Auto-Status .... Windshift received");
                if (allowautocog)
                {
                    m_pDialog->buttonAuto->SetLabel("Auto");
                    m_pDialog->buttonAuto->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
                    m_pDialog->buttonAuto->SetBackgroundColour(wxColour(255, 0, 0));
                    DeActivateAutoCOG();
                }
			}
			if (StandbySelfPressed == TRUE)
			{
				// Soll nach Standby gehen ist aber noch in Auto mode.
				DisplayShow = 2; // 2 Sequenzen abwarten
				if (IS_standby < 2)
				{
					IS_standby++;
					break;
				}
			}
			StandbySelfPressed = FALSE;
			if (NewAutoWindCommand)
			{
				// Send New Sentence Auto-Wind
				if (WriteMessages) wxLogMessage("Send New Auto-Wind Command");
                SendGotoAutoWind();
			}
			if (m_pDialog != NULL && DisplayShow == 0)
			{
				m_pDialog->SetStatusText("Wind-Shift");
				m_pDialog->SetCompassText(GetAutopilotCompassCourse(sentence) + " ( " + GetAutopilotCompassDifferenz(sentence) + " )");
				DisplayShow = 10;
			}
			break;
		case	OFFCOURSE:
			if (WriteDebug) wxLogInfo(("Received Off-Course %s"), sentence);
			if (Autopilot_Status_Before != Autopilot_Status)
			{
				// Nur f?r Logging
				if (WriteMessages) wxLogMessage("Auto-Status .... Off-Course received");
                if (allowautocog)
                {
                    m_pDialog->buttonAuto->SetLabel("Auto");
                    m_pDialog->buttonAuto->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
                    m_pDialog->buttonAuto->SetBackgroundColour(wxColour(255, 0, 0));
                    DeActivateAutoCOG();
                }
			}
			if (StandbySelfPressed == TRUE)
			{
				// Soll nach Standby gehen ist aber noch in Auto mode.
				DisplayShow = 2; // 2 Sequenzen abwarten
				if (IS_standby < 2)
				{
					IS_standby++;
					break;
				}
			}
			StandbySelfPressed = FALSE;
			if (m_pDialog != NULL && DisplayShow == 0)
			{
				m_pDialog->SetStatusText("Off-Course");
				m_pDialog->SetCompassText(GetAutopilotCompassCourse(sentence) + " ( " + GetAutopilotCompassDifferenz(sentence) + " )");
				DisplayShow = 10;
			}
			break;
		case	STANDBY :
			if (WriteDebug) wxLogInfo(("Received Standby %s"), sentence);
			if (Autopilot_Status_Before != Autopilot_Status)
			{
				// Nur f?r Logging
				if (WriteMessages) wxLogMessage("Auto-Status changed to STANDBY");
                if (allowautocog)
                {
                    m_pDialog->buttonAuto->SetLabel("Auto");
                    m_pDialog->buttonAuto->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
                    m_pDialog->buttonAuto->SetBackgroundColour(wxColour(255, 0, 0));
                    DeActivateAutoCOG();
                }
			}
			if (Autopilot_Status_Before != STANDBY &&
				NewStandbyNoStandbyReceived == TRUE &&  // Sool ?berhaupt ein Neues Standby gesendent werden ?
				Standbycommandreceived == FALSE &&
				NoStandbyCounter <= SelectCounterStandby &&  // Es soll StandbyCommando ausgewertet werden. Maximale Anzahl.
				ConfirmNextWaypoint(sentence) == false) // Kein Fehler aufgetreten, sonst geht der Autopilot selber in Standby
				
			{
				if (WriteMessages) wxLogMessage(("Standby received without StandbyCommand before %s"), sentence);
				if (CounterStandbySentencesReceived < 3) // 4 Senteces warten, ob doch noch ein Commando kommt.
				{
					if (m_pDialog != NULL)
					{
						m_pDialog->SetStatusText("No Standby");
						m_pDialog->SetCompassText("Error");
					}
					CounterStandbySentencesReceived++;
					break;
				}
				else
				{
					// Kein Kommando gekommen sende nun Neues Auto Commando.
					IS_standby = 0;
					if (WriteMessages) wxLogMessage(("StandbyCommandreceived = False %s"), sentence);
					CounterStandbySentencesReceived = 0;
					Autopilot_Status = Autopilot_Status_Before; // Dadurch werden mehrere Seqnenzen gesendet, wenn n?tig.
					if (Autopilot_Status_Before == AUTO)
					{
						if (WriteMessages) wxLogMessage("---------------Send New Auto------------");
                        SendGotoAuto();
						if (ChangeValueToLast == true)
						{
							// Kurskorrectur durchf?hren
							if (WriteMessages) wxLogMessage("Course correction is enabled");
							NeedCompassCorrection = true;
						}
						else
						{
							if (WriteMessages) wxLogMessage("Course correction is disabled using aktuell Compass-course");
						}
					}
					if (Autopilot_Status_Before == AUTOWIND)
					{
						if (WriteMessages) wxLogMessage("-------------Send New Auto-Wind---------");
                        SendGotoAutoWind();
					}
					if (Autopilot_Status_Before == AUTOTRACK)
					{
						if (WriteMessages) wxLogMessage("-------------Send New Auto-Track--------");
                        SendGotoAutoTrack();
					}
					// FehlerCounter hohchz?hlen.
					NoStandbyCounter++;
					if (NoStandbyCounter > SelectCounterStandby)
					{
						if (WriteMessages) wxLogMessage("-------Last Time Sending new One--------");
					}
					if (m_pDialog != NULL)
					{
						// Rot
						m_pDialog->SetBgTextStatusColor(wxColour(255, 128, 128));
						m_pDialog->SetBgTextCompassColor(wxColour(255, 128, 128));
					}
				}
				break;
			}
			else
			{
				if(CounterStandbySentencesReceived != 0)
					if (WriteMessages) wxLogMessage("Standby Push Signal received now.");
				CounterStandbySentencesReceived = 0;
				NeedCompassCorrection = false;
			}
			if (Autopilot_Status_Before == AUTO || Autopilot_Status_Before == AUTOWIND) // Zustand?nderung von Auto -> Standby
			{
				CounterStandbySentencesReceived = 0;
				if (StandbySelfPressed == FALSE &&
                    AutoPilotType == SMARTPILOT &&  // Nur bei Seatalk1 Autopilot
					NewAutoOnStandby == TRUE)  // Generell neues Auto Senden, wenn nicht von hier gesendet.
					                           // Ignoriert St6001 Standby Signal !! Vorsiht.
                                               // Wird auch genutzt f?r PGN EVO Set Pilot Heading oder Windmode Sendewahl.
				{
					// Standby not from here !! goto AUTO
					//
					if (WriteMessages) wxLogMessage(("Selfpressed = False, Auto-Status-before = Auto or Autowind %s"), sentence);
					if (WriteMessages) wxLogMessage("---------------Send New Auto------------");
					IS_standby = 0;
					Standbycommandreceived = FALSE;
					CounterStandbySentencesReceived = 0;
                    SendGotoAuto();
					MyLastSend = AUTO;
					if (ChangeValueToLast == true)
					{
						// Kurskorrectur durchf?hren
						if (WriteMessages) wxLogMessage("Course correction(2) is enabled");
						NeedCompassCorrection = true;
					}
					else
					{
						if (WriteMessages) wxLogMessage("Course correction(2) is disabled using aktuell Compass-course");
					}
				}
				StandbySelfPressed = FALSE;
			}
			if(Autopilot_Status_Before == STANDBY)
			{
				// War schon Standby nun Zur Sicherheit
				StandbySelfPressed = FALSE;
				Standbycommandreceived = FALSE;
				IS_standby = 0;
			}
			if (m_pDialog != NULL && DisplayShow == 0)
			{
				if (ConfirmNextWaypoint(sentence) == false) // Check if Print "NextWaypoint + Bearing"
				{
					m_pDialog->SetStatusText("Standby");
					m_pDialog->SetCompassText(GetAutopilotMAGCourse(sentence));
				}
			}
			break;
		case	UNKNOWN:
			if (WriteDebug) wxLogInfo(("Received Unknown %s"), sentence);
			if (m_pDialog != NULL && DisplayShow == 0)
			{
				m_pDialog->SetStatusText("----------");
				m_pDialog->SetCompassText("---");
			}
			IS_standby = 0;
			Standbycommandreceived = TRUE; // So when the Instruments are switched on again no Error !
			CounterStandbySentencesReceived = 0;
			NeedCompassCorrection = false;
            MAGcourse = -1;
            Received_65379 = false;
            GetHeadingFromSeatalkNG = false;
            EVOLockeHeading = N2kDoubleNA;
            Received_Heading_126208 = false;
            Received_AUTO_126208 = false;
            Received_LockedHeading_inStandby = false;
            AutoCOGHeadingChange = 0;
            LastCompassCourse = -1;
            if (allowautocog)
            {
                m_pDialog->buttonAuto->SetLabel("Auto");
                m_pDialog->buttonAuto->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
                m_pDialog->buttonAuto->SetBackgroundColour(wxColour(255, 0, 0));
                DeActivateAutoCOG();
            }
			break;
	}
}

bool raymarine_autopilot_pi::ConfirmNextWaypoint(const wxString &sentence)
{
	if (sentence.Mid(28, 2) == "02" || AutoPilotType != SMARTPILOT) // Don't know how to do with EVO
	{
		// Autopilot is in normal Mode
		GoneTimeToSendNewWaypoint = 0;
		return false;
	}

	char c,b;

	if (-1 == (c = GetHexValue((char)(sentence.Mid(28, 1)).GetChar(0))))
	{
		return false;
	}
	if (-1 == (b = GetHexValue((char)(sentence.Mid(20, 1)).GetChar(0))))
	{
		return false;
	}

	if ((c & 0x08) == 0x08 && (b & 0x02) == 0x02)  // Ist im AutoMode. und soll nach track
	{ 
		if (m_pDialog != NULL)
		{
			m_pDialog->SetStatusText("Next WayP.");
			m_pDialog->SetCompassText(WayPointBearing);
		}
		if (SendTrack)
		{
			// Send Track automatisch. after TimeToSendNewWaypiont
			if (TimeToSendNewWaypiont == GoneTimeToSendNewWaypoint)
			{
                SendGotoAutoTrack();
				if (WriteMessages) wxLogMessage("Send Track automatic ");
			}
			GoneTimeToSendNewWaypoint++;  // Not set to 0 here, because don't send too sentences after the other
		}		
		return true;
	}
	if ((c & 0x01) == 0x01)
	{   
		if (m_pDialog != NULL)
		{
			m_pDialog->SetStatusText("WayPoint");
			WayPointBearing = "large XTE";
			m_pDialog->SetCompassText(WayPointBearing);
		}
		return true;
	}
	if (-1 == (c = GetHexValue((char)(sentence.Mid(29, 1)).GetChar(0))))
	{
		return false;
	}
	if ((c & 0x08) == 0x08)
	{
		if (m_pDialog != NULL)
		{
			m_pDialog->SetStatusText("WayPoint");
			WayPointBearing = "No Data";
			m_pDialog->SetCompassText(WayPointBearing);
			StandbySelfPressed = TRUE; // Autopilot geht von selbst auf AUTO
		}
		return true;
	}
	GoneTimeToSendNewWaypoint = 0;
	return false; // Autopilot is in normal Mode
}

void raymarine_autopilot_pi::GetWaypointBearing(const wxString &sentence)
{
	// Get from RMB Message
	wxString s = sentence;
	int sLenght = s.Length();
	int i = 0;

	while (i < 11)
	{
		sLenght = sLenght - s.find(wxT(",")) - 1;
		if (sLenght <= 0)
		{
			WayPointBearing = "error";
			return;
		}
		s = s.Right(sLenght);
		i++;
		if (i == 11)
		{
			WayPointBearing = s.Left(s.find(wxT(",")));
			if (WayPointBearing.find(wxT(".")) != -1)
				WayPointBearing = WayPointBearing.Left(WayPointBearing.find(wxT(".")));
			WayPointBearing += " ?";
			return;
		}
	}
	WayPointBearing = "unknown";
	return;
}

int raymarine_autopilot_pi::GetAutopilotMode(wxString &sentence)
{
    if (AutoPilotType != SMARTPILOT)
        return Autopilot_Status;

	wxString s = sentence, HexValue;

	//s.Trim();
	char c;
	int sLenght = s.Length();
	int i = 0, ReturnStatus = UNKNOWN;
	
	while (i < 7)
	{
		sLenght = sLenght - s.find(wxT(",")  ) - 1;
		if (sLenght <= 0)
		{
			return UNKNOWN;
		}
		s = s.Right(sLenght);
		i++;
		if (i == 5)
		{
			HexValue = s.Left(s.find(wxT(",")));
			if (HexValue.Length() != 2)
			{
				ReturnStatus = UNKNOWN;
				break;
			}
			if (-1 == (c = GetHexValue((char)HexValue.GetChar(1))))
			{
				ReturnStatus = UNKNOWN;
				break;
			}
		/*	if ((c & 0x08) == 0x08)
				ReturnStatus = AUTOTRACK;
			if ((c & 0x06) == 0x06 && ReturnStatus == UNKNOWN)
				ReturnStatus = AUTOWIND;
			if ((c & 0x02) == 0x02 && ReturnStatus == UNKNOWN)
				ReturnStatus = AUTO;
			if ((c & 0x02) == 0x00 && ReturnStatus == UNKNOWN)
				ReturnStatus = STANDBY;  alte Version !! Fehler bei Standby und Autowind !   */
			if ((c & 0x02) == 0x00) // Wenn Bit 2 = 0 auf jeden Fall Standby.
				ReturnStatus = STANDBY;
			// Wenn Bit 2 gesetzt ist, ist auf jeden Fall ein Auto Mode.
			if ((c & 0x04) == 0x04 && ReturnStatus == UNKNOWN)
				ReturnStatus = AUTOWIND;
			if ((c & 0x08) == 0x08 && ReturnStatus == UNKNOWN)
				ReturnStatus = AUTOTRACK;
			if ((c & 0x02) == 0x02 && ReturnStatus == UNKNOWN)
				ReturnStatus = AUTO;
		}
		if (i == 6 && ReturnStatus == AUTOWIND)
		{
			HexValue = s.Left(s.find(wxT(",")));
			if (HexValue.Length() != 2)
				return UNKNOWN;
			if (-1 == (c = GetHexValue((char)HexValue.GetChar(1))))
				return UNKNOWN;
			if ((c & 0x08) == 0x08)
				return WINDSHIFT;
		}
		if (i == 6 && (ReturnStatus == AUTO || ReturnStatus == AUTOTRACK))
		{
			HexValue = s.Left(s.find(wxT(",")));
			if (HexValue.Length() != 2)
				return UNKNOWN;
			if (-1 == (c = GetHexValue((char)HexValue.GetChar(1))))
				return UNKNOWN;
			if ((c & 0x04) == 0x04)
				return OFFCOURSE;
		}
	}
	return ReturnStatus; 
}

char raymarine_autopilot_pi::GetHexValue(char AsChar)
{
	char HexT[] = "0123456789ABCDEF";
	char a = toupper(AsChar), i = 0;

	while(i <= 15)
	{
		if (HexT[i] == a)
			return i;
		i++;
	}
	return -1;
}

// This is the Set Value of Smartpilot
wxString raymarine_autopilot_pi::GetAutopilotCompassCourse(wxString &sentence)
{
    if (AutoPilotType != SMARTPILOT)
    {
        if (EVOLockeHeading != N2kDoubleNA)
        {
            return(wxString::Format(wxT("%i"), (int)EVOLockeHeading));
        }
        else
            return ("-");
    }
	wxString s = sentence, HexValue;

	s.Trim();
	unsigned char parameter[3] = { 0x00, 0x00, 0x00 };
	int sLenght = s.Length();
	int i = 0, CompassValue = -1;

	while (i < 5)
	{
		sLenght = sLenght - s.find(wxT(",")) - 1;
		if (sLenght <= 0)
		{
			return ("---");
		}
		s = s.Right(sLenght);
		HexValue = s.Left(s.find(wxT(",")));
		i++;        
		if (i == 3) // High Bit
		{
			if (HexValue.Length() != 2)
				return ("Err - 1");
			if (-1 == (parameter[0] = GetHexValue((char)HexValue.GetChar(0))))
				return ("Err - 2");
		}
		if (i == 4)
		{
			if (HexValue.Length() != 2)
				return ("Err - 3");
			if (-1 == (parameter[1] = GetHexValue((char)HexValue.GetChar(0))))
				return ("Err - 4");
			if (-1 == (parameter[2] = GetHexValue((char)HexValue.GetChar(1))))
				return ("Err - 5");
			parameter[1] = (parameter[1] << 4) | parameter[2];
		    if (360 <= (CompassValue = (int)((parameter[0] & 0x0c) >> 2) * 90 + parameter[1] / 2 + parameter[1] % 2)) // Very good checked with St6002
            {
                CompassValue = 0;
            }
			return(wxString::Format(wxT("%i"), CompassValue));
		}
	} 
	return ("---"); // Nicht def
}

// This ist the aktuelle MAG Compass Course of Boat
wxString raymarine_autopilot_pi::GetAutopilotMAGCourse(wxString &sentence)
{
    if (AutoPilotType != SMARTPILOT)
    {
        if (MAGcourse != -1)
        {
            return(wxString::Format(wxT("%i"), MAGcourse));
        }
        else
            return ("-"); // Nicht def
    }
	wxString s = sentence, HexValue;

	s.Trim();
	unsigned char parameter[3] = { 0x00, 0x00, 0x00 };
	int sLenght = s.Length();
	int i = 0, CompassValue = -1;

	while (i < 4)
	{
		sLenght = sLenght - s.find(wxT(",")) - 1;
		if (sLenght <= 0)
		{
			return ("---");
		}
		s = s.Right(sLenght);
		HexValue = s.Left(s.find(wxT(",")));
		i++;
		if (i == 2) // High Bit
		{
			if (HexValue.Length() != 2)
				return ("Err - 7");
			if (-1 == (parameter[0] = GetHexValue((char)HexValue.GetChar(0))))
				return ("Err - 8");
		}
		if (i == 3)
		{
			if (HexValue.Length() != 2)
				return ("Err - 9");
			if (-1 == (parameter[1] = GetHexValue((char)HexValue.GetChar(0))))
				return ("Err - 10");
			if (-1 == (parameter[2] = GetHexValue((char)HexValue.GetChar(1))))
				return ("Err - 11");
			parameter[1] = (parameter[1] << 4) | parameter[2];
            if (360 <= (CompassValue = (int)(((parameter[0] & 0x03) * 90)
                + ((parameter[1] & 0x3F) * 2)
                + (((parameter[0] >> 2) & 0x03) / 2) 
				+ ((parameter[0] >> 2) & 0x01))))
            {
                CompassValue = 0;
            }
            MAGcourse = CompassValue;
			return(wxString::Format(wxT("%i"), CompassValue));
		}
	}
    MAGcourse = -1;
	return ("---"); // Nicht def
}

wxString raymarine_autopilot_pi::GetAutopilotCompassDifferenz(wxString &sentence)
{

    int ReturnCompassValue;
    if (AutoPilotType != SMARTPILOT)
    {
        if (EVOLockeHeading != N2kDoubleNA && MAGcourse != -1)
        {
            ReturnCompassValue = (int)MAGcourse - (int)EVOLockeHeading;
            if (ReturnCompassValue >= 180)
                ReturnCompassValue -= 360;
            if (ReturnCompassValue < -180)
                ReturnCompassValue += 360;
            return(wxString::Format(wxT("%i"), ReturnCompassValue));
        }
        else
            return ("-"); // Nicht def
    }

	wxString s = sentence, HexValue;

	s.Trim();
	unsigned char parameter[3] = { 0x00, 0x00, 0x00 };
	int sLenght = s.Length();
	int i = 0, CompassValue = -1, AutoValue = -1;

	while (i < 5)
	{
		sLenght = sLenght - s.find(wxT(",")) - 1;
		if (sLenght <= 0)
		{
			return ("-");
		}
		s = s.Right(sLenght);
		HexValue = s.Left(s.find(wxT(",")));
		i++;
		if (i == 3) // High Bit
		{
			if (HexValue.Length() != 2)
				return ("a1");
			if (-1 == (parameter[0] = GetHexValue((char)HexValue.GetChar(0))))
				return ("a2");
		}
		if (i == 4)
		{
			if (HexValue.Length() != 2)
				return ("a3");
			if (-1 == (parameter[1] = GetHexValue((char)HexValue.GetChar(0))))
				return ("a4");
			if (-1 == (parameter[2] = GetHexValue((char)HexValue.GetChar(1))))
				return ("a5");
			parameter[1] = (parameter[1] << 4) | parameter[2];
			if (360 <= (CompassValue = (int)((parameter[0] & 0x0c) >> 2) * 90 + parameter[1] / 2 + parameter[1] % 2))
            {
                CompassValue = 0;
            }
		}
	}
	s = sentence;
	s.Trim();
	sLenght = s.Length();
	i = 0;
	while (i < 4)
	{
		sLenght = sLenght - s.find(wxT(",")) - 1;
		if (sLenght <= 0)
		{
			return ("-");
		}
		s = s.Right(sLenght);
		HexValue = s.Left(s.find(wxT(",")));
		i++;
		if (i == 2) // High Bit
		{
			if (HexValue.Length() != 2)
				return ("x7");
			if (-1 == (parameter[0] = GetHexValue((char)HexValue.GetChar(0))))
				return ("x8");
		}
		if (i == 3)
		{
			if (HexValue.Length() != 2)
				return ("x9");
			if (-1 == (parameter[1] = GetHexValue((char)HexValue.GetChar(0))))
				return ("x10");
			if (-1 == (parameter[2] = GetHexValue((char)HexValue.GetChar(1))))
				return ("x11");
			parameter[1] = (parameter[1] << 4) | parameter[2];
			if (360 <= (AutoValue = (int)(((parameter[0] & 0x03) * 90)
                + ((parameter[1] & 0x3F) * 2)
                + (((parameter[0] >> 2) & 0x03) / 2) 
				+ ((parameter[0] >> 2) & 0x01))))
            {
                AutoValue = 0;
            }
			ReturnCompassValue = AutoValue - CompassValue;
			if (ReturnCompassValue >= 180)
				ReturnCompassValue -= 360;
			if (ReturnCompassValue < -180)
				ReturnCompassValue += 360;
			return(wxString::Format(wxT("%i"), ReturnCompassValue));
		}
	}
	return ("-"); // Nicht def
}

void  raymarine_autopilot_pi::AddVariationToRMCanSendOut(wxString &sentence_incomming)
{
	wxString Newsentence = sentence_incomming.Left(sentence_incomming.find(wxT("*"))); // delete Checksumme

	Newsentence.SetChar(1, 'E'); // Set to comes from Electronic Charts
	Newsentence.SetChar(2, 'C');
	if (BoatVariation == 0x01FF)
	{
		SendNMEASentence(Newsentence);  // Send out the Sentence without new Variation. not avalibal do that $ECRMC is send the origianl will be filterd
		return;
	}

	int sLenght = Newsentence.Length();
	int i = 0;
	int LastKomma = 0; // Stelle 0
	while (i < 10)
	{
		if (sLenght < LastKomma)
		{
			if (WriteMessages) wxLogMessage("Wrong RMC Message detected");
			return; // error not the right
		}
		LastKomma += Newsentence.Right(sLenght - LastKomma).find(wxT(",")) + 1;
		if (LastKomma == 0)
		{
			if (WriteMessages) wxLogMessage("Wrong RMC Message detected");
			return; // error not the right
		}
		i++;
	}
	int Dummy = LastKomma;
	wxString Appand = "";
	// See if there is somthing after the NOT SET VAriation 'A' ...
	if (sLenght >= Dummy)
		Dummy += Newsentence.Right(sLenght - Dummy).find(wxT(",")) + 1;
	if (sLenght >= Dummy)
		Dummy += Newsentence.Right(sLenght - Dummy).find(wxT(",")) + 1;
	if (sLenght >= Dummy)
		Appand = Newsentence.Right(sLenght - Dummy);
	Newsentence = Newsentence.Left(LastKomma);
	if (abs(BoatVariation) < 100)
		Newsentence.Append("0");
	if (abs(BoatVariation) < 10)
		Newsentence.Append("0");
	Newsentence.Append(wxString::Format(_T("%3.1f"), abs(BoatVariation)));
	Newsentence.Append(wxT(","));
	if (BoatVariation > 0)
		Newsentence.Append(wxT("E"));
	else
		Newsentence.Append(wxT("W"));
	if (Appand.Length() != 0)
	{	
		Newsentence.Append(wxT(","));
		Newsentence.Append(Appand);
	}
	SendNMEASentence(Newsentence);
}

void raymarine_autopilot_pi::SendNMEASentence(wxString sentence)
{
	wxString Checksum = ComputeChecksum(sentence);
	sentence = sentence.Append(wxT("*"));
	sentence = sentence.Append(Checksum);
	sentence = sentence.Append(wxT("\r\n"));
	PushNMEABuffer(sentence);
}

wxString raymarine_autopilot_pi::ComputeChecksum(wxString sentence)
{
	unsigned char calculated_checksum = 0;
	for (wxString::const_iterator i = sentence.begin() + 1; i != sentence.end() && *i != '*'; ++i)
		calculated_checksum ^= static_cast<unsigned char> (*i);

	return(wxString::Format("%02X", calculated_checksum));
}


void raymarine_autopilot_pi::SendGotoAuto()
{
    if (AutoPilotType == SMARTPILOT)
    {
        wxString sentence = "$" + STALKSendName + ",86,21,01,FE";
        SendNMEASentence(sentence);
    }
    else
    {
        tN2kMsg N2kMsg;
        SetN2kPGN126208(N2kMsg, AUTO, 204); // Send to all dont know if 204 is alway correct
        SendN2kMessage(N2kMsg);
    }
    MyLastSend = AUTO;    
}

void raymarine_autopilot_pi::SendGotoStandby()
{
    if (AutoPilotType == SMARTPILOT)
    {
        wxString sentence = "$" + STALKSendName + ",86,21,02,FD";
        SendNMEASentence(sentence);
    }
    else
    {
        tN2kMsg N2kMsg;
        SetN2kPGN126208(N2kMsg, STANDBY, 204);
        SendN2kMessage(N2kMsg);
    }
    MyLastSend = STANDBY;    
}

void raymarine_autopilot_pi::SendGotoAutoWind()
{
    if (AutoPilotType == SMARTPILOT)
    {
        wxString sentence = "$" + STALKSendName + ",86,21,23,DC";
        SendNMEASentence(sentence);
    }
    else
    {
        tN2kMsg N2kMsg;
        SetN2kPGN126208(N2kMsg, AUTOWIND, 204);
        SendN2kMessage(N2kMsg);
    }
    MyLastSend = AUTOWIND;    
}

void raymarine_autopilot_pi::SendGotoAutoTrack()
{
    if (AutoPilotType == SMARTPILOT)
    {
        wxString sentence = "$" + STALKSendName + ",86,21,03,FC";
        SendNMEASentence(sentence);
    }
    else
    {
        tN2kMsg N2kMsg;
        SetN2kPGN126208(N2kMsg, AUTOTRACK, 204);
        SendN2kMessage(N2kMsg);
    }
    MyLastSend = AUTOTRACK;
}

void raymarine_autopilot_pi::SendIncrementOne()
{
    if (AutoPilotType == SMARTPILOT)
    {
        wxString sentence = "$" + STALKSendName + ",86,21,07,F8";
        SendNMEASentence(sentence);
    }
    else
    {
        tN2kMsg N2kMsg;
        N2kMsg.Destination = 204;  // Default address of EVO1 Pilot.
        if (Autopilot_Status == AUTO  && NewAutoOnStandby == false)  // NewAutoOnStandby is now send better Keystroke
        {
            if (EVOLockeHeading != N2kDoubleNA)
            {
                double NewEVOLockeHeading = EVOLockeHeading + 1;
                if (NewEVOLockeHeading >= 360) NewEVOLockeHeading -= 360;
                SetRaymarineLockedHeadingN2kPGN126208(N2kMsg, DegToRad(NewEVOLockeHeading));
            }
            else
               return;
        }
        else
            SetRaymarineKeyCommandPGN126720(N2kMsg, 204, 0x07F8);
        SendN2kMessage(N2kMsg);
    }
    MyLastSend = IncrementOne;
}

void raymarine_autopilot_pi::SendIncrementTen()
{
    if (AutoPilotType == SMARTPILOT)
    {
        wxString sentence = "$" + STALKSendName + ",86,21,08,F7";
        SendNMEASentence(sentence);
    }
    else
    {
        tN2kMsg N2kMsg;
        N2kMsg.Destination = 204;  // Default address of EVO1 Pilot.
        if (Autopilot_Status == AUTO && NewAutoOnStandby == false) // NewAutoOnStandby is now send better Keystroke
        {
            if (EVOLockeHeading != N2kDoubleNA)
            {
                double NewEVOLockeHeading = EVOLockeHeading + 10;
                if (NewEVOLockeHeading >= 360) NewEVOLockeHeading -= 360;
                SetRaymarineLockedHeadingN2kPGN126208(N2kMsg, DegToRad(NewEVOLockeHeading));
            }
            else
                return;
        }
        else
            SetRaymarineKeyCommandPGN126720(N2kMsg, 204, 0x08F7);
        SendN2kMessage(N2kMsg);
    }
    MyLastSend = IncrementTen;
}

void raymarine_autopilot_pi::SendDecrementOne()
{
    if (AutoPilotType == SMARTPILOT)
    {
        wxString sentence = "$" + STALKSendName + ",86,21,05,FA";
        SendNMEASentence(sentence);
    }
    else
    {
        tN2kMsg N2kMsg;
        N2kMsg.Destination = 204;  // Default address of EVO1 Pilot.
        if (Autopilot_Status == AUTO && NewAutoOnStandby == false) // NewAutoOnStandby is now send better Keystroke
        {
            if (EVOLockeHeading != N2kDoubleNA)
            {
                double NewEVOLockeHeading = EVOLockeHeading - 1;
                if (NewEVOLockeHeading < 0) NewEVOLockeHeading += 360;
                SetRaymarineLockedHeadingN2kPGN126208(N2kMsg, DegToRad(NewEVOLockeHeading));
            }
            else
                return;
        }
        else
            SetRaymarineKeyCommandPGN126720(N2kMsg, 204, 0x05FA);
        SendN2kMessage(N2kMsg);
    }
    MyLastSend = DecrementOne;
}

void raymarine_autopilot_pi::SendDecrementTen()
{
    if (AutoPilotType == SMARTPILOT)
    {
        wxString sentence = "$" + STALKSendName + ",86,21,06,F9";
        SendNMEASentence(sentence);
    }
    else
    {
        tN2kMsg N2kMsg;
        N2kMsg.Destination = 204;  // Default address of EVO1 Pilot.
        if (Autopilot_Status == AUTO && NewAutoOnStandby == false) // NewAutoOnStandby is now send better Keystroke
        {
            if (EVOLockeHeading != N2kDoubleNA)
            {
                double NewEVOLockeHeading = EVOLockeHeading - 10;
                if (NewEVOLockeHeading < 0) NewEVOLockeHeading += 360;
                SetRaymarineLockedHeadingN2kPGN126208(N2kMsg, DegToRad(NewEVOLockeHeading));
            }
            else
                return;
        }
        else
            SetRaymarineKeyCommandPGN126720(N2kMsg, 204, 0x06F9);
        SendN2kMessage(N2kMsg);
    }
    MyLastSend = DecrementTen;
}

// AuotCOG stuff
// ---------------------------------------------------------------------

void raymarine_autopilot_pi::ResetAUTOCOGValues()
{
    uint8_t i;
    DaysSince1970 = N2kUInt16NA;
    SOG_counter = 0;
    COG_counter = 0;
    SOG_valid = 0;
    COG_valid = 0;
    for (i = 0; i < 3; i++) SOGA[i] = -1;
    SOG = 0;
    for (i = 0; i < 30; i++)COGA[i] = -1;
    COG = -1;
    if (cogsensibility > 30 || cogsensibility < 1)
        cogsensibility = 15;
    if (allowautocog == false)
    {
        Autopilot_Status_Before = UNKNOWN;
        AutoCOGStatus = false;
        m_pDialog->buttonAuto->SetLabel("Auto");
        m_pDialog->buttonAuto->SetBackgroundColour(wxColour(255, 0, 0));
        if (NULL != p_GPSTimer)
        {
            p_GPSTimer->Stop();
            delete p_GPSTimer;
            p_GPSTimer = NULL;
        }
        if (NULL != p_AutoCogTimer)
        {
            p_AutoCogTimer->Stop();
            delete p_AutoCogTimer;
            p_AutoCogTimer = NULL;
        }
    }
    else
    {
        if (NULL != p_AutoCogTimer)
        {
            p_AutoCogTimer->Stop();
            if (p_AutoCogTimer->Start(cogsensibility * 2000) == false)
            {
                if (m_pDialog != NULL && DisplayShow == 0)
                {
                    m_pDialog->SetStatusText("No AutoCOG");
                    DisplayShow = 10;
                }
                AutoCOGStatus = false;
            }
        }
    }
}

void raymarine_autopilot_pi::ActualisateCOGSOG(wxString& sentence)
{
    RMC rmc;
    SENTENCE Sentence;
    Sentence = sentence;
    rmc.Parse(Sentence);
    MakeCOGSOG(rmc.SpeedOverGroundKnots, rmc.TrackMadeGoodDegreesTrue);
}


void raymarine_autopilot_pi::MakeCOGSOG(double SpeedOverGroundKnots, int TrackMadeGoodDegreesTrue)
{
    if (p_GPSTimer == NULL)
    {
        p_GPSTimer = new GPSTimer(this);
        if (Autopilot_Status == AUTO && AutoCOGStatus == false)
        {
            if (m_pDialog != NULL)
            {
                m_pDialog->buttonAuto->SetLabel("AutoCOG");
                m_pDialog->buttonAuto->SetBackgroundColour(wxColour(148, 88, 167));
            }
        }
    }
    p_GPSTimer->Stop();
    p_GPSTimer->StartOnce(7000);  // 7 Sekunden
    uint8_t i;
    int bcog = 0;    
    if (SOG_counter > 2) SOG_counter = 0;
    if (COG_counter >= cogsensibility) COG_counter = 0;    
    if (SOG_valid < 3 ) SOG_valid++;
    if (COG_valid < cogsensibility) COG_valid++;
    // SOG
    SOGA[SOG_counter] = SpeedOverGroundKnots;
    SOG = 0;
    for (i = 0; i < SOG_valid; i++) SOG += SOGA[i];
    SOG /= SOG_valid;
    // COG
    COGA[COG_counter] = TrackMadeGoodDegreesTrue;
    COG = 0;
    for (i = 0; i < COG_valid; i++)
    {
        if (COGA[i] >= bcog) bcog = COGA[i];
    }
    for (i = 0; i < COG_valid; i++)
    {
        COG += COGA[i];
        if (COGA[i] <= (bcog-180))
            COG += 360;
    }
    COG /= COG_valid;
    if (COG >= 360) COG -= 360;
    SOG_counter++;
    COG_counter++;
}

void raymarine_autopilot_pi::ActivateAutoCOG()
{
    if (AutoCOGStatus == true && Autopilot_Status == AUTO)
    {
        // wieder zur?ck zu normal Auto
        DeActivateAutoCOG();        
        return;
    }
    if (EVOLockeHeading == N2kDoubleNA && AutoPilotType != SMARTPILOT) 
    {
        if (m_pDialog != NULL && DisplayShow == 0)
        {
            m_pDialog->SetStatusText("No Pilot");
            DisplayShow = 8;
        }
        return;
    }
    if (COG == -1)
    {
        if (m_pDialog != NULL && DisplayShow == 0)
        {
            m_pDialog->SetStatusText("No COG");
            DisplayShow = 4;
        }
        return;
    }
    AutoCOGStatus = true;
    LastChange = 0;
    COGCourse = COG;    
    if (p_AutoCogTimer == NULL)
        p_AutoCogTimer = new AutoCogTimer(this);
    if (p_AutoCogTimer->Start(cogsensibility * 2000) == false) // from 2 Seconds to 1 Minute
    {
        if (m_pDialog != NULL && DisplayShow == 0)
        {
            m_pDialog->SetStatusText("No AutoCOG");
            DisplayShow = 10;
        }
        AutoCOGStatus = false;
    }
    else
    {
        m_pDialog->buttonAuto->SetLabel("Auto");
        m_pDialog->buttonAuto->SetBackgroundColour(wxColour(255, 0, 0));
        if (WriteMessages) wxLogMessage(" Activate AutoCOG");
    }
}

void raymarine_autopilot_pi::DeActivateAutoCOG()
{
    if (AutoCOGStatus == false)
        return;
    AutoCOGStatus = false;
    if (p_AutoCogTimer)
    {
        p_AutoCogTimer->Stop();
        delete p_AutoCogTimer;
        p_AutoCogTimer = NULL;
    }
    if (Autopilot_Status == AUTO)
    {
        m_pDialog->buttonAuto->SetLabel("AutoCOG");
        m_pDialog->buttonAuto->SetBackgroundColour(wxColour(148, 88, 167));
    }
    else
    {
        m_pDialog->buttonAuto->SetLabel("Auto");
        m_pDialog->buttonAuto->SetBackgroundColour(wxColour(255, 0, 0));
    }
    if (WriteMessages) wxLogMessage(" De-activate AutoCOG");
}

void raymarine_autopilot_pi::WriteCOGStatus()
{
    m_pDialog->SetStatusText("  AutoCOG  ");
    if (COG == -1)
        m_pDialog->SetCompassText("set: " + wxString::Format(wxT("%i"), COGCourse) + "  is: ---");
    else
        m_pDialog->SetCompassText("set: " + wxString::Format(wxT("%i"), COGCourse) + "  is: " + wxString::Format(wxT("%i"), COG));
}

void AutoCogTimer::Notify()
{
    if (pAutopilot->Autopilot_Status != AUTO)
        return;
    if (pAutopilot->COG == -1)
    {
        pAutopilot->AutoCOGStatus = false;
        if (pAutopilot->p_GPSTimer != NULL)
        {
            delete (pAutopilot->p_GPSTimer);
            pAutopilot->p_GPSTimer = NULL;
        }
        if (pAutopilot->WriteMessages) wxLogMessage(" COG lost for AutoCOG");
        if (pAutopilot->m_pDialog != 0)
        {
            if (pAutopilot->allowautocog)
            {
                pAutopilot->m_pDialog->buttonAuto->SetLabel("AutoCOG");
                pAutopilot->m_pDialog->buttonAuto->SetBackgroundColour(wxColour(148, 88, 167));
            }
            if (pAutopilot->DisplayShow == 0)
            {
                pAutopilot->m_pDialog->SetStatusText("COG lost");
                pAutopilot->DisplayShow = 7;
            }
        }
        Stop();
        return;
    }
    // Check SOG too slow?
    if (pAutopilot->SOG < pAutopilot->minspeedcog)
    {
        if (pAutopilot->WriteMessages) wxLogMessage(" SOG too slow");
        pAutopilot->AutoCOGStatus = false;
        if (pAutopilot->p_GPSTimer != NULL)
        {
            delete (pAutopilot->p_GPSTimer);
            pAutopilot->p_GPSTimer = NULL;
        }
        if (pAutopilot->m_pDialog != 0)
        {
            if (pAutopilot->allowautocog)
            {
                pAutopilot->m_pDialog->buttonAuto->SetLabel("AutoCOG");
                pAutopilot->m_pDialog->buttonAuto->SetBackgroundColour(wxColour(148, 88, 167));
            }
            if (pAutopilot->DisplayShow == 0)
            {
                pAutopilot->m_pDialog->SetStatusText("SOG slow");
                pAutopilot->DisplayShow = 6;
            }
        }
        Stop();
        return;
    }
    // Check COG and HDM
    int MAGCOGdiff = pAutopilot->COG - pAutopilot->MAGcourse;
    if (abs(MAGCOGdiff) > 180)
    {
        if (pAutopilot->COG > pAutopilot->MAGcourse)
            MAGCOGdiff = (pAutopilot->MAGcourse + 360) - pAutopilot->COG;
        else
            MAGCOGdiff = pAutopilot->MAGcourse - (pAutopilot->COG + 360);
    }
    if (abs(MAGCOGdiff) > pAutopilot->maxdegreediff && pAutopilot->MAGcourse != -1)
    {
        // diff between COG and MAG too big
        if (pAutopilot->WriteMessages) wxLogMessage(" COG-HDM big");
        pAutopilot->AutoCOGStatus = false;
        if (pAutopilot->p_GPSTimer != NULL)
        {
            delete (pAutopilot->p_GPSTimer);
            pAutopilot->p_GPSTimer = NULL;
        }
        if (pAutopilot->m_pDialog != 0)
        {
            if (pAutopilot->allowautocog)
            {
                pAutopilot->m_pDialog->buttonAuto->SetLabel("AutoCOG");
                pAutopilot->m_pDialog->buttonAuto->SetBackgroundColour(wxColour(148, 88, 167));
            }
            if (pAutopilot->DisplayShow == 0)
            {
                pAutopilot->m_pDialog->SetStatusText("COG-HDM");
                pAutopilot->DisplayShow = 7;
            }
        }
        Stop();
        return;
    }
    // Check Max Autopilot Set Heading change.
    if (abs(pAutopilot->AutoCOGHeadingChange) > pAutopilot->maxchangehdg)
    {
        // Set HDG of Autopilot too big
        if (pAutopilot->WriteMessages) wxLogMessage(" Set HDG too big");
        pAutopilot->AutoCOGStatus = false;
        if (pAutopilot->p_GPSTimer != NULL)
        {
            delete (pAutopilot->p_GPSTimer);
            pAutopilot->p_GPSTimer = NULL;
        }
        if (pAutopilot->m_pDialog != 0)
        {
            if (pAutopilot->allowautocog)
            {
                pAutopilot->m_pDialog->buttonAuto->SetLabel("AutoCOG");
                pAutopilot->m_pDialog->buttonAuto->SetBackgroundColour(wxColour(148, 88, 167));
            }
            if (pAutopilot->DisplayShow == 0)
            {
                pAutopilot->m_pDialog->SetStatusText("Big Change");
                pAutopilot->DisplayShow = 9;
            }
        }
        Stop();
        return;
    }
    // Now change Course 
    int COGdiff = pAutopilot->COGCourse - pAutopilot->COG;
    wxString sentence;
    // check if around 0 deg
    if (abs(COGdiff) > 180)
    {
        if (pAutopilot->COGCourse > pAutopilot->COG)
            COGdiff = (pAutopilot->COG + 360) - pAutopilot->COGCourse;
        else
            COGdiff = pAutopilot->COG - (pAutopilot->COGCourse + 360);
    }    
    if (COGdiff > 0) // Sollkurs ist gr?sser als istkurs  +1
    {
        if (pAutopilot->LastChange == -1)
        {
            // Nicht gleich wieder zurücktoggeln.
            pAutopilot->LastChange = 0;
            return;
        }
        if (pAutopilot->WriteMessages) wxLogMessage("AutoCOG +1");
        pAutopilot->SendIncrementOne();
        pAutopilot->AutoCOGHeadingChange++;
        pAutopilot->LastChange = 1;
        if (pAutopilot->DisplayShow == 0)
        {
            pAutopilot->m_pDialog->SetStatusText("   AutoCOG >");
            pAutopilot->DisplayShow = 2;
        }
        return;
    }
    if (COGdiff < 0)  // istkurs ist gr?sser als sollkurs -1
    {
        if (pAutopilot->LastChange == 1)
        {
            // Nicht gleich wieder zurücktoggeln.
            pAutopilot->LastChange = 0;
            return;
        }
        if (pAutopilot->WriteMessages) wxLogMessage("AutoCOG -1");
        pAutopilot->SendDecrementOne();
        pAutopilot->AutoCOGHeadingChange--;
        pAutopilot->LastChange = -1;
        if (pAutopilot->DisplayShow == 0)
        {
            pAutopilot->m_pDialog->SetStatusText("< AutoCOG   ");
            pAutopilot->DisplayShow = 2;
        }
        return;
    }
    pAutopilot->LastChange = 0;
}

localTimer::localTimer(raymarine_autopilot_pi *pAuto)
{
	pAutopilot = pAuto;
}

void localTimer::Notify()
{
	// Keine Informationen vom Kurscomputer
	if (pAutopilot->WriteMessages) wxLogInfo("No Data from Autopilot Computer");
	pAutopilot->Autopilot_Status = UNKNOWN;
    pAutopilot->MAGcourse = -1;
    pAutopilot->Received_65379 = false;
    pAutopilot->GetHeadingFromSeatalkNG = false;
    pAutopilot->EVOLockeHeading = N2kDoubleNA;
    pAutopilot->Received_Heading_126208 = false;
    pAutopilot->Received_AUTO_126208 = false;
    pAutopilot->Received_LockedHeading_inStandby = false;
    pAutopilot->AutoCOGHeadingChange = 0;
    pAutopilot->LastCompassCourse = -1;
	if (NULL != pAutopilot->m_pDialog)
	{
		pAutopilot->m_pDialog->SetCopmpassTextColor(wxColour(0, 0, 64));
		pAutopilot->m_pDialog->SetTextStatusColor(wxColour(0, 0, 128));
		pAutopilot->m_pDialog->SetStatusText("----------");
		pAutopilot->m_pDialog->SetCompassText("---");
		pAutopilot->WayPointBearing = "unknown";
		pAutopilot->GoneTimeToSendNewWaypoint = 0;
		pAutopilot->IS_standby = 0;
		pAutopilot->Standbycommandreceived = TRUE; // So when the Instruments are switched on again no Error !
		pAutopilot->CounterStandbySentencesReceived = 0;
        if (pAutopilot->allowautocog)
        {
            pAutopilot->m_pDialog->buttonAuto->SetLabel("Auto");
            pAutopilot->m_pDialog->buttonAuto->SetBackgroundColour(wxColour(255, 0, 0));
            pAutopilot->DeActivateAutoCOG();
        }
	}
}

//
// N2k
//

void raymarine_autopilot_pi::CheckSeasartSentence(wxString sentence)
{
    tN2kMsg N2kMsg;
    uint32_t timestamp = 42; // not used only a dummy
    SeasmartToN2k((const char*)sentence.mb_str(wxConvUTF8), timestamp, N2kMsg);
    switch (N2kMsg.PGN)
    {
    case 65360 : HandleN2kMsg_65360(N2kMsg);  break; // Pilot heading
    case 126208: HandleN2kMsg_126208(N2kMsg); break; // Set Set pilot heading or set auto/standby
    case 126720: HandleN2kMsg_126720(N2kMsg); break; // From EV1 indicating auto or standby state  ... and more !!!
    case 65379 : HandleN2kMsg_65379(N2kMsg);  break; // Pilot State
    case 65288 : HandleN2kMsg_65288(N2kMsg);  break; // Pilot Alarm
    case 65359 : HandleN2kMsg_65359(N2kMsg);  break; // Vessel heading, proprietary
    case 127250: HandleN2kMsg_127250(N2kMsg); break; // Vessel heading, standerd NMEA2000 
    case 129026: HandleN2kMsg_129026(N2kMsg); break; // COG SOG for AutoCOG 
    case 126992: HandleN2kMsg_126992(N2kMsg); break; // SystemTime
    case 129029: HandleN2kMsg_129029(N2kMsg); break; // Position
    default : if (WriteMessages) wxLogMessage("Unkown $PCDIN PGN %lu", N2kMsg.PGN);
    }
}

void SetN2kPGN126208(tN2kMsg& N2kMsg, uint8_t mode, uint8_t PilotSourceAddress) {
    N2kMsg.SetPGN(126208UL);
    N2kMsg.Priority = 3;
    N2kMsg.Destination = PilotSourceAddress;
    N2kMsg.AddByte(1); // Field 1, 1 = Command Message, 2 = Acknowledge Message...
    N2kMsg.AddByte(0x63);  // PGN 65379 
    N2kMsg.AddByte(0xff);  //
    N2kMsg.AddByte(0x00);  // end PGN
    N2kMsg.AddByte(0xf8);  // priority + reserved
    N2kMsg.AddByte(0x04);  // 4 Parameter
    N2kMsg.AddByte(0x01);  // // first param - 1 of PGN 65379 (manufacturer code)
    N2kMsg.AddByte(0x3b);  // Raymarine
    N2kMsg.AddByte(0x07);  //     "
    N2kMsg.AddByte(0x03);  // second param -  3 of pgn 65369 (Industry code)
    N2kMsg.AddByte(0x04);  // Ind. code 4
    N2kMsg.AddByte(0x04);  // third parameter - 4 of pgn 65379 (mode)

    // 0x00 = standby, 0x40 = auto, 0x0100=vane, 0x0180=track
    switch (mode) {
    case STANDBY:
        N2kMsg.AddByte(0x00);
        N2kMsg.AddByte(0x00);
        break;
    case AUTO:
        N2kMsg.AddByte(0x40);
        N2kMsg.AddByte(0x00);
        break;
    case AUTOWIND:
        N2kMsg.AddByte(0x00);
        N2kMsg.AddByte(0x01);
        break;
    case AUTOTRACK:
        N2kMsg.AddByte(0x80);
        N2kMsg.AddByte(0x01);
        break;
    case AUTOTURNWP:  // Not Used here
        N2kMsg.AddByte(0x81);
        N2kMsg.AddByte(0x01);
        break;
    }
    N2kMsg.AddByte(0x05);  // value of weird raymarine param
    N2kMsg.AddByte(0xff);
    N2kMsg.AddByte(0xff);
}

void SetRaymarineLockedHeadingN2kPGN126208(tN2kMsg& N2kMsg, double Heading)
{
    N2kMsg.SetPGN(126208UL);
    N2kMsg.Priority = 3;

    N2kMsg.AddByte(0x01);  // Field 1, 1 = Command Message, 2 = Acknowledge Message...
    N2kMsg.AddByte(0x50);  // PGN 65360 
    N2kMsg.AddByte(0xff);  //
    N2kMsg.AddByte(0x00);  // end PGN
    N2kMsg.AddByte(0xf8);  // priority + reserved
    N2kMsg.AddByte(0x03);  // 3 Parameter
    N2kMsg.AddByte(0x01);  // // first param - 1 of PGN 65360 (manufacturer code)
    N2kMsg.AddByte(0x3b);  // Raymarine
    N2kMsg.AddByte(0x07);  //     "
    N2kMsg.AddByte(0x03);  // second param -  3 of pgn 65360 (Industry code)
    N2kMsg.AddByte(0x04);  // Ind. code 4
    N2kMsg.AddByte(0x06);  // third parameter - 4 of pgn 65360 (mode)
    N2kMsg.Add2ByteUDouble(Heading, 0.0001);
}

// For Set new Windangle
void SetRaymarineKeyCommandPGN126720(tN2kMsg& N2kMsg, uint8_t destinationAddress, uint16_t command) {

    uint8_t commandByte0, commandByte1;
    commandByte0 = command >> 8;
    commandByte1 = command & 0xff;

    N2kMsg.SetPGN(126720UL);
    N2kMsg.Priority = 3;
    N2kMsg.Destination = destinationAddress;

    N2kMsg.AddByte(0x3b);  // Raymarine
    N2kMsg.AddByte(0x9f);
    N2kMsg.AddByte(0xf0);
    N2kMsg.AddByte(0x81);
    N2kMsg.AddByte(0x86);  // Key Command
    N2kMsg.AddByte(0x21);
    N2kMsg.AddByte(commandByte0);
    N2kMsg.AddByte(commandByte1);
    N2kMsg.AddByte(0xff);
    N2kMsg.AddByte(0xff);
    N2kMsg.AddByte(0xff);
    N2kMsg.AddByte(0xff);
    N2kMsg.AddByte(0xff);
    N2kMsg.AddByte(0xc1);
    N2kMsg.AddByte(0xc2);
    N2kMsg.AddByte(0xcd);
    N2kMsg.AddByte(0x66);
    N2kMsg.AddByte(0x80);
    N2kMsg.AddByte(0xd3);
    N2kMsg.AddByte(0x42);
    N2kMsg.AddByte(0xb1);
    N2kMsg.AddByte(0xc8);
}

// Seatalk Pilot Locked Heading 
bool ParseN2kPGN65360(const tN2kMsg& N2kMsg, double& HeadingTrue, double& HeadingMagnetic) {
    if (N2kMsg.PGN != 65360L) return false;

    int Index = 3;

    HeadingTrue = N2kMsg.Get2ByteUDouble(0.0001, Index);
    HeadingMagnetic = N2kMsg.Get2ByteUDouble(0.0001, Index);

    return true;
}


// Seatalk Pilot Heading 
bool ParseN2kPGN65359(const tN2kMsg& N2kMsg, double& HeadingTrue, double& HeadingMagnetic) {
    if (N2kMsg.PGN != 65359L) return false;

    int Index = 3;

    HeadingTrue = N2kMsg.Get2ByteUDouble(0.0001, Index);
    HeadingMagnetic = N2kMsg.Get2ByteUDouble(0.0001, Index);

    return true;
}

// Pilot State
bool ParseN2kPGN65379(const tN2kMsg& N2kMsg, unsigned char& Mode, unsigned char& Submode) {
    if (N2kMsg.PGN != 65379L) return false;

    int Index = 2;

    Mode = N2kMsg.GetByte(Index);
    Submode = N2kMsg.GetByte(Index);

    return true;
}

// ... is a N2k Message as Seatalk1 Message. 
bool ParseN2kPGN126720(const tN2kMsg& N2kMsg, uint8_t& Mode, uint8_t& SubMode, uint16_t& commandValues)
{
    if (N2kMsg.PGN != 126720UL) return false;

    int Index = 0;
    uint8_t Command;
    commandValues = 0;

    if (0x3b != N2kMsg.GetByte(Index))    // Not Raymarine
        return false;
    if (0x9f != N2kMsg.GetByte(Index))    // Not Raymarine
        return false;
    N2kMsg.GetByte(Index);
    N2kMsg.GetByte(Index);
    Command = (N2kMsg.GetByte(Index));
    if (Command == 0x84)  // Pilot State
    {    
        N2kMsg.GetByte(Index);
        N2kMsg.GetByte(Index);
        N2kMsg.GetByte(Index);
        Mode = N2kMsg.GetByte(Index);
        SubMode = N2kMsg.GetByte(Index);
        N2kMsg.GetByte(Index);
        N2kMsg.GetByte(Index);
        N2kMsg.GetByte(Index);
        return true;
    }
    if (0x86 == Command)
    {
        N2kMsg.GetByte(Index);
        commandValues = N2kMsg.GetByte(Index) << 8;
        commandValues |= N2kMsg.GetByte(Index);
        return true;       
    }
    return false;
}

// Keystroke from other Instruments or Raymarine Plotter.
bool ParseN2kPGN126208(const tN2kMsg& N2kMsg, uint8_t& CommandMode, double& Value)
{
    if (N2kMsg.PGN != 126208UL) return false;
    uint8_t vb;
    int Index = 0;
    CommandMode = 0;

    if (0x01 != N2kMsg.GetByte(Index)) return false;  // No Command
    vb = N2kMsg.GetByte(Index);
    if (0x63 == vb)  // PGN 65379     
    {
        // Set Command
        N2kMsg.GetByte(Index); // 0xff  unwichtig
        N2kMsg.GetByte(Index); // 0x00
        N2kMsg.GetByte(Index); // 0xf8
        N2kMsg.GetByte(Index); // 0x04 4 Parameter
        if (0x01 != N2kMsg.GetByte(Index)) return false;
        if (0x3B != N2kMsg.GetByte(Index)) return false; // Raymarine
        if (0x07 != N2kMsg.GetByte(Index)) return false; // Raymarine
        N2kMsg.GetByte(Index); // 0x03
        if (0x04 != N2kMsg.GetByte(Index)) return false; // Industrial Code
        N2kMsg.GetByte(Index); // 0x04  third Parameter

        Value = 0xFF;  // ung?ltig
        switch (N2kMsg.Get2ByteUInt(Index))
        {
        case 0x0000: Value = STANDBY;
            break;
        case 0x0040: Value = AUTO;
            break;
        case 0x0100: Value = AUTOWIND;
            break;
        case 0x0180: Value = TRACK;
            break;
        case 0x0181: Value = TRACK; // PILOT_MODE_TURNWP
            break;
        }
        if (Value != 0xFF)
            CommandMode = 1;  // Command set Mode
        return true;
    }
    if (0x50 == vb)  // PGN ???? 
    {
        // Command set Pilot coures
        N2kMsg.GetByte(Index); // 0xff  unwichtig
        N2kMsg.GetByte(Index); // 0x00
        N2kMsg.GetByte(Index); // 0xf8
        N2kMsg.GetByte(Index); // 0x04 4 oder 3 Parameter
        if (0x01 != N2kMsg.GetByte(Index)) return false;
        if (0x3B != N2kMsg.GetByte(Index)) return false; // Raymarine
        if (0x07 != N2kMsg.GetByte(Index)) return false; // Raymarine
        N2kMsg.GetByte(Index); // 0x03
        if (0x04 != N2kMsg.GetByte(Index)) return false; // Industrial Code
        N2kMsg.GetByte(Index); // 0x04 oder 06 egal  third Parameter
        Value = N2kMsg.Get2ByteUDouble(0.0001, Index);  // Pilot Course
        CommandMode = 2;  // Set Pilot Course
        return true;
    }
    if (0x41 == vb)  // PGN ???? 
    {
        // Command Pilot Wind
        N2kMsg.GetByte(Index); // 0xff  unwichtig
        N2kMsg.GetByte(Index); // 0x00
        N2kMsg.GetByte(Index); // 0xf8
        N2kMsg.GetByte(Index); // 0x04 4 oder 3 Parameter
        if (0x01 != N2kMsg.GetByte(Index)) return false;
        if (0x3B != N2kMsg.GetByte(Index)) return false; // Raymarine
        if (0x07 != N2kMsg.GetByte(Index)) return false; // Raymarine
        N2kMsg.GetByte(Index); // 0x03
        if (0x04 != N2kMsg.GetByte(Index)) return false; // Industrial Code
        N2kMsg.GetByte(Index); // 0x04 oder 06 egal  third Parameter
        Value = N2kMsg.Get2ByteUDouble(0.0001, Index);  // Command Pilot Wind
        CommandMode = 3;  // Set Pilot Wind
        return true;
    }
    return false;
}

bool ParseN2kPGN65288(const tN2kMsg& N2kMsg, unsigned char& AlarmStatus, unsigned char& AlarmCode, unsigned char& AlarmGroup) {
    if (N2kMsg.PGN != 65288L) return false;

    int Index = 3;

    AlarmStatus = N2kMsg.GetByte(Index);
    AlarmCode = N2kMsg.GetByte(Index);
    AlarmGroup = N2kMsg.GetByte(Index);

    return true;
}


// Send N2k Message
void raymarine_autopilot_pi::SendN2kMessage(tN2kMsg N2kMsg)
{
    if (AutoPilotType == EVO)
    {
        std::shared_ptr<std::vector<uint8_t>> payload(new std::vector<uint8_t>((uint8_t)N2kMsg.DataLen));
        for (int i = 0; i < N2kMsg.DataLen; i++)
            payload->at(i) = *(N2kMsg.Data + i);
        N2kContainer* pH = pHandleN2k;
        while (pH != NULL)
        {
            WriteCommDriverN2K(pH->HandleN2k, N2kMsg.PGN, N2kMsg.Destination, N2kMsg.Priority, payload);
            pH = pH->pNext;
        }
    }
    else
    {
        // Use Seasmart
        char buffer[MAX_NMEA0183_MSG_LEN];        
        size_t mgslen = N2kToSeasmart(N2kMsg, N2kMsg.MsgTime, buffer, sizeof(buffer));
        if (mgslen)
        {            
            wxString sentence(buffer);
            sentence = sentence.Append(wxT("\r\n"));
            PushNMEABuffer(sentence);
        }
        else
        {
            if (WriteMessages) wxLogMessage("Not enought space for sending $PCDIN Sentence");
        }            
    }
}

void raymarine_autopilot_pi::SendBoatVariationToN2k()
{
    tN2kMsg N2kMsg;
    unsigned char SID = 1;
    N2kMsg.Destination = 255;
    N2kMsg.Priority = 6;

    SetN2kMagneticVariation(N2kMsg, SID, N2kmagvar_WMM2015, DaysSince1970, DegToRad(BoatVariation));
    SendN2kMessage(N2kMsg);
}


void raymarine_autopilot_pi::HandleN2K_129026(ObservedEvt ev) // COG SOG for AutoCOG
{
    NMEA2000Id id_129026(129026);    
    std::vector<uint8_t> msg = GetN2000Payload(id_129026, ev);
    tN2kMsg N2kMsg = MakeN2kMsg(msg);
    HandleN2kMsg_129026(N2kMsg);
}

void raymarine_autopilot_pi::HandleN2kMsg_129026(tN2kMsg N2kMsg)
{
    unsigned char SID;
    tN2kHeadingReference ref;
    double SpeedOverGroundKnots;
    double TrackMadeGoodDegreesTrue;

    if (ParseN2kPGN129026(N2kMsg, SID, ref, TrackMadeGoodDegreesTrue, SpeedOverGroundKnots)) {
        MakeCOGSOG((SpeedOverGroundKnots * 1.9438444924406) , (int)(TrackMadeGoodDegreesTrue * 180.0 / M_PI) );
    }
}

void raymarine_autopilot_pi::HandleN2K_126992(ObservedEvt ev) // System Time
{
    NMEA2000Id id_126992(126992);
    std::vector<uint8_t> msg = GetN2000Payload(id_126992, ev);
    tN2kMsg N2kMsg = MakeN2kMsg(msg);
    HandleN2kMsg_126992(N2kMsg);

}
void raymarine_autopilot_pi::HandleN2kMsg_126992(tN2kMsg N2kMsg)
{
    unsigned char SID;
    uint16_t SystemDate;
    double SystemTime;
    tN2kTimeSource TimeSource;

    if (ParseN2kPGN126992(N2kMsg, SID, SystemDate, SystemTime,TimeSource)) {
        DaysSince1970 = SystemDate;
    }
}

void raymarine_autopilot_pi::HandleN2K_129029(ObservedEvt ev) // Position Data ... only need Dayssince1970
{
    NMEA2000Id id_126992(126992);    
    std::vector<uint8_t> msg = GetN2000Payload(id_126992, ev);
    tN2kMsg N2kMsg = MakeN2kMsg(msg);
    HandleN2kMsg_129029(N2kMsg);
}

void raymarine_autopilot_pi::HandleN2kMsg_129029(tN2kMsg N2kMsg)
{
    unsigned char SID;
    uint16_t SystemDate;
    double SecondsSinceMidnight;
    double Latitude;
    double Longitude;
    double Altitude;
    tN2kGNSStype GNSStype;
    tN2kGNSSmethod GNSSmethod;
    uint8_t nSatellites;
    double HDOP, PDOP;
    double GeoidalSeparation;
    uint8_t nReferenceStations;
    tN2kGNSStype ReferenceStationType;
    uint16_t ReferenceSationID;
    double AgeOfCorrection;

    if (ParseN2kPGN129029(N2kMsg, SID, SystemDate, SecondsSinceMidnight, Latitude, Longitude, Altitude, GNSStype, GNSSmethod,
        nSatellites, HDOP, PDOP, GeoidalSeparation, nReferenceStations, ReferenceStationType, ReferenceSationID, AgeOfCorrection)) {
        DaysSince1970 = SystemDate;
    }
}

void raymarine_autopilot_pi::HandleN2K_65360(ObservedEvt ev) // Pilot heading
{
    if (AutoPilotType == SMARTPILOT) return;

    NMEA2000Id id_65360(65360);
    std::vector<uint8_t> msg = GetN2000Payload(id_65360, ev);
    tN2kMsg N2kMsg = MakeN2kMsg(msg);
    HandleN2kMsg_65360(N2kMsg);
}

void raymarine_autopilot_pi::HandleN2kMsg_65360(tN2kMsg N2kMsg)
{
    double HeadingTrue, HeadingMagnetic;
    if (ParseN2kPGN65360(N2kMsg, HeadingTrue, HeadingMagnetic))
    {
        EVOLockeHeading = (int)RadToDeg(HeadingMagnetic);
        while (EVOLockeHeading >= 360) EVOLockeHeading -= 360;        
        if (Autopilot_Status == STANDBY)  // I think normaly PGN 65379 must receive before
        {
            Received_LockedHeading_inStandby = true;
            Autopilot_Status = AUTO;
        }        
    }
}

void raymarine_autopilot_pi::HandleN2K_126208(ObservedEvt ev) // Received Set pilot heading or set auto/standby received keystroke, keystroke could also be 126720 with Command "86"
{
    if (AutoPilotType == SMARTPILOT) return;

    NMEA2000Id id_126208(126208);    
    std::vector<uint8_t> msg = GetN2000Payload(id_126208, ev);
    tN2kMsg N2kMsg = MakeN2kMsg(msg);
    HandleN2kMsg_126208(N2kMsg);
}

void raymarine_autopilot_pi::HandleN2kMsg_126208(tN2kMsg N2kMsg)
{
    uint8_t CommandMode;
    double Value;
    double NewLockedHeading;
    int Headingdiff;

    if (ParseN2kPGN126208(N2kMsg, CommandMode, Value))
    {
        switch (CommandMode)
        {
        // Received Command set Mode
        case 1:
        if ((int)Value == AUTO)
        {
            Received_AUTO_126208 = true;
            AutoCOGHeadingChange = 0;
            if (WriteMessages) wxLogMessage("Received Auto Pressed from n2k PNG 126208");
            if (Autopilot_Status == AUTO && Received_LockedHeading_inStandby == false && allowautocog)
            {
                ActivateAutoCOG();
                MyLastSend = Nothing;
                break;
            }
            Received_LockedHeading_inStandby = false;
        }
        if ((int)Value == STANDBY)
        {
            Standbycommandreceived = TRUE;
            if (WriteMessages) wxLogMessage("Received Standby Pressed from n2k");
            NeedCompassCorrection = false;
            MyLastSend = Nothing;                               
        }
        break;
        // Received Set new Pilot Heading in Automode.
        case 2:
            Received_Heading_126208 = true;
            NewLockedHeading = (int)RadToDeg(Value);
            while (NewLockedHeading >= 360) NewLockedHeading -= 360;
            Headingdiff = (int)NewLockedHeading - (int)EVOLockeHeading;
            if (abs(Headingdiff) > 180)
            {
                if (NewLockedHeading > EVOLockeHeading)
                    Headingdiff = ((int)EVOLockeHeading + 360) - (int)NewLockedHeading;
                else
                    Headingdiff = (int)EVOLockeHeading - ((int)NewLockedHeading + 360);
            }
            COGCourse += Headingdiff;  // for AUTOCOG
            if (COGCourse < 0) COGCourse += 360;
            if (COGCourse >= 360) COGCourse -= 360;
            MyLastSend = Nothing;
            AutoCOGHeadingChange = 0;
            if (WriteMessages) wxLogMessage(("Received new Set Pilot Locked Heading from n2k %i COGDiff %i"), (int)NewLockedHeading, Headingdiff);
            break;
        // New Winddirection in AutoWindmode. Could not save.  ... needs work what to do with it. ?!?
        case 3:
            //EVOLockeHeading = (int)RadToDeg(Value);
            //while (EVOLockeHeading >= 360) EVOLockeHeading -= 360;
            break;
        }
    }
}

void raymarine_autopilot_pi::HandleN2K_126720(ObservedEvt ev) // From EV1 indicating auto or standby state only when not 65379 this PGN has same Syntax as from SmartPilot Seatalk1
{
    if (AutoPilotType == SMARTPILOT) return;

    NMEA2000Id id_126720(126720);
    std::vector<uint8_t> msg = GetN2000Payload(id_126720, ev);
    tN2kMsg N2kMsg = MakeN2kMsg(msg);
    HandleN2kMsg_126720(N2kMsg);
}

void raymarine_autopilot_pi::HandleN2kMsg_126720(tN2kMsg N2kMsg)
{
    uint8_t Mode, Submode;
    uint16_t commandValues;

    if (ParseN2kPGN126720(N2kMsg, Mode, Submode, commandValues)) 
    {
        if (commandValues != 0) // Key Command Received.
        {
            if (AutoCOGStatus == false)
            {
                MyLastSend = Nothing;
                return;
            }
            switch (commandValues)
            {
            case 0x02FD: // Received Standby
                Standbycommandreceived = TRUE;
                if (WriteMessages) wxLogMessage("Received Standby Pressed from n2k PGN 126720");
                NeedCompassCorrection = false;
                MyLastSend = Nothing;
                break;
            case 0x01FE: // Received AUTO
                if (WriteMessages) wxLogMessage("Received Auto Pressed from n2k in Auto State PGN 126720");
                if(Received_AUTO_126208 == false)
                {
                    AutoCOGHeadingChange = 0;
                    if (Autopilot_Status == AUTO && Received_LockedHeading_inStandby == false && allowautocog)
                    {
                        ActivateAutoCOG();
                        MyLastSend = Nothing;
                        break;
                    }
                    Received_LockedHeading_inStandby = false;
                }
                break;
            case 0x23DC: // Received AUTOWIND
                break;
            case 0x03FC: // Received AUTOTRACK
                break;
            case 0x05FA: // Receives -1
                if (WriteMessages) wxLogMessage("Received -1 Pressed from n2k in Auto State");
                if (Received_Heading_126208 == false) // -1
                {
                    AutoCOGHeadingChange = 0;
                    COGCourse--;
                }
                break;
            case 0x06F9: // Received -10
                if (WriteMessages) wxLogMessage("Received -10 Pressed from n2k in Auto State");
                if (Received_Heading_126208 == false) // -10
                {
                    AutoCOGHeadingChange = 0;
                    COGCourse -= 10;
                }
                break;
            case 0x07F8: // Received +1
                if (WriteMessages) wxLogMessage("Received +1 Pressed from n2k in Auto State");
                if (Received_Heading_126208 == false) // +1
                {
                    AutoCOGHeadingChange = 0;
                    COGCourse++;
                }
                break;
            case 0x08F7: // Received +10
                if (WriteMessages) wxLogMessage("Received +10 Pressed from n2k in Auto State");
                if (Received_Heading_126208 == false) // +1
                {
                    AutoCOGHeadingChange = 0;
                    COGCourse += 10;
                }
                break;
            }
            if (COGCourse < 0) COGCourse += 360;
            if (COGCourse >= 360) COGCourse -= 360;
            MyLastSend = Nothing;
            return;
        }
        if (Received_65379 == true)
            return;
        // Autopilot Staus Received
        Autopilot_Status_Before = Autopilot_Status;
        Autopilot_Status = UNKNOWN;        
        if ((Mode & 0x02) == 0x00) // Wenn Bit 2 = 0 auf jeden Fall Standby.
            Autopilot_Status = STANDBY;
        // Wenn Bit 2 gesetzt ist, ist auf jeden Fall ein Auto Mode.
        if ((Mode & 0x04) == 0x04 && Autopilot_Status == UNKNOWN)
            Autopilot_Status = AUTOWIND;
        if ((Mode & 0x08) == 0x08 && Autopilot_Status == UNKNOWN)
            Autopilot_Status = AUTOTRACK;
        if ((Mode & 0x02) == 0x02 && Autopilot_Status == UNKNOWN)
            Autopilot_Status = AUTO;
        if (Autopilot_Status == AUTOWIND)
        {       
            if ((Submode & 0x08) == 0x08)
                Autopilot_Status = WINDSHIFT;
        }
        if (Autopilot_Status == AUTO || Autopilot_Status == AUTOTRACK)
        {
            if ((Submode & 0x04) == 0x04)
                Autopilot_Status = OFFCOURSE;
        }
        ToUpdateAutoPilotControlDisplay();
    }
}

void raymarine_autopilot_pi::HandleN2K_65379(ObservedEvt ev)  // Autopilot State
{
    if (AutoPilotType == SMARTPILOT) return;

    NMEA2000Id id_65379(65379);
    std::vector<uint8_t> msg = GetN2000Payload(id_65379, ev);
    tN2kMsg N2kMsg = MakeN2kMsg(msg);
    HandleN2kMsg_65379(N2kMsg);
}

void raymarine_autopilot_pi::HandleN2kMsg_65379(tN2kMsg N2kMsg)
{
    unsigned char Mode, Submode;

    if (ParseN2kPGN65379(N2kMsg, Mode, Submode))
    {
        Autopilot_Status_Before = Autopilot_Status;
        Autopilot_Status = UNKNOWN;
        Received_65379 = true;        
        if (Mode == 0x00 && Submode == 0x00) {
            // PILOT_MODE_STANDBY;
            Autopilot_Status = STANDBY;
        }
        else if (Mode == 0x40 && Submode == 0x00) {
            // PILOT_MODE_AUTO;
            Autopilot_Status = AUTO;
        }
        else if (Mode == 0x00 && Submode == 0x01) {
            // PILOT_MODE_WIND;
            Autopilot_Status = AUTOWIND;
        }

        else if (Mode == 0x81 && Submode == 0x01) {
            // PILOT_MODE_TRACK; PILOT_MODE_TURNWP 
            Autopilot_Status = AUTOTRACK;
        }

        else if (Mode == 0x80 && Submode == 0x01) {
            // PILOT_MODE_TRACK;
            Autopilot_Status = AUTOTRACK;
        }
        ToUpdateAutoPilotControlDisplay();
        Received_LockedHeading_inStandby = false;
    }
}

void raymarine_autopilot_pi::HandleN2K_65288(ObservedEvt ev) // Pilot Alarm
{
    if (AutoPilotType == SMARTPILOT) return;

    NMEA2000Id id_65288(65288);
    std::vector<uint8_t> msg = GetN2000Payload(id_65288, ev);
    tN2kMsg N2kMsg = MakeN2kMsg(msg);
    HandleN2kMsg_65288(N2kMsg);
}

void raymarine_autopilot_pi::HandleN2kMsg_65288(tN2kMsg N2kMsg)
{
    unsigned char AlarmStatus, AlarmCode, AlarmGroup;

    if (ParseN2kPGN65288(N2kMsg, AlarmStatus, AlarmCode, AlarmGroup))
    {
        if (AlarmStatus != 0)
        {
            if (AlarmCode == 5 && AlarmGroup == 1) // Off Course;
            {
                Autopilot_Status_Before = Autopilot_Status;
                AutoCOGStatus = false;
                Autopilot_Status = OFFCOURSE;
                ToUpdateAutoPilotControlDisplay();
            }
            if (AlarmCode == 21 && AlarmGroup == 1) // windshift
            {
                Autopilot_Status_Before = Autopilot_Status;
                AutoCOGStatus = false;
                Autopilot_Status = WINDSHIFT;
                ToUpdateAutoPilotControlDisplay();
            }
        }
    }
}

void raymarine_autopilot_pi::HandleN2K_65359(ObservedEvt ev) // Vessel heading, SeatalkNG 
{
    if (AutoPilotType == SMARTPILOT) return;

    NMEA2000Id id_65359(65359);
    std::vector<uint8_t> msg = GetN2000Payload(id_65359, ev);
    tN2kMsg N2kMsg = MakeN2kMsg(msg);
    HandleN2kMsg_65359(N2kMsg);
}

void raymarine_autopilot_pi::HandleN2kMsg_65359(tN2kMsg N2kMsg)
{
    double HeadingTrue, HeadingMagnetic;

    if (ParseN2kPGN65360(N2kMsg, HeadingTrue, HeadingMagnetic))
    {
        if (HeadingMagnetic != N2kDoubleNA)
        {
            MAGcourse = (int)RadToDeg(HeadingMagnetic);
            while (MAGcourse >= 360) MAGcourse -= 360;
            GetHeadingFromSeatalkNG = true;
            return;
        }
        if (HeadingTrue != N2kDoubleNA)
        {
            MAGcourse = (int)RadToDeg(HeadingMagnetic);
            if (BoatVariation != 0x01FF)
                MAGcourse -= BoatVariation; // Want Magnetc
            while (MAGcourse >= 360) MAGcourse -= 360;
            GetHeadingFromSeatalkNG = true;
            return;
        }
    }
}

void raymarine_autopilot_pi::HandleN2K_127250(ObservedEvt ev) // Vessel heading, standard NMEA2000
{
    if (AutoPilotType == SMARTPILOT) return;

    NMEA2000Id id_127250(127250);    
    std::vector<uint8_t> msg = GetN2000Payload(id_127250, ev);
    tN2kMsg N2kMsg = MakeN2kMsg(msg);
}

void raymarine_autopilot_pi::HandleN2kMsg_127250(tN2kMsg N2kMsg)
{
    if (GetHeadingFromSeatalkNG == true) return;

    unsigned char SID;
    double Heading, Deviation, Variation;
    tN2kHeadingReference ref;

    if (ParseN2kPGN127250(N2kMsg, SID, Heading, Deviation, Variation, ref))
    {
        if (Heading != N2kDoubleNA)
        {
            MAGcourse = (int)RadToDeg(Heading);
            if (ref != N2khr_magnetic && BoatVariation != 0x01FF)
                MAGcourse -= BoatVariation;
            while (MAGcourse >= 360) MAGcourse -= 360;
        }
    }
}
