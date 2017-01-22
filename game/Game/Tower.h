#pragma once
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

	sf::CircleShape actionArea;
	sf::CircleShape boundsArea;

	Tower();
	~Tower();
	Tower(sf::Texture & texture, int column, int line);

	void SetSpriteMap(sf::Texture & texture, int column, int line);

	void SetActionRadius(const float radius);

	int GetNumFrameFromDirection(sf::Vector2f posEnemy);

	void SetBullet(Bullet usedBullet);
	Bullet GetBullet();

	void SetReloadTime(float value);

	void SetPrice(int value);
	int GetPrice();

	sf::Vector2f GetEnemyPos();

	void Update(const float time, sf::Vector2f posEnemy);
	void Update();
	void Draw(sf::RenderWindow & window);

private:
	float currFrame = 0;
	sf::Vector2f enemyPos;
	int price = 0;
};