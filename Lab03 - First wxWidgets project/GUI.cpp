///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

GUI::GUI( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 600, 500 ), wxDefaultSize );

	wxBoxSizer* container;
	container = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* leftSizer;
	leftSizer = new wxBoxSizer( wxHORIZONTAL );

	panel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	leftSizer->Add( panel, 1, wxEXPAND | wxALL, 5 );


	container->Add( leftSizer, 3, wxEXPAND, 5 );

	wxBoxSizer* rightSizer;
	rightSizer = new wxBoxSizer( wxVERTICAL );

	saveToFileButton = new wxButton( this, wxID_SaveButton, wxT("Zapis do pliku"), wxDefaultPosition, wxDefaultSize, 0 );
	rightSizer->Add( saveToFileButton, 0, wxALIGN_CENTER|wxALL, 5 );

	bananaCheckBox = new wxCheckBox( this, wxID_Banan, wxT("BANANA!"), wxDefaultPosition, wxDefaultSize, 0 );
	rightSizer->Add( bananaCheckBox, 0, wxALIGN_CENTER|wxALL, 5 );

	bananaPositionScrollBar = new wxScrollBar( this, wxID_ScrollBar, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	bananaPositionScrollBar->SetMinSize( wxSize( 180,15 ) );

	rightSizer->Add( bananaPositionScrollBar, 0, wxALIGN_CENTER|wxALL, 5 );

	bananaPositionGauge = new wxGauge( this, wxID_Gauge, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	bananaPositionGauge->SetValue( 0 );
	bananaPositionGauge->SetMinSize( wxSize( 180,15 ) );

	rightSizer->Add( bananaPositionGauge, 0, wxALIGN_CENTER|wxALL, 5 );

	startColorButton = new wxButton( this, wxID_ColorButton, wxT("Wybierz kolor gwiazdki"), wxDefaultPosition, wxDefaultSize, 0 );
	rightSizer->Add( startColorButton, 0, wxALIGN_CENTER|wxALL, 5 );

	edit = new wxTextCtrl( this, wxID_EDIT, wxT("tekst"), wxDefaultPosition, wxDefaultSize, 0 );
	rightSizer->Add( edit, 0, wxALIGN_CENTER|wxALL, 5 );

	wxString choiceBoxChoices[] = { wxString::FromUTF8("Gwiazdka"), wxString::FromUTF8("Księżyc"), wxString::FromUTF8("Słonko")};
	int choiceBoxNChoices = sizeof( choiceBoxChoices ) / sizeof( wxString );
	choiceBox = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choiceBoxNChoices, choiceBoxChoices, 0 );
	choiceBox->SetSelection( 0 );
	rightSizer->Add( choiceBox, 0, wxALIGN_CENTER|wxALL, 5 );


	container->Add( rightSizer, 0, wxFIXED_MINSIZE, 0 );


	this->SetSizer( container );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	panel->Connect( wxEVT_PAINT, wxPaintEventHandler( GUI::panelOnPaint ), NULL, this );
	panel->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( GUI::panelOnUpdateUI ), NULL, this );
	saveToFileButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI::saveToFileButtonOnButtonClick ), NULL, this );
	bananaCheckBox->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUI::bananaCheckBoxOnCheckBox ), NULL, this );
	bananaPositionScrollBar->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	startColorButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI::startColorButtonOnButtonClick ), NULL, this );
	edit->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUI::editOnText ), NULL, this );
	choiceBox->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUI::choiceBoxOnChoice ), NULL, this );
}

GUI::~GUI()
{
	// Disconnect Events
	panel->Disconnect( wxEVT_PAINT, wxPaintEventHandler( GUI::panelOnPaint ), NULL, this );
	panel->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( GUI::panelOnUpdateUI ), NULL, this );
	saveToFileButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI::saveToFileButtonOnButtonClick ), NULL, this );
	bananaCheckBox->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUI::bananaCheckBoxOnCheckBox ), NULL, this );
	bananaPositionScrollBar->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	bananaPositionScrollBar->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUI::bananaPositionScrollBarOnScroll ), NULL, this );
	startColorButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUI::startColorButtonOnButtonClick ), NULL, this );
	edit->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( GUI::editOnText ), NULL, this );
	choiceBox->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUI::choiceBoxOnChoice ), NULL, this );

}
