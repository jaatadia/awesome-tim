#include "CintaTransportadora.h"
#include "VistaFigAgrandable.h"	

CintaTransportadora::CintaTransportadora(double largo,double posX,double posY,double angulo):FiguraCompuesta(ID_CINTA_TRANSPORTADORA,new Cuadrado(ANCHO_CINTA_TRANSP*largo,ALTO_CINTA_TRANSP,posX,posY,0)){
	this->largo = largo;
	
	this->atadoDerecha = false;
	this->atadoIzquierda = false;

	//this->myVista = new VistaFigAgrandable(this);
	this->cinta = new Figura(ID_CINTA,new Cuadrado(ANCHO_CINTA_TRANSP*largo,ALTO_CINTA_TRANSP,posX,posY,0));
	(this->cinta)->myVista = new VistaFigAgrandable(this->cinta);
	this->circizq = new Figura(ID_CTRANSP_CIRC,new Circulo(RADIO_CTRANSP_CIRC,posX-ANCHO_CINTA/2+RADIO_CTRANSP_CIRC,posY,0));
	this->circder = new Figura(ID_CTRANSP_CIRC,new Circulo(RADIO_CTRANSP_CIRC,posX+ANCHO_CINTA/2-RADIO_CTRANSP_CIRC,posY,0));
	this->clavo = new Figura(ID_CTRANSP_CLAVO,new Circulo(RADIO_CTRANSP_CLAVO,posX,posY-ALTO_CINTA_TRANSP/2-RADIO_CTRANSP_CLAVO,0));

	this->partesFigura.push_back(this->cinta);
	this->partesFigura.push_back(this->circizq);
	this->partesFigura.push_back(this->circder);
	
	//puede q falte lo de inic angulos
}

CintaTransportadora::~CintaTransportadora(void){
}

void CintaTransportadora::agrandar(){
	if (this->largo < CINTA_TRANSP_MAXLARGO){
		this->largo++;
		this->getDimension()->setAncho(ANCHO_CINTA_TRANSP*largo);
		this->cinta->getDimension()->setAncho(ANCHO_CINTA_TRANSP*largo);
		setCambio(true);
	}
}
void CintaTransportadora::achicar(){
	if (this->largo > CINTA_TRANSP_MINLARGO){
		this->largo--;
		this->getDimension()->setAncho(ANCHO_CINTA_TRANSP*largo);
		this->cinta->getDimension()->setAncho(ANCHO_CINTA_TRANSP*largo);
		setCambio(true);
	}
}
double CintaTransportadora::getLargo(){
	return this->largo;
}
Figura* CintaTransportadora::clonar(){
	return new CintaTransportadora(this->largo,this->dimension->getX(),this->dimension->getY(),this->dimension->getAngulo());
}
void CintaTransportadora::calcularPosClavo(double angulo,double* posX_clavo,double* posY_clavo){
	
	Dimension* dim = this->getDimension();
	double alto_plat = dim->getAlto();
	double ancho_plat = dim->getAncho();
	double alto = dim->getAlto()/2;

	while (angulo < 0) angulo+=360;
	while (angulo >= 360) angulo-=360;
	angulo *= PI/180;
	
	if ( angulo >= 0 && angulo <= atan2(alto_plat,ancho_plat) ){

		*posY_clavo = dim->getY() + tan(angulo)/(ancho_plat/2);
		*posX_clavo = dim->getX() + (ancho_plat/2);

	}else if (angulo <= atan2(alto_plat,-ancho_plat)){

		*posY_clavo = dim->getY() + tan(angulo)/(ancho_plat/2);
		*posX_clavo = dim->getX() + (ancho_plat/2);

	}else if (angulo <= atan2(-alto_plat,-ancho_plat)){

		*posY_clavo = dim->getY() - tan(angulo)/(ancho_plat/2);
		*posX_clavo = dim->getX() - (ancho_plat/2);

	}else {

		*posY_clavo = dim->getY() + tan(angulo)/(ancho_plat/2);
		*posX_clavo = dim->getX() + (ancho_plat/2);
	}
	
}
void CintaTransportadora::setAngulo(double angulo){

		double margen = 2;
		double posX_clavo,posY_clavo;
	if(
		(this->circizq->getDimension()->getAngulo() < (angulo-margen))||
		(this->circizq->getDimension()->getAngulo() >(angulo+margen))
	){
		this->circizq->setAngulo(angulo);
		this->circder->setAngulo(angulo);
		calcularPosClavo(angulo,&posX_clavo,&posY_clavo);
		this->clavo->setX(posX_clavo);
		this->clavo->setY(posY_clavo);
		setCambio(true);
	}
}
int CintaTransportadora::getTipoFigura(){
	return CINTATRANSPORTADORA;
}
int CintaTransportadora::getTipoDimension(){
	return CUADRADO;
	}
