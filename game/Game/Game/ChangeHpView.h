#pragma once
#include "Header.h"
#include <iomanip>

class ChangeHpView
{
public:
	bool destroy = false;

	ChangeHpView() = default;
	ChangeHpView(float value_, Vector2f position_) 
		: value(value_), position(position_) 
	{
		ostringstream valueString;
		valueString << value;
		text.setString("-" + valueString.str());
		position = Vector2f(position.x + rand() % 10, position.y);
	}
	~ChangeHpView() = default;

	void SetValue(float value_)
	{
		value = value_;
		ostringstream valueString;
		valueString << value;
		text.setString("-" + valueString.str());
	}

	void SetFont(Font font_)
	{
		font = font_;
		text.setFont(font);
		text.setCharacterSize(12);
	}

	void SetPosition(Vector2f pos)
	{
		position = pos;
		position = Vector2f(position.x + rand() % 10, position.y);
	}

	void Update(float & time)
	{
		if (timerToDisappearance > 0)
		{
			timerToDisappearance -= time;
			position = Vector2f(position.x, position.y - 0.05f * time);
			currAlpha -= 0.2f * time;
			if (currAlpha < 0) currAlpha = 0;
			text.setColor(Color(255, 50, 50, Uint8(currAlpha)));
			text.setPosition(position);
		}
		else
		{
			destroy = true;
		}
	}

	void Draw(RenderWindow & window)
	{
		window.draw(text);
	}

private:
	float timerToDisappearance = 500;
	Vector2f position;
	float currAlpha = 255;
	float value = 0;
	Font font;
	Text text;
};