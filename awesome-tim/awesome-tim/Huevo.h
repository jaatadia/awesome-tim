#pragma once
#include "Circulo.h"
#include "Constantes.h"
#include "Figura.h"
#include "Sonidos.h"

#define FACTOR 4

class Huevo : public Figura
{

private:
	Huevo(const char* id,Dimension* dim,bool flag):Figura(id,dim){
		rompiendose = false;
		contador = -1;
	};
	
	bool rompiendose;
	int contador;

public:
	Huevo(double pos_X,double pos_Y):Figura(ID_HUEVO,new Circulo(RADIO_HUEVO,pos_X,pos_Y,0)){
		rompiendose = false;
		contador = -1;
	};
	~Huevo(void){};

	virtual int getTipoFigura(){return HUEVO;}
	virtual int getTipoDimension(){return CIRCULO;}
	
	Figura* clonar(){
		Figura* huevo = new Huevo(ID.c_str(),dimension->clonar(),true);
		this->completarInteraccionesPosibles(huevo);
		return huevo;
	}

	void romper(){
		rompiendose = true;
		contador++;
	}

	bool estaRompiendo(){
		return contador==0;
	}

	void actualizar(){
		if(rompiendose){
			contador++;
			
			if(contador == 1){
				Sonidos::playSound(HUEVO_SOUND);		
				this->ID = ID_HUEVO_ROMPIENDO1; 
				delete (this->myVista);
				this->myVista = new VistaFigura(this);
			}
			if(contador == (FPS/FACTOR)){
				this->ID = ID_HUEVO_ROMPIENDO2; 
				delete (this->myVista);
				this->myVista = new VistaFigura(this);			
			}
			if(contador == (2*FPS/FACTOR)){
				this->ID = ID_HUEVO_ROMPIENDO3; 
				delete (this->myVista);
				this->myVista = new VistaFigura(this);			
			}
			if(contador == (3*FPS/FACTOR)){
				this->ID = ID_HUEVO_ROMPIENDO4; 
				delete (this->myVista);
				this->myVista = new VistaFigura(this);			
			}
			if(contador == (4*FPS/FACTOR)){
				this->ID = ID_HUEVO_ROMPIENDO5; 
				delete (this->myVista);
				this->myVista = new VistaFigura(this);			
			}
			if(contador == (5*FPS/FACTOR)){
				this->ID = ID_HUEVO_ROMPIENDO6; 
				delete (this->myVista);
				this->myVista = new VistaFigura(this);			
			}
			if(contador == (6*FPS/FACTOR)){
				this->marcar(true);
				this->cumplirObjetivo();
			}
		}
	}

	void interactuar(){
		this->romper();
	}
};