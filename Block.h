#pragma once
#include "Entity.h"

class Block : public Entity
{
public:
	Block(sf::Texture text);
	Block(sf::Texture text, sf::Vector2f pos);
	virtual ~Block();

	virtual void Update(sf::Time elapsedTime);
	virtual void Render(sf::RenderWindow *window);
	virtual void collisionDetected(std::shared_ptr<Entity> entity, sf::FloatRect intersection);

};

