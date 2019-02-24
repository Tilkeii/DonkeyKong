#include "pch.h"
#include "Block.h"

Block::Block(sf::Texture text) : Entity(text)
{
}

Block::Block(sf::Texture text, sf::Vector2f pos) : Entity(text, pos) {

}

Block::~Block()
{
}

void Block::Update(sf::Time elapsedTime)
{
	Entity::Update(elapsedTime);
}

void Block::Render(sf::RenderWindow *window)
{
	Entity::Render(window);
}

void Block::collisionDetected(std::shared_ptr<Entity> entity, sf::FloatRect intersection)
{
}
