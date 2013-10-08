#include "Juego.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"
#include "CargadorYaml.h"
#include "GeneradorYaml.h"
#include "Cuadrado.h"
#include "Circulo.h"
#include "Soga.h"
#include "PoligonoRegular.h"
#include "Triangulo.h"

#include "Figura.h"

Juego::Juego(const char *fileIn,const char *fileOut,MaquinaEstados* maq){
	
	this->maq = maq;
	this->fileIn = fileIn;
	this->fileOut = fileOut;
	terreno = new Terreno(ANCHO_TERRENO,ALTO_TERRENO,true);
	botonera = new BotoneraController(ANCHO_BOTONERA,ALTO_BOTONERA, 4);
	comandos = new Comandos(ANCHO_COMANDOS,ALTO_COMANDOS);
	figuraEnAire=NULL;
	
	cargar();

	this->setCambio(true);

	shiftPressed = false;
	estaActiva = false;
	clickPressed = false;

//*********************prueba de soga***********************

//	terreno->agregarFigura(new Soga(ImgSegmSoga,new Cuadrado(80,ALTO_SEGMENTO_SOGA,50,50,0)));

}

bool Juego::cargar(){
	CargadorYaml::cargarJuego(fileIn,botonera,terreno);
	if(botonera->estaVacia()) botonera->agregarBotonesDefault();
	//necesario para que se ordenen cosas dentro de botonera
	botonera->resizear();
	return true;
}

bool Juego::guardar(){
	bool seGuardo = false;
	
	seGuardo = GeneradorYaml::guardarJuego(fileOut,botonera,terreno);
	
	if (!seGuardo){
		ErrorLogHandler::addError("GeneradorYaml", "Error al abrir o cerrar los archivos al guardar la partida.");
	
	}

	return true;
}

Juego::~Juego(){

	delete terreno;
	delete botonera;
	delete comandos;
	delete EscalasDeEjes::getInstance();
	Contenedor::deleteContenedor();
	if(figuraEnAire!=NULL)delete figuraEnAire;
}


//dibuja en pantalla

bool Juego:: onRender(Superficie* superficie){

	bool dibujar = false;
	
	if (figuraEnAire){
		confirmarPosicionFiguraEnAire();
	}
	
	if(this->huboCambios()){
		superficie->restore();
		setCambio(false);
		dibujar = true;
	}
	
	if(terreno->huboCambios()){
		//terreno->dibujate(superficie,EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(X_TERRENO_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(Y_TERRENO_LOGICO));
		superficie->dibujarSupreficie(terreno->getImpresion(),NULL,EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(X_TERRENO_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(Y_TERRENO_LOGICO));
		dibujar = true;
	}

	if(botonera->huboCambios()){
		superficie->dibujarSupreficie(botonera->getImpresion(),NULL,EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(X_BOTONERA_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(Y_BOTONERA_LOGICO));
		dibujar = true;
	}
	
	if(comandos->huboCambios()){
		superficie->dibujarSupreficie(comandos->getImpresion(),NULL,EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(X_COMANDOS_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(Y_COMANDOS_LOGICO));
		dibujar = true;
	}

	if(figuraEnAire){
		figuraEnAire->dibujar(superficie);
		dibujar = true;
	}

	return dibujar;
}
	
void Juego:: onLoop(){
	terreno->actualizarModelo();
}

//manejo de eventos
bool Juego:: onEvent(Ventana* ventana,Superficie** sup){

SDL_Event evento;
double posClickX, posClickY;
bool aux = false;

while(SDL_PollEvent(&evento)){
	switch(evento.type){
		case SDL_WINDOWEVENT:
		{
			actuarVentana(ventana,sup,evento.window.windowID,evento.window);
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
			if(clickPressed){
				if(charIngresado == '+'){
					if(figuraEnAire) figuraEnAire->agrandar();
					else terreno->agrandarFigura();
				}else if(charIngresado == '-'){
					if(figuraEnAire) figuraEnAire->achicar();
					else terreno->achicarFigura();
				}
			}else comandos->agregarLetra(charIngresado);

			break;
		}
		case SDL_MOUSEMOTION:
		{
			//convertir a unidades logicas

			double cantMovX = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(evento.motion.xrel);
			double cantMovY = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(evento.motion.yrel);

			posClickX = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(evento.motion.x);
			posClickY = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(evento.motion.y);

			//averiguar si esta en terreno o figuraViva u otro lado
				
			// y verificar que el boton izq este apretado o no deberia pasar arrastre, idem boton derecho
			if (posEnTerreno(posClickX,posClickY))
				if (evento.motion.state == SDL_BUTTON_LMASK){				
					terreno->arrastrarFigura(posClickX - X_TERRENO_LOGICO, posClickY - Y_TERRENO_LOGICO, cantMovX, cantMovY);
				}else
					if (evento.motion.state == SDL_BUTTON_RMASK){
						terreno->rotarFigura(posClickX - X_TERRENO_LOGICO, posClickY - Y_TERRENO_LOGICO, cantMovX, cantMovY);
					}

			//muevo la figura voladora, si es que la hay
			if (figuraEnAire)
				if ((estaActiva)){
					confirmarPosicionFiguraEnAire();
					figuraEnAire->cambiarPosicion(cantMovX, cantMovY);
				}
						
			//chequeo la posicion del mouse por si hay perdida de foco del terreno
			if (!posEnTerreno(posClickX,posClickY))
				terreno->soltarFigura();

			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			clickPressed = true;
			posClickX = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(evento.button.x);
			posClickY = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(evento.button.y);

			if (posEnTerreno(posClickX,posClickY))
				//es del terreno
				if ((evento.button.state == SDL_BUTTON_LMASK) && (shiftPressed))
					//click izq y shift
					terreno->borrarFigura(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO);
				else
					terreno->buscarActiva(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO);
				

			if (posEnBotonera(posClickX,posClickY)){
				//es de la botonera
				botonera->handleEventBotonera(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(posClickX - X_BOTONERA_LOGICO),  EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(posClickY - Y_BOTONERA_LOGICO),  evento.button.type);
			}

			//puede que me haya devuelto la figura en aire
			figuraEnAire = botonera->obtenerFiguraActual();
			if (figuraEnAire){
				estaActiva = true;
				//innecesario pero por si acaso
				figuraEnAire->getDimension()->setX(posClickX);
				figuraEnAire->getDimension()->setY(posClickY);
			}
			if (posEnComandos(posClickX,posClickY))
				//es de comandos
				if (evento.button.state == SDL_BUTTON_LMASK){
					comandos->click(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(posClickX - X_COMANDOS_LOGICO), EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(posClickY - Y_COMANDOS_LOGICO), this);
				}
// y borrar esto cuando la botonera funcione
// y en realidad ni me va a imprtar que este activa o no
			if (figuraEnAire)
				if (figuraEnAire->esMiPosicion(posClickX,posClickY))
					estaActiva = true;

			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			clickPressed=false;
			posClickX = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(evento.button.x);
			posClickY = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(evento.button.y);

			//O se suelta la figura agarrada por terreno
			terreno->soltarFigura();

			//Es siempre para la botonera, hasta que no se deja de clickear sigue scrolleando
			botonera->handleEventBotonera(posClickX - X_BOTONERA_LOGICO,  posClickY - Y_BOTONERA_LOGICO,  evento.button.type);

			if (figuraEnAire){
				//o es de figura viva
				soltarFiguraEnAire();
			}

			comandos->release(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(posClickX - X_COMANDOS_LOGICO), EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(posClickY - Y_COMANDOS_LOGICO),&aux,this);


			break;
		}
		case SDL_MOUSEWHEEL:
		{
			//scroll de botonera SIEMPRE sin importar la posicion
			if (evento.wheel.y > 0){	
				if(clickPressed){
					if(figuraEnAire) figuraEnAire->agrandar();
					else terreno->agrandarFigura();
				}else{
					this->botonera->ScrollUp();
				}
			}else if (evento.wheel.y < 0){
				if(clickPressed){
					if(figuraEnAire) figuraEnAire->achicar();
					else terreno->achicarFigura();
				}else{
					this->botonera->ScrollDown();
				}
			}
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
return aux;
}


void Juego::quit(){
	maq->salir();
}

void Juego::play(){
	maq->play(this->terreno);
}

void Juego::actuarVentana(Ventana* ventana,Superficie** sup,Uint32 IDventana,SDL_WindowEvent evento){

	switch (evento.event){
		case SDL_WINDOWEVENT_CLOSE:
		{
			//if (evento.windowID == ventana->getID())
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

			if (figuraEnAire)
				soltarFiguraEnAire();

			break;
		}
		case SDL_WINDOWEVENT_RESIZED:
		{
			double anchoActual= evento.data1;
			double altoActual= evento.data2;

			if(anchoActual != altoActual){
				if(anchoActual<altoActual){
					altoActual = anchoActual;
				}else{
					anchoActual = altoActual;
				}
				ventana->resize(anchoActual,altoActual);
			}
			EscalasDeEjes::getInstance()->setEscalaX(UNIDADES_LOGICAS_TOTAL/anchoActual);
			EscalasDeEjes::getInstance()->setEscalaY(UNIDADES_LOGICAS_TOTAL/altoActual);
			//obtengo superficie resizeada para el juego, esta es la grande donde se pegan las otras.
			delete (*sup);
			(*sup) = new Superficie(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(ANCHO_PANTALLA_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(ALTO_PANTALLA_LOGICO));

			//Y tambien cambian todas las vistas!!
			resizear();
			break;
		}
	}
}

void Juego::resume(){
	this->setCambio(true);
	resizear();
}

void Juego::resizear(){
	terreno->cambioVistaFiguras();
	terreno->resizear();

	botonera->resizear();
	//necesario moverla para que se ajuste la vista...
	botonera->ScrollDown();

	comandos->resizear();
}

void Juego::setFondo(const char* dir){
	terreno->setFondo(dir);
}

bool Juego::posEnTerreno(double posX,double posY){

	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX =  X_TERRENO_LOGICO ;
	finalLogicoX = ANCHO_TERRENO_LOGICO + X_TERRENO_LOGICO;
	ppioLogicoY = Y_TERRENO_LOGICO;
	finalLogicoY = ALTO_TERRENO_LOGICO + Y_TERRENO_LOGICO;

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}

bool Juego::posEnBotonera(double posX,double posY){

	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX =  X_BOTONERA_LOGICO ;
	finalLogicoX = ANCHO_BOTONERA_LOGICO + X_BOTONERA_LOGICO;
	ppioLogicoY = Y_BOTONERA_LOGICO;
	finalLogicoY = ALTO_BOTONERA_LOGICO + Y_BOTONERA_LOGICO;

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}

bool Juego::posEnComandos(double posX,double posY){
	
	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX =  X_COMANDOS_LOGICO;
	finalLogicoX = ANCHO_COMANDOS_LOGICO + X_COMANDOS_LOGICO;
	ppioLogicoY = Y_COMANDOS_LOGICO;
	finalLogicoY = ALTO_COMANDOS_LOGICO + Y_COMANDOS_LOGICO;

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}

void Juego::confirmarPosicionFiguraEnAire(){

	if (figEnEspacioIntermedio()){
		setCambio(true);
		terreno->setCambio(true);
		botonera->setCambio(true);
		comandos->setCambio(true);
	}
	else
		if (figEnBotonera())
			botonera->setCambio(true);
		else
			if (figEnTerreno())
				terreno->setCambio(true);
			else
				if (figEnComandos())
					comandos->setCambio(true);

}

bool Juego::figEnEspacioIntermedio(){

	//intersecar figura en aire con los 12 segmentos en cuestion
	//si cruza cualquiera de los bordes asumo que toca el espacio de separacion
	//no es necesariamente cierto, puede tener un borde coincidente y estar incluido en una de las 3 areas y si alguien
	//tiene ganas de chequear eso hagalo.

	//obviamente tambien asumo que no puede estar por completo en la separacion.
if( figuraEnAire->intersecaCon(X_TERRENO_LOGICO, Y_TERRENO_LOGICO, X_TERRENO_LOGICO + ANCHO_TERRENO_LOGICO, Y_TERRENO_LOGICO) ||
	figuraEnAire->intersecaCon(X_TERRENO_LOGICO + ANCHO_TERRENO_LOGICO, Y_TERRENO_LOGICO, X_TERRENO_LOGICO + ANCHO_TERRENO_LOGICO, Y_TERRENO_LOGICO + ALTO_TERRENO_LOGICO) ||
	figuraEnAire->intersecaCon(X_TERRENO_LOGICO, Y_TERRENO_LOGICO, X_TERRENO_LOGICO, Y_TERRENO_LOGICO + ALTO_TERRENO_LOGICO) ||
	figuraEnAire->intersecaCon(X_TERRENO_LOGICO, Y_TERRENO_LOGICO + ALTO_TERRENO_LOGICO, X_TERRENO_LOGICO + ANCHO_TERRENO_LOGICO, Y_TERRENO_LOGICO + ALTO_TERRENO_LOGICO) ||

	figuraEnAire->intersecaCon(X_BOTONERA_LOGICO, Y_BOTONERA_LOGICO, X_BOTONERA_LOGICO + ANCHO_BOTONERA_LOGICO, Y_BOTONERA_LOGICO) ||
	figuraEnAire->intersecaCon(X_BOTONERA_LOGICO + ANCHO_BOTONERA_LOGICO, Y_BOTONERA_LOGICO, X_BOTONERA_LOGICO + ANCHO_BOTONERA_LOGICO, Y_BOTONERA_LOGICO + ALTO_BOTONERA_LOGICO) ||
	figuraEnAire->intersecaCon(X_BOTONERA_LOGICO, Y_BOTONERA_LOGICO, X_BOTONERA_LOGICO, Y_BOTONERA_LOGICO + ALTO_BOTONERA_LOGICO) ||
	figuraEnAire->intersecaCon(X_BOTONERA_LOGICO, Y_BOTONERA_LOGICO + ALTO_BOTONERA_LOGICO, X_BOTONERA_LOGICO + ANCHO_BOTONERA_LOGICO, Y_BOTONERA_LOGICO + ALTO_BOTONERA_LOGICO) ||

	figuraEnAire->intersecaCon(X_COMANDOS_LOGICO, Y_COMANDOS_LOGICO, X_COMANDOS_LOGICO + ANCHO_COMANDOS_LOGICO, Y_COMANDOS_LOGICO) ||
	figuraEnAire->intersecaCon(X_COMANDOS_LOGICO + ANCHO_COMANDOS_LOGICO, Y_COMANDOS_LOGICO, X_COMANDOS_LOGICO + ANCHO_COMANDOS_LOGICO, Y_COMANDOS_LOGICO + ALTO_COMANDOS_LOGICO) ||
	figuraEnAire->intersecaCon(X_COMANDOS_LOGICO, Y_COMANDOS_LOGICO, X_COMANDOS_LOGICO, Y_COMANDOS_LOGICO + ALTO_COMANDOS_LOGICO) ||
	figuraEnAire->intersecaCon(X_COMANDOS_LOGICO, Y_COMANDOS_LOGICO + ALTO_COMANDOS_LOGICO, X_COMANDOS_LOGICO + ANCHO_COMANDOS_LOGICO, Y_COMANDOS_LOGICO + ALTO_COMANDOS_LOGICO) 
	)
	return true;
else
	return false;
}

//solo se usan si la figura en aire no toco contra ningun borde
//entonces si un punto coincide esta dentro de quien corresponda.
bool Juego::figEnBotonera(){

	if (figuraEnAire->getDimension()->getX()>X_BOTONERA_LOGICO && figuraEnAire->getDimension()->getX()<X_BOTONERA_LOGICO+ANCHO_BOTONERA_LOGICO
		&& figuraEnAire->getDimension()->getY()>Y_BOTONERA_LOGICO && figuraEnAire->getDimension()->getY()<Y_BOTONERA_LOGICO+ALTO_BOTONERA_LOGICO )
		return true;
	
	return false;
}

bool Juego::figEnTerreno(){

	if (figuraEnAire->getDimension()->getX()>X_TERRENO_LOGICO && figuraEnAire->getDimension()->getX()<X_TERRENO_LOGICO+ANCHO_TERRENO_LOGICO
		&& figuraEnAire->getDimension()->getY()>Y_TERRENO_LOGICO && figuraEnAire->getDimension()->getY()<Y_TERRENO_LOGICO+ALTO_TERRENO_LOGICO )
		return true;
	
	return false;
}

bool Juego::figEnComandos(){

	if (figuraEnAire->getDimension()->getX()>X_COMANDOS_LOGICO && figuraEnAire->getDimension()->getX()<X_COMANDOS_LOGICO+ANCHO_COMANDOS_LOGICO
		&& figuraEnAire->getDimension()->getY()>Y_COMANDOS_LOGICO && figuraEnAire->getDimension()->getY()<Y_COMANDOS_LOGICO+ALTO_COMANDOS_LOGICO )
		return true;
	
	return false;
}

void Juego::soltarFiguraEnAire(){
//cambiar cuando ande la interseccion con un circulo
//	confirmarPosicionFiguraEnAire(); //descomentar
	//borrar
	setCambio(true);
	terreno->setCambio(true);
	botonera->setCambio(true);
	comandos->setCambio(true);
	//borrar

	if (posEnTerreno(figuraEnAire->getDimension()->getX(),figuraEnAire->getDimension()->getY())){
		//relativizar posiciones al terreno!
		figuraEnAire->cambiarPosicion(-X_TERRENO_LOGICO,-Y_TERRENO_LOGICO);
		terreno->agregarFigura( figuraEnAire );
		figuraEnAire = NULL;
	}else{

		botonera->restaurarInstanciaActual();

		delete figuraEnAire;
		figuraEnAire = NULL;
	}

}