#pragma once
#include "Header.h"
#include "CalcHelp.h"
#include "SpriteMap.h"
#include "Tower.h"
#include "Entity.h"
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

	Enemy() = default;
	Enemy(Texture texture, int columnInMap, int lineInMap)
	{
		spriteMapRun.SetSpriteMap(texture, columnInMap, lineInMap);
		damageArea.setRadius(25);
		damageArea.setFillColor(Color::Red);
		damageArea.setOrigin(damageArea.getRadius(), damageArea.getRadius());
		spriteMapRun.sprite.setScale(Vector2f(0.6f, 0.6f));
	}
	~Enemy() = default;

	//Текстурки движения и атаки
	void SetTextureRun(Texture & texture, int columnInMap, int lineInMap)
	{
		spriteMapRun.SetSpriteMap(texture, columnInMap, lineInMap);
		damageArea.setRadius(25);
		damageArea.setFillColor(Color::Red);
		damageArea.setOrigin(damageArea.getRadius(), damageArea.getRadius());
		spriteMapRun.sprite.setScale(Vector2f(0.6f, 0.6f));
	}
	void SetTextureAttack(Texture & texture, int columnInMap, int lineInMap)
	{
		spriteMapAttack.SetSpriteMap(texture, columnInMap, lineInMap);
		spriteMapAttack.sprite.setScale(Vector2f(0.6f, 0.6f));
		spriteMapAttack.sprite.setOrigin(spriteMapAttack.sprite.getLocalBounds().width / 3, spriteMapAttack.sprite.getLocalBounds().height / 2);
	}

	void SetSpeedRunAnimation(float speed)
	{
		runAnimSpeed = speed;
	}
	void SetSpeedAttackAnimation(float speed)
	{
		attackAnimSpeed = speed;
	}

	void SetScale(float scaleFactorX, float scaleFactorY)
	{
		spriteMapRun.sprite.setScale(scaleFactorX, scaleFactorY);
		spriteMapAttack.sprite.setScale(scaleFactorX, scaleFactorY);
	}

	void SetBossAnim(bool bossAnim)
	{
		isBossAnim = bossAnim;
	}
	bool GetBossAnim()
	{
		return isBossAnim;
	}

	//Цели для нападения
	void SetTarget(Player *player_)
	{
		player = player_;
	}
	void SetTarget(Tower *tower_)
	{
		tower = tower_;
	}
	Tower *GetNearTower()
	{
		return tower;
	}

	//Сколько монеток выпадет
	void SetCoins(int coins_)
	{
		coins = coins_;
	}
	int GetCoins()
	{
		return coins;
	}
	
	//Скорость
	void SetSpeed(float speed_)
	{
		speed = speed_;
	}

	void Update(float const &time)
	{
		if (isActive)
		{
			if (attackTimer > 0)
			{
				attackTimer -= time;
			}

			Vector2f posTarget;
			if (!attackingPlayer)
			{
				posTarget = tower->GetPosition();

			}
			else
			{
				posTarget = player->GetPosition();
			}

			Vector2f dirVector = posTarget - position;
			float distance = CalculateDistance(dirVector);
			float dY = dirVector.y;
			float dX = dirVector.x;
			double angle = (atan2(dY, dX)) * 180 / 3.14159265 + 90;
			if (angle < 0) angle += 360;
			moveVector = dirVector / distance;

			if (distance > 60)
			{
				attack = false;
				position += moveVector * speed * time;
				frameSpeed = runAnimSpeed;
			}
			else
			{
				attack = true;
				if (attackTimer <= 0)
				{
					if (!attackingPlayer) tower->TakeDamage(damage);
					else player->TakeDamage(damage);
					attackTimer = attackDelay;
				}
				frameSpeed = attackAnimSpeed;
			}

			//В зависимости от угла выбираем линию в карте спрайта (направление)
			lineInSpriteMap = int(angle / 22.5);
			if (isBossAnim)
			{
				if (lineInSpriteMap > spriteMapRun.GetLines() - 2)
				{
					lineInSpriteMap = 16 - lineInSpriteMap;
					if (!spriteMapAttack.GetFlipX() || !spriteMapRun.GetFlipX())
					{
						spriteMapAttack.SetFlipX(true);
						spriteMapRun.SetFlipX(true);
					}
				}
				else
				{
					if (spriteMapAttack.GetFlipX() || spriteMapRun.GetFlipX())
					{
						spriteMapAttack.SetFlipX(false);
						spriteMapRun.SetFlipX(false);
					}
				}
			}			
			currFrame += frameSpeed * time;
			if (attack)
			{
				if (currFrame > spriteMapAttack.GetColumns()) currFrame = 1;
			}
			else
			{
				if (currFrame > spriteMapRun.GetColumns()) currFrame = 1;
			}

			if (attack)
			{
				spriteMapAttack.SetPosition(position);
				spriteMapAttack.SetFrame((int)currFrame, lineInSpriteMap);
			}
			else
			{
				spriteMapRun.SetPosition(position);
				spriteMapRun.SetFrame((int)currFrame, lineInSpriteMap);
			}
			damageArea.setPosition(position);
			SetHpPosition(position);
		}
	}
	void Draw(RenderWindow & window)
	{
		if (attack)
		{
			window.draw(spriteMapAttack.sprite);
		}
		else
		{
			window.draw(spriteMapRun.sprite);
		}
		DrawHp(window);
	}

private:
	Vector2f moveVector;
	float speed = 0.2f;
	float attackDelay = 1000.0f; // = /1000 секунд
	float attackTimer = 0;
	Vector2f posAttackTarget;
	bool attack = false;
	float currFrame = 1;
	int lineInSpriteMap = 0;
	float frameSpeed = 0.04f;
	float runAnimSpeed = 0.04f;
	float attackAnimSpeed = 0.01f;
	int coins = 0;
	bool isBossAnim = false;
};