#include "Balancin.h"
#include "Constantes.h"
#include "Cuadrado.h"

#define TABLA 0
#define DERECHA 1
#define IZQUIERDA 2

//#define PUNTA_NO_GIRADA 0

//Balancin::Balancin(double posX, double posY, double angulo,std::list<Figura*> listaFiguras):FiguraCompuesta(listaFiguras,angulo){
//	
//	//FIXME: Esta horrible esto hecho
//	int i = 0;
//	std::list<Figura*>::iterator iter;
//	for (iter = listaFiguras.begin(); iter != listaFiguras.end(); iter++){
//		switch(i){
//			case 0: this->tabla = *iter;
//					break;
//			case 1: this->circDer = *iter;
//					break;
//			case 2: this->circIzq = *iter;
//					break;
//		}
//	}
//
//	this->atadoDerecha = false;
//	this->atadoIzquierda = false;
//}

Balancin::Balancin(const char* id,double posX, double posY, double angulo):FiguraCompuesta(id,new Cuadrado(ANCHO_BALANCIN,ALTO_BALANCIN+2*RADIO_PUNTA_BALANCIN,posX,posY,0)){
	
	this->partesFigura = std::list<Figura*>();
	double posXPuntaIzq,posXPuntaDer,posYPunta;

	calcularPosPuntas(&posXPuntaIzq,&posXPuntaDer,&posYPunta,posX,posY);

	this->tabla = new Figura(ID_TABLA_BALANCIN,new Cuadrado(ANCHO_BALANCIN,ALTO_BALANCIN,posX,posY,0));
	this->circIzq = new Figura(ID_PUNTA_BALANCIN,new Circulo(RADIO_PUNTA_BALANCIN,posXPuntaIzq,posYPunta,0));
	this->circDer = new Figura(ID_PUNTA_BALANCIN,new Circulo(RADIO_PUNTA_BALANCIN,posXPuntaDer,posYPunta,0));

	this->partesFigura.push_back(this->tabla); //tabla
	this->partesFigura.push_back(this->circIzq); //punta izq
	this->partesFigura.push_back(this->circDer); //punta der

	this->atadoDerecha = false;
	this->atadoIzquierda = false;

	this->inicAngulosCentro();

	for (iterFig = partesFigura.begin(); iterFig != partesFigura.end(); iterFig++){
		//y obviamente aca poner en quien herede los que correspondan
		angulos.push_back((*iterFig)->getDimension()->getAngulo());
	}
	this->setAngulo(angulo);
}

Balancin::~Balancin(void){
	//std::list<Figura*>::iterator iter = this->partesFigura.begin();
	//
	//for(iter; iter != this->partesFigura.end();iter++){
	//	delete (*iter);
	//}
}
void Balancin::calcularPosPuntas(double* posXizq,double* posXder, double* posY, double posX_Tabla, double posY_Tabla){

	*posXizq = ( posX_Tabla - (ANCHO_BALANCIN / 2) + RADIO_PUNTA_BALANCIN);
	*posXder = ( posX_Tabla + (ANCHO_BALANCIN / 2) - RADIO_PUNTA_BALANCIN);
	*posY = ( posY_Tabla - (ALTO_BALANCIN / 2) - RADIO_PUNTA_BALANCIN);
}

/*bool Balancin::atar(double posX, double posY){
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
}*/

Figura* Balancin::clonar(){

	Cuadrado* dim = (Cuadrado*) this->getDimension();

	return new Balancin("",dim->getX(),dim->getY(),dim->getAngulo());
}//copia la figura


int Balancin::getTipoDimension(){
	return CUADRADO;
}

int Balancin::getTipoFigura(){
	return BALANCIN;
}

Figura* Balancin::getTabla(){
	return this->tabla;
}

Figura* Balancin::getPuntaIzq(){
	return this->circIzq;
}

Figura* Balancin::getPuntaDer(){
	return this->circDer;
}

int Balancin::esAtableSoga(double x,double y){
	if ((!this->atadoIzquierda) && x < this->getDimension()->getX()) return 1;
	else if ((!this->atadoDerecha) && x > this->getDimension()->getX()) return 2;
	return -1;
}

void Balancin::posAtableSoga(int numero,double* x,double* y){
	if (numero == 1){
		*x = this->circIzq->getDimension()->getX();
		*y = this->circIzq->getDimension()->getY();
	}else if (numero == 2){
		*x = this->circDer->getDimension()->getX();
		*y = this->circDer->getDimension()->getY();
	}
}
void Balancin::atarSoga(int numero){
}
void Balancin::desatarSoga(int numero){
}