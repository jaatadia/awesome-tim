#include "SensorB2ContactListener.h"

SensorB2ContactListener::SensorB2ContactListener(void){
}

SensorB2ContactListener::~SensorB2ContactListener(void){
}
void BeginContact(b2Contact* contact){

	Figura* fig1 = (Figura*)contact->GetFixtureA()->GetBody()->GetUserData();
	Figura* fig2 = (Figura*)contact->GetFixtureB()->GetBody()->GetUserData();
	
	if((fig1 == NULL)||(fig2 == NULL)) return;


}
void EndContact(b2Contact* contact){
}
void terminar(){
}