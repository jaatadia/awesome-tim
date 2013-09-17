#include "BotoneraController.h"

BotoneraController::BotoneraController(int ancho,int alto, int cantBotonesMostrados, double factorAreaFiguras, double scrollScaleFactor, double buttonScaleFactor) {
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
	this->sup = new Superficie(ancho,alto);
	this->figuraActual = 0;
	this->back = NULL;
	this->setScrollDirection(SCROLL_OFF);
	int scrollSide = (ancho > (this->altoAreaScroll >> 1)) ? (this->altoAreaScroll >> 1) * this->scrollScaleFactor : ancho * this->scrollScaleFactor;
	this->ScrollButtonUp = new Imagen("../images/ScrollButton.png");
	this->ScrollButtonUp = this->ScrollButtonUp->scaleImagen(scrollSide, scrollSide);
	this->ScrollButtonUpPressed = new Imagen("../images/ScrollButtonPressed.jpg");
	this->ScrollButtonUpPressed = this->ScrollButtonUpPressed->scaleImagen(scrollSide, scrollSide);
	this->ScrollButtonDown = this->ScrollButtonUp->rotarImagen(180);
	this->ScrollButtonDownPressed = this->ScrollButtonUpPressed->rotarImagen(180);
}

void BotoneraController::resize(int ancho, int alto){
	this->sup->scaleSurface(ancho, alto);
	this->setCambio(true);
}

BotoneraController::~BotoneraController() {
	if (this->sup) {
		delete (this->sup);
		this->sup = 0;
	}
	if (this->back) {
		delete (this->back);
		this->back = 0;
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
			break;
		case SDL_MOUSEBUTTONUP:
			// Borro aca la figura???
			this->figuraActual = 0;
			this->setScrollDirection(this->SCROLL_OFF);
			this->setCambio(true);
	}

	//Actualiza scroll
	if ((this->scrollBot | this->scrollTop) != 0 && (this->botonera->getAlturaMax() > this->altoAreaFiguras)) {
		this->setCambio(true);
		if (this->scrollBot) {
			int resto = this->botonera->getAlturaMax() - this->altoAreaFiguras - this->botonera->getY();
			int paso = (resto > this->scrollStep) ? this->scrollStep : (this->scrollStep - resto);
			if ((this->botonera->getY()%this->botonera->getAltoBoton()) + paso >= this->botonera->getAltoBoton())
				this->botonera->setIndice(this->botonera->getIndice() + 1);
			this->botonera->setY(this->botonera->getY() + paso);
		}
		else {
			int paso = (this->botonera->getY() > this->scrollStep) ? this->scrollStep : this->botonera->getY();
			if ((this->botonera->getY() - paso) >= 0) {
				if (((this->botonera->getAlturaMax() - this->botonera->getY())%this->botonera->getAltoBoton()) + paso >= this->botonera->getAltoBoton())
					this->botonera->setIndice(this->botonera->getIndice() - 1);
				this->botonera->setY(this->botonera->getY() - paso);
			}
		}
	}
}

Superficie* BotoneraController::getImpresion(EscalasDeEjes* escalas){
	//Dibuja en el buffer principal (Double Buffer)
	if (this->back && this->huboCambios()) {
		this->sup->dibujarCuadradoNegro(0,0,this->getAncho(),this->getAlto());
		this->sup->dibujarImagen(this->ScrollButtonUp, NULL, 0,0);
		Rectangulo rect(this->botonera->getX(), this->botonera->getY(), this->botonera->getAncho(), this->altoAreaFiguras);
		this->sup->dibujarSupreficie(this->back, &rect, 0, (this->altoAreaScroll >> 1));
		this->sup->dibujarImagen(this->ScrollButtonDown, NULL, 0,this->altoAreaFiguras + (this->altoAreaScroll >> 1));
	}
	return sup;
}

Superficie* BotoneraController::getImpresion(){
	//Dibuja en el buffer principal (Double Buffer)
	if (this->back && this->huboCambios()) {

		int x = (this->ScrollButtonUp->getAncho() >= this->botonera->getAncho()) ? 0 : ((this->botonera->getAncho() - this->ScrollButtonUp->getAncho()) >> 1);
		int y = ((this->ScrollButtonUp->getAlto() >= (this->altoAreaScroll >> 1)) ? 0 : (((this->altoAreaScroll >> 1) - this->ScrollButtonUp->getAlto()) >> 1));

		this->sup->dibujarCuadradoNegro(0,0,this->getAncho(),this->getAlto());

		if (this->scrollTop) this->sup->dibujarImagen(this->ScrollButtonUpPressed, NULL, x, y);
		else this->sup->dibujarImagen(this->ScrollButtonUp, NULL, x, y);

		Rectangulo rect(this->botonera->getX(), this->botonera->getY(), this->botonera->getAncho(), this->altoAreaFiguras);

		this->sup->dibujarSupreficie(this->back, &rect, 0, (this->altoAreaScroll >> 1));

		if (this->scrollBot)this->sup->dibujarImagen(this->ScrollButtonDownPressed, NULL, x, y + this->altoAreaFiguras + (this->altoAreaScroll >> 1));
		else this->sup->dibujarImagen(this->ScrollButtonDown, NULL, x, y + this->altoAreaFiguras + (this->altoAreaScroll >> 1));
	}
	return sup;
}

void BotoneraController::agregarBoton(int tipo, int cantidadInstancias, const char * ID) {
	this->lstRutas.push_back(ID);
	Imagen * img = new Imagen(ID);
	int buttonSide = (this->botonera->getAnchoBoton() > this->botonera->getAltoBoton()) ? this->botonera->getAltoBoton() * this->buttonScaleFactor : this->botonera->getAnchoBoton() * this->buttonScaleFactor;
	img = img->scaleImagen(buttonSide, buttonSide);
	Superficie * aux = new Superficie(this->botonera->getAncho(), this->botonera->getAlturaMax() + this->botonera->getAltoBoton());
	Rectangulo rect(0, 0, this->botonera->getAncho(), this->botonera->getAlturaMax());
	if (this->back)
		aux->dibujarSupreficie(this->back, &rect, 0, 0);
	rect.ancho = img->getAncho();
	rect.alto = img->getAlto();
	int x = (img->getAncho() >= this->botonera->getAncho()) ? 0 : ((this->botonera->getAncho() - img->getAncho()) >> 1);
	int y = this->botonera->getAlturaMax() + ((img->getAlto() >= this->botonera->getAltoBoton()) ? 0 : ((this->botonera->getAltoBoton() - img->getAlto()) >> 1));
	aux->dibujarImagen(img,&rect,x,y);
	if(this->back)
		delete (this->back);
	this->back = aux;
	this->botonera->agregarBoton(tipo, cantidadInstancias);
	this->botonera->setAlturaMax(this->botonera->getAlturaMax() + this->botonera->getAltoBoton());
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
	if (this->botonera->getY() >= this->altoAreaScroll && y <= (this->altoAreaScroll + this->altoAreaFiguras))
		return this->botonera->obtenerFigura(this->botonera->getIndice() + ((int)(this->botonera->getY() - this->altoAreaScroll))%this->botonera->getAltoBoton());
	return NULL;
}

int BotoneraController::getAlto() {
	return this->botonera->getAlto();
}

int BotoneraController::getAncho() {
	return this->botonera->getAncho();
}

std::list<int*> BotoneraController::getListaFiguras() {
	return this->botonera->getListaFiguras();
}