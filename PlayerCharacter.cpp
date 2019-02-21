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
	ShowHitbox(sf::Color(255, 0, 0, 75));
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::Update(sf::Time deltaTime)
{
	Entity::Update(deltaTime);
	float f_deltaTime = deltaTime.asSeconds();
	float blockYPosition = 0;
	//sf::Vector2f movement(0.0f, 0.0f);
	m_velocity = sf::Vector2f(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_velocity.x -= m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_velocity.x += m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_echelleCollisionUp)
		m_velocity.y -= m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_echelleCollisionDown)
		m_velocity.y += m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_canJump)
		Jump();
	m_velocity += sf::Vector2f(0.0f, 150.0f * f_deltaTime); // appliquer une gravité
	if (!m_canJump) { // si il est dans les airs
		//m_velocity += sf::Vector2f(0.0f, 150.0f * f_deltaTime); // appliquer une gravité
		if (m_sprite.getPosition().y - m_savePosWhenJump.y > m_jumpHeight && !m_jumpFall) {
			std::cout << "diff " << m_sprite.getPosition().y - m_savePosWhenJump.y << std::endl;
			m_velocity -= sf::Vector2f(0.0f, 400.0f * f_deltaTime); // appliquer une force vers le haut (pour le saut)
		}
		else {
			m_jumpFall = true;
		}
	}

	m_sprite.move(m_velocity);

}

void PlayerCharacter::Render(sf::RenderWindow *window)
{
	Entity::Render(window);
}

void PlayerCharacter::collisionDetected(std::shared_ptr<Entity> entity, sf::FloatRect intersection)
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

	if (std::shared_ptr<Block> block = std::dynamic_pointer_cast<Block>(entity)) {
		m_canJump = true;
		sf::FloatRect spriteFloatRect = m_sprite.getGlobalBounds();
		sf::FloatRect blockFloatRect = block->GetSprite().getGlobalBounds();

		float xDiff = (spriteFloatRect.left + (spriteFloatRect.width / 2)) -
			(blockFloatRect.left + (blockFloatRect.width / 2));
		float yDiff = (spriteFloatRect.top + (spriteFloatRect.height / 2)) -
			(blockFloatRect.top + (blockFloatRect.height / 2));

		float resolve = 0;

		if (abs(xDiff) > abs(yDiff)) {
			if (xDiff > 0) {
				resolve = (blockFloatRect.left + blockFloatRect.height) - spriteFloatRect.left;
			}
			else {
				resolve = -((spriteFloatRect.left + spriteFloatRect.width) - blockFloatRect.left);
			}
			m_sprite.move(resolve, 0);
		}
		else {
			if (yDiff > 0) {
				resolve = (blockFloatRect.top + blockFloatRect.height) - spriteFloatRect.top;
			}
			else {
				resolve = -((spriteFloatRect.top + spriteFloatRect.height) - blockFloatRect.top);
			}
			m_sprite.move(0, resolve);
		}
	}
}

void PlayerCharacter::Jump()
{
	m_canJump = false;
	m_jumpFall = false;
	m_savePosWhenJump = m_sprite.getPosition();
	std::cout << "m_savePosWhenJump : " << m_savePosWhenJump.x << ";" <<m_savePosWhenJump.y << std::endl;

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

