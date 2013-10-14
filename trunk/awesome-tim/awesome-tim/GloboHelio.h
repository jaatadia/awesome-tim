#pragma once
#include "Circulo.h"
#include "Constantes.h"
#include "Figura.h"

class GloboHelio : public Figura
{
private:
	GloboHelio(const char* id,Dimension* dim,bool flag):Figura(id,dim){
		atado = false;
	};
	bool atado;

public:
	GloboHelio(double pos_X,double pos_Y):Figura(ID_GLOBO,new Circulo(RADIO_GLOBOHELIO,pos_X,pos_Y,0)){
		atado = false;
	};
	~GloboHelio(void){};

	virtual int getTipoFigura(){return GLOBOHELIO;}
	virtual int getTipoDimension(){return CIRCULO;}

	Figura* clonar(){
		return new GloboHelio(ID.c_str(),dimension->clonar(),true);
	};

	//se le pasa la poicion en la que esta queriendo atar y devuelve el numero de posicion atable mas cercano(-1 es que no habia)
	virtual int esAtableSoga(double x,double y){
		if(!atado){
			return 1;
		}else{
			return -1;
		}
	}
	
	//se le pasa un numero de posicion atable y devuelve la posicion x e y de donde se ata por mas que ya este atado
	virtual void posAtableSoga(int numero,double* x,double* y){
		*x = this->getDimension()->getX();
		*y = this->getDimension()->getY() + this->getDimension()->getAlto()*5/12;
	}
	
	virtual void atarSoga(int numero){
		if(numero == 1) atado = true;
	};//le dice que ate una soga en su pocicion atable numero
	
	virtual void desatarSoga(int numero){
		if(numero == 1) atado = false;
	};//le dice que desate una soga de su posicion atable numero

//	bool choqueConFigura(Figura* fig);
};
