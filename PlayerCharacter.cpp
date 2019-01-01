#include "pch.h"
#include "PlayerCharacter.h"
#include "EntityManager.h"

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

	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		movement.x -= m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		movement.x += m_playerSpeed * f_deltaTime;

	m_sprite.move(movement);

	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities) {

		if (std::shared_ptr<PlayerCharacter> p = std::dynamic_pointer_cast<PlayerCharacter>(entity)) {
			continue;
		}

		if (entity->GetEnable() == false){
			continue;
		}

		if (checkCollision(entity)) {
			
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

