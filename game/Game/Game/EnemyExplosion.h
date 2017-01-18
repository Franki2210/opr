#pragma once
#include "Header.h"

class EnemyExplosion
{
public:
	EnemyExplosion() = default;
	~EnemyExplosion() = default;

	void SetEnemyExplosion(Texture & texture, int columnsInMap, int linesInMap)
	{
		spriteMap.SetSpriteMap(texture, columnsInMap, linesInMap);
	}

	void SetSpeedAnimation(float value)
	{
		speedAnimation = value;
	}

	void SetTimeToDestroy(float value)
	{
		timeToDestroy = value;
		timerToDestroy = timeToDestroy;
	}

	void SetPosition(Vector2f pos)
	{
		position = pos;
		spriteMap.sprite.setPosition(position);
	}
	void SetPosition(float x, float y)
	{
		position = Vector2f(x, y);
		spriteMap.sprite.setPosition(position);
	}
	Vector2f GetPosition()
	{
		return position;
	}

	bool GetIsDestroy()
	{
		return isDestroy;
	}

	void Update(float time)
	{
		if (timerToDestroy > 0)
		{
			timerToDestroy -= time;
			if (currFrame < spriteMap.GetColumns() * spriteMap.GetLines())
			{
				spriteMap.SetFrame((int)currFrame);
				currFrame += speedAnimation * time;
			}
			if (timerToDestroy < 2000)
			{
				currAlpha -= 0.13f * time;
				if (currAlpha <= 0) currAlpha = 0;
				spriteMap.sprite.setColor(Color(255, 255, 255, (Uint8)currAlpha));
			}
		}
		else isDestroy = true;
	}

	void Draw(RenderWindow & window)
	{
		window.draw(spriteMap.sprite);
	}
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