#pragma once
#include "Header.h"
#include "Entity.h"
#include "Bullet.h"

class Player : public Entity
{
public:
	bool isMove = false;
	bool canShot = false;

	Player() = default;
	Player(Texture texIdle, int colIdle, int lineIdle,
		Texture texRun, int colRun, int lineRun)
	{
		spriteMapIdle.SetSpriteMap(texIdle, colIdle, lineIdle);
		spriteMapRun.SetSpriteMap(texRun, colRun, lineRun);
	}
	~Player() = default;

	void SetSpriteMaps(Texture & texIdle, int colIdle, int lineIdle,
		Texture & texRun, int colRun, int lineRun)
	{
		spriteMapIdle.SetSpriteMap(texIdle, colIdle, lineIdle);
		spriteMapRun.SetSpriteMap(texRun, colRun, lineRun);
	}

	//Препятствие для игрока
	void SetObstacle(FloatRect obstacle_)
	{
		obstacle = obstacle_;
	}

	//Направление движения
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
		else return Direction::Up;
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

	//Пули
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

	void SetTimeBetweenShots(float timeBetween)
	{
		timeBetweenShots = timeBetween;
	}

	//Денюжка
	void AddCoins(int coin)
	{
		coins += coin;
	}
	void SubCoins(int coin)
	{
		coins -= coin;
	}
	int GetMoney()
	{
		return coins;
	}

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

		if (obstacle.contains(position.x + moveVector.x, position.y + moveVector.y))
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

	void Draw(RenderWindow & window)
	{
		if (isMove) window.draw(spriteMapRun.sprite);
		else window.draw(spriteMapIdle.sprite);
		DrawHp(window);
	}
private:
	float speed = 0.15f;
	Direction direction = Direction::Up;
	FloatRect obstacle;
	Bullet bullet;
	float reloadTime;
	float reloadTimer;
	float timeBetweenShots = 150;
	float timerBetweenShots = timeBetweenShots;
	SpriteMap spriteMapIdle;
	SpriteMap spriteMapRun;
	float currFrame = 0;
	float speedAnimation;
	int score;
	int coins = 0;
};