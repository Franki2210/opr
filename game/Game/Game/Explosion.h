#pragma once
#include "Header.h"
#include "SpriteMap.h"

class Explosion
{
public:
	Explosion() = default;
	~Explosion() = default;

	void SetExplosion(Texture & texture, int columnsInMap, int linesInMap, float speedAnimation_)
	{
		spriteMap.SetSpriteMap(texture, columnsInMap, linesInMap);
		speedAnimation = speedAnimation_;
	}

	void SetSound(Sound *sound_)
	{
		sound = sound_;

	}
	Sound *GetSound()
	{
		return sound;
	}

	void SetPosition(Vector2f position)
	{
		spriteMap.sprite.setPosition(position);
	}

	bool GetIsDestroy()
	{
		return isDestroy;
	}

	void Update(float time)
	{
		currFrame += speedAnimation * time;
		spriteMap.SetFrame((int)currFrame);
		if (spriteMap.GetIsEndSpriteMap())
		{
			isDestroy = true;
		}
	}

	void Draw(RenderWindow & window)
	{
		window.draw(spriteMap.sprite);
	}

private:
	SpriteMap spriteMap;
	bool isDestroy = false;
	float speedAnimation;
	float currFrame = 0;
	Sound *sound;
};