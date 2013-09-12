#pragma once

#include "Imprimible.h"
#include "Cambiable.h"
#include "EscalasDeEjes.h"
#include "Juego.h"

class Juego;


 


class Comandos: public Imprimible,public Cambiable
{
private:
	int ancho,alto;
	Superficie* sup;
	Imagen* BotonOK;
	Imagen* BotonSave;
	Imagen* BotonQuit;

	int SEP;

	int ANCHO_TBOX;
	int ALTO_TBOX;
	int X_TBOX;
	int Y_TBOX;
	
	int ANCHO_B_OK;
	int ALTO_B_OK;
	int X_B_OK;
	int Y_B_OK;

	int ANCHO_B_QUIT;
	int ALTO_B_QUIT;
	int X_B_QUIT;
	int Y_B_QUIT;

	int ANCHO_B_SAVE;
	int ALTO_B_SAVE;
	int X_B_SAVE;
	int Y_B_SAVE;
	
	char dir[256];
	int posDirActual;

public:
	Comandos(int ancho,int alto);
	~Comandos(void);
	void agregarLetra(char caracter);
	void borrarLetra();
	Superficie* getImpresion();
	Superficie* getImpresion(EscalasDeEjes * esc);
	void click(double x, double y,Juego* juego);
	void enterKeyPressed(Juego* juego);
	void resizear(EscalasDeEjes* escalas);
private:
	void redraw(EscalasDeEjes* escalas);
	bool in(int x, int y, int ancho,int alto,double x2,double y2);
};
