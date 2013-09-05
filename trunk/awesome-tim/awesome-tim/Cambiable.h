#pragma once

class Cambiable
{
private:
	bool cambios;
public:
	void setCambio(bool state){cambios = state;}
	bool huboCambios(){return cambios;}
	
};
