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

raymarine_autopilot_pi::raymarine_autopilot_pi(void *ppimgr) :opencpn_plugin_117(ppimgr)
{
      // Create the PlugIn icons
      initialize_images();
	  m_bShowautopilot = false;
	  Autopilot_Status = UNKNOWN;
	  StandbySelfPressed = FALSE;
	  LastCompassCourse = -1; // Nicht gültig
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
	  m_pDialog = new Dlg(m_parent_window, Skalefaktor);
	  m_pDialog->plugin = this;
	  m_pDialog->Move(wxPoint(m_route_dialog_x, m_route_dialog_y));
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
	  //SetColorScheme(cs);

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
    SaveConfig();
    RequestRefresh(m_parent_window); // refresh mainn window 
    return true;
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
      return _("Raymarine autopilot");
}


wxString raymarine_autopilot_pi::GetShortDescription()
{
      return _("Raymarine autopilot Control for Raymarine Smartpilot");
}

wxString raymarine_autopilot_pi::GetLongDescription()
{
      return _("Autopilot Control for Raymarine Smartpilot\r\n\
Simulates a Remote Control (Commandos from ST600x), by sending Seatalk(1) Data.\r\n\
Requires Seatalk <-> NMEA Converter. The Sentences must be in the format\r\n\
$SENTENCENAME,Seatalkbytes in Hex. ( $STALK,84,36,9D,88,40,00,FF,02,06*02 )\r\n\
send to the NMEA Output Port. $SENTENCENAME named in the Preferences.");
}

int raymarine_autopilot_pi::GetToolbarToolCount(void)
{
      return 1;
}
/*
void raymarine_autopilot_pi::SetColorScheme(PI_ColorScheme cs)
{
      if (NULL == m_pDialog)
            return;

      DimeWindow(m_pDialog);
	  m_pDialog->Refresh(false);
}*/

void raymarine_autopilot_pi::OnToolbarToolCallback(int id)
{
      if(NULL == m_pDialog)
      {
            m_pDialog = new Dlg(m_parent_window, Skalefaktor);
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
            return true;
      }
      else
            return false;
}

void raymarine_autopilot_pi::ShowPreferencesDialog(wxWindow* parent)
{
	ParameterDialog *dialog = new ParameterDialog(this, parent, wxID_ANY, _("Autopilot Preferences"), wxPoint(m_route_dialog_x, m_route_dialog_y), wxDefaultSize, wxDEFAULT_DIALOG_STYLE);
	dialog->Fit();
	wxColour cl;
	DimeWindow(dialog);
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
	if (dialog->ShowModal() == wxID_OK)
	{
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
		if (NULL != m_pDialog)
		{
			wxPoint p = m_pDialog->GetPosition();
			SetCalculatorDialogX(p.x);
			SetCalculatorDialogY(p.y);
			m_pDialog->Close();
            delete m_pDialog;
			m_pDialog = new Dlg(m_parent_window,Skalefaktor);
			m_pDialog->plugin = this;
			m_pDialog->Move(wxPoint(m_route_dialog_x, m_route_dialog_y));
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
	if (ShowParameters)
	{
		// Visible
		m_pDialog->ParameterChoise->Show();
		m_pDialog->ParameterValue->Show();
		m_pDialog->buttonSet->Show();
		m_pDialog->StaticLine3->Show();
		m_pDialog->SetMaxSize(Skalefaktor * m_pDialog->FromDIP(wxSize(160, 220)));
		m_pDialog->SetSize(Skalefaktor * m_pDialog->FromDIP(wxSize(160, 220)));
		m_pDialog->SetMinSize(Skalefaktor * m_pDialog->FromDIP(wxSize(160, 220)));
	}
	else
	{
		m_pDialog->ParameterChoise->Show(FALSE);
		m_pDialog->ParameterValue->Show(FALSE);
		m_pDialog->buttonSet->Show(FALSE);
		m_pDialog->StaticLine3->Show(FALSE);
		m_pDialog->SetSize(Skalefaktor * m_pDialog->FromDIP(wxSize(160, 194)));
		m_pDialog->SetMinSize(Skalefaktor * m_pDialog->FromDIP(wxSize(160, 194)));
		m_pDialog->SetMaxSize(Skalefaktor * m_pDialog->FromDIP(wxSize(160, 194)));
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
    if ((WMM_receive_count < 30 && BoatVariation != 0x01FF) || !ModyfyRMC)  // Do not need so often.
        return;
	if (message_id == _T("WMM_VARIATION_BOAT"))
	{
		wxJSONReader r;
		wxJSONValue v;
		r.Parse(message_body, &v);
		BoatVariation = v[_T("Decl")].AsDouble();
        WMM_receive_count = 0;
	}	
}

void raymarine_autopilot_pi::SetNMEASentence(wxString &sentence_incomming)
{
	// SS & 0x80 : Displays "Auto Rel" on 600R  this is Next Waypoint ist Bearing !!!
	// 
	wxString sentence = sentence_incomming;
	int tmp;

	sentence.Trim(); // entferne Spaces
	if (m_pDialog == NULL)
		return;
	if (sentence.Mid(3, 3) == "RMB")
	{
		GetWaypointBearing(sentence);
		return;
	}
	if (sentence.Mid(3, 3) == "RMC" && ModyfyRMC)
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
	wxString Lsentence = "$" + STALKReceiveName + ",84",
		     Lsentence_Command = "$" + STALKReceiveName + ",86",
	         Lsentence_Response = "$" + STALKReceiveName + ",87",
		     Lsentence_Rudder = "$" + STALKReceiveName + ",91";

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
			Standbycommandreceived = TRUE;
			if (WriteMessages) wxLogMessage(("Received Standby Pressed from ST6001 %s"), sentence);
			NeedCompassCorrection = false;
		}
		else
		{
			if (WriteMessages) wxLogMessage(("Received Button Pressed from ST6001 %s"), sentence);
			NeedCompassCorrection = false;
		}
		return;
	}
	if (sentence.Left(9) != Lsentence) // Comes in 1 Second delay
		return;    
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
	if (CounterStandbySentencesReceived == 0) // falls noch kein Kommando gekommen ist, bleibt der alte Status.
		Autopilot_Status_Before = Autopilot_Status;
	m_pDialog->SetCopmpassTextColor(wxColour(0, 0, 64));
	m_pDialog->SetTextStatusColor(wxColour(0, 0, 128));
	Autopilot_Status = GetAutopilotMode(sentence);
	switch (Autopilot_Status)
	{
		case	AUTO:
			if (WriteDebug) wxLogInfo(("Received Auto %s"), sentence);
			if (Autopilot_Status_Before != Autopilot_Status)
			{
				// Nur für Logging
				if (WriteMessages) wxLogMessage("Auto-Status changed to AUTO");
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
				// Drücken der Standbytaste noch kam, und dadurch den "Standbycommandreceived Status wieder nach
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
					// Korrectur durchführen
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
						// Nicht mehr als 30 Grad Änderung !!
						if (WriteMessages) wxLogMessage("No Correction more than 30 degree");
						NeedCompassCorrection = false;
						break;
					}
					if (WriteMessages) wxLogMessage(("Correct Compass course from %i to %i"),tmp, LastCompassCourse);
					if (180 < abs(tmp - LastCompassCourse))
					{
						// Über Nodern ändern
						if (tmp > LastCompassCourse)
						{
							// Compasskurs muss über Norden mit PLus verändert werden. (bis 0 Grad.)
							if ((tmp - LastCompassCourse) >= 10)
							{
								// Mehr als 10 Grad differenz !! also +10 Grad ändern.
								if (WriteMessages) wxLogMessage("Over North + 10");
								Lsentence = "$" + STALKSendName + ",86,21,08,F7";
								SendNMEASentence(Lsentence);
							}
							else
							{
								// Weniger als 10 Grad ändern.
								if (WriteMessages) wxLogMessage("Over North + 1");
								Lsentence = "$" + STALKSendName + ",86,21,07,F8";
								SendNMEASentence(Lsentence);
							}
						}
						else
						{
							// Compasskurs von z.B. 5 nach 340 ... ändern mit Minus
							if ((LastCompassCourse - tmp) >= 10)
							{
								// Mehr als 10 Grad differenz !! also +10 Grad ändern.
								if (WriteMessages) wxLogMessage("Over North - 10");
								Lsentence = "$" + STALKSendName + ",86,21,06,F9";
								SendNMEASentence(Lsentence);
							}
							else
							{
								// Weniger als 10 Grad ändern.
								if (WriteMessages) wxLogMessage("Over North - 1");
								Lsentence = "$" + STALKSendName + ",86,21,05,FA";
								SendNMEASentence(Lsentence);
							}
						}
					}
					else
					{
						// Normale Änderung nicht über Norden.
						if (tmp > LastCompassCourse)
						{
							// Der Neue Compasskurs ist grösser als der alte also Verkleineren.
							if ((tmp - LastCompassCourse) >= 10)
							{
								// Mehr als 10 Grad differenz !! also +10 Grad ändern.
								if (WriteMessages) wxLogMessage("Korrectur - 10");
								Lsentence = "$" + STALKSendName + ",86,21,06,F9";
								SendNMEASentence(Lsentence);
							}
							else
							{
								// Weniger als 10 Grad ändern.
								if (WriteMessages) wxLogMessage("Korrectur - 1");
								Lsentence = "$" + STALKSendName + ",86,21,05,FA";
								SendNMEASentence(Lsentence);
							}
						}
						else
						{
							// Der neue Compass kurs ist kleiner als der alte. also Vergrössern.
							if ((LastCompassCourse - tmp) >= 10)
							{
								// Mehr als 10 Grad differenz !! also +10 Grad ändern.
								if (WriteMessages) wxLogMessage("Korrectur + 10");
								Lsentence = "$" + STALKSendName + ",86,21,08,F7";
								SendNMEASentence(Lsentence);
							}
							else
							{
								// Weniger als 10 Grad ändern.
								if (WriteMessages) wxLogMessage("Korrectur + 1");
								Lsentence = "$" + STALKSendName + ",86,21,07,F8";
								SendNMEASentence(Lsentence);
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
						m_pDialog->SetStatusText("Auto");
						m_pDialog->SetCompassText(GetAutopilotCompassCourse(sentence) + " ( " + GetAutopilotCompassDifferenz(sentence) + " )");
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
				// Drücken der Standbytaste noch kam, und dadurch den "Standbycommandreceived Status wieder nach
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
				// Nur für Logging
				if (WriteMessages) wxLogMessage("Auto-Status changed to AUTO-WIND");
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
				// Drücken der Standbytaste noch kam, und dadurch den "Standbycommandreceived Status wieder nach
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
				// Nur für Logging
				if (WriteMessages) wxLogMessage("Auto-Status .... Windshift received");
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
				Lsentence = "$" + STALKSendName + ",86,21,23,DC";
				SendNMEASentence(Lsentence);
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
				// Nur für Logging
				if (WriteMessages) wxLogMessage("Auto-Status .... Off-Course received");
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
				// Nur für Logging
				if (WriteMessages) wxLogMessage("Auto-Status changed to STANDBY");
			}
			if (Autopilot_Status_Before != STANDBY &&
				NewStandbyNoStandbyReceived == TRUE &&  // Sool Überhaupt ein Neues Standby gesendent werden ?
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
					Autopilot_Status = Autopilot_Status_Before; // Dadurch werden mehrere Seqnenzen gesendet, wenn nötig.
					if (Autopilot_Status_Before == AUTO)
					{
						if (WriteMessages) wxLogMessage("---------------Send New Auto------------");
						Lsentence = "$" + STALKSendName + ",86,21,01,FE";
						if (ChangeValueToLast == true)
						{
							// Kurskorrectur durchführen
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
						Lsentence = "$" + STALKSendName + ",86,21,23,DC";
					}
					if (Autopilot_Status_Before == AUTOTRACK)
					{
						if (WriteMessages) wxLogMessage("-------------Send New Auto-Track--------");
						Lsentence = "$" + STALKSendName + ",86,21,03,FC";
					}
					SendNMEASentence(Lsentence);
					// FehlerCounter hohchzählen.
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
			if (Autopilot_Status_Before == AUTO || Autopilot_Status_Before == AUTOWIND) // Zustandänderung von Auto -> Standby
			{
				CounterStandbySentencesReceived = 0;
				if (StandbySelfPressed == FALSE &&
					NewAutoOnStandby == TRUE)  // Generell neues Auto Senden, wenn nicht von hier gesendet.
					                           // Ignoriert St6001 Standby Signal !! Vorsiht.
				{
					// Standby not from here !! goto AUTO
					//
					if (WriteMessages) wxLogMessage(("Selfpressed = False, Auto-Status-before = Auto or Autowind %s"), sentence);
					if (WriteMessages) wxLogMessage("---------------Send New Auto------------");
					IS_standby = 0;
					Standbycommandreceived = FALSE;
					CounterStandbySentencesReceived = 0;
					Lsentence = "$" + STALKSendName + ",86,21,01,FE";
					SendNMEASentence(Lsentence);
					if (ChangeValueToLast == true)
					{
						// Kurskorrectur durchführen
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
			break;
	}
}

bool raymarine_autopilot_pi::ConfirmNextWaypoint(const wxString &sentence)
{
	if (sentence.Mid(28, 2) == "02")
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
				wxString sentence = "$" + STALKSendName + ",86,21,03,FC";
				SendNMEASentence(sentence);
				if (WriteMessages) wxLogMessage(("Send Track automatic %s"), sentence);
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
			WayPointBearing += " °";
			return;
		}
	}
	WayPointBearing = "unknown";
	return;
}

int raymarine_autopilot_pi::GetAutopilotMode(wxString &sentence)
{
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


wxString raymarine_autopilot_pi::GetAutopilotCompassCourse(wxString &sentence)
{
	
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

wxString raymarine_autopilot_pi::GetAutopilotMAGCourse(wxString &sentence)
{

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
			return(wxString::Format(wxT("%i"), CompassValue));
		}
	}
	return ("---"); // Nicht def
}

wxString raymarine_autopilot_pi::GetAutopilotCompassDifferenz(wxString &sentence)
{

	wxString s = sentence, HexValue;

	s.Trim();
	unsigned char parameter[3] = { 0x00, 0x00, 0x00 };
	int sLenght = s.Length();
	int i = 0, CompassValue = -1, AutoValue = -1, ReturnCompassValue;

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
	if (sentence_incomming.GetChar(1) == 'E' && sentence_incomming.GetChar(2) == 'C')
		return; // is My sentence
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

localTimer::localTimer(raymarine_autopilot_pi *pAuto)
{
	pAutopilot = pAuto;
}

void localTimer::Notify()
{
	// Keine Informationen vom Kurscomputer
	if (pAutopilot->WriteMessages) wxLogInfo("No Data from Autopilot Computer");
	pAutopilot->Autopilot_Status = UNKNOWN;
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
	}
}
