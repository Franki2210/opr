#pragma once
#include "Header.h"

class ChangeHpView
{
public:
	bool destroy = false;

	ChangeHpView();
	ChangeHpView(const float valueChangeHp, Vector2f pos);
	~ChangeHpView();

	void SetValue(const float valueChangeHp);

	void SetFont(Font font);

	void SetPosition(Vector2f position);

	void Update(const float time);

	void Draw(RenderWindow & window);

private:
	float timerToDisappearance = 500;
	Vector2f position;
	float currAlpha = 255;
	float value = 0;
	Font font;
	Text text;
};