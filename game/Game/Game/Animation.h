#pragma once
#include "Header.h"
#include "SpriteMap.h"


class Animation
{
public:
	Animation() = default;

	SpriteMap currMap;

	void SetDefaultIdleTextureMap(const String &nameTexture, int columns, int lines)
	{
		spriteMapIdle.SetSpriteMap(nameTexture, columns, lines);
	}
	void SetIdleGunTextureMap(const String &nameTexture, int columns, int lines)
	{
		spriteMapIdleGun.SetSpriteMap(nameTexture, columns, lines);
	}
	void SetDefaultRunTextureMap(const String &nameTexture, int columns, int lines)
	{
		spriteMapRun.SetSpriteMap(nameTexture, columns, lines);
	}
	void SetRunGunTextureMap(const String &nameTexture, int columns, int lines)
	{
		spriteMapRunGun.SetSpriteMap(nameTexture, columns, lines);
	}

	void Update(float const &time, bool isMove, Direction direction)
	{
		if (isMove)
		{
			currMap = spriteMapRun;
			currFrame += 0.04f * time;
		}
		else
		{
			currMap = spriteMapIdle;
			currFrame += 0.01f * time;
		}

		if (currFrame > currMap.GetColumns()) currFrame = 1;
		currMap.SetFrame(direction, currFrame);
	}

private:
	SpriteMap spriteMapIdle;
	SpriteMap spriteMapRun;
	SpriteMap spriteMapIdleGun;
	SpriteMap spriteMapRunGun;
	float currFrame = 0;
};