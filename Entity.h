#pragma once

class Entity
{
public:
	Entity(sf::Texture text);
	Entity(sf::Texture text, sf::Vector2f pos);
	virtual ~Entity();

	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Render() = 0;

	bool checkCollision(std::shared_ptr<Entity> other);

	void SetPosition(sf::Vector2f position);
	void SetEnable(bool enable);

	sf::Texture GetTexture();
	sf::Sprite GetSprite();
	sf::Vector2f GetPosition();
	bool GetEnable();

protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	bool m_enabled = true;

};

