#pragma once

class Entity
{
public:
	bool isDestroy = false;

	Entity();
	Entity(sf::Vector2f pos, float HP, float damage);
	~Entity();

	//Жизни
	void SetMaxHp(const float maxHp);
	float GetMaxHp();
	void AddHp(const float value);
	void SetCurrentHp(const float hp);
	float GetCurrentHp();

	void SetHpPosition(const sf::Vector2f pos);

	//Урон
	void SetDamage(const float value);
	float GetDamage();
	//Принять урон
	void TakeDamage(const float value);

	//Позиция
	void SetPosition(const sf::Vector2f pos);
	void SetPosition(const float x, const float y);
	sf::Vector2f GetPosition();

	void DrawHp(sf::RenderWindow & window);

protected:
	float maxHp;
	float currHp;

	float damage;

	sf::Vector2f position;

	sf::Texture hpTex;
	sf::Sprite hpSpriteBG;
	sf::Sprite hpSprite;
	sf::Color hpSpriteBGColor;
	sf::Color hpSpriteColor;

	sf::Vector2f hpPosition;
};