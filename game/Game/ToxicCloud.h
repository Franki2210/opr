#pragma once

class ToxicCloud
{
public:
	ToxicCloud();
	~ToxicCloud();

	void SetToxicCloud(sf::Texture & texture, int columnsInMap, int linesInMap);

	void SetPosition(sf::Vector2f pos);
	void SetPosition(float x, float y);
	sf::Vector2f GetPosition();

	void SetSpeedAnimation(float value);

	sf::FloatRect GetGlobalBounds();

	void SetTimeToDestroy(float value);

	void SetSpeedDamage(float value);
	float GetSpeedDamage();

	void SetDamage(float value);
	float GetDamage();

	bool GetIsDestroy();

	void Update(const float time);

	void Draw(sf::RenderWindow & window);

private:
	sf::Vector2f position;
	float timeToDestroy = 10000;
	float timerToDestroy = timeToDestroy;
	bool isDestroy = false;
	SpriteMap spriteMap;
	float speedAnimation = 1;
	float currFrame = 1;
	float speedDamage = 0;
	float damage = 0;
	float currAlpha = 0;
};