#pragma once
#include "Header.h"
#include "Entity.h"
#include "SpriteMap.h"
#include "Tower.h"
#include "Player.h"

class Enemy : public Entity
{
public:
	SpriteMap spriteMapRun;
	SpriteMap spriteMapAttack;
	sf::CircleShape damageArea;

	Tower *tower = nullptr;
	Player *player = nullptr;
	bool attackingPlayer = false;
	bool isActive = true;

	Enemy();
	Enemy(sf::Texture & texture, const int columnInMap, const int lineInMap);
	~Enemy();

	//Текстурки движения и атаки
	void SetTextureRun(sf::Texture & texture, const int columnInMap, const int lineInMap);
	void SetTextureAttack(sf::Texture & texture, const int columnInMap, const int lineInMap);

	void SetSpeedRunAnimation(const float speedAnimation);
	void SetSpeedAttackAnimation(const float speedAnimation);

	void SetScale(const float scaleFactorX, const float scaleFactorY);

	void SetBossAnim(const bool bossAnim);
	bool GetBossAnim();

	//Цели для нападения
	void SetTarget(Player *targetPlayer);
	void SetTarget(Tower *targetTower);
	Tower *GetNearTower();

	//Сколько монеток выпадет
	void SetCoins(const int coinsEnenmy);
	int GetCoins();
	
	//Скорость
	void SetSpeed(const float speedEnemy);

	void Update(const float time);
	void Draw(sf::RenderWindow & window);

private:
	sf::Vector2f moveVector;
	float speed = 0.2f;
	float attackDelay = 1000.0f; // = /1000 секунд
	float attackTimer = 0;
	sf::Vector2f posAttackTarget;
	bool attack = false;
	float currFrame = 1;
	int lineInSpriteMap = 0;
	float frameSpeed = 0.04f;
	float runAnimSpeed = 0.04f;
	float attackAnimationSpeed = 0.01f;
	int coins = 0;
	bool isBossAnim = false;
};