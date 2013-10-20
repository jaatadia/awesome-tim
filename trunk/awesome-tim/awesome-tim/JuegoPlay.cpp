#include "JuegoPlay.h"

JuegoPlay::JuegoPlay(Superficie* fondo, Terreno* ter,MaquinaEstados* maq)
{
	this->fondo = fondo;
	this->maq = maq;
		
	comandos = new ComandosPlay(ANCHO_COMANDOS,ALTO_COMANDOS);
	terreno = new Terreno(ANCHO_TERRENO,ALTO_TERRENO,true);

	terreno->setFondo(ter->getFondo().c_str());
	
	std::list<Figura*> figurasAux;
	std::list<Figura*> figuras = ter->getListaFigs();
	std::list<Figura*>::iterator iteradorLista;
	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		if((*iteradorLista)->esUnion()){
			figurasAux.push_back((*iteradorLista));
		}else{
			terreno->agregarFigura((*iteradorLista)->clonar(false));
		}
	}
	for (iteradorLista = figurasAux.begin() ; iteradorLista != figurasAux.end(); iteradorLista++){
		terreno->agregarFigura((*iteradorLista)->clonar(false));
	}
	terreno->resizear();
	this->setCambio(true);

	//cosas para informar que se gano
	this->gano = false; //si quieren ver la animacion hay que ponerlo en true
	this->contadorGano = -1;
	imgGano = NULL;
}

JuegoPlay::~JuegoPlay(void)
{
	delete terreno;
	delete comandos;
	delete fondo;
	delete imgGano;
}

bool JuegoPlay::onEvent(Ventana* ventana,Superficie **sup){

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

void JuegoPlay::onLoop(){
	if(!gano){
		terreno->actualizarModelo();
	}else{
		actualizarVictoria();
	}
}

bool JuegoPlay::onRender(Superficie* sup){
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

void JuegoPlay::actuarVentana(Ventana* ventana,Superficie** sup,Uint32 IDventana,SDL_WindowEvent evento){

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

void JuegoPlay::quit(){
	maq->editor();
}


void JuegoPlay::actualizarVictoria(){
	contadorGano++;
	int ancho = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(ANCHO_TERRENO_LOGICO);
	int alto = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(ALTO_TERRENO_LOGICO);
	if (contadorGano==INICIO_GANO1){
		delete imgGano;
		//Sonidos::play("../images/sound.wav");
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

void JuegoPlay::dibujarVictoria(Superficie* sup){
	sup->dibujarImagen(imgGano,NULL,0,0);
}