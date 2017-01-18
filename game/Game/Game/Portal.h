#pragma once

#include "Header.h"
#include "SpriteMap.h"

class Portal
{
public:
	Portal() = default;
	~Portal() = default;

	void SetSpriteMap(Texture & texture, const int numColumns, const int numLines)
	{
		spriteMap.SetSpriteMap(texture, numColumns, numLines);
	}

	void SetSpeedAnimation(const float value)
	{
		speedAnimation = value;
	}

	void SetPosition(const float x, const float y)
	{
		spriteMap.SetPosition(x, y);
	}
	void SetPosition(const Vector2f pos)
	{
		spriteMap.SetPosition(pos);
	}

	void Update(const float time)
	{
		currFrame += speedAnimation * time;
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
	float speedAnimation = 0;
};
