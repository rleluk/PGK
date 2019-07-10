#include <wx/dc.h>
#include <memory>
#define _MATH_DEFINES
#include <math.h>

#include "ChartClass.h"
#include "vecmat.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c)
{
	cfg = std::move(c);
	x_step = 200;
}

void ChartClass::Set_Range()
{
	double xmin = 9999.9, xmax = -9999.9, ymin = 9999.9, ymax = -9999.9;
	double x, y, step;
	int i;

	xmin = cfg->Get_x_start();
	xmax = cfg->Get_x_stop();

	step = (cfg->Get_x_stop() - cfg->Get_x_start()) / (double)x_step;
	x = cfg->Get_x_start();

	for (i = 0; i <= x_step; i++)
	{
		y = GetFunctionValue(x);
		if (y > ymax) ymax = y;
		if (y < ymin) ymin = y;
		x = x + step;
	}

	y_min = ymin;
	y_max = ymax;
	x_min = xmin;
	x_max = xmax;
}

double ChartClass::GetFunctionValue(double x)
{
	if (cfg->Get_F_type() == 1) return x * x;
	if (cfg->Get_F_type() == 2) return 0.5*exp(4 * x - 3 * x*x);
	return x + sin(x*4.0);
}

double ChartClass::Get_Y_min()
{
	Set_Range();
	return y_min;
}

double ChartClass::Get_Y_max()
{
	Set_Range();
	return y_max;
}

/////////////////////// funkcje zmienione ///////////////////////

void ChartClass::line2d(Matrix transformation, double x1, double y1, double x2, double y2, wxDC *dc, int w, int h)
{
	Vector start, end;
	start.Set(x1, y1);
	start = transformation * start;

	end.Set(x2, y2);
	end = transformation * end;

	dc->DrawLine(start.GetX(), h - start.GetY(), end.GetX(), h - end.GetY());
}

Matrix ChartClass::transform(int w, int h) {
	// je¿eli x1 <= x0 lub y1 <= y0, to nie chcemy nic rysowaæ
	if (cfg->Get_x1() <= cfg->Get_x0() || cfg->Get_y1() <= cfg->Get_y0()) {
		_draw = false;
		return Matrix();
	}

	_draw = true;

	// translating
	Matrix translationMatrix;
	translationMatrix.data[0][0] = translationMatrix.data[1][1] = 1.;
	translationMatrix.data[0][2] = cfg->Get_dX();
	translationMatrix.data[1][2] = cfg->Get_dY();

	// scaling
	Matrix scaleMatrix;
	scaleMatrix.data[0][0] = (w - 20.) / (cfg->Get_x1() - cfg->Get_x0());
	scaleMatrix.data[1][1] = (h - 20.) / (cfg->Get_y1() - cfg->Get_y0());
	scaleMatrix.data[0][2] = 10. - scaleMatrix.data[0][0] * cfg->Get_x0();
	scaleMatrix.data[1][2] = 10. - scaleMatrix.data[1][1] * cfg->Get_y0();

	// rotating
	Matrix rotationMatrix;
	rotationMatrix.data[0][0] = rotationMatrix.data[1][1] = cos(cfg->Get_Alpha() * M_PI / 180);
	rotationMatrix.data[0][1] = -sin(cfg->Get_Alpha() * M_PI / 180);
	rotationMatrix.data[1][0] = sin(cfg->Get_Alpha() * M_PI / 180);

	Matrix translation1, translation2;
	translation1.data[0][0] = translation1.data[1][1] = 1.;
	translation2.data[0][0] = translation2.data[1][1] = 1.;

	if (cfg->RotateScreenCenter()) {
		translation1.data[0][2] = w / 2.0; 
		translation1.data[1][2] = h / 2.0;
	} else {
		translation1.data[0][2] = scaleMatrix.data[0][2];
		translation1.data[1][2] = scaleMatrix.data[1][2];
	}
	translation2.data[0][2] = -translation1.data[0][2];
	translation2.data[1][2] = -translation1.data[1][2];

	rotationMatrix = translation1 * rotationMatrix * translation2;

	if (cfg->RotateScreenCenter())
		return rotationMatrix * translationMatrix * scaleMatrix;
	else
		return translationMatrix * rotationMatrix * scaleMatrix;
}

void ChartClass::drawText(wxDC *dc, Matrix transformation, wxString text, double x, double y, int h) {
	Vector rotText;
	rotText.Set(x, y);
	rotText = transformation * rotText;
	dc->DrawRotatedText(text, rotText.GetX(), h - rotText.GetY(), cfg->Get_Alpha());
}

void ChartClass::drawAxes(wxDC *dc, Matrix transformation, int w, int h) {
	line2d(transformation, cfg->Get_x_start(), 0, cfg->Get_x_stop(), 0, dc, w, h);
	line2d(transformation, 0, Get_Y_min(), 0, Get_Y_max(), dc, w, h);
	const double dx = 1 + static_cast<int>((cfg->Get_x1() - cfg->Get_x0()) / 10.);
	const double dy = 1 + static_cast<int>((cfg->Get_y1() - cfg->Get_y0()) / 10.);

	// "podzia³ki" na osi x
	for (double x = x_min; x < x_max; x += dx/2) {
		if (x > 0.1 || x < -0.1) {
			line2d(transformation, x, -0.05, x, 0.05, dc, w, h);
			drawText(dc, transformation, wxString::Format(wxT("%.2g"), x), x, -0.1, h);
		}
	}

	// strza³ka na koñcu osi x
	line2d(transformation, x_max, 0, x_max - 0.05, 0.05, dc, w, h);
	line2d(transformation, x_max, 0, x_max - 0.05, -0.05, dc, w, h);

	// "podzia³ki" na osi y
	for (double y = y_min; y < y_max; y += dy/2) {
		if (y > 0.1 || y < -0.1) {
			line2d(transformation, -0.05, y, 0.05, y, dc, w, h);
			drawText(dc, transformation, wxString::Format(wxT("%.2g"), y), 0.1, y, h);
		}
	}

	// strza³ka na koñcu osi y
	line2d(transformation, 0, y_max, 0.05, y_max - 0.05, dc, w, h);
	line2d(transformation, 0, y_max, -0.05, y_max - 0.05, dc, w, h);
}

void ChartClass::Draw(wxDC *dc, int w, int h)
{
	dc->SetBackground(wxBrush(RGB(255, 255, 255)));
	dc->Clear();
	dc->SetPen(wxPen(RGB(255, 0, 0)));
	dc->DrawRectangle(10, 10, w - 20, h - 20);
	dc->SetClippingRegion(wxRect(10, 10, w - 20, h - 20)); 

	Matrix transformation = transform(w, h); // transformation matrix

	// nie rysuje je¿eli x1 <= x0 lub y1 <= y0
	if (!_draw)
		return;

	// rysowanie osi x i y
	dc->SetFont(*wxSMALL_FONT);
	dc->SetPen(wxPen(RGB(0, 0, 255)));
	drawAxes(dc, transformation, w, h);

	// rysowanie wykresu
	dc->SetPen(wxPen(RGB(0, 255, 0)));
	double delta = (cfg->Get_x1() - cfg->Get_x0()) / x_step;	
	for (double x = cfg->Get_x_start(); x < cfg->Get_x_stop(); x += delta) {
		line2d(transformation, x, GetFunctionValue(x), x + delta, GetFunctionValue(x + delta), dc, w, h);
	}
}
