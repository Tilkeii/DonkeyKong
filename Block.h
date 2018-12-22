#pragma once
#include "Entity.h"

class Block : public Entity
{
public:
	Block();
	~Block();

	virtual void Update(sf::Time elapsedTime);
	virtual void Render();

};

