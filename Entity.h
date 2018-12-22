#pragma once

class Entity
{
public:
	Entity() { };
	~Entity() { };

	virtual void Update(sf::Time elapsedTime) = 0;
	virtual void Render() = 0;
	void HandleCollision();

	void SetTexture(sf::Texture texture);
	void SetSprite(sf::Sprite sprite);
	void SetSize(sf::Vector2u size);
	void SetPosition(sf::Vector2f position);
	void SetEnable(bool enable);

	sf::Texture GetTexture();
	sf::Sprite GetSprite();
	sf::Vector2u GetSize();
	sf::Vector2f GetPosition();
	bool GetEnable();

protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2u m_size;
	sf::Vector2f m_position;
	bool m_enabled = true;

};

