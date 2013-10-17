#include "CintaTransportadora.h"
#include "VistaFigAgrandable.h"	

CintaTransportadora::CintaTransportadora(int largo,double posX,double posY,double angulo):FiguraCompuesta(ID_CINTA_TRANSPORTADORA,new Cuadrado(ANCHO_CINTA*largo,ALTO_CINTA,posX,posY,0)){
	this->largo = largo;
	
	this->atadoDerecha = false;
	this->atadoIzquierda = false;

	//this->myVista = new VistaFigAgrandable(this);
	this->cinta = new Figura(ID_CINTA,new Cuadrado(ANCHO_CINTA*largo,ALTO_CINTA,posX,posY,0));
	(this->cinta)->myVista = new VistaFigAgrandable(this->cinta);
	this->clavo = new Figura(ID_CTRANSP_CLAVO,new Circulo(RADIO_CTRANSP_CLAVO,posX+(ANCHO_CINTA*largo)/2-RADIO_CTRANSP_CIRC,posY-ALTO_CINTA/2+RADIO_CTRANSP_CLAVO,0));
	this->clavo2 = new Figura(ID_CTRANSP_CLAVO,new Circulo(RADIO_CTRANSP_CLAVO,posX-(ANCHO_CINTA*largo)/2+RADIO_CTRANSP_CIRC,posY+ALTO_CINTA/2-RADIO_CTRANSP_CLAVO,0));
	this->circizq = new Figura(ID_CTRANSP_CIRC,new Circulo(RADIO_CTRANSP_CIRC,posX-(ANCHO_CINTA*largo)/2+RADIO_CTRANSP_CIRC,posY,0));
	this->circder = new Figura(ID_CTRANSP_CIRC,new Circulo(RADIO_CTRANSP_CIRC,posX+(ANCHO_CINTA*largo)/2-RADIO_CTRANSP_CIRC,posY,0));

	this->partesFigura.push_back(this->cinta);
	this->partesFigura.push_back(this->clavo);
	this->partesFigura.push_back(this->clavo2);
	this->partesFigura.push_back(this->circizq);
	this->partesFigura.push_back(this->circder);
	
	this->cinta->setLargo(largo);
	
	//puede q falte lo de inic angulos
}

CintaTransportadora::~CintaTransportadora(void){
}

void CintaTransportadora::agrandar(){
	if (this->largo < CINTA_TRANSP_MAXLARGO){
		this->largo++;
		this->getDimension()->setAncho(ANCHO_CINTA*largo);

		double posX = this->getDimension()->getX();
		double posY = this->getDimension()->getY();

		this->cinta->getDimension()->setAncho(ANCHO_CINTA*largo);
		this->cinta->setLargo(largo);

		this->clavo->setX(posX+(ANCHO_CINTA*largo)/2-RADIO_CTRANSP_CIRC);
		this->clavo->setY(posY-ALTO_CINTA/2+RADIO_CTRANSP_CLAVO);

		this->clavo2->setX(posX-(ANCHO_CINTA*largo)/2+RADIO_CTRANSP_CIRC);
		this->clavo2->setY(posY+ALTO_CINTA/2-RADIO_CTRANSP_CLAVO);

		this->circizq->setX(posX-(ANCHO_CINTA*largo)/2+RADIO_CTRANSP_CIRC);
		this->circizq->setY(posY);

		this->circder->setX(posX+(ANCHO_CINTA*largo)/2-RADIO_CTRANSP_CIRC);
		this->circder->setY(posY);

		setCambio(true);
	}
}
void CintaTransportadora::achicar(){
	if (this->largo > CINTA_TRANSP_MINLARGO){
		this->largo--;
		this->getDimension()->setAncho(ANCHO_CINTA*largo);

		double posX = this->getDimension()->getX();
		double posY = this->getDimension()->getY();

		this->cinta->getDimension()->setAncho(ANCHO_CINTA*largo);
		this->cinta->setLargo(largo);

		this->clavo->setX(posX+(ANCHO_CINTA*largo)/2-RADIO_CTRANSP_CIRC);
		this->clavo->setY(posY-ALTO_CINTA/2+RADIO_CTRANSP_CLAVO);

		this->clavo2->setX(posX-(ANCHO_CINTA*largo)/2+RADIO_CTRANSP_CIRC);
		this->clavo2->setY(posY+ALTO_CINTA/2-RADIO_CTRANSP_CLAVO);

		this->circizq->setX(posX-(ANCHO_CINTA*largo)/2+RADIO_CTRANSP_CIRC);
		this->circizq->setY(posY);

		this->circder->setX(posX+(ANCHO_CINTA*largo)/2-RADIO_CTRANSP_CIRC);
		this->circder->setY(posY);

		setCambio(true);
	}
}
int CintaTransportadora::getLargo(){
	return this->largo;
}
Figura* CintaTransportadora::clonar(){
	return new CintaTransportadora(this->largo,this->dimension->getX(),this->dimension->getY(),this->dimension->getAngulo());
}
void CintaTransportadora::calcularPosClavo(double ang,double* posX_clavo,double* posY_clavo){
	
	Dimension* dim = this->getDimension();
	double alto_plat = dim->getAlto();
	double ancho_plat = dim->getAncho();
	double radio = ((Circulo*)this->clavo->getDimension())->getRadio();
	
	double angulo = ang;
	while (angulo < 0) angulo+=360;
	while (angulo >= 360) angulo-=360;

	double conversion = (ancho_plat+alto_plat)/180;//si en 360 grados tengo que andar 2alto y 2ancho
	double div1 = (180*ancho_plat/(ancho_plat+alto_plat));
	double div2 = 180;
	double div3 = (180*(2*ancho_plat+alto_plat)/(ancho_plat+alto_plat));
	double div4 = 360;

	if((angulo>=0)&&(angulo< div1)){
		*posX_clavo = dim->getX() + ancho_plat/2 - angulo*conversion;
		*posY_clavo = dim->getY() - alto_plat/2 + radio;
	}else if(angulo<=div2){
		*posX_clavo = dim->getX() - ancho_plat/2 + radio;
		*posY_clavo = dim->getY() - alto_plat/2 + (angulo-div1)*conversion;
	}else if(angulo<div3){
		*posX_clavo = dim->getX() - ancho_plat/2 + (angulo-div2)*conversion;
		*posY_clavo = dim->getY() + alto_plat/2 - radio;
	}else if(angulo<div4){
		*posX_clavo = dim->getX() + ancho_plat/2 - radio;
		*posY_clavo = dim->getY() + alto_plat/2 - (angulo-div3)*conversion;
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
		calcularPosClavo(angulo+180,&posX_clavo,&posY_clavo);
		this->clavo2->setX(posX_clavo);
		this->clavo2->setY(posY_clavo);
		setCambio(true);
	}
}
int CintaTransportadora::getTipoFigura(){
	return CINTATRANSPORTADORA;
}
int CintaTransportadora::getTipoDimension(){
	return CUADRADO;
	}

void CintaTransportadora::setLargo(int largoN){
	
	if (largoN <= CINTA_TRANSP_MAXLARGO && largoN >= CINTA_TRANSP_MINLARGO){
		largo = largoN;
		this->getDimension()->setAncho(ANCHO_CINTA*largo);
		
		//recalculo todas la sposiciones de las partes
		double posX = this->getDimension()->getX();
		double posY = this->getDimension()->getY();

		this->cinta->getDimension()->setAncho(ANCHO_CINTA*largo);
		this->cinta->setLargo(largo);

		this->clavo->setX(posX+(ANCHO_CINTA*largo)/2-RADIO_CTRANSP_CIRC);
		this->clavo->setY(posY-ALTO_CINTA/2+RADIO_CTRANSP_CLAVO);

		this->clavo2->setX(posX-(ANCHO_CINTA*largo)/2+RADIO_CTRANSP_CIRC);
		this->clavo2->setY(posY+ALTO_CINTA/2-RADIO_CTRANSP_CLAVO);

		this->circizq->setX(posX-(ANCHO_CINTA*largo)/2+RADIO_CTRANSP_CIRC);
		this->circizq->setY(posY);

		this->circder->setX(posX+(ANCHO_CINTA*largo)/2-RADIO_CTRANSP_CIRC);
		this->circder->setY(posY);

		setCambio(true);
	}

}
