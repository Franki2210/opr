#include "Header.h"
#include "Meteor.h"

using namespace sf;

Meteor::Meteor() = default;
Meteor::~Meteor() = default;

Meteor::Meteor(Texture & texture, Texture & textureShadow, Texture & textureArrival, const float damageMeteor, const float speedMeteor)
{
	sprite.setTexture(texture);
	spriteShadow.setTexture(textureShadow);
	spritePointArrival.setTexture(textureArrival);
	sprite.setOrigin(sprite.getGlobalBounds().left, sprite.getGlobalBounds().height);
	spriteShadow.setOrigin(spriteShadow.getGlobalBounds().left, spriteShadow.getGlobalBounds().height / 2);
	spritePointArrival.setOrigin(spritePointArrival.getGlobalBounds().width / 2, spritePointArrival.getGlobalBounds().height / 2);
	sprite.setScale(0.5f, 0.5f);
	spriteShadow.setScale(0.5f, 0.5f);
	spritePointArrival.setScale(0.9f, 0.9f);
	spriteShadow.setColor(Color(255, 255, 255, 50));
	spritePointArrival.setColor(Color(255, 255, 255, 50));

	damage = damageMeteor;
	speed = speedMeteor;
}

void Meteor::SetMeteor(Texture & texture, Texture & textureShadow, Texture & textureArrival, const float damageMeteor, const float speedMeteor)
{
	sprite.setTexture(texture);
	spriteShadow.setTexture(textureShadow);
	spritePointArrival.setTexture(textureArrival);
	sprite.setOrigin(sprite.getGlobalBounds().left, sprite.getGlobalBounds().height);
	spriteShadow.setOrigin(spriteShadow.getGlobalBounds().left, spriteShadow.getGlobalBounds().height / 2);
	spritePointArrival.setOrigin(spritePointArrival.getGlobalBounds().width / 2, spritePointArrival.getGlobalBounds().height / 2);
	sprite.setScale(0.5f, 0.5f);
	spriteShadow.setScale(0.5f, 0.5f);
	//spritePointArrival.setScale(0.9f, 0.9f);
	spriteShadow.setColor(Color(255, 255, 255, 50));
	spritePointArrival.setColor(Color(255, 255, 255, 50));

	damage = damageMeteor;
	speed = speedMeteor;
}

void Meteor::SetArrivalPosition(const Vector2f pos)
{
	arrivalPosition = pos;
	startPosition = arrivalPosition - moveVector * 5000.0f;
	currPosition = startPosition;

	sprite.setPosition(currPosition);
	spriteShadow.setPosition(currPosition.x, arrivalPosition.y);
	spritePointArrival.setPosition(arrivalPosition);
}
void Meteor::SetArrivalPosition(const float x, const float y)
{
	arrivalPosition = Vector2f(x, y);
	startPosition = arrivalPosition - moveVector * 3000.0f;
	currPosition = startPosition;

	sprite.setPosition(currPosition);
	spriteShadow.setPosition(currPosition.x, arrivalPosition.y);
	spritePointArrival.setPosition(arrivalPosition);
}
Vector2f Meteor::GetArrivalPosition()
{
	return arrivalPosition;
}
Vector2f Meteor::GetCurrentPosition()
{
	return currPosition;
}

void Meteor::SetMoveVector(const Vector2f value)
{
	moveVector = value;
}

FloatRect Meteor::GetArrivalArea()
{
	return spritePointArrival.getGlobalBounds();
}
float Meteor::GetDamage()
{
	return damage;
}

bool Meteor::GetArrival()
{
	return isArrival;
}

void Meteor::Update(const float time)
{
	currPosition += moveVector * speed * time;
	sprite.setPosition(currPosition);
	spriteShadow.setPosition(currPosition.x, arrivalPosition.y);
	spritePointArrival.setPosition(arrivalPosition);

	if (currPosition.x <= arrivalPosition.x + 10 && currPosition.x >= arrivalPosition.x - 10 &&
		currPosition.y <= arrivalPosition.y + 10 && currPosition.y >= arrivalPosition.y - 10)
	{
		isArrival = true;
	}
}

void Meteor::Draw(RenderWindow & window)
{
	window.draw(spritePointArrival);
	window.draw(spriteShadow);
	window.draw(sprite);
}