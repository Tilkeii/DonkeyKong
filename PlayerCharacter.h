#pragma once
#include "Entity.h"

class PlayerCharacter : public Entity
{
public:
	PlayerCharacter(sf::Texture text);
	PlayerCharacter(sf::Texture text, sf::Vector2f pos);
	virtual ~PlayerCharacter();
	
	virtual void Update(sf::Time elapsedTime);
	virtual void Render(sf::RenderWindow *window);
	virtual void collisionDetected(std::shared_ptr<Entity> entity);

	void Jump();
	void Attack();
	void GetHurt();
	void AddVelocity(sf::Vector2f vec);

	void SetMaxVelocity(sf::Vector2f velocity);

private:

	int m_lives;
	float m_playerSpeed = 250.0f;
	sf::Vector2f m_velocity;
	bool m_canJump = true;
	float m_jumpHeight = -25.0f;
	bool m_jumpFall = false;
	sf::Vector2f m_savePosWhenJump;

	bool m_echelleCollisionUp = false;
	bool m_echelleCollisionDown = false;
	bool m_canRight = true;
	bool m_canLeft = true;

};

