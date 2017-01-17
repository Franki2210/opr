#pragma once

#include "Header.h"
#include "SpriteMap.h"

class Coin
{
public:
	SpriteMap spriteMap;
	bool destroy = false;

	Coin() = default;
	Coin(Texture & texture, const int numColumns, const int numLines)
	{
		spriteMap.SetSpriteMap(texture, numColumns, numLines);
		spriteMap.sprite.setScale(0.3f, 0.3f);
	}
	~Coin() = default;

	void SetSpriteMap(Texture & texture, const int numColumns, const int numLines)
	{
		spriteMap.SetSpriteMap(texture, numColumns, numLines);
		spriteMap.sprite.setScale(0.3f, 0.3f);
	}

	void SetValue(const int value_)
	{
		value = value_;
		ostringstream valueString;
		valueString << value;
		text.setString("+" + valueString.str());
	}

	void SetFont(const Font font_)
	{
		font = font_;
		text.setFont(font);
		text.setCharacterSize(20);
	}

	void SetPosition(const Vector2f pos)
	{
		position = pos;
	}

	void Update(const float time)
	{
		if (timerToDestroy > 0)
		{
			timerToDestroy -= time;
			currFrame += 0.04f * time;
			if (currFrame > spriteMap.GetColumns()) currFrame = 0;
			spriteMap.SetFrame((int)currFrame);
			position = Vector2f(position.x, position.y - 0.04f * time);
			currAlpha -= 0.15f * time;
			if (currAlpha < 0) currAlpha = 0;
			spriteMap.sprite.setColor(Color(255, 255, 255, Uint8(currAlpha)));
			text.setColor(Color(255, 255, 255, Uint8(currAlpha)));
			spriteMap.sprite.setPosition(position);
			text.setPosition(position);
		}
		else
		{
			destroy = true;
		}
	}

	void Draw(RenderWindow & window)
	{
		window.draw(spriteMap.sprite);
		window.draw(text);
	}

private:
	float timerToDestroy = 2000;
	float currFrame = 0;
	Vector2f position;
	float currAlpha = 255;
	int value = 0;
	Font font;
	Text text;
};