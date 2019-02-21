#include "pch.h"
#include "Echelle.h"


Echelle::Echelle(sf::Texture text) : Entity(text)
{
}

Echelle::Echelle(sf::Texture text, sf::Vector2f pos) : Entity(text, pos)
{
	ShowHitbox(sf::Color(0, 255, 0, 75));
}

Echelle::~Echelle()
{
}

void Echelle::Update(sf::Time elapsedTime)
{
	Entity::Update(elapsedTime);
}

void Echelle::Render(sf::RenderWindow *window)
{
	Entity::Render(window);
}

void Echelle::collisionDetected(std::shared_ptr<Entity> entity, sf::FloatRect intersection)
{
}
