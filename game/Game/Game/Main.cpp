#include "Header.h"
#include "CalcHelp.h"
#include "FPS.h"
#include "SpriteMap.h"
#include "Tower.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Entity.h"
#include "Player.h"
#include "Coin.h"
#include "Portal.h"
#include "Bonus.h"

/*
TODO: 
  Сделать препятствия
	по карте (возможно) (какие-либо объекты)
  Сделать уровни
    каждый уровень даёт испробывать новую пушку (в идеале)
	с каждым уровнем сложнее
  Добавить звуки и музыку
  Добавить основное меню
  Добавить паузу
  Добавить меню паузы
  Добавить интерфейс
*/
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

	void SetSprite(string nameTexture)
	{
		if (!texture.loadFromFile(PATH_TO_TEXTURES + nameTexture + ".png"))
		{
			cout << "Сорян, не загрузилась: " << nameTexture << endl;
		}
		sprite.setTexture(texture);
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		sprite.setScale(Vector2f(0.2f, 0.2f));
		sprite.setColor(Color(100, 100, 100));
	}

	void SetPosition(Vector2f pos)
	{
		sprite.setPosition(pos);
	}
	void SetPosition(float x, float y)
	{
		sprite.setPosition(Vector2f(x, y));
	}

	void SetActive(bool isActive_)
	{
		isActive = isActive_;
		if (!isActive)
		{
			sprite.setColor(Color(100, 100, 100));
		}
		else
		{
			sprite.setColor(Color::White);
		}
	}
	bool GetActive()
	{
		return isActive;
	}

	void Draw(RenderWindow & window)
	{
		window.draw(sprite);
	}

private:
	Texture texture;
	bool isActive = false;
};

struct AreasPlacingTower
{
	CircleShape placingArea;
	CircleShape notPlacingArea;
};
struct UsedIcons
{
	Icon icon1;
	Icon icon2;
	Icon icon3;
};
struct UsedTowers
{
	Tower tower1;
	Tower tower2;
	Tower tower3;
};
struct UsedEnemies
{
	Enemy enemy1;
	Enemy enemy2;
	Enemy enemy3;
};
struct UsedCursors
{
	Sprite aimCursor;
	Sprite handCursor;
	Texture aimTex;
	Texture handTex;
};
struct UsedPortal
{
	SpriteMap spriteMap;
};
struct UsedBonuses
{
	Bonus fireAcceleration;
	Bonus speedIncrease;
	Bonus damageIncrease;
	Bonus healthIncrease;
};

struct ActiveGameObjects
{

};

struct Obstacles
{
	RectangleShape topObstacle;
	RectangleShape downObstacle;
	RectangleShape leftObstacle;
	RectangleShape rightObstacle;
};

struct TexturesEnemies
{
	Texture texRun;
	Texture texAttack;
};
struct TexturesPlayer
{
	Texture idle;
	Texture run;
};
struct TextureBonuses
{
	Texture fireAccelTex;
	Texture speedIncTex;
	Texture damageIncTex;
	Texture healthIncTex;
};

struct Textures
{
	TexturesEnemies enemie1;
	TexturesEnemies enemie2;
	TexturesEnemies enemie3;
	TexturesPlayer player;
	TextureBonuses bonuses;
	Texture tower1;
	Texture tower2;
	Texture tower3;
	Texture coin;
	Texture portal;
	Texture map;

};

void SpawnCoin(list<Coin*> & coins, Coin & coin, int value, Vector2f position)
{
	Coin *newCoin = new Coin;
	*newCoin = coin;
	newCoin->SetPosition(position);
	newCoin->SetValue(value);
	coins.push_back(newCoin);
}
void SpawnBonus(list<Bonus*> & bonuses, UsedBonuses & usedBonuses, Vector2f position)
{
	int chanceFall = rand() % 100;
	if (chanceFall <= 30)
	{
		Bonus *newBonus = new Bonus;
		int chanceBonus = rand() % 4;
		if (chanceBonus == 0)
		{
			*newBonus = usedBonuses.damageIncrease;
		}
		if (chanceBonus == 1)
		{
			*newBonus = usedBonuses.fireAcceleration;
		}
		if (chanceBonus == 2)
		{
			*newBonus = usedBonuses.healthIncrease;
		}
		if (chanceBonus == 3)
		{
			*newBonus = usedBonuses.speedIncrease;
		}
		newBonus->SetPosition(position);
		bonuses.push_back(newBonus);
	}
}

void PlayerShot(Player & player, list<Bullet*> & bullets, Vector2f mousePos)
{
	Bullet *bullet = new Bullet;
	*bullet = player.GetBullet();
	bullet->SetStartPosition(player.GetPosition());
	bullet->SetEnemyPos(mousePos);
	bullets.push_back(bullet);
	player.canShot = false;
}
void CheckObstacles(Obstacles & obstacles, Player & player)
{
	if (obstacles.topObstacle.getGlobalBounds().intersects(player.GetGlobalBounds()))
	{
		player.SetObstacle(obstacles.topObstacle.getGlobalBounds());
	}
	else if (obstacles.downObstacle.getGlobalBounds().intersects(player.GetGlobalBounds()))
	{
		player.SetObstacle(obstacles.downObstacle.getGlobalBounds());
	}
	else if (obstacles.leftObstacle.getGlobalBounds().intersects(player.GetGlobalBounds()))
	{
		player.SetObstacle(obstacles.leftObstacle.getGlobalBounds());
	}
	else if (obstacles.rightObstacle.getGlobalBounds().intersects(player.GetGlobalBounds()))
	{
		player.SetObstacle(obstacles.rightObstacle.getGlobalBounds());
	}
}

void TowerUpdateAndDraw(list<Tower*> & towers, list<Enemy*> & enemies, list<Bullet*> & bullets, Player & player, Tower *placingTower, bool &towerInstallation,
						bool & intersectAtPlacing, bool & drawActionArea, float & time, RenderWindow & window)
{
	for (auto it = towers.begin(); it != towers.end();)
	{
		Tower *tower = *it;
		if (tower->isDestroy)
		{
			it = towers.erase(it);
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
			if (tower->spriteMap.sprite.getGlobalBounds().intersects(player.GetGlobalBounds()))
			{
				player.SetObstacle(tower->spriteMap.sprite.getGlobalBounds());
			}

			//Если ставим новую башню...
			if (towerInstallation)
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
void EnemiesUpdateAndDraw(list<Enemy*> & enemies, list<Tower*> & towers, list<Bonus*> & bonuses, UsedBonuses & usedBonuses, Player & player, 
							list<Coin*> & coins, Coin & coin, RenderWindow & window, float & time)
{
	for (auto itEnemy = enemies.begin(); itEnemy != enemies.end();)
	{
		Enemy *enemy = *itEnemy;
		Vector2f itPosition = enemy->GetPosition();
		if (enemy->isDestroy)
		{
			//TODO: Звук смерти врага
			SpawnCoin(coins, coin, enemy->GetCoins(), itPosition);
			player.AddCoins(enemy->GetCoins());
			SpawnBonus(bonuses, usedBonuses, itPosition);
			itEnemy = enemies.erase(itEnemy);
			delete(enemy);
		}
		else
		{
			float minDistance = 5000;
			if (!towers.empty())
			{
				//Находим близжайшую башню
				Tower *nearTower = enemy->tower;
				nearTower = *towers.begin();
				minDistance = CalculateDistance(enemy->GetPosition(), nearTower->GetPosition());
				for (auto tower = towers.begin(); tower != towers.end(); tower++)
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

			if (minDistance > CalculateDistance(itPosition, player.GetPosition()) || towers.empty())
			{
				enemy->SetTarget(&player);
				if (!enemy->attackingPlayer) enemy->attackingPlayer = true;
			}

			FloatRect enemyBounds = enemy->damageArea.getGlobalBounds();
			for (auto it = enemies.begin(); it != enemies.end(); ++it)
			{
				if ((*it)->damageArea.getGlobalBounds().intersects(enemyBounds))
				{
					Vector2f VectorBetweenEnemies = (*it)->GetPosition() - enemy->GetPosition();
					Vector2f VectorThrowing = VectorBetweenEnemies / 100.0f;
					enemy->SetPosition(enemy->GetPosition() - VectorThrowing);
				}
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
void CoinsUpdateAndDraw(list<Coin*> & coins, RenderWindow & window, float time)
{
	for (auto it = coins.begin(); it != coins.end();)
	{
		Coin *coin = *it;
		if (coin->destroy)
		{
			it = coins.erase(it);
			delete(coin);
		}
		else
		{
			coin->Update(time);
			coin->Draw(window);
			it++;
		}
	}
}
void IconsUpdateAndDraw(UsedIcons & usedIcons, UsedTowers & usedTowers, Player & player, View & view, RenderWindow & window)
{
	if (usedIcons.icon1.GetActive() && player.GetMoney() < usedTowers.tower1.GetPrice())
	{
		usedIcons.icon1.SetActive(false);
	}
	else if (!usedIcons.icon1.GetActive() && player.GetMoney() >= usedTowers.tower1.GetPrice())
	{
		usedIcons.icon1.SetActive(true);
	}

	if (usedIcons.icon2.GetActive() && player.GetMoney() < usedTowers.tower2.GetPrice())
	{
		usedIcons.icon2.SetActive(false);
	}
	else if (!usedIcons.icon2.GetActive() && player.GetMoney() >= usedTowers.tower2.GetPrice())
	{
		usedIcons.icon2.SetActive(true);
	}

	if (usedIcons.icon3.GetActive() && player.GetMoney() < usedTowers.tower3.GetPrice())
	{
		usedIcons.icon3.SetActive(false);
	}
	else if (!usedIcons.icon3.GetActive() && player.GetMoney() >= usedTowers.tower3.GetPrice())
	{
		usedIcons.icon3.SetActive(true);
	}

	usedIcons.icon1.SetPosition(view.getCenter() + Vector2f(-100, 300));
	usedIcons.icon1.Draw(window);
	usedIcons.icon2.SetPosition(view.getCenter() + Vector2f(0, 300));
	usedIcons.icon2.Draw(window);
	usedIcons.icon3.SetPosition(view.getCenter() + Vector2f(100, 300));
	usedIcons.icon3.Draw(window);
}
void PortalUpdateAndDraw(Portal & portal, RenderWindow & window, float time)
{
	portal.Update(time);
	portal.Draw(window);
}
void PlayerUpdateAndDraw(Player & player, RenderWindow & window, float time)
{
	player.Update(time);
	player.Draw(window);
}
void BonusesUpdateAndDraw(list<Bonus*> & bonuses, Player & player, RenderWindow & window, float time)
{
	for (auto it = bonuses.begin(); it != bonuses.end();)
	{
		Bonus *bonus = *it;
		if (bonus->isDestroy)
		{
			it = bonuses.erase(it);
			delete(bonus);
		}
		else
		{
			if (bonus->GetGlobalBound().contains(player.GetPosition()))
			{
				player.AddBonus(*bonus);
				bonus->isDestroy = true;
			}
			bonus->UpdateOnMap(time);
			bonus->Draw(window);
			it++;
		}
	}
}

void InitCursors(UsedCursors & usedCursors)
{
	if (!usedCursors.aimTex.loadFromFile(PATH_TO_TEXTURES + "aim_cursor.png"))
	{
		cout << "Сорян, не загрузилась: " << "aim_cursor.png" << endl;
	}
	usedCursors.aimCursor.setTexture(usedCursors.aimTex);
	usedCursors.aimCursor.setOrigin(usedCursors.aimTex.getSize().x / 2.0f, usedCursors.aimTex.getSize().y / 2.0f);
	usedCursors.aimCursor.setScale(0.15f, 0.24f);

	if (!usedCursors.handTex.loadFromFile(PATH_TO_TEXTURES + "hand_cursor.png"))
	{
		cout << "Сорян, не загрузилась: " << "hand_cursor.png" << endl;
	}
	usedCursors.handCursor.setTexture(usedCursors.handTex);
	usedCursors.handCursor.setOrigin(usedCursors.handTex.getSize().x / 2.0f, usedCursors.handTex.getSize().y / 2.0f);
	usedCursors.handCursor.setScale(0.5, 0.5);
}
void InitTowers(UsedTowers & usedTowers, Textures & textures)
{
	textures.tower1.loadFromFile(PATH_TO_TEXTURES + "towers/gun_turret.png");
	textures.tower2.loadFromFile(PATH_TO_TEXTURES + "towers/twin_gun_turret.png");
	textures.tower3.loadFromFile(PATH_TO_TEXTURES + "towers/laser_turret.png");
	usedTowers.tower1.SetSpriteMap(textures.tower1, 2, 64);
	usedTowers.tower2.SetSpriteMap(textures.tower2, 8, 8);
	usedTowers.tower3.SetSpriteMap(textures.tower3, 8, 8);

	usedTowers.tower1.SetMaxHp(300);
	usedTowers.tower2.SetMaxHp(200);
	usedTowers.tower3.SetMaxHp(100);

	usedTowers.tower1.SetBullet("bullet", 0.5f, 0.5f);
	usedTowers.tower2.SetBullet("twin_bullet", 1, 0.5f);
	usedTowers.tower3.SetBullet("laser_bullet", 5, 2.f);

	usedTowers.tower2.bullet.bulletSprite.setScale(Vector2f(1.1f, 1.1f));
	usedTowers.tower3.bullet.bulletSprite.setScale(Vector2f(1.1f, 1.1f));

	usedTowers.tower1.SetReloadTime(200);
	usedTowers.tower2.SetReloadTime(200);
	usedTowers.tower3.SetReloadTime(1000);

	usedTowers.tower1.SetActionRadius(150);
	usedTowers.tower2.SetActionRadius(200);
	usedTowers.tower3.SetActionRadius(300);

	usedTowers.tower1.SetPrice(50);
	usedTowers.tower2.SetPrice(100);
	usedTowers.tower3.SetPrice(300);
}
void InitIcons(UsedIcons & usedIcons)
{
	usedIcons.icon1.SetSprite("gun_turret_icon");
	usedIcons.icon2.SetSprite("twin_gun_turret_icon");
	usedIcons.icon3.SetSprite("laser_turret_icon");

	usedIcons.icon1.SetPosition(540, 650);
	usedIcons.icon2.SetPosition(640, 650);
	usedIcons.icon3.SetPosition(740, 650);
}
void InitEnemies(UsedEnemies & usedEnemies, Textures & textures)
{
	textures.enemie1.texRun.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy1_run.png");
	textures.enemie1.texAttack.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy1_attack.png");

	usedEnemies.enemy1.SetTextureRun(textures.enemie1.texRun, 16, 16);
	usedEnemies.enemy1.SetTextureAttack(textures.enemie1.texAttack, 11, 16);
	usedEnemies.enemy1.SetPosition(800, 800);
	usedEnemies.enemy1.SetMaxHp(50);
	usedEnemies.enemy1.SetSpeed(0.2f);
	usedEnemies.enemy1.SetDamage(3);
	usedEnemies.enemy1.SetCoins(10);
	usedEnemies.enemy1.SetSpeedAttackAnimation(0.01f);
	usedEnemies.enemy1.SetSpeedRunAnimation(0.04f);

	textures.enemie2.texRun.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy2_run.png");
	textures.enemie2.texAttack.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy2_attack.png");

	usedEnemies.enemy2.SetTextureRun(textures.enemie2.texRun, 24, 16);
	usedEnemies.enemy2.SetTextureAttack(textures.enemie2.texAttack, 22, 16);
	usedEnemies.enemy2.SetPosition(800, 800);
	usedEnemies.enemy2.SetMaxHp(100);
	usedEnemies.enemy2.SetSpeed(0.12f);
	usedEnemies.enemy2.SetDamage(5);
	usedEnemies.enemy2.SetCoins(25);
	usedEnemies.enemy2.SetSpeedAttackAnimation(0.01f);
	usedEnemies.enemy2.SetSpeedRunAnimation(0.04f);

	textures.enemie3.texRun.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy3_run.png");
	textures.enemie3.texAttack.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy3_attack.png");

	usedEnemies.enemy3.SetTextureRun(textures.enemie3.texRun, 30, 9);
	usedEnemies.enemy3.SetTextureAttack(textures.enemie3.texAttack, 15, 9);
	usedEnemies.enemy3.SetPosition(800, 800);
	usedEnemies.enemy3.SetMaxHp(300);
	usedEnemies.enemy3.SetBossAnim(true);
	usedEnemies.enemy3.SetSpeed(0.1f);
	usedEnemies.enemy3.SetDamage(10);
	usedEnemies.enemy3.SetCoins(100);
	usedEnemies.enemy3.SetSpeedAttackAnimation(0.01f);
	usedEnemies.enemy3.SetSpeedRunAnimation(0.03f);
	usedEnemies.enemy3.SetScale(1.2f, 1.2f);
}
void InitPlayer(Player & player, Textures & textures)
{
	textures.player.idle.loadFromFile(PATH_TO_TEXTURES + "player_idle.png");
	textures.player.run.loadFromFile(PATH_TO_TEXTURES + "player_run.png");
	player.SetSpriteMaps(textures.player.idle, 22, 8, textures.player.run, 22, 8);
	player.SetPosition(800, 600);
	player.SetSpeed(0.15f);
	player.SetBullet("bullet", 5, 1.f);
	player.SetTimeBetweenShots(150.0f);
	player.SetMaxHp(50);
}
void InitAreasPlacingTower(AreasPlacingTower & areasPlacing)
{
	areasPlacing.placingArea.setRadius(150);
	Color placeAreaColor(0, 200, 0, 30);
	areasPlacing.placingArea.setFillColor(placeAreaColor);
	areasPlacing.placingArea.setOrigin(areasPlacing.placingArea.getRadius(), areasPlacing.placingArea.getRadius());

	areasPlacing.notPlacingArea.setRadius(50);
	Color nonPlaceAreaColor(200, 0, 0, 30);
	areasPlacing.notPlacingArea.setFillColor(nonPlaceAreaColor);
	areasPlacing.notPlacingArea.setOrigin(areasPlacing.notPlacingArea.getRadius(), areasPlacing.notPlacingArea.getRadius());
}
void InitPortal(Portal & portal, Textures & textures)
{
	textures.portal.loadFromFile(PATH_TO_TEXTURES + "portal.png");
	portal.SetSpriteMap(textures.portal, 7, 1);
	portal.SetPosition(800, 800);
}
void InitCoin(Coin & coin, Textures & textures, Font font)
{
	textures.coin.loadFromFile(PATH_TO_TEXTURES + "coin.png");
	coin.SetSpriteMap(textures.coin, 10, 1);
	coin.SetFont(font);
}
void InitMap(Sprite & map, Textures & textures)
{
	textures.map.loadFromFile(PATH_TO_TEXTURES + "map/map.png");
	map.setTexture(textures.map);
	map.setScale(2, 2);
}
void InitObstacles(Obstacles & obstacles)
{
	obstacles.topObstacle.setPosition(0, 0);
	obstacles.topObstacle.setSize(Vector2f(2025, 74));
	obstacles.downObstacle.setPosition(0, 1994);
	obstacles.downObstacle.setSize(Vector2f(2025, 74));
	obstacles.leftObstacle.setPosition(0, 74);
	obstacles.leftObstacle.setSize(Vector2f(95, 1920));
	obstacles.rightObstacle.setPosition(2018, 74);
	obstacles.rightObstacle.setSize(Vector2f(95, 1920));
}
void InitBonuses(UsedBonuses & usedBonuses, Textures & textures)
{
	textures.bonuses.damageIncTex.loadFromFile(PATH_TO_TEXTURES + "bonuses/damage_increase.png");
	textures.bonuses.healthIncTex.loadFromFile(PATH_TO_TEXTURES + "bonuses/health_increase.png");
	textures.bonuses.speedIncTex.loadFromFile(PATH_TO_TEXTURES + "bonuses/speed_increase.png");
	textures.bonuses.fireAccelTex.loadFromFile(PATH_TO_TEXTURES + "bonuses/fire_acceleration.png");

	usedBonuses.damageIncrease.SetBonus("damageInc", textures.bonuses.damageIncTex, 15, 8000, 10000);
	usedBonuses.healthIncrease.SetBonus("healthInc", textures.bonuses.healthIncTex, 20, 8000);
	usedBonuses.speedIncrease.SetBonus("speedInc", textures.bonuses.speedIncTex, 0.1, 8000, 10000);
	usedBonuses.fireAcceleration.SetBonus("fireAccel", textures.bonuses.fireAccelTex, 50, 8000, 10000);
	usedBonuses.damageIncrease.SetScale(0.5f, 0.5f);
	usedBonuses.healthIncrease.SetScale(0.5f, 0.5f);
	usedBonuses.speedIncrease.SetScale(0.5f, 0.5f);
	usedBonuses.fireAcceleration.SetScale(0.5f, 0.5f);
}

int main()
{
	RenderWindow window(VideoMode(1280, 720), "Gama", Style::Default);
	View view;
	view.reset(FloatRect(0, 0, 1280, 720));

	Font fontForMoney;
	fontForMoney.loadFromFile(PATH_TO_FONTS + "for_money.ttf");
	Text playerMoneyText("", fontForMoney, 20);
	playerMoneyText.setStyle(Text::Bold);

	Textures textures;

	Player player;
	UsedTowers usedTowers;
	UsedIcons usedIcons;
	UsedEnemies usedEnemies;
	UsedCursors usedCursors;
	AreasPlacingTower areasPlacingTower;
	Portal portal;
	Obstacles obstacles;
	UsedBonuses usedBonuses;
	Coin coin;
	
	InitPlayer(player, textures);
	InitTowers(usedTowers, textures);
	InitIcons(usedIcons);
	InitEnemies(usedEnemies, textures);
	InitCursors(usedCursors);
	InitAreasPlacingTower(areasPlacingTower);
	InitPortal(portal, textures);
	InitObstacles(obstacles);
	InitBonuses(usedBonuses, textures);
	InitCoin(coin, textures, fontForMoney);

	list<Tower*> towers;
	list<Enemy*> enemies;
	list<Bullet*> bullets;
	list<Coin*> coins;
	list<Bonus*> bonuses;

	Tower *placingTower = new Tower;

	bool intersectAtPlacing = false;
	bool towerInstallation = false;
	bool drawActionArea = false;

	Sprite mapSprite;
	InitMap(mapSprite, textures);

	vector<int> mapUsedEnemies = {1,1,2,2,1,3,3,3,1,1,1,1,1,1,1,1,2,3,2,1,2,3,2,1,2,2,2,1,2,3,3,3,2,1,2,2,3,3,2,2};

	vector<Enemy*> enemiesInLevel;
	enemiesInLevel.reserve(mapUsedEnemies.size());
	for (size_t i = 0; i < mapUsedEnemies.size(); i++)
	{
		Enemy *newEnemy = new Enemy;
		if (mapUsedEnemies[i] == 1)
		{
			*newEnemy = usedEnemies.enemy1;
		}
		else if (mapUsedEnemies[i] == 2)
		{
			*newEnemy = usedEnemies.enemy2;
		}
		else if (mapUsedEnemies[i] == 3)
		{
			*newEnemy = usedEnemies.enemy3;
		}
		enemiesInLevel.push_back(newEnemy);
	}
	vector<Enemy*>::iterator iterEnemy = enemiesInLevel.begin();

	float timerEnemySpawn = 4000;
	int difLevel = 0;

	window.setKeyRepeatEnabled(false);
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(150);
	Clock clock;
	FPS fps;

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
				if (event.key.code == Keyboard::Num1 || event.key.code == Keyboard::Num2 || event.key.code == Keyboard::Num3)
				{
					if (event.key.code == Keyboard::Num1 && player.GetMoney() >= usedTowers.tower1.GetPrice())
					{
						if (!towerInstallation) placingTower = new Tower;
						*placingTower = usedTowers.tower1;
						towerInstallation = true;
					}
					if (event.key.code == Keyboard::Num2 && player.GetMoney() >= usedTowers.tower2.GetPrice())
					{
						if (!towerInstallation) placingTower = new Tower;
						*placingTower = usedTowers.tower2;
						towerInstallation = true;
					}
					if (event.key.code == Keyboard::Num3 && player.GetMoney() >= usedTowers.tower3.GetPrice())
					{
						if (!towerInstallation) placingTower = new Tower;
						*placingTower = usedTowers.tower3;
						towerInstallation = true;
					}
					
				}
				if (event.key.code == Keyboard::Space)
				{
					//SpawnEnemy(enemies, usedEnemies, player);
				}
				if (event.key.code == Keyboard::R)
				{
					if (drawActionArea == false) drawActionArea = true;
					else drawActionArea = false;
				}
				if (event.key.code == Keyboard::Escape) window.close();
			}
		}

		timerEnemySpawn -= time;

		if (timerEnemySpawn <= 0)
		{
			if (difLevel >= 0 && difLevel < 5)
			{
				timerEnemySpawn = 4000;
			}
			else if (difLevel >= 5 && difLevel < 10)
			{
				timerEnemySpawn = 3500;
			}
			else if (difLevel >= 10 && difLevel < 15)
			{
				timerEnemySpawn = 3000;
			}
			else if (difLevel >= 15)
			{
				timerEnemySpawn = 2500;
			}

			if (iterEnemy != enemiesInLevel.end())
			{
				enemies.push_back(*iterEnemy);
				iterEnemy++;
			}
			difLevel++;
		}
		intersectAtPlacing = false;

		window.clear(Color::White);

		window.draw(mapSprite);		
	
		PortalUpdateAndDraw(portal, window, time);
		TowerUpdateAndDraw(towers, enemies, bullets, player, placingTower, towerInstallation, intersectAtPlacing, drawActionArea, time, window);
		BulletUpdateAndDraw(bullets, enemies, window, time);		
		EnemiesUpdateAndDraw(enemies, towers, bonuses, usedBonuses, player, coins, coin, window, time);
		BonusesUpdateAndDraw(bonuses, player, window, time);

		if (Mouse::isButtonPressed(Mouse::Left) && !towerInstallation && player.canShot)
		{
			PlayerShot(player, bullets, mousePos);
		}

		//Установка башни
		if (towerInstallation)
		{
			placingTower->SetPosition(mousePos);
			if (areasPlacingTower.placingArea.getGlobalBounds().contains(mousePos) && !areasPlacingTower.notPlacingArea.getGlobalBounds().contains(mousePos) && !intersectAtPlacing)
			{
				placingTower->spriteMap.sprite.setColor(Color::Green);
				window.draw(placingTower->actionArea);
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					towerInstallation = false;
					placingTower->isActive = true;
					placingTower->spriteMap.sprite.setColor(Color::White);
					towers.push_back(placingTower);
					player.SubCoins(placingTower->GetPrice());
					player.canShot = false;
				}
			}
			else
			{
				placingTower->spriteMap.sprite.setColor(Color::Red);
			}
			placingTower->Update(time);
			areasPlacingTower.placingArea.setPosition(player.GetPosition());
			areasPlacingTower.notPlacingArea.setPosition(player.GetPosition());
			window.draw(areasPlacingTower.placingArea);
			window.draw(areasPlacingTower.notPlacingArea);
			window.draw(placingTower->spriteMap.sprite);
		}

		CheckObstacles(obstacles, player);
		PlayerUpdateAndDraw(player, window, time);

		CoinsUpdateAndDraw(coins, window, time);

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

		if (towerInstallation)
		{
			usedCursors.handCursor.setPosition(mousePos);
			window.draw(usedCursors.handCursor);
		}
		else
		{
			usedCursors.aimCursor.setPosition(mousePos);
			window.draw(usedCursors.aimCursor);
		}

		IconsUpdateAndDraw(usedIcons, usedTowers, player, view, window);

		ostringstream playerMoneyString;
		playerMoneyString << player.GetMoney();
		playerMoneyText.setString("Money: " + playerMoneyString.str());
		playerMoneyText.setPosition(view.getCenter() + Vector2f(-540, 260));
		window.draw(playerMoneyText);
		
		window.display();
	}

	return 0;
}