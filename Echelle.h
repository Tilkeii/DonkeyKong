#pragma once
#include "Entity.h"

class Echelle : public Entity
{
public:
	Echelle(sf::Texture text);
	Echelle(sf::Texture text, sf::Vector2f pos);
	virtual ~Echelle();

	virtual void Update(sf::Time elapsedTime);
	virtual void Render(sf::RenderWindow *window);
	virtual void collisionDetected(std::shared_ptr<Entity> entity);

};

