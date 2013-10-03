#include "JuegoPlay.h"

JuegoPlay::JuegoPlay(Terreno* ter,MaquinaEstados* maq)
{
	this->maq = maq;
	terreno = new Terreno(ANCHO_TERRENO,ALTO_TERRENO,true);

	terreno->setFondo(ter->getFondo().c_str());
	
	std::list<Figura*> figuras = ter->getListaFigs();
	std::list<Figura*>::iterator iteradorLista;
	for (iteradorLista = figuras.begin() ; iteradorLista != figuras.end(); iteradorLista++){
		terreno->agregarFigura((*iteradorLista)->clonar());
	}
	terreno->resizear();
}

JuegoPlay::~JuegoPlay(void)
{
	delete terreno;
}

void JuegoPlay::onEvent(Ventana* ventana,Superficie **sup){

	SDL_Event evento;
	double posClickX, posClickY;

	while(SDL_PollEvent(&evento)){
		switch(evento.type){
			case SDL_WINDOWEVENT:
			{
				actuarVentana(ventana,sup,evento.window.windowID,evento.window);
				//actualiza las escalas si fue un resize
				break;
			}case SDL_MOUSEBUTTONDOWN:
			{
				maq->editor();
			}
		}
	}

}

void JuegoPlay::onLoop(){
	terreno->actualizarModelo();
}

bool JuegoPlay::onRender(Superficie* sup){
	sup->restore();
	sup->dibujarSupreficie(terreno->getImpresion(),NULL,EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(X_TERRENO_LOGICO),EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(Y_TERRENO_LOGICO));
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

			break;
		}

	}
}