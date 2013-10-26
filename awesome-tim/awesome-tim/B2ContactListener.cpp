#include "B2ContactListener.h"

B2ContactListener::B2ContactListener(void)
{
	listCinta = new PlataformaB2ContactListener();
	listSoga = new SogaB2ContactListener();
	listGlobo = new GloboB2ContactListener();
}

B2ContactListener::~B2ContactListener(void)
{
	delete listCinta;
	delete listSoga;
	delete listGlobo;
}

void B2ContactListener::BeginContact(b2Contact* contact){
	listCinta->BeginContact(contact);
	listSoga->BeginContact(contact);
	listGlobo->BeginContact(contact);
}

void B2ContactListener::EndContact(b2Contact* contact){
	listCinta->EndContact(contact);
	listSoga->EndContact(contact);
	listGlobo->EndContact(contact);
}

void B2ContactListener::terminar(){
	listCinta->terminar();
	listSoga->terminar();
	listGlobo->terminar();
}