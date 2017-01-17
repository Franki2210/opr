#pragma once
#include "Header.h"

class Icon
{
public:
	Sprite sprite;

	Icon() = default;
	Icon(string nameTexture)
	{
		if (!texture.loadFromFile(PATH_TO_TEXTURES + nameTexture + ".png"))
		{
			cout << "Сорян, не загрузилась: " << nameTexture << endl;
		}
		sprite.setTexture(texture);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sprite.setScale(Vector2f(0.2f, 0.2f));
	}
	~Icon() = default;

	void SetSprite(string nameTexture)
	{
		if (!texture.loadFromFile(PATH_TO_TEXTURES + nameTexture + ".png"))
		{
			cout << "Сорян, не загрузилась: " << nameTexture << endl;
		}
		sprite.setTexture(texture);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sprite.setScale(Vector2f(0.2f, 0.2f));
		sprite.setColor(Color(100, 100, 100));
	}

	void SetPosition(Vector2f pos)
	{
		sprite.setPosition(pos);
	}
	void SetPosition(float x, float y)
	{
		sprite.setPosition(Vector2f(x, y));
	}

	void SetActive(bool isActive_)
	{
		isActive = isActive_;
		if (!isActive)
		{
			sprite.setColor(Color(100, 100, 100));
		}
		else
		{
			sprite.setColor(Color::White);
		}
	}
	bool GetActive()
	{
		return isActive;
	}

	void Draw(RenderWindow & window)
	{
		window.draw(sprite);
	}

private:
	Texture texture;
	bool isActive = false;
};