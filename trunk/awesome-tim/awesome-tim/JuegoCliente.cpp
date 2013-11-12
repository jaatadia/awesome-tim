#include "JuegoCliente.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"
#include "CargadorYaml.h"
#include "GeneradorYaml.h"
#include "Figura.h"
#include "Linea.h"
#include <vector>


JuegoCliente::JuegoCliente(int numCliente,MaquinaEstados* maq){
	
	this->numCliente = numCliente;
	posVector = LARGO/5 * (numCliente);
	for(int i = 0;i<LARGO;i++){
		vector[i] = NULL;
	}

	this->maq = maq;
	this->fileIn = fileIn;
	this->fileOut = fileOut;
	terreno = new TerrenoCliente(ANCHO_TERRENO,ALTO_TERRENO,false);
	botonera = new BotoneraControllerCliente(ANCHO_BOTONERA,ALTO_BOTONERA, 4);
	comandos = new ComandosCliente(ANCHO_COMANDOS,ALTO_COMANDOS);
	figuraEnAire=NULL;
	figuraEnAire2=NULL;
	figuraEnAire3=NULL;
	figuraEnAire4=NULL;
	
	cargar();

	this->setCambio(true);

	shiftPressed = false;
	estaActiva = false;
	clickPressed = false;
	contEventosMov = 0;

	Sonidos::playMusic(MUSIC);

}

bool JuegoCliente::cargar(){
	return true;
}

bool JuegoCliente::guardar(){
	return true;
}

JuegoCliente::~JuegoCliente(){

	delete terreno;
	delete botonera;
	delete comandos;
	delete EscalasDeEjes::getInstance();
	Contenedor::deleteContenedor();
	if(figuraEnAire!=NULL)delete figuraEnAire;
}


//dibuja en pantalla

bool JuegoCliente:: onRender(Superficie* superficie){

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
	if(figuraEnAire2){
		figuraEnAire2->dibujar(superficie);
		dibujar = true;
	}
	if(figuraEnAire3){
		figuraEnAire3->dibujar(superficie);
		dibujar = true;
	}
	if(figuraEnAire4){
		figuraEnAire4->dibujar(superficie);
		dibujar = true;
	}

	return dibujar;
}
	
void JuegoCliente:: onLoop(){
	terreno->actualizarModelo(vector);
}

//manejo de eventos
bool JuegoCliente:: onEvent(Ventana* ventana,Superficie** sup){

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

			if (evento.key.keysym.sym == SDLK_TAB){
				if(clickPressed){
					if(figuraEnAire) figuraEnAire->shift();
					else terreno->shiftFigura();
				}
			}	

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
//			if(clickPressed){
				if(charIngresado == '+'){
					if(figuraEnAire) figuraEnAire->agrandar();
					else terreno->agrandarFigura();
				}else if(charIngresado == '-'){
					if(figuraEnAire) figuraEnAire->achicar();
					else terreno->achicarFigura();
//				}
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

			MouseMotionMessage * msg = new MouseMotionMessage();
			msg->setX(evento.motion.x);
			msg->setY(evento.motion.y);
			msg->setEstado(evento.motion.state);
			this->maq->pushMessage(msg);

			if (terreno->adentroZonaTerreno(posClickX,posClickY))
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
					//como ver si se superpone tarda demasiado lo hago solo cada 5 movimientos!
					
					//para saber si choca con las de terreno tengo que relativizar su posicion!
					figuraEnAire->cambiarPosicion(-X_TERRENO_LOGICO,-Y_TERRENO_LOGICO);

					if (contEventosMov % ITER_CHOQUE == 0){
						//si choca es superpuesta
						//para que no choque con las de terreno que sobrepasan el canvas
						if (terreno->adentroZonaTerreno(figuraEnAire->getDimension()->getX(),figuraEnAire->getDimension()->getY())){
							figuraEnAire->setSuperpuesta( terreno->posicionOcupada(figuraEnAire) );
						}else{
							figuraEnAire->setSuperpuesta( false );
						}
					}
					//y vuelvo para atras
					figuraEnAire->cambiarPosicion(X_TERRENO_LOGICO,Y_TERRENO_LOGICO);
				}
						
			//chequeo la posicion del mouse por si hay perdida de foco del terreno
			if (!terreno->adentroZonaTerreno(posClickX,posClickY))
				terreno->soltarFigura();

			contEventosMov++;

			if (contEventosMov > 10000){
				contEventosMov = 0;
			}

			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if(figuraEnAire){
				set2Click();
				break;
			}
			clickPressed = true;
			posClickX = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(evento.button.x);
			posClickY = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(evento.button.y);

			if (terreno->adentroZonaTerreno(posClickX,posClickY))
				//es del terreno
				if ((evento.button.state == SDL_BUTTON_LMASK) && (shiftPressed)){
					//al borrar algo restauro su contador de instancias
					std::vector<int> tipoFig = terreno->borrarFigura(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO);
					botonera->restaurarInstancias(tipoFig);
				}
				else
					terreno->buscarActiva(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO);
				

			if (posEnBotonera(posClickX,posClickY)){
				//es de la botonera
				botonera->handleEventBotonera(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(posClickX - X_BOTONERA_LOGICO),  EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(posClickY - Y_BOTONERA_LOGICO),  evento.button.type);
			}

			//puede que me haya devuelto la figura en aire
			figuraEnAire = botonera->obtenerFiguraActual();
			if (figuraEnAire){
				
				while(vector[posVector]!=NULL){
					posVector++;
					if (posVector == LARGO/5*(numCliente+1)){
						posVector = LARGO/5*(numCliente);
					}
				}
				figuraEnAire->numero = posVector;
				vector[posVector] = figuraEnAire;
				//enviarMensaje(figuraEnAire,"Se creo una desde la botonera!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
				MaquinaEstados::putMensaje(-1,figuraEnAire->numero,0,0);

				estaActiva = true;
				//innecesario pero por si acaso
				figuraEnAire->setX(posClickX);
				figuraEnAire->setY(posClickY);
			}
			if (posEnComandos(posClickX,posClickY))
				//es de comandos
				if (evento.button.state == SDL_BUTTON_LMASK){
					comandos->click(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(posClickX - X_COMANDOS_LOGICO), EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(posClickY - Y_COMANDOS_LOGICO), this);
				}

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
				if(!(figuraEnAire->getTipoFigura()==LINEA)&& !(figuraEnAire->getTipoFigura()==SOGA)){
					soltarFiguraEnAire();
				}
			}

			comandos->release(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(posClickX - X_COMANDOS_LOGICO), EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(posClickY - Y_COMANDOS_LOGICO),&aux,this);

			break;
		}
		case SDL_MOUSEWHEEL:
		{
			//scroll de botonera SIEMPRE sin importar la posicion
			if (evento.wheel.y > 0){	
				if(clickPressed){
					if(figuraEnAire){
						figuraEnAire->agrandar();
						if (terreno->adentroZonaTerreno(figuraEnAire->getDimension()->getX(),figuraEnAire->getDimension()->getY())){
							figuraEnAire->setSuperpuesta( terreno->posicionOcupada(figuraEnAire) );
						}else{
							figuraEnAire->setSuperpuesta( false );
						}
					}else terreno->agrandarFigura();
				}else{
					this->botonera->ScrollUp();
				}
			}else if (evento.wheel.y < 0){
				if(clickPressed){
					if(figuraEnAire){
						figuraEnAire->achicar();
						if (terreno->adentroZonaTerreno(figuraEnAire->getDimension()->getX(),figuraEnAire->getDimension()->getY())){
							figuraEnAire->setSuperpuesta( terreno->posicionOcupada(figuraEnAire) );
						}else{
							figuraEnAire->setSuperpuesta( false );
						}
					}else terreno->achicarFigura();
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


void JuegoCliente::quit(){
	MaquinaEstados::putMensaje(-1,0,0,0);
	maq->salir();
}

void JuegoCliente::play(){
	MaquinaEstados::putMensaje(-1,0,0,0);
	Sonidos::stopMusic();
	maq->play((void*)this->terreno);
}

void JuegoCliente::actuarVentana(Ventana* ventana,Superficie** sup,Uint32 IDventana,SDL_WindowEvent evento){

	switch (evento.event){
		case SDL_WINDOWEVENT_CLOSE:
		{
			//if (evento.windowID == ventana->getID())
				MaquinaEstados::putMensaje(-1,0,0,0);
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

void JuegoCliente::resume(){
	Sonidos::playMusic(MUSIC);
	this->setCambio(true);
	resizear();
}

void JuegoCliente::resizear(){
	terreno->cambioVistaFiguras();
	terreno->resizear();

	botonera->resizear();
	//necesario moverla para que se ajuste la vista...
	botonera->ScrollDown();

	comandos->resizear();
}

void JuegoCliente::setFondo(const char* dir){
	terreno->setFondo(dir);
}

bool JuegoCliente::posEnTerreno(double posX,double posY){

	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX =  X_TERRENO_LOGICO ;
	finalLogicoX = ANCHO_TERRENO_LOGICO + X_TERRENO_LOGICO;
	ppioLogicoY = Y_TERRENO_LOGICO;
	finalLogicoY = ALTO_TERRENO_LOGICO + Y_TERRENO_LOGICO;

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}

bool JuegoCliente::posEnBotonera(double posX,double posY){

	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX =  X_BOTONERA_LOGICO ;
	finalLogicoX = ANCHO_BOTONERA_LOGICO + X_BOTONERA_LOGICO;
	ppioLogicoY = Y_BOTONERA_LOGICO;
	finalLogicoY = ALTO_BOTONERA_LOGICO + Y_BOTONERA_LOGICO;

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}

bool JuegoCliente::posEnComandos(double posX,double posY){
	
	double ppioLogicoX, finalLogicoX, ppioLogicoY, finalLogicoY;

	ppioLogicoX =  X_COMANDOS_LOGICO;
	finalLogicoX = ANCHO_COMANDOS_LOGICO + X_COMANDOS_LOGICO;
	ppioLogicoY = Y_COMANDOS_LOGICO;
	finalLogicoY = ALTO_COMANDOS_LOGICO + Y_COMANDOS_LOGICO;

	return ((posX > ppioLogicoX) && (posX < finalLogicoX) && (posY > ppioLogicoY) && (posY < finalLogicoY)) ;
}

void JuegoCliente::confirmarPosicionFiguraEnAire(){

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

bool JuegoCliente::figEnEspacioIntermedio(){

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
bool JuegoCliente::figEnBotonera(){

	if (figuraEnAire->getDimension()->getX()>X_BOTONERA_LOGICO && figuraEnAire->getDimension()->getX()<X_BOTONERA_LOGICO+ANCHO_BOTONERA_LOGICO
		&& figuraEnAire->getDimension()->getY()>Y_BOTONERA_LOGICO && figuraEnAire->getDimension()->getY()<Y_BOTONERA_LOGICO+ALTO_BOTONERA_LOGICO )
		return true;
	
	return false;
}

bool JuegoCliente::figEnTerreno(){

	if (figuraEnAire->getDimension()->getX()>X_TERRENO_LOGICO && figuraEnAire->getDimension()->getX()<X_TERRENO_LOGICO+ANCHO_TERRENO_LOGICO
		&& figuraEnAire->getDimension()->getY()>Y_TERRENO_LOGICO && figuraEnAire->getDimension()->getY()<Y_TERRENO_LOGICO+ALTO_TERRENO_LOGICO )
		return true;
	
	return false;
}

bool JuegoCliente::figEnComandos(){

	if (figuraEnAire->getDimension()->getX()>X_COMANDOS_LOGICO && figuraEnAire->getDimension()->getX()<X_COMANDOS_LOGICO+ANCHO_COMANDOS_LOGICO
		&& figuraEnAire->getDimension()->getY()>Y_COMANDOS_LOGICO && figuraEnAire->getDimension()->getY()<Y_COMANDOS_LOGICO+ALTO_COMANDOS_LOGICO )
		return true;
	
	return false;
}




void JuegoCliente::soltarFiguraEnAire(){

	confirmarPosicionFiguraEnAire();

	if (terreno->adentroZonaTerreno(figuraEnAire->getDimension()->getX(),figuraEnAire->getDimension()->getY()) && !figuraEnAire->superpuesta){
		//relativizar posiciones al terreno!
		figuraEnAire->cambiarPosicion(-X_TERRENO_LOGICO,-Y_TERRENO_LOGICO);
		terreno->agregarFigura( figuraEnAire );
		
		MaquinaEstados::putMensaje(-1,figuraEnAire->numero,0,0);
		
		figuraEnAire = NULL;
	}else{

		botonera->restaurarInstanciaActual();
		
		vector[figuraEnAire->numero] = NULL;
		MaquinaEstados::putMensaje(-1,figuraEnAire->numero,0,0);

		delete figuraEnAire;
		figuraEnAire = NULL;
	}
}


void JuegoCliente::set2Click(){
	
	if(figuraEnAire->getTipoFigura()==LINEA){
		
		Linea* linea = ((Linea*)figuraEnAire);
		linea->cambiarPosicion(-X_TERRENO_LOGICO,-Y_TERRENO_LOGICO);
		
		double x = linea->getDimension()->getX();
		double y = linea->getDimension()->getY();

		Figura* result = terreno->getFiguraAtableCorrea(x,y);
		
		if(result==NULL){
			botonera->restaurarInstanciaActual();

			vector[figuraEnAire->numero] = NULL;
			MaquinaEstados::putMensaje(-1,figuraEnAire->numero,0,0);

			delete figuraEnAire;
			figuraEnAire = NULL;
			this->setCambio(true);
			terreno->setCambio(true);
			botonera->setCambio(true);
			comandos->setCambio(true);
		}else{
			result->posAtableCorrea(&x,&y);
			if(!linea->primerPuntoPuesto()){
				linea->setFigura1(result);
				linea->actualizar();

				MaquinaEstados::putMensaje(-1,figuraEnAire->numero,0,0);

			}else{
				if(linea->getFigura1() == result){
					botonera->restaurarInstanciaActual();

					vector[figuraEnAire->numero] = NULL;
					MaquinaEstados::putMensaje(-1,figuraEnAire->numero,0,0);

					delete figuraEnAire;
					figuraEnAire = NULL;
					this->setCambio(true);
					terreno->setCambio(true);
					botonera->setCambio(true);
					comandos->setCambio(true);
				}else{
					linea->setFigura2(result);
					
					MaquinaEstados::putMensaje(-1,figuraEnAire->numero,0,0);
					
					linea->getFigura1()->atarCorrea();
					linea->getFigura2()->atarCorrea();
					terreno->agregarFigura( figuraEnAire );

					MaquinaEstados::putMensaje(-1,figuraEnAire->numero,0,0);

					linea->actualizar();
					figuraEnAire = NULL;
				}
			}
		}
	}else if(figuraEnAire->getTipoFigura()==SOGA){
		
		Linea* linea = ((Linea*)figuraEnAire);
		linea->cambiarPosicion(-X_TERRENO_LOGICO,-Y_TERRENO_LOGICO);
		
		double x = linea->getDimension()->getX();
		double y = linea->getDimension()->getY();

		Figura* result = terreno->getFiguraAtableSoga(x,y);
		
		if(result==NULL){
			botonera->restaurarInstanciaActual();

			vector[figuraEnAire->numero] = NULL;
			MaquinaEstados::putMensaje(-1,figuraEnAire->numero,0,0);

			delete figuraEnAire;
			figuraEnAire = NULL;
			this->setCambio(true);
			terreno->setCambio(true);
			comandos->setCambio(true);
			botonera->setCambio(true);
		}else{
			int res = result->esAtableSoga(x,y);
			if(!linea->primerPuntoPuesto()){
				linea->setFigura1(result);

				MaquinaEstados::putMensaje(-1,figuraEnAire->numero,0,0);

				((Soga*)linea)->setNumsPosAtable(res,0);
				linea->actualizar();
			}else{
				if (result == linea->getFigura1()){
					botonera->restaurarInstanciaActual();			
					
					vector[figuraEnAire->numero] = NULL;
					MaquinaEstados::putMensaje(-1,figuraEnAire->numero,0,0);
					
					delete figuraEnAire;
					figuraEnAire = NULL;
					this->setCambio(true);
					terreno->setCambio(true);
					comandos->setCambio(true);
					botonera->setCambio(true);
				}else{
					linea->setFigura2(result);

					MaquinaEstados::putMensaje(-1,figuraEnAire->numero,0,0);

					((Soga*)linea)->setNumsPosAtable(((Soga*)linea)->num1,res);
					linea->actualizar();
					linea->getFigura1()->atarSoga(((Soga*)linea)->num1);
					linea->getFigura2()->atarSoga(((Soga*)linea)->num2);
					terreno->agregarFigura( figuraEnAire );
	
					MaquinaEstados::putMensaje(-1,figuraEnAire->numero,0,0);

					figuraEnAire = NULL;
				}
			}
		}
	}else{
			botonera->restaurarInstanciaActual();
			vector[figuraEnAire->numero] = NULL;
			MaquinaEstados::putMensaje(-1,figuraEnAire->numero,0,0);
	}
}