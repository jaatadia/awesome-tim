#include "Juego.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"

Juego::Juego(const char *file){
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
		ErrorLogHandler::addError(JUEGO_TAG,SDL_GetError());
		fallar();
	}
	
	ventana = new Ventana();
	superficie = new Superficie(ANCHO,ALTO);
	this->file = file;
	running = true;
	
	if(superficie->huboFallos()||ventana->huboFallos()){
		if(superficie->huboFallos()) ErrorLogHandler::addError("Programa","No se pudieron crear la superficie");
		else ErrorLogHandler::addError(JUEGO_TAG,"No se pudo crear la ventana");
		delete superficie;
		delete ventana;
		fallar();
	}
}


Juego::~Juego(){
	delete ventana;
	delete superficie;
	SDL_Quit();
	ErrorLogHandler::closeLog();
}


bool Juego::correr(){
	
	while((running)&&(!this->huboFallos())){
		onEvent();
		onLoop();
		onRender();
	}
	return true;

}

//dibuja en pantalla
void Juego:: onRender(){
	ventana->dibujar(superficie);
}

//manejo de eventos
void Juego:: onEvent(){
}

//manejo de eventos
void Juego:: onLoop(){
	
}

void Juego::quit(){
	running = false;
}