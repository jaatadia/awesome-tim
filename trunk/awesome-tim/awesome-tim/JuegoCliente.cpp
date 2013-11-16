#include "JuegoCliente.h"
#include "ErrorLogHandler.h"
#include "Constantes.h"
#include "CargadorYaml.h"
#include "GeneradorYaml.h"
#include "Figura.h"
#include "Linea.h"
#include <vector>
#include "FactoryFiguras.h"
#include "TransformFigureMessage.h"
#include "ClientMessage.h"
#include "SetAreaMessage.h"
#include "CreateButtonMessage.h"

//Definicion de constantes que no se que son: Jenny :P
#define MSG_SUBTYPE_MOVEMENT 0
#define MSG_SUBTYPE_SETANGLE 1
#define MSG_SUBTYPE_CREATE 2
#define MSG_SUBTYPE_DELETE 3
#define MSG_SUBTYPE_SHIFT 4
#define MSG_SUBTYPE_STRETCH 5

JuegoCliente::JuegoCliente(int numCliente,MaquinaEstados* maq){
	
	this->numCliente = numCliente;
	posVector = LARGO/5 * (numCliente);
	for(int i = 0;i<LARGO;i++){
		vector[i] = NULL;
	}

	this->maq = maq;
	this->fileIn = fileIn;
	this->fileOut = fileOut;
	
	std::string objetivo = NULL;

	terreno = new TerrenoCliente(ANCHO_TERRENO,ALTO_TERRENO,maq,numCliente,false);
	botonera = new BotoneraControllerCliente(ANCHO_BOTONERA,ALTO_BOTONERA, 4);
	comandos = new ComandosCliente(ANCHO_COMANDOS,ALTO_COMANDOS,NULL);

	for (int i = 0;i<=MAX_CLIENTES;i++){
		figurasEnAire[i]=NULL;
	}
	
	cargar();

	this->setCambio(true);

	shiftPressed = false;
	estaActiva = false;
	clickPressed = false;
	contEventosMov = 0;

	Sonidos::playMusic(MUSIC);

}

bool JuegoCliente::cargar(){
	//if(botonera->estaVacia()){
	//	botonera->agregarBotonesDefault();
	//	this->resume();
	//}
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
	for(int i=0;i<=MAX_CLIENTES;i++){
		if(figurasEnAire[i]!=NULL)delete figurasEnAire[i];
	}
	
}


//dibuja en pantalla

bool JuegoCliente:: onRender(Superficie* superficie){

	bool dibujar = false;
	
	confirmarPosicionFiguraEnAire();
	
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

	for(int i = 0;i<=MAX_CLIENTES;i++){
		if(figurasEnAire[i]){
			figurasEnAire[i]->dibujar(superficie);
			dibujar = true;
		}
	}

	return dibujar;
}
	
void JuegoCliente:: onLoop(){
	bool continuar = true;
	Message * msg = this->maq->getProcessMessage();
	while((continuar)&&(msg!=NULL)){
		switch (msg->getType()){
			case MSG_TYPE_CLIENT_MESSAGE:
				{
					ClientMessage* c_msg = (ClientMessage*)  msg;
					switch(c_msg->getAction()){
						case A_READY:
							{
								continuar = false;
								this->play();
							}
							break;
					}
				}
				break;
			case MSG_TYPE_CREATE_FIGURE:
				{
					Figura* fig = FactoryFiguras::create((CreateFigureMessage*)msg);
					if(fig!=NULL){
						vector[fig->numero] = fig;
						if (((CreateFigureMessage*)msg)->isInAir()){
							figurasEnAire[((CreateFigureMessage*)msg)->getId()] = fig;
						}else{
							terreno->agregarFigura(fig);
						}
					}
				}
				break;
			case MSG_TYPE_CREATE_BUTTON:
				{
					Figura* fig = FactoryFiguras::create((CreateFigureMessage*)msg);
					if(fig!=NULL){
						this->botonera->agregarBoton(fig,((CreateFigureMessage*)msg)->getData2());
						this->botonera->ScrollUp();
					}
				}
				break;
			case MSG_TYPE_SET_AREA:
				{
					SetAreaMessage* a_msg = (SetAreaMessage*)msg;
					double x1,y1,x2,y2;
					a_msg->getPuntos(&x1,&y1,&x2,&y2);
					this->terreno->setMiPorcion(x1,y1,x2,y2);
				}
				break;
			case MSG_TYPE_TRANSFORM_FIGURE:
				{
					TransformFigureMessage* t_msg = (TransformFigureMessage*) msg;
					Figura* fig = vector[t_msg->getFigureID()];
					if(fig!=NULL){
						switch(t_msg->getSizeChange()){
							case T_RESTORE:
								fig->setLargo(t_msg->getLength());
							case T_ROTATE:
								fig->setAngulo(t_msg->getAngle());
								fig->setX(t_msg->getX());
								fig->setY(t_msg->getY());
								if(figurasEnAire[t_msg->getClientID()]==NULL) terreno->setCambio(true);
								break;
							case T_SHIFT:
								fig->shift();
								fig->setAngulo(t_msg->getAngle());
								fig->setX(t_msg->getX());
								fig->setY(t_msg->getY());
								if(figurasEnAire[t_msg->getClientID()]==NULL) terreno->setCambio(true);
								break;
							case T_SHRINK:
								fig->achicar();
								fig->setX(t_msg->getX());
								fig->setY(t_msg->getY());
								if(figurasEnAire[t_msg->getClientID()]==NULL) terreno->setCambio(true);
								break;
							case T_GROW:
								fig->agrandar();
								fig->setX(t_msg->getX());
								fig->setY(t_msg->getY());
								if(figurasEnAire[t_msg->getClientID()]==NULL) terreno->setCambio(true);
								break;
							case T_NONE:
								fig->setX(t_msg->getX());
								fig->setY(t_msg->getY());
								if(figurasEnAire[t_msg->getClientID()]==NULL) terreno->setCambio(true);
								break;
							case T_DROP:
								figurasEnAire[t_msg->getClientID()] = NULL;
								terreno->agregarFigura(fig);
								fig->setX(t_msg->getX());
								fig->setY(t_msg->getY());
								break;
							case T_DROPDEAD:
								figurasEnAire[t_msg->getClientID()] = NULL;
								vector[t_msg->getFigureID()] = NULL;
								delete fig;
								break;
							case T_REMOVE:
								fig->desUnir();
								vector[t_msg->getFigureID()] = NULL;
								terreno->eliminarFigura(fig);
								terreno->setCambio(true);
								delete fig;
								break;
						}
					}
				}
				break;
		}
		delete msg;
		if(continuar){
			msg = this->maq->getProcessMessage();
		}

	}

	terreno->actualizarModelo(vector);
}

//manejo de eventos
bool JuegoCliente:: onEvent(Ventana* ventana,Superficie** sup){

SDL_Event evento;
double posClickX, posClickY;
bool aux = false;

std::list<Figura*> figurasAMover;

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
					if(figurasEnAire[this->numCliente]) figurasEnAire[this->numCliente]->shift();
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
					if(figurasEnAire[this->numCliente]) figurasEnAire[this->numCliente]->agrandar();
					else terreno->agrandarFigura();
				}else if(charIngresado == '-'){
					if(figurasEnAire[this->numCliente]) figurasEnAire[this->numCliente]->achicar();
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

			if (terreno->adentroZonaTerreno(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO))
				if (evento.motion.state == SDL_BUTTON_LMASK){
					terreno->arrastrarFigura(posClickX - X_TERRENO_LOGICO, posClickY - Y_TERRENO_LOGICO, cantMovX, cantMovY,&figurasAMover);
				}else
					if (evento.motion.state == SDL_BUTTON_RMASK){
						terreno->rotarFigura(posClickX - X_TERRENO_LOGICO, posClickY - Y_TERRENO_LOGICO, cantMovX, cantMovY);
					}

			//muevo la figura voladora, si es que la hay
			if (figurasEnAire[this->numCliente])
				if ((estaActiva)){
					confirmarPosicionFiguraEnAire();
					figurasEnAire[this->numCliente]->cambiarPosicion(cantMovX, cantMovY);
					//como ver si se superpone tarda demasiado lo hago solo cada 5 movimientos!
					
					//para saber si choca con las de terreno tengo que relativizar su posicion!
					figurasEnAire[this->numCliente]->cambiarPosicion(-X_TERRENO_LOGICO,-Y_TERRENO_LOGICO);

					if (contEventosMov % ITER_CHOQUE == 0){
						//si choca es superpuesta
						//para que no choque con las de terreno que sobrepasan el canvas
						if (terreno->adentroZonaTerreno(figurasEnAire[this->numCliente]->getDimension()->getX() - X_TERRENO_LOGICO, figurasEnAire[this->numCliente]->getDimension()->getY() - Y_TERRENO_LOGICO)){
							figurasEnAire[this->numCliente]->setSuperpuesta( terreno->posicionOcupada(figurasEnAire[this->numCliente]) );
						}else{
							figurasEnAire[this->numCliente]->setSuperpuesta( false );
						}
					}
					//y vuelvo para atras
					figurasEnAire[this->numCliente]->cambiarPosicion(X_TERRENO_LOGICO,Y_TERRENO_LOGICO);

					figurasAMover.push_back(figurasEnAire[this->numCliente]);

				}
						
			//chequeo la posicion del mouse por si hay perdida de foco del terreno
			if (!terreno->adentroZonaTerreno(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO))
				terreno->soltarFigura();

			contEventosMov++;

			if (contEventosMov > 10000){
				contEventosMov = 0;
			}

			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if(figurasEnAire[this->numCliente]){
				set2Click();
				break;
			}
			clickPressed = true;
			posClickX = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(evento.button.x);
			posClickY = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(evento.button.y);

			if (terreno->adentroZonaTerreno(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO))
				//es del terreno
				if ((evento.button.state == SDL_BUTTON_LMASK) && (shiftPressed)){
					//al borrar algo restauro su contador de instancias
					std::vector<int> tipoFig = terreno->borrarFigura(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO,vector);
					botonera->restaurarInstancias(tipoFig);
				}
				else
					terreno->buscarActiva(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO);
				

			if (posEnBotonera(posClickX,posClickY)){
				//es de la botonera
				botonera->handleEventBotonera(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(posClickX - X_BOTONERA_LOGICO),  EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(posClickY - Y_BOTONERA_LOGICO),  evento.button.type);
			}

			//puede que me haya devuelto la figura en aire
			figurasEnAire[this->numCliente] = botonera->obtenerFiguraActual();
			if (figurasEnAire[this->numCliente]){
				estaActiva = true;
				//innecesario pero por si acaso
				figurasEnAire[this->numCliente]->setX(posClickX);
				figurasEnAire[this->numCliente]->setY(posClickY);
				
				while(vector[posVector]!=NULL){
					posVector++;
					if (posVector == LARGO/5*(numCliente+1)){
						posVector = LARGO/5*(numCliente);
					}
				}
				figurasEnAire[this->numCliente]->numero = posVector;
				vector[posVector] = figurasEnAire[this->numCliente];
					CreateFigureMessage * msg = new CreateFigureMessage();
					msg->setId(this->maq->getId());
					msg->setFigureType(figurasEnAire[this->numCliente]->getTipoFigura());
					msg->setFigureID(figurasEnAire[this->numCliente]->numero);
					msg->setX(figurasEnAire[this->numCliente]->getDimension()->getX());
					msg->setY(figurasEnAire[this->numCliente]->getDimension()->getY());
					msg->setAngle(figurasEnAire[this->numCliente]->getDimension()->getAngulo());
					msg->setInAir(true);
					double d1,d2;
					figurasEnAire[this->numCliente]->getExtraData(&d1,&d2);
					msg->setData1(d1);
					msg->setData2(d2);

				this->maq->pushSendMessage(msg,numCliente);
				std::cout<<maq->getId()<<"|"<<numCliente<<"\n";
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

			if (figurasEnAire[this->numCliente]){
				//o es de figura viva
				if(!(figurasEnAire[this->numCliente]->getTipoFigura()==LINEA)&& !(figurasEnAire[this->numCliente]->getTipoFigura()==SOGA)){
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
					if(figurasEnAire[this->numCliente]){
						figurasEnAire[this->numCliente]->agrandar();
						if (terreno->adentroZonaTerreno(figurasEnAire[this->numCliente]->getDimension()->getX() - X_TERRENO_LOGICO,figurasEnAire[this->numCliente]->getDimension()->getY() - Y_TERRENO_LOGICO)){
							figurasEnAire[this->numCliente]->setSuperpuesta( terreno->posicionOcupada(figurasEnAire[this->numCliente]) );
						}else{
							figurasEnAire[this->numCliente]->setSuperpuesta( false );
						}
					}else terreno->agrandarFigura();
				}else{
					this->botonera->ScrollUp();
				}
			}else if (evento.wheel.y < 0){
				if(clickPressed){
					if(figurasEnAire[this->numCliente]){
						figurasEnAire[this->numCliente]->achicar();
						if (terreno->adentroZonaTerreno(figurasEnAire[this->numCliente]->getDimension()->getX() - X_TERRENO_LOGICO,figurasEnAire[this->numCliente]->getDimension()->getY() - Y_TERRENO_LOGICO)){
							figurasEnAire[this->numCliente]->setSuperpuesta( terreno->posicionOcupada(figurasEnAire[this->numCliente]) );
						}else{
							figurasEnAire[this->numCliente]->setSuperpuesta( false );
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

	figurasAMover.unique();
	for(std::list<Figura*>::iterator iter = figurasAMover.begin();iter!=figurasAMover.end();iter++){
		TransformFigureMessage* t_msg = new TransformFigureMessage();
		t_msg->setClientID(this->numCliente);
		t_msg->setFigureID((*iter)->numero);
		t_msg->setX((*iter)->getDimension()->getX());
		t_msg->setY((*iter)->getDimension()->getY());
		t_msg->setSizeChange(T_NONE);
		this->maq->pushSendMessage(t_msg,numCliente);
	}


return aux;
}


void JuegoCliente::quit(){
	maq->salir();
}

void JuegoCliente::play(){
	Sonidos::stopMusic();
	maq->play((void*)this->terreno);
}

void JuegoCliente::sendReady(){
	ClientMessage* c_msg = new ClientMessage();
	c_msg->setClientID(this->numCliente);
	c_msg->setAction(A_READY);
	this->maq->pushSendMessage(c_msg);
}

void JuegoCliente::sendUnready(){
	ClientMessage* c_msg = new ClientMessage();
	c_msg->setClientID(this->numCliente);
	c_msg->setAction(A_UNREADY);
	this->maq->pushSendMessage(c_msg);
}

void JuegoCliente::actuarVentana(Ventana* ventana,Superficie** sup,Uint32 IDventana,SDL_WindowEvent evento){

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

			if (figurasEnAire[this->numCliente])
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
	}else{
		if (figEnBotonera())
			botonera->setCambio(true);
		if (figEnTerreno())
			terreno->setCambio(true);
		if (figEnComandos())
			comandos->setCambio(true);
	}

}

bool JuegoCliente::figEnEspacioIntermedio(){

	//intersecar figura en aire con los 12 segmentos en cuestion
	//si cruza cualquiera de los bordes asumo que toca el espacio de separacion
	//no es necesariamente cierto, puede tener un borde coincidente y estar incluido en una de las 3 areas y si alguien
	//tiene ganas de chequear eso hagalo.

	//obviamente tambien asumo que no puede estar por completo en la separacion.
	for(int i = 0;i<=MAX_CLIENTES;i++){
		if( figurasEnAire[i] ==NULL) continue;
		if( figurasEnAire[i]->intersecaCon(X_TERRENO_LOGICO, Y_TERRENO_LOGICO, X_TERRENO_LOGICO + ANCHO_TERRENO_LOGICO, Y_TERRENO_LOGICO) ||
			figurasEnAire[i]->intersecaCon(X_TERRENO_LOGICO + ANCHO_TERRENO_LOGICO, Y_TERRENO_LOGICO, X_TERRENO_LOGICO + ANCHO_TERRENO_LOGICO, Y_TERRENO_LOGICO + ALTO_TERRENO_LOGICO) ||
			figurasEnAire[i]->intersecaCon(X_TERRENO_LOGICO, Y_TERRENO_LOGICO, X_TERRENO_LOGICO, Y_TERRENO_LOGICO + ALTO_TERRENO_LOGICO) ||
			figurasEnAire[i]->intersecaCon(X_TERRENO_LOGICO, Y_TERRENO_LOGICO + ALTO_TERRENO_LOGICO, X_TERRENO_LOGICO + ANCHO_TERRENO_LOGICO, Y_TERRENO_LOGICO + ALTO_TERRENO_LOGICO) ||

			figurasEnAire[i]->intersecaCon(X_BOTONERA_LOGICO, Y_BOTONERA_LOGICO, X_BOTONERA_LOGICO + ANCHO_BOTONERA_LOGICO, Y_BOTONERA_LOGICO) ||
			figurasEnAire[i]->intersecaCon(X_BOTONERA_LOGICO + ANCHO_BOTONERA_LOGICO, Y_BOTONERA_LOGICO, X_BOTONERA_LOGICO + ANCHO_BOTONERA_LOGICO, Y_BOTONERA_LOGICO + ALTO_BOTONERA_LOGICO) ||
			figurasEnAire[i]->intersecaCon(X_BOTONERA_LOGICO, Y_BOTONERA_LOGICO, X_BOTONERA_LOGICO, Y_BOTONERA_LOGICO + ALTO_BOTONERA_LOGICO) ||
			figurasEnAire[i]->intersecaCon(X_BOTONERA_LOGICO, Y_BOTONERA_LOGICO + ALTO_BOTONERA_LOGICO, X_BOTONERA_LOGICO + ANCHO_BOTONERA_LOGICO, Y_BOTONERA_LOGICO + ALTO_BOTONERA_LOGICO) ||

			figurasEnAire[i]->intersecaCon(X_COMANDOS_LOGICO, Y_COMANDOS_LOGICO, X_COMANDOS_LOGICO + ANCHO_COMANDOS_LOGICO, Y_COMANDOS_LOGICO) ||
			figurasEnAire[i]->intersecaCon(X_COMANDOS_LOGICO + ANCHO_COMANDOS_LOGICO, Y_COMANDOS_LOGICO, X_COMANDOS_LOGICO + ANCHO_COMANDOS_LOGICO, Y_COMANDOS_LOGICO + ALTO_COMANDOS_LOGICO) ||
			figurasEnAire[i]->intersecaCon(X_COMANDOS_LOGICO, Y_COMANDOS_LOGICO, X_COMANDOS_LOGICO, Y_COMANDOS_LOGICO + ALTO_COMANDOS_LOGICO) ||
			figurasEnAire[i]->intersecaCon(X_COMANDOS_LOGICO, Y_COMANDOS_LOGICO + ALTO_COMANDOS_LOGICO, X_COMANDOS_LOGICO + ANCHO_COMANDOS_LOGICO, Y_COMANDOS_LOGICO + ALTO_COMANDOS_LOGICO) 
			)
			return true;
	}
	return false;
}

//solo se usan si la figura en aire no toco contra ningun borde
//entonces si un punto coincide esta dentro de quien corresponda.
bool JuegoCliente::figEnBotonera(){

	for(int i = 0;i<=MAX_CLIENTES;i++){
		if( figurasEnAire[i] ==NULL) continue;
		if (figurasEnAire[i]->getDimension()->getX()>X_BOTONERA_LOGICO && figurasEnAire[i]->getDimension()->getX()<X_BOTONERA_LOGICO+ANCHO_BOTONERA_LOGICO
			&& figurasEnAire[i]->getDimension()->getY()>Y_BOTONERA_LOGICO && figurasEnAire[i]->getDimension()->getY()<Y_BOTONERA_LOGICO+ALTO_BOTONERA_LOGICO )
			return true;
	}
	
	return false;
}

bool JuegoCliente::figEnTerreno(){

	for(int i = 0;i<=MAX_CLIENTES;i++){
		if( figurasEnAire[i] ==NULL) continue;
		if (figurasEnAire[i]->getDimension()->getX()>X_TERRENO_LOGICO && figurasEnAire[i]->getDimension()->getX()<X_TERRENO_LOGICO+ANCHO_TERRENO_LOGICO
			&& figurasEnAire[i]->getDimension()->getY()>Y_TERRENO_LOGICO && figurasEnAire[i]->getDimension()->getY()<Y_TERRENO_LOGICO+ALTO_TERRENO_LOGICO )
			return true;
	}	
	return false;
}

bool JuegoCliente::figEnComandos(){

	for(int i = 0;i<=MAX_CLIENTES;i++){
		if( figurasEnAire[i] ==NULL) continue;
		if (figurasEnAire[i]->getDimension()->getX()>X_COMANDOS_LOGICO && figurasEnAire[i]->getDimension()->getX()<X_COMANDOS_LOGICO+ANCHO_COMANDOS_LOGICO
			&& figurasEnAire[i]->getDimension()->getY()>Y_COMANDOS_LOGICO && figurasEnAire[i]->getDimension()->getY()<Y_COMANDOS_LOGICO+ALTO_COMANDOS_LOGICO )
			return true;
	}
	return false;
}




void JuegoCliente::soltarFiguraEnAire(){

	confirmarPosicionFiguraEnAire();

	if (terreno->adentroZonaTerreno(figurasEnAire[this->numCliente]->getDimension()->getX() - X_TERRENO_LOGICO,figurasEnAire[this->numCliente]->getDimension()->getY() - Y_TERRENO_LOGICO) && !figurasEnAire[this->numCliente]->superpuesta){
		//relativizar posiciones al terreno!
		figurasEnAire[this->numCliente]->cambiarPosicion(-X_TERRENO_LOGICO,-Y_TERRENO_LOGICO);
		terreno->agregarFigura( figurasEnAire[this->numCliente] );
		
		
		

		TransformFigureMessage* t_msg = new TransformFigureMessage();
		t_msg->setClientID(this->numCliente);
		t_msg->setFigureID(figurasEnAire[this->numCliente]->numero);
		t_msg->setSizeChange(T_DROP);
		t_msg->setX(figurasEnAire[this->numCliente]->getDimension()->getX());
		t_msg->setY(figurasEnAire[this->numCliente]->getDimension()->getY());

		this->maq->pushSendMessage(t_msg,this->numCliente);

		figurasEnAire[this->numCliente] = NULL;
	}else{

		botonera->restaurarInstanciaActual();
		vector[figurasEnAire[this->numCliente]->numero] = NULL;

		TransformFigureMessage* t_msg = new TransformFigureMessage();
		t_msg->setClientID(this->numCliente);
		t_msg->setFigureID(figurasEnAire[this->numCliente]->numero);
		t_msg->setSizeChange(T_DROPDEAD);
		this->maq->pushSendMessage(t_msg,this->numCliente);

		delete figurasEnAire[this->numCliente];
		figurasEnAire[this->numCliente] = NULL;
	}
}


void JuegoCliente::set2Click(){
	
	if(figurasEnAire[this->numCliente]->getTipoFigura()==LINEA){
		
		Linea* linea = ((Linea*)figurasEnAire[this->numCliente]);
		linea->cambiarPosicion(-X_TERRENO_LOGICO,-Y_TERRENO_LOGICO);
		
		double x = linea->getDimension()->getX();
		double y = linea->getDimension()->getY();

		Figura* result = terreno->getFiguraAtableCorrea(x,y);
		
		if(result==NULL){
			botonera->restaurarInstanciaActual();

			vector[figurasEnAire[this->numCliente]->numero] = NULL;

			delete figurasEnAire[this->numCliente];
			figurasEnAire[this->numCliente] = NULL;
			this->setCambio(true);
			terreno->setCambio(true);
			botonera->setCambio(true);
			comandos->setCambio(true);
		}else{
			result->posAtableCorrea(&x,&y);
			if(!linea->primerPuntoPuesto()){
				linea->setFigura1(result);
				linea->actualizar();

			}else{
				if(linea->getFigura1() == result){
					botonera->restaurarInstanciaActual();

					vector[figurasEnAire[this->numCliente]->numero] = NULL;

					delete figurasEnAire[this->numCliente];
					figurasEnAire[this->numCliente] = NULL;
					this->setCambio(true);
					terreno->setCambio(true);
					botonera->setCambio(true);
					comandos->setCambio(true);
				}else{
					linea->setFigura2(result);
					
					linea->getFigura1()->atarCorrea();
					linea->getFigura2()->atarCorrea();
					terreno->agregarFigura( figurasEnAire[this->numCliente] );

					linea->actualizar();
					figurasEnAire[this->numCliente] = NULL;
				}
			}
		}
	}else if(figurasEnAire[this->numCliente]->getTipoFigura()==SOGA){
		
		Linea* linea = ((Linea*)figurasEnAire[this->numCliente]);
		linea->cambiarPosicion(-X_TERRENO_LOGICO,-Y_TERRENO_LOGICO);
		
		double x = linea->getDimension()->getX();
		double y = linea->getDimension()->getY();

		Figura* result = terreno->getFiguraAtableSoga(x,y);
		
		if(result==NULL){
			botonera->restaurarInstanciaActual();

			vector[figurasEnAire[this->numCliente]->numero] = NULL;

			delete figurasEnAire[this->numCliente];
			figurasEnAire[this->numCliente] = NULL;
			this->setCambio(true);
			terreno->setCambio(true);
			comandos->setCambio(true);
			botonera->setCambio(true);
		}else{
			int res = result->esAtableSoga(x,y);
			if(!linea->primerPuntoPuesto()){
				linea->setFigura1(result);

				((Soga*)linea)->setNumsPosAtable(res,0);
				linea->actualizar();
			}else{
				if (result == linea->getFigura1()){
					botonera->restaurarInstanciaActual();			
					
					vector[figurasEnAire[this->numCliente]->numero] = NULL;
					
					delete figurasEnAire[this->numCliente];
					figurasEnAire[this->numCliente] = NULL;
					this->setCambio(true);
					terreno->setCambio(true);
					comandos->setCambio(true);
					botonera->setCambio(true);
				}else{
					linea->setFigura2(result);

					((Soga*)linea)->setNumsPosAtable(((Soga*)linea)->num1,res);
					linea->actualizar();
					linea->getFigura1()->atarSoga(((Soga*)linea)->num1);
					linea->getFigura2()->atarSoga(((Soga*)linea)->num2);
					terreno->agregarFigura( figurasEnAire[this->numCliente] );

					figurasEnAire[this->numCliente] = NULL;
				}
			}
		}
	}else{
			botonera->restaurarInstanciaActual();
			vector[figurasEnAire[this->numCliente]->numero] = NULL;
	}
}

void JuegoCliente::procesarMensaje(MessageFigura* msj){

	//declaro un stringstream que uso para pasar de string a int cuando lo necesito
	stringstream ss;
	ss.str("");

	int subtipo = msj->getSubtipoMsj();
	
	//antes que nada obtengo el id de la figura (pos en el vector)
	int idFig = msj->getIdFigura();

	switch (subtipo){
		case MSG_SUBTYPE_MOVEMENT:
		{
			//data1 es mov en x y data2 mov en y
			double movX,movY;

			ss << msj->getData1();
			ss >> movX;
			
			ss.str("");
			ss << msj->getData2();
			ss >> movY;

			//muevo la figura que sea
			vector[idFig]->cambiarPosicion(movX,movY);

			break;
		}
		case MSG_SUBTYPE_SETANGLE:
		{
			//data1 es angulo
			double angulo;

			ss << msj->getData1();
			ss >> angulo;

			//muevo la figura que sea
			vector[idFig]->setAngulo(angulo);

			break;
		}
		case MSG_SUBTYPE_CREATE:
		{
			//data1 es tipoFig y data2 y data 3 la posicion
			//ToDo
			/*No olvidar meterla en alguna de las figuras en aire*/
			break;
		}
		case MSG_SUBTYPE_DELETE:
		{
			break;
		}
		case MSG_SUBTYPE_SHIFT:
		{
			break;
		}
		case MSG_SUBTYPE_STRETCH:
		{
			break;
		}
/*		case MSG_SUBTYPE_ADD:
		{
			//agregarla al terreno!
			break;
		}
*/
	}
}