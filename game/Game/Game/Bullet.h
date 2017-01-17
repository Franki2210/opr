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
		bulletSprite.setTexture(texture);
	}
	~Bullet() = default;

	Sprite bulletSprite;
	bool arrived = false;

	Vector2f GetPosition()
	{
		return pos;
	}

	void SetTexture(Texture & texture)
	{
		bulletSprite.setTexture(texture);
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
	void SetVolumeSounds(float volume)
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

	void SetDamage(float damage_)
	{
		damage = damage_;
	}
	float GetDamage()
	{
		return damage;
	}

	void SetStartPosition(Vector2f pos_)
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

	SoundsBullet soundsBullet;
};