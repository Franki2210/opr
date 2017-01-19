#include "SpriteMap.h"

SpriteMap::SpriteMap() = default;
SpriteMap::~SpriteMap() = default;

SpriteMap::SpriteMap(Texture & texture, const int column, const int line)
	: columns(column),
	lines(line)
{
	sprite.setTexture(texture);
	GetTileSize();
	sprite.setTextureRect(IntRect(0, 0, (int)tileSize.x, (int)tileSize.y));
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void SpriteMap::SetSpriteMap(Texture & texture, const int columnsInMap, const int linesInMap)
{
	sprite.setTexture(texture);
	columns = columnsInMap;
	lines = linesInMap;
	GetTileSize(texture);
	sprite.setTextureRect(IntRect(0, 0, (int)tileSize.x, (int)tileSize.y));
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void SpriteMap::SetFrame(const int frame)
{
	int lineFrame = frame / columns;
	int columnFrame = frame % columns;
	sprite.setTextureRect(IntRect((int)tileSize.x * columnFrame, (int)tileSize.y * lineFrame, (int)tileSize.x, (int)tileSize.y));
}
void SpriteMap::SetFrame(const Direction direction, const float frame)
{
	sprite.setTextureRect(IntRect(tileSize.x * (int)frame, (int)direction * tileSize.y, tileSize.x, tileSize.y));
}
void SpriteMap::SetFrame(const int column, const int line)
{
	if (flipX)
	{
		sprite.setTextureRect(IntRect(tileSize.x * (int)column + tileSize.x, tileSize.y * (int)line, -tileSize.x, tileSize.y));
	}
	else
	{
		sprite.setTextureRect(IntRect(tileSize.x * (int)column, tileSize.y * (int)line, tileSize.x, tileSize.y));
	}
}

void SpriteMap::SetFlipX(const bool flip)
{
	flipX = flip;
}
bool SpriteMap::GetFlipX()
{
	return flipX;
}

int SpriteMap::GetColumns()
{
	return columns;
}
int SpriteMap::GetLines()
{
	return lines;
}

Vector2i SpriteMap::GetTileSize(Texture & texture)
{
	if (tileSize == Vector2i(0, 0))
	{
		tileSize = Vector2i(texture.getSize().x / columns, texture.getSize().y / lines);
	}
	return tileSize;
}
Vector2i SpriteMap::GetTileSize()
{
	return tileSize;
}

void SpriteMap::SetPosition(const Vector2f position)
{
	sprite.setPosition(position);
}
void SpriteMap::SetPosition(const float x, const float y)
{
	sprite.setPosition(Vector2f(x, y));
}