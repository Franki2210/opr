#include "SpriteMap.h"
#include "Player.h"

using namespace sf;

Player::Player() = default;
Player::Player(Texture texIdle, const  int colIdle, const int lineIdle,
				Texture texRun, const int colRun, const int lineRun)
{
	spriteMapIdle.SetSpriteMap(texIdle, colIdle, lineIdle);
	spriteMapRun.SetSpriteMap(texRun, colRun, lineRun);
}
Player::~Player() = default;

void Player::SetSpriteMaps(Texture & texIdle, const int colIdle, const int lineIdle,
	Texture & texRun, const int colRun, const int lineRun)
{
	spriteMapIdle.SetSpriteMap(texIdle, colIdle, lineIdle);
	spriteMapRun.SetSpriteMap(texRun, colRun, lineRun);
}

void Player::SetSoundSteps(const SoundBuffer & soundBuf1, const SoundBuffer & soundBuf2, const SoundBuffer & soundBuf3, const SoundBuffer & soundBuf4,
	const float timeBetweenSounds, const float volume)
{
	soundsSteps.step1.setBuffer(soundBuf1);
	soundsSteps.step2.setBuffer(soundBuf2);
	soundsSteps.step3.setBuffer(soundBuf3);
	soundsSteps.step4.setBuffer(soundBuf4);

	soundsSteps.step1.setVolume(volume);
	soundsSteps.step2.setVolume(volume);
	soundsSteps.step3.setVolume(volume);
	soundsSteps.step4.setVolume(volume);

	timeBetweenSoundsSteps = timeBetweenSounds;
	timerBetweenSoundsSteps = timeBetweenSoundsSteps;
}

FloatRect Player::GetGlobalBounds()
{
	return spriteMapRun.sprite.getGlobalBounds();
}

//Направление движения
Direction Player::DirectionFromKey()
{
	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A))
	{
		return Direction::UpLeft;
	}
	if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D))
	{
		return Direction::UpRight;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A))
	{
		return Direction::DownLeft;
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D))
	{
		return Direction::DownRight;
	}

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		return Direction::Up;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		return Direction::Right;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		return Direction::Down;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		return Direction::Left;
	}
	else return Direction::Up;
}
Vector2f Player::MoveFromDirection(float const &time)
{
	float dx = 0;
	float dy = 0;

	if (direction == Direction::Up) { dy = -speed * time; }
	else if (direction == Direction::Down) { dy = speed * time; }
	else if (direction == Direction::Left) { dx = -speed * time; }
	else if (direction == Direction::Right) { dx = speed * time; }
	else if (direction == Direction::UpLeft) { dx = -speed * 0.7f * time; dy = -speed * 0.7f * time; }
	else if (direction == Direction::UpRight) { dx = speed * 0.7f * time; dy = -speed * 0.7f * time; }
	else if (direction == Direction::DownLeft) { dx = -speed * 0.7f * time; dy = speed * 0.7f * time; }
	else if (direction == Direction::DownRight) { dx = speed * 0.7f * time; dy = speed * 0.7f * time; }

	return Vector2f(dx, dy);
}

//Пули
void Player::SetBullet(Bullet usedBullet)
{
	bullet = usedBullet;
}
Bullet Player::GetBullet()
{
	return bullet;
}

void Player::SetTimeBetweenShots(float timeBetween)
{
	timeBetweenShots = timeBetween;
}
void Player::SetSpeed(float value)
{
	speed = value;
}

void Player::AddBonus(Bonus bonus)
{
	activeBonuses.push_back(bonus);
}

//Денюжка
void Player::AddCoins(int coin)
{
	coins += coin;
}
void Player::SubCoins(int coin)
{
	coins -= coin;
}
int Player::GetMoney()
{
	return coins;
}

void Player::BonusUpdate(float time)
{
	for (auto it = activeBonuses.begin(); it != activeBonuses.end();)
	{
		if (it->isDisactive)
		{
			if (it->GetName() == "speedInc")
			{
				speed -= it->GetValue();
			}
			else if (it->GetName() == "fireAccel")
			{
				timeBetweenShots += it->GetValue();
			}
			else if (it->GetName() == "damageInc")
			{
				bullet.SetDamage(bullet.GetDamage() - it->GetValue());
				it->isUsed = true;
			}
			it = activeBonuses.erase(it);
		}
		else
		{
			if (!it->isUsed)
			{
				if (it->GetName() == "healthInc")
				{
					AddHp(it->GetValue());
					it->isDisactive = true;
				}
				else if (it->GetName() == "speedInc")
				{
					speed += it->GetValue();
					it->isUsed = true;
				}
				else if (it->GetName() == "fireAccel")
				{
					timeBetweenShots -= it->GetValue();
					it->isUsed = true;
				}
				else if (it->GetName() == "damageInc")
				{
					bullet.SetDamage(bullet.GetDamage() + it->GetValue());
					it->isUsed = true;
				}
			}
			it->UpdateOnPlayer(time);
			it++;
		}
	}
}

void Player::Update(float const & time)
{
	Vector2f moveVector = { 0, 0 };
	isMove = false;

	BonusUpdate(time);

	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::A) ||
		Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::D))
	{
		direction = DirectionFromKey();
		moveVector = MoveFromDirection(time);
		isMove = true;
	}


	if (obstacle.contains(position.x + moveVector.x, position.y + moveVector.y))
	{
		isMove = false;
	}
	else
	{
		position += moveVector;
	}

	if (isMove)
	{
		if (timerBetweenSoundsSteps > 0)
		{
			timerBetweenSoundsSteps -= time;
		}
		else
		{
			timerBetweenSoundsSteps = timeBetweenSoundsSteps;
			int randSound = rand() % 4;
			if (randSound == 0) soundsSteps.step1.play();
			if (randSound == 1) soundsSteps.step2.play();
			if (randSound == 2) soundsSteps.step3.play();
			if (randSound == 3) soundsSteps.step4.play();
		}
	}

	if (timerBetweenShots > 0 && !canShot)
	{
		timerBetweenShots -= time;
	}
	else
	{
		canShot = true;
		timerBetweenShots = timeBetweenShots;
	}

	if (isMove) speedAnimation = 0.04f;
	else speedAnimation = 0.01f;

	currFrame += speedAnimation * time;
	if (isMove)
	{
		if (currFrame > spriteMapRun.GetColumns()) currFrame = 0;
		spriteMapRun.SetFrame(direction, currFrame);
		spriteMapRun.SetPosition(position);
	}
	else
	{
		if (currFrame > spriteMapIdle.GetColumns()) currFrame = 0;
		spriteMapIdle.SetFrame(direction, currFrame);
		spriteMapIdle.SetPosition(position);
	}
	SetHpPosition(position);
}

void Player::Draw(RenderWindow & window)
{
	if (isMove) window.draw(spriteMapRun.sprite);
	else window.draw(spriteMapIdle.sprite);
	DrawHp(window);
}