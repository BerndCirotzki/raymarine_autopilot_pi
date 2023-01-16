///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "autopilotgui.h"

///////////////////////////////////////////////////////////////////////////

m_dialog::m_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxDialog( parent, id, title, pos, size, style, name )
{
	this->SetSizeHints( wxSize( 160,205 ), wxSize( -1,-1 ) );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	StaticLine1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxSize( -1,2 ), wxLI_HORIZONTAL );
	StaticLine1->SetMinSize( wxSize( -1,2 ) );
	StaticLine1->SetMaxSize( wxSize( -1,2 ) );

	bSizer10->Add( StaticLine1, 1, wxEXPAND | wxALL, 3 );

	TextStatus = new wxTextCtrl( this, wxID_ANY, _("----------"), wxDefaultPosition, wxSize( 120,30 ), wxTE_CENTER|wxTE_READONLY );
	TextStatus->SetFont( wxFont( 13, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	TextStatus->SetForegroundColour( wxColour( 0, 0, 128 ) );
	TextStatus->SetBackgroundColour( wxColour( 255, 255, 225 ) );

	bSizer10->Add( TextStatus, 0, wxALIGN_CENTER_HORIZONTAL, 5 );

	TextCompass = new wxTextCtrl( this, wxID_ANY, _("---"), wxDefaultPosition, wxSize( 120,20 ), wxTE_READONLY|wxTE_CENTER );
	TextCompass->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	TextCompass->SetForegroundColour( wxColour( 0, 0, 64 ) );
	TextCompass->SetBackgroundColour( wxColour( 255, 255, 225 ) );

	bSizer10->Add( TextCompass, 0, wxALIGN_CENTER_HORIZONTAL, 5 );

	StaticLine2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxSize( -1,2 ), wxLI_HORIZONTAL );
	StaticLine2->SetMaxSize( wxSize( -1,2 ) );

	bSizer10->Add( StaticLine2, 1, wxALL|wxEXPAND, 4 );

	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxString ParameterChoiseChoices[] = { _("------------"), _("Response"), _("WindTrim"), _("RudderGain") };
	int ParameterChoiseNChoices = sizeof( ParameterChoiseChoices ) / sizeof( wxString );
	ParameterChoise = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 69,18 ), ParameterChoiseNChoices, ParameterChoiseChoices, 0 );
	ParameterChoise->SetSelection( 3 );
	ParameterChoise->SetFont( wxFont( 6, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	ParameterChoise->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	ParameterChoise->SetMinSize( wxSize( 69,18 ) );

	fgSizer4->Add( ParameterChoise, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 0 );

	wxString ParameterValueChoices[] = { _("-"), _("1"), _("2"), _("3"), _("4"), _("5"), _("6"), _("7"), _("8"), _("9") };
	int ParameterValueNChoices = sizeof( ParameterValueChoices ) / sizeof( wxString );
	ParameterValue = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 28,18 ), ParameterValueNChoices, ParameterValueChoices, 0 );
	ParameterValue->SetSelection( 5 );
	ParameterValue->SetFont( wxFont( 6, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	ParameterValue->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	ParameterValue->SetMinSize( wxSize( 28,18 ) );

	fgSizer4->Add( ParameterValue, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 0 );

	buttonSet = new wxButton( this, wxID_ANY, _("Set"), wxDefaultPosition, wxSize( 38,18 ), 0 );
	buttonSet->SetFont( wxFont( 6, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonSet->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	buttonSet->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	buttonSet->SetMinSize( wxSize( 38,18 ) );

	fgSizer4->Add( buttonSet, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0 );


	bSizer10->Add( fgSizer4, 0, wxALIGN_CENTER_HORIZONTAL, 1 );

	StaticLine3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxSize( -1,2 ), wxLI_HORIZONTAL );
	StaticLine3->SetMaxSize( wxSize( -1,2 ) );

	bSizer10->Add( StaticLine3, 1, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 4 );

	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	buttonDecOne = new wxButton( this, wxID_ANY, _("-1"), wxDefaultPosition, wxSize( 34,34 ), 0 );
	buttonDecOne->SetFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonDecOne->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );

	fgSizer5->Add( buttonDecOne, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1 );

	buttonDecTen = new wxButton( this, wxID_ANY, _("-10"), wxDefaultPosition, wxSize( 30,30 ), 0 );
	buttonDecTen->SetFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonDecTen->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );

	fgSizer5->Add( buttonDecTen, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 1 );

	buttonIncTen = new wxButton( this, wxID_ANY, _("+10"), wxDefaultPosition, wxSize( 30,30 ), 0 );
	buttonIncTen->SetFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonIncTen->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );

	fgSizer5->Add( buttonIncTen, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 1 );

	buttonIncOne = new wxButton( this, wxID_ANY, _("+1"), wxDefaultPosition, wxSize( 34,34 ), 0 );
	buttonIncOne->SetFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonIncOne->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );

	fgSizer5->Add( buttonIncOne, 0, wxALIGN_CENTER_VERTICAL, 1 );


	bSizer10->Add( fgSizer5, 0, wxALIGN_CENTER_HORIZONTAL, 1 );

	wxGridSizer* gSizer7;
	gSizer7 = new wxGridSizer( 0, 2, 0, 0 );

	buttonAuto = new wxButton( this, wxID_ANY, _("Auto"), wxDefaultPosition, wxSize( 65,28 ), 0|wxBORDER_DEFAULT );
	buttonAuto->SetFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonAuto->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	buttonAuto->SetBackgroundColour( wxColour( 255, 0, 0 ) );

	gSizer7->Add( buttonAuto, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxALIGN_CENTER_VERTICAL, 1 );

	buttonStandby = new wxButton( this, wxID_ANY, _("Standby"), wxDefaultPosition, wxSize( 65,28 ), 0 );
	buttonStandby->SetFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonStandby->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	buttonStandby->SetBackgroundColour( wxColour( 0, 255, 0 ) );

	gSizer7->Add( buttonStandby, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxALIGN_CENTER_VERTICAL, 1 );

	buttonAutoWind = new wxButton( this, wxID_ANY, _("Auto-Wind"), wxDefaultPosition, wxSize( 65,28 ), 0 );
	buttonAutoWind->SetFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonAutoWind->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	buttonAutoWind->SetBackgroundColour( wxColour( 255, 128, 128 ) );

	gSizer7->Add( buttonAutoWind, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM|wxALIGN_CENTER_VERTICAL, 1 );

	buttonTrack = new wxButton( this, wxID_ANY, _("Track"), wxDefaultPosition, wxSize( 65,28 ), 0 );
	buttonTrack->SetFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonTrack->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	buttonTrack->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );

	gSizer7->Add( buttonTrack, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1 );


	bSizer10->Add( gSizer7, 0, wxALIGN_CENTER, 1 );


	this->SetSizer( bSizer10 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( m_dialog::OnActiveApp ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( m_dialog::OnCloseApp ) );
	TextStatus->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( m_dialog::OnKlickInDisplay ), NULL, this );
	TextCompass->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( m_dialog::OnKlickInDisplay ), NULL, this );
	ParameterChoise->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( m_dialog::OnSelectParameter ), NULL, this );
	buttonSet->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnSetParameterValue ), NULL, this );
	buttonDecOne->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnDecrementOne ), NULL, this );
	buttonDecTen->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnDecrementTen ), NULL, this );
	buttonIncTen->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnIncrementTen ), NULL, this );
	buttonIncOne->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnIncrementOne ), NULL, this );
	buttonAuto->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnAuto ), NULL, this );
	buttonStandby->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnStandby ), NULL, this );
	buttonAutoWind->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnAutoWind ), NULL, this );
	buttonTrack->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_dialog::OnTrack ), NULL, this );
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

	m_checkParameters = new wxCheckBox( this, wxID_ANY, _("Autopilot Parameters changeable"), wxDefaultPosition, wxDefaultSize, 0 );
	m_checkParameters->SetValue(true);
	bSizer2->Add( m_checkParameters, 0, wxALL, 5 );

	m_SendNewAutoWind = new wxCheckBox( this, wxID_ANY, _("Send new \"Auto-Wind\" Command when \"Wind Shift\""), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_SendNewAutoWind, 0, wxALL, 5 );

	m_SendNewAutoonStandby = new wxCheckBox( this, wxID_ANY, _("Send new \"Auto\" or \"Auto-Wind\" Command, when \"Standby\" is not send from here, but the \"Auto\" was from here"), wxDefaultPosition, wxDefaultSize, 0 );
	m_SendNewAutoonStandby->SetMaxSize( wxSize( 680,-1 ) );

	bSizer2->Add( m_SendNewAutoonStandby, 0, wxALL|wxEXPAND, 5 );

	m_NewStandbyNoStandbyReceived = new wxCheckBox( this, wxID_ANY, _("Send new \"Auto\" Command, when No Standby-Information is received from other Instrument or from here"), wxDefaultPosition, wxDefaultSize, 0 );
	m_NewStandbyNoStandbyReceived->SetValue(true);
	bSizer2->Add( m_NewStandbyNoStandbyReceived, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer2->Add( 20, 0, 1, wxEXPAND, 3 );

	m_NoStandbyCounter = new wxTextCtrl( this, wxID_ANY, _("0"), wxDefaultPosition, wxSize( 40,20 ), wxTE_CENTER );
	#ifdef __WXGTK__
	if ( !m_NoStandbyCounter->HasFlag( wxTE_MULTILINE ) )
	{
	m_NoStandbyCounter->SetMaxLength( 2 );
	}
	#else
	m_NoStandbyCounter->SetMaxLength( 2 );
	#endif
	fgSizer2->Add( m_NoStandbyCounter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 3 );

	m_NoStandbyCounterValueText = new wxStaticText( this, wxID_ANY, _("Counter for Autopilot is in Standby Mode, but without \"Standby\" Command received"), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_NoStandbyCounterValueText->Wrap( -1 );
	fgSizer2->Add( m_NoStandbyCounterValueText, 0, wxALL|wxALIGN_CENTER_VERTICAL, 3 );

	m_ResetStandbyCounter = new wxButton( this, wxID_ANY, _("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ResetStandbyCounter->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_ResetStandbyCounter->SetMinSize( wxSize( -1,20 ) );

	fgSizer2->Add( m_ResetStandbyCounter, 0, wxALL|wxALIGN_CENTER_VERTICAL, 3 );


	fgSizer2->Add( 0, 0, 1, wxEXPAND, 3 );

	wxString m_SelectCounterStandbyChoices[] = { _("1"), _("2"), _("3"), _("4"), _("5"), _("6"), _("7"), _("8"), _("9"), _("10") };
	int m_SelectCounterStandbyNChoices = sizeof( m_SelectCounterStandbyChoices ) / sizeof( wxString );
	m_SelectCounterStandby = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 40,20 ), m_SelectCounterStandbyNChoices, m_SelectCounterStandbyChoices, 0 );
	m_SelectCounterStandby->SetSelection( 0 );
	fgSizer2->Add( m_SelectCounterStandby, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL, 3 );

	m_Text = new wxStaticText( this, wxID_ANY, _("Value, for maximum  \"Not recived Standby Commands\" not sending \"Auto\" Command again"), wxDefaultPosition, wxSize( 500,-1 ), 0 );
	m_Text->Wrap( -1 );
	fgSizer2->Add( m_Text, 0, wxALL|wxALIGN_CENTER_VERTICAL, 3 );


	fgSizer2->Add( 0, 0, 1, wxEXPAND, 3 );


	fgSizer2->Add( 0, 0, 1, wxEXPAND, 3 );

	m_ChangeValueToLast = new wxCheckBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_ChangeValueToLast->SetValue(true);
	fgSizer2->Add( m_ChangeValueToLast, 0, wxALL|wxALIGN_CENTER_VERTICAL, 3 );

	m_Text1 = new wxStaticText( this, wxID_ANY, _("Change course value back to the last Compass course value, the Course Computer\nhad, before the Auto Signal lost"), wxDefaultPosition, wxSize( 500,-1 ), 0 );
	m_Text1->Wrap( -1 );
	fgSizer2->Add( m_Text1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 3 );


	bSizer2->Add( fgSizer2, 0, wxEXPAND, 5 );

	m_SendTrack = new wxCheckBox( this, wxID_ANY, _("Send \"Track\" automatic when Autopilot has new Waypoint. Be careful with this normaly you have to accept yourself."), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_SendTrack, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer5->Add( 20, 0, 1, wxEXPAND, 5 );

	m_TimeToSendNewWaypiont = new wxTextCtrl( this, wxID_ANY, _("10"), wxDefaultPosition, wxSize( 40,20 ), wxTE_CENTER );
	#ifdef __WXGTK__
	if ( !m_TimeToSendNewWaypiont->HasFlag( wxTE_MULTILINE ) )
	{
	m_TimeToSendNewWaypiont->SetMaxLength( 2 );
	}
	#else
	m_TimeToSendNewWaypiont->SetMaxLength( 2 );
	#endif
	fgSizer5->Add( m_TimeToSendNewWaypiont, 0, wxALL, 5 );

	m_NoStandbyCounterValueText1 = new wxStaticText( this, wxID_ANY, _("Time in seconds to wait before sending \"Track\" sentence."), wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_NoStandbyCounterValueText1->Wrap( -1 );
	fgSizer5->Add( m_NoStandbyCounterValueText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );


	bSizer2->Add( fgSizer5, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_STALKreceivename = new wxTextCtrl( this, wxID_ANY, _("STALK"), wxDefaultPosition, wxSize( 45,20 ), wxTE_CENTER );
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

	m_STALKsendname = new wxTextCtrl( this, wxID_ANY, _("STALK"), wxDefaultPosition, wxSize( 45,20 ), wxTE_CENTER );
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


	bSizer2->Add( fgSizer1, 1, wxEXPAND, 5 );

	m_WriteMessages = new wxCheckBox( this, wxID_ANY, _("Write Message Info to OPENCPN Logfile"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_WriteMessages, 0, wxALL, 5 );

	m_WriteDebug = new wxCheckBox( this, wxID_ANY, _("Debug all \"$STALK\" Messages into OPENCPN Logfile"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_WriteDebug, 0, wxALL, 5 );

	m_ModyfyRMC = new wxCheckBox( this, wxID_ANY, _("Modify RMC Sentence as \"$ECRMC\" and replace or fill with Variationfield with the value from WMM Plugin"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_ModyfyRMC, 0, wxALL, 5 );

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
	m_checkParameters->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnParameterChanged ), NULL, this );
	m_SendNewAutoWind->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnAutoWindNew ), NULL, this );
	m_SendNewAutoonStandby->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnNewAuto ), NULL, this );
	m_ResetStandbyCounter->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnStandbyCounterReset ), NULL, this );
}

m_Parameterdialog::~m_Parameterdialog()
{
	// Disconnect Events
	m_checkParameters->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnParameterChanged ), NULL, this );
	m_SendNewAutoWind->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnAutoWindNew ), NULL, this );
	m_SendNewAutoonStandby->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnNewAuto ), NULL, this );
	m_ResetStandbyCounter->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnStandbyCounterReset ), NULL, this );

}
