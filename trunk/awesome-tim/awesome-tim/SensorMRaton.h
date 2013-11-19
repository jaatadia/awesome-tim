#pragma once

#include "Figura.h"

class SensorMRaton:Figura
{
private:
	//referencia a su motor, como figura o se crea una inclusion circular
	Figura* motorRaton;

public:
	SensorMRaton(Figura* motor):Figura("",new Cuadrado(1,1,1,1,0),false){
		motorRaton = motor;
	}

	~SensorMRaton(void){};

	Figura* getMotor(){return motorRaton;};
};
