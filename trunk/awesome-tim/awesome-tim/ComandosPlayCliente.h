#pragma once

#pragma once

#include "Imprimible.h"
#include "Cambiable.h"
#include "EscalasDeEjes.h"
#include "JuegoPlayCliente.h"

class JuegoPlayCliente;

class ComandosPlayCliente: public Imprimible,public Cambiable
{
private:
	int anchoOrig,altoOrig;
	int ancho,alto;
	Superficie* sup;
	
	Imagen* BotonStopOrigApretado;
	Imagen* BotonStopOrigSinApretar;
	Imagen* BotonStopApretado;
	Imagen* BotonStopSinApretar;
	
	bool botonStopActivo;

	int SEPX;
	int SEPY;

	int ANCHO_B_STOP;
	int ALTO_B_STOP;
	int X_B_STOP;
	int Y_B_STOP;
	
public:
	ComandosPlayCliente(int ancho,int alto);
	~ComandosPlayCliente(void);

	void click(double x, double y,JuegoPlayCliente* juego);
	void release(double x, double y,bool* flag,JuegoPlayCliente* juego);
	Superficie* getImpresion();
	void resizear();
	void dibujate(Superficie* sup,int xIni,int yIni);

private:
	void redraw();
	bool in(int x, int y, int ancho,int alto,double x2,double y2);

};
