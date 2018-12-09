#include "pch.h"
#include "EntityManager.h"
#include "Player.h"
#include "Block.h"
#include "Ladder.h"

std::shared_ptr<Player> EntityManager::m_Player;
std::vector<std::shared_ptr<Block>> EntityManager::m_Blocks;
std::vector<std::shared_ptr<Ladder>> EntityManager::m_Ladders;
std::vector<std::shared_ptr<Coin>> EntityManager::m_Coins;

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

int EntityManager::GetCoinsEaten()
{
	int coins = 0;
	for (std::shared_ptr<Entity> entity : EntityManager::m_Coins)
	{
		if (!entity->m_enabled)
		{
			coins += 1;
		}
	}
	return coins;
}
