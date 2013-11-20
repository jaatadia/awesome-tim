#include "MEstadosCliente.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"
#include "JuegoPlayCliente.h"
#include "JuegoCliente.h"
#include "Sonidos.h"
#include "SDL_image.h"

MEstadosCliente::MEstadosCliente(){
	
	if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS)!=0){
		ErrorLogHandler::addError(M_ESTADOS,SDL_GetError());
		fallar();
	}
	IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
	Sonidos::initialize();
	
	Eactivo = NULL;
	Eanterior = NULL;

	Eeditor = NULL;
	Eplay = NULL;

	running = true;

	ventana = new Ventana();
	superficie = new Superficie(ANCHO_PANTALLA,ALTO_PANTALLA);
	if(superficie->huboFallos()||ventana->huboFallos()){
		if(superficie->huboFallos()) ErrorLogHandler::addError("Programa","No se pudieron crear la superficie");
		else ErrorLogHandler::addError(M_ESTADOS,"No se pudo crear la ventana");
		delete superficie;
		delete ventana;
		fallar();
	}
}

MEstadosCliente::~MEstadosCliente(void){
	
	delete ventana;
	delete superficie;
	
	try{
		//if(Eanterior!=NULL)delete Eanterior;
		if(Eeditor!=NULL)delete Eeditor;
		if(Eplay!=NULL)delete Eplay;
	}catch(...){
	}
	
	SDL_Quit();
	ErrorLogHandler::closeLog();
}

bool MEstadosCliente::isRunning(){
	return running;
}

bool MEstadosCliente::onEvent(){
	if(getEstadoActivo()!=NULL){
		return getEstadoActivo()->onEvent(ventana,&superficie);
	}else{
		return false;
	}
}

bool MEstadosCliente::onLoop(){
	if(Eanterior){
		delete Eanterior;
		Eanterior = NULL;
	}
	if(getEstadoActivo()!=NULL){
		return getEstadoActivo()->onLoop();
	}else{
		return false;
	}
}

void MEstadosCliente::onRender(){
	if(getEstadoActivo()!=NULL){
		bool dibujar = getEstadoActivo()->onRender(superficie);
		if (dibujar) ventana->dibujar(superficie);
	}
}

void MEstadosCliente::salir(){
	running = false;
}

void MEstadosCliente::editor(){
	Eanterior = Eplay;
	Eplay = NULL;
	Eactivo = Eeditor;
	Eactivo->resume();
}

void MEstadosCliente::play(void* ter){
	
	Superficie* aux = superficie->scaleSurface(superficie->getAncho(),superficie->getAlto());
	superficie->restore();
	
	Eplay = new JuegoPlayCliente(aux,(void*) ter,this);
	Eactivo = Eplay;
}

void MEstadosCliente::init(int id)
{
	running = true;
	Eactivo = Eeditor = new JuegoCliente(id,this);
	Eanterior = Eplay = NULL;
}