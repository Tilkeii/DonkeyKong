#include "pch.h"
#include "PlayerCharacter.h"
#include "EntityManager.h"
#include "Echelle.h"
#include "Block.h"
#include "Game.h"

PlayerCharacter::PlayerCharacter(sf::Texture text) : Entity(text) 
{
	sf::IntRect rectSourceSprite(155, 3, 15, 16);
	m_sprite = sf::Sprite(m_texture, rectSourceSprite);

	m_sprite.setScale(3.f, 3.f);
	SetHitbox(0.f, 0.f, (-(float)m_texture.getSize().x + 15.f) * 3, (-(float)m_texture.getSize().y + 16.f) * 3);
	m_sprite.setPosition(sf::Vector2f(100.f + 70.f, BLOCK_SPACE * 5 - 16.f * 3));
}

PlayerCharacter::PlayerCharacter(sf::Texture text, sf::Vector2f pos) : Entity(text, pos)
{
	m_sprite.setScale(3.f, 3.f);
	SetHitbox(0.f, 0.f, 0.f, 0.f);
}

PlayerCharacter::~PlayerCharacter()
{
}

void PlayerCharacter::Update(sf::Time deltaTime)
{
	Entity::Update(deltaTime);
	float f_deltaTime = deltaTime.asSeconds();
	float blockYPosition = 0;
	sf::IntRect rectSourceSprite = m_sprite.getTextureRect();
	//sf::Vector2f movement(0.0f, 0.0f);
	m_velocity = sf::Vector2f(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_canLeft){
		rectSourceSprite.left = 136;
		m_velocity.x -= m_playerSpeed * f_deltaTime;
		rectSourceSprite = m_sprite.getTextureRect();
		if (rectSourceSprite.left < 95)
			rectSourceSprite.left = 136;
		else
			rectSourceSprite.left -= 21;
		m_sprite.setTextureRect(rectSourceSprite);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_canRight) {

		rectSourceSprite.left = 155;
		m_velocity.x += m_playerSpeed * f_deltaTime;
		rectSourceSprite = m_sprite.getTextureRect();
		if (rectSourceSprite.left >= 197)
			rectSourceSprite.left = 155;
		else
			rectSourceSprite.left += 21;
		m_sprite.setTextureRect(rectSourceSprite);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_echelleCollisionUp)
		m_velocity.y -= m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_echelleCollisionDown)
		m_velocity.y += m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_canJump)
		Jump();
	if(!m_isOnFloor && !m_echelleCollisionUp && !m_echelleCollisionDown)
		m_velocity += sf::Vector2f(0.0f, GRAVITY * f_deltaTime); // appliquer une gravité
	if (!m_canJump) { // si il est dans les airs
		if (m_sprite.getPosition().y - m_savePosWhenJump.y > m_jumpHeight && !m_jumpFall) {
			m_velocity -= sf::Vector2f(0.0f, 700.0f * f_deltaTime); // appliquer une force vers le haut (pour le saut)
		}
		else {
			m_jumpFall = true;
		}
	}

	m_isOnFloor = false;

	m_sprite.move(m_velocity);

}

void PlayerCharacter::Render(sf::RenderWindow *window)
{
	Entity::Render(window);
}

void PlayerCharacter::collisionDetected(std::shared_ptr<Entity> entity, sf::FloatRect intersection)
{
	
	m_echelleCollisionUp = false;
	m_echelleCollisionDown = false;
	m_canRight = true;
	m_canLeft = true;

	if (std::shared_ptr<Echelle> echelle = std::dynamic_pointer_cast<Echelle>(entity)) {		
		
		m_canRight = false;
		m_canLeft = false;

		

		//pour descendre
		if (m_sprite.getPosition().y >= echelle->GetHitbox().top - m_hitbox.height + 1) {
			m_echelleCollisionUp = false;
			m_echelleCollisionDown = true;
		}

		//v�rif que le milieu de Mario est dans l'�chelle
		if (m_sprite.getPosition().x + m_hitbox.width / 2 <= echelle->GetHitbox().left + echelle->GetHitbox().width
				&& m_sprite.getPosition().x + m_hitbox.width / 2 >= echelle->GetHitbox().left) {
			m_echelleCollisionUp = true;
			
		}
		else {
			m_echelleCollisionUp = false;
			m_echelleCollisionDown = false;
		}

		//peut gauche droite quand en haut de l'�chelle
		if (m_sprite.getPosition().y + m_hitbox.height <= echelle->GetHitbox().top + m_playerSpeed * Game::TimePerFrame.asSeconds()) {
			m_canRight = true;
			m_canLeft = true;
		}

		//peut gauche droite quand en bas de l'�chelle
		if (m_sprite.getPosition().y + m_hitbox.height >= echelle->GetHitbox().top + echelle->GetTexture().getSize().y - m_playerSpeed * Game::TimePerFrame.asSeconds()) {
			m_canRight = true;
			m_canLeft = true;
		}

		//Nous aligne bien en haut de l'�chelle
		if (m_sprite.getPosition().y + m_hitbox.height <= echelle->GetHitbox().top + m_playerSpeed * Game::TimePerFrame.asSeconds()
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			m_sprite.setPosition(m_sprite.getPosition().x, echelle->GetHitbox().top - m_hitbox.height + 1);
			m_echelleCollisionUp = false;
			m_echelleCollisionDown = false;
			m_canRight = true;
			m_canLeft = true;
		}
		
		//Nous aligne bien en bas de l'�chelle
		if (m_sprite.getPosition().y + m_hitbox.height >= echelle->GetHitbox().top + echelle->GetHitbox().height - m_playerSpeed * Game::TimePerFrame.asSeconds()
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			m_sprite.setPosition(m_sprite.getPosition().x, echelle->GetHitbox().top - m_hitbox.height + echelle->GetHitbox().height + 1);
			m_echelleCollisionUp = false;
			m_echelleCollisionDown = false;
			m_canRight = true;
			m_canLeft = true;
		}
	}

	if (std::shared_ptr<Block> block = std::dynamic_pointer_cast<Block>(entity)) {

		m_canJump = true;
;

		if(m_sprite.getPosition().y + m_texture.getSize().y <= block->GetPosition().y + 1 || m_sprite.getPosition().y + m_texture.getSize().y >= block->GetPosition().y + 1){
			m_isOnFloor = true;
		}

	}
}

void PlayerCharacter::Jump()
{
	m_echelleCollisionUp = false;
	m_echelleCollisionDown = false;
	m_canJump = false;
	m_jumpFall = false;
	m_savePosWhenJump = m_sprite.getPosition();

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

