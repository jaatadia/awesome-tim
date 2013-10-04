#pragma once

class Cambiable
{
private:
	bool cambios;
public:
	Cambiable(){cambios = true;};
	virtual ~Cambiable(){};
	void setCambio(bool state){cambios = state;};
	bool huboCambios(){return cambios;};
	
};
