#pragma once
#include "client.h"

#include "MEstados.h"
#include "ErrorLogHandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include<sys/timeb.h>
#include "Constantes.h"

#include "Contenedor.h"
#include "GeneradorYaml.h"

#define RUTA_DEFAULT_IN "../yaml/archivoDefault.yml"
#define RUTA_DEFAULT_OUT "../yaml/nuevoJuego.yml"

class ClientTIM :
	public Client
{
public:
	ClientTIM(void);
	~ClientTIM(void);
protected:
	virtual void initThread(){};
	virtual void run(char* rutaIn, char* rutaOut);
	virtual void flushThread(){};
};
