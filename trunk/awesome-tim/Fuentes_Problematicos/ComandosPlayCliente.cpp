#include "ComandosPlayCliente.h"

ComandosPlayCliente::ComandosPlayCliente(int ancho,int alto){
	anchoOrig = this->ancho = ancho;
	altoOrig = this->alto = alto;
	
	this->sup = NULL;
	/*this->sup = new Superficie(ancho,alto);
	this->sup->restoreAlpha();*/
	
	int anchoTemp,altoTemp;

	anchoTemp = ancho;
	altoTemp = alto;

	SEPX = ancho/100;
	SEPY = alto/10;

	ANCHO_B_STOP = anchoTemp/8;
	ALTO_B_STOP = altoTemp -2*SEPY;
	X_B_STOP = anchoTemp - (ANCHO_B_STOP*3+3*SEPX);
	Y_B_STOP = SEPY;

	BotonStopOrigApretado = new Imagen("../images/botonStopApretado.png");
	BotonStopOrigSinApretar = new Imagen("../images/botonStopSinApretar.png");
	BotonStopApretado = BotonStopOrigApretado->scaleImagen(ANCHO_B_STOP,ALTO_B_STOP);
	BotonStopSinApretar = BotonStopOrigSinApretar->scaleImagen(ANCHO_B_STOP,ALTO_B_STOP);

	botonStopActivo = false;
	
	this->setCambio(true);

	resizear();
}

ComandosPlayCliente::~ComandosPlayCliente(void)
{
	delete BotonStopOrigApretado;
	delete BotonStopOrigSinApretar;
	delete BotonStopApretado;
	delete BotonStopSinApretar;

	delete this->sup;
}

Superficie* ComandosPlayCliente::getImpresion(){
	/*if(this->huboCambios()) 
		redraw();
	this->setCambio(false);
	return this->sup;*/
	return NULL;
}

void ComandosPlayCliente::redraw(){
	/*sup->restoreGris();
	if(botonStopActivo){
		sup->dibujarImagen(BotonStopApretado,NULL,X_B_STOP,Y_B_STOP);
	}
	else{
		sup->dibujarImagen(BotonStopSinApretar,NULL,X_B_STOP,Y_B_STOP);
	}*/
}

void ComandosPlayCliente::click(double x, double y,JuegoPlayCliente* juego){
	if(in(X_B_STOP,Y_B_STOP,ANCHO_B_STOP,ALTO_B_STOP,x,y)){
		botonStopActivo = true;
		setCambio(true);
	}
}


bool ComandosPlayCliente::in(int x, int y, int ancho, int alto, double x2, double y2){
	if((x2>=x)&&(x2<=x+ancho)&&(y2>=y)&&(y2<= y+alto))return true;
	else return false;
}

void ComandosPlayCliente::resizear(){

	//si cambiaron las escalas...consigo una nueva superficie del tamanio correcto
	ancho = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(anchoOrig/5);
	alto =  EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(altoOrig/5);

	/*delete sup;
	sup = new Superficie(ancho,alto);*/
		
	int anchoTemp = ancho;
	int altoTemp = alto;

	SEPX = ancho/100;
	SEPY = alto/10;

	ANCHO_B_STOP = anchoTemp/8;
	ALTO_B_STOP = altoTemp -2*SEPY;
	X_B_STOP = anchoTemp - (ANCHO_B_STOP*3+3*SEPX);
	Y_B_STOP = SEPY;

	delete BotonStopApretado;
	delete BotonStopSinApretar;
	BotonStopApretado = BotonStopOrigApretado->scaleImagen(ANCHO_B_STOP,ALTO_B_STOP);
	BotonStopSinApretar = BotonStopOrigSinApretar->scaleImagen(ANCHO_B_STOP,ALTO_B_STOP);
	
	this->setCambio(true);
}


void ComandosPlayCliente::release(double x, double y,bool* flag,JuegoPlayCliente* juego){
	if(in(X_B_STOP,Y_B_STOP,ANCHO_B_STOP,ALTO_B_STOP,x,y)&&botonStopActivo){
		juego->quit();
		*flag = true;
	}

	botonStopActivo = false;
	setCambio(true);

}

void ComandosPlayCliente::dibujate(Superficie* sup,int xIni,int yIni){
	if(botonStopActivo){
		sup->dibujarImagen(BotonStopApretado,NULL,xIni+X_B_STOP,yIni+Y_B_STOP);
	}
	else{
		sup->dibujarImagen(BotonStopSinApretar,NULL,xIni+X_B_STOP,yIni+Y_B_STOP);
	}
}
