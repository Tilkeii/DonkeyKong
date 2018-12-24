#pragma once
#include "Entity.h"

class Echelle : public Entity
{
public:
	Echelle(sf::Texture text);
	Echelle(sf::Texture text, sf::Vector2f pos);
	~Echelle();

	virtual void Update(sf::Time elapsedTime);
	virtual void Render();

};

