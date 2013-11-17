#pragma once

#include "Imprimible.h"
#include "Cambiable.h"
#include "EscalasDeEjes.h"
#include "JuegoCliente.h"

class JuegoCliente;


 


class ComandosCliente: public Imprimible,public Cambiable
{
private:
	int anchoOrig,altoOrig;
	int ancho,alto;
	Superficie* sup;
	
//	Imagen* BotonOKOrigApretado;
//	Imagen* BotonSaveOrigApretado;
	Imagen* BotonQuitOrigApretado;
//	Imagen* BotonOKOrigSinApretar;
//	Imagen* BotonSaveOrigSinApretar;
	Imagen* BotonQuitOrigSinApretar;
	
	Imagen* BotonPlayOrigApretado;
	Imagen* BotonPlayOrigSinApretar;
	Imagen* BotonPlayApretado;
	Imagen* BotonPlaySinApretar;

//	Imagen* BotonOKApretado;
//	Imagen* BotonSaveApretado;
	Imagen* BotonQuitApretado;
//	Imagen* BotonOKSinApretar;
//	Imagen* BotonSaveSinApretar;
	Imagen* BotonQuitSinApretar;

	Imagen* ImagenObjetivoOrig;
	Imagen* ImagenObjetivo;

	bool botonOkActivo, botonSaveActivo, botonQuitActivo,botonPlayActivo;

	int SEPX;
	int SEPY;

/*	int ANCHO_TBOX;
	int ALTO_TBOX;
	int X_TBOX;
	int Y_TBOX;
	
	int ANCHO_B_OK;
	int ALTO_B_OK;
	int X_B_OK;
	int Y_B_OK;
*/
	int ANCHO_B_QUIT;
	int ALTO_B_QUIT;
	int X_B_QUIT;
	int Y_B_QUIT;

	int ANCHO_OBJ;
	int ALTO_OBJ;
	int X_OBJ;
	int Y_OBJ;


/*	int ANCHO_B_SAVE;
	int ALTO_B_SAVE;
	int X_B_SAVE;
	int Y_B_SAVE;
*/	
	int ANCHO_B_PLAY;
	int ALTO_B_PLAY;
	int X_B_PLAY;
	int Y_B_PLAY;

	char dir[256];
	int posDirActual;

	bool ready;

public:
	ComandosCliente(int ancho,int alto,std::string id_imagen_texto_objetivo);
	~ComandosCliente(void);
	void agregarLetra(char caracter);
	void borrarLetra();
	Superficie* getImpresion();
	void click(double x, double y,JuegoCliente* juego);
	void release(double x, double y,bool* flag,JuegoCliente* juego);
	void enterKeyPressed(JuegoCliente* juego);
	void resizear();

	void setImagenObjetivo(std::string id_imagen_texto_objetivo);

	void setListoUnpressed();

private:
	void redraw();
	bool in(int x, int y, int ancho,int alto,double x2,double y2);
};
