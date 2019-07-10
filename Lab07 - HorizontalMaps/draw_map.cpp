#include <wx/wx.h>
#include "GUIMyFrame1.h"
#include <omp.h>
#define SIZE 500

inline double Shepard(int N, float d[100][3], float x, float y) {
	double numerator = 0.;
	double denominator = 0.;
	double w = 0.;
	for (int i = 0; i < N; i++) {
		w = 1. / fabs(pow(x - d[i][0], 2) + pow(y - d[i][1], 2));	
		numerator += w * d[i][2];
		denominator += w;
	}
	return numerator / denominator;
}


void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints)
{
 wxMemoryDC memDC;
 memDC.SelectObject(MemoryBitmap);
 memDC.SetBackground(*wxWHITE_BRUSH);
 memDC.Clear();

 memDC.SetPen(*wxBLACK_PEN);
 memDC.SetBrush(*wxTRANSPARENT_BRUSH);
 double approximation[SIZE][SIZE] = { 0 }, fMin = d[0][2], fMax = d[0][2];

#pragma omp parallel for

 for (int x = 0; x < SIZE; x++)
	 for (int y = 0; y < SIZE; y++)
		 approximation[x][y] = Shepard(N, d, x / 100. - 2.5, -y / 100. + 2.5); // [-2.5, 2.5] range
 
 for (int i = 0; i < N; i++) {
	 if (d[i][2] > fMax)
		 fMax = d[i][2];
	 if (d[i][2] < fMin)
		 fMin = d[i][2];	
 }


 if (MappingType) {
	 unsigned char* data = new unsigned char[SIZE * SIZE * 3];
	 switch (MappingType) {
	 case 1:
		 for (int x = 0; x < SIZE; x++) {
			 for (int y = 0; y < SIZE; y++) {
				 unsigned char color = static_cast<unsigned char>((approximation[x][y] - fMin) / (fMax - fMin) * 255.);
				 data[y * SIZE * 3 + x * 3 + 0] = 255 - color;
				 data[y * SIZE * 3 + x * 3 + 1] = 0;
				 data[y * SIZE * 3 + x * 3 + 2] = color;
			 }
		 }
		 break;
	 case 2:
		 for (int x = 0; x < SIZE; x++) {
			 for (int y = 0; y < SIZE; y++) {
				 float w_x = (approximation[x][y] - fMin) / (fMax - fMin);
				 data[y * SIZE * 3 + x * 3 + 0] = w_x < 0.5 ? (1 - 2 * w_x) * 255. : 0;
				 data[y * SIZE * 3 + x * 3 + 1] = w_x < 0.5 ? 2 * w_x * 255. : 2 * (1 - w_x) * 255.;
				 data[y * SIZE * 3 + x * 3 + 2] = w_x < 0.5 ? 0 : w_x / 2. * 255.;
			 }
		 }
		 break;
	 case 3:
		 for (int x = 0; x < SIZE; x++) {
			 for (int y = 0; y < SIZE; y++) {
				 unsigned char color = static_cast<unsigned char>((approximation[x][y] - fMin) / (fMax - fMin) * 255.);
				 data[y * SIZE * 3 + x * 3 + 0] = color;
				 data[y * SIZE * 3 + x * 3 + 1] = color;
				 data[y * SIZE * 3 + x * 3 + 2] = color;
			 }
		 }
		 break;
	 }
	 memDC.DrawBitmap(wxBitmap(wxImage(SIZE, SIZE, data)), 0, 0);
 }
  
 if (Contour) {
	 for (int level = 0; level < NoLevels; level++) {
		 float thresholdPoint = fMin + (level + 1) * (fMax - fMin) / (NoLevels + 1.0f);
		 for (int x = 0; x < SIZE; x++) {
			 for (int y = 0; y < SIZE; y++) {
				 if (approximation[x][y] > thresholdPoint) {
					 for (int i = -1; i <= 1; i++) {
						 for (int j = -1; j <= 1; j++) {
							 if (i != 0 && j != 0 && (x + i >= 0) && (x + i < SIZE) && (y + j >= 0) &&
								 (y + j < SIZE) && (approximation[x + i][y + j] < thresholdPoint)) {
								 memDC.DrawPoint(x, y);
							 }
						 }
					 }
				 }
			 }
		 }
	 }
 }

 if (ShowPoints) {
	 for (int i = 0; i < N; i++) {
		 // 0 - 500
		 const int x = static_cast<int>((d[i][0] + 2.5) * 100);
		 const int y = static_cast<int>((2.5 - d[i][1]) * 100);
		 memDC.DrawLine(x - 3, y, x + 4, y);
		 memDC.DrawLine(x, y - 3, x, y + 4);
	 }
 }
}