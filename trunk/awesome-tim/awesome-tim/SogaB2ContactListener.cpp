#include "SogaB2ContactListener.h"
#include "Figura.h"
#include "PedacitoSoga.h"

SogaB2ContactListener::SogaB2ContactListener(void)
{
}

SogaB2ContactListener::~SogaB2ContactListener(void)
{
}

void SogaB2ContactListener::BeginContact(b2Contact* contact){
	Figura* fig1 = (Figura*)contact->GetFixtureA()->GetBody()->GetUserData();
	Figura* fig2 = (Figura*)contact->GetFixtureB()->GetBody()->GetUserData();
	if((fig1 == NULL)||(fig2 == NULL)) return;
	
	PedacitoSoga* soga = NULL;
	Figura* fig = NULL;

	if (fig1->getTipoFigura()==PEDACITOSOGA){
		soga = (PedacitoSoga*)fig1;
		fig = fig2;
	}else if (fig2->getTipoFigura()==PEDACITOSOGA){
		soga = (PedacitoSoga*)fig2;
		fig = fig1;
	}

	if (soga == NULL) return;

	if (fig->cortaSoga()){
		mundo = contact->GetFixtureA()->GetBody()->GetWorld();
		
		b2Joint* jsoga = soga->jointSoga;

		//me fijo si existe la soga
		b2Joint* joint = mundo->GetJointList();
		bool encontrado = false;
		while((!encontrado )&&(joint!=NULL)){
			if(joint == jsoga) encontrado = true;
			joint = joint->GetNext();
		}
		if(!encontrado) return;
		
		//me fijo si no la estoy por borrar ya
		encontrado = false;
		std::list<b2Joint*>::iterator iter = lista.begin();
		while((iter!=lista.end())&&(!encontrado)){
			if((*iter)==jsoga) encontrado = true;
			iter++;
		}
		if(encontrado) return;

		lista.push_back(soga->jointSoga);
		if (soga->pedacitoIzq->getTipoFigura()==PEDACITOSOGA){
			lista.push_back(soga->jointIzq);
		}else{
			lista.push_back(soga->jointDer);
		}
	}
}

void SogaB2ContactListener::EndContact(b2Contact* contact){
}

void SogaB2ContactListener::terminar(){
	while(lista.size()!=0){
		mundo->DestroyJoint(lista.back());
		lista.pop_back();
	}
}