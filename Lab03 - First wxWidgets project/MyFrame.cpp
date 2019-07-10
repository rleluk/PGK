#include "MyFrame.h"

MyFrame::MyFrame() : GUI(nullptr) , starColour(new wxColour(*wxBLACK)) {
	wxImage::AddHandler(new wxPNGHandler);
	wxImage * imgBanana = new wxImage(wxSize(50, 38));
	imgBanana->LoadFile("banana.png", wxBITMAP_TYPE_PNG);
	bananaBitmap = new wxBitmap(*imgBanana);
	panel->SetBackgroundColour(wxColor(*wxWHITE));
	bananaPositionScrollBar->SetScrollbar(0, 1, 100, 1);
	bananaPositionScrollBar->Enable(false);
	bananaPositionGauge->SetRange(99);
	saveDialog = new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("PNG files (*.png)|*.png"), wxFD_SAVE);
}

void MyFrame::saveToFileButtonOnButtonClick(wxCommandEvent& event) {
	wxClientDC dc(panel);
	wxBufferedDC buffDC(&dc);
	PrepareDC(buffDC);
	wxInitAllImageHandlers();

	if (saveDialog->ShowModal() == wxID_OK) {
		Refresh();
		wxString fileName = saveDialog->GetPath();
		wxSize panelSize = panel->GetVirtualSize();
		wxBitmap saveBitmap = wxBitmap(panelSize);
		wxMemoryDC saveMemes;
		
		saveMemes.SelectObject(saveBitmap);
		saveMemes.Blit(0, 0, panelSize.GetX(), panelSize.GetY(), &buffDC, 0, 0, wxCOPY, true);
		saveBitmap.ConvertToImage().SaveFile(fileName, wxBITMAP_TYPE_PNG);
	}
}

void MyFrame::bananaCheckBoxOnCheckBox(wxCommandEvent& event) {
	isBanana = event.IsChecked();
	if (!isBanana) bananaPositionScrollBar->Enable(false);
	else bananaPositionScrollBar->Enable(true);
	Refresh();
}

void MyFrame::bananaPositionScrollBarOnScroll(wxScrollEvent& event) {
	bananaPosition = event.GetPosition();
	bananaPositionGauge->SetValue(bananaPosition);
	Refresh();
}

void MyFrame::startColorButtonOnButtonClick(wxCommandEvent& event) {
	wxColourDialog cd(this);
	if (cd.ShowModal() == wxID_OK) 
		*starColour = cd.GetColourData().GetColour();
	Refresh();
}

void MyFrame::editOnText(wxCommandEvent& event) {
	text = event.GetString();
	wxClientDC dc(panel);
	drawOnPanel(dc);
	Refresh();
}

void MyFrame::choiceBoxOnChoice(wxCommandEvent& event) {
	choice = event.GetSelection();
	Refresh();
}

void MyFrame::panelOnUpdateUI(wxUpdateUIEvent& event) {
	wxClientDC dc(panel);
	drawOnPanel(dc);
}

void MyFrame::panelOnPaint(wxPaintEvent& event) {
	wxClientDC dc(panel);
	panel->Refresh();
	panel->Update();
	drawOnPanel(dc);
}

void MyFrame::drawOnPanel(wxClientDC &dc) {
	wxBufferedDC buffDC(&dc);
	PrepareDC(buffDC);
	buffDC.Clear();

	wxSize centre = panel->GetVirtualSize();
	int x = centre.GetWidth() / 2;
	int y = centre.GetHeight() / 2;
	int radius = 24;

	buffDC.SetDeviceOrigin(x, y);
	buffDC.SetPen(wxPen(wxColor(0, 0, 0), 1));

	//head
	buffDC.DrawCircle(wxPoint(0, 0), radius);
	buffDC.DrawEllipse(wxPoint(-13, -8), wxSize(10, 7));

	//torso
	buffDC.DrawLine(wxPoint(0, radius), wxPoint(0, radius + 80));

	//legs
	buffDC.DrawLine(wxPoint(0, radius + 80), wxPoint(30, radius + 150));
	buffDC.DrawLine(wxPoint(0, radius + 80), wxPoint(-30, radius + 150));

	//right arm
	buffDC.DrawLine(wxPoint(0, radius + 10), wxPoint(50, radius + 30));

	// BANANA
	if (isBanana) {
		if (bananaBitmap)
			buffDC.DrawBitmap(*bananaBitmap, wxPoint(-40 - 38, -bananaPosition / 2 + radius + 10));
		buffDC.DrawLine(wxPoint(0, radius + 10), wxPoint(-50, -bananaPosition / 2 + radius + 30));
		buffDC.DrawEllipticArc(wxPoint(-14, 5), wxSize(30, 10) , 0, -180);
		buffDC.DrawEllipse(wxPoint(3, -8), wxSize(10, 7));
	} else {
		buffDC.DrawLine(wxPoint(0, radius + 10), wxPoint(-50, -bananaPosition / 2 + radius + 30));
		buffDC.DrawEllipticArc(wxPoint(-14, 5), wxSize(30, 10), 0, 180);
		buffDC.DrawEllipse(wxPoint(6, -11), wxSize(7, 10));
	}

	if (choice == STAR) {
		buffDC.SetPen(wxPen(*starColour));
		buffDC.SetBrush(*starColour);
		starXY[0] = wxPoint(-100, -60);
		starXY[1] = wxPoint(-60, -150);
		starXY[2] = wxPoint(-160, -100);
		starXY[3] = wxPoint(-40, -100);
		starXY[4] = wxPoint(-140, -150);
		buffDC.DrawPolygon(5, starXY, wxWINDING_RULE);
	} else if (choice == MOON) {
		buffDC.SetPen(*wxBLACK_PEN);
		buffDC.SetBrush(*wxGREY_BRUSH);
		buffDC.DrawCircle(wxPoint(-100, -100), 50);
		buffDC.SetPen(*wxWHITE_PEN);
		buffDC.SetBrush(*wxWHITE_BRUSH);
		buffDC.DrawCircle(wxPoint(-100 - 15, -100 - 15), 43);
		buffDC.SetPen(*wxBLACK_PEN);
		buffDC.SetBrush(*wxBLACK_BRUSH);
		buffDC.DrawCircle(wxPoint(-72, -100), 4);
		buffDC.DrawLine(wxPoint(-85, -70), wxPoint(-100, -75));
	} else {
		buffDC.SetPen(*wxBLACK_PEN);
		buffDC.SetBrush(*wxYELLOW_BRUSH);
		buffDC.DrawCircle(wxPoint(-100, -100), 50);
	}
	//drawing text
	buffDC.SetPen(wxPen(wxColor(0, 0, 0), 3));
	buffDC.DrawText(text, wxPoint(-60 , radius + 150));
	// wxDEFAULT, wxDECORATIVE, wxROMAN, wxSCRIPT, wxSWISS, wxMODERN. wxMODERN
	buffDC.SetFont(wxFont(25, wxSCRIPT, wxITALIC, wxBOLD));
	buffDC.DrawRotatedText(text, wxPoint(80, radius + 130), 90);
}
