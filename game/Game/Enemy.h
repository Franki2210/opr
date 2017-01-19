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
	CircleShape damageArea;

	Tower *tower = nullptr;
	Player *player = nullptr;
	bool attackingPlayer = false;
	bool isActive = true;

	Enemy();
	Enemy(Texture & texture, const int columnInMap, const int lineInMap);
	~Enemy();

	//��������� �������� � �����
	void SetTextureRun(Texture & texture, const int columnInMap, const int lineInMap);
	void SetTextureAttack(Texture & texture, const int columnInMap, const int lineInMap);

	void SetSpeedRunAnimation(const float speedAnimation);
	void SetSpeedAttackAnimation(const float speedAnimation);

	void SetScale(const float scaleFactorX, const float scaleFactorY);

	void SetBossAnim(const bool bossAnim);
	bool GetBossAnim();

	//���� ��� ���������
	void SetTarget(Player *targetPlayer);
	void SetTarget(Tower *targetTower);
	Tower *GetNearTower();

	//������� ������� �������
	void SetCoins(const int coins_);
	int GetCoins();
	
	//��������
	void SetSpeed(const float speed_);

	void Update(const float time);
	void Draw(RenderWindow & window);

private:
	Vector2f moveVector;
	float speed = 0.2f;
	float attackDelay = 1000.0f; // = /1000 ������
	float attackTimer = 0;
	Vector2f posAttackTarget;
	bool attack = false;
	float currFrame = 1;
	int lineInSpriteMap = 0;
	float frameSpeed = 0.04f;
	float runAnimSpeed = 0.04f;
	float attackAnimationSpeed = 0.01f;
	int coins = 0;
	bool isBossAnim = false;
};