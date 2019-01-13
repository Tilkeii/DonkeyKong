#pragma once
#include "Entity.h"

class Tonneau : public Entity
{
public:
	Tonneau(sf::Texture text);
	Tonneau(sf::Texture text, sf::Vector2f pos);
	virtual ~Tonneau();

	virtual void Update(sf::Time elapsedTime);
	virtual void Render(sf::RenderWindow *window);
	virtual void collisionDetected(std::shared_ptr<Entity> entity);

};

