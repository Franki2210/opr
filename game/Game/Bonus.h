#pragma once
#include "Header.h"

class Bonus
{
public:
	bool isDestroy = false;
	bool isDisactive = false;
	bool isUsed = false;

	Bonus() = default;
	Bonus(Texture & texture, const float value, const float timeToDestroy, const float timeOfAction);
	~Bonus() = default;

	void SetBonus(const string nameBonus, Texture & texture, const float value, const float timeToDestroy, const float timeOfAction);

	string GetName();

	void SetPosition(Vector2f pos);
	void SetPosition(const float x, const float y);
	Vector2f GetPosition();

	void SetScale(const float x, const float y);

	float GetValue();

	FloatRect GetGlobalBound();

	void UpdateOnMap(const float time);
	void UpdateOnPlayer(const float time);

	void Draw(RenderWindow & window);

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