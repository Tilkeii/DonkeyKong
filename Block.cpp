#include "pch.h"
#include "Block.h"


Block::Block()
{
}


Block::~Block()
{
}

void Block::Update(sf::Time elapsedTime)
{
	Entity::Update(elapsedTime);
}

void Block::Render()
{
	Entity::Render();
}
