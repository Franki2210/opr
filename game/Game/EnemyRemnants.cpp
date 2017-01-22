#include "Header.h"
#include "SpriteMap.h"
#include "EnemyRemnants.h"

EnemyRemnants::EnemyRemnants() = default;
EnemyRemnants::~EnemyRemnants() = default;

void EnemyRemnants::SetEnemyExplosion(sf::Texture & texture, int columnsInMap, int linesInMap)
{
	spriteMap.SetSpriteMap(texture, columnsInMap, linesInMap);
}

void EnemyRemnants::SetSpeedAnimation(float value)
{
	speedAnimation = value;
}

void EnemyRemnants::SetRandomRotate()
{
	spriteMap.sprite.setRotation(rand() % 360);
}

void EnemyRemnants::SetTimeToDestroy(float value)
{
	timeToDestroy = value;
	timerToDestroy = timeToDestroy;
}

void EnemyRemnants::SetPosition(sf::Vector2f pos)
{
	position = pos;
	spriteMap.sprite.setPosition(position);
}
void EnemyRemnants::SetPosition(float x, float y)
{
	position = sf::Vector2f(x, y);
	spriteMap.sprite.setPosition(position);
}
sf::Vector2f EnemyRemnants::GetPosition()
{
	return position;
}

bool EnemyRemnants::GetIsDestroy()
{
	return isDestroy;
}

void EnemyRemnants::Update(float time)
{
	if (timerToDestroy > 0)
	{
		timerToDestroy -= time;
		if (currFrame < spriteMap.GetColumns() * spriteMap.GetLines())
		{
			spriteMap.SetFrame((int)currFrame);
			currFrame += speedAnimation * time;
		}
		if (timerToDestroy < 2000)
		{
			currAlpha -= 0.13f * time;
			if (currAlpha <= 0) currAlpha = 0;
			spriteMap.sprite.setColor(sf::Color(255, 255, 255, sf::Uint8(currAlpha)));
		}
	}
	else isDestroy = true;
}

void EnemyRemnants::Draw(sf::RenderWindow & window)
{
	window.draw(spriteMap.sprite);
}