#include "Juego.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"
#include "CargadorYaml.h"
#include "GeneradorYaml.h"

#include "Cuadrado.h"
#include "Circulo.h"
#include "PoligonoRegular.h"
#include "Triangulo2.h"

#include "Figura.h"

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

	this->setCambio(true);

	shiftPressed = false;
	estaActiva = false;

/***************Test de arrastra y girar figura*************************/

	Contenedor::putMultimedia("../images/cuadrado.jpg",new Imagen("../images/Cuadrado.png"));
	Figura* fig = new Figura("../images/cuadrado.jpg",new Cuadrado(20,20,50,50,0));
	terreno->agregarFigura(fig);

	Contenedor::putMultimedia("../images/triangulo.png",new Imagen("../images/triangulo.png"));
	fig = new Figura("../images/triangulo.png",new Triangulo2(0,0,0,20,20));
	terreno->agregarFigura(fig);

	Contenedor::putMultimedia("../images/Ptriangulo.png",new Imagen("../images/Ptriangulo.png"));
	fig = new Figura("../images/Ptriangulo.png",new PoligonoRegular(20,20,10,3,0));
	terreno->agregarFigura(fig);

	Contenedor::putMultimedia("../images/Ppentagono.png",new Imagen("../images/Ppentagono.png"));
	fig = new Figura("../images/Ppentagono.png",new PoligonoRegular(20,20,10,5,0));
	terreno->agregarFigura(fig);

	Contenedor::putMultimedia("../images/Circulo.jpg",new Imagen("../images/Circulo.png"));
	fig = new Figura("../images/Circulo.jpg",new Circulo(20,50,50,0));
	terreno->agregarFigura(fig);

/*****************Figura En aire******************************************/

	figuraEnAire = new Figura("../images/Ppentagono.png",new PoligonoRegular(20,20,10,5,0));

}

bool Juego::cargar(){
	//CargadorYaml::cargarJuego(file,botonera,terreno);
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

	if(this->huboCambios()){
		superficie->restore();
		setCambio(false);
	}
	
	if(terreno->huboCambios()){
		superficie->dibujarSupreficie(terreno->getImpresion(escalas),NULL,escalas->getCantidadUnidadesFisicasX(X_TERRENO_LOGICO),escalas->getCantidadUnidadesFisicasY(Y_TERRENO_LOGICO));
	}

	if(botonera->huboCambios()){
		superficie->dibujarSupreficie(botonera->getImpresion(),NULL,escalas->getCantidadUnidadesFisicasX(X_BOTONERA_LOGICO),escalas->getCantidadUnidadesFisicasY(Y_BOTONERA_LOGICO));
	}
	
	//if(comandos->huboCambios()){
		superficie->dibujarSupreficie(comandos->getImpresion(escalas),NULL,escalas->getCantidadUnidadesFisicasX(X_COMANDOS_LOGICO),escalas->getCantidadUnidadesFisicasY(Y_COMANDOS_LOGICO));
	//}

	if (figuraEnAire)
		figuraEnAire->dibujar(superficie,escalas);

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
			if (posEnTerreno(posClickX,posClickY))
				if (evento.motion.state == SDL_BUTTON_LMASK){				
					terreno->arrastrarFigura(posClickX - X_TERRENO_LOGICO, posClickY - Y_TERRENO_LOGICO, cantMovX, cantMovY);
				}else
					if (evento.motion.state == SDL_BUTTON_RMASK){
						terreno->rotarFigura(posClickX - X_TERRENO_LOGICO, posClickY - Y_TERRENO_LOGICO, cantMovX, cantMovY);
					}

			//muevo la figura voladora, si es que la hay
			if (figuraEnAire)
				if ((figuraEnAire->esMiPosicion(posClickX,posClickY)) && (estaActiva)){
						figuraEnAire->cambiarPosicion(cantMovX, cantMovY);
						confirmarPosicionFiguraEnAire();
				}
						
			//chequeo la posicion del mouse por si hay perdida de foco del terreno

			if (!posEnTerreno(posClickX,posClickY))
				terreno->soltarFigura();

			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{

			posClickX = escalas->getCantidadUnidadesLogicasX(evento.button.x);
			posClickY = escalas->getCantidadUnidadesLogicasY(evento.button.y);

			if (posEnTerreno(posClickX,posClickY))
				//es del terreno
				if ((evento.button.state == SDL_BUTTON_LMASK) && (shiftPressed))
					//click izq y shift
					terreno->borrarFigura(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO);
				else
					terreno->buscarActiva(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO);
				

			if (posEnBotonera(posClickX,posClickY)){
				//botonera tiene su manejo propio
				botonera->handleEventBotonera(posClickX - X_BOTONERA_LOGICO,  posClickY - Y_BOTONERA_LOGICO,  evento.button.type);
			}

			//puede que me haya devuelto la figura en aire
			//DESCOMENTAR CUANDO FUNCIONE
/*			figuraEnAire = botonera->obtenerFiguraActual();
			if (figuraEnAire)
				estaActiva = true;
*/
			if (posEnComandos(posClickX,posClickY))
				//es de comandos
				if (evento.button.state == SDL_BUTTON_LMASK){
					comandos->click(escalas->getCantidadUnidadesFisicasX(posClickX - X_COMANDOS_LOGICO), escalas->getCantidadUnidadesFisicasY(posClickY - Y_COMANDOS_LOGICO), this);
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
			posClickX = escalas->getCantidadUnidadesLogicasX(evento.button.x);
			posClickY = escalas->getCantidadUnidadesLogicasY(evento.button.y);

			//O se suelta la figura agarrada por terreno
			terreno->soltarFigura();

			//Es siempre para la botonera, hasta que no se deja de clickear sigue scrolleando
			botonera->handleEventBotonera(posClickX - X_BOTONERA_LOGICO,  posClickY - Y_BOTONERA_LOGICO,  evento.button.type);

			if (figuraEnAire){
				//o es de figura viva
				soltarFiguraEnAire();
			}


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

			if (figuraEnAire)
				soltarFiguraEnAire();

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
			terreno->cambioVistaFiguras();
			terreno->resizear(escalas);

			//incluyendo a la del aire!!
			//en realidad es innecesario, sacar cuando ande botonera!
			if (figuraEnAire)
				figuraEnAire->setCambio(true);

			botonera->setCambio(true);
			//no se si es necesario algo similar para botonera

			comandos->resizear(escalas);

			break;
		}
	}
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

	confirmarPosicionFiguraEnAire();

	if (posEnTerreno(figuraEnAire->getDimension()->getX(),figuraEnAire->getDimension()->getY())){
		//relativizar posiciones al terreno!
		figuraEnAire->cambiarPosicion(-X_TERRENO_LOGICO,-Y_TERRENO_LOGICO);
		terreno->agregarFigura( figuraEnAire );
		figuraEnAire = NULL;
	}else{
		delete figuraEnAire;
		figuraEnAire = NULL;
	}

}