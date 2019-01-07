#include "pch.h"
#include "PlayerCharacter.h"
#include "EntityManager.h"
#include "Echelle.h"
#include "Block.h"
#include "Game.h"

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
	sf::Vector2f movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		movement.x -= m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		movement.x += m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_echelleCollisionUp)
		movement.y -= m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_echelleCollisionDown)
		movement.y += m_playerSpeed * f_deltaTime;
	m_sprite.move(movement);

}

void PlayerCharacter::Render()
{
	Entity::Render();
}

void PlayerCharacter::collisionDetected(std::shared_ptr<Entity> entity)
{
	std::cout << "Collision detected with " << typeid(*entity).name() << std::endl;
	m_echelleCollisionUp = false;
	m_echelleCollisionDown = false;

	if (std::shared_ptr<Echelle> echelle = std::dynamic_pointer_cast<Echelle>(entity)) {
		m_echelleCollisionUp = true;
		m_echelleCollisionDown = true;
		if (m_sprite.getPosition().y == echelle->GetPosition().y - this->m_texture.getSize().y + 1) {
			m_echelleCollisionUp = false;
			m_echelleCollisionDown = true;
		}
		else if (m_sprite.getPosition().y + this->m_texture.getSize().y <= echelle->GetPosition().y + m_playerSpeed * Game::TimePerFrame.asSeconds()
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			m_sprite.setPosition(m_sprite.getPosition().x, echelle->GetPosition().y - this->m_texture.getSize().y + 1);
			m_echelleCollisionUp = false;
			m_echelleCollisionDown = false;
		}
		if (m_sprite.getPosition().y + this->m_texture.getSize().y >= echelle->GetPosition().y + echelle->GetTexture().getSize().y - m_playerSpeed * Game::TimePerFrame.asSeconds()
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			m_sprite.setPosition(m_sprite.getPosition().x, echelle->GetPosition().y - this->m_texture.getSize().y + echelle->GetTexture().getSize().y);
			m_echelleCollisionUp = false;
			m_echelleCollisionDown = false;
		}
	}
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

