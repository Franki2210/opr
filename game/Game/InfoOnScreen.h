#pragma once
#include "Header.h"
#include "Player.h"

/*
TODO:
  Доделать класс информационного наложения
*/
struct TextObject
{
	Text text;
	Text value;
	Vector2f position;
};

class InfoOnScreen
{
public:
	InfoOnScreen() = default;
	~InfoOnScreen() = default;

	void SetFont(Font font)
	{
		hp.text.setFont(font);
		hp.value.setFont(font);
		speed.text.setFont(font);
		speed.value.setFont(font);
		damage.text.setFont(font);
		damage.value.setFont(font);
		speedFire.text.setFont(font);
		speedFire.value.setFont(font);
	}

	void Update(Vector2f posView, float time)
	{
		hp.text.setPosition(posView + hp.position);
		hp.value.setPosition(posView + hp.position);
		speed.text.setPosition(posView + speed.position);
		speed.value.setPosition(posView + speed.position);
	}

	void Draw(RenderWindow & window)
	{

	}

private:
	TextObject hp;
	TextObject speed;
	TextObject damage;
	TextObject speedFire;
	Player *player = nullptr;
};