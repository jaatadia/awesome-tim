#include "FactoryFiguras.h"
#include "PelotaBasquet.h"
#include "PelotaBowling.h"
#include "GloboHelio.h"
#include "Balancin.h"
#include "Soga.h"
#include "Plataforma.h"
#include "PelotaTenis.h"
#include "CintaTransportadora.h"
#include "Motor.h"
#include "Linea.h"
#include "Vela.h"
#include "Polea.h"
#include "Yunque.h"
#include "Clavo.h"
#include "Tijera.h"
#include "Huevo.h"
#include "Domino.h"
#include "Chinche.h"
#include "Aro.h"
#include "Carrito.h"
#include "PaletaFlipper.h"
#include "Queso.h"
#include "Arco.h"
#include "Flecha.h"
#include "Escopeta.h"
#include "Bala.h"
#include "CarroAtable.h"
#include "MotorRaton.h"
#include "Canio.h"
#include "Codo.h"


Figura* FactoryFiguras::create(CreateFigureMessage* msg){
	Figura* fig = NULL;
	switch(msg->getFigureType()){
		case PELOTABASQUET:
			fig = new PelotaBasquet(msg->getX(),msg->getY(),msg->getAngle());
			break;
		case PELOTABOWLING:
			fig = new PelotaBowling(msg->getX(),msg->getY(),msg->getAngle());
			break;
		case GLOBOHELIO:
			fig = new GloboHelio(msg->getX(),msg->getY(),msg->getData1());
			break;
		case BALANCIN:
			fig = new Balancin(msg->getX(),msg->getY(),msg->getAngle());
			break;
		case SOGA:
			fig = new Soga(msg->getX(),msg->getY(),msg->getX(),msg->getY());
			break;
		case PLATAFORMA:
			fig = new Plataforma(msg->getData1(),msg->getX(),msg->getY(),msg->getAngle());
			break;
		case PELOTATENIS:
			fig = new PelotaTenis(msg->getX(),msg->getY());
			break;
		case ENGRANAJE:
			fig = new Engranaje(msg->getX(),msg->getY());
			break;
		case CINTATRANSPORTADORA:
			fig = new CintaTransportadora(msg->getData1(),msg->getX(),msg->getY(),msg->getAngle());
			break;
		case MOTOR:
			fig = new Motor(msg->getX(),msg->getY());
			break;
		case LINEA:
			fig = new Linea(msg->getX(),msg->getY(),msg->getX(),msg->getY());
			break;
		case VELA:
			fig = new Vela(ID_VELA,msg->getX(),msg->getY(),msg->getAngle());
			break;
		case POLEA:
			fig = new Polea(msg->getX(),msg->getY());
			break;
		case YUNQUE:
			fig = new Yunque(msg->getX(),msg->getY());
			break;
		case CLAVO:
			fig = new Clavo(msg->getX(),msg->getY());
			break;
		case TIJERA:
			fig = new Tijera(msg->getX(),msg->getY(),msg->getAngle());
			break;
		case HUEVO:
			fig = new Huevo(msg->getX(),msg->getY());
			break;
		case DOMINO:
			fig = new Domino(msg->getX(),msg->getY());
			break;
		case CHINCHE:
			fig = new Chinche(msg->getX(),msg->getY());
			break;
		case ARO:
			fig = new Aro(msg->getX(),msg->getY());
			break;
		case CARRITO:
			fig = new Carrito(msg->getX(),msg->getY(),msg->getAngle());
			break;
		case PALETA:
			fig = new PaletaFlipper(msg->getX(),msg->getY(),msg->getData1());
			break;
		case QUESO:
			fig = new Queso(msg->getX(),msg->getY());
			break;
		case ARCO:
			fig = new Arco(msg->getX(),msg->getY(),msg->getAngle());
			break;
		case FLECHA:
			fig = new Flecha(msg->getX(),msg->getY(),msg->getAngle(),0,0);
			break;
		case ESCOPETA:
			fig = new Escopeta(msg->getX(),msg->getY(),msg->getAngle());
			break;
		case BALA:
			fig = new Bala(msg->getX(),msg->getY(),msg->getAngle(),0,0);
			break;
		case CARRO_ATABLE:
			fig = new CarroAtable(msg->getX(),msg->getY());
			break;
		case MOTOR_RATON:
			fig = new MotorRaton(msg->getX(),msg->getY());
			break;
		case CANIO:
			fig = new Canio(msg->getData1(),msg->getX(),msg->getY(),msg->getAngle());
			break;
		case CODO:
			fig = new Codo(msg->getX(),msg->getY(),msg->getAngle());
			break;
	}
	
	if (fig!=NULL){
		fig->numero = msg->getFigureID();
	}

	return fig;
} 
