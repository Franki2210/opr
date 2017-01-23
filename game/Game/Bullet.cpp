#include "Header.h"
#include "Bullet.h"
#include "CalcHelp.h"

using namespace sf;

Bullet::Bullet(Texture & texture)
{
	sprite.setTexture(texture);
}

Vector2f Bullet::GetPosition()
{
	return position;
}

void Bullet::SetTexture(Texture & texture)
{
	sprite.setTexture(texture);
}

void Bullet::SetSpeed(const float speed)
{
	this->speed = speed;
}

void Bullet::SetSounds(Sound * sound1, Sound * sound2, Sound * sound3)
{
	soundsBullet.sound1 = sound1;
	soundsBullet.sound2 = sound2;
	soundsBullet.sound3 = sound3;
}
void Bullet::SetVolumeSounds(const float volume)
{
	soundsBullet.sound1->setVolume(volume);
	soundsBullet.sound2->setVolume(volume);
	soundsBullet.sound3->setVolume(volume);
}
float Bullet::GetVolumeSounds()
{
	return soundsBullet.sound1->getVolume();
}
Sound *Bullet::GetSound()
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

bool Bullet::GetIsDestroy()
{
	return isDestroy;
}
void Bullet::SetIsDestroy(const bool value)
{
	isDestroy = value;
}

void Bullet::SetScaleSprite(const float x, const float y)
{
	sprite.setScale(x, y);
}

void Bullet::SetDamage(const float damage)
{
	this->damage = damage;
}
float Bullet::GetDamage()
{
	return damage;
}

void Bullet::SetStartPosition(const Vector2f startPosition)
{
	position = startPosition;
}

void Bullet::SetEnemyPos(const Vector2f EnemyPosition)
{
	positionEnemy = EnemyPosition;
}

void Bullet::Update(const float time)
{
	dirVector = positionEnemy - position;
	distance = CalculateDistance(dirVector);
	direction = Vector2f(dirVector.x / distance, dirVector.y / distance);
	float dX = positionEnemy.x - position.x;
	float dY = positionEnemy.y - position.y;
	float angle = (atan2(dY, dX)) * 180 / 3.14159f + 90;
	sprite.setRotation(angle);

	if (distance > 5)
	{
		position += direction * speed * time;
	}
	else
	{
		isDestroy = true;
	}

	sprite.setPosition(position);
}

void Bullet::Draw(RenderWindow & window)
{
	window.draw(sprite);
}