#pragma once
#include "Header.h"
#include "Entity.h"
#include "Animation.h"
#include "Bullet.h"

class Player : public Entity
{
public:
	bool isMove = false;

	Player(const String &texFileIdle, int colIdle, int lineIdle,
		const String &texFileIdleGun, int colIdleGun, int lineIdleGun,
		const String &texFileRun, int colRun, int lineRun,
		const String &texFileRunGun, int colRunGun, int lineRunGun)
	{
		playerAnimation.SetDefaultIdleTextureMap(texFileIdle, colIdle, lineIdle);
		playerAnimation.SetIdleGunTextureMap(texFileIdleGun, colIdleGun, lineIdleGun);
		playerAnimation.SetDefaultRunTextureMap(texFileRun, colRun, lineRun);
		playerAnimation.SetRunGunTextureMap(texFileRunGun, colRunGun, lineRunGun);
	}

	~Player() = default;

	Animation playerAnimation;

	void SetObstacle(FloatRect towerObstacle_)
	{
		towerObstacle = towerObstacle_;
	}

	Vector2f GetSize()
	{
		return Vector2f(playerAnimation.currMap.sprite.getGlobalBounds().width, playerAnimation.currMap.sprite.getGlobalBounds().height);
	}

	Direction DirectionFromKey()
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
	}

	Vector2f MoveFromDirection(float const &time)
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

	void SetBullet(string nameTexture, float damage, float speedBullet)
	{
		bullet.SetTexture(nameTexture);
		bullet.SetDamage(damage);
		bullet.SetSpeed(speedBullet);
	}

	Bullet GetBullet()
	{
		return bullet;
	}

	bool canShot = false;

	void Update(float const & time)
	{
		Vector2f moveVector = { 0, 0 };
		isMove = false;

		if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::A) ||
			Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::D))
		{
			direction = DirectionFromKey();
			moveVector = MoveFromDirection(time);
			isMove = true;
		}

		if (towerObstacle.contains(position.x + moveVector.x, position.y + moveVector.y))
		{
			isMove = false;
		}
		else
		{
			position += moveVector;
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

		playerAnimation.Update(time, isMove, direction);
		playerAnimation.currMap.sprite.setPosition(position);
		SetHpPosition(position);
	}

	void Draw(RenderWindow & window)
	{
		window.draw(playerAnimation.currMap.sprite);
		DrawHp(window);
	}
private:
	float speed = 0.15f;
	Direction direction = Direction::Up;
	FloatRect towerObstacle;
	Bullet bullet;
	float reloadTime;
	float reloadTimer;
	float timeBetweenShots = 300;
	float timerBetweenShots = timeBetweenShots;
};