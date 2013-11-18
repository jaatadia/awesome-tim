#include "JuegoPlayCliente.h"
#include "Sonidos.h"
#include "CreateFigureMessage.h"
#include "ClientMessage.h"
#include "FactoryFiguras.h"
#include "ActualizeFigureMessage.h"
#include "RemoveFigureMessage.h"
#include "FireBowMessage.h"
#include "FireShotgunMessage.h"
#include "RotateMessage.h"
#include "BreakEggMessage.h"

#include "Tijera.h"
#include "GloboHelio.h"
#include "Arco.h"
#include "Escopeta.h"
#include "Huevo.h"

JuegoPlayCliente::JuegoPlayCliente(Superficie* fondo, void* tere,MaquinaEstados* maq)
{

	for(int i = 0;i<LARGO;i++){
		vector[i] = NULL;
	}

	TerrenoCliente* ter = (TerrenoCliente*) tere;
	this->fondo = fondo;
	this->maq = maq;
	this->numCliente = maq->getId();
		
	comandos = new ComandosPlayCliente(ANCHO_COMANDOS,ALTO_COMANDOS);
	terreno = new TerrenoCliente(ANCHO_TERRENO,ALTO_TERRENO,maq,numCliente,true);

	terreno->setFondo(ter->getFondo().c_str());
	
	std::list<Figura*> figurasAux;
	std::list<Figura*> figuras = ter->getListaFigs();
	std::list<Figura*>::iterator iteradorLista;
	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		if((*iteradorLista)->esUnion()){
			figurasAux.push_back((*iteradorLista));
		}else{
			Figura* fig = (*iteradorLista)->clonar(false);
			fig->numero = (*iteradorLista)->numero;
			this->vector[fig->numero] = fig;
			terreno->agregarFigura(fig);
		}
	}
	for (iteradorLista = figurasAux.begin() ; iteradorLista != figurasAux.end(); iteradorLista++){
		Figura* fig = (*iteradorLista)->clonar(false);
		fig->numero = (*iteradorLista)->numero;
		this->vector[fig->numero] = fig;
		terreno->agregarFigura(fig);
	}
	terreno->resizear();
	this->setCambio(true);

	//cosas para informar que se gano
	this->gano = false; //si quieren ver la animacion hay que ponerlo en true
	this->contadorGano = -1;
	imgGano = NULL;

	terreno->setMiPorcion(ter->x1,ter->y1,ter->x2,ter->y2);
}

JuegoPlayCliente::~JuegoPlayCliente(void)
{
	delete terreno;
	delete comandos;
	delete fondo;
	delete imgGano;
}

bool JuegoPlayCliente::onEvent(Ventana* ventana,Superficie **sup){

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
			}case SDL_MOUSEBUTTONDOWN:
			{
				posClickX = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(evento.button.x);
				posClickY = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(evento.button.y);

				if (evento.button.state == SDL_BUTTON_LMASK){
					comandos->click(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(posClickX - X_COMANDOS_LOGICO), EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(posClickY - Y_COMANDOS_LOGICO), this);
				}

				terreno->interactuar(posClickX - X_TERRENO_LOGICO,posClickY - Y_TERRENO_LOGICO);
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				posClickX = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(evento.button.x);
				posClickY = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(evento.button.y);

				comandos->release(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(posClickX - X_COMANDOS_LOGICO), EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(posClickY - Y_COMANDOS_LOGICO),&aux ,this);
				break;
			}
		}
	}
	return aux;
}

void JuegoPlayCliente::onLoop(){
	bool continuar = true;
	Message * msg = this->maq->getProcessMessage();
	while((continuar)&&(msg!=NULL)){
		switch (msg->getType()){
			case MSG_TYPE_CREATE_FIGURE:
				{
					Figura* fig = FactoryFiguras::create((CreateFigureMessage*)msg);
					if(fig!=NULL){
						vector[fig->numero] = fig;
						terreno->agregarFigura(fig);
					}
					delete msg;
				}
				break;
			case MSG_TYPE_TRANSFORM_FIGURE:
				{
					TransformFigureMessage* t_msg = (TransformFigureMessage*) msg;
					Figura* fig = vector[t_msg->getFigureID()];
					if(fig!=NULL){
						switch(t_msg->getSizeChange()){
							case T_ROTATE:
								fig->setAngulo(t_msg->getAngle());
								fig->setX(t_msg->getX());
								fig->setY(t_msg->getY());
								break;
						}
					}
					delete msg;
				}
				break;
			case MSG_TYPE_REMOVE:
				{
					FigureMessage* r_msg = (FigureMessage*) msg;
					Figura* fig = vector[r_msg->getFigureID()];
					terreno->eliminarFigura(fig);
					vector[r_msg->getFigureID()] = NULL;
					delete msg;
				}
				break;
			case MSG_TYPE_ACTUALIZE:
				{
					FigureMessage* r_msg = (FigureMessage*) msg;
					vector[r_msg->getFigureID()]->actualizar();
					delete msg;
				}
				break;
			case MSG_TYPE_CLOSE_SCISSOR:
				{
					FigureMessage* r_msg = (FigureMessage*) msg;
					((Tijera*)(vector[r_msg->getFigureID()]))->cerrar();
					delete msg;
				}
				break;
			case MSG_TYPE_BREAK_EGG:
				{
					FigureMessage* r_msg = (FigureMessage*) msg;
					((Huevo*)(vector[r_msg->getFigureID()]))->romper();
					delete msg;
				}
				break;
			case MSG_TYPE_POP_BALLOON:
				{
					FigureMessage* r_msg = (FigureMessage*) msg;
					((GloboHelio*)(vector[r_msg->getFigureID()]))->pinchar();
					delete msg;
				}
				break;
			case MSG_TYPE_FIRE_BOW:
				{
					FireBowMessage* fb_msg = (FireBowMessage*) msg;
					int gunID  = fb_msg->getGunID();
					int proyectileID  = fb_msg->getProyectileID();
					Arco* gun = (Arco*)vector[gunID];
					gun->desatarSoga(0);
					Figura* fig = gun->disparar();
					fig->numero = proyectileID;
					this->terreno->agregarFigura(fig);
					vector[proyectileID] = fig;
					delete msg;
				}
				break;
			case MSG_TYPE_FIRE_SHOTGUN:
				{
					FireShotgunMessage* fb_msg = (FireShotgunMessage*) msg;
					int gunID  = fb_msg->getGunID();
					int proyectileID  = fb_msg->getProyectileID();
					Escopeta* gun = (Escopeta*)vector[gunID];
					Figura* fig = gun->disparar();
					fig->numero = proyectileID;
					this->terreno->agregarFigura(fig);
					vector[proyectileID] = fig;
					delete msg;
				}
				break;
			case MSG_TYPE_VICTORY:
				{
					this->gano = true;
					this->actualizarVictoria();
					delete msg;
				}
				break;
			case MSG_TYPE_ROTATE:
				{
					RotateMessage* r_msg = (RotateMessage*) msg;
					vector[r_msg->getFigureID()]->setAnguloPartesRotables(r_msg->getAngle());
					delete msg;
				}
				break;
			case MSG_TYPE_CLIENT_MESSAGE:
				{
					ClientMessage* c_msg = (ClientMessage*)  msg;
					switch(c_msg->getAction()){
						case A_DISCONECT:
						case A_UNREADY:
							{
								if (c_msg->getClientID()==this->numCliente){
									this->maq->returnProcessMessage(msg);
								}else{
									delete msg;
								}
								continuar = false;
								this->quit();
							}
							break;
					}
				}
				break;
		}
		
		if(continuar){
			msg = this->maq->getProcessMessage();
		}

	}

	terreno->actualizarModelo(vector);
	terreno->setCambio(true);
}

bool JuegoPlayCliente::onRender(Superficie* sup){
	if(this->huboCambios()){
		Superficie* temp = fondo->scaleSurface(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(ANCHO_PANTALLA_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(ALTO_PANTALLA_LOGICO));
		temp->setTransparency(100);
		sup->dibujarSupreficie(temp,NULL,0,0);
		delete temp;
		this->setCambio(false);
	}
	
	sup->dibujarSupreficie(terreno->getImpresion(),NULL,EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(X_TERRENO_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(Y_TERRENO_LOGICO));
	if(comandos->huboCambios()){
		//sup->dibujarSupreficie(comandos->getImpresion(),NULL,EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(X_COMANDOS_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(Y_COMANDOS_LOGICO));
		comandos->dibujate(sup,EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(X_COMANDOS_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(Y_COMANDOS_LOGICO));
	}
	if(gano){
		dibujarVictoria(sup);
	}
	return true;
}

void JuegoPlayCliente::actuarVentana(Ventana* ventana,Superficie** sup,Uint32 IDventana,SDL_WindowEvent evento){

	switch (evento.event){
		case SDL_WINDOWEVENT_CLOSE:
		{
			//if (evento.windowID == ventana->getID())
				maq->salir();
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
			terreno->cambioVistaFiguras();
			terreno->resizear();
			comandos->resizear();
			
			this->setCambio(true);

			break;
		}

	}
}

void JuegoPlayCliente::quit(){
	Sonidos::stopMusic();
	maq->editor();
}


void JuegoPlayCliente::actualizarVictoria(){
	contadorGano++;
	int ancho = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(ANCHO_TERRENO_LOGICO);
	int alto = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(ALTO_TERRENO_LOGICO);
	if (contadorGano==INICIO_GANO1){
		Sonidos::playMusic(VICTORY_MUS);
		delete imgGano;
		imgGano = (Imagen*)Contenedor::getMultimedia(GANO_1);
		imgGano = imgGano->scaleImagen(ancho,alto);
	}else if (contadorGano==INICIO_GANO2){
		delete imgGano;
		imgGano = (Imagen*)Contenedor::getMultimedia(GANO_2);
		imgGano = imgGano->scaleImagen(ancho,alto);
	}else if (contadorGano==INICIO_GANO3){
		delete imgGano;
		imgGano = (Imagen*)Contenedor::getMultimedia(GANO_3);
		imgGano = imgGano->scaleImagen(ancho,alto);
	}else if (contadorGano==INICIO_GANO4){
		delete imgGano;
		imgGano = (Imagen*)Contenedor::getMultimedia(GANO_4);
		imgGano = imgGano->scaleImagen(ancho,alto);
	}else if (contadorGano==INICIO_GANO5){
		delete imgGano;
		imgGano = (Imagen*)Contenedor::getMultimedia(GANO_5);
		imgGano = imgGano->scaleImagen(ancho,alto);
	}else if (contadorGano==INICIO_GANO6){
		delete imgGano;
		imgGano = (Imagen*)Contenedor::getMultimedia(GANO_6);
		imgGano = imgGano->scaleImagen(ancho,alto);
	}else if (contadorGano==DURACION_FRAMES){
		if(REPEAT){
			contadorGano = REPEAT_FROM -1;
		}
	}
}

void JuegoPlayCliente::dibujarVictoria(Superficie* sup){
	sup->dibujarImagen(imgGano,NULL,0,0);
}

void JuegoPlayCliente::sendUnready(){
	ClientMessage* c_msg = new ClientMessage();
	c_msg->setClientID(this->numCliente);
	c_msg->setAction(A_UNREADY);
	this->maq->pushSendMessage(c_msg,numCliente);
}