#pragma once

#include "Figura.h"
#include "Rectangulo.h"

class Tijera: public Figura
{
private:
	bool atado1,atado2,cerrada;
	int contador;
	Tijera(const char* ID, Dimension* dim,bool flag):Figura(ID,dim){
		cerrada=atado1=atado2=false;
		contador = 0;
	}

public:
	Tijera(double posX,double posY ,double angulo = 0):Figura(ID_TIJERA,new Cuadrado(ANCHO_TIJERA,ALTO_TIJERA,posX,posY,angulo)){
		cerrada=atado1=atado2=false;
		contador = 0;
	}
	~Tijera(void){
	}

	virtual int getTipoFigura(){
		return TIJERA;
	}

	virtual int getTipoDimension(){
		return CUADRADO;
	}

	virtual Figura* clonar(){
		return new Tijera(ID.c_str(),dimension->clonar(),true);
	}

	virtual int esAtableSoga(double x,double y){
		if(atado1 && atado2){
			return -1;
		}else if(!atado1 && !atado2){
			if(y<dimension->getY()){
				return 2;
			}else{
				return 1;
			}
		}else if(atado1){
			return 2; 
		}else{
			return 1;
		}
	}


	virtual void posAtableSoga(int numero,double* x,double* y){
		double desfasaje = dimension->getAlto()*3/8;
		desfasaje *= (numero == 1) ? 1:-1;
		*x = this->getDimension()->getX() - dimension->getAncho()*3/8;
		*y = this->getDimension()->getY() + desfasaje;
	}
	
	virtual void atarSoga(int numero){
		if(numero == 1){
			atado1 = true;
		}else{
			atado2 = true; 
		}
	};
	
	virtual void desatarSoga(int numero){
		if(numero == 1){
			atado1 = false;
		}else{
			atado2 = false; 
		}
	};

	virtual void cerrar(){
		if(!cerrada){
			delete this->myVista;
			ID = ID_TIJERA_CERRADA;
			this->myVista = new VistaFigura(this);
			cerrada = true;
		}
	}

	virtual bool cortaSoga(){
		return contador==1;
	}

	virtual void actualizar(){
		if (cerrada){
			contador++;
		}
	}
};
