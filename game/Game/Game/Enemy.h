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

	bool attackingPlayer = false;
	bool isActive = true;

	Enemy() = default;
	Enemy(string nameTexture, int columnInMap, int lineInMap)
	{
		spriteMapRun.SetSpriteMap(nameTexture, columnInMap, lineInMap);
		damageArea.setRadius(25);
		damageArea.setFillColor(Color::Red);
		damageArea.setOrigin(damageArea.getRadius(), damageArea.getRadius());
		spriteMapRun.sprite.setScale(Vector2f(0.6f, 0.6f));
	}

	~Enemy() = default;

	void SetTextureRun(string nameTexture, int columnInMap, int lineInMap)
	{
		spriteMapRun.SetSpriteMap(nameTexture, columnInMap, lineInMap);
		damageArea.setRadius(25);
		damageArea.setFillColor(Color::Red);
		damageArea.setOrigin(damageArea.getRadius(), damageArea.getRadius());
		spriteMapRun.sprite.setScale(Vector2f(0.6f, 0.6f));
	}

	void SetTextureAttack(string nameTexture, int columnInMap, int lineInMap)
	{
		spriteMapAttack.SetSpriteMap(nameTexture, columnInMap, lineInMap);
		spriteMapAttack.sprite.setScale(Vector2f(0.6f, 0.6f));
		spriteMapAttack.sprite.setOrigin(spriteMapAttack.sprite.getLocalBounds().width / 3, spriteMapAttack.sprite.getLocalBounds().height / 2);
	}

	void SetTarget(Tower *tower_)
	{
		tower = tower_;
	}
	Tower *GetNearTower()
	{
		return tower;
	}

	void SetTarget(Player *player_)
	{
		player = player_;
	}

	void SetSpeed(float speed_)
	{
		speed = speed_;
	}

	Tower *tower = nullptr;
	Player *player;

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
			if (true)
			{

			}
			if (distance > 60)
			{
				attack = false;
				position += moveVector * speed * time;
				frameSpeed = 0.04f;
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
				frameSpeed = 0.01f;
			}

			//В зависимости от угла выбираем линию в карте спрайта (направление)
			lineInSpriteMap = angle / 22.5;
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
		//window.draw(currSpriteMap.sprite);
		DrawHp(window);
	}


private:
	Vector2f moveVector;
	float speed = 0.2f;
	float attackDelay = 1000; // = /1000 секунд
	float attackTimer = 0;
	Vector2f posAttackTarget;
	bool attack = false;
	float currFrame = 1;
	int lineInSpriteMap = 0;
	float frameSpeed = 0.04f;
};

