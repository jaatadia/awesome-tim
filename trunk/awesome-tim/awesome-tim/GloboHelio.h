#pragma once
#include "Circulo.h"
#include "Constantes.h"
#include "Figura.h"
#include "Sonidos.h"

class GloboHelio : public Figura
{

private:
	GloboHelio(const char* id,Dimension* dim,int color):Figura(id,dim){
		pinchando = false;
		atado = false;
		contador = -1;
		miColor = color;
	};
	bool atado;
	static int color;
	int miColor;	
	int contador;
	bool pinchando;

public:
	GloboHelio(double pos_X,double pos_Y,int color):Figura("",new Circulo(RADIO_GLOBOHELIO,pos_X,pos_Y,0),false){
		
		if (color == CELESTE){
			this->ID = ID_COLOR_CELESTE;
			miColor = CELESTE;
		}else if (color == ROJO){
			this->ID = ID_COLOR_ROJO;
			miColor = ROJO;
		}else if (color == AMARILLO){
			this->ID = ID_COLOR_AMARILLO;
			miColor = AMARILLO;
		}else if (color == ROSA){
			this->ID = ID_COLOR_ROSA;
			miColor = ROSA;
		}else if (color == VERDE){
			this->ID = ID_COLOR_VERDE;
			miColor = VERDE;
		}else if (color == VIOLETA){
			this->ID = ID_COLOR_VIOLETA;
			miColor = VIOLETA;
		} else {
			this->ID = ID_COLOR_CELESTE;
			miColor = CELESTE;
		}
		this->myVista = new VistaFigura(this);
		pinchando = false;
		atado = false;
		contador = -1;
	};
	~GloboHelio(void){};

	virtual int getTipoFigura(){return GLOBOHELIO;}
	virtual int getTipoDimension(){return CIRCULO;}
	
	Figura* clonar(){
		return this->clonar(true);
	}

	Figura* clonar(bool cambiar){ //YA SE, ESTA FEO
		int elcolor = this->miColor;
		if (cambiar){
			color = (color+1) % CANT_COLORES;
			if (color == CELESTE){
				this->ID = ID_COLOR_CELESTE;
				elcolor = CELESTE;
			}
			else if (color == ROJO){
				this->ID = ID_COLOR_ROJO;
				elcolor = ROJO;
			}
			else if (color == AMARILLO){
				this->ID = ID_COLOR_AMARILLO;
				elcolor = AMARILLO;
			}
			else if (color == ROSA){
				this->ID = ID_COLOR_ROSA;
				elcolor = ROSA;
			}
			else if (color == VERDE){
				this->ID = ID_COLOR_VERDE;
				elcolor = VERDE;
			}
			else if (color == VIOLETA){
				this->ID = ID_COLOR_VIOLETA;
				elcolor = VIOLETA;
			}
		}
		Figura* globo = new GloboHelio(ID.c_str(),dimension->clonar(),elcolor);
		this->completarInteraccionesPosibles(globo);
		return globo;
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
		if(!pinchando){
			pinchando = true;
			contador ++;
			Sonidos::playSound(POP_BALLOON);
		}
	}

	bool estaPinchando(){
		//return pinchando;
		return contador == 0;
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
				this->cumplirObjetivo();
			}
		}
	}

	void interactuar(int accion){
		if (accion == CLICK_MOUSE)
			this->pinchar();
	}

	virtual bool rompeHuevo(Dimension* dim){
		return false;
	}
	virtual void getExtraData(double* d1,double* d2){
	*d1 = miColor;
	*d2 = -1;
	}
	int getColor(){
		return this->miColor;
	}
};