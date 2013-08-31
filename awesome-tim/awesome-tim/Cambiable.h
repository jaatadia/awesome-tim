#pragma once

class Cambiable
{
private:
	bool cambios;
public:
	void cambio(){cambios = true;}
	void noCambio(){cambios = false;}
	bool huboCambios(){return cambios;}
	
};
