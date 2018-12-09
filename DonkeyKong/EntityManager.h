#pragma once
#include "Entity.h"
#include "Block.h"
#include "Ladder.h"
#include "Player.h"
#include "Coin.h"


class EntityManager
{
public:
	EntityManager();
	~EntityManager();

public:
	static int GetCoinsEaten();

public:
	static std::shared_ptr<Player> m_Player;
	static std::vector<std::shared_ptr<Block>> m_Blocks;
	static std::vector<std::shared_ptr<Ladder>> m_Ladders;
	static std::vector<std::shared_ptr<Coin>> m_Coins;
};