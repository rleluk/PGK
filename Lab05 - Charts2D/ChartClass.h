#ifndef __ChartClass__
#define __ChartClass__

#include <memory>
#include "ConfigClass.h"
class Matrix;

class ChartClass
{
public:
	ChartClass(std::shared_ptr<ConfigClass> c);
	void Set_Range();   // ustala wartosci zmiennych x_min,y_min,x_max,y_max
	double Get_Y_min(); // zwraca y_min
	double Get_Y_max(); // zwraca y_max
	void Draw(wxDC *dc, int w, int h);  // rysuje wykres

private:
	std::shared_ptr<ConfigClass> cfg;
	int x_step;         // liczba odcinkow z jakich bedzie sie skladal wykres
	double x_min, x_max; // zakres zmiennej x
	double y_min, y_max; // zakres wartosci przyjmowanych przez funkcje
	double GetFunctionValue(double x); // zwraca wartosci rysowanej funkcji

	///////////////////////
	bool _draw = true;

	void line2d(Matrix transformation, double x1, double y1, double x2, double y2, wxDC *dc, int w, int h);
	Matrix transform(int w, int h);
	void drawAxes(wxDC *dc, Matrix transformation, int w, int h);
	void drawText(wxDC *dc, Matrix transformation, wxString text, double x, double y, int h);
};

#endif
