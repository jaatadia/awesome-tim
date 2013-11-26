#pragma once

#include "Dimension.h"
#include "Constantes.h"

class DLinea: public Dimension
{
public:
	double x1, y1, x2, y2, ancho;
	bool activo;
public:
	DLinea(double x1,double y1,double x2,double y2,double ancho):Dimension(x1,y1,0){
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		this->ancho = ancho;
		activo = false;
	};

	~DLinea(void){};

	virtual double getAncho(){
		if(!activo)return 10;
		else return abs(x1-x2)*2;
	};
	virtual double getAlto(){
		if(!activo)return 10;
		else return abs(y1-y2)*2;
	};
	
	virtual int getTipoDimension(){return LINEA;};
	
	virtual Dimension* clonar(){return new DLinea(x1,y1,x2,y2,ancho);};

	bool puntoPertenece(double pos_X, double pos_Y){
/*		bool pertenece = false;
		if(y1<=y2){
			pertenece = ((pos_Y>=y1)&&(pos_Y<=y2));
		}else{
			pertenece = ((pos_Y<=y1)&&(pos_Y>=y2));
		}
		if(!pertenece) return false;

		double centroX = (x1+x2)/2.0;
		double centroY = (y1+y2)/2.0;
			
		double margen = 1;
		
		double signoC = (centroX-(x1+margen))/(x2-x1) - (centroY-y1)/(y2-y1);
		double signo = (pos_X-(x1+margen))/(x2-x1) - (pos_Y-y1)/(y2-y1);
		if (!(((signoC<=0)&&(signo<=0))||((signoC>=0)&&(signo>=0)))){
			return false;
		}

		signoC = (centroX-(x1-margen))/(x2-x1) - (centroY-y1)/(y2-y1);
		signo = (pos_X-(x1-margen))/(x2-x1) - (pos_Y-y1)/(y2-y1);
		if (!(((signoC<=0)&&(signo<=0))||((signoC>=0)&&(signo>=0)))){
			return false;
		}

		return true;
*/
		return false;
	};

	
	void putP1(double x,double y){
		activo = true;
		this->x1 = x;
		this->y1 = y;
	}

	void putP2(double x,double y){
		setX(x);
		setY(y);
	}

	void setX(double x){
		this->x = x;
		this->x2 = x;
	};

	void setY(double y){
		this->y = y;
		this->y2 = y;
	};
};
