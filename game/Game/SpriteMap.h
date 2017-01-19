#pragma once
#include "Header.h"

class SpriteMap
{
public:
	SpriteMap();
	~SpriteMap();

	Sprite sprite;
	SpriteMap(Texture & texture, const int column, const int line);

	void SetSpriteMap(Texture & texture, const int columnsInMap, const int linesInMap);

	void SetFrame(const int frame);
	void SetFrame(const Direction direction, const float frame);
	void SetFrame(const int column, const int line);

	void SetFlipX(const bool flip);
	bool GetFlipX();

	int GetColumns();
	int GetLines();

	Vector2i GetTileSize(Texture & texture);
	Vector2i GetTileSize();

	void SetPosition(const Vector2f position);
	void SetPosition(const float x, const float y);

private:
	Vector2i tileSize = { 0, 0 };

	int columns;
	int lines;
	bool flipX = false;
	bool isEndSpriteMap = false;
};