#include "ComandosCliente.h"

ComandosCliente::ComandosCliente(int ancho,int alto,std::string id_imagen_texto_objetivo){
	anchoOrig = this->ancho = ancho;
	altoOrig = this->alto = alto;
	sup = new Superficie(ancho,alto);
	ready = false;

	this->posDirActual = 0;
	dir[0] = '\0';
	
	int anchoTemp,altoTemp;

	anchoTemp = ancho;
	altoTemp = alto;

	SEPX = ancho/100;
	SEPY = alto/10;

	//Objetivo:
	ANCHO_OBJ = anchoTemp*0.71;
	ALTO_OBJ = altoTemp -2*SEPY;
	X_OBJ = SEPX;
	Y_OBJ = SEPY;

	ANCHO_B_PLAY = anchoTemp/8;
	ALTO_B_PLAY = ALTO_OBJ;
	X_B_PLAY = anchoTemp - (ANCHO_B_PLAY*3 + 3*SEPX - 75);
	Y_B_PLAY = Y_OBJ;

	ANCHO_B_QUIT = ANCHO_B_PLAY;
	ALTO_B_QUIT = ALTO_OBJ;
	X_B_QUIT = X_B_PLAY + ANCHO_B_PLAY + SEPX;
	Y_B_QUIT = Y_OBJ;

	//Objetivo
	ImagenObjetivoOrig = NULL;
	ImagenObjetivo = NULL;


	BotonQuitOrigApretado = new Imagen("../images/botonQuitApretado.png");
	BotonQuitOrigSinApretar = new Imagen("../images/botonQuitSinApretar.png");
	BotonQuitApretado = BotonQuitOrigApretado->scaleImagen(ANCHO_B_QUIT,ALTO_B_QUIT);
	BotonQuitSinApretar = BotonQuitOrigSinApretar->scaleImagen(ANCHO_B_PLAY,ALTO_B_PLAY);
	
	BotonPlayOrigApretado = new Imagen("../images/botonReadyApretado.png");
	BotonPlayOrigSinApretar = new Imagen("../images/botonReadySinApretar.png");
	BotonPlayApretado = BotonPlayOrigApretado->scaleImagen(ANCHO_B_QUIT,ALTO_B_QUIT);
	BotonPlaySinApretar = BotonPlayOrigSinApretar->scaleImagen(ANCHO_B_PLAY,ALTO_B_PLAY);

	botonPlayActivo =  botonQuitActivo = false;
//	botonOkActivo = botonSaveActivo = false;

	this->setCambio(true);
}

ComandosCliente::~ComandosCliente(void){
	delete sup;
	
//	delete BotonOKApretado;
	delete BotonQuitApretado;
//	delete BotonSaveApretado;
	delete BotonPlayApretado;

//	delete BotonOKOrigApretado;
	delete BotonQuitOrigApretado;
//	delete BotonSaveOrigApretado;
	delete BotonPlayOrigApretado;

//	delete BotonOKSinApretar;
	delete BotonQuitSinApretar;
//	delete BotonSaveSinApretar;
	delete BotonPlaySinApretar;

//	delete BotonOKOrigSinApretar;
	delete BotonQuitOrigSinApretar;
//	delete BotonSaveOrigSinApretar;
	delete BotonPlayOrigSinApretar;

	delete ImagenObjetivo;
}

Superficie* ComandosCliente::getImpresion(){
	if(this->huboCambios()) 
		redraw();
	this->setCambio(false);
	return sup;
}

void ComandosCliente::redraw(){

	sup->restoreGris();
//	sup->dibujarCuadradoNegro(X_TBOX,Y_TBOX,ANCHO_TBOX,ALTO_TBOX);
	if (ImagenObjetivo != NULL){
		sup->dibujarImagen(ImagenObjetivo,NULL,X_OBJ,Y_OBJ);
	}

/*	if(botonOkActivo){
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
*/
	if(botonQuitActivo){
		sup->dibujarImagen(BotonQuitApretado,NULL,X_B_QUIT,Y_B_QUIT);
	}
	else{
		sup->dibujarImagen(BotonQuitSinApretar,NULL,X_B_QUIT,Y_B_QUIT);
	}

	if(ready || botonPlayActivo){
		sup->dibujarImagen(BotonPlayApretado,NULL,X_B_PLAY,Y_B_PLAY);
	}
	else{
		sup->dibujarImagen(BotonPlaySinApretar,NULL,X_B_PLAY,Y_B_PLAY);
	}
/*
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
*/
}

void ComandosCliente::borrarLetra(){
	if(posDirActual != 0){
		this->setCambio(true);	
		posDirActual--;
		dir[posDirActual] = '\0';
	}
}

void ComandosCliente::agregarLetra(char caracter){
	if(posDirActual != 255){
		this->setCambio(true);
		dir[posDirActual] = caracter;
		posDirActual++;
		dir[posDirActual] = '\0';
	}
}

void ComandosCliente::click(double x, double y,JuegoCliente* juego){
/*	if(in(X_B_OK,Y_B_OK,ANCHO_B_OK,ALTO_B_OK,x,y)){
		botonOkActivo = true;
		setCambio(true);
	}else if(in(X_B_SAVE,Y_B_SAVE,ANCHO_B_SAVE,ALTO_B_SAVE,x,y)){
		botonSaveActivo = true;
		setCambio(true);
	}else */if(in(X_B_PLAY,Y_B_PLAY,ANCHO_B_PLAY,ALTO_B_PLAY,x,y)){
		botonPlayActivo = true;
		setCambio(true);
	}else {
		if(in(X_B_QUIT,Y_B_QUIT,ANCHO_B_QUIT,ALTO_B_QUIT,x,y)){
			botonQuitActivo = true;
			setCambio(true);
		}
	}
}

bool ComandosCliente::in(int x, int y, int ancho, int alto, double x2, double y2){
	if((x2>=x)&&(x2<=x+ancho)&&(y2>=y)&&(y2<= y+alto))return true;
	else return false;
}

void ComandosCliente::resizear(){

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

	ANCHO_OBJ = anchoTemp*0.67;
	ALTO_OBJ = altoTemp - 2*SEPY;
	X_OBJ = SEPX;
	Y_OBJ = SEPY;

	ANCHO_B_PLAY = anchoTemp/8;
	ALTO_B_PLAY = ALTO_OBJ;
	X_B_PLAY = anchoTemp - (ANCHO_B_PLAY*3+3*SEPX-75);
	Y_B_PLAY = Y_OBJ;

	ANCHO_B_QUIT = ANCHO_B_PLAY;
	ALTO_B_QUIT = ALTO_OBJ;
	X_B_QUIT = X_B_PLAY + ANCHO_B_PLAY + SEPX;
	Y_B_QUIT = Y_OBJ;

	if(ImagenObjetivoOrig!=NULL){
		delete ImagenObjetivo;
		ImagenObjetivo = ImagenObjetivoOrig->scaleImagen(ANCHO_OBJ,ALTO_OBJ);
	}

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

void ComandosCliente::enterKeyPressed(JuegoCliente* juego){
	if(this->posDirActual!=0) juego->setFondo(dir);
}

void ComandosCliente::release(double x, double y,bool* flag,JuegoCliente* juego){
	/*if(in(X_B_OK,Y_B_OK,ANCHO_B_OK,ALTO_B_OK,x,y)&&botonOkActivo){
		juego->setFondo(dir);
	}else if(in(X_B_SAVE,Y_B_SAVE,ANCHO_B_SAVE,ALTO_B_SAVE,x,y)&&botonSaveActivo){
		juego->guardar();
	}else */if(in(X_B_PLAY,Y_B_PLAY,ANCHO_B_PLAY,ALTO_B_PLAY,x,y)&&botonPlayActivo){
		ready = !ready;
		if(ready){
			juego->sendReady();
		}else{
			juego->sendUnready();
		}
	} else {
		if(in(X_B_QUIT,Y_B_QUIT,ANCHO_B_QUIT,ALTO_B_QUIT,x,y)&&botonQuitActivo){
			juego->quit();
		}
	}
	botonPlayActivo =  botonQuitActivo = false;
//	botonOkActivo = botonSaveActivo = false;
	setCambio(true);

}
void ComandosCliente::setImagenObjetivo(std::string id_imagen_texto_objetivo){
	ImagenObjetivoOrig = new Imagen(id_imagen_texto_objetivo.c_str());
	ImagenObjetivo = ImagenObjetivoOrig->scaleImagen(ANCHO_OBJ,ALTO_OBJ);
}

void ComandosCliente::setListoUnpressed(){
	ready = false;
	botonPlayActivo = false;
	this->setCambio(true);
}