#include "Juego.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"
#include "Cuadrado.h"
#include "CargadorYaml.h"
#include "GeneradorYaml.h"

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
	botonera = new Botonera(ANCHO_BOTONERA,ALTO_BOTONERA, 4);
	comandos = new Comandos(ANCHO_COMANDOS,ALTO_COMANDOS);
	escalas = new EscalasDeEjes();
	figuraEnAire=NULL;

	cargar();

	if(superficie->huboFallos()||ventana->huboFallos()){
		if(superficie->huboFallos()) ErrorLogHandler::addError("Programa","No se pudieron crear la superficie");
		else ErrorLogHandler::addError(JUEGO_TAG,"No se pudo crear la ventana");
		delete superficie;
		delete ventana;
		fallar();
	}

/******************para prueba de arrastrar y rotar figura por el terreno**********************/
/*
	Contenedor::putMultimedia("../images/cuadrado.jpg",new Imagen("../images/Cuadrado.png"));
	Figura* fig = new Figura("../images/cuadrado.jpg",new Cuadrado(20,20,50,50,0));
	terreno->agregarFigura(fig);
*/
}

bool Juego::cargar(){
	CargadorYaml::cargarJuego(file,botonera,terreno);
	return true;
}

bool Juego::guardar(){
	GeneradorYaml::guardarJuego(file,botonera,terreno);
	return true;
}

Juego::~Juego(){
	delete ventana;
	delete superficie;
	delete terreno;
	delete botonera;
	delete comandos;
	delete escalas;
	if(figuraEnAire!=NULL)delete figuraEnAire;
	SDL_Quit();
	ErrorLogHandler::closeLog();
}


bool Juego::isRunning(){
	return running;
}

//dibuja en pantalla
void Juego:: onRender(){
	
	
	if(terreno->huboCambios()){
		superficie->dibujarSupreficie(terreno->getImpresion(escalas),NULL,X_TERRENO,Y_TERRENO);
	}

	if(botonera->huboCambios()){
		superficie->dibujarSupreficie(botonera->getImpresion(),NULL,X_BOTONERA,Y_BOTONERA);
	}
	
	if(comandos->huboCambios()){
		superficie->dibujarSupreficie(comandos->getImpresion(),NULL,X_COMANDOS,Y_COMANDOS);
	}

	ventana->dibujar(superficie);
	
}

void Juego:: onLoop(){
}



//manejo de eventos
void Juego:: onEvent(){

SDL_Event evento;
double posClickX, posClickY;

while(SDL_PollEvent(&evento)){
	switch(evento.type){
		case SDL_WINDOWEVENT:
		{
			actuarVentana(evento.window.windowID,evento.window,this->escalas);//tipo escala
			//actualiza las escalas si fue un resize
			break;
		}
		case SDL_KEYDOWN: 
		{
			//averiguar como leer un shift...
			break;
		}
		case SDL_TEXTINPUT:
		{
			//para el textbox en comandos
			break;
		}
		case SDL_MOUSEMOTION:
		{
			//convertir a unidades logicas

			double cantMovX = escalas->getCantidadUnidadesLogicasX(evento.motion.xrel);
			double cantMovY = escalas->getCantidadUnidadesLogicasY(evento.motion.yrel);

			posClickX = escalas->getCantidadUnidadesLogicasX(evento.motion.x);
			posClickY = escalas->getCantidadUnidadesLogicasY(evento.motion.y);

			//averiguar si esta en terreno o figuraViva u otro lado
				
			// y verificar que el boton izq este apretado o no deberia pasar arrastre, idem boton derecho
			if ((posClickX>=escalas->getCantidadUnidadesLogicasX(X_TERRENO)) && (posClickX<=escalas->getCantidadUnidadesLogicasX(ANCHO_TERRENO+X_TERRENO)) && (posClickY>=escalas->getCantidadUnidadesLogicasX(Y_TERRENO)) && (posClickY<=escalas->getCantidadUnidadesLogicasX(ALTO_TERRENO+Y_TERRENO)))
				if (evento.motion.state == SDL_BUTTON_LMASK){				
				//  terreno->arrastrarFigura(posClickX - X_TERRENO, posClickY - Y_TERRENO, cantMovX, cantMovY);
					terreno->arrastrarFigura(posClickX , posClickY , cantMovX, cantMovY);
				}else
					if (evento.motion.state == SDL_BUTTON_RMASK){
						terreno->rotarFigura(posClickX , posClickY , cantMovX, cantMovY);
					}

			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			//verificar que boton es el apretado!!!

			posClickX = escalas->getCantidadUnidadesLogicasX(evento.button.x);
			posClickY = escalas->getCantidadUnidadesLogicasY(evento.button.y);

			if (posClickX>=X_TERRENO && posClickX<=ANCHO_TERRENO+X_TERRENO && posClickY>=Y_TERRENO && posClickY<=ALTO_TERRENO+Y_TERRENO)
				//es del terreno

			if ((posClickX>=X_BOTONERA && posClickX<=ANCHO_BOTONERA+X_BOTONERA && posClickY>=Y_BOTONERA && posClickY<=ALTO_BOTONERA+Y_BOTONERA))
				//es de la botonera
				//poner un while apretado para el scroll

			if ((posClickX>=X_BOTONERA && posClickX<=ANCHO_BOTONERA+X_BOTONERA && posClickY>=Y_BOTONERA && posClickY<=ALTO_BOTONERA+Y_BOTONERA))
				//es de comandos

			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			posClickX = escalas->getCantidadUnidadesLogicasX(evento.button.x);
			posClickY = escalas->getCantidadUnidadesLogicasY(evento.button.y);

			if (posClickX>=X_TERRENO && posClickX<=ANCHO_TERRENO+X_TERRENO && posClickY>=Y_TERRENO && posClickY<=ALTO_TERRENO+Y_TERRENO)
				//es del terreno
				terreno->soltarFigura();

			//o es de figura viva

			break;
		}
		case SDL_MOUSEWHEEL:
		{
			//scroll de botonera SIEMPRE sin importar la posicion

			break;
		}
		case SDL_QUIT: //salir del juego
		{
			quit();
			break;
		}
	}
}

}


void Juego::quit(){
	running = false;
}

void Juego::actuarVentana(Uint32 IDventana,SDL_WindowEvent evento,EscalasDeEjes* escalas){

	if(evento.event == SDL_WINDOWEVENT_CLOSE){
		if (evento.windowID == ventana->getID())
			quit();
	}
}