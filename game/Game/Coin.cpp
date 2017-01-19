#include "Header.h"
#include "SpriteMap.h"
#include "Coin.h"

Coin::Coin() = default;
Coin::Coin(Texture & texture, const int numColumns, const int numLines)
{
	spriteMap.SetSpriteMap(texture, numColumns, numLines);
	spriteMap.sprite.setScale(0.3f, 0.3f);
}
Coin::~Coin() = default;

void Coin::SetSpriteMap(Texture & texture, const int numColumns, const int numLines)
{
	spriteMap.SetSpriteMap(texture, numColumns, numLines);
	spriteMap.sprite.setScale(0.3f, 0.3f);
}

void Coin::SetValue(const int value_)
{
	value = value_;
	ostringstream valueString;
	valueString << value;
	text.setString("+" + valueString.str());
}

void Coin::SetFont(const Font font_)
{
	font = font_;
	text.setFont(font);
	text.setCharacterSize(20);
}

void Coin::SetPosition(const Vector2f pos)
{
	position = pos;
}

void Coin::Update(const float time)
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

void Coin::Draw(RenderWindow & window)
{
	window.draw(spriteMap.sprite);
	window.draw(text);
}