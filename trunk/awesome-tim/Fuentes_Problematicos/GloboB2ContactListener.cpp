#include "GloboB2ContactListener.h"
#include "GloboHelio.h"

GloboB2ContactListener::GloboB2ContactListener(void)
{
}

GloboB2ContactListener::~GloboB2ContactListener(void)
{
}

void GloboB2ContactListener::BeginContact(b2Contact* contact){
	
	Figura* fig1 = (Figura*)contact->GetFixtureA()->GetBody()->GetUserData();
	Figura* fig2 = (Figura*)contact->GetFixtureB()->GetBody()->GetUserData();
	
	if((fig1 == NULL)||(fig2 == NULL)) return;
	
	GloboHelio* globo = NULL;
	Figura* fig = NULL;
	b2Body* body = NULL;
	if(fig1->getTipoFigura()==GLOBOHELIO){
		globo = (GloboHelio*) fig1; 
		body = contact->GetFixtureA()->GetBody();
		fig = fig2;
	}else if(fig2->getTipoFigura()==GLOBOHELIO){
		globo = (GloboHelio*) fig2;
		body = contact->GetFixtureB()->GetBody();
		fig = fig1;
	}else{
		return;
	}

	if(fig->pinchaGlobo(globo->getDimension())){
		globo->pinchar();
	}
}

void GloboB2ContactListener::EndContact(b2Contact* contact){
}

void GloboB2ContactListener::terminar(){
}