#include "Header.h"
//#include "Player.h"
#include <fstream>
#include <iostream>
#include <windows.h>
#include <list>

const string PATH_TO_TEXTURES =  "recources/textures/";

enum Direction { Up = 0, UpRight, Right, DownRight, Down, DownLeft, Left, UpLeft};

class SpriteMap
{
public:
	SpriteMap() = default;
	SpriteMap(string nameTexture, int column, int line)
		: columns(column),
		lines(line)
	{
		if (!texture.loadFromFile(PATH_TO_TEXTURES + nameTexture + ".png"))
		{
			cout << "—ор€н, не загрузилась: " << nameTexture << endl;
		}
	}
	
	int columns;
	int lines;
	Sprite sprite;

	void SetSpriteMap(const String &nameTexture, int columnsInMap, int linesInMap)
	{
		texture.loadFromFile(PATH_TO_TEXTURES + nameTexture + ".png");
		columns = columnsInMap;
		lines = linesInMap;
		tileSize = GetTileSize();

		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, (int)tileSize.x, (int)tileSize.y));
	}

	~SpriteMap() = default;

	void SetFrame(int frame)
	{
		int lineFrame = frame / columns;
		int columnFrame = frame % columns;
		sprite.setTextureRect(IntRect(tileSize.x * columnFrame, tileSize.y * lineFrame, tileSize.x, tileSize.y));
	}

	void NextFrame(Direction direction, float frame)
	{
		sprite.setTextureRect(IntRect(tileSize.x * (int)frame, (int)direction * tileSize.y, tileSize.x, tileSize.y));
	}

	Vector2f GetTileSize()
	{
		if (tileSize == Vector2f(0, 0))
		{
			tileSize = Vector2f(texture.getSize().x / columns, texture.getSize().y / lines);
		}
		return tileSize;
	}

private:
	Texture texture;
	Vector2f tileSize = { 0, 0 };
};

class Animation
{
public:
	Animation() = default;

	SpriteMap currMap;

	void SetDefaultIdleTextureMap(const String &nameTexture, int columns, int lines)
	{
		spriteMapIdle.SetSpriteMap(nameTexture, columns, lines);
	}
	void SetIdleGunTextureMap(const String &nameTexture, int columns, int lines)
	{
		spriteMapIdleGun.SetSpriteMap(nameTexture, columns, lines);
	}
	void SetDefaultRunTextureMap(const String &nameTexture, int columns, int lines)
	{
		spriteMapRun.SetSpriteMap(nameTexture, columns, lines);
	}
	void SetRunGunTextureMap(const String &nameTexture, int columns, int lines)
	{
		spriteMapRunGun.SetSpriteMap(nameTexture, columns, lines);
	}

	void Update(float const &time, bool isMove, Direction direction)
	{
		if (isMove) 
		{ 
			currMap = spriteMapRun;
			currFrame += 0.04f * time;
		}
		else
		{
			currMap = spriteMapIdle;
			currFrame += 0.01f * time;
		}

		if (currFrame > currMap.columns) currFrame = 1;
		currMap.NextFrame(direction, currFrame);
	}

private:
	SpriteMap spriteMapIdle;
	SpriteMap spriteMapRun;
	SpriteMap spriteMapIdleGun;
	SpriteMap spriteMapRunGun;
	float currFrame = 0;
};

class Player
{
	
public:
	Player(const String &texFileIdle, int colIdle, int lineIdle,
		   const String &texFileIdleGun, int colIdleGun, int lineIdleGun, 
		   const String &texFileRun, int colRun, int lineRun, 
		   const String &texFileRunGun, int colRunGun, int lineRunGun)		
	{
		playerAnimation.SetDefaultIdleTextureMap(texFileIdle, colIdle, lineIdle);
		playerAnimation.SetIdleGunTextureMap(texFileIdleGun, colIdleGun, lineIdleGun);
		playerAnimation.SetDefaultRunTextureMap(texFileRun, colRun, lineRun);
		playerAnimation.SetRunGunTextureMap(texFileRunGun, colRunGun, lineRunGun);
	}

	~Player() = default;

	void SetPosition(float X, float Y)
	{
		x = X;
		y = Y;
	}

	Vector2f GetPosition()
	{
		return Vector2f(x, y);
	}

	Sprite Draw()
	{
		return playerAnimation.currMap.sprite;
	}

	Direction DirectionFromKey()
	{
		if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A))
		{
			return Direction::UpLeft;
		}
		if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D))
		{
			return Direction::UpRight;
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A))
		{
			return Direction::DownLeft;
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::D))
		{
			return Direction::DownRight;
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			return Direction::Up;
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			return Direction::Right;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			return Direction::Down;
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			return Direction::Left;
		}
	}

	Vector2f MoveFromDirection(float const &time)
	{
		float dx = 0;
		float dy = 0;

		if (direction == Direction::Up) { dy = -speed * time; }
		else if (direction == Direction::Down) { dy = speed * time; }
		else if (direction == Direction::Left) { dx = -speed * time; }
		else if (direction == Direction::Right) { dx = speed * time; }
		else if (direction == Direction::UpLeft) { dx = -speed * 0.7f * time; dy = -speed * 0.7f * time; }
		else if (direction == Direction::UpRight) { dx = speed * 0.7f * time; dy = -speed * 0.7f * time; }
		else if (direction == Direction::DownLeft) { dx = -speed * 0.7f * time; dy = speed * 0.7f * time; }
		else if (direction == Direction::DownRight) { dx = speed * 0.7f * time; dy = speed * 0.7f * time; }

		return Vector2f(dx, dy);
	}

	void Update(float const &time)
	{
		Vector2f moveVector = {0, 0};
		isMove = false;

		if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::A) ||
			Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::D))
		{
			direction = DirectionFromKey();
			moveVector = MoveFromDirection(time);
			isMove = true;
		}

		x += moveVector.x; 
		y += moveVector.y;

		playerAnimation.Update(time, isMove, direction);  // адр анимации

		playerAnimation.currMap.sprite.setPosition(x, y); //ѕеремещение игрока
	}

private:
	Animation playerAnimation;

	float x;
	float y;

	float speed = 0.15;
	Direction direction = Direction::Up;
	bool isMove = false;
};

class Tower
{
public:
	SpriteMap spriteMap;

	Tower() = default;	
	Tower(String nameTowerTexture, int column, int line, float X, float Y)
		: x(X), y(Y)
	{
		spriteMap.SetSpriteMap(nameTowerTexture, column, line);
		spriteMap.sprite.setOrigin(spriteMap.sprite.getLocalBounds().width/2, spriteMap.sprite.getLocalBounds().height / 2);
		spriteMap.sprite.setPosition(x, y);
	}

	int GetNumFrameFromDirection(Vector2f posEnemy)
	{
		float dX = posEnemy.x - x;//вектор , колинеарный пр€мой, котора€ пересекает спрайт и курсор
		float dY = posEnemy.y - y;//он же, координата y
		float angle = (atan2(dY, dX)) * 180 / 3.14159265 + 90;//получаем угол в радианах и переводим его в градусы
		if (angle < 0) angle += 360;
		int frame = angle / (360. / (spriteMap.columns * spriteMap.lines));
		return frame;
	}

	void Update(float const &time, Vector2f posEnemy)
	{
		spriteMap.SetFrame(GetNumFrameFromDirection(posEnemy));
	}

private:
	float currFrame = 1;
	float damage;
	float reloadTimer;
	float x = 300;
	float y = 300;
};



int main()
{
	RenderWindow window(sf::VideoMode(1280, 720), "Game?");
	
	Player player("player_idle", 22, 8,
				  "player_idle_gun", 22, 8, 
				  "player_run", 22, 8, 
				  "player_run_gun", 22, 18);

	player.SetPosition(100, 100);

	CircleShape placeArea(100);
	Color placeAreaColor(200, 0, 0, 30);
	placeArea.setFillColor(placeAreaColor);
	placeArea.setOrigin(placeArea.getRadius() / 2, placeArea.getRadius() / 2);

	Tower tower("gun_turret", 2, 64, 300, 300);
	Tower tower2("twin_gun_turret", 8, 8, 200, 300);
	Tower tower3("laser_turret", 8, 8, 400, 200);
	list<Tower> towers;
	list<Tower>::iterator it;
	towers.push_back(tower);
	towers.push_back(tower2);
	towers.push_back(tower3);

	int selectTower;

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 1000;
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f mousePos = window.mapPixelToCoords(pixelPos);

		player.Update(time);
		placeArea.setPosition(player.GetPosition().x - 25, player.GetPosition().y);

		window.clear(Color::White);

		for (it = towers.begin(); it != towers.end();)
		{
			it->Update(time, mousePos);
			window.draw(it->spriteMap.sprite);
			it++;
		}

		window.draw(placeArea);
		window.draw(player.Draw());
		window.display();
	}

	return 0;
}