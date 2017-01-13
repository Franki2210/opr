#pragma once
#include "Header.h"
#include "CalcHelp.h"

class Bullet
{
public:
	Bullet() = default;
	~Bullet() = default;

	Sprite bulletSprite;
	bool arrived = false;

	Bullet(string nameTexture)
	{
		if (!bulletTexture.loadFromFile(PATH_TO_TEXTURES + nameTexture + ".png"))
		{
			cout << "Сорян, не загрузилась: " << nameTexture << endl;
		}
		bulletSprite.setTexture(bulletTexture);
	}

	Vector2f GetPosition()
	{
		return pos;
	}

	void SetTexture(string nameTexture)
	{
		if (!bulletTexture.loadFromFile(PATH_TO_TEXTURES + nameTexture + ".png"))
		{
			cout << "Сорян, не загрузилась: " << nameTexture << endl;
		}
		bulletSprite.setTexture(bulletTexture);
	}

	void SetSpeed(float speed_)
	{
		speed = speed_;
	}

	void SetDamage(float damage_)
	{
		damage = damage_;
	}

	float GetDamage()
	{
		return damage;
	}

	void SetPosition(Vector2f pos_)
	{
		pos = pos_;
	}

	void SetEnemyPos(Vector2f EnemyPos)
	{
		posEnemy = EnemyPos;
	}

	void Update(float const &time)
	{
		dirVector = posEnemy - pos;
		distance = CalculateDistance(dirVector);
		direction = Vector2f(dirVector.x / distance, dirVector.y / distance);
		float dX = posEnemy.x - pos.x;
		float dY = posEnemy.y - pos.y;
		float angle = (atan2(dY, dX)) * 180 / 3.14159f + 90;
		bulletSprite.setRotation(angle);

		if (distance > 5)
		{
			pos += direction * speed * time;
		}
		else
		{
			arrived = true;
		}

		bulletSprite.setPosition(pos);
	}

	void Draw(RenderWindow & window)
	{
		window.draw(bulletSprite);
	}

private:
	Vector2f pos = Vector2f(0, 0);
	Vector2f posEnemy = Vector2f(0, 0);
	Vector2f dirVector = Vector2f(0, 0);
	Vector2f direction = Vector2f(0, 0);

	float speed = 1;
	float distance = 0;
	float damage = 5;

	Texture bulletTexture;
};

