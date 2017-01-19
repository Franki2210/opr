#include "Header.h"
#include "Enemy.h"
#include "CalcHelp.h"
#include "SpriteMap.h"
#include "Tower.h"
#include "Entity.h"
#include "Player.h"

Enemy::Enemy() = default;
Enemy::Enemy(Texture & texture, const int columnInMap, const int lineInMap)
{
	spriteMapRun.SetSpriteMap(texture, columnInMap, lineInMap);
	damageArea.setRadius(25);
	damageArea.setFillColor(Color::Red);
	damageArea.setOrigin(damageArea.getRadius(), damageArea.getRadius());
	spriteMapRun.sprite.setScale(Vector2f(0.6f, 0.6f));
}
Enemy::~Enemy() = default;

//Текстурки движения и атаки
void Enemy::SetTextureRun(Texture & texture, const int columnInMap, const int lineInMap)
{
	spriteMapRun.SetSpriteMap(texture, columnInMap, lineInMap);
	damageArea.setRadius(25);
	damageArea.setFillColor(Color::Red);
	damageArea.setOrigin(damageArea.getRadius(), damageArea.getRadius());
	spriteMapRun.sprite.setScale(Vector2f(0.6f, 0.6f));
}
void Enemy::SetTextureAttack(Texture & texture, const int columnInMap, const int lineInMap)
{
	spriteMapAttack.SetSpriteMap(texture, columnInMap, lineInMap);
	spriteMapAttack.sprite.setScale(Vector2f(0.6f, 0.6f));
	spriteMapAttack.sprite.setOrigin(spriteMapAttack.sprite.getLocalBounds().width / 3, spriteMapAttack.sprite.getLocalBounds().height / 2);
}

void Enemy::SetSpeedRunAnimation(const float speedAnimation)
{
	runAnimSpeed = speedAnimation;
}
void Enemy::SetSpeedAttackAnimation(const float speedAnimation)
{
	this->attackAnimationSpeed = speedAnimation;
}

void Enemy::SetScale(const float scaleFactorX, const float scaleFactorY)
{
	spriteMapRun.sprite.setScale(scaleFactorX, scaleFactorY);
	spriteMapAttack.sprite.setScale(scaleFactorX, scaleFactorY);
}

void Enemy::SetBossAnim(const bool bossAnim)
{
	isBossAnim = bossAnim;
}
bool Enemy::GetBossAnim()
{
	return isBossAnim;
}

//Цели для нападения
void Enemy::SetTarget(Player *targetPlayer)
{
	player = targetPlayer;
}
void Enemy::SetTarget(Tower *targetTower)
{
	tower = targetTower;
}
Tower *Enemy::GetNearTower()
{
	return tower;
}

//Сколько монеток выпадет
void Enemy::SetCoins(const int coins_)
{
	coins = coins_;
}
int Enemy::GetCoins()
{
	return coins;
}

//Скорость
void Enemy::SetSpeed(const float speed_)
{
	speed = speed_;
}

void Enemy::Update(const float time)
{
	if (attackTimer > 0) attackTimer -= time;

	Vector2f posTarget;
	if (!attackingPlayer) posTarget = tower->GetPosition();
	else posTarget = player->GetPosition();

	Vector2f dirVector = posTarget - position;
	float distance = CalculateDistance(dirVector);
	double angle = (atan2(dirVector.y, dirVector.x)) * 180 / 3.14159265 + 90;
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
			if (attackingPlayer) player->TakeDamage(damage);
			else tower->TakeDamage(damage);
			attackTimer = attackDelay;
		}
		frameSpeed = attackAnimationSpeed;
	}

	//В зависимости от угла выбираем линию в карте спрайта (направление)
	if (isBossAnim)
	{
		lineInSpriteMap = int(angle / (360.0f / (spriteMapRun.GetLines() * 2 - 2)));
		if (lineInSpriteMap > spriteMapRun.GetLines() - 2)
		{
			lineInSpriteMap = spriteMapRun.GetLines() * 2 - 2 - lineInSpriteMap;
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
	else lineInSpriteMap = int(angle / (360.0f / (float)spriteMapRun.GetLines()));

	if (lineInSpriteMap > spriteMapRun.GetLines())
	{
		lineInSpriteMap = spriteMapRun.GetLines();
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
void Enemy::Draw(RenderWindow & window)
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