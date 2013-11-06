#pragma once
#include "Circulo.h"
#include "Constantes.h"
#include "Figura.h"
#include "Sonidos.h"

class GloboHelio : public Figura
{

private:
	GloboHelio(const char* id,Dimension* dim,bool flag):Figura(id,dim){
		pinchando = false;
		atado = false;
		contador = 0;
	};
	bool atado;
	static int color;
	
	int contador;
	bool pinchando;

public:
	GloboHelio(double pos_X,double pos_Y):Figura(ID_GLOBO,new Circulo(RADIO_GLOBOHELIO,pos_X,pos_Y,0)){
		pinchando = false;
		atado = false;
		contador = 0;
	};
	~GloboHelio(void){};

	virtual int getTipoFigura(){return GLOBOHELIO;}
	virtual int getTipoDimension(){return CIRCULO;}
	
	Figura* clonar(){
		return this->clonar(true);
	}

	Figura* clonar(bool cambiar){ //YA SE, ESTA FEO
		if (cambiar){
			color = (color+1) % CANT_COLORES;
			if (color == 0) this->ID = COLOR_CELESTE;
			else if (color == 1) this->ID = COLOR_ROJO;
			else if (color == 2) this->ID = COLOR_AMARILLO;
			else if (color == 3) this->ID = COLOR_ROSA;
			else if (color == 4) this->ID = COLOR_VERDE;
			else if (color == 5) this->ID = COLOR_VIOLETA;
		}
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
	void pinchar(){
		pinchando = true;
		Sonidos::playSound(POP_BALLOON);
	}

	bool estaPinchando(){
		return pinchando;
	}

	void actualizar(){
		if(pinchando){
			contador++;

			if(contador == 1){
				this->ID = ID_GLOBO_EXPLOTANDO1; 
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

	virtual bool esObjetivo(){
		return true;
	}

	virtual bool cumplioObjetivo(){
		return this->estaMarcada();
	}

	virtual bool rompeHuevo(Dimension* dim){
		return false;
	}

};