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

	CircleShape actionArea;
	CircleShape boundsArea;

	Tower();
	~Tower();
	Tower(Texture & texture, int column, int line);

	void SetSpriteMap(Texture & texture, int column, int line);

	void SetActionRadius(float radius);

	int GetNumFrameFromDirection(Vector2f posEnemy);

	void SetBullet(Bullet usedBullet);
	Bullet GetBullet();

	void SetReloadTime(float value);

	void SetPrice(int value);
	int GetPrice();

	Vector2f GetEnemyPos();

	void Update(const float time, Vector2f posEnemy);
	void Update();
	void Draw(RenderWindow & window);

private:
	float currFrame = 0;
	Vector2f enemyPos;
	int price;
};