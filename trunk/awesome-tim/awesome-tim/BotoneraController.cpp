#include "BotoneraController.h"

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
//olvidate de mantener una relacion cuadrada porque el layer de figuras se deforma segun el resize asique nunca encajarian
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

	if (this->supFiguraActual) {
		delete (this->supFiguraActual);
		this->supFiguraActual = 0;
	}
	if (this->botonera) {
		delete (this->botonera);
		this->botonera = 0;
	}
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
			// Borro aca la figura???
			this->figuraActual = 0;
			this->setScrollDirection(this->SCROLL_OFF);
			this->buttonPressed = false;
			this->setCambio(true);
	}
}

Superficie* BotoneraController::getImpresion(){
	//Dibuja en el buffer principal (Double Buffer)
	if (this->layerFiguras && this->huboCambios()) {

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
		this->layerPrincipal->dibujarSupreficie(this->layerFiguras, &rect, 0, (this->altoAreaScroll >> 1));

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

	return layerPrincipal;
}

void BotoneraController::agregarBoton(Figura * figura, int cantidadInstancias) {
	Imagen * img = new Imagen(figura->getID());
	int buttonSide = (this->botonera->getAnchoBoton() > this->botonera->getAltoBoton()) ? this->botonera->getAltoBoton() * this->buttonScaleFactor : this->botonera->getAnchoBoton() * this->buttonScaleFactor;
	img = img->scaleImagen(buttonSide, buttonSide);
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

int BotoneraController::getAlto() {
	return this->botonera->getAlto();
}

int BotoneraController::getAncho() {
	return this->botonera->getAncho();
}

std::list<map<Figura *, int>> BotoneraController::getListaFiguras() {
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

bool BotoneraController::agregarBotonesDefault(){
	
	const char* ID = "../images/triangulo.png";
	Imagen* img = new Imagen(ID);
	Figura* fig = new Figura(ID,new Triangulo(0,0,0,10,10));
	Contenedor::putMultimedia(ID,img);
	this->agregarBoton(fig,100);
	
	ID = "../images/Cuadrado.png";
	img = new Imagen(ID);
	fig = new Figura(ID,new Cuadrado(20,20,0,0,0));
	Contenedor::putMultimedia(ID,img);
	this->agregarBoton(fig,100);
	
	ID = "../images/Pelota-Basket.png";
	img = new Imagen(ID);
	fig = new Figura(ID,new PelotaBasquet(10,0,0,0));
	Contenedor::putMultimedia(ID,img);
	this->agregarBoton(fig,100);

	ID = "../images/Ptriangulo.png";
	img = new Imagen(ID);
	fig = new Figura(ID,new PoligonoRegular(0,0,10,3,0));
	Contenedor::putMultimedia(ID,img);
	this->agregarBoton(fig,100);
	
	ID = "../images/Pcuadrado.png";
	img = new Imagen(ID);
	fig = new Figura(ID,new PoligonoRegular(0,0,10,4,0));
	Contenedor::putMultimedia(ID,img);
	this->agregarBoton(fig,100);

	ID = "../images/Ppentagono.png";
	img = new Imagen(ID);
	fig = new Figura(ID,new PoligonoRegular(0,0,10,5,0));
	Contenedor::putMultimedia(ID,img);
	this->agregarBoton(fig,100);

	ID = "../images/Phexagono.png";
	img = new Imagen(ID);
	fig = new Figura(ID,new PoligonoRegular(0,0,10,6,0));
	Contenedor::putMultimedia(ID,img);
	this->agregarBoton(fig,100);

	ID = "../images/Pheptagono.png";
	img = new Imagen(ID);
	fig = new Figura(ID,new PoligonoRegular(0,0,10,7,0));
	Contenedor::putMultimedia(ID,img);
	this->agregarBoton(fig,100);

	ID = "../images/Poctogono.png";
	img = new Imagen(ID);
	fig = new Figura(ID,new PoligonoRegular(0,0,10,6,0));
	Contenedor::putMultimedia(ID,img);
	this->agregarBoton(fig,100);

	return true;
}

bool BotoneraController::estaVacia(){
	std::list<map<Figura *, int>> lista = this->botonera->getListaFiguras();
	return (lista.size()==0);
}