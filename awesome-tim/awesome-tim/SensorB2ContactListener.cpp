#include "SensorB2ContactListener.h"

Figura** SensorB2ContactListener::vector = NULL;

SensorB2ContactListener::SensorB2ContactListener(void){
}

SensorB2ContactListener::~SensorB2ContactListener(void){
}
void SensorB2ContactListener::BeginContact(b2Contact* contact){

	Figura* fig1 = (Figura*)contact->GetFixtureA()->GetBody()->GetUserData();
	Figura* fig2 = (Figura*)contact->GetFixtureB()->GetBody()->GetUserData();
	
	if((fig1 == NULL)||(fig2 == NULL)) return;

	FiguraSensor* sensor = NULL;
	Figura* fig = NULL;
	//b2Body* bodySensor = NULL;
	//b2Body* bodyFig = NULL;

	if(fig1->getTipoFigura() == FIG_SENSOR){
		sensor = (FiguraSensor*) fig1; 
		//bodySensor = contact->GetFixtureA()->GetBody();
		//bodyFig = contact->GetFixtureB()->GetBody();
		fig = fig2;

	} else if(fig2->getTipoFigura() == FIG_SENSOR){
		sensor = (FiguraSensor*) fig2;
		//bodySensor = contact->GetFixtureB()->GetBody();
		//bodyFig = contact->GetFixtureA()->GetBody();
		fig = fig1;
		}else{
			return;
		}
	
	switch (fig->getTipoFigura()){

		case QUESO:{
			sensor->accionarMotor(vector);
			break;
		}
		case GLOBOHELIO:{
			sensor->cumplirObjetivo(vector,fig);
			break;
		}
		case PELOTATENIS:{
			sensor->cumplirObjetivo(vector,fig);
			break;
		}
		case PELOTABASQUET:{
			sensor->cumplirObjetivo(vector,fig);
			break;
		}
	}
}
void SensorB2ContactListener::EndContact(b2Contact* contact){
}
void SensorB2ContactListener::terminar(){
}