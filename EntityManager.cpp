#include "pch.h"
#include <memory>
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

		if (std::shared_ptr<PlayerCharacter> p = std::dynamic_pointer_cast<PlayerCharacter>(entity)) {
			return p;
		}
	}

	return nullptr;
}
