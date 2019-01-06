#include "pch.h"
#include "PlayerCharacter.h"
#include "EntityManager.h"
#include "Echelle.h"
#include "Block.h"

PlayerCharacter::PlayerCharacter(sf::Texture text) : Entity(text) 
{
}

PlayerCharacter::PlayerCharacter(sf::Texture text, sf::Vector2f pos) : Entity(text, pos)
{
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::Update(sf::Time deltaTime)
{
	Entity::Update(deltaTime);
	float f_deltaTime = deltaTime.asSeconds();
	float blockYPosition = 0;
	static bool echelleColision = false;
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		movement.x -= m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		movement.x += m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && echelleColision)
		movement.y -= m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && echelleColision)
		movement.y += m_playerSpeed * f_deltaTime;
	m_sprite.move(movement);


	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities) {

		if (std::shared_ptr<PlayerCharacter> p = std::dynamic_pointer_cast<PlayerCharacter>(entity)) {
			continue;
		}

		if (entity->GetEnable() == false){
			continue;
		}

		if (checkCollision(entity)) {
			if (typeid(*entity) == typeid(Block)) {
				blockYPosition = (*entity).GetPosition().y;
			}
			if (typeid(*entity) == typeid(Echelle)){
				echelleColision = true;
				if (m_sprite.getPosition().y + this->m_texture.getSize().y <= (*entity).GetPosition().y + m_playerSpeed * f_deltaTime
					&& sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					m_sprite.setPosition(m_sprite.getPosition().x, blockYPosition - this->m_texture.getSize().y);
					echelleColision = false;
				}
				if (m_sprite.getPosition().y + this->m_texture.getSize().y >= blockYPosition
					&& m_sprite.getPosition().y <= blockYPosition
					&& sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					m_sprite.setPosition(m_sprite.getPosition().x, blockYPosition - this->m_texture.getSize().y);
					echelleColision = false;
				}
			}
			else {
				echelleColision = false;
			}
		}
	}
}

void PlayerCharacter::Render()
{
	Entity::Render();
}

void PlayerCharacter::Jump()
{
}

void PlayerCharacter::Attack()
{
}

void PlayerCharacter::GetHurt()
{
}

void PlayerCharacter::AddVelocity(sf::Vector2f vec)
{
}

void PlayerCharacter::SetMaxVelocity(sf::Vector2f velocity)
{
}

