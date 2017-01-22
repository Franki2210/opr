#pragma once
#include "Header.h"

class ChangeHpView
{
public:
	bool destroy = false;

	ChangeHpView();
	ChangeHpView(const float valueChangeHp, sf::Vector2f pos);
	~ChangeHpView();

	void SetValue(const float valueChangeHp);

	void SetFont(sf::Font font);

	void SetPosition(sf::Vector2f position);

	void Update(const float time);

	void Draw(sf::RenderWindow & window);

private:
	float timerToDisappearance = 500;
	sf::Vector2f position;
	float currAlpha = 255;
	float value = 0;
	sf::Font font;
	sf::Text text;
};