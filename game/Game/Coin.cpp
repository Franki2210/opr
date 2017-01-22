#include "Header.h"
#include "SpriteMap.h"
#include "Coin.h"

Coin::Coin() = default;
Coin::Coin(sf::Texture & texture, const int numColumns, const int numLines)
{
	spriteMap.SetSpriteMap(texture, numColumns, numLines);
	spriteMap.sprite.setScale(0.3f, 0.3f);
}
Coin::~Coin() = default;

void Coin::SetSpriteMap(sf::Texture & texture, const int numColumns, const int numLines)
{
	spriteMap.SetSpriteMap(texture, numColumns, numLines);
	spriteMap.sprite.setScale(0.3f, 0.3f);
}

void Coin::SetValue(const int valueCoin)
{
	value = valueCoin;
	std::ostringstream valueString;
	valueString << value;
	text.setString("+" + valueString.str());
}

void Coin::SetFont(const sf::Font fontCoin)
{
	font = fontCoin;
	text.setFont(font);
	text.setCharacterSize(20);
}

void Coin::SetPosition(const sf::Vector2f pos)
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
		position = sf::Vector2f(position.x, position.y - 0.04f * time);
		currAlpha -= 0.15f * time;
		if (currAlpha < 0) currAlpha = 0;
		spriteMap.sprite.setColor(sf::Color(255, 255, 255, sf::Uint8(currAlpha)));
		text.setColor(sf::Color(255, 255, 255, sf::Uint8(currAlpha)));
		spriteMap.sprite.setPosition(position);
		text.setPosition(position);
	}
	else
	{
		destroy = true;
	}
}

void Coin::Draw(sf::RenderWindow & window)
{
	window.draw(spriteMap.sprite);
	window.draw(text);
}