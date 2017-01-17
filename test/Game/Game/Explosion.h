#pragma once
#include "Header.h"
#include "SpriteMap.h"

class Explosion
{
public:
	Explosion() = default;
	~Explosion() = default;

	void SetExplosion(Texture & texture, const int columnsInMap, const int linesInMap, const float speedAnimation_)
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

	void SetPosition(const Vector2f position)
	{
		spriteMap.sprite.setPosition(position);
	}

	bool GetIsDestroy()
	{
		return isDestroy;
	}

	void Update(const float time)
	{
		currFrame += speedAnimation * time;
		spriteMap.SetFrame((int)currFrame);
		if (currFrame >= spriteMap.GetColumns() * spriteMap.GetLines())
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