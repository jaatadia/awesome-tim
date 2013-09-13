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
	
	botonera = new BotoneraController(ANCHO_BOTONERA,ALTO_BOTONERA, 4);
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

/***************Test de arrastra y girar figura*************************/

	Contenedor::putMultimedia("../images/cuadrado.jpg",new Imagen("../images/Cuadrado.png"));
	Figura* fig = new Figura("../images/cuadrado.jpg",new Cuadrado(20,20,50- X_TERRENO_LOGICO,50- Y_TERRENO_LOGICO,0));
	terreno->agregarFigura(fig);

	Contenedor::putMultimedia("../images/Circulo.jpg",new Imagen("../images/Circulo.png"));
	fig = new Figura("../images/Circulo.jpg",new Circulo(20,50- X_TERRENO_LOGICO,50- Y_TERRENO_LOGICO,0));
	terreno->agregarFigura(fig);

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
		superficie->dibujarSupreficie(terreno->getImpresion(escalas),NULL,escalas->getCantidadUnidadesFisicasX(X_TERRENO_LOGICO),escalas->getCantidadUnidadesFisicasY(Y_TERRENO_LOGICO));
	}

	if(botonera->huboCambios()){
		superficie->dibujarSupreficie(botonera->getImpresion(),NULL,escalas->getCantidadUnidadesFisicasX(X_BOTONERA_LOGICO),escalas->getCantidadUnidadesFisicasY(Y_BOTONERA_LOGICO));
	}
	
	//if(comandos->huboCambios()){
		superficie->dibujarSupreficie(comandos->getImpresion(escalas),NULL,escalas->getCantidadUnidadesFisicasX(X_COMANDOS_LOGICO),escalas->getCantidadUnidadesFisicasY(Y_COMANDOS_LOGICO));
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

			if (evento.key.keysym.sym == SDLK_KP_ENTER || evento.key.keysym.sym == SDLK_RETURN)
				comandos->enterKeyPressed(this);

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
					terreno->arrastrarFigura(posClickX - X_TERRENO_LOGICO, posClickY - Y_TERRENO_LOGICO, cantMovX, cantMovY);
				}else
					if (evento.motion.state == SDL_BUTTON_RMASK){
						terreno->rotarFigura(posClickX - X_TERRENO_LOGICO, posClickY - Y_TERRENO_LOGICO, cantMovX, cantMovY);
					}

			//muevo la figura voladora, si es que la hay
			if (figuraEnAire)
				if (figuraEnAire->esMiPosicion(posClickX,posClickY))
					figuraEnAire->cambiarPosicion(cantMovX, cantMovY);


			//chequeo la posicion final del mouse por si hay perdida de foco del terreno

			double posFinalX = posClickX + cantMovX;
			double posFinalY = posClickY + cantMovY;

			if (!enTerreno(posFinalX,posFinalY))
				terreno->soltarFigura();

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
				if ((evento.button.state == SDL_BUTTON_LMASK) && (shiftPressed)){
					//click izq y shift
					terreno->borrarFigura(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO);
				}
				else{
					if (evento.button.state == SDL_BUTTON_LMASK)
						terreno->buscarActiva(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO);
				}

			if (enBotonera(posClickX,posClickY)){
				//es de la botonera
				//scroll o crear figura
			}

			if (enComandos(posClickX,posClickY))
				//es de comandos
				if (evento.button.state == SDL_BUTTON_LMASK){
					//como comandos trabaja con pixels (?) lo paso sin convertir
					//y por cierto: REFERENCIA CIRCULAAAAR!!!
					comandos->click(escalas->getCantidadUnidadesFisicasX(posClickX - X_COMANDOS_LOGICO), escalas->getCantidadUnidadesFisicasY(posClickY - Y_COMANDOS_LOGICO), this);
				}

			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			posClickX = escalas->getCantidadUnidadesLogicasX(evento.button.x);
			posClickY = escalas->getCantidadUnidadesLogicasY(evento.button.y);
			//siempre se suelta la figura agarrada por terreno
			terreno->soltarFigura();

			if (figuraEnAire)
				//o es de figura viva
				//soltarFiguraenAire();


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
		case SDL_WINDOWEVENT_LEAVE:
		{
			//mouse salio de la pantalla
			
			terreno->soltarFigura();
			//soltarFiguraEnAire() si es que la hay

			break;
		}
		case SDL_WINDOWEVENT_RESIZED:
		{
			double anchoActual= evento.data1;
			double altoActual= evento.data2;

			escalas->setEscalaX(UNIDADES_LOGICAS_TOTAL/anchoActual);
			escalas->setEscalaY(UNIDADES_LOGICAS_TOTAL/altoActual);
			//obtengo superficie resizeada para el juego, esta es la grande donde se pegan las otras.
			delete superficie;
			superficie = new Superficie(escalas->getCantidadUnidadesFisicasX(ANCHO_PANTALLA_LOGICO),escalas->getCantidadUnidadesFisicasY(ALTO_PANTALLA_LOGICO));

			//Y tambien cambian todas las vistas!!
			terreno->setCambio(true);
			terreno->cambioVistaFiguras();
			terreno->resizear(escalas);

			botonera->setCambio(true);
			//no se si es necesario algo similar para botonera


			comandos->setCambio(true);
			comandos->resizear(escalas);

			break;
		}
	}
}

void Juego::setFondo(const char* dir){
	terreno->setFondo(dir);
}

bool Juego::enTerreno(double posX,double posY){

	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX =  X_TERRENO_LOGICO ;
	finalLogicoX = ANCHO_TERRENO_LOGICO + X_TERRENO_LOGICO;
	ppioLogicoY = Y_TERRENO_LOGICO;
	finalLogicoY = ALTO_TERRENO_LOGICO + Y_TERRENO_LOGICO;

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}

bool Juego::enBotonera(double posX,double posY){

	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX =  X_BOTONERA_LOGICO ;
	finalLogicoX = ANCHO_BOTONERA_LOGICO + X_BOTONERA_LOGICO;
	ppioLogicoY = Y_BOTONERA_LOGICO;
	finalLogicoY = ALTO_BOTONERA_LOGICO + Y_BOTONERA_LOGICO;

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}

bool Juego::enComandos(double posX,double posY){
	
	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX =  X_COMANDOS_LOGICO;
	finalLogicoX = ANCHO_COMANDOS_LOGICO + X_COMANDOS_LOGICO;
	ppioLogicoY = Y_COMANDOS_LOGICO;
	finalLogicoY = ALTO_COMANDOS_LOGICO + Y_COMANDOS_LOGICO;

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}