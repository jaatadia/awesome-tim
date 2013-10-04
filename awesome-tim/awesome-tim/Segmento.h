#pragma once
#include "Recta.h"

class Segmento : public Recta
{
private:
	double XInicial, XFinal, YInicial, YFinal;
	double XMin, XMax, YMin, YMax;

public:
	Segmento(double X1, double Y1, double X2, double Y2);
	~Segmento(void);

	bool intersecaCon(Recta* otraRecta);
	bool intersecaCon(Segmento* otroSegmento);

	double getXInicial(){ return XInicial;};

	double getXFinal(){ return XFinal;};

	double getYInicial(){ return YInicial;};

	double getYFinal(){ return YFinal;};

	double getXMax(){ return XMax;};

	double getXMin(){ return XMin;};
};

