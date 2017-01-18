#pragma once
#include "Header.h"

class ToxicCloud
{
public:
	ToxicCloud() = default;
	~ToxicCloud() = default;

	void SetToxicCloud(Texture & texture, int columnsInMap, int linesInMap)
	{
		spriteMap.SetSpriteMap(texture, columnsInMap, linesInMap);
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

	void SetSpeedAnimation(float value)
	{
		speedAnimation = value;
	}

	FloatRect GetGlobalBounds()
	{
		return spriteMap.sprite.getGlobalBounds();
	}

	void SetTimeToDestroy(float value)
	{
		timeToDestroy = value;
		timerToDestroy = timeToDestroy;
	}

	void SetSpeedDamage(float value)
	{
		speedDamage = value;
	}
	float GetSpeedDamage()
	{
		return speedDamage;
	}

	void SetDamage(float value)
	{
		damage = value;
	}
	float GetDamage()
	{
		return damage;
	}

	bool GetIsDestroy()
	{
		return isDestroy;
	}

	void Update(const float time)
	{
		if (timerToDestroy > 0)
		{
			timerToDestroy -= time;
			currFrame += speedAnimation * time;
			if (currFrame >= spriteMap.GetColumns() * spriteMap.GetLines())
			{
				currFrame = 0;
			}
			spriteMap.SetFrame((int)currFrame);
			if (timerToDestroy < timeToDestroy && timerToDestroy > timeToDestroy - 1000.0f)
			{
				currAlpha += 0.26f * time;
				if (currAlpha >= 255) currAlpha = 255;
				spriteMap.sprite.setColor(Color(255, 255, 255, (Uint8)currAlpha));
			}
			if (timerToDestroy < 2000)
			{
				currAlpha -= 0.13f * time;
				if (currAlpha <= 0) currAlpha = 0;
				spriteMap.sprite.setColor(Color(255, 255, 255, (Uint8)currAlpha));
			}
		}
		else
		{
			isDestroy = true;
		}
	}

	void Draw(RenderWindow & window)
	{
		window.draw(spriteMap.sprite);
	}

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