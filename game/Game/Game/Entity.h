#pragma once
#include "Header.h"
#include "SpriteMap.h"

class Entity
{
public:
	bool isDestroy = false;

	Entity()
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
		cout << "Создан Entity" << endl;
	}
	Entity(Vector2f pos, float HP, float damage_)
		: 
		position(pos),
		maxHp(HP),
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
	~Entity() = default;

	//Жизни
	void SetMaxHp(float maxHp_)
	{
		maxHp = maxHp_;
	}
	float GetMaxHp()
	{
		return maxHp;
	}
	float GetCurrentHp()
	{
		return currHp;
	}
	void SetHpPosition(Vector2f pos)
	{
		hpPosition = pos;
		hpSprite.setPosition(hpPosition);
		hpSpriteBG.setPosition(hpPosition);
	}

	//Урон
	void SetDamage(float damage_)
	{
		damage = damage_;
	}
	float GetDamage()
	{
		return damage;
	}
	//Принять урон
	void TakeDamage(float damage_)
	{
		currHp -= damage_;
		if (currHp < 0)
		{
			isDestroy = true;
		}
		else
		{
			hpSprite.setTextureRect(IntRect(0, 0, (int)(currHp * 50 / 100), 10));
		}
	}

	//Позиция
	void SetPosition(Vector2f pos)
	{
		position = pos;
		SetHpPosition(position);
	}
	void SetPosition(float x, float y)
	{
		position = Vector2f(x, y);
		SetHpPosition(position);
	}
	Vector2f GetPosition()
	{
		return position;
	}

	void DrawHp(RenderWindow & window)
	{
		window.draw(hpSpriteBG);
		window.draw(hpSprite);
	}

protected:
	float maxHp;
	float currHp;

	float damage;

	Vector2f position;

	Texture hpTex;
	Sprite hpSpriteBG;
	Sprite hpSprite;
	Color hpSpriteBGColor;
	Color hpSpriteColor;

	Vector2f hpPosition;
};