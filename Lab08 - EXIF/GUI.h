#pragma once
#include "MyFrame.h"
#include <array>
class GUI : public MyFrame {
	public:
		GUI::GUI();
		void refresh(wxClientDC &dc);

	private:
		virtual void LoadImageOnButtonClick(wxCommandEvent& event);
		virtual void CensorshipOnButtonClick(wxCommandEvent& event);
		virtual void ErodeOnButtonClick(wxCommandEvent& event);
		virtual void AnimationOnCheckBox(wxCommandEvent& event);
		virtual void MyFrameOnUpdateUI(wxUpdateUIEvent& event);

		wxImage imgCopy;
		wxImage imgOrg;
		std::array<wxBitmap, 360> animations;
		int tick = 1;
};

