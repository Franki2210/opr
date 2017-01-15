#pragma once

#include "Header.h"
#include "SpriteMap.h"

class Coin
{
public:
	SpriteMap spriteMap;
	bool destroy = false;

	Coin() = default;
	Coin(Texture & texture, int numColumns, int numLines)
	{
		spriteMap.SetSpriteMap(texture, numColumns, numLines);
		spriteMap.sprite.setScale(0.3f, 0.3f);
	}
	~Coin() = default;

	void SetSpriteMap(Texture & texture, int numColumns, int numLines)
	{
		spriteMap.SetSpriteMap(texture, numColumns, numLines);
		spriteMap.sprite.setScale(0.3f, 0.3f);
	}

	void SetValue(int value_)
	{
		value = value_;
		ostringstream valueString;
		valueString << value;
		text.setString("+" + valueString.str());
	}

	void SetFont(Font font_)
	{
		font = font_;
		text.setFont(font);
		text.setCharacterSize(20);
	}

	void SetPosition(Vector2f pos)
	{
		position = pos;
	}

	void Update(float & time)
	{
		if (timerToDisappearance > 0)
		{
			timerToDisappearance -= time;
			currFrame += 0.04f * time;
			if (currFrame > spriteMap.GetColumns()) currFrame = 0;
			spriteMap.SetFrame((int)currFrame);
			position = Vector2f(position.x, position.y - 0.04f * time);
			currAlpha -= byte(0.04 * time);
			if (currAlpha < 0) currAlpha = 0;
			spriteMap.sprite.setColor(Color(255, 255, 255, currAlpha));
			text.setColor(Color(255, 255, 255, currAlpha));
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
	float timerToDisappearance = 2000;
	float currFrame = 0;
	Vector2f position;
	byte currAlpha = 255;
	int value = 0;
	Font font;
	Text text;
};