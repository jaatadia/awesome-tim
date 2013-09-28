#include "MEstados.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"
#include "Juego.h"

MEstados::MEstados(const char *fileIn,const char *fileOut){
	
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
		ErrorLogHandler::addError(M_ESTADOS,SDL_GetError());
		fallar();
	}
	
	ventana = new Ventana();
	superficie = new Superficie(ANCHO_PANTALLA,ALTO_PANTALLA);
	if(superficie->huboFallos()||ventana->huboFallos()){
		if(superficie->huboFallos()) ErrorLogHandler::addError("Programa","No se pudieron crear la superficie");
		else ErrorLogHandler::addError(M_ESTADOS,"No se pudo crear la ventana");
		delete superficie;
		delete ventana;
		fallar();
	}

	this->fileIn = fileIn;
	this->fileOut = fileOut;
	running = true;

	Eactivo = Eeditor = new Juego(fileIn,fileOut,this);
	Eplay = NULL;
}

MEstados::~MEstados(void){
	
	delete Eeditor;
	delete Eplay;

	delete ventana;
	delete superficie;
	SDL_Quit();
	ErrorLogHandler::closeLog();
}

bool MEstados::isRunning(){
	return running;
}

void MEstados::onEvent(){
	getEstadoActivo()->onEvent(&superficie);
}

void MEstados::onLoop(){
	getEstadoActivo()->onLoop();
}

void MEstados::onRender(){
	getEstadoActivo()->onRender(superficie);
	ventana->dibujar(superficie);
}
	
void MEstados::esperar(double miliseconds){
	SDL_Delay(miliseconds);
}

void MEstados::salir(){
	running = false;
}

void MEstados::editor(){}

void MEstados::play(){}