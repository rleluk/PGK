#include "GUI.h"
#include <wx/dcbuffer.h>
#include <wx/window.h>
#include <string>
#include <wx/filedlg.h>
#include "FreeImage.h"
#include "CImg.h"
#include <omp.h>

GUI::GUI() : MyFrame::MyFrame(nullptr) {
	m_panel1->SetBackgroundColour(wxColor(*wxBLACK));
	wxImage::AddHandler(new wxJPEGHandler);
}

void GUI::LoadImageOnButtonClick(wxCommandEvent& event) {
	//wxClientDC dc(m_panel1);
	wxImage::AddHandler(new wxJPEGHandler);
	wxFileDialog *loadDialog = new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("JPEG files (*.jpg)|*.jpg"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (loadDialog->ShowModal() == wxID_OK) {
		FIBITMAP *dib = FreeImage_Load(FIF_JPEG, loadDialog->GetPath(), JPEG_DEFAULT);
		wxString metadata = "";
		metadata << "Rozmiar obrazka: " << FreeImage_GetWidth(dib) << "*" << FreeImage_GetHeight(dib) << "\r\n" << "EXIF INFO: \r\n";
		if (FreeImage_GetMetadataCount(FIMD_EXIF_MAIN, dib)) {
			FITAG *tag = NULL;
			FIMETADATA *mdhandle = NULL;
			mdhandle = FreeImage_FindFirstMetadata(FIMD_EXIF_MAIN, dib, &tag);
			if (mdhandle) {
				do {
					metadata << FreeImage_GetTagKey(tag) << ": " << FreeImage_TagToString(FIMD_EXIF_MAIN, tag) << "\r\n";
				} while (FreeImage_FindNextMetadata(mdhandle, &tag));
			}
			FreeImage_FindCloseMetadata(mdhandle);
		}
		FreeImage_Unload(dib);
		imgOrg.LoadFile(loadDialog->GetPath(), wxBITMAP_TYPE_JPEG);
		imgCopy = imgOrg.Copy();
		m_textCtrl1->Clear();
		m_textCtrl1->AppendText(metadata);
		//refresh(dc);
	}
}

void GUI::CensorshipOnButtonClick(wxCommandEvent& event) {
	//wxClientDC dc(m_panel1);
	if (imgOrg.Ok()) {
		imgCopy = imgOrg.Copy();
		const int height = 0.15 * imgCopy.GetHeight();
		const int width = 0.15 * imgCopy.GetWidth();
		const int x_0 = 0.57 * imgCopy.GetWidth();
		const int y_0 = 0.02 * imgCopy.GetHeight();
		cimg_library::CImg<unsigned char> cImage(width, height, 1, 3);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				cImage(i, j, 0) = imgCopy.GetRed(x_0 + i, y_0 + j);
				cImage(i, j, 1) = imgCopy.GetGreen(x_0 + i, y_0 + j);
				cImage(i, j, 2) = imgCopy.GetBlue(x_0 + i, y_0 + j);
			}
		}
		cImage.blur(3);
		for (int i = 0; i < width; i++) 
			for (int j = 0; j < height; j++) 
				imgCopy.SetRGB(x_0 + i, y_0 + j, cImage(i, j, 0), cImage(i, j, 1), cImage(i, j, 2));
			
		//refresh(dc);
	}
}

void GUI::ErodeOnButtonClick(wxCommandEvent& event) {
	//wxClientDC dc(m_panel1);
	if (imgOrg.Ok()) {
		imgCopy = imgOrg.Copy();
		const int height = imgCopy.GetHeight();
		const int width = imgCopy.GetWidth();
		cimg_library::CImg<unsigned char> cImage(width, height, 1, 3);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				cImage(i, j, 0) = imgCopy.GetRed(i, j);
				cImage(i, j, 1) = imgCopy.GetGreen(i, j);
				cImage(i, j, 2) = imgCopy.GetBlue(i, j);
			}
		}
		cImage.erode(6);
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				imgCopy.SetRGB(i, j, cImage(i, j, 0), cImage(i, j, 1), cImage(i, j, 2));

		//refresh(dc);
	}
}

void GUI::AnimationOnCheckBox(wxCommandEvent& event) {
	if (imgOrg.IsOk() && Animation->IsChecked()) {
		int height = imgOrg.GetSize().y;
		int width = imgOrg.GetSize().x;

		cimg_library::CImg<float> copy(width, height, 1, 3);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				copy(i, j, 0) = imgOrg.GetRed(i, j);
				copy(i, j, 1) = imgOrg.GetGreen(i, j);
				copy(i, j, 2) = imgOrg.GetBlue(i, j);
			}
		}

		float* spec = new float[3]{ 1.0f, 1.0f, 1.0f };

#pragma omp parallel
#pragma omp for schedule(dynamic, 16)
		for (int i = 359; i >= 0; --i) {
			cimg_library::CImg<float> gauss(width, height, 1, 3);
			cimg_library::CImg<float> gauss2(width, height, 1, 3);
			cimg_library::CImg<float> tmp(copy);

			float* CImgData = tmp.data();

			gauss.draw_gaussian(width / 2 + (width * 0.4) * cos(i / 2 * acos(-1) / 180.0),
				height / 2 + (height * 0.4) * sin(i / 2 * acos(-1) / 180.0), 150.0f, spec, 1.0f);
			gauss2.draw_gaussian(width / 2 + (width * 0.4) * cos(((i / 2 + 180) % 360) * acos(-1) / 180.0),
				height / 2 + (height * 0.4) * sin(((i / 2 + 180) % 360) * acos(-1) / 180.0), 150.0f, spec, 1.0f);
			gauss += gauss2;
			tmp.mul(gauss);

			unsigned char* newData = static_cast<unsigned char*>(malloc(width * height * 3 * sizeof(unsigned char)));
			wxImage animation;

			for (int y = 0; y < height; ++y) {
				for (int x = 0; x < width; ++x) {
					newData[3 * (width * y + x) + 0] = CImgData[width * height * 0 + width * y + x];
					newData[3 * (width * y + x) + 1] = CImgData[width * height * 1 + width * y + x];
					newData[3 * (width * y + x) + 2] = CImgData[width * height * 2 + width * y + x];
				}
			}
			animation.SetData(newData, width, height, true);
			//animation.Rescale(m_panel1->GetSize().x, m_panel1->GetSize().y);
			animations[i] = wxBitmap(animation);
			delete newData;
		}
		delete spec;
	}
}

void GUI::refresh(wxClientDC &dc) {
  wxBufferedDC buffDC(&dc);
	if (imgOrg.Ok()) {
		if (Animation->IsChecked() && animations.size() > 0) {
			buffDC.DrawBitmap(animations[tick], 0, 0);
			tick = (tick + 1) % 360;
			Update();
			RefreshRect(wxRect(1, 1, 1, 1), false);
		} else {
			imgCopy.Rescale(dc.GetSize().x, dc.GetSize().y);
			wxBitmap bitmap(imgCopy);
			buffDC.DrawBitmap(bitmap, 0, 0);
		}
	}
}

void GUI::MyFrameOnUpdateUI(wxUpdateUIEvent& event) {
	wxClientDC dc(m_panel1);
	refresh(dc);
}