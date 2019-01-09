#include "pch.h"
#include "Player.h"
#include "LevelFactory.h"


Player::Player(float x, float y) : Entity(x, y)
{
	m_speed = 150.f;

	UpdateTexture("Media/Textures/mario_right.png");
	mSprite.setPosition(x, y);
}

Player::~Player()
{
}

void Player::Jump(sf::Time elapsedTime) {
	if (!this->IsOnLadder()) {
		GoesToTheRight ? UpdateTexture(mRightJumpTexturePath) : UpdateTexture(mLeftJumpTexturePath);

		sf::Vector2f movement(0.f, 0.f);
		movement.y -= m_speed;
		this->mSprite.move(movement * elapsedTime.asSeconds());
	}
}

void Player::GravityHandle() {
	if (cptFall != 30) {
		GoesToTheRight ? UpdateTexture(mRightJumpTexturePath) : UpdateTexture(mLeftJumpTexturePath);
	}
	if (cptFly > 0 && cptFly < 40) {
		cptFly++;
	}
	else {
		if (cptJump == 30) {
			cptFly++;
			mIsJumping = false;
		}
		if (!mIsJumping)
			cptJump = 0;
		if (!mIsJumping && cptFall != 30)
			cptFall++;
		if (mIsJumping) {
			cptJump++;
			cptFall--;
		}
		if (cptFly == 40)
			cptFly = 0;
	}
	std::cout << cptFly << std::endl;
}

void Player::TryToEatCoin()
{
	for (std::shared_ptr<Entity> entity : LevelFactory::GetLevel()->mCoins)
	{
		sf::FloatRect fr = entity->mSprite.getGlobalBounds();
		if (this->mSprite.getGlobalBounds().intersects(fr))
		{
			entity->mEnabled = false;
			break;
		}
	}
}

bool Player::HasEatenAllCoins()
{
	if (LevelFactory::GetLevel()->GetCoinsEaten() == LevelFactory::GetLevel()->mCoins.size())
	{
		return true;
	}
	return false;
}

bool Player::HasCollidedEnemy()
{
	for (std::shared_ptr<Entity> entity : LevelFactory::GetLevel()->mEnemies)
	{
		sf::FloatRect fr = entity->mSprite.getGlobalBounds();
		if (this->mSprite.getGlobalBounds().intersects(fr))
		{
			return true;
		}
	}
	return false;
}

void Player::GoLeft(sf::Time elapsedTime)
{
	if (cptFall == 30) {
		UpdateTexture(mleftTexturePath);
	}
	Entity::GoLeft(elapsedTime);
}

void Player::GoRight(sf::Time elapsedTime)
{
	if (cptFall == 30) {
		UpdateTexture(mRightTexturePath);
	}
	Entity::GoRight(elapsedTime);
}

bool Player::GoUp(sf::Time elapsedTime)
{
	if(IsAboveOrOnLadder())
		UpdateTexture(mUpTexturePath);
	return Entity::GoUp(elapsedTime); 
}

bool Player::GoDown(sf::Time elapsedTime)
{
	if (this->IsAboveOrOnLadder() || OnVoid())
	{
		if (IsOnLadder()) 
			UpdateTexture(mUpTexturePath);

		sf::Vector2f movement(0.f, 0.f);
		movement.y += 100.f;
		this->mSprite.move(movement * elapsedTime.asSeconds());
		return true;
	}
	return false;
}

void Player::Dies()
{	
	if (mDiesBuffer.loadFromFile(mDeathSoundPath))
	{
		mDeathSound.setBuffer(mDiesBuffer);
		mDeathSound.play();
		mDeathSound.setPlayingOffset(sf::seconds(2.f));
	}
}

void Player::Wins()
{
	if (mWinsBuffer.loadFromFile(mWin1SoundPath))
	{
		mWin1Sound.setBuffer(mWinsBuffer);
		mWin1Sound.play();
		mWin1Sound.setPlayingOffset(sf::seconds(2.f));
	}
}



