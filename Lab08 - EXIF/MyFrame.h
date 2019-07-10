	///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/event.h>
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/button.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/checkbox.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>

class MyFrame : public wxFrame
{
	private:

	protected:
		wxButton* LoadImage;
		wxButton* Censorship;
		wxButton* Erode;
		wxCheckBox* Animation;
		wxGauge* m_gauge1;
		wxTextCtrl* m_textCtrl1;
		wxPanel* m_panel1;

		virtual void LoadImageOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void CensorshipOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void ErodeOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void AnimationOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void MyFrameOnUpdateUI(wxUpdateUIEvent& event) { event.Skip(); }

	public:

		MyFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = "GFK Lab08", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1075, 572), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MyFrame();

};

