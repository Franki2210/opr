#pragma once
#include "Header.h"
#include "SpriteMap.h"
#include "Bullet.h"
#include "Entity.h"

class Tower : public Entity
{
public:
	SpriteMap spriteMap;
	bool isCanBuy = false;
	bool isActive = false;
	bool canShot = false;
	Bullet bullet;

	float reloadTime = 500; // = reloadTime / 1000 секунд
	float reloadTimer = reloadTime;

	CircleShape actionArea;
	CircleShape boundsArea;

	Tower()
	{
		actionArea.setRadius(400);
		Color actionAreaColor(100, 200, 100, 20);
		Color actionAreaBorderColor(100, 200, 100, 100);
		actionArea.setFillColor(actionAreaColor);
		actionArea.setOutlineColor(actionAreaBorderColor);
		actionArea.setOutlineThickness(5);
		actionArea.setOrigin(actionArea.getRadius(), actionArea.getRadius());
		actionArea.setPointCount(60);

		boundsArea.setOrigin(boundsArea.getRadius(), boundsArea.getRadius());
		boundsArea.setRadius(50);
		Color boundsAreaColor(200, 50, 50, 100);
		boundsArea.setFillColor(boundsAreaColor);
	}
	~Tower() = default;
	Tower(Texture & texture, int column, int line)
	{
		spriteMap.SetSpriteMap(texture, column, line);
		actionArea.setRadius(400);
		Color actionAreaColor(100, 200, 100, 20);
		Color actionAreaBorderColor(100, 200, 100, 100);
		actionArea.setFillColor(actionAreaColor);
		actionArea.setOutlineColor(actionAreaBorderColor);
		actionArea.setOutlineThickness(5);
		actionArea.setOrigin(actionArea.getRadius(), actionArea.getRadius());
		actionArea.setPointCount(60);

		boundsArea.setOrigin(boundsArea.getRadius(), boundsArea.getRadius());
		boundsArea.setRadius(50);
		Color boundsAreaColor(200, 50, 50, 100);
		boundsArea.setFillColor(boundsAreaColor);
	}

	void SetSpriteMap(Texture & texture, int column, int line)
	{
		spriteMap.SetSpriteMap(texture, column, line);
	}

	void SetActionRadius(float radius)
	{
		actionArea.setRadius(radius);
		actionArea.setOrigin(actionArea.getRadius(), actionArea.getRadius());
	}

	int GetNumFrameFromDirection(Vector2f posEnemy)
	{
		float dX = posEnemy.x - position.x;
		float dY = posEnemy.y - position.y;
		float angle = (atan2(dY, dX)) * 180 / 3.14159265f + 90;
		if (angle < 0) angle += 360;
		int frame = (int)(angle / (360. / (spriteMap.GetColumns() * spriteMap.GetLines())));
		return frame;
	}

	void SetBullet(Bullet bullet_)
	{
		bullet = bullet_;
	}
	Bullet GetBullet()
	{
		return bullet;
	}

	void SetReloadTime(float reloadTime_)
	{
		reloadTime = reloadTime_;
	}

	void SetPrice(int price_)
	{
		price = price_;
	}
	int GetPrice()
	{
		return price;
	}

	Vector2f GetEnemyPos()
	{
		return enemyPos;
	}

	void Update(const float time, Vector2f posEnemy)
	{
		if (reloadTimer > 0 && !canShot)
		{
			reloadTimer -= time;
		}

		enemyPos = posEnemy;

		if (actionArea.getGlobalBounds().contains(posEnemy))
		{
			currFrame = (float)GetNumFrameFromDirection(posEnemy);
			if (reloadTimer <= 0)
			{
				canShot = true;
				reloadTimer = reloadTime;
			}
		}
		spriteMap.SetFrame((int)currFrame);
	}
	void Update()
	{
		spriteMap.sprite.setPosition(position);
		actionArea.setPosition(position);
		boundsArea.setPosition(position.x - boundsArea.getRadius(), position.y - boundsArea.getRadius());
		bullet.SetStartPosition(position);
	}
	void Draw(RenderWindow & window)
	{
		window.draw(spriteMap.sprite);
		DrawHp(window);
	}

private:
	float currFrame = 0;
	Vector2f enemyPos;
	int price;
};