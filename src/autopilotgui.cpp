///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "autopilotgui.h"

///////////////////////////////////////////////////////////////////////////

m_dialog::m_dialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxDialog( parent, id, title, pos, size, style, name )
{
	this->SetSizeHints( wxSize( 181,230 ), wxSize( 181,265 ) );
	this->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	StaticLine1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxLI_HORIZONTAL );
	bSizer10->Add( StaticLine1, 0, wxEXPAND | wxALL, 5 );

	TextStatus = new wxTextCtrl( this, wxID_ANY, wxT("----------"), wxDefaultPosition, wxSize( 135,35 ), wxTE_READONLY|wxTE_CENTER );
	TextStatus->SetFont( wxFont( 16, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	TextStatus->SetForegroundColour( wxColour( 0, 0, 128 ) );
	TextStatus->SetBackgroundColour( wxColour( 255, 255, 225 ) );

	bSizer10->Add( TextStatus, 0, wxALIGN_CENTER_HORIZONTAL, 5 );

	TextCompass = new wxTextCtrl( this, wxID_ANY, wxT("---"), wxDefaultPosition, wxSize( 135,25 ), wxTE_READONLY|wxTE_CENTER );
	TextCompass->SetFont( wxFont( 12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	TextCompass->SetForegroundColour( wxColour( 0, 0, 64 ) );
	TextCompass->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INFOBK ) );

	bSizer10->Add( TextCompass, 0, wxALIGN_CENTER_HORIZONTAL, 5 );

	StaticLine2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxLI_HORIZONTAL );
	bSizer10->Add( StaticLine2, 0, wxALL|wxEXPAND, 5 );

	wxGridSizer* ValueSizer;
	ValueSizer = new wxGridSizer( 0, 5, 0, 0 );

	wxString ParameterChoiseChoices[] = { wxT("------------"), wxT("Response"), wxT("WindTrim"), wxT("RudderGain") };
	int ParameterChoiseNChoices = sizeof( ParameterChoiseChoices ) / sizeof( wxString );
	ParameterChoise = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 90,20 ), ParameterChoiseNChoices, ParameterChoiseChoices, 0 );
	ParameterChoise->SetSelection( 0 );
	ParameterChoise->SetFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	ParameterChoise->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	ValueSizer->Add( ParameterChoise, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );


	ValueSizer->Add( 0, 0, 0, 0, 5 );


	ValueSizer->Add( 0, 0, 0, 0, 5 );

	wxString ParameterValueChoices[] = { wxT("-"), wxT("1"), wxT("2"), wxT("3"), wxT("4"), wxT("5"), wxT("6"), wxT("7"), wxT("8"), wxT("9") };
	int ParameterValueNChoices = sizeof( ParameterValueChoices ) / sizeof( wxString );
	ParameterValue = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 33,20 ), ParameterValueNChoices, ParameterValueChoices, 0 );
	ParameterValue->SetSelection( 0 );
	ParameterValue->SetFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	ParameterValue->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	ValueSizer->Add( ParameterValue, 0, wxALIGN_CENTER_VERTICAL, 5 );

	buttonSet = new wxButton( this, wxID_ANY, wxT("Set"), wxDefaultPosition, wxSize( 30,22 ), 0 );
	buttonSet->SetFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonSet->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	buttonSet->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );

	ValueSizer->Add( buttonSet, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxRIGHT, 5 );


	bSizer10->Add( ValueSizer, 1, wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL, 5 );

	StaticLine3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer10->Add( StaticLine3, 0, wxALL|wxEXPAND, 5 );

	wxGridSizer* gSizer6;
	gSizer6 = new wxGridSizer( 0, 4, 0, 0 );

	gSizer6->SetMinSize( wxSize( 1,-1 ) );
	buttonDecOne = new wxButton( this, wxID_ANY, wxT("-1"), wxDefaultPosition, wxSize( 36,36 ), 0 );
	buttonDecOne->SetFont( wxFont( 11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonDecOne->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );

	gSizer6->Add( buttonDecOne, 0, wxALIGN_CENTER_HORIZONTAL|wxLEFT, 5 );

	buttonDecTen = new wxButton( this, wxID_ANY, wxT("-10"), wxDefaultPosition, wxSize( 32,32 ), 0 );
	buttonDecTen->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonDecTen->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );

	gSizer6->Add( buttonDecTen, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxLEFT, 3 );

	buttonIncTen = new wxButton( this, wxID_ANY, wxT("+10"), wxDefaultPosition, wxSize( 32,32 ), 0 );
	buttonIncTen->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonIncTen->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );

	gSizer6->Add( buttonIncTen, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_CENTER_HORIZONTAL|wxLEFT, 3 );

	buttonIncOne = new wxButton( this, wxID_ANY, wxT("+1"), wxDefaultPosition, wxSize( 36,36 ), 0 );
	buttonIncOne->SetFont( wxFont( 11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonIncOne->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );

	gSizer6->Add( buttonIncOne, 0, wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer10->Add( gSizer6, 0, wxFIXED_MINSIZE|wxLEFT|wxRIGHT|wxSHAPED|wxALIGN_CENTER_HORIZONTAL, 5 );

	wxGridSizer* gSizer7;
	gSizer7 = new wxGridSizer( 0, 2, 0, 0 );

	buttonAuto = new wxButton( this, wxID_ANY, wxT("Auto"), wxDefaultPosition, wxSize( 74,28 ), 0|wxBORDER_DEFAULT );
	buttonAuto->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonAuto->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	buttonAuto->SetBackgroundColour( wxColour( 255, 0, 0 ) );

	gSizer7->Add( buttonAuto, 0, wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL|wxTOP, 5 );

	buttonStandby = new wxButton( this, wxID_ANY, wxT("Standby"), wxDefaultPosition, wxSize( 74,28 ), 0 );
	buttonStandby->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonStandby->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	buttonStandby->SetBackgroundColour( wxColour( 0, 255, 0 ) );

	gSizer7->Add( buttonStandby, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP, 5 );

	buttonAutoWind = new wxButton( this, wxID_ANY, wxT("Auto-Wind"), wxDefaultPosition, wxSize( 74,28 ), 0 );
	buttonAutoWind->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonAutoWind->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	buttonAutoWind->SetBackgroundColour( wxColour( 255, 128, 128 ) );

	gSizer7->Add( buttonAutoWind, 0, wxALIGN_CENTER_HORIZONTAL|wxBOTTOM, 5 );

	buttonTrack = new wxButton( this, wxID_ANY, wxT("Track"), wxDefaultPosition, wxSize( 74,28 ), 0 );
	buttonTrack->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonTrack->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNTEXT ) );
	buttonTrack->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );

	gSizer7->Add( buttonTrack, 0, wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer10->Add( gSizer7, 0, wxALIGN_CENTER|wxRIGHT|wxLEFT, 4 );


	this->SetSizer( bSizer10 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_ACTIVATE_APP, wxActivateEventHandler( m_dialog::OnActiveApp ) );
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
	bSizer2->Add( m_checkParameters, 0, wxALL, 5 );

	m_SendNewAutoWind = new wxCheckBox( this, wxID_ANY, _("Send new \"Auto-Wind\" Command when \"Wind Shift\""), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_SendNewAutoWind, 0, wxALL, 5 );

	m_SendNewAutoonStandby = new wxCheckBox( this, wxID_ANY, _("Send new \"Auto\" or \"Auto-Wind\" Command, when \"Standby\" is not send from here, but the \"Auto\" was from here"), wxDefaultPosition, wxDefaultSize, 0 );
	m_SendNewAutoonStandby->SetValue(true);
	m_SendNewAutoonStandby->SetMaxSize( wxSize( 640,-1 ) );

	bSizer2->Add( m_SendNewAutoonStandby, 0, wxALL, 5 );

	m_NewStandbyNoStandbyReceived = new wxCheckBox( this, wxID_ANY, _("Send new \"Auto\" Command, when No Standby-Information is received from other Instrument or from here"), wxDefaultPosition, wxDefaultSize, 0 );
	m_NewStandbyNoStandbyReceived->SetValue(true);
	bSizer2->Add( m_NewStandbyNoStandbyReceived, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer2->Add( 15, 0, 1, wxEXPAND, 5 );

	m_NoStandbyCounter = new wxTextCtrl( this, wxID_ANY, wxT("0"), wxDefaultPosition, wxSize( 40,20 ), wxTE_CENTER );
	#ifdef __WXGTK__
	if ( !m_NoStandbyCounter->HasFlag( wxTE_MULTILINE ) )
	{
	m_NoStandbyCounter->SetMaxLength( 2 );
	}
	#else
	m_NoStandbyCounter->SetMaxLength( 2 );
	#endif
	fgSizer2->Add( m_NoStandbyCounter, 0, wxALL, 5 );

	m_NoStandbyCounterValueText = new wxStaticText( this, wxID_ANY, _("Counter for Autopilot is in Standby Mode, but without \"Standby\" Command received"), wxDefaultPosition, wxSize( 500,-1 ), 0 );
	m_NoStandbyCounterValueText->Wrap( -1 );
	fgSizer2->Add( m_NoStandbyCounterValueText, 0, wxALL, 5 );

	m_ResetStandbyCounter = new wxButton( this, wxID_ANY, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	m_ResetStandbyCounter->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	m_ResetStandbyCounter->SetMinSize( wxSize( 50,20 ) );

	fgSizer2->Add( m_ResetStandbyCounter, 0, wxALL, 5 );


	fgSizer2->Add( 0, 0, 1, wxEXPAND, 5 );

	wxString m_SelectCounterStandbyChoices[] = { wxT("1"), wxT("2"), wxT("3"), wxT("4"), wxT("5"), wxT("6"), wxT("7"), wxT("8"), wxT("9"), wxT("10") };
	int m_SelectCounterStandbyNChoices = sizeof( m_SelectCounterStandbyChoices ) / sizeof( wxString );
	m_SelectCounterStandby = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 40,20 ), m_SelectCounterStandbyNChoices, m_SelectCounterStandbyChoices, 0 );
	m_SelectCounterStandby->SetSelection( 0 );
	fgSizer2->Add( m_SelectCounterStandby, 0, wxALL, 5 );

	m_Text = new wxStaticText( this, wxID_ANY, _("Value, for maximum  \"Not recived Standby Commands\" not sending \"Auto\" Command again"), wxDefaultPosition, wxSize( 500,-1 ), 0 );
	m_Text->Wrap( -1 );
	fgSizer2->Add( m_Text, 0, wxALL, 5 );


	bSizer2->Add( fgSizer2, 1, wxEXPAND, 5 );

	m_SendSNBSE = new wxCheckBox( this, wxID_ANY, _("Send \"$SNBSE\" message to switch sending \"$STALK\" messages from SeatalkLink off, when Autopilot in not visible"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_SendSNBSE, 0, wxALL, 5 );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_STALKreceivename = new wxTextCtrl( this, wxID_ANY, wxT("STALK"), wxDefaultPosition, wxSize( 45,20 ), wxTE_CENTER );
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

	m_STALKsendname = new wxTextCtrl( this, wxID_ANY, wxT("STALK"), wxDefaultPosition, wxSize( 45,20 ), wxTE_CENTER );
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
