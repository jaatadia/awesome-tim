#pragma once

class Contenedor
{
public:
	Contenedor(void);
	~Contenedor(void);

	void putMultimedia(unsigned int ID,void* medio);
	void* getMultimedia(unsigned int ID);
};
