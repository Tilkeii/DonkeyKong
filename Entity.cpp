#include "pch.h"
#include "Entity.h"
#include "EntityManager.h"

Entity::Entity(sf::Texture text) {
	m_texture = text;
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(sf::Vector2f(0.f, 0.f));
}

Entity::Entity(sf::Texture text, sf::Vector2f pos) {
	m_texture = text;
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(pos);

	m_rect.setSize(sf::Vector2f(m_texture.getSize().x, m_texture.getSize().y));
	m_rect.setFillColor(sf::Color(40 + rand() % 185, 40 + rand() % 185, 40 + rand() % 185, 75));
}

Entity::~Entity() {

}

void Entity::Update(sf::Time deltaTime)
{
	m_rect.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y));
	checkCollision();
}

void Entity::Render(sf::RenderWindow *window)
{
	window->draw(m_sprite);
	window->draw(m_rect);
}

void Entity::checkCollision()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities) {

		if (entity == getEntity()) {
			continue;
		}

		if (entity->GetEnable() == false) {
			continue;
		}

		sf::FloatRect otherBoundingBox = entity->GetSprite().getGlobalBounds();
		sf::FloatRect thisBoundingBox = GetSprite().getGlobalBounds();

		if (thisBoundingBox.intersects(otherBoundingBox)) {
			entity->collisionDetected(getEntity());
			this->collisionDetected(entity);
		}
	}
}

void Entity::collisionDetected(std::shared_ptr<Entity> entity) {  }

void Entity::SetPosition(sf::Vector2f position) {  }

void Entity::SetEnable(bool enable) { m_enabled = enable; }

sf::Texture Entity::GetTexture() { return m_texture; }

sf::Sprite Entity::GetSprite() { return m_sprite; }

sf::Vector2f Entity::GetPosition() { return m_sprite.getPosition(); }

bool Entity::GetEnable() { return m_enabled; }
