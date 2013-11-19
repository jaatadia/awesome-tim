#include "RatonB2ContactListener.h"

RatonB2ContactListener::RatonB2ContactListener(void){
}

RatonB2ContactListener::~RatonB2ContactListener(void){
}
void RatonB2ContactListener::BeginContact(b2Contact* contact){
	
	Figura* fig1 = (Figura*)contact->GetFixtureA()->GetBody()->GetUserData();
	Figura* fig2 = (Figura*)contact->GetFixtureB()->GetBody()->GetUserData();
	
	if((fig1 == NULL)||(fig2 == NULL)) return;

	MotorRaton* raton = NULL;
	//Figura* fig = NULL;
	//b2Body* bodyRaton = NULL;
	//b2Body* bodyFig = NULL;

	//-1 es lo que devuelve la fig auxiliar en el data user del sensor
	if((fig2->getTipoFigura() == QUESO) && (fig1->getTipoFigura() == -1)){
		raton = (MotorRaton*) (((SensorMRaton*)fig1)->getMotor()); 	
		raton->ActivarMotor();
		raton->B2Motor->SetFixedRotation(true);
		raton->B2Motor->SetAngularVelocity(VELOCIDAD_MOTOR*raton->sentido);
		//bodyRaton = contact->GetFixtureA()->GetBody();
		//bodyFig = contact->GetFixtureB()->GetBody();
		//fig = fig2;
	}else if((fig1->getTipoFigura() == QUESO) && (fig2->getTipoFigura() == -1)){
		raton = (MotorRaton*) (((SensorMRaton*)fig2)->getMotor());
		raton->ActivarMotor();
		raton->B2Motor->SetFixedRotation(true);
		raton->B2Motor->SetAngularVelocity(VELOCIDAD_MOTOR*raton->sentido);
		//bodyRaton = contact->GetFixtureB()->GetBody();
		//bodyFig = contact->GetFixtureA()->GetBody();
		//fig = fig1;
	}else{
		return;
	}
}

void RatonB2ContactListener::EndContact(b2Contact* contact){
	
	Figura* fig1 = (Figura*)contact->GetFixtureA()->GetBody()->GetUserData();
	Figura* fig2 = (Figura*)contact->GetFixtureB()->GetBody()->GetUserData();
	
	if((fig1 == NULL)||(fig2 == NULL)) return;

	MotorRaton* raton = NULL;
	//Figura* fig = NULL;
	//b2Body* bodyRaton = NULL;
	//b2Body* bodyFig = NULL;

	//-1 es lo que devuelve la fig auxiliar en el data user del sensor
	if((fig2->getTipoFigura() == QUESO) && (fig1->getTipoFigura() == -1)){
		raton = (MotorRaton*) (((SensorMRaton*)fig1)->getMotor()); 	
		raton->ActivarMotor();
		raton->B2Motor->SetFixedRotation(true);
		raton->B2Motor->SetAngularVelocity(0);
		//bodyRaton = contact->GetFixtureA()->GetBody();
		//bodyFig = contact->GetFixtureB()->GetBody();
		//fig = fig2;
	}else if((fig1->getTipoFigura() == QUESO) && (fig2->getTipoFigura() == -1)){
		raton = (MotorRaton*) (((SensorMRaton*)fig2)->getMotor());
		raton->ActivarMotor();
		raton->B2Motor->SetFixedRotation(true);
		raton->B2Motor->SetAngularVelocity(0);
		//bodyRaton = contact->GetFixtureB()->GetBody();
		//bodyFig = contact->GetFixtureA()->GetBody();
		//fig = fig1;
	}else{
		return;
	}
}

void RatonB2ContactListener::terminar(){
}