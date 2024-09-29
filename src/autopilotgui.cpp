///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
///////////////////////////////////////////////////////////////////////////

#include "autopilotgui.h"

///////////////////////////////////////////////////////////////////////////

m_dialog::m_dialog(wxWindow* parent, double Skalefaktor, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxDialog(parent, id, title, pos, size, style, name)
{
	this->SetSizeHints(Skalefaktor * FromDIP(wxSize(160, 194)), Skalefaktor * FromDIP(wxSize(160, 220)));
	this->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
	this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer(wxVERTICAL);
	StaticLine1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, Skalefaktor * FromDIP(wxSize(-1, 2)), wxLI_HORIZONTAL);
	StaticLine1->SetMinSize(FromDIP(wxSize(-1, Skalefaktor * 2)));
	StaticLine1->SetMaxSize(FromDIP(wxSize(-1, Skalefaktor * 2)));

	bSizer10->Add(StaticLine1, 0, wxEXPAND | wxALL, 3);

	TextStatus = new wxTextCtrl(this, wxID_ANY, ("----------"), wxDefaultPosition, Skalefaktor * FromDIP(wxSize(120, 30)), wxTE_CENTER | wxTE_READONLY);
	TextStatus->SetFont(wxFont(Skalefaktor * 13, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
	TextStatus->SetForegroundColour(wxColour(0, 0, 128));
	TextStatus->SetBackgroundColour(wxColour(255, 255, 225));

	bSizer10->Add(TextStatus, 0, wxALIGN_CENTER_HORIZONTAL, 5);

	TextCompass = new wxTextCtrl(this, wxID_ANY, ("---"), wxDefaultPosition, Skalefaktor * FromDIP(wxSize(120, 20)), wxTE_READONLY | wxTE_CENTER);
	TextCompass->SetFont(wxFont(Skalefaktor * 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
	TextCompass->SetForegroundColour(wxColour(0, 0, 64));
	TextCompass->SetBackgroundColour(wxColour(255, 255, 225));

	bSizer10->Add(TextCompass, 0, wxALIGN_CENTER_HORIZONTAL, 5);

	StaticLine2 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, Skalefaktor * FromDIP(wxSize(-1, 2)), wxLI_HORIZONTAL);
	StaticLine2->SetMaxSize(FromDIP(wxSize(-1, Skalefaktor * 2)));

	bSizer10->Add(StaticLine2, 0, wxALL | wxEXPAND, 4);

	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer(0, 3, 0, 0);
	fgSizer4->SetFlexibleDirection(wxBOTH);
	fgSizer4->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxString ParameterChoiseChoices[] = { ("------------"), ("Response"), ("WindTrim"), ("RudderGain") };
	int ParameterChoiseNChoices = sizeof(ParameterChoiseChoices) / sizeof(wxString);
	ParameterChoise = new wxChoice(this, wxID_ANY, wxDefaultPosition, Skalefaktor * FromDIP(wxSize(69, 18)), ParameterChoiseNChoices, ParameterChoiseChoices, 0);
	ParameterChoise->SetSelection(3);
	ParameterChoise->SetFont(wxFont(Skalefaktor * 6, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
	ParameterChoise->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
	ParameterChoise->SetMinSize(FromDIP(wxSize(Skalefaktor * 69, -1)));

	fgSizer4->Add(ParameterChoise, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 0);

	wxString ParameterValueChoices[] = { ("-"), ("1"), ("2"), ("3"), ("4"), ("5"), ("6"), ("7"), ("8"), ("9") };
	int ParameterValueNChoices = sizeof(ParameterValueChoices) / sizeof(wxString);
	ParameterValue = new wxChoice(this, wxID_ANY, wxDefaultPosition, Skalefaktor * FromDIP(wxSize(28, 18)), ParameterValueNChoices, ParameterValueChoices, 0);
	ParameterValue->SetSelection(5);
	ParameterValue->SetFont(wxFont(Skalefaktor * 6, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
	ParameterValue->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
	ParameterValue->SetMinSize(FromDIP(wxSize(Skalefaktor * 28, -1)));

	fgSizer4->Add(ParameterValue, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_CENTER_HORIZONTAL, 0);

	buttonSet = new wxButton(this, wxID_ANY, _("Set"), wxDefaultPosition, Skalefaktor * FromDIP(wxSize(38, 18)), 0);
	buttonSet->SetFont(wxFont(Skalefaktor * 6, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
	buttonSet->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
	buttonSet->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER));
	buttonSet->SetMinSize(Skalefaktor * FromDIP(wxSize(38, 18)));

	fgSizer4->Add(buttonSet, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 0);

	bSizer10->Add(fgSizer4, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);

	StaticLine3 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, Skalefaktor * FromDIP(wxSize(-1, 2)), wxLI_HORIZONTAL);
	StaticLine3->SetMaxSize(FromDIP(wxSize(-1, Skalefaktor * 2)));

	bSizer10->Add(StaticLine3, 0, wxALIGN_CENTER_HORIZONTAL | wxALL | wxEXPAND, 3);

	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer(0, 4, 0, 0);
	fgSizer5->SetFlexibleDirection(wxBOTH);
	fgSizer5->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	buttonDecOne = new wxButton(this, wxID_ANY, ("-1"), wxDefaultPosition, Skalefaktor * FromDIP(wxSize(34, 34)), 0);
	buttonDecOne->SetFont(wxFont(Skalefaktor * 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
	buttonDecOne->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER));

	fgSizer5->Add(buttonDecOne, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 1);

	buttonDecTen = new wxButton(this, wxID_ANY, ("-10"), wxDefaultPosition, Skalefaktor * FromDIP(wxSize(30, 30)), 0);
	buttonDecTen->SetFont(wxFont(Skalefaktor * 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
	buttonDecTen->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER));

	fgSizer5->Add(buttonDecTen, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 1);

	buttonIncTen = new wxButton(this, wxID_ANY, ("+10"), wxDefaultPosition, Skalefaktor * FromDIP(wxSize(30, 30)), 0);
	buttonIncTen->SetFont(wxFont(Skalefaktor * 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
	buttonIncTen->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER));

	fgSizer5->Add(buttonIncTen, 0, wxALIGN_CENTER_VERTICAL | wxALIGN_RIGHT, 1);

	buttonIncOne = new wxButton(this, wxID_ANY, ("+1"), wxDefaultPosition, Skalefaktor * FromDIP(wxSize(34, 34)), 0);
	buttonIncOne->SetFont(wxFont(Skalefaktor * 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
	buttonIncOne->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER));

	fgSizer5->Add(buttonIncOne, 0, wxALIGN_CENTER_VERTICAL, 1);

	bSizer10->Add(fgSizer5, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 0);

	wxGridSizer* gSizer7;
	gSizer7 = new wxGridSizer(0, 2, 0, 0);

	buttonAuto = new wxButton(this, wxID_ANY, ("Auto"), wxDefaultPosition, Skalefaktor * FromDIP(wxSize(65, 28)), 0 | wxBORDER_DEFAULT);
	buttonAuto->SetFont(wxFont(Skalefaktor * 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
	buttonAuto->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
	buttonAuto->SetBackgroundColour(wxColour(255, 0, 0));

	gSizer7->Add(buttonAuto, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxALIGN_CENTER_VERTICAL, 1);

	buttonStandby = new wxButton(this, wxID_ANY, ("Standby"), wxDefaultPosition, Skalefaktor * FromDIP(wxSize(65, 28)), 0);
	buttonStandby->SetFont(wxFont(Skalefaktor * 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
	buttonStandby->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
	buttonStandby->SetBackgroundColour(wxColour(0, 255, 0));

	gSizer7->Add(buttonStandby, 0, wxALIGN_CENTER_HORIZONTAL | wxTOP | wxALIGN_CENTER_VERTICAL, 1);

	buttonAutoWind = new wxButton(this, wxID_ANY, ("Auto-Wind"), wxDefaultPosition, Skalefaktor * FromDIP(wxSize(65, 28)), 0);
	buttonAutoWind->SetFont(wxFont(Skalefaktor * 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
	buttonAutoWind->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
	buttonAutoWind->SetBackgroundColour(wxColour(255, 128, 128));

	gSizer7->Add(buttonAutoWind, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM | wxALIGN_CENTER_VERTICAL, 1);

	buttonTrack = new wxButton(this, wxID_ANY, ("Track"), wxDefaultPosition, Skalefaktor * FromDIP(wxSize(65, 28)), 0);
	buttonTrack->SetFont(wxFont(Skalefaktor * 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, wxT("Arial")));
	buttonTrack->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));
	buttonTrack->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVEBORDER));

	gSizer7->Add(buttonTrack, 0, wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 1);

	bSizer10->Add(gSizer7, 0, wxALIGN_CENTER | wxALL, 0);

	this->SetSizer(bSizer10);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	this->Connect(wxEVT_ACTIVATE_APP, wxActivateEventHandler(m_dialog::OnActiveApp));
	this->Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(m_dialog::OnCloseApp));
	TextStatus->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(m_dialog::OnKlickInDisplay), NULL, this);
	TextCompass->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(m_dialog::OnKlickInDisplay), NULL, this);
	ParameterChoise->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(m_dialog::OnSelectParameter), NULL, this);
	buttonSet->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(m_dialog::OnSetParameterValue), NULL, this);
	buttonDecOne->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(m_dialog::OnDecrementOne), NULL, this);
	buttonDecTen->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(m_dialog::OnDecrementTen), NULL, this);
	buttonIncTen->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(m_dialog::OnIncrementTen), NULL, this);
	buttonIncOne->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(m_dialog::OnIncrementOne), NULL, this);
	buttonAuto->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(m_dialog::OnAuto), NULL, this);
	buttonStandby->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(m_dialog::OnStandby), NULL, this);
	buttonAutoWind->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(m_dialog::OnAutoWind), NULL, this);
	buttonTrack->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(m_dialog::OnTrack), NULL, this);
}

m_dialog::~m_dialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( m_dialog::OnActiveApp ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( m_dialog::OnCloseApp ) );
	TextStatus->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( m_dialog::OnKlickInDisplay ), NULL, this );
	TextCompass->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( m_dialog::OnKlickInDisplay ), NULL, this );
	ParameterChoise->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( m_dialog::OnSelectParameter ), NULL, this );
	buttonSet->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnSetParameterValue ), NULL, this );
	buttonDecOne->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnDecrementOne ), NULL, this );
	buttonDecTen->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnDecrementTen ), NULL, this );
	buttonIncTen->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnIncrementTen ), NULL, this );
	buttonIncOne->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnIncrementOne ), NULL, this );
	buttonAuto->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnAuto ), NULL, this );
	buttonStandby->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnStandby ), NULL, this );
	buttonAutoWind->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnAutoWind ), NULL, this );
	buttonTrack->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnTrack ), NULL, this );

}

m_Parameterdialog::m_Parameterdialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	fgSizer12->SetMinSize( FromDIP(wxSize( -1,40 )) );

	fgSizer12->Add( 12, 0, 1, wxEXPAND, 5 );

	m_AutopilotTypeText = new wxStaticText( this, wxID_ANY, _("Autopilot Type  :"), wxDefaultPosition, FromDIP(wxSize( -1,-1 )), 0 );
	m_AutopilotTypeText->Wrap( -1 );
	m_AutopilotTypeText->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );

	fgSizer12->Add( m_AutopilotTypeText, 0, wxALL, 14 );

	wxString m_AutopilotTypeChoices[] = { _("Raymarine Seatalk1 Autopilots (S1,S2,S3, ...), connected over NMEA0183/Seatalk1 translater"), _("Raymarine EVO Autopilot (connected over N2K / SeatalkNG)"), _("Raymarine EVO Autopilot (connected over Seasmart NMEA0183 $PCDIN)") };
	int m_AutopilotTypeNChoices = sizeof( m_AutopilotTypeChoices ) / sizeof( wxString );
	m_AutopilotType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_AutopilotTypeNChoices, m_AutopilotTypeChoices, 0 );
	m_AutopilotType->SetSelection( 0 );
	fgSizer12->Add( m_AutopilotType, 0, wxALL, 11 );


	bSizer2->Add( fgSizer12, 0, wxEXPAND, 20 );

	m_staticline42 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline42, 0, wxEXPAND | wxALL, 5 );
	m_checkParameters = new wxCheckBox( this, wxID_ANY, _("Autopilot Parameters changeable"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkParameters->SetValue(true);
	bSizer2->Add( m_checkParameters, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer51;
	fgSizer51 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer51->SetFlexibleDirection( wxBOTH );
	fgSizer51->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer51->Add( 20, 0, 1, wxEXPAND, 5 );

	m_NoStandbyCounterValueText11 = new wxStaticText( this, wxID_ANY, _("Autopilot Control display zoom factor          "), wxDefaultPosition, FromDIP(wxSize( -1,-1 )), 0 );
	m_NoStandbyCounterValueText11->Wrap( -1 );
	fgSizer51->Add( m_NoStandbyCounterValueText11, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );

	m_Skalefaktor = new wxSlider( this, wxID_ANY, 0, 0, 10, wxDefaultPosition, FromDIP(wxSize( 220,-1 )), wxSL_BOTH|wxSL_BOTTOM|wxSL_HORIZONTAL|wxSL_LABELS );
	m_Skalefaktor->SetFont( wxFont( 7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	fgSizer51->Add( m_Skalefaktor, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 0 );


	bSizer2->Add( fgSizer51, 0, 0, 0 );

	m_SendNewAutoWind = new wxCheckBox( this, wxID_ANY, _("Send new \"Auto-Wind\" Command when \"Wind Shift\""), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_SendNewAutoWind, 0, wxALL, 5 );

	m_SendNewAutoonStandby = new wxCheckBox( this, wxID_ANY, _("Send new \"Auto\" or \"Auto-Wind\" Command, when \"Standby\" is not send from here, but the \"Auto\" was from here"), wxDefaultPosition, wxDefaultSize, 0 );
	m_SendNewAutoonStandby->SetMaxSize( FromDIP(wxSize( 680,-1 )) );

	bSizer2->Add( m_SendNewAutoonStandby, 0, wxALL|wxEXPAND, 5 );

	m_NewStandbyNoStandbyReceived = new wxCheckBox( this, wxID_ANY, _("Send new \"Auto\" Command, when No Standby-Information is received from other Instrument or from here"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_NewStandbyNoStandbyReceived, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer2->Add( 18, 0, 1, wxEXPAND, 3 );

	m_NoStandbyCounter =  new wxTextCtrl( this, wxID_ANY, ("0"), wxDefaultPosition, FromDIP(wxSize( 40,20 )), wxTE_CENTER );
	#ifdef __WXGTK__
	if ( !m_NoStandbyCounter->HasFlag( wxTE_MULTILINE ) )
	{
	m_NoStandbyCounter->SetMaxLength( 2 );
	}
	#else
	m_NoStandbyCounter->SetMaxLength( 2 );
	#endif
	fgSizer2->Add( m_NoStandbyCounter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 3 );

	m_NoStandbyCounterValueText = new wxStaticText( this, wxID_ANY, _("Counter for Autopilot is in Standby Mode, but without \"Standby\" Command received"), wxDefaultPosition, FromDIP(wxSize( -1,-1 )), 0 );
	m_NoStandbyCounterValueText->Wrap( -1 );
	fgSizer2->Add( m_NoStandbyCounterValueText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 3 );

	m_ResetStandbyCounter = new wxButton( this, wxID_ANY, _("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ResetStandbyCounter->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	fgSizer2->Add( m_ResetStandbyCounter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 0 );


	fgSizer2->Add( 0, 0, 1, wxEXPAND, 3 );

	wxString m_SelectCounterStandbyChoices[] = { ("1"), ("2"), ("3"), ("4"), ("5"), ("6"), ("7"), ("8"), ("9"), ("10") };
	int m_SelectCounterStandbyNChoices = sizeof( m_SelectCounterStandbyChoices ) / sizeof( wxString );
	m_SelectCounterStandby = new wxChoice( this, wxID_ANY, wxDefaultPosition, FromDIP(wxSize( 40,20 )), m_SelectCounterStandbyNChoices, m_SelectCounterStandbyChoices, 0 );
	m_SelectCounterStandby->SetSelection( 0 );
	fgSizer2->Add( m_SelectCounterStandby, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 3 );

	m_Text = new wxStaticText( this, wxID_ANY, _("Value, for maximum  \"Not recived Standby Commands\" not sending \"Auto\" Command again"), wxDefaultPosition, FromDIP(wxSize( 500,-1 )), 0 );
	m_Text->Wrap( -1 );
	fgSizer2->Add( m_Text, 0, wxALL|wxALIGN_CENTER_VERTICAL, 3 );


	fgSizer2->Add( 0, 0, 1, wxEXPAND, 3 );


	fgSizer2->Add( 0, 0, 1, wxEXPAND, 3 );

	m_ChangeValueToLast = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_ChangeValueToLast->SetValue(true);
	fgSizer2->Add( m_ChangeValueToLast, 0, wxALL|wxALIGN_CENTER_VERTICAL, 3 );

	m_Text1 = new wxStaticText( this, wxID_ANY, _("Change course value back to the last Compass course value, the Course Computer\nhad, before the Auto Signal lost"), wxDefaultPosition, FromDIP(wxSize( 500,-1 )), 0 );
	m_Text1->Wrap( -1 );
	fgSizer2->Add( m_Text1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 3 );


	bSizer2->Add( fgSizer2, 0, wxEXPAND, 5 );

	m_SendTrack = new wxCheckBox( this, wxID_ANY, _("Send \"Track\" automatic when Autopilot has new Waypoint. Be careful with this normaly you have to accept yourself."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_SendTrack, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer5->Add( 18, 0, 1, wxEXPAND, 5 );

	m_TimeToSendNewWaypiont = new wxTextCtrl( this, wxID_ANY, ("10"), wxDefaultPosition, FromDIP(wxSize( 40,20 )), wxTE_CENTER );
	#ifdef __WXGTK__
	if ( !m_TimeToSendNewWaypiont->HasFlag( wxTE_MULTILINE ) )
	{
	m_TimeToSendNewWaypiont->SetMaxLength( 2 );
	}
	#else
	m_TimeToSendNewWaypiont->SetMaxLength( 2 );
	#endif
	fgSizer5->Add( m_TimeToSendNewWaypiont, 0, wxALL, 5 );

	m_NoStandbyCounterValueText1 = new wxStaticText( this, wxID_ANY, _("Time in seconds to wait before sending \"Track\" sentence."), wxDefaultPosition, FromDIP(wxSize( -1,-1 )), 0 );
	m_NoStandbyCounterValueText1->Wrap( -1 );
	fgSizer5->Add( m_NoStandbyCounterValueText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );


	bSizer2->Add( fgSizer5, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_STALKreceivename = new wxTextCtrl( this, wxID_ANY, ("STALK"), wxDefaultPosition, FromDIP(wxSize( 45,20 )), wxTE_CENTER );
	#ifdef __WXGTK__
	if ( !m_STALKreceivename->HasFlag( wxTE_MULTILINE ) )
	{
	m_STALKreceivename->SetMaxLength( 5 );
	}
	#else
	m_STALKreceivename->SetMaxLength( 5 );
	#endif
	fgSizer1->Add( m_STALKreceivename, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText11 = new wxStaticText( this, wxID_ANY, _("NMEA Sentencename from  Seatalk bus converted by SeatalkLink"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer1->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_STALKsendname = new wxTextCtrl( this, wxID_ANY, ("STALK"), wxDefaultPosition, FromDIP(wxSize( 45,20 )), wxTE_CENTER );
	#ifdef __WXGTK__
	if ( !m_STALKsendname->HasFlag( wxTE_MULTILINE ) )
	{
	m_STALKsendname->SetMaxLength( 5 );
	}
	#else
	m_STALKsendname->SetMaxLength( 5 );
	#endif
	fgSizer1->Add( m_STALKsendname, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText21 = new wxStaticText( this, wxID_ANY, _("NMEA Sentencename to Seatalk bus converted by SeatalkLink"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer1->Add( m_staticText21, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer2->Add( fgSizer1, 0, wxEXPAND, 5 );

	m_WriteMessages = new wxCheckBox( this, wxID_ANY, _("Write Message Info to OPENCPN Logfile"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_WriteMessages, 0, wxALL, 5 );

	m_WriteDebug = new wxCheckBox( this, wxID_ANY, _("Debug all \"$STALK\" Messages into OPENCPN Logfile"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_WriteDebug, 0, wxALL, 5 );

	m_ModyfyRMC = new wxCheckBox( this, wxID_ANY, _("Modify RMC Sentence as \"$ECRMC\" and replace or fill with Variationfield with the value from WMM Plugin"), wxDefaultPosition, FromDIP(wxSize(690, -1)), 0 );
	bSizer2->Add( m_ModyfyRMC, 0, wxALL, 5 );

	m_staticline4 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline4, 0, wxALL|wxEXPAND, 5 );

	m_allowautocog = new wxCheckBox( this, wxID_ANY, _("Allow use AUTO-COG function"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_allowautocog, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer5111;
	fgSizer5111 = new wxFlexGridSizer( 0, 6, 0, 0 );
	fgSizer5111->SetFlexibleDirection( wxBOTH );
	fgSizer5111->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer5111->Add( 20, 0, 1, wxEXPAND, 5 );

	m_sensebilitytext1 = new wxStaticText( this, wxID_ANY, _("the autopilot controller will get new +1 or -1 keystroke information to hold the Course Over Ground."), wxDefaultPosition, FromDIP(wxSize( -1,-1 )), 0 );
	m_sensebilitytext1->Wrap( -1 );
	fgSizer5111->Add( m_sensebilitytext1, 0, wxALL, 0 );


	bSizer2->Add( fgSizer5111, 0, wxEXPAND, 0 );

	wxFlexGridSizer* fgSizer511;
	fgSizer511 = new wxFlexGridSizer( 0, 6, 0, 0 );
	fgSizer511->SetFlexibleDirection( wxBOTH );
	fgSizer511->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer511->Add( 20, 0, 1, wxEXPAND, 7 );

	m_sensebilitytext = new wxStaticText( this, wxID_ANY, _("Sensibility "), wxDefaultPosition, FromDIP(wxSize( -1,-1 )), 0 );
	m_sensebilitytext->Wrap( -1 );
	fgSizer511->Add( m_sensebilitytext, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );


	fgSizer511->Add( 30, 0, 1, wxEXPAND, 5 );

	m_slowtext = new wxStaticText( this, wxID_ANY, _("slow"), wxDefaultPosition, FromDIP(wxSize( -1,-1 )), 0 );
	m_slowtext->Wrap( -1 );
	m_slowtext->SetFont( wxFont( 7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_slowtext->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );

	fgSizer511->Add( m_slowtext, 0, wxALL, 8 );

	m_cogsensibility = new wxSlider( this, wxID_ANY, 15, 1, 30, wxDefaultPosition, FromDIP(wxSize( 220,-1 )), wxSL_BOTH|wxSL_BOTTOM|wxSL_HORIZONTAL|wxSL_INVERSE );
	m_cogsensibility->SetFont( wxFont( 7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	fgSizer511->Add( m_cogsensibility, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 2 );

	m_fast = new wxStaticText( this, wxID_ANY, _("fast"), wxDefaultPosition, FromDIP(wxSize( -1,-1 )), 0 );
	m_fast->Wrap( -1 );
	m_fast->SetFont( wxFont( 7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_fast->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_HIGHLIGHT ) );

	fgSizer511->Add( m_fast, 0, wxALL, 8 );


	bSizer2->Add( fgSizer511, 0, wxEXPAND, 6 );

	wxFlexGridSizer* fgSizer52;
	fgSizer52 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer52->SetFlexibleDirection( wxBOTH );
	fgSizer52->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer52->Add( 18, 0, 0, wxEXPAND, 5 );

	m_maxdegreediff = new wxTextCtrl( this, wxID_ANY, ("45"), wxDefaultPosition, FromDIP(wxSize( 40,20 )), wxTE_CENTER );
	#ifdef __WXGTK__
	if ( !m_maxdegreediff->HasFlag( wxTE_MULTILINE ) )
	{
	m_maxdegreediff->SetMaxLength( 3 );
	}
	#else
	m_maxdegreediff->SetMaxLength( 3 );
	#endif
	fgSizer52->Add( m_maxdegreediff, 0, wxALL, 3 );

	m_maxdegtext = new wxStaticText( this, wxID_ANY, _("maximum difference between COG and magnetic heading in degrees"), wxDefaultPosition, FromDIP(wxSize( -1,-1 )), 0 );
	m_maxdegtext->Wrap( -1 );
	fgSizer52->Add( m_maxdegtext, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );


	bSizer2->Add( fgSizer52, 0, wxEXPAND, 0 );

	wxFlexGridSizer* fgSizer521;
	fgSizer521 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer521->SetFlexibleDirection( wxBOTH );
	fgSizer521->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer521->Add( 18, 0, 0, wxEXPAND, 5 );

	m_minspeedcog = new wxTextCtrl( this, wxID_ANY, ("1.5"), wxDefaultPosition, FromDIP(wxSize( 40,20 )), wxTE_CENTER );
	#ifdef __WXGTK__
	if ( !m_minspeedcog->HasFlag( wxTE_MULTILINE ) )
	{
	m_minspeedcog->SetMaxLength( 3 );
	}
	#else
	m_minspeedcog->SetMaxLength( 3 );
	#endif
	fgSizer521->Add( m_minspeedcog, 0, wxALL, 3 );

	m_minspeed = new wxStaticText( this, wxID_ANY, _("minimun speed in nodes (SOG) for using AUTO-COG function"), wxDefaultPosition, FromDIP(wxSize( -1,-1 )), 0 );
	m_minspeed->Wrap( -1 );
	fgSizer521->Add( m_minspeed, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );


	bSizer2->Add( fgSizer521, 0, wxEXPAND, 0 );

	wxFlexGridSizer* fgSizer522;
	fgSizer522 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer522->SetFlexibleDirection( wxBOTH );
	fgSizer522->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer522->Add( 18, 0, 0, wxEXPAND, 5 );

	m_maxchangehdg = new wxTextCtrl( this, wxID_ANY, ("20"), wxDefaultPosition, FromDIP(wxSize( 40,20 )), wxTE_CENTER );
	#ifdef __WXGTK__
	if ( !m_maxchangehdg->HasFlag( wxTE_MULTILINE ) )
	{
	m_maxchangehdg->SetMaxLength( 3 );
	}
	#else
	m_maxchangehdg->SetMaxLength( 3 );
	#endif
	fgSizer522->Add( m_maxchangehdg, 0, wxALL, 3 );

	m_maxchangehdgtext = new wxStaticText( this, wxID_ANY, _("maximum change of the \"is set pilot heading\" from last set in degrees"), wxDefaultPosition, FromDIP(wxSize( -1,-1 )), 0 );
	m_maxchangehdgtext->Wrap( -1 );
	fgSizer522->Add( m_maxchangehdgtext, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );


	bSizer2->Add( fgSizer522, 1, wxEXPAND, 5 );
	
	m_staticline41 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer2->Add( m_staticline41, 0, wxEXPAND | wxALL, 6 );

	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();

	bSizer2->Add( m_sdbSizer1, 1, wxALL, 5 );


	this->SetSizer( bSizer2 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_AutopilotType->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( m_Parameterdialog::OnChoiceAutoPilot ), NULL, this );
	m_checkParameters->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnParameterChanged ), NULL, this );
	m_SendNewAutoWind->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnAutoWindNew ), NULL, this );
	m_SendNewAutoonStandby->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnNewAuto ), NULL, this );
	m_ResetStandbyCounter->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnStandbyCounterReset ), NULL, this );
	m_allowautocog->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnAutoCogchange ), NULL, this );
}

m_Parameterdialog::~m_Parameterdialog()
{
	// Disconnect Events
	m_AutopilotType->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( m_Parameterdialog::OnChoiceAutoPilot ), NULL, this );
	m_checkParameters->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnParameterChanged ), NULL, this );
	m_SendNewAutoWind->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnAutoWindNew ), NULL, this );
	m_SendNewAutoonStandby->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnNewAuto ), NULL, this );
	m_ResetStandbyCounter->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnStandbyCounterReset ), NULL, this );
	m_allowautocog->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnAutoCogchange ), NULL, this );
}
