#include "PlataformaB2ContactListener.h"
#include "Figura.h"
#include "CintaTransportadora.h"

PlataformaB2ContactListener::PlataformaB2ContactListener(void)
{
}

PlataformaB2ContactListener::~PlataformaB2ContactListener(void)
{
}


void PlataformaB2ContactListener::BeginContact(b2Contact* contact){
	Figura* fig1 = (Figura*)contact->GetFixtureA()->GetBody()->GetUserData();
	Figura* fig2 = (Figura*)contact->GetFixtureA()->GetBody()->GetUserData();
	if((fig1 == NULL)||(fig2 == NULL)) return;
	
	CintaTransportadora* cinta = NULL;
	b2Body* cuerpoCinta;
	b2Body* cuerpo;

	if (fig1->getTipoFigura()==CINTATRANSPORTADORA){
		cinta = (CintaTransportadora*)fig1;
		cuerpoCinta = contact->GetFixtureA()->GetBody();
		cuerpo = contact->GetFixtureB()->GetBody();
	}else if (fig2->getTipoFigura()==CINTATRANSPORTADORA){
		cinta = (CintaTransportadora*)fig2;
		cuerpo = contact->GetFixtureA()->GetBody();
		cuerpoCinta = contact->GetFixtureB()->GetBody();
	}

	if (cinta == NULL) return;

	
	int sentido = 1;
	if (cuerpo->GetPosition().y > cuerpoCinta->GetPosition().y) sentido *= -1; 

	b2JointEdge* edge = cuerpoCinta->GetJointList();
	while(edge->joint->GetType()!=e_revoluteJoint) {edge = edge->next;}
	
	int velCentro = 0;
	if (edge->joint->GetBodyA() == cuerpoCinta){
		velCentro = edge->joint->GetBodyB()->GetAngularVelocity();
	}else{
		velCentro = edge->joint->GetBodyA()->GetAngularVelocity();
	}
	
	if(velCentro == 0) return;

	//cuerpo->ApplyLinearImpulse(b2Vec2(sentido*cuerpo->GetMass()*velCentro,0),cuerpo->GetPosition());
	double velX = sentido*velCentro*VELOCITY_MULTIPLIER;
	double velY = cuerpo->GetLinearVelocity().y+0;
	cuerpo->SetLinearVelocity(b2Vec2(velX,velY));
}

void PlataformaB2ContactListener::EndContact(b2Contact* contact){
	//Figura* fig1 = (Figura*)contact->GetFixtureA()->GetBody()->GetUserData();
	//Figura* fig2 = (Figura*)contact->GetFixtureA()->GetBody()->GetUserData();
	//if((fig1 == NULL)||(fig2 == NULL)) return;
	//
	//CintaTransportadora* cinta = NULL;
	//b2Body* cuerpo;

	//if (fig1->getTipoFigura()==CINTATRANSPORTADORA){
	//	cinta = (CintaTransportadora*)fig1;
	//	cuerpo = contact->GetFixtureA()->GetBody();
	//}else if (fig2->getTipoFigura()==CINTATRANSPORTADORA){
	//	cinta = (CintaTransportadora*)fig2;
	//	cuerpo = contact->GetFixtureB()->GetBody();
	//}

	//if (cinta == NULL) return;

	//std::cout<<"dejo de chocar!!!!\n";
}