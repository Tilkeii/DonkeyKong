#pragma once
#include "Entity.h"

class Tonneau : public Entity
{
public:
	Tonneau();
	~Tonneau();

	virtual void Update(sf::Time elapsedTime);
	virtual void Render();

};

