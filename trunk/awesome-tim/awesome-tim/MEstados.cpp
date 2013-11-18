#include "MEstados.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"
#include "Juego.h"
#include "JuegoPlay.h"
#include "Fuente.h"

MEstados::MEstados(const char *fileIn,const char *fileOut){
	
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
		ErrorLogHandler::addError(M_ESTADOS,SDL_GetError());
		fallar();
	}
	ventana = NULL;
	superficie = NULL;
	//ventana = new Ventana();
	//superficie = new Superficie(ANCHO_PANTALLA,ALTO_PANTALLA);
	//if(superficie->huboFallos()||ventana->huboFallos()){
	//	if(superficie->huboFallos()) ErrorLogHandler::addError("Programa","No se pudieron crear la superficie");
	//	else ErrorLogHandler::addError(M_ESTADOS,"No se pudo crear la ventana");
	//	delete superficie;
	//	delete ventana;
	//	fallar();
	//}

	this->fileIn = fileIn;
	this->fileOut = fileOut;
	running = true;

	this->setId(0);

	Sonidos::noSound();

	Eactivo = Eeditor = new Juego(fileIn,fileOut,this);
	Eanterior = Eplay = NULL;

}

MEstados::~MEstados(void){
	
	delete ventana;
	delete superficie;
	
	delete Eanterior;
	delete Eeditor;
	delete Eplay;
	
	Fuente::end();
	Sonidos::end();
	SDL_Quit();
	ErrorLogHandler::closeLog();
}

bool MEstados::isRunning(){
	return running;
}

bool MEstados::onEvent(){
	//return getEstadoActivo()->onEvent(ventana,&superficie);
	return false;
}

void MEstados::onLoop(){
	if(Eanterior){
		delete Eanterior;
		Eanterior = NULL;
	}
	getEstadoActivo()->onLoop();
}

void MEstados::onRender(){
	//bool dibujar = getEstadoActivo()->onRender(superficie);
	//if (dibujar) ventana->dibujar(superficie);
}

void MEstados::salir(){
	running = false;
}

void MEstados::editor(){
	Eanterior = Eplay;
	Eplay = NULL;
	Eactivo = Eeditor;
	Eactivo->resume();
}

void MEstados::play(void* ter){
	
	Superficie* aux = NULL;//superficie->scaleSurface(superficie->getAncho(),superficie->getAlto());
	//superficie->restore();
	
	Eplay = new JuegoPlay(aux,ter,this);
	Eactivo = Eplay;
}