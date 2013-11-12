#include "HuevoB2ContactListener.h"
#include "Huevo.h"
#include "Constantes.h"

HuevoB2ContactListener::HuevoB2ContactListener(void){}

HuevoB2ContactListener::~HuevoB2ContactListener(void){}

void HuevoB2ContactListener::BeginContact(b2Contact* contact){
	
	Figura* fig1 = (Figura*)contact->GetFixtureA()->GetBody()->GetUserData();
	Figura* fig2 = (Figura*)contact->GetFixtureB()->GetBody()->GetUserData();
	
	if((fig1 == NULL)||(fig2 == NULL)) return;

	Huevo* huevo = NULL;
	Figura* fig = NULL;
	b2Body* bodyHuevo = NULL;
	b2Body* bodyFig = NULL;

	if(fig1->getTipoFigura() == HUEVO){
		huevo = (Huevo*) fig1; 
		bodyHuevo = contact->GetFixtureA()->GetBody();
		bodyFig = contact->GetFixtureB()->GetBody();
		fig = fig2;
	}else if(fig2->getTipoFigura() == HUEVO){
		huevo = (Huevo*) fig2;
		bodyHuevo = contact->GetFixtureB()->GetBody();
		bodyFig = contact->GetFixtureA()->GetBody();
		fig = fig1;
	}else{
		return;
	}

	if(!fig->rompeHuevo(huevo->getDimension())){
		return;
	}

	b2Vec2 velocityHuevo = bodyHuevo->GetLinearVelocity();

	int velYHuevo = velocityHuevo.y;

	b2Vec2 velocityFig = bodyFig->GetLinearVelocity();

	int velXFig = velocityFig.x;
	int velYFig = velocityFig.y;

	bool hayMovimientoQueRompa = ((velYHuevo > VELOCIDAD_MIN_RUPTURA) || (velYFig > VELOCIDAD_MIN_RUPTURA) || (velXFig > VELOCIDAD_MIN_RUPTURA) );

	if (hayMovimientoQueRompa)
		huevo->romper();
}

void HuevoB2ContactListener::EndContact(b2Contact* contact){
}

void HuevoB2ContactListener::terminar(){
}