#pragma once
#include "Header.h"
#include "SpriteMap.h"
#include "Bullet.h"
#include "Entity.h"

class Tower : public Entity
{
public:
	SpriteMap spriteMap;
	bool isActive = false;
	bool canShot = false;
	Bullet bullet;

	float reloadTime = 500; // = reloadTime / 1000 секунд
	float reloadTimer = reloadTime;

	CircleShape actionArea;
	CircleShape boundsArea;

	Texture maxHpTex;
	Texture currHpTex;
	Sprite maxHpSprite;
	Sprite currHpSprite;

	Tower() = default;
	~Tower() = default;
	Tower(String nameTowerTexture, int column, int line)
	{
		spriteMap.SetSpriteMap(nameTowerTexture, column, line);
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
		cout << "Создан Tower" << endl;
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

	Vector2f GetSize()
	{
		return Vector2f(spriteMap.sprite.getGlobalBounds().width, spriteMap.sprite.getGlobalBounds().height);
	}

	void SetReloadTime(float reloadTime_)
	{
		reloadTime = reloadTime_;
	}

	Vector2f GetEnemyPos()
	{
		return enemyPos;
	}

	void Update(float & time, Vector2f posEnemy)
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

	void Update(float const &time)
	{
		spriteMap.sprite.setPosition(position);
		actionArea.setPosition(position);
		boundsArea.setPosition(position.x - boundsArea.getRadius(), position.y - boundsArea.getRadius());
		bullet.SetPosition(position);
	}

	void Draw(RenderWindow & window)
	{
		window.draw(spriteMap.sprite);
		DrawHp(window);
	}

private:
	float currFrame = 1;
	Vector2f enemyPos;
};

