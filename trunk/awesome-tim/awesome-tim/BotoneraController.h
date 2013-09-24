#ifndef __BOTONERACONTROLLER_H__
#define __BOTONERACONTROLLER_H__

#include "Botonera.h"
#include "Superficie.h"
#include "Imprimible.h"
#include "Cambiable.h"
#include "Figura.h"
#include "EscalasDeEjes.h"
#include "Contenedor.h"
#include "Triangulo.h"
#include "Cuadrado.h"
#include "Circulo.h"
#include "PoligonoRegular.h"
#include <iostream>

using namespace std;

class BotoneraController: public Imprimible, public Cambiable
{
private:

	static const int COLOR_FONDO = 255;

	Botonera * botonera;
	Superficie * layerPrincipal;
	Superficie * layerFiguras;
	Superficie * layerFigurasOrig;
	Superficie * layerScroll;
	Superficie * supFiguraActual;
	Imagen * scrollButtonUp;
	Imagen * scrollButtonUpPressed;
	Imagen * scrollButtonDown;
	Imagen * scrollButtonDownPressed;
	Imagen * squareButton;
	Imagen * squareButtonPressed;
	Figura * figuraActual;
	bool scrollTop, scrollBot, buttonPressed;
	int scrollStep, altoAreaScroll, altoAreaFiguras, scrollX, scrollY,cantBotonesMostradosOrig, numeroFigActual;
	double factorAreaFiguras, scrollScaleFactor, buttonScaleFactor;
	Figura * obtenerFigura(double x, double y);

	double anchoOriginal,altoOriginal;

public:
	static const int FACTOR_SCROLL = 10;
	static const int SCROLL_OFF  = 0;
	static const int SCROLL_TOP = SCROLL_OFF + 1;
	static const int SCROLL_BOT = SCROLL_TOP + 1;
	BotoneraController(int ancho,int alto, int cantBotonesMostrados, double factorAreaFiguras = 0.8, double scrollScaleFactor = 0.8, double buttonScaleFactor = 0.5);
	~BotoneraController(void);
	Superficie* getImpresion();
	void handleEventBotonera(double mouseX, double mouseY, Uint32 type);
	void agregarBoton(Figura * figura, int cantidadInstancias);
	void setScrollDirection(int direction);

	void setFactorAreaFiguras(double factorAreaFiguras) {this->factorAreaFiguras = factorAreaFiguras;}
	void setScrollScaleFactor(double scrollScaleFactor) {this->scrollScaleFactor = scrollScaleFactor;}
	void setButtonScaleFactor(double buttonScaleFactor) {this->buttonScaleFactor = buttonScaleFactor;}

	Figura * obtenerFiguraActual() {return this->figuraActual;}
	void restaurarInstanciaActual();

	int getAncho();
	int getAlto();
	std::list<map<Figura *, int>> getListaFiguras();

	bool estaVacia();

	void ScrollUp();
	void ScrollDown();

	bool agregarBotonesDefault();



	void resizear();
};
#endif //__BOTONERACONTROLLER_H__