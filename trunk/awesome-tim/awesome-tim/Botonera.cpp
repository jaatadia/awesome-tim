#include "Botonera.h"

Botonera::Botonera(int ancho,int alto, int cantBotonesMostrados, double factorAreaFiguras){
	this->ancho = ancho;
	this->alto = alto;
	this->x = this->y = this->scrollBot = this->scrollTop = 0;
	this->altoAreaFiguras = factorAreaFiguras*this->alto;
	this->altoAreaScroll = this->alto - this->altoAreaFiguras;
	this->altoBoton = this->altoAreaFiguras / cantBotonesMostrados;
	this->scrollStep = this->altoBoton / this->FACTOR_SCROLL;
	this->alturaMax = 0;
	this->indice = 0;
	this->figuraActual = 0;
	this->supFiguraActual = 0;
	sup = new Superficie(ancho,alto);
}

Superficie* Botonera::getImpresion(){
	return sup;
}

void Botonera::updateBotonera(){
	if (this->scrollBot & this->scrollTop == 0) {
		if (this->scrollBot) {
			int resto = this->alturaMax - this->y - this->altoAreaFiguras;
			int paso = (resto > this->scrollStep) ? this->scrollStep : (this->scrollStep - resto);
			if ((this->y%this->altoBoton) + paso >= this->altoBoton)
					++(this->indice);
			this->y += paso;
			this->scrollBot = false;
		}
		else {
			int paso = (this->y > this->scrollStep) ? this->scrollStep : this->y;
			if ((this->y - paso) >= 0) {
				if (((this->alturaMax - this->y)%this->altoBoton) + paso >= this->altoBoton)
					--(this->indice);
				this->y -= paso;
			}
			this->scrollTop = false;
		}
	}
	if (this->back) {
		//Falta limpiar sup
		Rectangulo rect(this->x, this->y, this->ancho, this->altoAreaFiguras);
		this->sup->dibujarSupreficie(this->back, &rect, 0, 0);
	}
	//Falta renderear flechas scroll
}

void Botonera::agregarBoton(int tipo, Superficie *img) {
	Superficie * aux = new Superficie(this->ancho, this->alturaMax + this->altoBoton);
	Rectangulo rect(0, 0, this->ancho, this->alturaMax);
	if (this->back)
		aux->dibujarSupreficie(this->back, &rect, 0, 0);
	rect.ancho = img->getAncho();
	rect.alto = img->getAlto();
	int x = (img->getAncho() >= this->ancho) ? 0 : (this->ancho - img->getAncho());
	int y = this->alturaMax + ((img->getAlto() >= this->altoBoton) ? 0 : (this->altoBoton - img->getAlto()));
	aux->dibujarSupreficie(img, &rect, x, y);
	this->back = aux;
	this->lstFiguras.push_back(tipo);
	this->alturaMax += this->altoBoton;
}

void Botonera::setScrollDirection(int direction) {
	switch (direction) {
		case this->SCROLL_BOT:
			this->scrollBot = true;
			this->scrollTop = false;
			break;
		case this->SCROLL_TOP:
			this->scrollBot = false;
			this->scrollTop = true;
			break;
	}
}

Figura * Botonera::obtenerFigura(double x, double y){
	Figura * retorno = 0;
	if (y >= this->altoAreaScroll && y <= (this->altoAreaScroll + this->altoAreaFiguras)) {
		int numeroFigura = this->indice + ((int)(y - this->altoAreaScroll))%this->altoBoton;
		std::list<int>::iterator itFig = this->lstFiguras.begin();
		for (int i = 0; itFig != this->lstFiguras.end(); i++)
		{
			if (i == numeroFigura)
				continue;
			++itFig;
		}
		switch (*(itFig)) {
			case this->TRIANGULO:
				//retorno = new Triangulo();
				cout << "triangulo" << endl;
				break;
			case this->CUADRADO:
				cout << "cuadrado" << endl;
				break;
			case this->CIRCULO:
				cout << "circulo" << endl;
				break;
		}
	}
	return retorno;
}

Botonera::~Botonera() {
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
	if (this->figuraActual) {
		delete (this->figuraActual);
		this->figuraActual = 0;
	}
	this->lstFiguras.clear();
}

Superficie* Botonera::getImpresion(EscalasDeEjes* escalas){
	return sup;
}