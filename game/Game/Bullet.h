#pragma once
#include "Header.h"
struct SoundsBullet
{
	sf::Sound sound1;
	sf::Sound sound2;
	sf::Sound sound3;
};

class Bullet
{
public:
	Bullet() = default;
	Bullet(sf::Texture & texture);
	~Bullet() = default;

	sf::Vector2f GetPosition();

	void SetTexture(sf::Texture & texture);

	void SetSpeed(const float speed);

	void SetSounds(sf::Sound & sound1, sf::Sound & sound2, sf::Sound & sound3);
	void SetVolumeSounds(const float volume);
	float GetVolumeSounds();
	sf::Sound &GetSound();

	bool GetIsDestroy();
	void SetIsDestroy(const bool value);

	void SetScaleSprite(const float x, const float y);

	void SetDamage(const float damage);
	float GetDamage();

	void SetStartPosition(const sf::Vector2f startPosition);

	void SetEnemyPos(const sf::Vector2f EnemyPos);

	void Update(const float time);

	void Draw(sf::RenderWindow & window);

private:
	sf::Vector2f position = sf::Vector2f(0, 0);
	sf::Vector2f positionEnemy = sf::Vector2f(0, 0);
	sf::Vector2f dirVector = sf::Vector2f(0, 0);
	sf::Vector2f direction = sf::Vector2f(0, 0);

	float speed = 1;
	float distance = 0;
	float damage = 5;

	sf::Sprite sprite;
	bool isDestroy = false;

	SoundsBullet soundsBullet;
};