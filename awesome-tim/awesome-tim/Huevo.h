#pragma once
#include "Circulo.h"
#include "Constantes.h"
#include "Figura.h"

class Huevo : public Figura
{

private:
	Huevo(const char* id,Dimension* dim,bool flag):Figura(id,dim){
		rompiendose = false;
		contador = 0;
	};
	
	bool rompiendose;
	int contador;

public:
	Huevo(double pos_X,double pos_Y):Figura(ID_HUEVO,new Circulo(RADIO_HUEVO,pos_X,pos_Y,0)){
		rompiendose = false;
		contador = 0;
	};
	~Huevo(void){};

	virtual int getTipoFigura(){return HUEVO;}
	virtual int getTipoDimension(){return CIRCULO;}
	
	Figura* clonar(){
		return new Huevo(ID.c_str(),dimension->clonar(),true);
	}


//	bool choqueConFigura(Figura* fig);
	void pinchar(){
		rompiendose = true;
	}

	bool estaPinchando(){
		return rompiendose;
	}

	void actualizar(){
		if(rompiendose){
			contador++;

			if(contador == 1){
				this->ID = ID_HUEVO_ROMPIENDO; 
				delete (this->myVista);
				this->myVista = new VistaFigura(this);
			}

			if(contador == FPS/4){
				this->marcar(true);
			}
		}
	}

	void interactuar(){
		this->pinchar();
	}
};