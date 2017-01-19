#include <iomanip>
#include "ChangeHpView.h"

ChangeHpView::ChangeHpView() = default;
ChangeHpView::ChangeHpView(const float valueChangeHp, Vector2f pos)
	: value(valueChangeHp), position(pos)
{
	ostringstream valueString;
	valueString << valueChangeHp;
	text.setString("-" + valueString.str());
	position = Vector2f(pos.x + rand() % 10, pos.y);
}
ChangeHpView::~ChangeHpView() = default;

void ChangeHpView::SetValue(const float valueChangeHp)
{
	value = valueChangeHp;
	ostringstream valueString;
	valueString << value;
	text.setString("-" + valueString.str());
}

void ChangeHpView::SetFont(Font fontChangeHpView)
{
	font = fontChangeHpView;
	text.setFont(font);
	text.setCharacterSize(12);
}

void ChangeHpView::SetPosition(Vector2f pos)
{
	position = pos;
	position = Vector2f(position.x + rand() % 10, position.y);
}

void ChangeHpView::Update(const float time)
{
	if (timerToDisappearance > 0)
	{
		timerToDisappearance -= time;
		position = Vector2f(position.x, position.y - 0.05f * time);
		currAlpha -= 0.2f * time;
		if (currAlpha < 0) currAlpha = 0;
		text.setColor(Color(255, 50, 50, Uint8(currAlpha)));
		text.setPosition(position);
	}
	else
	{
		destroy = true;
	}
}

void ChangeHpView::Draw(RenderWindow & window)
{
	window.draw(text);
}