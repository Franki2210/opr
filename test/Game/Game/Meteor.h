#pragma once
#include "Header.h"

class Meteor
{
public:
	Meteor() = default;
	~Meteor() = default;

	void SetMeteor(Texture & texture, Texture & textureShadow, Texture & textureArrival, const float damage_, const float speed_)
	{
		sprite.setTexture(texture);
		spriteShadow.setTexture(textureShadow);
		spritePointArrival.setTexture(textureArrival);
		sprite.setOrigin(sprite.getGlobalBounds().left, sprite.getGlobalBounds().height);
		spriteShadow.setOrigin(spriteShadow.getGlobalBounds().left, spriteShadow.getGlobalBounds().height / 2);
		spritePointArrival.setOrigin(spritePointArrival.getGlobalBounds().width / 2, spritePointArrival.getGlobalBounds().height / 2);
		sprite.setScale(0.5f, 0.5f);
		spriteShadow.setScale(0.5f, 0.5f);
		spritePointArrival.setScale(0.5f, 0.5f);
		spriteShadow.setColor(Color(255,255,255,50));
		spritePointArrival.setColor(Color(255, 255, 255, 50));

		damage = damage_;
		speed = speed_;
	}
	void SetSounds(Sound *sound_)
	{
		sound = sound_;
	}
	Sound *GetSound()
	{
		return sound;
	}

	void SetArrivalPosition(const Vector2f pos)
	{
		arrivalPosition = pos;
		startPosition = arrivalPosition - moveVector * 1000.0f;
		currPosition = startPosition;

		sprite.setPosition(currPosition);
		spriteShadow.setPosition(currPosition.x, arrivalPosition.y);
		spritePointArrival.setPosition(arrivalPosition);
	}
	void SetArrivalPosition(const float x, const float y)
	{
		arrivalPosition = Vector2f(x, y);
		startPosition = arrivalPosition - moveVector * 1000.0f;
		currPosition = startPosition;

		sprite.setPosition(currPosition);
		spriteShadow.setPosition(currPosition.x, arrivalPosition.y);
		spritePointArrival.setPosition(arrivalPosition);
	}
	Vector2f GetArrivalPosition()
	{
		return arrivalPosition;
	}
	Vector2f GetCurrentPosition()
	{
		return currPosition;
	}

	void SetMoveVector(const Vector2f value)
	{
		moveVector = value;
	}

	FloatRect GetArrivalArea()
	{
		return spritePointArrival.getGlobalBounds();
	}
	float GetDamage()
	{
		return damage;
	}

	bool GetArrival()
	{
		return isArrival;
	}

	void Update(const float time)
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

	void Draw(RenderWindow & window)
	{
		window.draw(spritePointArrival);
		window.draw(spriteShadow);
		window.draw(sprite);
	}

private:
	Sprite sprite;
	Sprite spriteShadow;
	Sprite spritePointArrival;

	Vector2f arrivalPosition;
	Vector2f currPosition;
	Vector2f moveVector = Vector2f(-0.81f, 0.57f);
	Vector2f startPosition;

	bool isArrival;

	float speed = 0.2f;
	float damage;
	Sound *sound;
};