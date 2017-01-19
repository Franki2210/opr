#include "Header.h"
#include "Tower.h"

Tower::Tower()
{
	actionArea.setRadius(400);
	Color actionAreaColor(100, 200, 100, 20);
	Color actionAreaBorderColor(100, 200, 100, 100);
	actionArea.setFillColor(actionAreaColor);
	actionArea.setOutlineColor(actionAreaBorderColor);
	actionArea.setOutlineThickness(5);
	actionArea.setOrigin(actionArea.getRadius(), actionArea.getRadius());
	actionArea.setPointCount(60);

	boundsArea.setOrigin(boundsArea.getRadius(), boundsArea.getRadius());
	boundsArea.setRadius(50);
	Color boundsAreaColor(200, 50, 50, 100);
	boundsArea.setFillColor(boundsAreaColor);
}
Tower::~Tower() = default;
Tower::Tower(Texture & texture, int column, int line)
{
	spriteMap.SetSpriteMap(texture, column, line);
	actionArea.setRadius(400);
	Color actionAreaColor(100, 200, 100, 20);
	Color actionAreaBorderColor(100, 200, 100, 100);
	actionArea.setFillColor(actionAreaColor);
	actionArea.setOutlineColor(actionAreaBorderColor);
	actionArea.setOutlineThickness(5);
	actionArea.setOrigin(actionArea.getRadius(), actionArea.getRadius());
	actionArea.setPointCount(60);

	boundsArea.setOrigin(boundsArea.getRadius(), boundsArea.getRadius());
	boundsArea.setRadius(50);
	Color boundsAreaColor(200, 50, 50, 100);
	boundsArea.setFillColor(boundsAreaColor);
}

void Tower::SetSpriteMap(Texture & texture, int column, int line)
{
	spriteMap.SetSpriteMap(texture, column, line);
}

void Tower::SetActionRadius(float radius)
{
	actionArea.setRadius(radius);
	actionArea.setOrigin(actionArea.getRadius(), actionArea.getRadius());
}

int Tower::GetNumFrameFromDirection(Vector2f posEnemy)
{
	float dX = posEnemy.x - position.x;
	float dY = posEnemy.y - position.y;
	float angle = (atan2(dY, dX)) * 180 / 3.14159265f + 90;
	if (angle < 0) angle += 360;
	int frame = (int)(angle / (360. / (spriteMap.GetColumns() * spriteMap.GetLines())));
	return frame;
}

void Tower::SetBullet(Bullet usedBullet)
{
	bullet = usedBullet;
}
Bullet Tower::GetBullet()
{
	return bullet;
}

void Tower::SetReloadTime(float value)
{
	reloadTime = value;
}

void Tower::SetPrice(int value)
{
	price = value;
}
int Tower::GetPrice()
{
	return price;
}

Vector2f Tower::GetEnemyPos()
{
	return enemyPos;
}

void Tower::Update(const float time, Vector2f posEnemy)
{
	if (reloadTimer > 0 && !canShot)
	{
		reloadTimer -= time;
	}

	enemyPos = posEnemy;

	if (actionArea.getGlobalBounds().contains(posEnemy))
	{
		currFrame = (float)GetNumFrameFromDirection(posEnemy);
		if (reloadTimer <= 0)
		{
			canShot = true;
			reloadTimer = reloadTime;
		}
	}
	spriteMap.SetFrame((int)currFrame);
}
void Tower::Update()
{
	spriteMap.sprite.setPosition(position);
	actionArea.setPosition(position);
	boundsArea.setPosition(position.x - boundsArea.getRadius(), position.y - boundsArea.getRadius());
	bullet.SetStartPosition(position);
}
void Tower::Draw(RenderWindow & window)
{
	window.draw(spriteMap.sprite);
	DrawHp(window);
}
