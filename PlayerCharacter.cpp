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
	static bool echelleColisionUp = false;
	static bool echelleColisionDown = false;
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		movement.x -= m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		movement.x += m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && echelleColisionUp)
		movement.y -= m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && echelleColisionDown)
		movement.y += m_playerSpeed * f_deltaTime;
	m_sprite.move(movement);

	echelleColisionUp = false;
	echelleColisionDown = false;
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities) {

		if (std::shared_ptr<PlayerCharacter> p = std::dynamic_pointer_cast<PlayerCharacter>(entity)) {
			continue;
		}

		if (entity->GetEnable() == false){
			continue;
		}
		
		if (checkCollision(entity)) {
			if (typeid(*entity) == typeid(Echelle)){
				echelleColisionUp = true;
				echelleColisionDown = true;
				if (m_sprite.getPosition().y == (*entity).GetPosition().y - this->m_texture.getSize().y + 1) {
					echelleColisionUp = false;
					echelleColisionDown = true;
				}
				else if (m_sprite.getPosition().y + this->m_texture.getSize().y <= (*entity).GetPosition().y + m_playerSpeed * f_deltaTime
					&& sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					m_sprite.setPosition(m_sprite.getPosition().x, (*entity).GetPosition().y - this->m_texture.getSize().y + 1);
					echelleColisionUp = false;
					echelleColisionDown = false;
				}
				if (m_sprite.getPosition().y + this->m_texture.getSize().y >= (*entity).GetPosition().y + (*entity).GetTexture().getSize().y - m_playerSpeed * f_deltaTime
					&& sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					m_sprite.setPosition(m_sprite.getPosition().x, (*entity).GetPosition().y - this->m_texture.getSize().y + (*entity).GetTexture().getSize().y);
					echelleColisionUp = false;
					echelleColisionDown = false;
				}

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

