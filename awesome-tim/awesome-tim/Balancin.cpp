#include "Balancin.h"
#include "Constantes.h"
#include "Cuadrado.h"

#define TABLA 0
#define DERECHA 1
#define IZQUIERDA 2

#define PUNTA_NO_GIRADA 0

Balancin::Balancin(double posX, double posY, double angulo,std::list<Figura*> listaFiguras):FiguraCompuesta(listaFiguras,angulo){
	
	//FIXME: Esta horrible esto hecho
	int i = 0;
	std::list<Figura*>::iterator iter;
	for (iter = listaFiguras.begin(); iter != listaFiguras.end(); iter++){
		switch(i){
			case 0: this->tabla = *iter;
					break;
			case 1: this->circDer = *iter;
					break;
			case 2: this->circIzq = *iter;
					break;
		}
	}
	/////////////////////

	this->atadoDerecha = false;
	this->atadoIzquierda = false;
}

void Balancin::calcularPosPuntas(double* posXizq,double* posXder, double* posY, double posX_Tabla, double posY_Tabla){

	*posXizq = ( posX_Tabla - (ANCHO_BALANCIN / 2) + RADIO_PUNTA_BALANCIN);
	*posXder = ( posX_Tabla + (ANCHO_BALANCIN / 2) - RADIO_PUNTA_BALANCIN);
	*posY = ( posY_Tabla + (ALTO_BALANCIN / 2) + RADIO_PUNTA_BALANCIN);
}

bool Balancin::atar(double posX, double posY){
	bool der = this->circDer->esMiPosicion(posX,posY);
	if(der && (!this->atadoDerecha)){
		this->atadoDerecha = true;
		return true;
	}

	bool izq = this->circIzq->esMiPosicion(posX,posY);
	if(izq && (!this->atadoIzquierda)){
		this->atadoIzquierda = true;
		return true;
	}

	return false;
}

bool Balancin::desatar(double posX, double posY){
	bool der = this->circDer->esMiPosicion(posX,posY);
	if(der && this->atadoDerecha){
		this->atadoDerecha = false;
		return true;
	}

	bool izq = this->circIzq->esMiPosicion(posX,posY);
	if(izq && this->atadoIzquierda){
		this->atadoIzquierda = false;
		return true;
	}

	return false;
}

bool Balancin::esAtable(double* posX, double* posY){
	bool izq = this->circIzq->esMiPosicion(*posX,*posY);
	if(izq){
		*posX = (this->circIzq->getDimension())->getX();
		*posY = (this->circIzq->getDimension())->getY();
		return true;
	}
	bool der = this->circDer->esMiPosicion(*posX,*posY);
	if(der){
		*posX = (this->circDer->getDimension())->getX();
		*posY = (this->circDer->getDimension())->getY();
		return true;
	}
	return false;
}

//void Balancin::setAngulo(double angulo){
//FIXME: se redefine? xq hay que mover los circulos cuando se gira la tabla	
//}

Figura* Balancin::clonar(){
		return NULL;
}//copia la figura


int Balancin::getTipoDimension(){
	return 0;
}

int Balancin::getTipoFigura(){
	return 0;
}
