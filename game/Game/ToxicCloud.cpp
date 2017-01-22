#include "Header.h"
#include "SpriteMap.h"
#include "ToxicCloud.h"

using namespace sf;

ToxicCloud::ToxicCloud() = default;
ToxicCloud::~ToxicCloud() = default;

void ToxicCloud::SetToxicCloud(Texture & texture, int columnsInMap, int linesInMap)
{
	spriteMap.SetSpriteMap(texture, columnsInMap, linesInMap);
}

void ToxicCloud::SetPosition(Vector2f pos)
{
	position = pos;
	spriteMap.sprite.setPosition(position);
}
void ToxicCloud::SetPosition(float x, float y)
{
	position = Vector2f(x, y);
	spriteMap.sprite.setPosition(position);
}
Vector2f ToxicCloud::GetPosition()
{
	return position;
}

void ToxicCloud::SetSpeedAnimation(float value)
{
	speedAnimation = value;
}

FloatRect ToxicCloud::GetGlobalBounds()
{
	return spriteMap.sprite.getGlobalBounds();
}

void ToxicCloud::SetTimeToDestroy(float value)
{
	timeToDestroy = value;
	timerToDestroy = timeToDestroy;
}

void ToxicCloud::SetSpeedDamage(float value)
{
	speedDamage = value;
}
float ToxicCloud::GetSpeedDamage()
{
	return speedDamage;
}

void ToxicCloud::SetDamage(float value)
{
	damage = value;
}
float ToxicCloud::GetDamage()
{
	return damage;
}

bool ToxicCloud::GetIsDestroy()
{
	return isDestroy;
}

void ToxicCloud::Update(const float time)
{
	if (timerToDestroy > 0)
	{
		timerToDestroy -= time;
		currFrame += speedAnimation * time;
		if (currFrame >= spriteMap.GetColumns() * spriteMap.GetLines())
		{
			currFrame = 0;
		}
		spriteMap.SetFrame((int)currFrame);
		if (timerToDestroy < timeToDestroy && timerToDestroy > timeToDestroy - 1000.0f)
		{
			currAlpha += 0.26f * time;
			if (currAlpha >= 255) currAlpha = 255;
			spriteMap.sprite.setColor(Color(255, 255, 255, (Uint8)currAlpha));
		}
		if (timerToDestroy < 2000)
		{
			currAlpha -= 0.13f * time;
			if (currAlpha <= 0) currAlpha = 0;
			spriteMap.sprite.setColor(Color(255, 255, 255, (Uint8)currAlpha));
		}
	}
	else
	{
		isDestroy = true;
	}
}

void ToxicCloud::Draw(RenderWindow & window)
{
	window.draw(spriteMap.sprite);
}