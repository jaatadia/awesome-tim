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
	terreno->setFondo("../images/test.jpg");
	
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

	shiftPressed = false;
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
	//delete botonera;
	delete comandos;
	delete escalas;
	Contenedor::deleteContenedor();
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
	
	//if(comandos->huboCambios()){
		superficie->dibujarSupreficie(comandos->getImpresion(),NULL,X_COMANDOS,Y_COMANDOS);
	//}

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
			actuarVentana(evento.window.windowID,evento.window,this->escalas);
			//actualiza las escalas si fue un resize
			break;
		}
		case SDL_KEYDOWN: 
		{
			if ((evento.key.keysym.sym == SDLK_LSHIFT) || (evento.key.keysym.sym == SDLK_RSHIFT))
				shiftPressed = true;

			//si fue backtrace entonces borrar una letra de comandos
			if (evento.key.keysym.sym == SDLK_BACKSPACE)
				comandos->borrarLetra();

			break;
		}
		case SDL_KEYUP: 
		{
			if ((evento.key.keysym.sym == SDLK_LSHIFT) || (evento.key.keysym.sym == SDLK_RSHIFT))
				shiftPressed = false;

			break;
		}
		case SDL_TEXTINPUT:
		{
			char charIngresado;

			charIngresado = evento.text.text[0];
			comandos->agregarLetra(charIngresado);

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
			if (enTerreno(posClickX,posClickY))
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
			//verificar shift o no!!!

			posClickX = escalas->getCantidadUnidadesLogicasX(evento.button.x);
			posClickY = escalas->getCantidadUnidadesLogicasY(evento.button.y);

			if (enTerreno(posClickX,posClickY))
				//es del terreno
				if ((evento.button.state == SDL_BUTTON_LMASK) && (shiftPressed))
					//click izq y shift
					terreno->borrarFigura(posClickX,posClickY);

			if (enBotonera(posClickX,posClickY)){
				//es de la botonera
				//poner un while apretado para el scroll
			}

			if (enComandos(posClickX,posClickY))
				//es de comandos
				if (evento.button.state == SDL_BUTTON_LMASK){
					//como comandos trabaja con pixels (?) lo paso sin convertir
					//y por cierto: REFERENCIA CIRCULAAAAR!!!
					comandos->click(evento.button.x - X_COMANDOS, evento.button.y - Y_COMANDOS, this);

				}

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
		case SDL_QUIT: 
		{
			//salir del juego
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

	switch (evento.event){
		case SDL_WINDOWEVENT_CLOSE:
		{
			if (evento.windowID == ventana->getID())
				quit();

			break;
		}	
		//INVESTIGAR ESTE CASO

		//case SDL_WINDOWEVENT_SIZE_CHANGED:
		//{
		//	//cambio las escalas

		//break;
		//}
		case SDL_WINDOWEVENT_RESIZED:
		{
			double anchoActual= evento.data1;
			double altoActual= evento.data2;

			escalas->setEscalaX(120/anchoActual); //CONSTANTE UNIDADES LOGICAS TOTALES
			escalas->setEscalaY(120/altoActual);
		break;
		}
	}
}

void Juego::setFondo(const char* dir){
	terreno->setFondo(dir);
}

bool Juego::enTerreno(double posX,double posY){

	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX = escalas->getCantidadUnidadesLogicasX( X_TERRENO );
	finalLogicoX = escalas->getCantidadUnidadesLogicasX(ANCHO_TERRENO + X_TERRENO);
	ppioLogicoY = escalas->getCantidadUnidadesLogicasY(Y_TERRENO);
	finalLogicoY = escalas->getCantidadUnidadesLogicasY(ALTO_TERRENO + Y_TERRENO);

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}

bool Juego::enBotonera(double posX,double posY){

	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX = escalas->getCantidadUnidadesLogicasX( X_BOTONERA );
	finalLogicoX = escalas->getCantidadUnidadesLogicasX(ANCHO_BOTONERA + X_BOTONERA);
	ppioLogicoY = escalas->getCantidadUnidadesLogicasY(Y_BOTONERA);
	finalLogicoY = escalas->getCantidadUnidadesLogicasY(ALTO_BOTONERA + Y_BOTONERA);

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}

bool Juego::enComandos(double posX,double posY){
	
	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX = escalas->getCantidadUnidadesLogicasX( X_COMANDOS);
	finalLogicoX = escalas->getCantidadUnidadesLogicasX(ANCHO_COMANDOS + X_COMANDOS);
	ppioLogicoY = escalas->getCantidadUnidadesLogicasY(Y_COMANDOS);
	finalLogicoY = escalas->getCantidadUnidadesLogicasY(ALTO_COMANDOS + Y_COMANDOS);

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}