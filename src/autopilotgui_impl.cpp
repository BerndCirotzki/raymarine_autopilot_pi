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


ParameterDialog::ParameterDialog(raymarine_autopilot_pi* p, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : m_Parameterdialog(parent, id, title, pos, size, style)
{
	ptoPlugin = p;
}

void ParameterDialog::OnStandbyCounterReset(wxCommandEvent& event)
{
	m_NoStandbyCounter->SetValue(wxString::Format(wxT("%i"), 0));
	ptoPlugin->NoStandbyCounter = 0;
	if(ptoPlugin->m_pDialog != NULL)
		ptoPlugin->m_pDialog->SetBackgroundColour(wxColour(255,255,225));
	ptoPlugin->Standbycommandreceived = TRUE;
}

void ParameterDialog::OnNewAuto(wxCommandEvent& event)
{
    if (m_AutopilotType->GetSelection() != SMARTPILOT)
        return;
	if (m_SendNewAutoonStandby->GetValue() == TRUE)
	{
		m_NewStandbyNoStandbyReceived->Enable(false);
		m_NoStandbyCounter->Enable(false);
		m_NoStandbyCounterValueText->Enable(false);
		m_SelectCounterStandby->Enable(false);
		m_ResetStandbyCounter->Enable(false);
		m_SelectCounterStandby->Enable(false);
		m_Text->Enable(false);
		ptoPlugin->NewStandbyNoStandbyReceived = FALSE;
	}
	else
	{
		m_NewStandbyNoStandbyReceived->Enable(true);
		m_NoStandbyCounter->Enable(true);
		m_NoStandbyCounterValueText->Enable(true);
		m_SelectCounterStandby->Enable(true);
		m_ResetStandbyCounter->Enable(true);
		m_SelectCounterStandby->Enable(true);
		m_Text->Enable(true);
	}
}

void ParameterDialog::OnAutoCogchange(wxCommandEvent& event)
{
    if (m_allowautocog->GetValue() == false)
    {
        m_sensebilitytext->Enable(false);
        m_cogsensibility->Enable(false);
        m_slowtext->Enable(false);
        m_fast->Enable(false);
        m_maxdegreediff->Enable(false);
        m_maxdegtext->Enable(false);
        m_minspeedcog->Enable(false);
        m_minspeed->Enable(false);
        m_maxchangehdg->Enable(false);
        m_maxchangehdgtext->Enable(false);
    }
    else
    {
        m_sensebilitytext->Enable(true);
        m_cogsensibility->Enable(true);
        m_slowtext->Enable(true);
        m_fast->Enable(true);
        m_maxdegreediff->Enable(true);
        m_maxdegtext->Enable(true);
        m_minspeedcog->Enable(true);
        m_minspeed->Enable(true);
        m_maxchangehdg->Enable(true);
        m_maxchangehdgtext->Enable(true);
    }
}

void ParameterDialog::OnChoiceAutoPilot(wxCommandEvent& event)
{
    if (m_AutopilotType->GetSelection() == EVO || m_AutopilotType->GetSelection() == EVOSEASMART)
    {  
        m_checkParameters->Enable(false);
        m_ChangeValueToLast->Enable(false);
        m_SendTrack->Enable(false);
        m_TimeToSendNewWaypiont->Enable(false);
        m_NewStandbyNoStandbyReceived->Enable(false);
        m_NoStandbyCounter->Enable(false);
        m_NoStandbyCounterValueText->Enable(false);
        m_SelectCounterStandby->Enable(false);
        m_ResetStandbyCounter->Enable(false);
        m_SelectCounterStandby->Enable(false);
        m_Text->Enable(false);
        m_STALKreceivename->Enable(false);
        m_staticText11->Enable(false);
        m_STALKsendname->Enable(false);
        m_staticText21->Enable(false);
        m_Text1->Enable(false);
        m_NoStandbyCounterValueText1->Enable(false);
        m_ModyfyRMC->SetLabel(_("Send variation PNG 127258 to N2K/SeatalkNG with the value from WMM Plugin"));
        m_SendNewAutoonStandby->SetLabel(_("Send PGN 126720 (keystroke) instead of PGN 126208 (set heading) in AutoMode"));
    }
    else
    {        
        m_checkParameters->Enable(true);
        m_ChangeValueToLast->Enable(true);
        m_SendTrack->Enable(true);
        m_TimeToSendNewWaypiont->Enable(true);
        m_NewStandbyNoStandbyReceived->Enable(true);
        m_NoStandbyCounter->Enable(true);
        m_NoStandbyCounterValueText->Enable(true);
        m_SelectCounterStandby->Enable(true);
        m_ResetStandbyCounter->Enable(true);
        m_SelectCounterStandby->Enable(true);
        m_Text->Enable(true);
        m_STALKreceivename->Enable(true);
        m_staticText11->Enable(true);
        m_STALKsendname->Enable(true);
        m_staticText21->Enable(true);
        m_Text1->Enable(true);
        m_NoStandbyCounterValueText1->Enable(true);
        m_ModyfyRMC->SetLabel(_("Modify RMC Sentence as \"$ECRMC\" and replace or fill with Variationfield with the value from WMM Plugin"));
        m_SendNewAutoonStandby->SetLabel(_("Send new \"Auto\" or \"Auto - Wind\" Command, when \"Standby\" is not send from here, but the \"Auto\" was from here"));
    }
}

Dlg::Dlg( wxWindow* parent, double Skalefaktor, long style, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size) : m_dialog( parent, Skalefaktor, id, title, pos, size, style )
{	
    this->Fit();
	SetToggel = 0;    
    m_parent = parent;
    Connect(wxEVT_CONTEXT_MENU,
        wxContextMenuEventHandler(Dlg::OnContextMenu), NULL,
        this);
    Connect(wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(Dlg::OnContextMenuSelect), NULL,
        this);
}

void Dlg::SetStatusText(wxString Text)
{
	this->TextStatus->SetValue(Text);
}
void Dlg::SetCompassText(wxString Text)
{
	if (plugin->NoStandbyCounter != 0)
	{
		// No Standby Fehler ist aktiv
		SetToggel++;
		if (SetToggel >= 3)
		{
			SetToggel = 0;
			this->TextCompass->SetValue(_T("klick to reset"));
			this->TextStatus->Refresh();
			this->TextCompass->Refresh();
			return;
		}
	}
	this->TextCompass->SetValue(Text);
}

void Dlg::SetCopmpassTextColor(wxColour Color)
{
	this->TextCompass->SetForegroundColour(Color);
}

void Dlg::SetTextStatusColor(wxColour Color)
{
	this->TextStatus->SetForegroundColour(Color);
}

void Dlg::SetBgTextStatusColor(wxColour Color)
{
	this->TextStatus->SetBackgroundColour(Color);
}

void Dlg::SetBgTextCompassColor(wxColour Color)
{
	this->TextCompass->SetBackgroundColour(Color);
}

void Dlg::OnClose(wxCloseEvent& event)
{	
	plugin->OnautopilotDialogClose();
}

void Dlg::OnCloseApp(wxCloseEvent& event)
{
	plugin->OnautopilotDialogClose();
}

void Dlg::OnKlickInDisplay(wxMouseEvent& event)
{
	if(plugin->Autopilot_Status == UNKNOWN)
		this->TextCompass->SetValue("---");
	SetBgTextCompassColor(wxColour(255, 255, 225));
	SetBgTextStatusColor(wxColour(255, 255, 225));
	TextStatus->Refresh();
	TextCompass->Refresh();
	plugin->NoStandbyCounter = 0;
	plugin->Standbycommandreceived = TRUE;
	plugin->NeedCompassCorrection = false;
    plugin->DeActivateAutoCOG();
}

void Dlg::OnAuto(wxCommandEvent& event)
{
    plugin->AutoCOGHeadingChange = 0;
    if (plugin->Autopilot_Status == AUTO && plugin->allowautocog)
    {
        // AutoCOG aktivieren
        plugin->ActivateAutoCOG();
        return;
    }
    plugin->SendGotoAuto();
	if (plugin->WriteMessages) wxLogMessage(" Pushed Auto");
	plugin->NeedCompassCorrection = false;
}

void Dlg::OnAutoWind(wxCommandEvent& event)
{
    plugin->SendGotoAutoWind();	
	if (plugin->WriteMessages) wxLogMessage(" Pushed Autowind");
	plugin->NeedCompassCorrection = false;
    plugin->DeActivateAutoCOG();    
}

void Dlg::OnTrack(wxCommandEvent& event)
{
	if (plugin->Autopilot_Status == STANDBY)
	{
		plugin->DisplayShow = 1;
		this->TextStatus->SetForegroundColour(wxColour(255, 0, 0));
		this->TextStatus->SetValue("Not in Auto");
		return;
	}
    plugin->SendGotoAutoTrack();	
	if (plugin->WriteMessages) wxLogMessage(" Pushed Track");
	plugin->NeedCompassCorrection = false;
    plugin->DeActivateAutoCOG();    
}

void Dlg::OnStandby(wxCommandEvent& event)
{
	plugin->StandbySelfPressed = TRUE;
	plugin->Standbycommandreceived = TRUE;
	plugin->NeedCompassCorrection = false;
	plugin->SendGotoStandby();	
	if (plugin->Autopilot_Status == STANDBY)
	{
		if (plugin->WriteMessages) wxLogMessage(" Pushed Standby in Standby-Mode");
	}
	else
	{
		if (plugin->WriteMessages) wxLogMessage(" Pushed Standby");
	}
    plugin->DeActivateAutoCOG();    
}

void Dlg::OnDecrementOne(wxCommandEvent& event)
{
    if (plugin->Autopilot_Status == AUTO ||
        plugin->Autopilot_Status == AUTOWIND)
        plugin->SendDecrementOne();
	plugin->NeedCompassCorrection = false;
    if (plugin->AutoCOGStatus == true)
    {
        plugin->COGCourse--;
        if (plugin->COGCourse < 0) plugin->COGCourse = 359;
    }
	if (plugin->WriteMessages) wxLogMessage(" Pushed -1");
    plugin->AutoCOGHeadingChange = 0;
}

void Dlg::OnDecrementTen(wxCommandEvent& event)
{
	if (plugin->Autopilot_Status == AUTO ||
        plugin->Autopilot_Status == AUTOWIND)
        plugin->SendDecrementTen();		
	plugin->NeedCompassCorrection = false;
    if (plugin->AutoCOGStatus == true)
    {
        plugin->COGCourse -= 10;
        if (plugin->COGCourse < 0) plugin->COGCourse += 360;
    }
	if (plugin->WriteMessages) wxLogMessage(" Pushed -10 ");
    plugin->AutoCOGHeadingChange = 0;
}

void Dlg::OnIncrementTen(wxCommandEvent& event)
{
    if (plugin->Autopilot_Status == AUTO ||
        plugin->Autopilot_Status == AUTOWIND)
        plugin->SendIncrementTen();
	plugin->NeedCompassCorrection = false;
    if (plugin->AutoCOGStatus == true)
    {
        plugin->COGCourse +=10;
        if (plugin->COGCourse >= 360) plugin->COGCourse -= 360;
    }
	if (plugin->WriteMessages) wxLogMessage(" Pushed +10 ");
    plugin->AutoCOGHeadingChange = 0;
}

void Dlg::OnIncrementOne(wxCommandEvent& event)
{	
	if (plugin->Autopilot_Status == AUTO ||
		plugin->Autopilot_Status == AUTOWIND)
		plugin->SendIncrementOne();
	plugin->NeedCompassCorrection = false;
    if (plugin->AutoCOGStatus == true)
    {
        plugin->COGCourse++;
        if (plugin->COGCourse >= 360) plugin->COGCourse -= 360;
    }
	if (plugin->WriteMessages) wxLogMessage(" Pushed +1");
    plugin->AutoCOGHeadingChange = 0;
}

void Dlg::OnActiveApp(wxCommandEvent& event)
{
	this->TextStatus->SetValue("----");
}

void Dlg::OnSetParameterValue(wxCommandEvent& event)
{
    if (plugin->AutoPilotType != SMARTPILOT)
        return;
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
    if (plugin->AutoPilotType != SMARTPILOT)
        return;
	wxString Sentence;
	// Set To DefaultValue because the aktive is not konwn.
	switch (this->ParameterChoise->GetSelection())
	{
	case	0:
		this->ParameterValue->SetSelection(0);
		break;
	case	1:	// Response
		// old : this->ParameterValue->SetSelection(plugin->ResponseLevel);
		// Anzeige auf ST6002 Display für 5 Sekunden
		Sentence = "$" + plugin->STALKSendName + ",86,21,2E,D1"; // (Response Display)
		plugin->SendNMEASentence(Sentence);
		break;
	case	2:	// WindTrim
		this->ParameterValue->SetSelection(5);
		break;
	case	3:  // Ruddergain
		// old : this->ParameterValue->SetSelection(2);
		// Anzeige auf ST6002 Display für 5 Sekunden
		Sentence = "$" + plugin->STALKSendName + ",86,21,6E,91"; // (Rudder Gain Display)
		plugin->SendNMEASentence(Sentence);
		break;
	}
}

void Dlg::OnContextMenu(wxContextMenuEvent& event)
{
    wxMenu* contextMenu = new wxMenu();

    if (plugin->DialogStyle)
    {
        contextMenu->Append(1, _("Dock Window"));        
    }
    else
    {
        contextMenu->Append(1, _("Undock Window"));       
    }
    contextMenu->AppendSeparator();
    contextMenu->Append(0, _("Close Window"));
    contextMenu->AppendSeparator();
    contextMenu->Append(2, _("Preferences..."));
    PopupMenu(contextMenu);

    delete contextMenu;
}

void Dlg::OnContextMenuSelect(wxCommandEvent& event)
{
    switch (event.GetId()) {
    case 0: {
        Hide();
        return;
    }
    case 1: {
        wxPoint p = GetPosition();
        plugin->SetCalculatorDialogX(p.x);
        plugin->SetCalculatorDialogY(p.y);
        if (plugin->DialogStyle)
        {
            plugin->DialogStyle = 0;
            plugin->m_route_dialog_x += 6;
        }
        else
        {
            plugin->DialogStyle = wxDEFAULT_DIALOG_STYLE;
            if ((plugin->m_route_dialog_x -= 6) < 0) plugin->m_route_dialog_x = 0;
        }
        wxWindow* pW = plugin->m_pDialog->m_parent;
        plugin->m_pDialog = NULL;
        plugin->m_pDialog = new Dlg(pW, plugin->Skalefaktor, plugin->DialogStyle);
        plugin->m_pDialog->plugin = plugin;
        plugin->m_pDialog->Move(wxPoint(plugin->m_route_dialog_x, plugin->m_route_dialog_y));
        if (plugin->Autopilot_Status == AUTO && plugin->allowautocog == true && plugin->AutoCOGStatus == false)
        {
            plugin->m_pDialog->buttonAuto->SetLabel("AutoCOG");
            plugin->m_pDialog->buttonAuto->SetBackgroundColour(wxColour(148, 88, 167));
        }
        if (plugin->m_bShowautopilot)
            plugin->m_pDialog->Show();
        plugin->SetAutopilotparametersChangeable();
        delete this;
        return;
    }
    case 2: {
        plugin->ShowPreferencesDialog(m_parent);
        return;  // Does it's own save.
    }
    }
}

