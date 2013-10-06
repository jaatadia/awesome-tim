#pragma once
#include "figura.h"

class Plataforma :
	public Figura
{
public:
	Plataforma(double largo,double pos_x,double pos_y,double angulo);
	~Plataforma(void);
};
