#pragma once

#include "Box2D/Box2D.h"

class PlataformaB2ContactListener: public b2ContactListener
{

public:
	PlataformaB2ContactListener(void);
	~PlataformaB2ContactListener(void);
	
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);

	void terminar();
};
