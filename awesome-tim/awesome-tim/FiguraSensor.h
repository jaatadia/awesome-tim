#pragma once
#include "figura.h"
#include <list>
#include "MotorRaton.h"
#include "JuegoPlayCliente.h"

class FiguraSensor :
	public Figura
{
private:

	Figura* figInteractuar; //para sacarle el numero
	int numInteractuar;
	//int ID;

	FiguraSensor(double ancho,double alto,double posX,double posY,double angulo,int numero):Figura("",new Cuadrado(ancho,alto,posX,posY,angulo),false){
	
		this->numInteractuar = numero;
	};

public:
	FiguraSensor(double ancho,double alto,double posX,double posY,double angulo,Figura* figura);
	~FiguraSensor(void);
	virtual int getTipoFigura();
	virtual int getTipoDimension();
	Figura* clonar();

	//virtual void accionarMotor(Figura** vector);
	virtual void cumplirObjetivo(Figura** vec,Figura* fig);

	//FIX: espero que sean estas las q tengo q hacer false (?) 
	virtual bool intersecaCon(double X1, double Y1, double X2, double Y2);
	virtual bool choqueConFigura(Figura* fig);
	virtual bool choqueConDimension(Dimension* dim);
	virtual	void dibujar(Superficie* super);
};
