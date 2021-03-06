#pragma once

#define ECHELLE_COUNT 4
#define BLOCK_COUNT_X 14
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 170.f
#define GRAVITY 250.f

class Game
{
public:
	Game();
	~Game() { };
	void run();

	static const sf::Time	TimePerFrame;

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void updateStatistics(sf::Time deltaTime);

private:

	sf::RenderWindow		mWindow;
	sf::Font	mFont;
	sf::Text	mStatisticsText;
	sf::Time	mStatisticsUpdateTime;
	std::size_t	mStatisticsNumFrames;

};

