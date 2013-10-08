#include "Engranaje.h"
#include "Constantes.h"
#include "Circulo.h"

class Engranaje2 : public Engranaje
{
private:
	Engranaje2(const char* id,Dimension* dim,bool flag):Engranaje(id,dim,flag){};
public:
	Engranaje2(double pos_X,double pos_Y,double radio1 = RADIO_MINENGRANAJE, double angulo = 0):Engranaje(pos_X,pos_Y){}			
	~Engranaje2(void){};
	virtual int getTipoDimension(){
		return ENGRANAJE2;
	};
	
	Figura* clonar(){
		Engranaje* eng = new Engranaje2(ID.c_str(),dimension->clonar(),true);
		eng->setRadio(this->radio1);
		return eng;
	};
};
