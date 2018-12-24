#include "pch.h"
#include "Entity.h"

Entity::Entity(sf::Texture text) {
	m_texture = text;
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(sf::Vector2f(0.f, 0.f));
}

Entity::Entity(sf::Texture text, sf::Vector2f pos) {
	m_texture = text;
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(pos);
}

Entity::~Entity() {

}

void Entity::Update(sf::Time elapsedTime)
{
}

void Entity::Render()
{
}

void Entity::HandleCollision()
{
}

void Entity::SetPosition(sf::Vector2f position) {  }

void Entity::SetEnable(bool enable) { m_enabled = enable; }

sf::Texture Entity::GetTexture() { return m_texture; }

sf::Sprite Entity::GetSprite() { return m_sprite; }

sf::Vector2f Entity::GetPosition() { return sf::Vector2f(); }

bool Entity::GetEnable() { return m_enabled; }
