#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "Block.h"
#include "Echelle.h"
#include "PlayerCharacter.h"
#include "EntityManager.h"

const sf::Vector2f GRAVITY = sf::Vector2f(0.f, 9.81f);
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close)
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
{
	mWindow.setFramerateLimit(160);

	// Draw blocks

	sf::Texture textBlock;
	textBlock.loadFromFile("Media/Textures/Block.png");
	sf::Vector2u sizeBlock = textBlock.getSize();

	for (int i = 0; i < BLOCK_COUNT_X; i++)
	{
		for (int j = 0; j < BLOCK_COUNT_Y; j++)
		{
			sf::Vector2f pos = sf::Vector2f(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1));
			std::shared_ptr<Block> block = std::make_shared<Block>(textBlock, pos);

			EntityManager::m_Entities.push_back(block);
		}
	}

	// Draw Echelles
	sf::Texture textEchelle;
	textEchelle.loadFromFile("Media/Textures/Echelle.png");

	for (int i = 0; i < ECHELLE_COUNT; i++)
	{
		sf::Vector2f pos = sf::Vector2f(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) + sizeBlock.y);
		std::shared_ptr<Echelle> echelle = std::make_shared<Echelle>(textEchelle, pos);

		EntityManager::m_Entities.push_back(echelle);
	}

	// Draw Mario

	sf::Texture textMario;
	textMario.loadFromFile("Media/Textures/Mario_small_transparent.png"); // Mario_small.png");
	sf::Vector2u sizeMario = textMario.getSize();

	sf::Vector2f pos = sf::Vector2f(100.f + 70.f, BLOCK_SPACE * 5 - sizeMario.y);
	std::shared_ptr<PlayerCharacter> mario = std::make_shared<PlayerCharacter>(textMario, pos);

	EntityManager::m_Entities.push_back(mario);

	// Draw Statistic Font 

	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->GetEnable() == false)
		{
			continue;
		}

		entity->Update(elapsedTime);
	}
}

void Game::render()
{
	mWindow.clear();

	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->GetEnable() == false)
		{
			continue;
		}

		mWindow.draw(entity->GetSprite());
	}

	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up)
		//mIsMovingUp = isPressed;
		EntityManager::GetPlayer()->Move(sf::Vector2f(0.f, 150.f));
	else if (key == sf::Keyboard::Down)
		//mIsMovingDown = isPressed;
		EntityManager::GetPlayer()->Move(sf::Vector2f(0.f, -150.f));
	else if (key == sf::Keyboard::Left)
		//mIsMovingLeft = isPressed;
		EntityManager::GetPlayer()->Move(sf::Vector2f(-150.f, 0.f));
	else if (key == sf::Keyboard::Right)
		//mIsMovingRight = isPressed;
		EntityManager::GetPlayer()->Move(sf::Vector2f(150.f, 150.f));

	if (key == sf::Keyboard::Space)
	{
	}
}
