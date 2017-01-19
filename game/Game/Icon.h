#pragma once

class Icon
{
public:
	Sprite sprite;

	Icon();
	Icon(string nameTexture);
	~Icon();

	void SetSprite(string nameTexture);

	void SetPosition(Vector2f pos);
	void SetPosition(float x, float y);

	void SetActive(bool isActive_);
	bool GetActive();

	void Draw(RenderWindow & window);

private:
	Texture texture;
	bool isActive = false;
};