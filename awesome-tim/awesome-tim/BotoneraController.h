#ifndef __BOTONERACONTROLLER_H__
#define __BOTONERACONTROLLER_H__

#include "Botonera.h"
#include "Superficie.h"
#include "Imprimible.h"
#include "Cambiable.h"
#include "Figura.h"

class BotoneraController: public Imprimible, public Cambiable
{
private:
	Botonera * botonera;
	Superficie * sup;
	Superficie * back;
	Superficie * supFiguraActual;
	Imagen * ScrollButtonUp;
	Imagen * ScrollButtonUpPressed;
	Imagen * ScrollButtonDown;
	Imagen * ScrollButtonDownPressed;
	Figura * figuraActual;
	bool scrollTop, scrollBot;
	int scrollStep, altoAreaScroll, altoAreaFiguras, scrollX, scrollY;
	double factorAreaFiguras, scrollScaleFactor, buttonScaleFactor;
	Figura * obtenerFigura(double x, double y);
	std::list<const char *> lstRutas;

public:
	static const int FACTOR_SCROLL = 10;
	static const int SCROLL_OFF  = 0;
	static const int SCROLL_TOP = SCROLL_OFF + 1;
	static const int SCROLL_BOT = SCROLL_TOP + 1;
	BotoneraController(int ancho,int alto, int cantBotonesMostrados, double factorAreaFiguras = 0.8, double scrollScaleFactor = 0.8, double buttonScaleFactor = 0.8);
	~BotoneraController(void);
	Superficie* getImpresion();
	Superficie* getImpresion(EscalasDeEjes* escalas);
	void handleEventBotonera(double mouseX, double mouseY, Uint32 type);
	void agregarBoton(int tipo, int cantidadInstancias, const char * ID);
	void setScrollDirection(int direction);

	void setFactorAreaFiguras(double factorAreaFiguras) {this->factorAreaFiguras = factorAreaFiguras;}
	void setScrollScaleFactor(double scrollScaleFactor) {this->scrollScaleFactor = scrollScaleFactor;}
	void setButtonScaleFactor(double buttonScaleFactor) {this->buttonScaleFactor = buttonScaleFactor;}

	Figura * obtenerFiguraActual() {return this->figuraActual;}
	int getAncho();
	int getAlto();
	void resize(int ancho, int alto);
	std::list<int*> getListaFiguras();
};
#endif //__BOTONERACONTROLLER_H__