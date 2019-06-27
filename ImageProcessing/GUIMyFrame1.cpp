#include "GUIMyFrame1.h"
#define _MATH_DEFINES
#include <math.h>
#include <omp.h>

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
	 m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
	 m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
	 this->SetBackgroundColour(wxColor(192, 192, 192));
	 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
	 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
	 Repaint();
}			

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy().ConvertToGreyscale();
}

void GUIMyFrame1::m_b_blur_click(wxCommandEvent& event)
{
	Img_Cpy = Img_Org.Copy().Blur(5);
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy().Mirror();
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
}	

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy().Rescale(320, 240);
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy().Rotate(30 * M_PI / 180., wxPoint(Img_Org.GetWidth() / 2., Img_Org.GetHeight() / 2));
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.RotateHue(0.5);
}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
	Brightness(m_s_brightness->GetValue() - 100);
	Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
	Contrast(m_s_contrast->GetValue() - 100);
	Repaint();
}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
    Img_Cpy = Img_Org.Copy();
	unsigned char * pixels = Img_Cpy.GetData();
	unsigned char * old = new unsigned char[Img_Cpy.GetHeight() * Img_Cpy.GetWidth() * 3];
#pragma omp parallel for
	for (int i = 0; i < Img_Cpy.GetHeight() * Img_Cpy.GetWidth() * 3; i++)
		old[i] = pixels[i];
#pragma omp parallel for
	for (int i = 1; i < Img_Cpy.GetHeight() - 1; i++) {
		for (int j = 1; j < Img_Cpy.GetWidth() - 1; j++) {
			for (int c = 0; c < 3; ++c) {
                int val = 0;
                val +=      old[c +  i      * Img_Cpy.GetWidth() * 3 + (j + 1) * 3];
                val +=    - old[c +  i      * Img_Cpy.GetWidth() * 3 + (j - 1) * 3];
                val +=      old[c + (i + 1) * Img_Cpy.GetWidth() * 3 + (j + 1) * 3];
                val +=    - old[c + (i + 1) * Img_Cpy.GetWidth() * 3 + (j - 1) * 3];
                val +=      old[c + (i - 1) * Img_Cpy.GetWidth() * 3 + (j + 1) * 3];
                val +=    - old[c + (i - 1) * Img_Cpy.GetWidth() * 3 + (j - 1) * 3];
                pixels[c + i * Img_Cpy.GetWidth() * 3 + j * 3] = fabs(val) / 3.0;
			}
		}
	}
	delete old;
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	unsigned char *pixels = Img_Cpy.GetData();
#pragma omp parallel for
	for (int i = 0; i < Img_Cpy.GetHeight() * Img_Cpy.GetWidth() * 3; i++) 
		pixels[i] = pixels[i] > 128 ? 255 : 0;
}


void GUIMyFrame1::Contrast(int value)
{
	Img_Cpy = Img_Org.Copy();
	unsigned char *pixels = Img_Cpy.GetData();
	int tmp;
	double alpha = (value + 100) / (double)(101 - value);
#pragma omp parallel for
	for (int i = 0; i < Img_Cpy.GetHeight() * Img_Cpy.GetWidth() * 3; i++) {
		tmp = alpha * (pixels[i] - 128) + 128;
		if (tmp > 255)
			tmp = 255;
		else if (tmp < 0)
			tmp = 0;
		pixels[i] = tmp;
	}
}

void GUIMyFrame1::Repaint()
{
 wxBitmap bitmap(Img_Cpy);          
 wxClientDC dc(m_scrolledWindow);   
 wxBufferedDC buffDC(&dc);
 buffDC.Clear();
 m_scrolledWindow->DoPrepareDC(buffDC); 
 buffDC.DrawBitmap(bitmap, 0, 0, true); 
}

void GUIMyFrame1::Brightness(int value)
{
	Img_Cpy = Img_Org.Copy();
	unsigned char *pixels = Img_Cpy.GetData();
	int tmp;
#pragma omp parallel for
	for (int i = 0; i < Img_Cpy.GetHeight() * Img_Cpy.GetWidth() * 3; i++) {
		tmp = pixels[i] + value;
		if (tmp > 255)
			tmp = 255;
		else if (tmp < 0)
			tmp = 0;
		pixels[i] = tmp;
	}
}

void GUIMyFrame1::dodatkowe_click(wxCommandEvent& event) {
	Img_Cpy = Img_Org.Copy();
	unsigned char *pixels = Img_Cpy.GetData();
	int width = Img_Cpy.GetWidth();
	int height = Img_Cpy.GetHeight();
#pragma omp parallel for
	for (int x = 0; x < width / 2; x++) {
		for (int y = 0; y < height; y++) {
			pixels[3 * (width * y + x) + 0] = Img_Cpy.GetRed(x, y);
			pixels[3 * (width * y + x) + 1] = Img_Cpy.GetRed(x, y);
			pixels[3 * (width * y + x) + 2] = Img_Cpy.GetRed(x, y);
		}
	}
}