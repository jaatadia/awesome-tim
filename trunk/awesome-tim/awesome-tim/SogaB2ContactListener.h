#pragma once

#include "Box2D/Box2D.h"
#include <list>


class SogaB2ContactListener: public b2ContactListener
{
private:
	b2World* mundo;
	std::list<b2Joint*> lista;
public:
	SogaB2ContactListener(void);
	~SogaB2ContactListener(void);

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);

	void terminar();
};
