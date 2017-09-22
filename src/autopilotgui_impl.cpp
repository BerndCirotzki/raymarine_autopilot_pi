/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  autopilot Plugin
 * Author:   Dipl.Ing. Bernd Cirotzki
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

#include "autopilotgui_impl.h"
#include <wx/progdlg.h>
#include <wx/wx.h>
#include "wx/dir.h"
#include <list>
#include <cmath>
#include "autopilot_pi.h"


class Position;

#define FAIL(X) do { error = X; goto failed; } while(0)


Dlg::Dlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : m_dialog( parent, id, title, pos, size, style )
{	
    this->Fit();
    dbg=false; //for debug output set to true
}

void Dlg::SetStatusText(wxString Text)
{
	this->TextStatus->SetValue(Text);
}
void Dlg::SetCompassText(wxString Text)
{
	this->TextCompass->SetValue(Text);
}

void Dlg::SetCopmpassTextColor(wxColour Color)
{
	this->TextCompass->SetForegroundColour(wxColour(0, 0, 64));
}

void Dlg::SetTextStatusColor(wxColour Color)
{
	this->TextStatus->SetForegroundColour(wxColour(0, 0, 128));
}


void Dlg::OnClose(wxCloseEvent& event)
{	
	plugin->OnautopilotDialogClose();
}

void Dlg::OnAuto(wxCommandEvent& event)
{
	wxString sentence = "$" + plugin->STALKSendName + ",86,21,01,FE";
	plugin->SendNMEASentence(sentence);
}

void Dlg::OnAutoWind(wxCommandEvent& event)
{
	wxString sentence = "$" + plugin->STALKSendName + ",86,21,23,DC";
	plugin->SendNMEASentence(sentence);
}

void Dlg::OnTrack(wxCommandEvent& event)
{
	wxString sentence = "$" + plugin->STALKSendName + ",86,21,03,FC";
	plugin->SendNMEASentence(sentence);
}

void Dlg::OnStandby(wxCommandEvent& event)
{
	wxString sentence;
	plugin->StandbySelfPressed = TRUE;
	if (plugin->Autopilot_Status == AUTOWIND)
	{
		sentence = "$" + plugin->STALKSendName + ",86,21,01,FE";
		plugin->SendNMEASentence(sentence);
	}
	sentence = "$" + plugin->STALKSendName + ",86,21,02,FD";
	plugin->SendNMEASentence(sentence);
}

void Dlg::OnDecrementOne(wxCommandEvent& event)
{
	wxString sentence = "$" + plugin->STALKSendName + ",86,21,05,FA";
	if (plugin->Autopilot_Status == AUTO ||
		plugin->Autopilot_Status == AUTOWIND)
		plugin->SendNMEASentence(sentence);
}

void Dlg::OnDecrementTen(wxCommandEvent& event)
{
	wxString sentence = "$" + plugin->STALKSendName + ",86,21,06,F9";
	if (plugin->Autopilot_Status == AUTO ||
		plugin->Autopilot_Status == AUTOWIND)
		plugin->SendNMEASentence(sentence);
}

void Dlg::OnIncrementTen(wxCommandEvent& event)
{
	wxString sentence = "$" + plugin->STALKSendName + ",86,21,08,F7";
	if (plugin->Autopilot_Status == AUTO ||
		plugin->Autopilot_Status == AUTOWIND)
		plugin->SendNMEASentence(sentence);
}

void Dlg::OnIncrementOne(wxCommandEvent& event)
{
	wxString sentence = "$" + plugin->STALKSendName + ",86,X1,07,F8";
	if (plugin->Autopilot_Status == AUTO ||
		plugin->Autopilot_Status == AUTOWIND)
		plugin->SendNMEASentence(sentence);
}

void Dlg::OnActiveApp(wxCommandEvent& event)
{
	this->TextStatus->SetValue("----");
}

void Dlg::OnSetParameterValue(wxCommandEvent& event)
{
	int Value;

	if (plugin->DisplayShow > 0)   // Es wurde gerade ein Parameter gesetzt.
	{
		plugin->DisplayShow--;   // trotdem einen weniger !!
		return;
	}
	if (0 >= (Value = this->ParameterValue->GetSelection()))
	{
		wxMessageBox(_("No Value selected"));
		return;
	}
	if (0 >= this->ParameterChoise->GetSelection())
	{
		wxMessageBox(_("No Parameter selected"));
		return;
	}
	wxString i = _("is set to  "), Sentence;

	this->TextStatus->SetValue(this->ParameterChoise->GetString(this->ParameterChoise->GetSelection()));
	i = i + this->ParameterValue->GetString(this->ParameterValue->GetSelection());
	this->TextCompass->SetValue(i);
	this->TextCompass->SetForegroundColour(wxColour(255, 0, 0));
	this->TextStatus->SetForegroundColour(wxColour(255, 0, 0));
	plugin->DisplayShow = 2;

	switch (this->ParameterChoise->GetSelection())
	{
	case	1:	// Response
		Sentence = "$" + plugin->STALKSendName + ",92,02,12,0" + wxString::Format(wxT("%i"), Value) + ",00";
		plugin->SendNMEASentence(Sentence);
		// Anzeige auf ST6002 Display für 5 Sekunden
		Sentence = "$" + plugin->STALKSendName + ",86,21,2E,D1";
		plugin->SendNMEASentence(Sentence);
		break;
	case	2:	// WindTrim
		Sentence = "$" + plugin->STALKSendName + ",92,02,11,0" + wxString::Format(wxT("%i"), Value) + ",00";
		plugin->SendNMEASentence(Sentence);
		break;
	case	3:  // Ruddergain
		Sentence = "$" + plugin->STALKSendName + ",92,02,01,0" + wxString::Format(wxT("%i"), Value) + ",00";
		plugin->SendNMEASentence(Sentence);
		// Anzeige auf ST6002 Display für 5 Sekunden
		Sentence = "$" + plugin->STALKSendName + ",86,21,6E,91";
		plugin->SendNMEASentence(Sentence);
		break;
	}
}

void Dlg::OnSelectParameter(wxCommandEvent& event)
{
	// Set To DefaultValue because the aktive is not konwn.
	switch (this->ParameterChoise->GetSelection())
	{
	case	0:
		this->ParameterValue->SetSelection(0);
		break;
	case	1:	// Response
		this->ParameterValue->SetSelection(5);
		break;
	case	2:	// WindTrim
		this->ParameterValue->SetSelection(5);
		break;
	case	3:  // Ruddergain
		this->ParameterValue->SetSelection(2);
		break;
	}
}
