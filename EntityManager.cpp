#include "pch.h"
#include "EntityManager.h"

std::vector<std::shared_ptr<Entity>> EntityManager::m_Entities;

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

std::shared_ptr<PlayerCharacter> EntityManager::GetPlayer()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->GetEnable() == false)
		{
			continue;
		}

		if (PlayerCharacter* p = dynamic_cast<PlayerCharacter*>(entity.get())) {
			return std::shared_ptr<PlayerCharacter>(p);
		}
	}

	return nullptr;
}
