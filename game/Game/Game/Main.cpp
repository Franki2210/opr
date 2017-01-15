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
#include "ChangeHpView.h"

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

struct Obstacles
{
	RectangleShape topObstacle;
	RectangleShape downObstacle;
	RectangleShape leftObstacle;
	RectangleShape rightObstacle;
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
struct UsedBonuses
{
	Bonus fireAcceleration;
	Bonus speedIncrease;
	Bonus damageIncrease;
	Bonus healthIncrease;
};

struct UsedEntities
{
	UsedIcons icons;
	UsedTowers towers;
	UsedEnemies enemies;
	UsedCursors cursors;
	UsedBonuses bonuses;
	ChangeHpView changeHpView;
};

struct Entities
{
	Player player;
	Portal portal;
	Obstacles obstacles;
	list<Tower*> towers;
	list<Enemy*> enemies;
	list<Bullet*> bullets;
	list<Coin*> coins;
	list<Bonus*> bonuses;
	list<ChangeHpView*> changeHpViews;
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
void SpawnChangeHpView(list<ChangeHpView*> & changeHpViews, ChangeHpView & usedChangeHpView, float damage, Vector2f position)
{
	ChangeHpView* newChangeHpView = new ChangeHpView;
	*newChangeHpView = usedChangeHpView;
	newChangeHpView->SetPosition(position);
	newChangeHpView->SetValue(damage);
	changeHpViews.push_back(newChangeHpView);
}

void PlayerShot(Entities & entities, Vector2f mousePos)
{
	Bullet *bullet = new Bullet;
	*bullet = entities.player.GetBullet();
	bullet->SetStartPosition(entities.player.GetPosition());
	bullet->SetEnemyPos(mousePos);
	entities.bullets.push_back(bullet);
	entities.player.canShot = false;
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

void TowerUpdateAndDraw(Entities & entities, Tower *placingTower, bool & towerInstallation, bool & intersectAtPlacing, 
						bool & drawActionArea, float & time, RenderWindow & window)
{
	for (auto it = entities.towers.begin(); it != entities.towers.end();)
	{
		Tower *tower = *it;
		if (tower->isDestroy)
		{
			it = entities.towers.erase(it);
			delete(tower);
		}
		else
		{
			//Если башня активна, обновляем состояние
			if (tower->isActive)
			{
				if (!entities.enemies.empty())
				{
					float minDistance = 5000;
					Vector2f nearEnemyPosition = (*entities.enemies.begin())->GetPosition();
					for (auto enemy = entities.enemies.begin(); enemy != entities.enemies.end(); enemy++)
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
						entities.bullets.push_back(bullet);
						tower->canShot = false;
					}
				}
			}

			//Препятствие для игрока
			if (tower->spriteMap.sprite.getGlobalBounds().intersects(entities.player.GetGlobalBounds()))
			{
				entities.player.SetObstacle(tower->spriteMap.sprite.getGlobalBounds());
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
void EnemiesUpdateAndDraw(Entities & entities, UsedBonuses & bonuses, Coin & coin, RenderWindow & window, float & time)
{
	for (auto itEnemy = entities.enemies.begin(); itEnemy != entities.enemies.end();)
	{
		Enemy *enemy = *itEnemy;
		Vector2f itPosition = enemy->GetPosition();
		if (enemy->isDestroy)
		{
			//TODO: Звук смерти врага
			SpawnCoin(entities.coins, coin, enemy->GetCoins(), itPosition);
			entities.player.AddCoins(enemy->GetCoins());
			SpawnBonus(entities.bonuses, bonuses, itPosition);

			itEnemy = entities.enemies.erase(itEnemy);
			delete(enemy);
		}
		else
		{
			float minDistance = 5000;
			if (!entities.towers.empty())
			{
				//Находим близжайшую башню
				Tower *nearTower = enemy->tower;
				nearTower = *entities.towers.begin();
				minDistance = CalculateDistance(enemy->GetPosition(), nearTower->GetPosition());
				for (auto tower = entities.towers.begin(); tower != entities.towers.end(); tower++)
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

			if (minDistance > CalculateDistance(itPosition, entities.player.GetPosition()) || entities.towers.empty())
			{
				enemy->SetTarget(&entities.player);
				if (!enemy->attackingPlayer) enemy->attackingPlayer = true;
			}

			//Проверка столкновения между врагами
			FloatRect enemyBounds = enemy->damageArea.getGlobalBounds();
			for (auto it = entities.enemies.begin(); it != entities.enemies.end(); ++it)
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
void BulletUpdateAndDraw(Entities & entities, UsedEntities & usedEntities, RenderWindow & window, float & time)
{
	for (auto it = entities.bullets.begin(); it != entities.bullets.end();)
	{
		Bullet *bullet = *it;	
		bullet->Update(time);
		Vector2f bulletPosition = bullet->GetPosition();
		for (auto enemy = entities.enemies.begin(); enemy != entities.enemies.end();)
		{
			if ((*enemy)->damageArea.getGlobalBounds().contains(bulletPosition))
			{
				float damage = bullet->GetDamage();
				(*enemy)->TakeDamage(damage);
				bullet->arrived = true;
				SpawnChangeHpView(entities.changeHpViews, usedEntities.changeHpView, damage, bulletPosition);
				break;
			}
			enemy++;
		}
		if (bullet->arrived)
		{
			it = entities.bullets.erase(it);
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
void IconsUpdateAndDraw(UsedEntities & usedEntities, Entities & entities, View & view, RenderWindow & window)
{
	if (usedEntities.icons.icon1.GetActive() && entities.player.GetMoney() < usedEntities.towers.tower1.GetPrice())
	{
		usedEntities.icons.icon1.SetActive(false);
	}
	else if (!usedEntities.icons.icon1.GetActive() && entities.player.GetMoney() >= usedEntities.towers.tower1.GetPrice())
	{
		usedEntities.icons.icon1.SetActive(true);
	}

	if (usedEntities.icons.icon2.GetActive() && entities.player.GetMoney() < usedEntities.towers.tower2.GetPrice())
	{
		usedEntities.icons.icon2.SetActive(false);
	}
	else if (!usedEntities.icons.icon2.GetActive() && entities.player.GetMoney() >= usedEntities.towers.tower2.GetPrice())
	{
		usedEntities.icons.icon2.SetActive(true);
	}

	if (usedEntities.icons.icon3.GetActive() && entities.player.GetMoney() < usedEntities.towers.tower3.GetPrice())
	{
		usedEntities.icons.icon3.SetActive(false);
	}
	else if (!usedEntities.icons.icon3.GetActive() && entities.player.GetMoney() >= usedEntities.towers.tower3.GetPrice())
	{
		usedEntities.icons.icon3.SetActive(true);
	}

	usedEntities.icons.icon1.SetPosition(view.getCenter() + Vector2f(-100, 300));
	usedEntities.icons.icon1.Draw(window);
	usedEntities.icons.icon2.SetPosition(view.getCenter() + Vector2f(0, 300));
	usedEntities.icons.icon2.Draw(window);
	usedEntities.icons.icon3.SetPosition(view.getCenter() + Vector2f(100, 300));
	usedEntities.icons.icon3.Draw(window);
}
void PortalUpdateAndDraw(Entities & entities, RenderWindow & window, float time)
{
	entities.portal.Update(time);
	entities.portal.Draw(window);
}
void PlayerUpdateAndDraw(Player & player, RenderWindow & window, float time)
{
	player.Update(time);
	player.Draw(window);
}
void BonusesUpdateAndDraw(Entities & entities, RenderWindow & window, float time)
{
	for (auto it = entities.bonuses.begin(); it != entities.bonuses.end();)
	{
		Bonus *bonus = *it;
		if (bonus->isDestroy)
		{
			it = entities.bonuses.erase(it);
			delete(bonus);
		}
		else
		{
			if (bonus->GetGlobalBound().contains(entities.player.GetPosition()))
			{
				entities.player.AddBonus(*bonus);
				bonus->isDestroy = true;
			}
			bonus->UpdateOnMap(time);
			bonus->Draw(window);
			it++;
		}
	}
}
void ChangeHpViewsUpdateAndDraw(Entities & entities, RenderWindow & window, float time)
{
	for (auto it = entities.changeHpViews.begin(); it != entities.changeHpViews.end();)
	{
		ChangeHpView *hp = *it;
		if (hp->destroy)
		{
			it = entities.changeHpViews.erase(it);
			delete(hp);
		}
		else
		{
			hp->Update(time);
			hp->Draw(window);
			it++;
		}
	}
}

void InitCursors(UsedCursors & cursors)
{
	if (!cursors.aimTex.loadFromFile(PATH_TO_TEXTURES + "aim_cursor.png"))
	{
		cout << "Сорян, не загрузилась: " << "aim_cursor.png" << endl;
	}
	cursors.aimCursor.setTexture(cursors.aimTex);
	cursors.aimCursor.setOrigin(cursors.aimTex.getSize().x / 2.0f, cursors.aimTex.getSize().y / 2.0f);
	cursors.aimCursor.setScale(0.15f, 0.24f);

	if (!cursors.handTex.loadFromFile(PATH_TO_TEXTURES + "hand_cursor.png"))
	{
		cout << "Сорян, не загрузилась: " << "hand_cursor.png" << endl;
	}
	cursors.handCursor.setTexture(cursors.handTex);
	cursors.handCursor.setOrigin(cursors.handTex.getSize().x / 2.0f, cursors.handTex.getSize().y / 2.0f);
	cursors.handCursor.setScale(0.5, 0.5);
}
void InitTowers(UsedTowers & towers, Textures & textures)
{
	textures.tower1.loadFromFile(PATH_TO_TEXTURES + "towers/gun_turret.png");
	towers.tower1.SetSpriteMap(textures.tower1, 2, 64);
	towers.tower1.SetMaxHp(300);
	towers.tower1.SetBullet("bullet", 1.0f, 0.5f);
	towers.tower1.SetReloadTime(200);
	towers.tower1.SetActionRadius(150);
	towers.tower1.SetPrice(50);

	textures.tower2.loadFromFile(PATH_TO_TEXTURES + "towers/twin_gun_turret.png");
	towers.tower2.SetSpriteMap(textures.tower2, 8, 8);
	towers.tower2.SetMaxHp(200);
	towers.tower2.SetBullet("twin_bullet", 2.0f, 0.5f);
	towers.tower2.bullet.bulletSprite.setScale(Vector2f(1.1f, 1.1f));
	towers.tower2.SetReloadTime(200);
	towers.tower2.SetActionRadius(200);
	towers.tower2.SetPrice(100);

	textures.tower3.loadFromFile(PATH_TO_TEXTURES + "towers/laser_turret.png");
	towers.tower3.SetSpriteMap(textures.tower3, 8, 8);
	towers.tower3.SetMaxHp(100);
	towers.tower3.SetBullet("laser_bullet", 10, 2.f);
	towers.tower3.bullet.bulletSprite.setScale(Vector2f(1.1f, 1.1f));
	towers.tower3.SetReloadTime(1000);
	towers.tower3.SetActionRadius(300);
	towers.tower3.SetPrice(300);
}
void InitIcons(UsedIcons & icons)
{
	icons.icon1.SetSprite("gun_turret_icon");
	icons.icon2.SetSprite("twin_gun_turret_icon");
	icons.icon3.SetSprite("laser_turret_icon");

	icons.icon1.SetPosition(540, 650);
	icons.icon2.SetPosition(640, 650);
	icons.icon3.SetPosition(740, 650);
}
void InitEnemies(UsedEnemies & enemies, Textures & textures)
{
	textures.enemie1.texRun.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy1_run.png");
	textures.enemie1.texAttack.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy1_attack.png");

	enemies.enemy1.SetTextureRun(textures.enemie1.texRun, 16, 16);
	enemies.enemy1.SetTextureAttack(textures.enemie1.texAttack, 11, 16);
	enemies.enemy1.SetPosition(800, 800);
	enemies.enemy1.SetMaxHp(35);
	enemies.enemy1.SetSpeed(0.2f);
	enemies.enemy1.SetDamage(3);
	enemies.enemy1.SetCoins(10);
	enemies.enemy1.SetSpeedAttackAnimation(0.01f);
	enemies.enemy1.SetSpeedRunAnimation(0.04f);

	textures.enemie2.texRun.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy2_run.png");
	textures.enemie2.texAttack.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy2_attack.png");

	enemies.enemy2.SetTextureRun(textures.enemie2.texRun, 24, 16);
	enemies.enemy2.SetTextureAttack(textures.enemie2.texAttack, 22, 16);
	enemies.enemy2.SetPosition(800, 800);
	enemies.enemy2.SetMaxHp(100);
	enemies.enemy2.SetSpeed(0.12f);
	enemies.enemy2.SetDamage(5);
	enemies.enemy2.SetCoins(25);
	enemies.enemy2.SetSpeedAttackAnimation(0.01f);
	enemies.enemy2.SetSpeedRunAnimation(0.04f);

	textures.enemie3.texRun.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy3_run.png");
	textures.enemie3.texAttack.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy3_attack.png");

	enemies.enemy3.SetTextureRun(textures.enemie3.texRun, 30, 9);
	enemies.enemy3.SetTextureAttack(textures.enemie3.texAttack, 15, 9);
	enemies.enemy3.SetPosition(800, 800);
	enemies.enemy3.SetMaxHp(300);
	enemies.enemy3.SetBossAnim(true);
	enemies.enemy3.SetSpeed(0.1f);
	enemies.enemy3.SetDamage(10);
	enemies.enemy3.SetCoins(100);
	enemies.enemy3.SetSpeedAttackAnimation(0.01f);
	enemies.enemy3.SetSpeedRunAnimation(0.03f);
	enemies.enemy3.SetScale(1.2f, 1.2f);
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
void InitChangeHpView(ChangeHpView & changeHpView, Font font)
{
	changeHpView.SetFont(font);
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
void InitBonuses(UsedBonuses & bonuses, Textures & textures)
{
	textures.bonuses.damageIncTex.loadFromFile(PATH_TO_TEXTURES + "bonuses/damage_increase.png");
	textures.bonuses.healthIncTex.loadFromFile(PATH_TO_TEXTURES + "bonuses/health_increase.png");
	textures.bonuses.speedIncTex.loadFromFile(PATH_TO_TEXTURES + "bonuses/speed_increase.png");
	textures.bonuses.fireAccelTex.loadFromFile(PATH_TO_TEXTURES + "bonuses/fire_acceleration.png");

	bonuses.damageIncrease.SetBonus("damageInc", textures.bonuses.damageIncTex, 15, 8000, 10000);
	bonuses.healthIncrease.SetBonus("healthInc", textures.bonuses.healthIncTex, 20, 8000);
	bonuses.speedIncrease.SetBonus("speedInc", textures.bonuses.speedIncTex, 0.1, 8000, 10000);
	bonuses.fireAcceleration.SetBonus("fireAccel", textures.bonuses.fireAccelTex, 50, 8000, 10000);
	bonuses.damageIncrease.SetScale(0.5f, 0.5f);
	bonuses.healthIncrease.SetScale(0.5f, 0.5f);
	bonuses.speedIncrease.SetScale(0.5f, 0.5f);
	bonuses.fireAcceleration.SetScale(0.5f, 0.5f);
}

int main()
{
	RenderWindow window(VideoMode(1280, 720), "Gama", Style::Default);
	View view;
	view.reset(FloatRect(0, 0, 1280, 720));

	Font font;
	font.loadFromFile(PATH_TO_FONTS + "font1.ttf");
	Text playerMoneyText("", font, 20);
	playerMoneyText.setStyle(Text::Bold);

	UsedEntities usedEntities;
	Textures textures;
	Entities entities;

	AreasPlacingTower areasPlacingTower;

	Coin coin;
	
	InitPlayer(entities.player, textures);
	InitTowers(usedEntities.towers, textures);
	InitIcons(usedEntities.icons);
	InitEnemies(usedEntities.enemies, textures);
	InitCursors(usedEntities.cursors);
	InitAreasPlacingTower(areasPlacingTower);
	InitPortal(entities.portal, textures);
	InitObstacles(entities.obstacles);
	InitBonuses(usedEntities.bonuses, textures);
	InitCoin(coin, textures, font);
	InitChangeHpView(usedEntities.changeHpView, font);

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
			*newEnemy = usedEntities.enemies.enemy1;
		}
		else if (mapUsedEnemies[i] == 2)
		{
			*newEnemy = usedEntities.enemies.enemy2;
		}
		else if (mapUsedEnemies[i] == 3)
		{
			*newEnemy = usedEntities.enemies.enemy3;
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

		entities.player.isMove = false;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)//событие нажатия клавиши
			{
				if (event.key.code == Keyboard::Num1 || event.key.code == Keyboard::Num2 || event.key.code == Keyboard::Num3)
				{
					if (event.key.code == Keyboard::Num1 && entities.player.GetMoney() >= usedEntities.towers.tower1.GetPrice())
					{
						if (!towerInstallation) placingTower = new Tower;
						*placingTower = usedEntities.towers.tower1;
						towerInstallation = true;
					}
					if (event.key.code == Keyboard::Num2 && entities.player.GetMoney() >= usedEntities.towers.tower2.GetPrice())
					{
						if (!towerInstallation) placingTower = new Tower;
						*placingTower = usedEntities.towers.tower2;
						towerInstallation = true;
					}
					if (event.key.code == Keyboard::Num3 && entities.player.GetMoney() >= usedEntities.towers.tower3.GetPrice())
					{
						if (!towerInstallation) placingTower = new Tower;
						*placingTower = usedEntities.towers.tower3;
						towerInstallation = true;
					}
					
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
				entities.enemies.push_back(*iterEnemy);
				iterEnemy++;
			}
			difLevel++;
		}
		intersectAtPlacing = false;

		window.clear(Color::White);

		window.draw(mapSprite);		
	
		PortalUpdateAndDraw(entities, window, time);
		TowerUpdateAndDraw(entities, placingTower, towerInstallation, intersectAtPlacing, drawActionArea, time, window);
		BulletUpdateAndDraw(entities, usedEntities, window, time);
		EnemiesUpdateAndDraw(entities, usedEntities.bonuses, coin, window, time);
		BonusesUpdateAndDraw(entities, window, time);
		ChangeHpViewsUpdateAndDraw(entities, window, time);

		if (Mouse::isButtonPressed(Mouse::Left) && !towerInstallation && entities.player.canShot)
		{
			PlayerShot(entities, mousePos);
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
					entities.towers.push_back(placingTower);
					entities.player.SubCoins(placingTower->GetPrice());
					entities.player.canShot = false;
				}
			}
			else
			{
				placingTower->spriteMap.sprite.setColor(Color::Red);
			}
			placingTower->Update(time);
			areasPlacingTower.placingArea.setPosition(entities.player.GetPosition());
			areasPlacingTower.notPlacingArea.setPosition(entities.player.GetPosition());
			window.draw(areasPlacingTower.placingArea);
			window.draw(areasPlacingTower.notPlacingArea);
			window.draw(placingTower->spriteMap.sprite);
		}

		CheckObstacles(entities.obstacles, entities.player);
		PlayerUpdateAndDraw(entities.player, window, time);

		CoinsUpdateAndDraw(entities.coins, window, time);

		if (entities.player.GetPosition().x < 640 || entities.player.GetPosition().x > 1472 || entities.player.GetPosition().y < 360 || entities.player.GetPosition().y > 1752)
		{
			float tempX = entities.player.GetPosition().x;
			float tempY = entities.player.GetPosition().y;
			if (entities.player.GetPosition().x < 640) tempX = 640;
			if (entities.player.GetPosition().x > 1472) tempX = 1472;
			if (entities.player.GetPosition().y < 360) tempY = 360;
			if (entities.player.GetPosition().y > 1752) tempY = 1752;
			view.setCenter(tempX, tempY);
		}
		else view.setCenter(entities.player.GetPosition());
		window.setView(view);

		if (towerInstallation)
		{
			usedEntities.cursors.handCursor.setPosition(mousePos);
			window.draw(usedEntities.cursors.handCursor);
		}
		else
		{
			usedEntities.cursors.aimCursor.setPosition(mousePos);
			window.draw(usedEntities.cursors.aimCursor);
		}

		IconsUpdateAndDraw(usedEntities, entities, view, window);

		ostringstream playerMoneyString;
		playerMoneyString << entities.player.GetMoney();
		playerMoneyText.setString("Money: " + playerMoneyString.str());
		playerMoneyText.setPosition(view.getCenter() + Vector2f(-540, 260));
		window.draw(playerMoneyText);
		
		window.display();
	}

	return 0;
}