#pragma once

class Entity : public std::enable_shared_from_this<Entity>
{
public:
	Entity(sf::Texture text);
	Entity(sf::Texture text, sf::Vector2f pos);
	std::shared_ptr<Entity> getEntity() { return shared_from_this(); }
	virtual ~Entity();

	virtual void Update(sf::Time deltaTime) = 0;
	virtual void Render(sf::RenderWindow *mWindow) = 0;
	virtual void collisionDetected(std::shared_ptr<Entity> entity);

	void checkCollision();
	void SetPosition(sf::Vector2f position);
	void SetEnable(bool enable);

	sf::Texture GetTexture();
	sf::Sprite GetSprite();
	sf::Vector2f GetPosition();
	bool GetEnable();

protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::RectangleShape m_rect;

	bool m_enabled = true;

};

