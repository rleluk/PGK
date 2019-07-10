#pragma once
#include "GUI.h"

#include <wx/wxprec.h>
#include <wx/dcbuffer.h>
#include <wx/dcmemory.h>
#include <wx/colordlg.h>

class MyFrame : public GUI {
public:
	MyFrame();

private:
	wxColour *starColour;
	wxBitmap *bananaBitmap;
	wxPoint starXY[5];
	wxFileDialog *saveDialog;
	/////////////////////
	bool isBanana = false;
	int bananaPosition = 0;
	wxString text = "tekst";
	int choice = STAR;

	virtual void panelOnPaint(wxPaintEvent& event);
	virtual void panelOnUpdateUI(wxUpdateUIEvent& event);
	virtual void saveToFileButtonOnButtonClick(wxCommandEvent& event);
	virtual void bananaCheckBoxOnCheckBox(wxCommandEvent& event);
	virtual void bananaPositionScrollBarOnScroll(wxScrollEvent& event);
	virtual void startColorButtonOnButtonClick(wxCommandEvent& event);
	virtual void editOnText(wxCommandEvent& event);
	virtual void choiceBoxOnChoice(wxCommandEvent& event);
	virtual void drawOnPanel(wxClientDC &dc);

	enum {
		STAR = 0,
		MOON = 1,
		SUN = 2
	};
};
