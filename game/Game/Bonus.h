#pragma once
#include "Header.h"

class Bonus
{
public:
	bool isDestroy = false;
	bool isDisactive = false;
	bool isUsed = false;

	Bonus() = default;
	Bonus(sf::Texture & texture, const float value, const float timeToDestroy, const float timeOfAction);
	~Bonus() = default;

	void SetBonus(const std::string nameBonus, sf::Texture & texture, const float value, const float timeToDestroy, const float timeOfAction);

	std::string GetName();

	void SetPosition(sf::Vector2f pos);
	void SetPosition(const float x, const float y);
	sf::Vector2f GetPosition();

	void SetScale(const float x, const float y);

	float GetValue();

	sf::FloatRect GetGlobalBound();

	void UpdateOnMap(const float time);
	void UpdateOnPlayer(const float time);

	void Draw(sf::RenderWindow & window);

private:
	sf::Sprite sprite;
	sf::Vector2f position;
	float timeToDestroy = 8000;
	float timerToDestroy = timeToDestroy;
	float timeOfAction = 5000;
	float timerOfAction = timeOfAction;
	float value;
	std::string name;
};