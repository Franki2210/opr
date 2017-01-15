#pragma once

#include "Header.h"
#include "SpriteMap.h"

class Portal
{
public:
	Portal() = default;
	~Portal() = default;

	void SetSpriteMap(Texture & texture, int numColumns, int numLines)
	{
		spriteMap.SetSpriteMap(texture, numColumns, numLines);
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
		currFrame += 0.01f * time;
		if (currFrame > spriteMap.GetColumns()) currFrame = 0;
		spriteMap.SetFrame((int)currFrame);
	}

	void Draw(RenderWindow & window)
	{
		window.draw(spriteMap.sprite);
	}

private:
	SpriteMap spriteMap;
	float currFrame = 0;
};
