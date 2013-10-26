#pragma once

#include "Box2D/Box2D.h"
#include "PlataformaB2ContactListener.h"
#include "SogaB2ContactListener.h"
#include "GloboB2ContactListener.h"

class B2ContactListener: public b2ContactListener
{
private:
	PlataformaB2ContactListener* listCinta;
	SogaB2ContactListener* listSoga;
	GloboB2ContactListener* listGlobo;

public:
	B2ContactListener(void);
	~B2ContactListener(void);

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);

	void terminar();
};
