#include "Comandos.h"

Comandos::Comandos(int ancho,int alto){
	this->ancho = ancho;
	this->alto = alto;
	sup = new Superficie(ancho,alto);

	this->posDirActual = 0;
	dir[0] = '\0';
	
	//paso todo a unidades logicas originales
	//lo puedo harcodear sin afterefects porque esta en el constructor
	int anchoTemp,altoTemp;

	anchoTemp = ancho/5;
	altoTemp=alto/5;

	SEP = 1;

	ANCHO_TBOX = anchoTemp/3;
	ALTO_TBOX = altoTemp *3/4;
	X_TBOX = SEP;
	Y_TBOX = altoTemp/8 ;
	
	ANCHO_B_OK = anchoTemp/8;
	ALTO_B_OK = ALTO_TBOX;
	X_B_OK = X_TBOX + ANCHO_TBOX + SEP;
	Y_B_OK = Y_TBOX;


	ANCHO_B_SAVE = ANCHO_B_OK;
	ALTO_B_SAVE = ALTO_TBOX;
	X_B_SAVE = anchoTemp - (ANCHO_B_SAVE*2+2*SEP);
	Y_B_SAVE = Y_TBOX;

	ANCHO_B_QUIT = ANCHO_B_OK;
	ALTO_B_QUIT = ALTO_TBOX;
	X_B_QUIT = X_B_SAVE + ANCHO_B_SAVE + SEP;
	Y_B_QUIT = Y_TBOX;

	
	
	Imagen* temp = new Imagen("../images/botonOK.png");
	BotonOK = temp->scaleImagen(5*ANCHO_B_OK,5*ALTO_B_OK);
	delete temp;

	temp = new Imagen("../images/botonSave.png");
	BotonSave = temp->scaleImagen(5*ANCHO_B_SAVE,5*ALTO_B_SAVE);
	delete temp;

	temp = new Imagen("../images/botonQuit.png");
	BotonQuit = temp->scaleImagen(5*ANCHO_B_QUIT,5*ALTO_B_QUIT);
	delete temp;
	
	
	this->setCambio(true);
}

Comandos::~Comandos(void){
	delete sup;
	delete BotonOK;
	delete BotonQuit;
	delete BotonSave;
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
	
	int X_TBOX = escalas->getCantidadUnidadesFisicasX(this->X_TBOX);
	int Y_TBOX = escalas->getCantidadUnidadesFisicasY(this->Y_TBOX);
	int ANCHO_TBOX = escalas->getCantidadUnidadesFisicasX(this->ANCHO_TBOX);
	int ALTO_TBOX = escalas->getCantidadUnidadesFisicasY(this->ALTO_TBOX);
	int X_B_OK = escalas->getCantidadUnidadesFisicasX(this->X_B_OK);
	int Y_B_OK = escalas->getCantidadUnidadesFisicasY(this->Y_B_OK);
	int X_B_SAVE = escalas->getCantidadUnidadesFisicasX(this->X_B_SAVE);
	int Y_B_SAVE = escalas->getCantidadUnidadesFisicasY(this->Y_B_SAVE);
	int X_B_QUIT = escalas->getCantidadUnidadesFisicasX(this->X_B_QUIT);
	int Y_B_QUIT = escalas->getCantidadUnidadesFisicasY(this->Y_B_QUIT);

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
	ancho = escalas->getCantidadUnidadesFisicasX(ANCHO_COMANDOS_LOGICO);
	alto =  escalas->getCantidadUnidadesFisicasY(ALTO_COMANDOS_LOGICO);

	delete sup;

	sup = new Superficie(ancho,alto);

}