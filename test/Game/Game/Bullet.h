#pragma once
#include "Header.h"
#include "CalcHelp.h"

struct SoundsBullet
{
	Sound *sound1;
	Sound *sound2;
	Sound *sound3;
};

class Bullet
{
public:
	Bullet() = default;
	Bullet(Texture & texture)
	{
		sprite.setTexture(texture);
	}
	~Bullet() = default;

	Vector2f GetPosition()
	{
		return pos;
	}

	void SetTexture(Texture & texture)
	{
		sprite.setTexture(texture);
	}

	void SetSpeed(float speed_)
	{
		speed = speed_;
	}

	void SetSounds(Sound *sound1, Sound *sound2, Sound *sound3)
	{
		soundsBullet.sound1 = sound1;
		soundsBullet.sound2 = sound2;
		soundsBullet.sound3 = sound3;
	}
	void SetVolumeSounds(const float volume)
	{
		soundsBullet.sound1->setVolume(volume);
		soundsBullet.sound2->setVolume(volume);
		soundsBullet.sound3->setVolume(volume);
	}
	float GetVolumeSounds()
	{
		return soundsBullet.sound1->getVolume();
	}
    Sound *GetSound()
	{
		int randSound = rand() % 3;
		switch (randSound) 
		{
		case 0: return soundsBullet.sound1;
		case 1: return soundsBullet.sound2;
		case 2: return soundsBullet.sound3;
		default: return soundsBullet.sound1;
		}
	}

	bool GetIsDestroy()
	{
		return isDestroy;
	}
	void SetIsDestroy(const bool value)
	{
		isDestroy = value;
	}

	void SetScaleSprite(const float x, const float y)
	{
		sprite.setScale(x, y);
	}

	void SetDamage(const float damage_)
	{
		damage = damage_;
	}
	float GetDamage()
	{
		return damage;
	}

	void SetStartPosition(const Vector2f pos_)
	{
		pos = pos_;
	}

	void SetEnemyPos(const Vector2f EnemyPos)
	{
		posEnemy = EnemyPos;
	}

	void Update(const float time)
	{
		dirVector = posEnemy - pos;
		distance = CalculateDistance(dirVector);
		direction = Vector2f(dirVector.x / distance, dirVector.y / distance);
		float dX = posEnemy.x - pos.x;
		float dY = posEnemy.y - pos.y;
		float angle = (atan2(dY, dX)) * 180 / 3.14159f + 90;
		sprite.setRotation(angle);

		if (distance > 5)
		{
			pos += direction * speed * time;
		}
		else
		{
			isDestroy = true;
		}

		sprite.setPosition(pos);
	}

	void Draw(RenderWindow & window)
	{
		window.draw(sprite);
	}

private:
	Vector2f pos = Vector2f(0, 0);
	Vector2f posEnemy = Vector2f(0, 0);
	Vector2f dirVector = Vector2f(0, 0);
	Vector2f direction = Vector2f(0, 0);

	float speed = 1;
	float distance = 0;
	float damage = 5;

	Sprite sprite;
	bool isDestroy = false;

	SoundsBullet soundsBullet;
};