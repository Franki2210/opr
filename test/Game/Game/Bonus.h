#pragma once
#include "Header.h"

class Bonus
{
public:
	bool isDestroy = false;
	bool isDisactive = false;
	bool isUsed = false;

	Bonus() = default;
	Bonus(Texture & texture, float value_, float timeToDestroy_, float timeOfAction_)
	{
		sprite.setTexture(texture);
		value = value_;
		timeToDestroy = timeToDestroy_;
		timerToDestroy = timeToDestroy;
		timeOfAction = timeOfAction_;
	}
	~Bonus() = default;

	void SetBonus(string name_, Texture & texture, float value_, float timeToDestroy_, float timeOfAction_ = 0)
	{
		name = name_;
		sprite.setTexture(texture);
		sprite.setOrigin(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f);
		value = value_;
		timeToDestroy = timeToDestroy_;
		timerToDestroy = timeToDestroy;
		timeOfAction = timeOfAction_;
	}

	string GetName()
	{
		return name;
	}

	void SetPosition(Vector2f pos)
	{
		position = pos;
		sprite.setPosition(position);
	}
	void SetPosition(float x, float y)
	{
		position = Vector2f(x, y);
		sprite.setPosition(position);
	}
	Vector2f GetPosition()
	{
		return position;
	}

	void SetScale(float x, float y)
	{
		sprite.setScale(x, y);
		sprite.setOrigin(sprite.getGlobalBounds().width / 2.0f, sprite.getGlobalBounds().height / 2.0f);
	}

	float GetValue()
	{
		return value;
	}

	FloatRect GetGlobalBound()
	{
		return sprite.getGlobalBounds();
	}

	void UpdateOnMap(float time)
	{
		if (timerToDestroy > 0) timerToDestroy -= time;
		else isDestroy = true;
	}
	void UpdateOnPlayer(float time)
	{
		if (timerOfAction > 0) timerOfAction -= time;
		else isDisactive = true;
	}

	void Draw(RenderWindow & window)
	{
		window.draw(sprite);
	}

private:
	Sprite sprite;
	Vector2f position;
	float timeToDestroy = 8000;
	float timerToDestroy = timeToDestroy;
	float timeOfAction = 5000;
	float timerOfAction = timeOfAction;
	float value;
	string name;
};