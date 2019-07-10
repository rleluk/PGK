#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"

struct Point {
 float x, y, z;
 Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
 int R, G, B;
 Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
 Point begin, end;
 Color color;
 Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
 m_staticText25->SetLabel(_("Obr\u00F3t X:"));
 m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
 m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

 WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
 WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
 WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

 WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
 WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
 WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

 WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(2.7 * 40);
 WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(2.8 * 40);
 WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);

 update_labels();
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
 Repaint();
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
 wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

 if (WxOpenFileDialog.ShowModal() == wxID_OK)
 {
  double x1, y1, z1, x2, y2, z2;
  int r, g, b;

  std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
  if (in.is_open())
  {
   data.clear();
   while (!in.eof())
   {
    in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
    data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
   }
   in.close();
  }

  WxSB_TranslationX->SetValue(100);
  WxSB_TranslationY->SetValue(100);
  WxSB_TranslationZ->SetValue(100);

  WxSB_RotateX->SetValue(0);
  WxSB_RotateY->SetValue(0);
  WxSB_RotateZ->SetValue(0);

  WxSB_ScaleX->SetValue(100);
  WxSB_ScaleY->SetValue(100);
  WxSB_ScaleZ->SetValue(100);

  update_labels();
 }
}

void GUIMyFrame1::ScrollX_Updated(wxScrollEvent& event) {
	int value = WxSB_ScaleX->GetValue() / 40. * 100.;
	if (value <= 15) {
		WxSB_ScaleX->SetValue(.15);
		return;
	}

	int remainder = value % 15;
	if (remainder != 0) {
		value -= remainder;
		WxSB_ScaleX->SetValue(value * 40. / 100.);
	}
	update_labels();
}

void GUIMyFrame1::ScrollY_Updated(wxScrollEvent& event) {
	int value = WxSB_ScaleY->GetValue() / 40. * 10.;
	if (value <= 7) {
		WxSB_ScaleY->SetValue(.7);
		return;
	}

	int remainder = value % 7;
	if (remainder != 0) {
		value -= remainder;
		WxSB_ScaleY->SetValue(value * 40. / 10.);
	}
	update_labels();
}

void GUIMyFrame1::ScrollZ_Updated(wxScrollEvent& event) {
	update_labels();
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
	update_labels();
}

void GUIMyFrame1::update_labels() {
	WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 10.0));
	WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 10.0));
	WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 10.0));

	WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
	WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
	WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

	WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 40.0));
	WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 40.0));
	WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 40.0));

	Repaint();
}

Matrix4 GUIMyFrame1::getRotationMatrix() {
	Matrix4 rotX, rotY, rotZ;
	const double angleX = WxSB_RotateX->GetValue() * M_PI / 180;
	const double angleY = WxSB_RotateY->GetValue() * M_PI / 180;
	const double angleZ = WxSB_RotateZ->GetValue() * M_PI / 180;

	rotX.data[0][0] = rotY.data[1][1] = rotZ.data[2][2] = 1.;
	
	// rotation X
	rotX.data[1][1] = rotX.data[2][2] = cos(angleX);
	rotX.data[2][1] = sin(angleX);
	rotX.data[1][2] = -sin(angleX);

	// rotation Y
	rotY.data[0][0] = rotY.data[2][2] = cos(angleY);
	rotY.data[0][2] = -sin(angleY);
	rotY.data[2][0] = sin(angleY);

	// rotation Z
	rotZ.data[0][0] = rotZ.data[1][1] = cos(angleZ);
	rotZ.data[1][0] = sin(angleZ);
	rotZ.data[0][1] = -sin(angleZ);

	return rotX * rotY * rotZ;
}

Matrix4 GUIMyFrame1::getScaleMatrix() {
	Matrix4 scale;
	scale.data[0][0] = WxSB_ScaleX->GetValue() / 40.;
	scale.data[1][1] = -WxSB_ScaleY->GetValue() / 40.;
	scale.data[2][2] = WxSB_ScaleZ->GetValue() / 40.;
	return scale;
}

Matrix4 GUIMyFrame1::getTranslationMatrix() {
	Matrix4 translate;
	translate.data[0][0] = translate.data[1][1] = translate.data[2][2] = 1.;
	translate.data[0][3] = (WxSB_TranslationX->GetValue() - 100.) / 10.;
	translate.data[1][3] = -(WxSB_TranslationY->GetValue() - 100.) / 10.;
	translate.data[2][3] = (WxSB_TranslationZ->GetValue() - 100.) / 10. + 10.01;
	return translate;
}

Matrix4 GUIMyFrame1::getCenterMatrix() {
	Matrix4 center;
	center.data[0][0] = center.data[1][1] = center.data[2][2] = 1.;
	center.data[0][3] = center.data[1][3] = 0.5;
	return center;
}

void GUIMyFrame1::Repaint()
{
	wxClientDC dc(WxPanel);
	wxBufferedDC buffDC(&dc);
	int width = WxPanel->GetSize().GetX();
	int height = WxPanel->GetSize().GetY();
	buffDC.SetBackground(wxBrush(wxColor(255, 255, 255)));
	buffDC.Clear();

	Matrix4 transformation = getTranslationMatrix() * getRotationMatrix() * getScaleMatrix();
	Matrix4 center = getCenterMatrix();
	bool draw = true;
	for (auto &element : data) {
		Vector4 start, end;
		draw = true;

		start.Set(element.begin.x, element.begin.y, element.begin.z);
		start = transformation * start;

		end.Set(element.end.x, element.end.y, element.end.z);
		end = transformation * end;

		if(start.GetZ() < 0. && end.GetZ() < 0.) 
			draw = false;
		else if (start.GetZ() < 0.)
			start.data[2] = 0.001;
		else if (end.GetZ() < 0.)
			end.data[2] = 0.001;

		start.Set(start.GetX() / start.GetZ(), start.GetY() / start.GetZ(), start.GetZ());
		start = center * start;
		
		end.Set(end.GetX() / end.GetZ(), end.GetY() / end.GetZ(), end.GetZ());
		end = center * end;
		
		if (draw) {
			buffDC.SetPen(wxPen(wxColor(element.color.R, element.color.G, element.color.B)));
			buffDC.DrawLine(start.GetX() * width, start.GetY() * height, end.GetX() * width, end.GetY() * height);
		}
	}
}