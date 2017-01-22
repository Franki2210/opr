#pragma once
#include "Header.h"

class SpriteMap
{
public:
	SpriteMap();
	~SpriteMap();

	sf::Sprite sprite;
	SpriteMap(sf::Texture & texture, const int column, const int line);

	void SetSpriteMap(sf::Texture & texture, const int columnsInMap, const int linesInMap);

	void SetFrame(const int frame);
	void SetFrame(const Direction direction, const float frame);
	void SetFrame(const int column, const int line);

	void SetFlipX(const bool flip);
	bool GetFlipX();

	int GetColumns();
	int GetLines();

	sf::Vector2i GetTileSize(sf::Texture & texture);
	sf::Vector2i GetTileSize();

	void SetPosition(const sf::Vector2f position);
	void SetPosition(const float x, const float y);

private:
	sf::Vector2i tileSize = { 0, 0 };

	int columns;
	int lines;
	bool flipX = false;
	bool isEndSpriteMap = false;
};