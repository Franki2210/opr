#pragma once

class EnemyRemnants
{
public:
	EnemyRemnants();
	~EnemyRemnants();

	void SetEnemyExplosion(Texture & texture, int columnsInMap, int linesInMap);

	void SetSpeedAnimation(float value);

	void SetTimeToDestroy(float value);

	void SetPosition(Vector2f pos);
	void SetPosition(float x, float y);
	Vector2f GetPosition();

	bool GetIsDestroy();

	void Update(float time);

	void Draw(RenderWindow & window);
private:
	float timeToDestroy = 4000;
	float timerToDestroy = timeToDestroy;
	float currFrame = 0;
	float currAlpha = 255;
	SpriteMap spriteMap;
	Vector2f position;
	bool isDestroy = false;
	float speedAnimation = 0.14f;
};