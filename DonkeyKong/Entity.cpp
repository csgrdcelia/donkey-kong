#include "pch.h"
#include "Entity.h"
#include "LevelFactory.h"

Entity::Entity()
{
}

Entity::Entity(float x, float y)
{

}

Entity::Entity(float x, float y, std::string pathToPNG)
{
	m_texture.loadFromFile(pathToPNG);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(x, y);
}


void Entity::GoRight(sf::Time elapsedTime)
{
	if (!CollidesBlock())
	{
		sf::Vector2f movement(0.f, 0.f);
		movement.x += m_speed;
		this->m_sprite.move(movement * elapsedTime.asSeconds());

			/*while (CollidesBlock())
				GoLeft(elapsedTime);*/

	}
}

void Entity::GoLeft(sf::Time elapsedTime)
{
	if (!CollidesBlock())
	{
		sf::Vector2f movement(0.f, 0.f);
		movement.x -= m_speed;
		this->m_sprite.move(movement * elapsedTime.asSeconds());

			/*while (CollidesBlock())
				GoRight(elapsedTime);*/

	}
}

bool Entity::GoUp(sf::Time elapsedTime)
{
	if (this->IsOnLadder())
	{
		sf::Vector2f movement(0.f, 0.f);
		movement.y -= m_speed;
		this->m_sprite.move(movement * elapsedTime.asSeconds());
		return true;
	}
	return false;
}

bool Entity::GoDown(sf::Time elapsedTime)
{
	if (this->IsAboveOrOnLadder())
	{
		sf::Vector2f movement(0.f, 0.f);
		movement.y += m_speed;
		this->m_sprite.move(movement * elapsedTime.asSeconds());
		return true;
	}
	return false;
}

bool Entity::IsOnLadder()
{
	for (std::shared_ptr<Entity> entity : LevelFactory::GetLevel()->mLadders)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		// we add the height of the block texture so our entity can hike on it
		fr.top -= 33;
		fr.height += 33;
		// we adjust the weight of the block so entities cannot go up if they intersect with only 1 pixel
		fr.left += 13;
		fr.width -= 20;

		if (this->m_sprite.getGlobalBounds().intersects(fr))
		{
			return true;
		}
	}
	return false;
}

bool Entity::IsAboveOrOnLadder()
{
	for (std::shared_ptr<Entity> entity : LevelFactory::GetLevel()->mLadders)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		fr.top -= this->m_sprite.getTexture()->getSize().y + 10;
		fr.height += 13;
		if (this->m_sprite.getGlobalBounds().intersects(fr))
		{
			return true;
		}
	}
	return false;
}

bool Entity::CollidesBlock() {
	for (std::shared_ptr<Entity> entity : LevelFactory::GetLevel()->mBlocks)
	{
		if (this->m_sprite.getGlobalBounds().intersects(entity->m_sprite.getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}

bool Entity::OnVoid()
{
	bool OnEdge = true;
	for (std::shared_ptr<Entity> entity : LevelFactory::GetLevel()->mBlocks)
	{
		sf::FloatRect fr = entity->m_sprite.getGlobalBounds();
		fr.top -= 5;
		fr.left += 5;
		fr.width -= 10;
		if (m_sprite.getGlobalBounds().intersects(fr))
			OnEdge = false;
	}
	return !IsOnLadder() && OnEdge;
}

bool Entity::IsOutsideOfWindow()
{
	if (this->m_sprite.getPosition().y > 600)
		return true;
	return false;
}
