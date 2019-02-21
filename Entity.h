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
	virtual void collisionDetected(std::shared_ptr<Entity> entity, sf::FloatRect intersection);

	void checkCollision();
	void SetPosition(sf::Vector2f position);
	void SetEnable(bool enable);
	void updateHitbox();

	sf::Texture GetTexture();
	sf::Sprite GetSprite();
	sf::Vector2f GetPosition();
	bool GetEnable();
	bool ShowHitbox(sf::Color color);
	bool HideHitbox();

protected:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::FloatRect m_hitbox;

	sf::RectangleShape m_rect;

	bool m_enabled = true;
	bool m_showHitbox = false;

};

