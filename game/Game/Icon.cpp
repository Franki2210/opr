#include "Header.h"
#include "Icon.h"

Icon::Icon() = default;
Icon::Icon(string nameTexture)
{
	if (!texture.loadFromFile(PATH_TO_TEXTURES + nameTexture + ".png"))
	{
		cout << "Сорян, не загрузилась: " << nameTexture << endl;
	}
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setScale(Vector2f(0.2f, 0.2f));
}
Icon::~Icon() = default;

void Icon::SetSprite(string nameTexture)
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

void Icon::SetPosition(Vector2f pos)
{
	sprite.setPosition(pos);
}
void Icon::SetPosition(float x, float y)
{
	sprite.setPosition(Vector2f(x, y));
}

void Icon::SetActive(bool isActive_)
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
bool Icon::GetActive()
{
	return isActive;
}

void Icon::Draw(RenderWindow & window)
{
	window.draw(sprite);
}