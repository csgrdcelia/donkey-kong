#include "pch.h"
#include "EntityManager.h"
#include "Player.h"
#include "Block.h"
#include "Ladder.h"

std::shared_ptr<Player> EntityManager::m_Player;
std::vector<std::shared_ptr<Block>> EntityManager::m_Blocks;
std::vector<std::shared_ptr<Ladder>> EntityManager::m_Ladders;
std::vector<std::shared_ptr<Coin>> EntityManager::m_Coins;
std::vector<std::shared_ptr<Enemy>> EntityManager::m_Enemies;

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}

void EntityManager::AssignEntities() 
{
	// Player
	EntityManager::m_Player = std::make_shared<Player>(170.f, 550.f - 40.f);
	
	// Blocks
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{

			std::shared_ptr<Block> se = std::make_shared<Block>(100.f + 70.f * (i + 1.f), 110.f * (j + 1.f));
			EntityManager::m_Blocks.push_back(se);
		}
	}

	// Ladders
	for (int i = 0; i < 4; i++)
	{
		std::shared_ptr<Ladder> se = std::make_shared<Ladder>(100.f + 70.f * (i + 3), 110.f * (i + 1) + 33);
		EntityManager::m_Ladders.push_back(se);
	}

	// Coins
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::shared_ptr<Coin> se = std::make_shared<Coin>(100.f + 130.f * (j + 1), 110.f * (i + 1) + 50.f);
			if (!se->CollidesLadder())
				EntityManager::m_Coins.push_back(se);
		}
	}

	// Enemies

	for (int i = 0; i < 4; i++)
	{
		std::shared_ptr<Enemy> se = std::make_shared<Enemy>(100.f + 90.f * (i + 1), 110.f * (i + 1) + 78.f);
		EntityManager::m_Enemies.push_back(se);
	}
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
