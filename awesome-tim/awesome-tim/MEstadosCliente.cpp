#include "MEstadosCliente.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"
#include "JuegoPlayCliente.h"
#include "JuegoCliente.h"


MEstadosCliente::MEstadosCliente(){
	
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
		ErrorLogHandler::addError(M_ESTADOS,SDL_GetError());
		fallar();
	}
	
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
	
	delete Eanterior;
	delete Eeditor;
	delete Eplay;
	
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

void MEstadosCliente::onLoop(){
	if(Eanterior){
		delete Eanterior;
		Eanterior = NULL;
	}
	if(getEstadoActivo()!=NULL){
		getEstadoActivo()->onLoop();
	}
}

void MEstadosCliente::onRender(){
	if(getEstadoActivo()!=NULL){
		bool dibujar = getEstadoActivo()->onRender(superficie);
		if (dibujar) ventana->dibujar(superficie);
	}
}
	
void MEstadosCliente::esperar(double miliseconds){
	SDL_Delay(miliseconds);
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

void MEstadosCliente::init()
{
	std::cout<<"entroaca!!!\n";
	running = true;
	Eactivo = Eeditor = new JuegoCliente(this->id,this);
	Eanterior = Eplay = NULL;
}