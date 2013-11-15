#include "SensorB2ContactListener.h"

SensorB2ContactListener::SensorB2ContactListener(void){
}

SensorB2ContactListener::~SensorB2ContactListener(void){
}
void SensorB2ContactListener::BeginContact(b2Contact* contact){

	Figura* fig1 = (Figura*)contact->GetFixtureA()->GetBody()->GetUserData();
	Figura* fig2 = (Figura*)contact->GetFixtureB()->GetBody()->GetUserData();
	
	if((fig1 == NULL)||(fig2 == NULL)) return;


}
void SensorB2ContactListener::EndContact(b2Contact* contact){
}
void SensorB2ContactListener::terminar(){
}