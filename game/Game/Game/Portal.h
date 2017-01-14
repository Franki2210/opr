#pragma once

#include "Header.h"
#include "SpriteMap.h"

class Portal
{
public:
	Portal() = default;
	~Portal() = default;

	void SetSpriteMap(string nameTexture, int numColumns, int numLines)
	{
		spriteMap.SetSpriteMap(nameTexture, numColumns, numLines);
	}

	void SetPosition(float x, float y)
	{
		spriteMap.SetPosition(x, y);
	}
	void SetPosition(Vector2f pos)
	{
		spriteMap.SetPosition(pos);
	}

	void Update(float time)
	{
		currFrame += 0.01 * time;
		if (currFrame > spriteMap.GetColumns()) currFrame = 0;
		spriteMap.SetFrame(currFrame);
	}

	void Draw(RenderWindow & window)
	{
		window.draw(spriteMap.sprite);
	}

private:
	SpriteMap spriteMap;
	float currFrame = 0;
};
