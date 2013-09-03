#include "Juego.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"
#include "ManejadorYaml.h"

Juego::Juego(const char *file){
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
		ErrorLogHandler::addError(JUEGO_TAG,SDL_GetError());
		fallar();
	}
	
	this->file = file;
	running = true;

	ventana = new Ventana();
	
	superficie = new Superficie(ANCHO_PANTALLA,ALTO_PANTALLA);
	terreno = new Terreno(ANCHO_TERRENO,ALTO_TERRENO);
	botonera = new Botonera(ANCHO_BOTONERA,ALTO_BOTONERA);
	comandos = new Comandos(ANCHO_COMANDOS,ALTO_COMANDOS);
	
	cargar();

	if(superficie->huboFallos()||ventana->huboFallos()){
		if(superficie->huboFallos()) ErrorLogHandler::addError("Programa","No se pudieron crear la superficie");
		else ErrorLogHandler::addError(JUEGO_TAG,"No se pudo crear la ventana");
		delete superficie;
		delete ventana;
		fallar();
	}
}
bool Juego::cargar(){
	ManejadorYaml::cargarJuego(file,botonera,terreno);
	return true;
}

bool Juego::guardar(){
	ManejadorYaml::guardarJuego(file,botonera,terreno);
	return true;
}

Juego::~Juego(){
	delete ventana;
	delete superficie;
	delete terreno;
	delete botonera;
	delete comandos;
	delete figuraEnAire;
	SDL_Quit();
	ErrorLogHandler::closeLog();
}


bool Juego::isRunning(){
	return running;
}

//dibuja en pantalla
void Juego:: onRender(){
	
	if(terreno->huboCambios()){
		superficie->dibujarSupreficie(terreno->getImpresion(),NULL,X_TERRENO,Y_TERRENO);
	}

	if(botonera->huboCambios()){
		superficie->dibujarSupreficie(botonera->getImpresion(),NULL,X_BOTONERA,Y_BOTONERA);
	}
	
	if(comandos->huboCambios()){
		superficie->dibujarSupreficie(comandos->getImpresion(),NULL,X_COMANDOS,Y_COMANDOS);
	}

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