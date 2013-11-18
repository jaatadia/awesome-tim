#pragma once

#include "Figura.h"
#include "Rectangulo.h"

class Tijera: public Figura
{
public:
	int pos;
private:
	bool atado1,atado2,cerrada;
	int contador;
	Tijera(const char* ID, Dimension* dim,bool flag):Figura(ID,dim){
		cerrada=atado1=atado2=false;
		contador = 0;
		pos = 0;
	}

public:
	Tijera(double posX,double posY ,double angulo = 0):Figura(ID_TIJERA,new Cuadrado(ANCHO_TIJERA,ALTO_TIJERA,posX,posY,angulo)){
		cerrada=atado1=atado2=false;
		contador = 0;
		pos = 0;
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
		 Tijera* tij = new Tijera(ID.c_str(),dimension->clonar(),true);
		 tij->pos = pos;
		 this->completarInteraccionesPosibles(tij);
		 return tij;
	}

	virtual int esAtableSoga(double x,double y){
		if(atado1 && atado2){
			return -1;
		}else if(!atado1 && !atado2){
			if(pos==0){
				if(y<dimension->getY()){
					return 2;
				}else{
					return 1;
				}
			}else if(pos==1){
				if(x<dimension->getX()){
					return 2;
				}else{
					return 1;
				}
			}else if(pos==2){
				if(y<dimension->getY()){
					return 1;
				}else{
					return 2;
				}
			}else{
				if(x<dimension->getX()){
					return 1;
				}else{
					return 2;
				}
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
		
		double cx = dimension->getX();
		double cy = dimension->getY();
		
		if(pos == 0){
			*x = cx - dimension->getAncho()*3/8;
			*y = cy + desfasaje;
		}else if(pos == 1){
			*x = cx + desfasaje;
			*y = cy + dimension->getAncho()*3/8;
		}else if(pos == 2){
			*x = cx + dimension->getAncho()*3/8;
			*y = cy - desfasaje;
		}else{
			*x = cx - desfasaje;;
			*y = cy - dimension->getAncho()*3/8;
		}

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
	
	virtual void getCuadradoCortante(double* x1,double* y1,double* x2,double* y2){
		double cx = dimension->getX();
		double cy = dimension->getY();
		double ancho = dimension->getAncho();
		double alto = dimension->getAlto();
		
		if(pos == 0){
			*x1 = cx;
			*y1 = cy - alto/2;
			*x2 = cx + ancho/2;
			*y2 = cy + alto/2;
		}else if(pos == 3){
			*x1 = cx - alto/2;
			*y1 = cy;
			*x2 = cx + alto/2;
			*y2 = cy + ancho/2;
		}else if(pos == 2){
			*x1 = cx - ancho/2;
			*y1 = cy - alto/2;
			*x2 = cx;
			*y2 = cy + alto/2;
		}else{
			*x1 = cx - alto/2;
			*y1 = cy - ancho/2;
			*x2 = cx + alto/2;
			*y2 = cy;
		}

	}

	virtual bool pinchaGlobo(Dimension* dim){

		double cx = dimension->getX();
		double cy = dimension->getY();
		double ancho = dimension->getAncho();
		double alto = dimension->getAlto();
		
		if(pos == 0){

		}else if(pos == 3){

		}else if(pos == 2){

		}else{

		}
		return false;
	}

	

	virtual void actualizar(){
		if (cerrada){
			contador++;
		}
	}

	virtual void shift(){
		dimension->setAngulo(dimension->getAngulo() + 90);
		pos = (pos + 1)%4;
		this->setCambio(true);
	}

	virtual void setAngulo(double angulo){
		this->setCambio(true);
		if(angulo<90){
			dimension->setAngulo(0);
			pos = 0;
		}else if(angulo<180){
			dimension->setAngulo(90);
			pos = 1;
		}else if(angulo<270){
			dimension->setAngulo(180);
			pos = 2;
		}else{
			dimension->setAngulo(270);
			pos = 3;
		}
	}

};
