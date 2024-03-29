#include "BotoneraControllerCliente.h"
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
#include "Polea.h"
#include "Vela.h"
#include "Aro.h"
#include "Yunque.h"
#include "Clavo.h"
#include "Tijera.h"
#include "Chinche.h"
#include "Carrito.h"
#include "Arco.h"
#include "Canio.h"
#include "Codo.h"
#include "Escopeta.h"
#include "PaletaFlipper.h"
#include "Domino.h"
#include "Huevo.h"
#include "MotorRaton.h"
#include "Queso.h"

#include "Boton.h"

BotoneraControllerCliente::BotoneraControllerCliente(int ancho,int alto, int cantBotonesMostrados, double factorAreaFiguras, double scrollScaleFactor, double buttonScaleFactor) {
	//try{
		
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

		Contenedor::putMultimedia("../images/ScrollButtonPressed.png", new Imagen("../images/ScrollButtonPressed.png\0"));
		this->scrollButtonUpPressed = ((Imagen *)Contenedor::getMultimedia("../images/ScrollButtonPressed.png"))->scaleImagen(scrollSide, scrollSide);

		this->scrollButtonDown = this->scrollButtonUp->rotarImagen180();
		this->scrollButtonDownPressed = this->scrollButtonUpPressed->rotarImagen180();

		int x = (this->scrollButtonUp->getAncho() >= this->botonera->getAncho()) ? 0 : ((this->botonera->getAncho() - this->scrollButtonUp->getAncho()) >> 1);
		int y = ((this->scrollButtonUp->getAlto() >= (this->altoAreaScroll >> 1)) ? 0 : (((this->altoAreaScroll >> 1) - this->scrollButtonUp->getAlto()) >> 1));

		this->layerScroll = new Superficie(ancho, alto);
		this->layerScroll->dibujarCuadradoNegro(0, 0, ancho, alto);
		this->layerScroll->dibujarImagen(this->scrollButtonUp, NULL, x, y);
		this->layerScroll->dibujarImagen(this->scrollButtonDown, NULL, x, y + this->altoAreaFiguras + (this->altoAreaScroll >> 1));
	//}catch(...){
	//}
}

void BotoneraControllerCliente::resizear(){

	//try{
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
		int alt = botonera->getAlturaMax();
		if (botonera->getAlturaMax() == 0){
			alt = 100;
		}
		Superficie* layerFigurasTemp = layerFigurasOrig->scaleSurface(anchoTemp, alt );

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
	//}catch(...){
	//}
}

BotoneraControllerCliente::~BotoneraControllerCliente() {
	//try{
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
	//}catch(...){
	//}
}

void BotoneraControllerCliente::handleEventBotonera(double mouseX, double mouseY, Uint32 type) {
		//Analiza que tipo de accion recibio
	//try{
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
	//}catch(...){
	//}
}

Superficie* BotoneraControllerCliente::getImpresion(){
	//try{
		//Dibuja en el buffer principal (Double Buffer)
		if (this->layerFiguras && this->huboCambios()) {
			//try{
				//Pone los numeritos de cuantas instancias quedan
				this->dibujarCantInstancias();
			//}catch(...){
			//}

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
		//this->setCambio(false);
		return layerPrincipal;
	//}catch(...){
	//	try{
	//		this->resizear();
	//	}catch(...){
	//	}
	//}
}

void BotoneraControllerCliente::agregarBoton(Figura * figura, int cantidadInstancias) {
	//try{
		Imagen * img = new Imagen(figura->getID());
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
	//}catch(...){
	//}
}

void BotoneraControllerCliente::setScrollDirection(int direction) {
	/*try{*/
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
	//}catch(...){
	//	std::cout<<"fallo agregar boton\n"
	//}
}

Figura * BotoneraControllerCliente::obtenerFigura(double x, double y){
	//try{
		this->buttonPressed = true;
		this->numeroFigActual= ((int)(this->botonera->getY() + y - (this->altoAreaScroll >> 1)))/this->botonera->getAltoBoton();
		return this->botonera->obtenerFigura(this->numeroFigActual);
	//}catch(...){
	//	std::cout<<"fallo obtener figura\n"
	//}
}

void BotoneraControllerCliente::restaurarInstanciaActual(){
	/*try{*/
		this->botonera->restaurarInstanciaActual( this->numeroFigActual );
	/*}catch(...){
		std::cout<<"fallo obtener instancia actual\n"
	}*/
}

void BotoneraControllerCliente::restaurarInstancias( std::list<int> numsFigARestaurar ){
	/*try{*/
		this->botonera->restaurarInstancias(numsFigARestaurar);
	//}catch(...){
	//	std::cout<<"fallo restaurar instancias\n"
	//}
}

int BotoneraControllerCliente::getAlto() {
	/*try{*/
		return this->botonera->getAlto();
	//}catch(...){
	//	std::cout<<"fallo getAlto\n"
	//}
	
}

int BotoneraControllerCliente::getAncho() {
	//try{
		return this->botonera->getAncho();
	//}catch(...){
	//	std::cout<<"fallo getAncho\n"
	//}
}

std::list<struct boton> BotoneraControllerCliente::getListaFiguras() {
	//try{
		return this->botonera->getListaFiguras();
	//}catch(...){
	//	std::cout<<"fallo getListaFiguras\n"
	//}
}



void BotoneraControllerCliente::ScrollUp(){
	/*try{*/
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
	//}catch(...){
	//	std::cout<<"fallo scroll up\n"
	//}
}

void BotoneraControllerCliente::ScrollDown(){
	//try{
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
	//}catch(...){
	//	std::cout<<"fallo scroll down\n"
	//}
}



bool BotoneraControllerCliente::agregarBotonesDefault(){
	//try{
		this->agregarBoton(new Arco(0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Canio(0,0,0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Carrito(0,0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Codo(0,0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Escopeta(0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new GloboHelio((double)0,(double)0,CELESTE),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Linea(0,0,0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new PaletaFlipper(0,0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new PelotaBasquet(0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Plataforma(LARGO_PLATAFORMA_DEFAULT,0,0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Polea(0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Soga(0,0,0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Vela(ID_VELA,0,0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Aro(0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Balancin(0,0,ANGULO_BALANCIN_IZQ),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Chinche(0,0),INSTANCIAS_DEFAULT);	
		this->agregarBoton(new CintaTransportadora(3,0,0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Clavo(0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Domino(0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Engranaje(0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Huevo(0,0),INSTANCIAS_DEFAULT); 
		this->agregarBoton(new Motor(0,0),INSTANCIAS_DEFAULT); 
		this->agregarBoton(new MotorRaton(0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new PelotaBowling(0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new PelotaTenis(0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Queso(0,0),INSTANCIAS_DEFAULT); 
		this->agregarBoton(new Tijera(0,0),INSTANCIAS_DEFAULT);
		this->agregarBoton(new Yunque(0,0),INSTANCIAS_DEFAULT);
	//}catch(...){
	//}
	return true;
}

bool BotoneraControllerCliente::estaVacia(){
	/*try{*/
		std::list<struct boton> lista = this->botonera->getListaFiguras();
		return (lista.size()==0);
	//}catch(...){
	//	return true;
	//}
}


void BotoneraControllerCliente::dibujarCantInstancias(){
	//try{
		int altoBoton = botonera->getAltoBoton();
		int cantDeFig = layerFigurasOrig->getAlto()/altoBoton;


		int posBotonX = 0;
		int posBotonY = 0;

		std::list<struct boton> figs = botonera->getListaFiguras();
		std::list<struct boton>::iterator itFig = figs.begin();

		int cantInstancias;
		Imagen* img;
		//solo para copiarla y no cambiar la original
		layerADibujar = layerFiguras->rotarSuperficie(0);

		for(itFig = figs.begin(); itFig != figs.end(); itFig++){
			//try{
				cantInstancias = (*itFig).cantInstancias;

				//convertir a c string
				stringstream ss;
				ss<<cantInstancias;
				string digito =ss.str();
				const char* dig = digito.c_str();

				//dibujar
				img = NULL;
				img = new Imagen(dig,altoBoton*0.2,255,255,255);
				//y un peque�o desplazamiento para que entren bien al boton
				layerADibujar->dibujarImagen(img, NULL, 7, posBotonY+7);

				posBotonY += altoBoton;

				delete img;
			//}catch(...){
			//}
		}
	//}catch(...){
	//}

}