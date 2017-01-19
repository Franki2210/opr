#include "Header.h"
#include "SpriteMap.h"
#include "Entity.h"

Entity::Entity()
{
	currHp = maxHp = 100;
	position = Vector2f(0, 0);
	damage = 1;
	hpSpriteBG.setTexture(hpTex);
	hpSprite.setTexture(hpTex);
	hpSpriteBG.setTextureRect(IntRect(0, 0, 50, 10));
	hpSprite.setTextureRect(IntRect(0, 0, 50, 10));
	hpSpriteBGColor = Color(200, 0, 0, 100);
	hpSpriteColor = Color(0, 200, 0, 100);
	hpSpriteBG.setColor(hpSpriteBGColor);
	hpSprite.setColor(hpSpriteColor);
	hpSpriteBG.setOrigin(25.f, 50.f);
	hpSprite.setOrigin(25.f, 50.f);
}
Entity::Entity(Vector2f pos, float HP, float damage_)
	:
	position(pos),
	maxHp(HP),
	currHp(HP),
	damage(damage_)
{
	hpSpriteBG.setTexture(hpTex);
	hpSprite.setTexture(hpTex);
	hpSpriteBG.setTextureRect(IntRect(0, 0, 50, 10));
	hpSprite.setTextureRect(IntRect(0, 0, 50, 10));
	hpSpriteBGColor = Color(200, 0, 0, 100);
	hpSpriteColor = Color(0, 200, 0, 100);
	hpSpriteBG.setOrigin(25.f, 5.f);
	hpSprite.setOrigin(25.f, 5.f);
	hpPosition = Vector2f(0.f, 45.f);
}
Entity::~Entity() = default;

//Жизни
void Entity::SetMaxHp(const float maxHp_)
{
	maxHp = maxHp_;
	currHp = maxHp;
}
float Entity::GetMaxHp()
{
	return maxHp;
}
void Entity::AddHp(const float value)
{
	if (currHp + value > maxHp) currHp = maxHp;
	else currHp += value;
	hpSprite.setTextureRect(IntRect(0, 0, (int)(currHp / maxHp * 50), 10));
}
void Entity::SetCurrentHp(const float hp)
{
	currHp = hp;
}
float Entity::GetCurrentHp()
{
	return currHp;
}
void Entity::SetHpPosition(const Vector2f pos)
{
	hpPosition = pos;
	hpSprite.setPosition(hpPosition);
	hpSpriteBG.setPosition(hpPosition);
}

//Урон
void Entity::SetDamage(const float damage_)
{
	damage = damage_;
}
float Entity::GetDamage()
{
	return damage;
}
//Принять урон
void Entity::TakeDamage(const float damage_)
{
	currHp -= damage_;
	if (currHp < 0)
	{
		isDestroy = true;
	}
	else
	{
		hpSprite.setTextureRect(IntRect(0, 0, (int)(currHp / maxHp * 50), 10));
	}
}

//Позиция
void Entity::SetPosition(const Vector2f pos)
{
	position = pos;
	SetHpPosition(position);
}
void Entity::SetPosition(const float x, const float y)
{
	position = Vector2f(x, y);
	SetHpPosition(position);
}
Vector2f Entity::GetPosition()
{
	return position;
}

void Entity::DrawHp(RenderWindow & window)
{
	window.draw(hpSpriteBG);
	window.draw(hpSprite);
}