#include "BotoneraController.h"
#include "Constantes.h"
#include "PelotaBasquet.h"
#include "PelotaBowling.h"
#include "PelotaTenis.h"
#include "GloboHelio.h"
#include "Plataforma.h"
#include "Engranaje.h"
#include "Motor.h"
#include "Linea.h"
#include "Soga.h"
#include "Balancin.h"
#include "CintaTransportadora.h"
#include "Arco.h"
#include "Escopeta.h"

BotoneraController::BotoneraController(int ancho,int alto, int cantBotonesMostrados, double factorAreaFiguras, double scrollScaleFactor, double buttonScaleFactor) {
	altoOriginal = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasY(alto);
	anchoOriginal = EscalasDeEjes::getInstance()->getCantidadUnidadesLogicasX(ancho);
	cantBotonesMostradosOrig = cantBotonesMostrados;

	this->factorAreaFiguras = factorAreaFiguras;
	this->scrollScaleFactor = scrollScaleFactor;
	this->buttonScaleFactor = buttonScaleFactor;
	this->altoAreaFiguras = int(factorAreaFiguras*alto);
	this->altoAreaScroll = alto - this->altoAreaFiguras;
	this->botonera = new Botonera(ancho, alto);
	this->botonera->setAltoBoton(this->altoAreaFiguras / cantBotonesMostrados);
	this->botonera->setAnchoBoton(ancho);
	this->scrollStep = this->botonera->getAltoBoton() / this->FACTOR_SCROLL;
	this->supFiguraActual = 0;
	this->numeroFigActual = 0;
	this->layerPrincipal = new Superficie(ancho, alto);
	this->figuraActual = 0;
	this->layerFiguras = NULL;
	this->layerADibujar = NULL;
	this->layerFigurasOrig = NULL;
	this->setScrollDirection(SCROLL_OFF);
	this->buttonPressed = false;

	//int buttonSide = (this->botonera->getAltoBoton() > this->botonera->getAnchoBoton()) ? this->botonera->getAnchoBoton() : this->botonera->getAltoBoton();
	int botonAncho = this->botonera->getAnchoBoton();
	int botonAlto = this->botonera->getAltoBoton();

	Contenedor::putMultimedia("../images/SquareButton.png", new Imagen("../images/SquareButton.png"));
	this->squareButton = ((Imagen *)Contenedor::getMultimedia("../images/SquareButton.png"))->scaleImagen(botonAncho, botonAlto);

	Contenedor::putMultimedia("../images/SquareButtonPressed.png", new Imagen("../images/SquareButtonPressed.png"));
	this->squareButtonPressed = ((Imagen *)Contenedor::getMultimedia("../images/SquareButtonPressed.png"))->scaleImagen(botonAncho, botonAlto);

	int scrollSide = (ancho > (this->altoAreaScroll >> 1)) ? (this->altoAreaScroll >> 1) * this->scrollScaleFactor : ancho * this->scrollScaleFactor;

	Contenedor::putMultimedia("../images/ScrollButton.png", new Imagen("../images/ScrollButton.png"));
	this->scrollButtonUp = ((Imagen *)Contenedor::getMultimedia("../images/ScrollButton.png"))->scaleImagen(scrollSide, scrollSide);

	Contenedor::putMultimedia("../images/ScrollButtonPressed.png", new Imagen("../images/ScrollButtonPressed.png"));
	this->scrollButtonUpPressed = ((Imagen *)Contenedor::getMultimedia("../images/ScrollButtonPressed.png"))->scaleImagen(scrollSide, scrollSide);

	this->scrollButtonDown = this->scrollButtonUp->rotarImagen(180);
	this->scrollButtonDownPressed = this->scrollButtonUpPressed->rotarImagen(180);

	int x = (this->scrollButtonUp->getAncho() >= this->botonera->getAncho()) ? 0 : ((this->botonera->getAncho() - this->scrollButtonUp->getAncho()) >> 1);
	int y = ((this->scrollButtonUp->getAlto() >= (this->altoAreaScroll >> 1)) ? 0 : (((this->altoAreaScroll >> 1) - this->scrollButtonUp->getAlto()) >> 1));

	this->layerScroll = new Superficie(ancho, alto);
	this->layerScroll->dibujarCuadradoNegro(0, 0, ancho, alto);
	this->layerScroll->dibujarImagen(this->scrollButtonUp, NULL, x, y);
	this->layerScroll->dibujarImagen(this->scrollButtonDown, NULL, x, y + this->altoAreaFiguras + (this->altoAreaScroll >> 1));
}

void BotoneraController::resizear(){

	setCambio(true);

	double altoTemp = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(altoOriginal);
	double anchoTemp = EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasX(anchoOriginal);

	this->altoAreaFiguras = int(factorAreaFiguras*altoTemp);
	this->altoAreaScroll = altoTemp - this->altoAreaFiguras;

	botonera->setAlto(altoTemp);
	botonera->setAncho(anchoTemp);


	botonera->setAltoBoton(this->altoAreaFiguras / cantBotonesMostradosOrig);
	botonera->setAnchoBoton(anchoTemp);
	botonera->setAlturaMax(EscalasDeEjes::getInstance()->getCantidadUnidadesFisicasY(botonera->getAlturaMaxOrig()/5));

	this->scrollStep = botonera->getAltoBoton() / this->FACTOR_SCROLL;

	Superficie* layerPrincipalTemp = layerPrincipal->scaleSurface(anchoTemp, altoTemp);
	Superficie* layerFigurasTemp = layerFigurasOrig->scaleSurface(anchoTemp, botonera->getAlturaMax() );

	delete layerPrincipal;
	delete layerFiguras;

	layerPrincipal = layerPrincipalTemp;
	layerFiguras = layerFigurasTemp;

//	int buttonSide = (this->botonera->getAltoBoton() > this->botonera->getAnchoBoton()) ? this->botonera->getAnchoBoton() : this->botonera->getAltoBoton();
//olvidate de mantener una relacion cuadrada porque el layer de figuras se deforma segun el resize asi que nunca encajarian
	int botonAncho = this->botonera->getAnchoBoton();
	int botonAlto = this->botonera->getAltoBoton();

	delete squareButton;
	this->squareButton = ((Imagen *)Contenedor::getMultimedia("../images/SquareButton.png"))->scaleImagen(botonAncho, botonAlto);

	delete squareButtonPressed;
	this->squareButtonPressed = ((Imagen *)Contenedor::getMultimedia("../images/SquareButtonPressed.png"))->scaleImagen(botonAncho, botonAlto);

	int scrollSide = (anchoTemp > (this->altoAreaScroll >> 1)) ? (this->altoAreaScroll >> 1) * this->scrollScaleFactor : anchoTemp * this->scrollScaleFactor;

	delete scrollButtonUp;
	this->scrollButtonUp = ((Imagen *)Contenedor::getMultimedia("../images/ScrollButton.png"))->scaleImagen(scrollSide, scrollSide);

	delete scrollButtonUpPressed;
	this->scrollButtonUpPressed = ((Imagen *)Contenedor::getMultimedia("../images/ScrollButtonPressed.png"))->scaleImagen(scrollSide, scrollSide);

	delete scrollButtonDown;
	delete scrollButtonDownPressed;
	this->scrollButtonDown = this->scrollButtonUp->rotarImagen(180);
	this->scrollButtonDownPressed = this->scrollButtonUpPressed->rotarImagen(180);

	int x = (this->scrollButtonUp->getAncho() >= this->botonera->getAncho()) ? 0 : ((this->botonera->getAncho() - this->scrollButtonUp->getAncho()) >> 1);
	int y = ((this->scrollButtonUp->getAlto() >= (this->altoAreaScroll >> 1)) ? 0 : (((this->altoAreaScroll >> 1) - this->scrollButtonUp->getAlto()) >> 1));


	Superficie* layerScrollTemp = layerScroll->scaleSurface(anchoTemp,altoTemp);
	delete layerScroll;
	layerScroll	= layerScrollTemp;

	this->layerScroll->dibujarCuadradoNegro(0, 0, anchoTemp, altoTemp);
	this->layerScroll->dibujarImagen(this->scrollButtonUp, NULL, x, y);
	this->layerScroll->dibujarImagen(this->scrollButtonDown, NULL, x, y + this->altoAreaFiguras + (this->altoAreaScroll >> 1));
}

BotoneraController::~BotoneraController() {
	if (this->layerPrincipal) {
		delete (this->layerPrincipal);
		this->layerPrincipal = 0;
	}
	if (this->layerFiguras) {
		delete (this->layerFiguras);
		this->layerFiguras = 0;
	}
	if (this->layerFigurasOrig) {
		delete (this->layerFigurasOrig);
		this->layerFigurasOrig = 0;
	}
	if (this->layerADibujar) {
		delete (this->layerADibujar);
		this->layerADibujar = 0;
	}
	if (this->supFiguraActual) {
		delete (this->supFiguraActual);
		this->supFiguraActual = 0;
	}
	if (this->botonera) {
		delete (this->botonera);
		this->botonera = 0;
	}
	delete this->layerScroll;
	delete this->scrollButtonDown;
	delete this->scrollButtonDownPressed;
	delete this->scrollButtonUp;
	delete this->scrollButtonUpPressed;
	delete this->squareButton;
	delete this->squareButtonPressed;
}

void BotoneraController::handleEventBotonera(double mouseX, double mouseY, Uint32 type) {
	//Analiza que tipo de accion recibio
	this->setCambio(false);
	switch (type) {
		case SDL_MOUSEBUTTONDOWN:
			if (this->layerPrincipal->getPixel(mouseX, mouseY) != this->COLOR_FONDO) {
				if (mouseX >= 0 && mouseX <= this->botonera->getAncho()) {
					if (mouseY >= 0 && mouseY <= (this->altoAreaScroll >> 1)) {
						//Scroll arriba
						this->setScrollDirection(this->SCROLL_TOP);
						this->setCambio(true);
					} else if (mouseY >= this->altoAreaFiguras + (this->altoAreaScroll >> 1)&& mouseY <= this->botonera->getAlto()) {
						//Scroll abajo
						this->setScrollDirection(this->SCROLL_BOT);
						this->setCambio(true);
					} else if (mouseY >= (this->altoAreaScroll >> 1) && mouseY <= this->altoAreaFiguras + (this->altoAreaScroll >> 1)) {
						//Seleccion de figuras
						if (this->figuraActual = obtenerFigura(mouseX, mouseY))
							this->setCambio(true);
					}
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			this->figuraActual = 0;
			this->setScrollDirection(this->SCROLL_OFF);
			this->buttonPressed = false;
			this->setCambio(true);
	}
}

Superficie* BotoneraController::getImpresion(){
	//Dibuja en el buffer principal (Double Buffer)
	if (this->layerFiguras && this->huboCambios()) {

		//Pone los numeritos de cuantas instancias quedan
		this->dibujarCantInstancias();

		//Actualiza scroll
		if ((this->scrollBot | this->scrollTop) != 0 && (this->botonera->getAlturaMax() > this->altoAreaFiguras)) {
			this->setCambio(true);
			if (this->scrollBot) {
				int resto = this->botonera->getAlturaMax() - this->altoAreaFiguras - this->botonera->getY();
				int paso = (resto > this->scrollStep) ? this->scrollStep : resto;
				this->botonera->setY(this->botonera->getY() + paso);
			}
			else {
				int paso = (this->botonera->getY() > this->scrollStep) ? this->scrollStep : this->botonera->getY();
				this->botonera->setY(this->botonera->getY() - paso);
			}
		}

		Rectangulo rect(this->botonera->getX(), this->botonera->getY(), this->botonera->getAncho(), this->altoAreaFiguras);
		this->layerPrincipal->dibujarCuadradoNegro(0,0,this->getAncho(),this->getAlto());
		this->layerPrincipal->dibujarSupreficie(this->layerScroll, NULL, 0, 0);
		this->layerPrincipal->dibujarSupreficie(this->layerADibujar, &rect, 0, (this->altoAreaScroll >> 1));\
		//ya no es necesario
		delete this->layerADibujar;
		layerADibujar = NULL;

		if (this->buttonPressed) 
		{
			int squareX = (this->squareButton->getAncho() == this->botonera->getAnchoBoton()) ? 0 : (this->botonera->getAnchoBoton() - this->squareButton->getAncho()) >> 1;
			int squareY = (this->squareButton->getAlto() == this->botonera->getAltoBoton()) ? (this->botonera->getAltoBoton() - this->squareButton->getAlto()) >> 1 : 0;
			squareY += this->botonera->getAltoBoton() * this->numeroFigActual - this->botonera->getY() + (this->altoAreaScroll >> 1);
			rect.x = 0;
			rect.y = (this->botonera->getY() > this->botonera->getAltoBoton() * this->numeroFigActual) ? this->botonera->getY() % this->botonera->getAltoBoton() : 0;
			rect.ancho = this->squareButtonPressed->getAncho();
			rect.alto = (squareY + this->squareButton->getAlto() > this->altoAreaFiguras + (this->altoAreaScroll >> 1)) ? this->altoAreaFiguras + (this->altoAreaScroll >> 1) - squareY : this->squareButton->getAlto();
			this->layerPrincipal->dibujarImagen(this->squareButtonPressed, &rect, squareX, squareY + rect.y);
		}

		if (this->scrollTop | this->scrollBot != 0) {
			int x = (this->scrollButtonUp->getAncho() >= this->botonera->getAncho()) ? 0 : ((this->botonera->getAncho() - this->scrollButtonUp->getAncho()) >> 1);
			int y = ((this->scrollButtonUp->getAlto() >= (this->altoAreaScroll >> 1)) ? 0 : (((this->altoAreaScroll >> 1) - this->scrollButtonUp->getAlto()) >> 1));
			if (this->scrollTop)
				this->layerPrincipal->dibujarImagen(this->scrollButtonUpPressed, NULL, x, y);
			else
				this->layerPrincipal->dibujarImagen(this->scrollButtonDownPressed, NULL, x, y + this->altoAreaFiguras + (this->altoAreaScroll >> 1));
		}
	}
	this->setCambio((this->scrollTop) || (this->scrollBot));
	return layerPrincipal;
}

void BotoneraController::agregarBoton(Figura * figura, int cantidadInstancias) {
	Imagen * img = new Imagen(figura->getIDBotonera());
	int buttonSide = (this->botonera->getAnchoBoton() > this->botonera->getAltoBoton()) ? this->botonera->getAltoBoton() * this->buttonScaleFactor : this->botonera->getAnchoBoton() * this->buttonScaleFactor;
	
	Imagen* temp = img->scaleImagen(buttonSide, buttonSide);
	delete img;
	img = temp;

	Superficie * aux = new Superficie(this->botonera->getAncho(), this->botonera->getAlturaMax() + this->botonera->getAltoBoton());
	Rectangulo rect(0, 0, this->botonera->getAncho(), this->botonera->getAlturaMax());
	if (this->layerFigurasOrig)
		aux->dibujarSupreficie(this->layerFigurasOrig, &rect, 0, 0);
	rect.ancho = img->getAncho();
	rect.alto = img->getAlto();
	int x = (img->getAncho() >= this->botonera->getAncho()) ? 0 : ((this->botonera->getAncho() - img->getAncho()) >> 1);
	int y = this->botonera->getAlturaMax() + ((img->getAlto() >= this->botonera->getAltoBoton()) ? 0 : ((this->botonera->getAltoBoton() - img->getAlto()) >> 1));
	int squareX = (this->squareButton->getAncho() == this->botonera->getAnchoBoton()) ? 0 : (this->botonera->getAnchoBoton() - this->squareButton->getAncho()) >> 1;
	int squareY = (this->squareButton->getAncho() == this->botonera->getAnchoBoton()) ? (this->botonera->getAltoBoton() - this->squareButton->getAlto()) >> 1 : 0;
	
	aux->dibujarImagen(this->squareButton, NULL, squareX, this->botonera->getAlturaMax() + squareY);
	aux->dibujarImagen(img,&rect,x,y);
	delete img;

	if(this->layerFigurasOrig)
		delete (this->layerFigurasOrig);
	this->layerFigurasOrig = aux;
	this->botonera->agregarBoton(figura, cantidadInstancias);
	this->botonera->setAlturaMax(this->botonera->getAlturaMax() + this->botonera->getAltoBoton());
	this->botonera->setAlturaMaxOrig(this->botonera->getAlturaMaxOrig() + this->botonera->getAltoBoton());
}

void BotoneraController::setScrollDirection(int direction) {
	switch (direction) {
		case this->SCROLL_BOT:
			this->scrollBot = true;
			this->scrollTop = false;
			break;
		case this->SCROLL_TOP:
			this->scrollBot = false;
			this->scrollTop = true;
			break;
		case this->SCROLL_OFF:
			this->scrollBot = false;
			this->scrollTop = false;
	}
}

Figura * BotoneraController::obtenerFigura(double x, double y){
	this->buttonPressed = true;
	this->numeroFigActual= ((int)(this->botonera->getY() + y - (this->altoAreaScroll >> 1)))/this->botonera->getAltoBoton();
	return this->botonera->obtenerFigura(this->numeroFigActual);
}

void BotoneraController::restaurarInstanciaActual(){
	this->botonera->restaurarInstanciaActual( this->numeroFigActual );
}

void BotoneraController::restaurarInstancias( std::vector<int> numsFigARestaurar ){
	this->botonera->restaurarInstancias(numsFigARestaurar);
}

int BotoneraController::getAlto() {
	return this->botonera->getAlto();
}

int BotoneraController::getAncho() {
	return this->botonera->getAncho();
}

std::list<struct boton> BotoneraController::getListaFiguras() {
	return this->botonera->getListaFiguras();
}



void BotoneraController::ScrollUp(){
	this->setScrollDirection(this->SCROLL_TOP);
	if (this->scrollBot) {
		int resto = this->botonera->getAlturaMax() - this->altoAreaFiguras - this->botonera->getY();
		int paso = (resto > this->scrollStep*2) ? this->scrollStep*2 : resto;
		this->botonera->setY(this->botonera->getY() + paso);
	}
	else {
		int paso = (this->botonera->getY() > (this->scrollStep*2)) ? (this->scrollStep*2) : this->botonera->getY();
		this->botonera->setY(this->botonera->getY() - paso);
	}
	this->setScrollDirection(this->SCROLL_OFF);
	this->setCambio(true);
}

void BotoneraController::ScrollDown(){
	this->setScrollDirection(this->SCROLL_BOT);
	if (this->scrollBot) {
		int resto = this->botonera->getAlturaMax() - this->altoAreaFiguras - this->botonera->getY();
		int paso = (resto > this->scrollStep*2) ? this->scrollStep*2 : resto;
		this->botonera->setY(this->botonera->getY() + paso);
	}
	else {
		int paso = (this->botonera->getY() > (this->scrollStep*2)) ? (this->scrollStep*2) : this->botonera->getY();
		this->botonera->setY(this->botonera->getY() - paso);
	}
	this->setScrollDirection(this->SCROLL_OFF);
	this->setCambio(true);
}

#include "Polea.h"
#include "Vela.h"
#include "Aro.h"
#include "Yunque.h"
#include "Clavo.h"
#include "Tijera.h"
#include "Chinche.h"
#include "PaletaFlipper.h"
#include "Canio.h"
#include "Codo.h"
#include "Huevo.h"
#include "Queso.h"

bool BotoneraController::agregarBotonesDefault(){

	this->agregarBoton(new Queso(0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Canio(LARGO_CANIO_DEFAULT,0,0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Codo(0,0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Huevo(0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Escopeta(0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Arco(0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Aro(0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Soga(0,0,0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new GloboHelio((double)0,(double)0,CELESTE),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Chinche(0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Tijera(0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Clavo(0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Yunque(0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Vela(ID_VELA,0,0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Polea(0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new PelotaTenis(0,0),INSTANCIAS_DEFAULT);	
	this->agregarBoton(new CintaTransportadora(3,0,0,0),INSTANCIAS_DEFAULT); 
	this->agregarBoton(new Linea(0,0,0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Motor(0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Plataforma(LARGO_PLATAFORMA_DEFAULT,0,0,0),INSTANCIAS_DEFAULT); 
	this->agregarBoton(new PelotaBowling(0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new PelotaBasquet(0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Engranaje(0,0),INSTANCIAS_DEFAULT);
	this->agregarBoton(new Balancin(0,0,ANGULO_BALANCIN_IZQ),INSTANCIAS_DEFAULT);
	this->agregarBoton(new PaletaFlipper(0,0,IZQUIERDA),INSTANCIAS_DEFAULT);	

	return true;
}

bool BotoneraController::estaVacia(){
	std::list<struct boton> lista = this->botonera->getListaFiguras();
	return (lista.size()==0);
}


void BotoneraController::dibujarCantInstancias(){
	try{
		int anchoBoton = botonera->getAnchoBoton();
		int altoBoton = botonera->getAltoBoton();


		int posBotonX = 0;
		int posBotonY = 0;

		std::list<struct boton> figs = botonera->getListaFiguras();
		std::list<struct boton>::iterator itFig = figs.begin();

		int cantInstancias;
		Imagen* img;
		//solo para copiarla y no cambiar la original
		layerADibujar = layerFiguras->rotarSuperficie(0);

		int cantDeFig = figs.size();

		for(itFig = figs.begin(); itFig != figs.end(); itFig++){

			cantInstancias = (*itFig).cantInstancias;

			//convertir a c string
			stringstream ss;
			ss<<cantInstancias;
			string digito =ss.str();
			const char* dig = digito.c_str();

			//dibujar
			img = new Imagen(dig,altoBoton*0.2,255,255,255);
			//y un pequeño desplazamiento para que entren bien al boton
			layerADibujar->dibujarImagen(img, NULL, 7, posBotonY+7);

			posBotonY += altoBoton;

			if(img!=NULL){
				delete img;
			}
		}
	}catch(...){
	}

}