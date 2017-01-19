#pragma once
#include "Header.h"
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
	Bullet(Texture & texture);
	~Bullet() = default;

	Vector2f GetPosition();

	void SetTexture(Texture & texture);

	void SetSpeed(const float speed);

	void SetSounds(Sound *sound1, Sound *sound2, Sound *sound3);
	void SetVolumeSounds(const float volume);
	float GetVolumeSounds();
	Sound *GetSound();

	bool GetIsDestroy();
	void SetIsDestroy(const bool value);

	void SetScaleSprite(const float x, const float y);

	void SetDamage(const float damage);
	float GetDamage();

	void SetStartPosition(const Vector2f pos_);

	void SetEnemyPos(const Vector2f EnemyPos);

	void Update(const float time);

	void Draw(RenderWindow & window);

private:
	Vector2f position = Vector2f(0, 0);
	Vector2f positionEnemy = Vector2f(0, 0);
	Vector2f dirVector = Vector2f(0, 0);
	Vector2f direction = Vector2f(0, 0);

	float speed = 1;
	float distance = 0;
	float damage = 5;

	Sprite sprite;
	bool isDestroy = false;

	SoundsBullet soundsBullet;
};