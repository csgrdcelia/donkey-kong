#include "pch.h"
#include "EntityManager.h"
#include "Player.h"
#include "Block.h"
#include "Ladder.h"

std::shared_ptr<Player> EntityManager::m_Player;
std::vector<std::shared_ptr<Block>> EntityManager::m_Blocks;
std::vector<std::shared_ptr<Ladder>> EntityManager::m_Ladders;

EntityManager::EntityManager()
{
}


EntityManager::~EntityManager()
{
}
