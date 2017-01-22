#include <iomanip>
#include "ChangeHpView.h"

ChangeHpView::ChangeHpView() = default;
ChangeHpView::ChangeHpView(const float valueChangeHp, sf::Vector2f pos)
	: value(valueChangeHp), position(pos)
{
	std::ostringstream valueString;
	valueString << valueChangeHp;
	text.setString("-" + valueString.str());
	position = sf::Vector2f(pos.x + rand() % 10, pos.y);
}
ChangeHpView::~ChangeHpView() = default;

void ChangeHpView::SetValue(const float valueChangeHp)
{
	value = valueChangeHp;
	std::ostringstream valueString;
	valueString << value;
	text.setString("-" + valueString.str());
}

void ChangeHpView::SetFont(sf::Font fontChangeHpView)
{
	font = fontChangeHpView;
	text.setFont(font);
	text.setCharacterSize(12);
}

void ChangeHpView::SetPosition(sf::Vector2f pos)
{
	position = pos;
	position = sf::Vector2f(position.x + rand() % 10, position.y);
}

void ChangeHpView::Update(const float time)
{
	if (timerToDisappearance > 0)
	{
		timerToDisappearance -= time;
		position = sf::Vector2f(position.x, position.y - 0.05f * time);
		currAlpha -= 0.2f * time;
		if (currAlpha < 0) currAlpha = 0;
		text.setColor(sf::Color(255, 50, 50, sf::Uint8(currAlpha)));
		text.setPosition(position);
	}
	else
	{
		destroy = true;
	}
}

void ChangeHpView::Draw(sf::RenderWindow & window)
{
	window.draw(text);
}