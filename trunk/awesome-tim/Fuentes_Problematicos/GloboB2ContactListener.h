#pragma once

#include "Box2D/Box2D.h"
#include <list>
#include "Figura.h"

class GloboB2ContactListener: public b2ContactListener
{
private:

public:

	GloboB2ContactListener(void);
	~GloboB2ContactListener(void);

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	void terminar();
};
