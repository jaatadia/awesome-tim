#include "Engranaje.h"
#include "Constantes.h"
#include "Circulo.h"
#include "VistaFiguraEstatica.h"

class Motor : public Engranaje
{
private:
	VistaFiguraEstatica* myVista2;
	Motor(const char* id,Dimension* dim,bool flag):Engranaje(id,dim,flag){
	sentido = 1;
	myVista2 = new VistaFiguraEstatica(this,ID_MOTOR);
	};
	
public:
	int sentido;

public:
	Motor(double pos_X,double pos_Y,double radio1 = RADIO_MINENGRANAJE, double angulo = 0):Engranaje(ID_MOTOR_1,pos_X,pos_Y,radio1){
		sentido = 1;
		myVista2 = new VistaFiguraEstatica(this,ID_MOTOR);
	}			
	~Motor(void){
		delete myVista2;
	};
	
	Figura* clonar(){
		Motor* eng = new Motor(ID.c_str(),dimension->clonar(),true);
		eng->setRadio(this->radio1);
		if(this->sentido == -1) eng->shift();
		return eng;
	};

	virtual int getTipoFigura(){return MOTOR;}
	virtual int getTipoDimension(){return CIRCULO;}

	virtual void shift(){
		this->sentido = -this->sentido;
		delete this->myVista;
		if(sentido == 1) this->ID = ID_MOTOR_1;
		if(sentido == -1) this->ID = ID_MOTOR_2;
		this->myVista = new VistaFigura(this);
		this->setCambio(true);
	}
	
	void dibujar(Superficie* super){
		myVista2->dibujar(super);
		myVista->dibujar(super);
		setCambio(false);
	}

	bool choqueConFigura(Figura* fig){

		//me fijo si fig que me pasaron choca con esta dimension (para cada una que tenga en este caso solo 1)
		bool choca = false;

		Dimension* dimAux = new Cuadrado(dimension->getAncho(),dimension->getAncho(),dimension->getX(),dimension->getY(),dimension->getAngulo());

		Dimension* dimensionRotada = dimAux->rotarDimension(dimension->getX(),dimension->getY(),dimension->getAngulo());

		choca = fig->choqueConDimension(dimensionRotada);
		//caso en que una esta dentro de la otra
		if ( (!choca) && fig->esMiPosicion(this->getDimension()->getX() , this->getDimension()->getY()) ){
			choca = true;
		}

		delete dimensionRotada;
		delete dimAux;

		return choca;
	}


	bool choqueConDimension(Dimension* dim){

		Dimension* dimAux = new Cuadrado(dimension->getAncho(),dimension->getAncho(),dimension->getX(),dimension->getY(),dimension->getAngulo());
		
		bool choca = dimAux->choqueConDimension(dim);

		delete dimAux; 

		return choca;
	}

	virtual bool cortaSoga(){return false;}
	virtual bool pinchaGlobo(){return false;}
};
