#pragma once

class Coin
{
public:
	SpriteMap spriteMap;
	bool destroy = false;

	Coin();
	Coin(sf::Texture & texture, const int numColumns, const int numLines);
	~Coin();

	void SetSpriteMap(sf::Texture & texture, const int numColumns, const int numLines);

	void SetValue(const int valueCoin);

	void SetFont(const sf::Font fontCoin);

	void SetPosition(const sf::Vector2f pos);

	void Update(const float time);

	void Draw(sf::RenderWindow & window);

private:
	float timerToDestroy = 2000;
	float currFrame = 0;
	sf::Vector2f position;
	float currAlpha = 255;
	int value = 0;
	sf::Font font;
	sf::Text text;
};