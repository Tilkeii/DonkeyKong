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

	m_hitbox = sf::FloatRect(GetPosition().y, GetPosition().y, m_texture.getSize().x, m_texture.getSize().y); // init rectangle hitbox
	m_rect.setSize(sf::Vector2f(m_hitbox.width, m_hitbox.height));
}

Entity::~Entity() {

}

void Entity::Update(sf::Time deltaTime)
{
	updateHitbox();
	checkCollision();
}

void Entity::Render(sf::RenderWindow *window)
{
	window->draw(m_sprite);
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
		sf::FloatRect intersection;
		if (thisBoundingBox.intersects(otherBoundingBox, intersection)) {
			entity->collisionDetected(getEntity(), intersection);
			this->collisionDetected(entity, intersection);
		}
	}
}

void Entity::collisionDetected(std::shared_ptr<Entity> entity, sf::FloatRect intersection) {  }

void Entity::SetPosition(sf::Vector2f position) {  }

void Entity::SetEnable(bool enable) { m_enabled = enable; }

void Entity::updateHitbox()
{
	m_rect.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y));
}

sf::Texture Entity::GetTexture() { return m_texture; }

sf::Sprite Entity::GetSprite() { return m_sprite; }

sf::Vector2f Entity::GetPosition() { return m_sprite.getPosition(); }

bool Entity::GetEnable() { return m_enabled; }
