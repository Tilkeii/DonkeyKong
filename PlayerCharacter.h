#pragma once
#include "Entity.h"

class PlayerCharacter : public Entity
{
public:
	PlayerCharacter(sf::Texture text);
	PlayerCharacter(sf::Texture text, sf::Vector2f pos);
	~PlayerCharacter();
	
	virtual void Update(sf::Time elapsedTime);
	virtual void Render();
	void Jump();
	void Attack();
	void GetHurt();
	void Move(sf::Vector2f vec);
	void AddVelocity(sf::Vector2f vec);

	void SetMaxVelocity(sf::Vector2f velocity);

private:
	// Player Character movement
	int m_lives;
	float m_playerSpeed = 100.f;
	sf::Vector2f m_velocity;
	sf::Vector2f m_maxVelocity;
	sf::Vector2f m_jumpVelocity;
	sf::Vector2f m_acceleration;

	bool m_isMovingUp;
	bool m_isMovingDown;
	bool m_isMovingRight;
	bool m_isMovingLeft;
};

