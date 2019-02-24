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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_canLeft)
		m_velocity.x -= m_playerSpeed * f_deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_canRight)
		m_velocity.x += m_playerSpeed * f_deltaTime;
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
			std::cout << "test : " << m_isOnFloor  << std::endl;
			std::cout << "diff " << m_sprite.getPosition().y - m_savePosWhenJump.y << std::endl;
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
		if (m_sprite.getPosition().y >= echelle->GetHitbox().top - m_texture.getSize().y + 1) {
			m_echelleCollisionUp = false;
			m_echelleCollisionDown = true;
		}

		//v�rif que le milieu de Mario est dans l'�chelle
		if (m_sprite.getPosition().x + m_texture.getSize().x / 2 <= echelle->GetHitbox().left + echelle->GetHitbox().width
				&& m_sprite.getPosition().x + m_texture.getSize().x / 2 >= echelle->GetHitbox().left) {
			m_echelleCollisionUp = true;
			
		}
		else {
			m_echelleCollisionUp = false;
			m_echelleCollisionDown = false;
		}

		//peut gauche droite quand en haut de l'�chelle
		if (m_sprite.getPosition().y + m_texture.getSize().y <= echelle->GetHitbox().top + m_playerSpeed * Game::TimePerFrame.asSeconds()) {
			m_canRight = true;
			m_canLeft = true;
		}

		//peut gauche droite quand en bas de l'�chelle
		if (m_sprite.getPosition().y + m_texture.getSize().y >= echelle->GetHitbox().top + echelle->GetTexture().getSize().y - m_playerSpeed * Game::TimePerFrame.asSeconds()) {
			m_canRight = true;
			m_canLeft = true;
		}

		//Nous aligne bien en haut de l'�chelle
		if (m_sprite.getPosition().y + m_texture.getSize().y <= echelle->GetHitbox().top + m_playerSpeed * Game::TimePerFrame.asSeconds()
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			m_sprite.setPosition(m_sprite.getPosition().x, echelle->GetHitbox().top - m_texture.getSize().y + 1);
			m_echelleCollisionUp = false;
			m_echelleCollisionDown = false;
			m_canRight = true;
			m_canLeft = true;
		}
		
		//Nous aligne bien en bas de l'�chelle
		if (m_sprite.getPosition().y + m_texture.getSize().y >= echelle->GetHitbox().top + echelle->GetHitbox().height - m_playerSpeed * Game::TimePerFrame.asSeconds()
			&& sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			m_sprite.setPosition(m_sprite.getPosition().x, echelle->GetHitbox().top - m_texture.getSize().y + echelle->GetHitbox().height + 1);
			m_echelleCollisionUp = false;
			m_echelleCollisionDown = false;
			m_canRight = true;
			m_canLeft = true;
		}
	}

	if (std::shared_ptr<Block> block = std::dynamic_pointer_cast<Block>(entity)) {

		m_canJump = true;
		sf::FloatRect hitboxPlayer = GetHitbox();
		sf::FloatRect hitboxBlock = block->GetHitbox();

		/*std::cout << 
			"Sprite Height : " << hitboxPlayer.height << 
			" Width : " << hitboxPlayer.width <<
			" Left : " << hitboxPlayer.left <<
			" Top : " << hitboxPlayer.top << std::endl;

		std::cout <<
			"Hitbox Height : " << hitboxPlayer.height <<
			" Width : " << hitboxPlayer.width <<
			" Left : " << hitboxPlayer.left <<
			" Top : " << hitboxPlayer.top << std::endl;*/
		if(m_sprite.getPosition().y + m_texture.getSize().y <= block->GetPosition().y + 1 || m_sprite.getPosition().y + m_texture.getSize().y >= block->GetPosition().y + 1){
			m_isOnFloor = true;
		}

	}
	//std::cout << "on touche  " << typeid(*entity).name() << std::endl;
	//std::cout << "resultat up " << m_echelleCollisionUp << std::endl;
	//std::cout << "resultat down " << m_echelleCollisionDown << std::endl;
}

void PlayerCharacter::Jump()
{
	m_echelleCollisionUp = false;
	m_echelleCollisionDown = false;
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

