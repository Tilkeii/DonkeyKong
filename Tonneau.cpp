#include "pch.h"
#include "Tonneau.h"

Tonneau::Tonneau(sf::Texture text) : Entity(text)
{
}

Tonneau::Tonneau(sf::Texture text, sf::Vector2f pos) : Entity(text, pos)
{

}

Tonneau::~Tonneau()
{
}

void Tonneau::Update(sf::Time elapsedTime)
{
	Entity::Update(elapsedTime);
}

void Tonneau::Render(sf::RenderWindow *window)
{
	Entity::Render(window);
}

void Tonneau::collisionDetected(std::shared_ptr<Entity> entit, sf::FloatRect intersectiony)
{
}
