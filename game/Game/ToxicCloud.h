#pragma once

class ToxicCloud
{
public:
	ToxicCloud();
	~ToxicCloud();

	void SetToxicCloud(Texture & texture, int columnsInMap, int linesInMap);

	void SetPosition(Vector2f pos);
	void SetPosition(float x, float y);
	Vector2f GetPosition();

	void SetSpeedAnimation(float value);

	FloatRect GetGlobalBounds();

	void SetTimeToDestroy(float value);

	void SetSpeedDamage(float value);
	float GetSpeedDamage();

	void SetDamage(float value);
	float GetDamage();

	bool GetIsDestroy();

	void Update(const float time);

	void Draw(RenderWindow & window);

private:
	Vector2f position;
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