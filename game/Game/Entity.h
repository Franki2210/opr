#pragma once

class Entity
{
public:
	bool isDestroy = false;

	Entity();
	Entity(Vector2f pos, float HP, float damage_);
	~Entity();

	//Жизни
	void SetMaxHp(const float maxHp_);
	float GetMaxHp();
	void AddHp(const float value);
	void SetCurrentHp(const float hp);
	float GetCurrentHp();

	void SetHpPosition(const Vector2f pos);

	//Урон
	void SetDamage(const float damage_);
	float GetDamage();
	//Принять урон
	void TakeDamage(const float damage_);

	//Позиция
	void SetPosition(const Vector2f pos);
	void SetPosition(const float x, const float y);
	Vector2f GetPosition();

	void DrawHp(RenderWindow & window);

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