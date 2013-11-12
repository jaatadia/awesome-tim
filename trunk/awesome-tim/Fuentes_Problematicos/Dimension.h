#pragma once

#include "Posicion.h"
#include "Segmento.h"

class Dimension: public Posicion
{
protected:
	//el angulo de la figura
	double angulo; // de 0 a 360 !!

	//el angulo verdadero de los puntos
	double anguloReal;

public:

	Dimension(double X, double Y,double ang):Posicion(X,Y){
		while(ang<0) ang+=360;
		while(ang>=360) ang-=360;
		this->angulo=ang;

		anguloReal = 0;
	};
	
	virtual ~Dimension(){};
	virtual double getAncho()=0;
	virtual double getAlto()=0;
	virtual int getTipoDimension()=0;
	virtual Dimension* clonar()=0;
	virtual void setAncho(double nuevoLargo){};

	virtual double getAngulo(){
		return angulo;
	};
	
	virtual double getAnguloReal(){
		return anguloReal;
	};

	virtual void setAngulo(double ang){
		while(ang<0) ang+=360;
		while(ang>=360) ang-=360;
		this->angulo=ang;
	};

	virtual void setAnguloReal(double ang){
		while(ang<0) ang+=360;
		while(ang>=360) ang-=360;
		this->anguloReal=ang;
	};

	virtual void putP1(double x,double y){};
	virtual void putP2(double x,double y){};

	virtual bool puntoPertenece(double X, double Y)=0;
	//la haria abstracta pero ahora mismo no se que dimensiones van a quedar, asi que implemento en poligono, circulo y cuadrado
	virtual bool intersecaCon(double X1, double Y1, double X2, double Y2){ return true;};

	//SOLO pensado para usar con circulos! (No olvidar castearlo si es necesario)
	virtual Dimension* devolverPoligonEnvolvente(){return NULL;};

	virtual bool choqueConDimension(Dimension* dim){return false;};
	//angulo es por cuantos grados lo quiero rotar, NO en que angulo tiene que quedar
	virtual Dimension* rotarDimension(double Xrot, double yRot, double angulo){return NULL;};
};
