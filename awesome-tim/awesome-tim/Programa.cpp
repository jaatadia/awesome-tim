#include "Programa.h"
#include "SDL.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"
#include "Contenedor.h"
#include "Cuadrado.h"

//crea el programa
Programa::Programa(const char* file)
{
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0){
		ErrorLogHandler::addError(PROGRAMA_TAG,SDL_GetError());
		fallar();
	}
	
	ventana = new Ventana();
	superficie = new Superficie(ANCHO_PANTALLA,ALTO_PANTALLA);
	//img = new Imagen("../images/test.jpg");
	rot = 0;
	
	Contenedor::putMultimedia("../images/test.jpg",new Imagen("../images/test.jpg"));
	this->fig = new Figura("../images/test.jg",new Cuadrado(200,200),20,200,300);
	

	if(superficie->huboFallos()||ventana->huboFallos()/*||img->huboFallos()*/){
		if(superficie->huboFallos()) ErrorLogHandler::addError("Programa","No se pudieron crear la superficie");
		else ErrorLogHandler::addError(PROGRAMA_TAG,"No se pudo crear la ventana");
		delete superficie;
		delete ventana;
		fallar();
	}
	running = true;
}

//destruye el programa
Programa::~Programa(void)
{
	if(!huboFallos()){
		delete ventana;
		delete superficie;
		//delete img;
		SDL_Quit();
	}
	ErrorLogHandler::closeLog();
}

//inicia el programa
void Programa::correr(){
	
	while((running)&&(!this->huboFallos())){
		onEvent();
		onLoop();
		onRender();
	}
}

//actualiza el modelo
void Programa:: onLoop(){
	rot+=16;
	if(rot>(360*2))rot=0;
}

//dibuja en pantalla
void Programa:: onRender(){
	superficie->restore();
	//Imagen* temp;
	//if(rot<360)	temp = img->rotarImagen(rot);
	//else temp = img->rotarCuadradoImagen(rot);
	//superficie->dibujarImagen(temp,NULL,0,0);
	//delete temp;
	fig->dibujar(superficie);
	ventana->dibujar(superficie);
}

//manejo de eventos
void Programa:: onEvent(){
	SDL_Event evento;
	while(SDL_PollEvent(&evento)){
		if (evento.type == SDL_WINDOWEVENT){
			if(evento.window.event == SDL_WINDOWEVENT_CLOSE){
				if (evento.window.windowID == ventana->getID()) running = false;
			}
		}
	}
}

