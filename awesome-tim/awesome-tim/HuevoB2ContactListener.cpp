#include "HuevoB2ContactListener.h"
#include "Huevo.h"

HuevoB2ContactListener::HuevoB2ContactListener(void){}

HuevoB2ContactListener::~HuevoB2ContactListener(void){}

void HuevoB2ContactListener::BeginContact(b2Contact* contact){
	
	Figura* fig1 = (Figura*)contact->GetFixtureA()->GetBody()->GetUserData();
	Figura* fig2 = (Figura*)contact->GetFixtureB()->GetBody()->GetUserData();
	
	if((fig1 == NULL)||(fig2 == NULL)) return;
	
	Huevo* huevo = NULL;
	Figura* fig = NULL;
	b2Body* body = NULL;
	if(fig1->getTipoFigura() == HUEVO){
		huevo = (Huevo*) fig1; 
		body = contact->GetFixtureA()->GetBody();
		fig = fig2;
	}else if(fig2->getTipoFigura() == HUEVO){
		huevo = (Huevo*) fig2;
		body = contact->GetFixtureB()->GetBody();
		fig = fig1;
	}else{
		return;
	}

	if(fig->rompeHuevo(huevo->getDimension())){
		huevo->romper();
	}
}

void HuevoB2ContactListener::EndContact(b2Contact* contact){
}

void HuevoB2ContactListener::terminar(){
}