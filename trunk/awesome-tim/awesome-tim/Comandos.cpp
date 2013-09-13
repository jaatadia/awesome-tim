#include "Comandos.h"

Comandos::Comandos(int ancho,int alto){
	anchoOrig = this->ancho = ancho;
	altoOrig = this->alto = alto;
	sup = new Superficie(ancho,alto);

	this->posDirActual = 0;
	dir[0] = '\0';
	
	//paso todo a unidades logicas originales
	//lo puedo harcodear sin afterefects porque esta en el constructor
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

	ANCHO_B_QUIT = ANCHO_B_OK;
	ALTO_B_QUIT = ALTO_TBOX;
	X_B_QUIT = X_B_SAVE + ANCHO_B_SAVE + SEPX;
	Y_B_QUIT = Y_TBOX;

	
	
	BotonOKOrig = new Imagen("../images/botonOK.png");
	BotonOK = BotonOKOrig->scaleImagen(ANCHO_B_OK,ALTO_B_OK);
	

	BotonSaveOrig = new Imagen("../images/botonSave.png");
	BotonSave = BotonSaveOrig->scaleImagen(ANCHO_B_SAVE,ALTO_B_SAVE);
	
	BotonQuitOrig = new Imagen("../images/botonQuit.png");
	BotonQuit = BotonQuitOrig->scaleImagen(ANCHO_B_QUIT,ALTO_B_QUIT);
	
	
	
	this->setCambio(true);
}

Comandos::~Comandos(void){
	delete sup;
	delete BotonOK;
	delete BotonQuit;
	delete BotonSave;
	delete BotonOKOrig;
	delete BotonQuitOrig;
	delete BotonSaveOrig;
}

Superficie* Comandos::getImpresion(EscalasDeEjes* escalas){
	if(this->huboCambios()) redraw(escalas);
	this->setCambio(false);
	return sup;
}

Superficie* Comandos::getImpresion(){
	return sup;
}

void Comandos::redraw(EscalasDeEjes* escalas){

	sup->restoreGris();
	sup->dibujarCuadradoNegro(X_TBOX,Y_TBOX,ANCHO_TBOX,ALTO_TBOX);
	sup->dibujarImagen(BotonOK,NULL,X_B_OK,Y_B_OK);
	sup->dibujarImagen(BotonSave,NULL,X_B_SAVE,Y_B_SAVE);
	sup->dibujarImagen(BotonQuit,NULL,X_B_QUIT,Y_B_QUIT);

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
		juego->setFondo(dir);
	}else if(in(X_B_SAVE,Y_B_SAVE,ANCHO_B_SAVE,ALTO_B_SAVE,x,y)){
		juego->guardar();
	}else if(in(X_B_QUIT,Y_B_QUIT,ANCHO_B_QUIT,ALTO_B_QUIT,x,y)){
		juego->quit();
	}
}

bool Comandos::in(int x, int y, int ancho, int alto, double x2, double y2){
	if((x2>=x)&&(x2<=x+ancho)&&(y2>=y)&&(y2<= y+alto))return true;
	else return false;
}

void Comandos::resizear(EscalasDeEjes* escalas){

	
	//si cambiaron las escalas...consigo una nueva superficie del tamanio correcto
	ancho = escalas->getCantidadUnidadesFisicasX(anchoOrig/5);
	alto =  escalas->getCantidadUnidadesFisicasY(altoOrig/5);

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

	ANCHO_B_QUIT = ANCHO_B_OK;
	ALTO_B_QUIT = ALTO_TBOX;
	X_B_QUIT = X_B_SAVE + ANCHO_B_SAVE + SEPX;
	Y_B_QUIT = Y_TBOX;
	
	delete BotonOK;
	BotonOK = BotonOKOrig->scaleImagen(ANCHO_B_OK,ALTO_B_OK);
	//BotonOK = new Imagen("OK",ALTO_B_OK,255,255,255);

	delete BotonSave;
	BotonSave = BotonSaveOrig->scaleImagen(ANCHO_B_SAVE,ALTO_B_SAVE);
	//BotonSave = new Imagen("Save",ALTO_B_SAVE,255,255,255);

	delete BotonQuit;
	BotonQuit = BotonQuitOrig->scaleImagen(ANCHO_B_QUIT,ALTO_B_QUIT);
	//BotonQuit = new Imagen("Quit",ALTO_B_QUIT,255,255,255);
	
	this->setCambio(true);
}

void Comandos::enterKeyPressed(Juego* juego){
	if(this->posDirActual!=0) juego->setFondo(dir);
}