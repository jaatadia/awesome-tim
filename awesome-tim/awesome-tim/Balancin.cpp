#include "Balancin.h"
#include "Constantes.h"
#include "Cuadrado.h"

#define TABLA 0

/*#define PUNTA_NO_GIRADA 0

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
*/

Balancin::Balancin(const char* id,double posX, double posY, double angulo):FiguraCompuesta(id,new Cuadrado(ANCHO_BALANCIN,ALTO_BALANCIN+2*RADIO_PUNTA_BALANCIN,posX,posY,0)){

	this->partesFigura = std::list<Figura*>();
	double posXPuntaIzq,posXPuntaDer,posYPuntaIzq,posYPuntaDer;

	calcularPosPuntas(posXPuntaIzq,posXPuntaDer,posYPuntaIzq,posYPuntaDer,posX,posY,angulo, 162.89727103 , 17.10272897);

	this->tabla = new Figura(ID_TABLA_BALANCIN,new Cuadrado(ANCHO_BALANCIN,ALTO_BALANCIN,posX,posY,0));
	this->circIzq = new Figura(ID_PUNTA_BALANCIN,new Circulo(RADIO_PUNTA_BALANCIN,posXPuntaIzq,posYPuntaIzq,0));
	this->circDer = new Figura(ID_PUNTA_BALANCIN,new Circulo(RADIO_PUNTA_BALANCIN,posXPuntaDer,posYPuntaDer,0));

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
void Balancin::calcularPosPuntas(double& posXizq,double& posXder, double& posYizq,double& posYder, double posX_Tabla, double posY_Tabla, double angulo, double angulo1, double angulo2){

	posXizq = ( posX_Tabla - (ANCHO_BALANCIN / 2) + RADIO_PUNTA_BALANCIN);
	posXder = ( posX_Tabla + (ANCHO_BALANCIN / 2) - RADIO_PUNTA_BALANCIN);
	posYizq = posYder = ( posY_Tabla - (ALTO_BALANCIN / 2) - (0.5)*RADIO_PUNTA_BALANCIN);

//	double centroX = posX_Tabla;
//	double centroY = posY_Tabla;
//
//	double angle ;
//	angle = (angulo + angulo1) *PI/180;
////roto el de la derecha
//	double XRelCentro = posXder - centroX;
//	double YRelCentro = posYder - centroY;
//
//	double radio = sqrt ( XRelCentro*XRelCentro + YRelCentro*YRelCentro );
//
//	double nuevoX = radio*cos(-angle) + centroX;
//	double nuevoY = radio*sin(-angle) + centroY;
//		
//	posXder = nuevoX ;
//	posYder = nuevoY;
//
////roto el de la izquierda
//	angle = (angulo + angulo2) *PI/180;
//
//	XRelCentro = posXizq - centroX;
//	YRelCentro = posYizq - centroY;
//
//	radio = sqrt ( XRelCentro*XRelCentro + YRelCentro*YRelCentro );
//
//	nuevoX = radio*cos(-angle) + centroX;
//	nuevoY = radio*sin(-angle) + centroY;
//		
//	posXizq = nuevoX ;
//	posYizq = nuevoY;

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
	if ((!this->atadoIzquierda) && x <= this->getDimension()->getX()) return 1;
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
	if (numero == 1){
		atadoIzquierda = true;
	}else if (numero == 2){
		atadoDerecha = true;
	}
}
void Balancin::desatarSoga(int numero){
	if (numero == 1){
		atadoIzquierda = false;
	}else if (numero == 2){
		atadoDerecha = false;
	}
}

//#define ANGULO_BALANCIN_IZQ 45
//#define ANGULO_BALANCIN_DER 315
void Balancin::shift(){

	if (dimension->getAngulo()==ANGULO_BALANCIN_IZQ)
		this->setAngulo(-45);
	else
		this->setAngulo(ANGULO_BALANCIN_IZQ);

}