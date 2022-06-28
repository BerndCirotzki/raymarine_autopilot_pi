/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  autopilot Plugin
 * Author:   Dipl. Ing. Bernd Cirotzki
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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */

#ifndef _CALCULATORGUI_IMPL_H_
#define _CALCULATORGUI_IMPL_H_

#ifdef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "autopilotgui.h"
#include "autopilot_pi.h"

#include <list>
#include <vector>

using namespace std;

class raymarine_autopilot_pi;

class Position;

class ParameterDialog : public m_Parameterdialog
{
public:
	ParameterDialog(raymarine_autopilot_pi* p, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style);
	void OnStandbyCounterReset(wxCommandEvent& event);
	void OnNewAuto(wxCommandEvent& event);
private:
	raymarine_autopilot_pi* ptoPlugin;
};
	
class Dlg : public m_dialog
{
public:
        Dlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Autopilot Control"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

        void OnPSGPX( wxCommandEvent& event );		
		bool OpenXML();
		
		vector<Position> my_positions;
		vector<Position> my_points;

		//void OnGenerate(autopilot_pi& a);
		void OnKlickInDisplay(wxMouseEvent& event);
		void OnAuto(wxCommandEvent& event);
		void OnAutoWind(wxCommandEvent& event);
		void OnTrack(wxCommandEvent& event);
		void OnDecrementOne(wxCommandEvent& event);
		void OnDecrementTen(wxCommandEvent& event);
		void OnIncrementTen(wxCommandEvent& event);
		void OnIncrementOne(wxCommandEvent& event);
		void OnStandby(wxCommandEvent& event);
		void OnActiveApp(wxCommandEvent& event);
		void SetStatusText(wxString Text);
		void SetCompassText(wxString Text);
		void SetTextStatusColor(wxColour Color);
		void SetCopmpassTextColor(wxColour Color);
		void SetBgTextStatusColor(wxColour Color);
		void SetBgTextCompassColor(wxColour Color);
		void OnSetParameterValue(wxCommandEvent& event);
		void OnSelectParameter(wxCommandEvent& event);
		void OnCloseApp(wxCloseEvent& event);
		raymarine_autopilot_pi *plugin; 

		wxString rte_start;
	    wxString rte_end;

private:
	    void OnClose( wxCloseEvent& event );
        double lat1, lon1, lat2, lon2;
        bool error_found;
        bool dbg;
		wxString     m_gpx_path;
		short int SetToggel;
};


class Position
{
public:

    wxString lat, lon, wpt_num;
    Position *prev, *next; /* doubly linked circular list of positions */
    int routepoint;

};

#endif
