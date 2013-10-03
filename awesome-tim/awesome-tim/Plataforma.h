#pragma once
#include "figura.h"

class Plataforma :
	public Figura
{
public:
	Plataforma(const char* ID,Dimension* dim);
	~Plataforma(void);
};
