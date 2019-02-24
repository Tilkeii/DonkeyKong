#pragma once
#include "Entity.h"
#include "PlayerCharacter.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

public:
	static std::vector<std::shared_ptr<Entity>> m_Entities;
	static std::shared_ptr<PlayerCharacter> GetPlayer();
};

