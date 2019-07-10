///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_SaveButton 1000
#define wxID_Banan 1001
#define wxID_ScrollBar 1002
#define wxID_Gauge 1003
#define wxID_ColorButton 1004

///////////////////////////////////////////////////////////////////////////////
/// Class GUI
///////////////////////////////////////////////////////////////////////////////
class GUI : public wxFrame
{
	private:

	protected:
		wxPanel* panel;
		wxButton* saveToFileButton;
		wxCheckBox* bananaCheckBox;
		wxScrollBar* bananaPositionScrollBar;
		wxGauge* bananaPositionGauge;
		wxButton* startColorButton;
		wxTextCtrl* edit;
		wxChoice* choiceBox;

		// Virtual event handlers, overide them in your derived class
		virtual void panelOnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void panelOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void saveToFileButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void bananaCheckBoxOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void bananaPositionScrollBarOnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void startColorButtonOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void editOnText( wxCommandEvent& event ) { event.Skip(); }
		virtual void choiceBoxOnChoice( wxCommandEvent& event ) { event.Skip(); }


	public:

		GUI( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Monkey D. Luffy"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 860,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~GUI();

};

