#pragma once
#include "Header.h"

class Vignette
{
public:
	Vignette() = default;
	~Vignette() = default;

	void SetTexture(Texture & texture)
	{
		sprite.setTexture(texture);
		sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	}

	void SetActive(bool value)
	{
		isActive = value;
	}
	bool GetActive()
	{
		return isActive;
	}

	void Draw(RenderWindow & window)
	{
		sprite.setPosition(window.getView().getCenter());
		window.draw(sprite);
	}
private:
	bool isActive = false;
	Sprite sprite;
};