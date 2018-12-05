#include "pch.h"
#include "EntityManager.h"
#include "Player.h"

std::vector<std::shared_ptr<Entity>> EntityManager::m_Entities;

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

std::shared_ptr<Entity> EntityManager::GetPlayer()
{
	for (std::shared_ptr<Entity> entity : EntityManager::m_Entities)
	{
		if (entity->m_enabled == false)
		{
			continue;
		}

		//if (entity->m_type == EntityType::player)
		if(Player* p = dynamic_cast<Player*>(entity.get))
		{
			return entity;
		}
	}

	return nullptr;
}
