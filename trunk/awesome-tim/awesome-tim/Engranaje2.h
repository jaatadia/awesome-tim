#include "Engranaje.h"
#include "Constantes.h"
#include "Circulo.h"
#include "VistaFiguraEstatica.h"

class Engranaje2 : public Engranaje
{
private:
	VistaFiguraEstatica* myVista2;
	Engranaje2(const char* id,Dimension* dim,bool flag):Engranaje(id,dim,flag){
		sentido = 1;
		myVista2 = new VistaFiguraEstatica(this,ID_MOTOR);
	};
	
public:
	int sentido;

public:
	Engranaje2(double pos_X,double pos_Y,double radio1 = RADIO_MINENGRANAJE, double angulo = 0):Engranaje(ID_ENGRANAJE2_1,pos_X,pos_Y){
		sentido = 1;
		myVista2 = new VistaFiguraEstatica(this,ID_MOTOR);
	}			
	~Engranaje2(void){
		delete myVista2;
	};
	
	Figura* clonar(){
		Engranaje2* eng = new Engranaje2(ID.c_str(),dimension->clonar(),true);
		eng->setRadio(this->radio1);
		if(this->sentido == -1) eng->shift();
		return eng;
	};

	virtual int getTipoFigura(){return ENGRANAJE2;}
	virtual int getTipoDimension(){return CIRCULO;}

	virtual void shift(){
		this->sentido = -this->sentido;
		delete this->myVista;
		if(sentido == 1) this->ID = ID_ENGRANAJE2_1;
		if(sentido == -1) this->ID = ID_ENGRANAJE2_2;
		this->myVista = new VistaFigura(this);
		this->setCambio(true);
	}
	
	void dibujar(Superficie* super){
		myVista2->dibujar(super);
		myVista->dibujar(super);
		setCambio(false);
	}
};
