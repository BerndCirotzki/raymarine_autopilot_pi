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

#include "version.h"

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    7

#define AUTO		1
#define STANDBY		2
#define AUTOWIND	3
#define TRACK		4
#define	WINDSHIFT	5
#define AUTOTRACK	6
#define UNKNOWN		0


class Dlg;
class localTimer;

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

#define CALCULATOR_TOOL_POSITION    -1          // Request default positioning of toolbar tool

class raymarine_autopilot_pi : public opencpn_plugin_17
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
      wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();
	  void SetNMEASentence(wxString &sentence);

//    The required override PlugIn Methods
      int GetToolbarToolCount(void);
	  void ShowPreferencesDialog(wxWindow* parent);
      void OnToolbarToolCallback(int id);
     

//    Optional plugin overrides
      void SetColorScheme(PI_ColorScheme cs);


//    The override PlugIn Methods

//    Other public methods
      void SetCalculatorDialogX         (int x){ m_route_dialog_x = x;};
      void SetCalculatorDialogY         (int x){ m_route_dialog_y = x;};
      void SetCalculatorDialogWidth     (int x){ m_route_dialog_width = x;};
      void SetCalculatorDialogHeight    (int x){ m_route_dialog_height = x;};      
	  void OnautopilotDialogClose();
	  int			   Autopilot_Status;
	  int			   Autopilot_Status_Before;
	  int			   DisplayShow; // Anzahl ser $STALK,84, ... Sequenzen, bis wider Werte anzezeigt werden.
	  bool			   ShowParameters;
	  bool			   NewAutoWindCommand;
	  bool			   NewAutoOnStandby;
	  bool			   SendSNBSE;
	  wxString	       STALKSendName;
	  wxString		   STALKReceiveName;
	  bool			   StandbySelfPressed;
	  Dlg				*m_pDialog;

private:
      
	  void OnClose( wxCloseEvent& event );
	  int GetAutopilotMode(wxString &sentence);
	  wxString GetAutopilotCompassCourse(wxString &sentence);
	  wxString GetAutopilotMAGCourse(wxString &sentence);
	  char GetHexValue(char AsChar);
	  void SetAutopilotparametersChangeable();
	  raymarine_autopilot_pi *plugin;
  
	  wxFileConfig      *m_pconfig;
      wxWindow          *m_parent_window;
      bool              LoadConfig(void);
      bool              SaveConfig(void);
      int               m_route_dialog_x, m_route_dialog_y,m_route_dialog_width,m_route_dialog_height;
      int               m_display_width, m_display_height;      
      int               m_leftclick_tool_id;
      bool              m_ShowHelp,m_bCaptureCursor,m_bCaptureShip;
      double			m_ship_lon,m_ship_lat,m_cursor_lon,m_cursor_lat;
	  bool             m_bautopilotShowIcon;
	  bool             m_bShowautopilot;
	  wxTimer		   *p_Resettimer;
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


#endif
