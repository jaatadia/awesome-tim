#include "Comandos.h"

Comandos::Comandos(int ancho,int alto){
	anchoOrig = this->ancho = ancho;
	altoOrig = this->alto = alto;
	sup = new Superficie(ancho,alto);

	this->posDirActual = 0;
	dir[0] = '\0';
	
	int anchoTemp,altoTemp;

	anchoTemp = ancho;
	altoTemp = alto;

	SEPX = ancho/100;
	SEPY = alto/10;

	ANCHO_TBOX = anchoTemp/3;
	ALTO_TBOX = altoTemp -2*SEPY;
	X_TBOX = SEPX;
	Y_TBOX = SEPY;
	
	ANCHO_B_OK = anchoTemp/8;
	ALTO_B_OK = ALTO_TBOX;
	X_B_OK = X_TBOX + ANCHO_TBOX + SEPX;
	Y_B_OK = Y_TBOX;



	ANCHO_B_SAVE = ANCHO_B_OK;
	ALTO_B_SAVE = ALTO_TBOX;
	X_B_SAVE = anchoTemp - (ANCHO_B_SAVE*2+2*SEPX);
	Y_B_SAVE = Y_TBOX;

	ANCHO_B_PLAY = ANCHO_B_OK;
	ALTO_B_PLAY = ALTO_TBOX;
	X_B_PLAY = anchoTemp - (ANCHO_B_SAVE*3+3*SEPX);
	Y_B_PLAY = Y_TBOX;

	ANCHO_B_QUIT = ANCHO_B_OK;
	ALTO_B_QUIT = ALTO_TBOX;
	X_B_QUIT = X_B_SAVE + ANCHO_B_SAVE + SEPX;
	Y_B_QUIT = Y_TBOX;

	BotonOKOrigApretado = new Imagen("../images/botonOkApretado.png");
	BotonOKOrigSinApretar = new Imagen("../images/botonOkSinApretar.png");
	BotonOKApretado = BotonOKOrigApretado->scaleImagen(ANCHO_B_OK,ALTO_B_OK);
	BotonOKSinApretar = BotonOKOrigSinApretar->scaleImagen(ANCHO_B_OK,ALTO_B_OK);

	BotonSaveOrigApretado = new Imagen("../images/botonSaveApretado.png");
	BotonSaveOrigSinApretar = new Imagen("../images/botonSaveSinApretar.png");
	BotonSaveApretado = BotonSaveOrigApretado->scaleImagen(ANCHO_B_SAVE,ALTO_B_SAVE);
	BotonSaveSinApretar = BotonSaveOrigSinApretar->scaleImagen(ANCHO_B_OK,ALTO_B_OK);
	
	BotonQuitOrigApretado = new Imagen("../images/botonQuitApretado.png");
	BotonQuitOrigSinApretar = new Imagen("../images/botonQuitSinApretar.png");
	BotonQuitApretado = BotonQuitOrigApretado->scaleImagen(ANCHO_B_QUIT,ALTO_B_QUIT);
	BotonQuitSinApretar = BotonQuitOrigSinApretar->scaleImagen(ANCHO_B_OK,ALTO_B_OK);
	
	BotonPlayOrigApretado = new Imagen("../images/botonPlayApretado.png");
	BotonPlayOrigSinApretar = new Imagen("../images/botonPlaySinApretar.png");
	BotonPlayApretado = BotonPlayOrigApretado->scaleImagen(ANCHO_B_QUIT,ALTO_B_QUIT);
	BotonPlaySinApretar = BotonPlayOrigSinApretar->scaleImagen(ANCHO_B_OK,ALTO_B_OK);

	botonPlayActivo = botonOkActivo = botonQuitActivo = botonSaveActivo = false;
	
	this->setCambio(true);
}

Comandos::~Comandos(void){
	delete sup;
	
	delete BotonOKApretado;
	delete BotonQuitApretado;
	delete BotonSaveApretado;
	delete BotonPlayApretado;

	delete BotonOKOrigApretado;
	delete BotonQuitOrigApretado;
	delete BotonSaveOrigApretado;
	delete BotonPlayOrigApretado;

	delete BotonOKSinApretar;
	delete BotonQuitSinApretar;
	delete BotonSaveSinApretar;
	delete BotonPlaySinApretar;

	delete BotonOKOrigSinApretar;
	delete BotonQuitOrigSinApretar;
	delete BotonSaveOrigSinApretar;
	delete BotonPlayOrigSinApretar;
}

Superficie* Comandos::getImpresion(){
	if(this->huboCambios()) 
		redraw();
	this->setCambio(false);
	return sup;
}

void Comandos::redraw(){

	sup->restoreGris();
	sup->dibujarCuadradoNegro(X_TBOX,Y_TBOX,ANCHO_TBOX,ALTO_TBOX);

	if(botonOkActivo){
		sup->dibujarImagen(BotonOKApretado,NULL,X_B_OK,Y_B_OK);
	}
	else{
		sup->dibujarImagen(BotonOKSinApretar,NULL,X_B_OK,Y_B_OK);
	}

	if(botonSaveActivo){
		sup->dibujarImagen(BotonSaveApretado,NULL,X_B_SAVE,Y_B_SAVE);
	}
	else{
		sup->dibujarImagen(BotonSaveSinApretar,NULL,X_B_SAVE,Y_B_SAVE);
	}

	if(botonQuitActivo){
		sup->dibujarImagen(BotonQuitApretado,NULL,X_B_QUIT,Y_B_QUIT);
	}
	else{
		sup->dibujarImagen(BotonQuitSinApretar,NULL,X_B_QUIT,Y_B_QUIT);
	}

	if(botonPlayActivo){
		sup->dibujarImagen(BotonPlayApretado,NULL,X_B_PLAY,Y_B_PLAY);
	}
	else{
		sup->dibujarImagen(BotonPlaySinApretar,NULL,X_B_PLAY,Y_B_PLAY);
	}

	if(posDirActual != 0){
		Imagen* img = new Imagen(dir,ALTO_TBOX*2/3,255,255,255);
		if(img->getAncho() <= ANCHO_TBOX)
			sup->dibujarImagen(img,NULL,X_TBOX,Y_TBOX+(ALTO_TBOX - img->getAlto())/2);
		else{
			Rectangulo rect = Rectangulo(img->getAncho()- ANCHO_TBOX,0,ANCHO_TBOX,ALTO_TBOX);
			sup->dibujarImagen(img,&rect,X_TBOX,Y_TBOX+(ALTO_TBOX - img->getAlto())/2);
		}
		delete img;
	}

}

void Comandos::borrarLetra(){
	if(posDirActual != 0){
		this->setCambio(true);	
		posDirActual--;
		dir[posDirActual] = '\0';
	}
}

void Comandos::agregarLetra(char caracter){
	if(posDirActual != 255){
		this->setCambio(true);
		dir[posDirActual] = caracter;
		posDirActual++;
		dir[posDirActual] = '\0';
	}
}

void Comandos::click(double x, double y,Juego* juego){
	if(in(X_B_OK,Y_B_OK,ANCHO_B_OK,ALTO_B_OK,x,y)){
		botonOkActivo = true;
		setCambio(true);
	}else if(in(X_B_SAVE,Y_B_SAVE,ANCHO_B_SAVE,ALTO_B_SAVE,x,y)){
		botonSaveActivo = true;
		setCambio(true);
	}else if(in(X_B_PLAY,Y_B_PLAY,ANCHO_B_PLAY,ALTO_B_PLAY,x,y)){
		botonPlayActivo = true;
		setCambio(true);
	}else {
		if(in(X_B_QUIT,Y_B_QUIT,ANCHO_B_QUIT,ALTO_B_QUIT,x,y)){
			botonQuitActivo = true;
			setCambio(true);
		}
	}
}

bool Comandos::in(int x, int y, int ancho, int alto, double x2, double y2){
	if((x2>=x)&&(x2<=x+ancho)&&(y2>=y)&&(y2<= y+alto))return true;
	else return false;
}

void Comandos::resizear(){

	this->setCambio(true);
	
	//si cambiaron las escalas...consigo una nueva superficie del tamanio correcto
	ancho = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(anchoOrig/5);
	alto =  EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(altoOrig/5);

	delete sup;
	sup = new Superficie(ancho,alto);

	int anchoTemp = ancho;
	int altoTemp = alto;

	SEPX = ancho/100;
	SEPY = alto/10;

	ANCHO_TBOX = anchoTemp/3;
	ALTO_TBOX = altoTemp -2*SEPY;
	X_TBOX = SEPX;
	Y_TBOX = SEPY;
	
	ANCHO_B_OK = anchoTemp/8;
	ALTO_B_OK = ALTO_TBOX;
	X_B_OK = X_TBOX + ANCHO_TBOX + SEPX;
	Y_B_OK = Y_TBOX;

	ANCHO_B_SAVE = ANCHO_B_OK;
	ALTO_B_SAVE = ALTO_TBOX;
	X_B_SAVE = anchoTemp - (ANCHO_B_SAVE*2+2*SEPX);
	Y_B_SAVE = Y_TBOX;

	ANCHO_B_PLAY = ANCHO_B_OK;
	ALTO_B_PLAY = ALTO_TBOX;
	X_B_PLAY = anchoTemp - (ANCHO_B_SAVE*3+3*SEPX);
	Y_B_PLAY = Y_TBOX;

	ANCHO_B_QUIT = ANCHO_B_OK;
	ALTO_B_QUIT = ALTO_TBOX;
	X_B_QUIT = X_B_SAVE + ANCHO_B_SAVE + SEPX;
	Y_B_QUIT = Y_TBOX;

	delete BotonOKApretado;
	delete BotonOKSinApretar;
	BotonOKApretado = BotonOKOrigApretado->scaleImagen(ANCHO_B_OK,ALTO_B_OK);
	BotonOKSinApretar = BotonOKOrigSinApretar->scaleImagen(ANCHO_B_OK,ALTO_B_OK);

	delete BotonSaveApretado;
	delete BotonSaveSinApretar;
	BotonSaveApretado = BotonSaveOrigApretado->scaleImagen(ANCHO_B_SAVE,ALTO_B_SAVE);
	BotonSaveSinApretar = BotonSaveOrigSinApretar->scaleImagen(ANCHO_B_SAVE,ALTO_B_SAVE);

	delete BotonQuitApretado;
	delete BotonQuitSinApretar;
	BotonQuitApretado = BotonQuitOrigApretado->scaleImagen(ANCHO_B_QUIT,ALTO_B_QUIT);
	BotonQuitSinApretar = BotonQuitOrigSinApretar->scaleImagen(ANCHO_B_QUIT,ALTO_B_QUIT);
	
	delete BotonPlayApretado;
	delete BotonPlaySinApretar;
	BotonPlayApretado = BotonPlayOrigApretado->scaleImagen(ANCHO_B_QUIT,ALTO_B_QUIT);
	BotonPlaySinApretar = BotonPlayOrigSinApretar->scaleImagen(ANCHO_B_QUIT,ALTO_B_QUIT);

	this->setCambio(true);
}

void Comandos::enterKeyPressed(Juego* juego){
	if(this->posDirActual!=0) juego->setFondo(dir);
}

void Comandos::release(double x, double y,Juego* juego){
	if(in(X_B_OK,Y_B_OK,ANCHO_B_OK,ALTO_B_OK,x,y)&&botonOkActivo){
		juego->setFondo(dir);
	}else if(in(X_B_SAVE,Y_B_SAVE,ANCHO_B_SAVE,ALTO_B_SAVE,x,y)&&botonSaveActivo){
		juego->guardar();
	}else if(in(X_B_PLAY,Y_B_PLAY,ANCHO_B_PLAY,ALTO_B_PLAY,x,y)&&botonPlayActivo){
		juego->play();
	} else {
		if(in(X_B_QUIT,Y_B_QUIT,ANCHO_B_QUIT,ALTO_B_QUIT,x,y)&&botonQuitActivo){
			juego->quit();
		}
	}
	botonPlayActivo = botonOkActivo = botonSaveActivo = botonQuitActivo = false;
	setCambio(true);

}