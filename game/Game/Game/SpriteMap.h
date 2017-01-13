#pragma once
#include "Header.h"

class SpriteMap
{
public:
	SpriteMap() = default;
	~SpriteMap() = default;

	Sprite sprite;
	SpriteMap(string &nameTexture, int &column, int &line)
		: columns(column),
		lines(line)
	{
		if (!texture.loadFromFile(PATH_TO_TEXTURES + nameTexture + ".png"))
		{
			cout << "Сорян, не загрузилась: " << nameTexture << endl;
		}
		sprite.setTexture(texture);
		GetTileSize();
		sprite.setTextureRect(IntRect(0, 0, (int)tileSize.x, (int)tileSize.y));
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	}

	void SetSpriteMap(string nameTexture, int columnsInMap, int linesInMap)
	{
		if (!texture.loadFromFile(PATH_TO_TEXTURES + nameTexture + ".png"))
		{
			cout << "Сорян, не загрузилась: " << nameTexture << endl;
		}
		columns = columnsInMap;
		lines = linesInMap;
		sprite.setTexture(texture);
		GetTileSize();
		sprite.setTextureRect(IntRect(0, 0, (int)tileSize.x, (int)tileSize.y));
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	}

	void SetFrame(int frame)
	{
		int lineFrame = frame / columns;
		int columnFrame = frame % columns;
		sprite.setTextureRect(IntRect((int)tileSize.x * columnFrame, (int)tileSize.y * lineFrame, (int)tileSize.x, (int)tileSize.y));
	}
	void SetFrame(Direction direction, float frame)
	{
		sprite.setTextureRect(IntRect(tileSize.x * (int)frame, (int)direction * tileSize.y, tileSize.x, tileSize.y));
	}
	void SetFrame(int column, int line)
	{
		sprite.setTextureRect(IntRect(tileSize.x * (int)column, tileSize.y * (int)line, tileSize.x, tileSize.y));
	}

	int GetColumns()
	{
		return columns;
	}
	int GetLines()
	{
		return lines;
	}

	Vector2i GetTileSize()
	{
		if (tileSize == Vector2i(0, 0))
		{
			tileSize = Vector2i(texture.getSize().x / columns, texture.getSize().y / lines);
		}
		return tileSize;
	}

	void SetPosition(Vector2f position)
	{
		sprite.setPosition(position);
	}
	void SetPosition(float x, float y)
	{
		sprite.setPosition(Vector2f(x, y));
	}

private:
	Texture texture;
	Vector2i tileSize = { 0, 0 };

	int columns;
	int lines;
};

