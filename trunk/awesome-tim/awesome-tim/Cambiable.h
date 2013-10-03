#pragma once

class Cambiable
{
private:
	bool cambios;
public:
	//virtual ~Cambiable(){};
	void setCambio(bool state){cambios = state;}
	bool huboCambios(){return cambios;}
	
};
