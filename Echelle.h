#pragma once
#include "Entity.h"

class Echelle : public Entity
{
public:
	Echelle();
	~Echelle();

	virtual void Update(sf::Time elapsedTime);
	virtual void Render();

};

