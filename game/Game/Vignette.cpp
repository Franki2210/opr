#include "Header.h"
#include "Vignette.h"

Vignette::Vignette() = default;
Vignette::~Vignette() = default;

void Vignette::SetTexture(Texture & texture)
{
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

void Vignette::SetActive(bool value)
{
	isActive = value;
}
bool Vignette::GetActive()
{
	return isActive;
}

void Vignette::Draw(RenderWindow & window)
{
	sprite.setPosition(window.getView().getCenter());
	window.draw(sprite);
}