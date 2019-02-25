#include "pch.h"
#include "Echelle.h"


Echelle::Echelle(sf::Texture text) : Entity(text)
{
}

Echelle::Echelle(sf::Texture text, sf::Vector2f pos) : Entity(text, pos)
{
	m_sprite.setScale(1.7f,2.f);
	SetHitbox(0, 33.f, 0.f, 33.f);
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
