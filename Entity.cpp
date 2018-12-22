#include "pch.h"
#include "Entity.h"

Entity::Entity() {

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

void Entity::SetTexture(sf::Texture texture){ m_texture = texture; }

void Entity::SetSprite(sf::Sprite sprite) { m_sprite = sprite; }

void Entity::SetSize(sf::Vector2u size) { m_size = size; }

void Entity::SetPosition(sf::Vector2f position) { m_position = position; }

void Entity::SetEnable(bool enable) { m_enabled = enable; }

sf::Texture Entity::GetTexture() { return sf::Texture(); }

sf::Sprite Entity::GetSprite() { return sf::Sprite(); }

sf::Vector2u Entity::GetSize() { return sf::Vector2u(); }

sf::Vector2f Entity::GetPosition() { return sf::Vector2f(); }

bool Entity::GetEnable() { return false; }
