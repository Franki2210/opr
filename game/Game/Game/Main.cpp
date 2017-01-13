#include "Header.h"
#include "CalcHelp.h"
#include "FPS.h"
#include "SpriteMap.h"
#include "Tower.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Entity.h"
#include "Player.h"

class Icon
{
public:
	Sprite sprite;

	Icon() = default;
	Icon(string nameTexture)
	{
		if (!texture.loadFromFile(PATH_TO_TEXTURES + nameTexture + ".png"))
		{
			cout << "Сорян, не загрузилась: " << nameTexture << endl;
		}
		sprite.setTexture(texture);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sprite.setScale(Vector2f(0.2f, 0.2f));
	}
	~Icon() = default;

	void SetPosition(Vector2f pos)
	{
		sprite.setPosition(pos);
	}
	void SetPosition(float x, float y)
	{
		sprite.setPosition(Vector2f(x, y));
	}
	void Draw(RenderWindow & window)
	{
		window.draw(sprite);
	}

private:
	Texture texture;
};

void SpawnEnemy(list<Enemy*> & enemies, Enemy & enemy, Player & player)
{
	Enemy *spawnEnemy = new Enemy;
	*spawnEnemy = enemy;
	if (rand()%2 == 0)
	{
		spawnEnemy->SetPosition(player.GetPosition().x + rand() % 640, player.GetPosition().y + rand() % 360);
	}
	else
	{
		spawnEnemy->SetPosition(player.GetPosition().x - rand() % 640, player.GetPosition().y - rand() % 360);
	}
	
	enemies.push_back(spawnEnemy);
}

void TowerUpdateAndDraw(list<Tower*> & towersInGame, list<Enemy*> & enemies, list<Bullet*> & bullets, Player & player, Tower *placingTower, bool &establishedTower,
						bool & intersectAtPlacing, bool & drawActionArea, float & time, RenderWindow & window)
{
	for (auto it = towersInGame.begin(); it != towersInGame.end();)
	{
		Tower *tower = *it;
		if (tower->isDestroy)
		{
			it = towersInGame.erase(it);
			delete(tower);
		}
		else
		{
			//Если башня активна, обновляем состояние
			if (tower->isActive)
			{
				if (!enemies.empty())
				{
					float minDistance = 5000;
					Vector2f nearEnemyPosition = (*enemies.begin())->GetPosition();
					for (auto enemy = enemies.begin(); enemy != enemies.end(); enemy++)
					{
						Vector2f enemyPosition = (*enemy)->GetPosition();
						if (tower->actionArea.getGlobalBounds().contains(enemyPosition))
						{
							float distance = CalculateDistance(tower->GetPosition(), enemyPosition);
							if (distance < minDistance)
							{
								minDistance = distance;
								nearEnemyPosition = enemyPosition;
							}
						}
					}
					if (tower->actionArea.getGlobalBounds().contains(nearEnemyPosition))
					{
						tower->Update(time, nearEnemyPosition);
					}

					if (tower->canShot) //????
					{
						Bullet *bullet = new Bullet;
						*bullet = tower->GetBullet();
						bullet->SetEnemyPos(tower->GetEnemyPos());
						bullets.push_back(bullet);
						tower->canShot = false;
					}
				}
			}

			//Препятствие для игрока
			if (tower->spriteMap.sprite.getGlobalBounds().contains(player.GetPosition()))
			{
				player.SetObstacle(tower->spriteMap.sprite.getGlobalBounds());
			}

			//Если ставим новую башню...
			if (establishedTower)
			{
				//Не даём поставить новую башню на место установленной
				if (tower->spriteMap.sprite.getGlobalBounds().intersects(placingTower->spriteMap.sprite.getGlobalBounds()))
				{
					intersectAtPlacing = true;
				}
				window.draw(tower->boundsArea);
				window.draw(tower->actionArea);
			}

			//Отрисовка площади действия
			if (drawActionArea)
			{
				window.draw(tower->actionArea);
			}
			tower->Draw(window);
			it++;
		}
	}
}

void EnemiesUpdateAndDraw(list<Enemy*> & enemies, list<Tower*> & towersInGame, Player & player, RenderWindow & window, float & time)
{
	for (auto itEnemy = enemies.begin(); itEnemy != enemies.end();)
	{
		Enemy *enemy = *itEnemy;
		Vector2f itPosition = enemy->GetPosition();
		if (enemy->isDestroy)
		{
			itEnemy = enemies.erase(itEnemy);
			delete(enemy);
		}
		else
		{
			float minDistance = 5000;
			if (!towersInGame.empty())
			{
				//Находим близжайшую башню
				Tower *nearTower = enemy->tower;
				nearTower = *towersInGame.begin();
				minDistance = CalculateDistance(enemy->GetPosition(), nearTower->GetPosition());
				for (auto tower = towersInGame.begin(); tower != towersInGame.end(); tower++)
				{
					float distance = CalculateDistance(itPosition, (*tower)->GetPosition());
					if (distance < minDistance)
					{
						minDistance = distance;
						nearTower = *tower;
					}
				}
				enemy->SetTarget(nearTower);
				if (enemy->attackingPlayer) enemy->attackingPlayer = false;
			}

			if (minDistance > CalculateDistance(itPosition, player.GetPosition()) || towersInGame.empty())
			{
				enemy->SetTarget(&player);
				if (!enemy->attackingPlayer) enemy->attackingPlayer = true;
			}

			enemy->Update(time);
			(*itEnemy)->Draw(window);
			itEnemy++;
		}
	}
}

void BulletUpdateAndDraw(list<Bullet*> & bullets, list<Enemy*> & enemies, RenderWindow & window, float & time)
{
	for (auto it = bullets.begin(); it != bullets.end();)
	{
		Bullet *bullet = *it;	
		bullet->Update(time);
		Vector2f bulletPosition = bullet->GetPosition();
		for (auto enemy = enemies.begin(); enemy != enemies.end();)
		{
			if ((*enemy)->damageArea.getGlobalBounds().contains(bulletPosition))
			{
				(*enemy)->TakeDamage(bullet->GetDamage());
				bullet->arrived = true;
				break;
			}
			enemy++;
		}
		if (bullet->arrived)
		{
			it = bullets.erase(it);
			delete(bullet);
		}
		else
		{
			bullet->Draw(window);
			it++;
		}
	}
}

int main()
{
	ContextSettings settings;
	settings.antialiasingLevel = 4;

	RenderWindow window(VideoMode(1920, 1080), "Gama", Style::Fullscreen, settings);
	View view;
	view.reset(FloatRect(0, 0, 1280, 720));

	setlocale(LC_ALL, "rus");

	Player player("player_idle", 22, 8,
				  "player_idle_gun", 22, 8, 
				  "player_run", 22, 8, 
				  "player_run_gun", 22, 18);
	player.SetPosition(100, 100);
	player.SetBullet("bullet", 5, 1.f);

	Tower tower1("gun_turret", 2, 64);
	Tower tower2("twin_gun_turret", 8, 8);
	Tower tower3("laser_turret", 8, 8);

	tower1.SetBullet("bullet", 0.5f, 0.5f);
	tower2.SetBullet("twin_bullet", 1, 0.5f);
	tower3.SetBullet("laser_bullet", 5, 2.f);

	tower1.SetReloadTime(200);
	tower2.SetReloadTime(200);
	tower3.SetReloadTime(1000);

	tower1.SetActionRadius(100);	
	tower2.SetActionRadius(150);
	tower3.SetActionRadius(300);

	tower2.bullet.bulletSprite.setScale(Vector2f(1.1f, 1.1f));	

	Icon icon1("gun_turret_icon");
	Icon icon2("twin_gun_turret_icon");
	Icon icon3("laser_turret_icon");
	icon1.SetPosition(540, 650);
	icon2.SetPosition(640, 650);
	icon3.SetPosition(740, 650);

	CircleShape placeArea(150);
	Color placeAreaColor(0, 200, 0, 30);
	Color nonPlaceAreaColor(200, 0, 0, 30);
	placeArea.setFillColor(placeAreaColor);
	placeArea.setOrigin(placeArea.getRadius(), placeArea.getRadius());
	CircleShape nonPlaceArea(50);
	nonPlaceArea.setFillColor(nonPlaceAreaColor);
	nonPlaceArea.setOrigin(nonPlaceArea.getRadius(), nonPlaceArea.getRadius());
	
	Enemy enemy1;
	enemy1.SetTextureRun("enemy_run", 16, 16);
	enemy1.SetTextureAttack("enemy_attack", 11, 16);
	enemy1.SetSpeed(0.1f);
	enemy1.SetDamage(5);

	Enemy *spawnEnemy = new Enemy;
	list<Enemy*> enemies;

	float timerEnemySpawn = 2000;

	Tower *placingTower = new Tower;
	list<Tower*> towersInGame;

	bool intersectAtPlacing = false;
	bool establishedTower = false;
	bool drawActionArea = false;

	bool establishedEnemy = false;

	list<Bullet*> bullets;

	window.setKeyRepeatEnabled(false);
	Clock clock;
	FPS fps;

	Texture mapTex;
	mapTex.loadFromFile("map.png");
	Sprite mapSprite;
	mapSprite.setTexture(mapTex);
	//mapSprite.setOrigin(mapTex.getSize().x / 2, mapTex.getSize().y / 2);
	mapSprite.setScale(2, 2);

	Texture aimTex;
	aimTex.loadFromFile(PATH_TO_TEXTURES + "aim_cursor.png");
	Sprite aimSprite;
	aimSprite.setTexture(aimTex);
	aimSprite.setOrigin(aimTex.getSize().x / 2, aimTex.getSize().y / 2);
	aimSprite.setScale(0.15, 0.24);

	Texture handTex;
	handTex.loadFromFile(PATH_TO_TEXTURES + "hand_cursor.png");
	Sprite handSprite;
	handSprite.setTexture(handTex);
	handSprite.setOrigin(handTex.getSize().x / 2, handTex.getSize().y / 2);
	handSprite.setScale(0.5, 0.5);

	window.setMouseCursorVisible(false);

	while (window.isOpen())
	{
		float time = (float)clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 1000;
		fps.printFPS(time);

		Event event;

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f mousePos = window.mapPixelToCoords(pixelPos);

		player.isMove = false;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)//событие нажатия клавиши
			{
				if ((event.key.code == Keyboard::Num1) || (event.key.code == Keyboard::Num2) || (event.key.code == Keyboard::Num3))
				{
					if (!establishedTower) placingTower = new Tower;

					if (event.key.code == Keyboard::Num1) *placingTower = tower1;
					if (event.key.code == Keyboard::Num2) *placingTower = tower2;
					if (event.key.code == Keyboard::Num3) *placingTower = tower3;
					establishedTower = true;
				}

				if (event.key.code == Keyboard::G)
				{
					if (!establishedEnemy) spawnEnemy = new Enemy;
					*spawnEnemy = enemy1;
					establishedEnemy = true;
					spawnEnemy->isActive = false;
				}

				if (event.key.code == Keyboard::Space)
				{
					SpawnEnemy(enemies, enemy1, player);
				}
				if (event.key.code == Keyboard::Escape) window.close();
			}
		}

		timerEnemySpawn -= time;

		if (timerEnemySpawn <= 0)
		{
			timerEnemySpawn = 4000;
			//SpawnEnemy(enemies);
		}

		drawActionArea = false;
		if (Keyboard::isKeyPressed(Keyboard::R)) drawActionArea = true;

		window.clear(Color::White);

		window.draw(mapSprite);

		intersectAtPlacing = false;
		
		TowerUpdateAndDraw(towersInGame, enemies, bullets, player, placingTower, establishedTower, intersectAtPlacing, drawActionArea, time, window);
		BulletUpdateAndDraw(bullets, enemies, window, time);		
		EnemiesUpdateAndDraw(enemies, towersInGame, player, window, time);

		if (Mouse::isButtonPressed(Mouse::Left) && !establishedTower && !establishedEnemy && player.canShot)
		{
			Bullet *bullet = new Bullet;
			*bullet = player.GetBullet();
			bullet->SetPosition(player.GetPosition());
			bullet->SetEnemyPos(mousePos);
			bullets.push_back(bullet);
			player.canShot = false;
		}

		if (establishedEnemy)
		{
			spawnEnemy->SetPosition(mousePos);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				establishedEnemy = false;
				spawnEnemy->isActive = true;
				enemies.push_back(spawnEnemy);
				player.canShot = false;
			}
			spawnEnemy->Draw(window);
		}

		//Установка башни
		if (establishedTower)
		{
			placingTower->SetPosition(mousePos);
			if (placeArea.getGlobalBounds().contains(mousePos) && !nonPlaceArea.getGlobalBounds().contains(mousePos) && !intersectAtPlacing)
			{
				placingTower->spriteMap.sprite.setColor(Color::Green);
				window.draw(placingTower->actionArea);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					establishedTower = false;
					placingTower->isActive = true;
					placingTower->spriteMap.sprite.setColor(Color::White);
					towersInGame.push_back(placingTower);
					cout << towersInGame.size() << endl;
					player.canShot = false;
				}
			}
			else
			{
				placingTower->spriteMap.sprite.setColor(Color::Red);
			}
			placingTower->Update(time);
			placeArea.setPosition(player.GetPosition().x, player.GetPosition().y);
			nonPlaceArea.setPosition(player.GetPosition().x, player.GetPosition().y);
			window.draw(placeArea);
			window.draw(nonPlaceArea);
			window.draw(placingTower->spriteMap.sprite);
		}

		player.Update(time);
		player.Draw(window);

		if (player.GetPosition().x < 640 || player.GetPosition().x > 1472 || player.GetPosition().y < 360 || player.GetPosition().y > 1752)
		{
			float tempX = player.GetPosition().x;
			float tempY = player.GetPosition().y;
			if (player.GetPosition().x < 640) tempX = 640;
			if (player.GetPosition().x > 1472) tempX = 1472;
			if (player.GetPosition().y < 360) tempY = 360;
			if (player.GetPosition().y > 1752) tempY = 1752;
			view.setCenter(tempX, tempY);
		}
		else view.setCenter(player.GetPosition());
		window.setView(view);

		icon1.SetPosition(view.getCenter() + Vector2f(-100, 300));
		icon1.Draw(window);
		icon2.SetPosition(view.getCenter() + Vector2f(0, 300));
		icon2.Draw(window);
		icon3.SetPosition(view.getCenter() + Vector2f(100, 300));
		icon3.Draw(window);

		if (establishedTower || establishedEnemy)
		{
			handSprite.setPosition(mousePos);
			window.draw(handSprite);
		}
		else
		{
			aimSprite.setPosition(mousePos);
			window.draw(aimSprite);
		}
		
		window.display();
	}

	return 0;
}