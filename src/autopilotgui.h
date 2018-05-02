///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jan 23 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __AUTOPILOTGUI_H__
#define __AUTOPILOTGUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/statline.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class m_dialog
///////////////////////////////////////////////////////////////////////////////
class m_dialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticLine* StaticLine1;
		wxTextCtrl* TextStatus;
		wxTextCtrl* TextCompass;
		wxStaticLine* StaticLine2;
		wxButton* buttonDecOne;
		wxButton* buttonDecTen;
		wxButton* buttonIncTen;
		wxButton* buttonIncOne;
		wxButton* buttonAuto;
		wxButton* buttonStandby;
		wxButton* buttonAutoWind;
		wxButton* buttonTrack;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnActiveApp( wxActivateEvent& event ) { event.Skip(); }
		virtual void OnSelectParameter( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSetParameterValue( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDecrementOne( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDecrementTen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnIncrementTen( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnIncrementOne( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAuto( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStandby( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAutoWind( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTrack( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxChoice* ParameterChoise;
		wxChoice* ParameterValue;
		wxButton* buttonSet;
		wxStaticLine* StaticLine3;
		
		m_dialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Autopilot Control"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 181,265 ), long style = wxCAPTION|wxMINIMIZE_BOX, const wxString& name = wxT("Raymarine Autopilot") ); 
		~m_dialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class m_Parameterdialog
///////////////////////////////////////////////////////////////////////////////
class m_Parameterdialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText21;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnParameterChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAutoWindNew( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnNewAuto( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxCheckBox* m_checkParameters;
		wxCheckBox* m_SendNewAutoWind;
		wxCheckBox* m_SendNewAutoonStandby;
		wxCheckBox* m_SendSNBSE;
		wxTextCtrl* m_STALKreceivename;
		wxTextCtrl* m_STALKsendname;
		
		m_Parameterdialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Autopilot"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 645,245 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~m_Parameterdialog();
	
};

#endif //__AUTOPILOTGUI_H__
