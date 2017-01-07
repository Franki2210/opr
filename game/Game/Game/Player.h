#pragma once

using namespace sf;

enum Direction {Left = 0, Right, Up, Down};

class Player
{
public:
	Player(String texFileIdle, String texFileRun)
	{
		textureIdle.loadFromFile("recources/textures/" + texFileIdle + ".png");
		textureRun.loadFromFile("resources/textures/" + texFileRun + ".png");

		tileSizeIdle = GetTileSize(textureIdle, 22, 8);
		spriteIdle.setTexture(textureIdle);
		spriteIdle.setTextureRect(IntRect(0, 0, tileSizeIdle.x, tileSizeIdle.y));

		tileSizeRun = GetTileSize(textureRun, 22, 8);
		spriteRun.setTexture(textureRun);
		spriteRun.setTextureRect(IntRect(0, 0, tileSizeRun.x, tileSizeRun.y));
	}

	Vector2i GetTileSize(Texture texture, int numColumns, int numLines)
	{
		return Vector2i(texture.getSize().x / numColumns, texture.getSize().y / numLines);
	}

	void SetPosition(int X, int Y)
	{
		x = X;
		y = Y;
	}

	~Player() = default;

	Vector2i GetPosition()
	{
		return Vector2i(x, y);
	}

	Vector2f GetSize()
	{
		return Vector2f(w, h);
	}

	void SetMove(bool IsMove)
	{
		isMove = IsMove;
	}

	void SetDirection(Direction dir)
	{
		direction = dir;
	}

	Sprite GetSprite()
	{
		return currSprite;
	}

	void Update(float time)
	{
		if (isMove)
		{
			currSprite = spriteRun;
			switch (direction)
			{
			case Direction::Left:
				dx = -speed;
				dy = 0;
				break;
			case Direction::Right:
				dx = speed;
				dy = 0;
				break;
			case Direction::Up:
				dx = 0;
				dy = -speed;
				break;
			case Direction::Down:
				dx = 0;
				dy = speed;
				break;
			}
			x += dx * time;
			y += dy * time;
			spriteRun.setPosition(x, y);
		}
		else
		{
			currSprite = spriteIdle;
			switch (direction)
			{
			case Direction::Left:
				dx = -speed;
				dy = 0;
				break;
			case Direction::Right:
				dx = speed;
				dy = 0;
				break;
			case Direction::Up:
				dx = 0;
				dy = -speed;
				break;
			case Direction::Down:
				dx = 0;
				dy = speed;
				break;
			}
			spriteIdle.setPosition(x, y);
		}
	}

private:
	Texture textureIdle;
	Texture textureRun;
	Sprite spriteIdle;
	Sprite spriteRun;
	Sprite currSprite;

	int x;
	int y;
	float w;
	float h;

	Vector2i tileSizeRun;
	Vector2i tileSizeIdle;

	float speed;
	Direction direction;
	bool isMove = false;

	float currFrame;

	float dx; float dy;
};

