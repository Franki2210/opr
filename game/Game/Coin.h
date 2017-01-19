#pragma once

class Coin
{
public:
	SpriteMap spriteMap;
	bool destroy = false;

	Coin();
	Coin(Texture & texture, const int numColumns, const int numLines);
	~Coin();

	void SetSpriteMap(Texture & texture, const int numColumns, const int numLines);

	void SetValue(const int value_);

	void SetFont(const Font font_);

	void SetPosition(const Vector2f pos);

	void Update(const float time);

	void Draw(RenderWindow & window);

private:
	float timerToDestroy = 2000;
	float currFrame = 0;
	Vector2f position;
	float currAlpha = 255;
	int value = 0;
	Font font;
	Text text;
};