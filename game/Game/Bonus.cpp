#include "Bonus.h"

using namespace sf;

Bonus::Bonus(Texture & texture, const float valueBonus, const float timeToDestroy, const float timeOfAction)
{
	sprite.setTexture(texture);
	value = valueBonus;
	this->timeToDestroy = timeToDestroy;
	timerToDestroy = timeToDestroy;
	this->timeOfAction = timeOfAction;
}

void Bonus::SetBonus(const std::string nameBonus, sf::Texture & texture, const float valueBonus, const float timeToDestroy, const float timeOfAction = 0)
{
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f);
	name = nameBonus;
	value = valueBonus;
	this->timeToDestroy = timeToDestroy;
	timerToDestroy = timeToDestroy;
	this->timeOfAction = timeOfAction;
}

std::string Bonus::GetName()
{
	return name;
}

void Bonus::SetPosition(sf::Vector2f pos)
{
	position = pos;
	sprite.setPosition(position);
}
void Bonus::SetPosition(const float x, const float y)
{
	position = Vector2f(x, y);
	sprite.setPosition(position);
}
sf::Vector2f Bonus::GetPosition()
{
	return position;
}

void Bonus::SetScale(const float x, const float y)
{
	sprite.setScale(x, y);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f);
}

float Bonus::GetValue()
{
	return value;
}

FloatRect Bonus::GetGlobalBound()
{
	return sprite.getGlobalBounds();
}

void Bonus::UpdateOnMap(const float time)
{
	if (timerToDestroy > 0) timerToDestroy -= time;
	else isDestroy = true;
}
void Bonus::UpdateOnPlayer(const float time)
{
	if (timerOfAction > 0) timerOfAction -= time;
	else isDisactive = true;
}

void Bonus::Draw(RenderWindow & window)
{
	window.draw(sprite);
}