#pragma once
#include "Entity.h"

class PlayerCharacter : public Entity
{
public:
	PlayerCharacter(sf::Texture text);
	PlayerCharacter(sf::Texture text, sf::Vector2f pos);
	virtual ~PlayerCharacter();
	
	virtual void Update(sf::Time elapsedTime);
	virtual void Render();
	void Jump();
	void Attack();
	void GetHurt();
	void AddVelocity(sf::Vector2f vec);

	void SetMaxVelocity(sf::Vector2f velocity);

private:

	int m_lives;
	float m_playerSpeed = 250.0f;

	bool m_canJump = true;
	float jumpHeight;

};

