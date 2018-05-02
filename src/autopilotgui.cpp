///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 23 2018)
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
	
	TextStatus = new wxTextCtrl( this, wxID_ANY, wxT("----------"), wxDefaultPosition, wxSize( 135,35 ), wxTE_CENTRE|wxTE_READONLY );
	TextStatus->SetFont( wxFont( 16, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	TextStatus->SetForegroundColour( wxColour( 0, 0, 128 ) );
	TextStatus->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INFOBK ) );
	
	bSizer10->Add( TextStatus, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	TextCompass = new wxTextCtrl( this, wxID_ANY, wxT("---"), wxDefaultPosition, wxSize( 135,25 ), wxTE_CENTRE|wxTE_READONLY );
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
	
	ValueSizer->Add( ParameterChoise, 0, 0, 5 );
	
	
	ValueSizer->Add( 0, 0, 0, 0, 5 );
	
	
	ValueSizer->Add( 0, 0, 0, 0, 5 );
	
	wxString ParameterValueChoices[] = { wxT("-"), wxT("1"), wxT("2"), wxT("3"), wxT("4"), wxT("5"), wxT("6"), wxT("7"), wxT("8"), wxT("9") };
	int ParameterValueNChoices = sizeof( ParameterValueChoices ) / sizeof( wxString );
	ParameterValue = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 33,20 ), ParameterValueNChoices, ParameterValueChoices, 0 );
	ParameterValue->SetSelection( 0 );
	ParameterValue->SetFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	ParameterValue->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	
	ValueSizer->Add( ParameterValue, 0, 0, 5 );
	
	buttonSet = new wxButton( this, wxID_ANY, wxT("Set"), wxDefaultPosition, wxSize( 30,20 ), 0 );
	buttonSet->SetFont( wxFont( 8, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonSet->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	ValueSizer->Add( buttonSet, 0, wxLEFT, 5 );
	
	
	bSizer10->Add( ValueSizer, 1, wxRIGHT|wxLEFT|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	StaticLine3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer10->Add( StaticLine3, 0, wxALL|wxEXPAND, 5 );
	
	wxGridSizer* gSizer6;
	gSizer6 = new wxGridSizer( 0, 4, 0, 0 );
	
	gSizer6->SetMinSize( wxSize( 1,-1 ) ); 
	buttonDecOne = new wxButton( this, wxID_ANY, wxT("-1"), wxDefaultPosition, wxSize( 40,40 ), 0 );
	buttonDecOne->SetFont( wxFont( 11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonDecOne->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	gSizer6->Add( buttonDecOne, 0, wxALIGN_CENTER_HORIZONTAL|wxRIGHT|wxLEFT, 5 );
	
	buttonDecTen = new wxButton( this, wxID_ANY, wxT("-10"), wxDefaultPosition, wxSize( 37,37 ), 0 );
	buttonDecTen->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonDecTen->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	gSizer6->Add( buttonDecTen, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 3 );
	
	buttonIncTen = new wxButton( this, wxID_ANY, wxT("+10"), wxDefaultPosition, wxSize( 37,37 ), 0 );
	buttonIncTen->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonIncTen->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	gSizer6->Add( buttonIncTen, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxTOP|wxRIGHT|wxLEFT, 3 );
	
	buttonIncOne = new wxButton( this, wxID_ANY, wxT("+1"), wxDefaultPosition, wxSize( 40,40 ), 0 );
	buttonIncOne->SetFont( wxFont( 11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonIncOne->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	gSizer6->Add( buttonIncOne, 0, wxALIGN_CENTER_HORIZONTAL|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer10->Add( gSizer6, 0, wxFIXED_MINSIZE|wxLEFT|wxRIGHT|wxSHAPED|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxGridSizer* gSizer7;
	gSizer7 = new wxGridSizer( 0, 2, 0, 0 );
	
	buttonAuto = new wxButton( this, wxID_ANY, wxT("Auto"), wxDefaultPosition, wxSize( 88,30 ), 0 );
	buttonAuto->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonAuto->SetBackgroundColour( wxColour( 255, 0, 0 ) );
	
	gSizer7->Add( buttonAuto, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	buttonStandby = new wxButton( this, wxID_ANY, wxT("Standby"), wxDefaultPosition, wxSize( 88,30 ), 0 );
	buttonStandby->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonStandby->SetBackgroundColour( wxColour( 0, 255, 0 ) );
	
	gSizer7->Add( buttonStandby, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP|wxRIGHT|wxLEFT, 5 );
	
	buttonAutoWind = new wxButton( this, wxID_ANY, wxT("Auto-Wind"), wxDefaultPosition, wxSize( 88,30 ), 0 );
	buttonAutoWind->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonAutoWind->SetBackgroundColour( wxColour( 255, 128, 128 ) );
	
	gSizer7->Add( buttonAutoWind, 0, wxALIGN_CENTER_HORIZONTAL|wxRIGHT|wxLEFT, 5 );
	
	buttonTrack = new wxButton( this, wxID_ANY, wxT("Track"), wxDefaultPosition, wxSize( 88,30 ), 0 );
	buttonTrack->SetFont( wxFont( 10, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );
	buttonTrack->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_ACTIVEBORDER ) );
	
	gSizer7->Add( buttonTrack, 0, wxALIGN_CENTER_HORIZONTAL|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer10->Add( gSizer7, 0, wxALIGN_CENTER|wxRIGHT|wxLEFT, 5 );
	
	
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
	
	m_SendNewAutoWind = new wxCheckBox( this, wxID_ANY, _("Send new \"Auto Wind\" Command when Wind Shift ( be careful with This)"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_SendNewAutoWind, 0, wxALL, 5 );
	
	m_SendNewAutoonStandby = new wxCheckBox( this, wxID_ANY, _("Send new \"Auto\" or \"Auto Wind\" Command, when Standby is not send from here.  ( be careful with This)"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_SendNewAutoonStandby, 0, wxALL, 5 );
	
	m_SendSNBSE = new wxCheckBox( this, wxID_ANY, _("Send $SNBSE message to switch sending $STALK messages from SeatalkLink off, when Autopilot in not visible"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_SendSNBSE, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_STALKreceivename = new wxTextCtrl( this, wxID_ANY, wxT("STALK"), wxDefaultPosition, wxSize( 45,20 ), 0 );
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
	
	m_STALKsendname = new wxTextCtrl( this, wxID_ANY, wxT("STALK"), wxDefaultPosition, wxSize( 45,20 ), 0 );
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
}

m_Parameterdialog::~m_Parameterdialog()
{
	// Disconnect Events
	m_checkParameters->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnParameterChanged ), NULL, this );
	m_SendNewAutoWind->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnAutoWindNew ), NULL, this );
	m_SendNewAutoonStandby->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( m_Parameterdialog::OnNewAuto ), NULL, this );
	
}
