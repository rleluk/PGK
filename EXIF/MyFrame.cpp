#include "MyFrame.h"

MyFrame::MyFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	LoadImage = new wxButton( this, wxID_ANY, wxT("Wczytaj obrazek"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( LoadImage, 0, wxALIGN_CENTER|wxALL, 5 );

	Censorship = new wxButton( this, wxID_ANY, wxT("Cenzura"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( Censorship, 0, wxALIGN_CENTER|wxALL, 5 );

	Erode = new wxButton( this, wxID_ANY, wxT("Erode"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( Erode, 0, wxALIGN_CENTER|wxALL, 5 );

	Animation = new wxCheckBox( this, wxID_ANY, wxT("Animacja"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( Animation, 0, wxALIGN_CENTER|wxALL, 5 );

	m_gauge1 = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_gauge1->SetValue( 0 );
	m_gauge1->Hide();

	bSizer2->Add( m_gauge1, 0, wxALIGN_CENTER|wxALL, 5 );

	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_RICH);
	m_textCtrl1->SetMinSize( wxSize( 250,-1 ) );

	bSizer2->Add( m_textCtrl1, 1, wxALIGN_CENTER_HORIZONTAL|wxALL|wxEXPAND, 5 );


	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 800,533 ), wxTAB_TRAVERSAL );
	bSizer3->Add( m_panel1, 1, wxEXPAND, 5 );


	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame::MyFrameOnUpdateUI));
	LoadImage->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::LoadImageOnButtonClick ), NULL, this );
	Censorship->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::CensorshipOnButtonClick ), NULL, this );
	Erode->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::ErodeOnButtonClick ), NULL, this );
	Animation->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame::AnimationOnCheckBox ), NULL, this );
}

MyFrame::~MyFrame()
{
	// Disconnect Events
	this->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(MyFrame::MyFrameOnUpdateUI));
	LoadImage->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::LoadImageOnButtonClick ), NULL, this );
	Censorship->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::CensorshipOnButtonClick ), NULL, this );
	Erode->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyFrame::ErodeOnButtonClick ), NULL, this );
	Animation->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( MyFrame::AnimationOnCheckBox ), NULL, this );

}
