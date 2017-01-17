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
#include "Meteor.h"
#include "Explosion.h"
#include "Menu.h"
#include "Lose.h"
#include "Win.h"

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

/*
TODO:
  Добавить облачко после монстра
*/

class CameraShake
{
public:
	CameraShake() = default;
	~CameraShake() = default;

	void SetShake(bool shake)
	{
		isShake = shake;
	}
	bool GetShake()
	{
		return isShake;
	}
	void SetOffsetWithShake(int value)
	{
		offset = value;
	}

	void Update(View & view, Vector2f & positionPlayer, float time)
	{
		if (timerShake > 0 && isShake)
		{
			timerShake -= time;
			Vector2f randPosition((offset/2) - float(rand()%offset), (offset / 2) - float(rand() % offset));
			view.setCenter(positionPlayer + randPosition);
		}
		else
		{
			isShake = false;
			timerShake = timeShake;
		}
	}
private:
	float timeShake = 1000.0f;
	float timerShake = timeShake;
	int offset = 1;
	bool isShake;
};
class Vignette
{
public:
	Vignette() = default;
	~Vignette() = default;
	
	void SetTexture(Texture & texture)
	{
		sprite.setTexture(texture);
		sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
	}

	void SetActive(bool value)
	{
		isActive = value;
	}
	bool GetActive()
	{
		return isActive;
	}

	void Draw(RenderWindow & window)
	{
		sprite.setPosition(window.getView().getCenter());
		window.draw(sprite);
	}
private:
	bool isActive = false;
	Sprite sprite;
};
class ToxicCloud
{
public:
	ToxicCloud() = default;
	~ToxicCloud() = default;

	void SetToxicCloud(Texture & texture, int columnsInMap, int linesInMap)
	{
		spriteMap.SetSpriteMap(texture, columnsInMap, linesInMap);
	}

	void SetPosition(Vector2f pos)
	{
		position = pos;
		spriteMap.sprite.setPosition(position);
	}
	void SetPosition(float x, float y)
	{
		position = Vector2f(x, y);
		spriteMap.sprite.setPosition(position);
	}
	Vector2f GetPosition()
	{
		return position;
	}

	void SetSpeedAnimation(float value)
	{
		speedAnimation = value;
	}

	FloatRect GetGlobalBounds()
	{
		return spriteMap.sprite.getGlobalBounds();
	}

	void SetTimeToDestroy(float value)
	{
		timeToDestroy = value;
		timerToDestroy = timeToDestroy;
	}

	void SetSpeedDamage(float value)
	{
		speedDamage = value;
	}
	float GetSpeedDamage()
	{
		return speedDamage;
	}

	void SetDamage(float value)
	{
		damage = value;
	}
	float GetDamage()
	{
		return damage;
	}

	bool GetIsDestroy()
	{
		return isDestroy;
	}

	void Update(float & time)
	{
		if (timerToDestroy > 0)
		{
			timerToDestroy -= time;
			currFrame += speedAnimation * time;
			if (currFrame >= spriteMap.GetColumns() * spriteMap.GetLines())
			{
				currFrame = 0;
			}
			spriteMap.SetFrame((int)currFrame);
			if (timerToDestroy < timeToDestroy && timerToDestroy > timeToDestroy - 1000.0f)
			{
				currAlpha += 0.26f * time;
				if (currAlpha >= 255) currAlpha = 255;
				spriteMap.sprite.setColor(Color(255, 255, 255, (Uint8)currAlpha));
			}
			if (timerToDestroy < 2000)
			{
				currAlpha -= 0.13f * time;
				if (currAlpha <= 0) currAlpha = 0;
				spriteMap.sprite.setColor(Color(255, 255, 255, (Uint8)currAlpha));
			}
		}
		else 
		{ 
			isDestroy = true; 
		}
	}

	void Draw(RenderWindow & window)
	{
		window.draw(spriteMap.sprite);
	}

private:
	Vector2f position;
	float timeToDestroy = 10000;
	float timerToDestroy = timeToDestroy;
	bool isDestroy = false;
	SpriteMap spriteMap;
	float speedAnimation = 1;
	float currFrame = 1;
	float speedDamage = 0;
	float damage = 0;
	float currAlpha = 0;
};
class EnemyExplosion
{
public:
	EnemyExplosion() = default;
	~EnemyExplosion() = default;

	void SetEnemyExplosion(Texture & texture, int columnsInMap, int linesInMap)
	{
		spriteMap.SetSpriteMap(texture, columnsInMap, linesInMap);
	}

	void SetSpeedAnimation(float value)
	{
		speedAnimation = value;
	}

	void SetTimeToDestroy(float value)
	{
		timeToDestroy = value;
		timerToDestroy = timeToDestroy;
	}

	void SetPosition(Vector2f pos)
	{
		position = pos;
		spriteMap.sprite.setPosition(position);
	}
	void SetPosition(float x, float y)
	{
		position = Vector2f(x, y);
		spriteMap.sprite.setPosition(position);
	}
	Vector2f GetPosition()
	{
		return position;
	}

	bool GetIsDestroy()
	{
		return isDestroy;
	}

	void Update(float time)
	{
		if (timerToDestroy > 0)
		{
			timerToDestroy -= time;
			if (currFrame < spriteMap.GetColumns() * spriteMap.GetLines())
			{
				spriteMap.SetFrame((int)currFrame);
				currFrame += speedAnimation * time;
			}
			if (timerToDestroy < 2000)
			{
				currAlpha -= 0.13f * time;
				if (currAlpha <= 0) currAlpha = 0;
				spriteMap.sprite.setColor(Color(255, 255, 255, (Uint8)currAlpha));
			}
		}
		else isDestroy = true;
	}

	void Draw(RenderWindow & window)
	{
		window.draw(spriteMap.sprite);
	}
private:
	float timeToDestroy = 4000;
	float timerToDestroy = timeToDestroy;
	float currFrame = 0;
	float currAlpha = 255;
	SpriteMap spriteMap;
	Vector2f position;
	bool isDestroy = false;
	float speedAnimation = 0.14f;
};

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

struct TexturesEnemie
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
struct TexturesBullets
{
	Texture gunShot;
	Texture twinGunShot;
	Texture laserShot;
};
struct TexturesMeteor
{
	Texture texture;
	Texture shadow;
	Texture pointArrival;
};

struct Textures
{
	TexturesEnemie enemie1;
	TexturesEnemie enemie2;
	TexturesEnemie enemie3;
	TexturesPlayer player;
	TextureBonuses bonuses;
	TexturesBullets bullets;
	TexturesMeteor meteor;
	Texture tower1;
	Texture tower2;
	Texture tower3;
	Texture coin;
	Texture portal;
	Texture map;
	Texture explosion;
	Texture vignette;
	Texture toxicCloud;
	Texture enemyExplosion;
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
struct UsedBullets
{
	Bullet playerGunShot;
	Bullet gunShot;
	Bullet twinGunShot;
	Bullet laserShot;
};
struct UsedEntities
{
	UsedIcons icons;
	UsedTowers towers;
	UsedEnemies enemies;
	UsedCursors cursors;
	UsedBonuses bonuses;
	UsedBullets bullets;
	ChangeHpView changeHpView;
	Meteor meteor;
	Explosion explosion;
	ToxicCloud toxicCloud;
	EnemyExplosion enemyExplosion;
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
	list<Meteor*> meteors;
	list<Explosion*> explosions;
	list<ToxicCloud*> toxicClouds;
	list<EnemyExplosion*> enemyExplosions;
};

struct UsedTextsTowersPrice
{
	Text tower1;
	Text tower2;
	Text tower3;
};
struct UsedTexts
{
	UsedTextsTowersPrice towersPrice;
};

struct GunShotSounds
{
	SoundBuffer shot1Buffer;
	SoundBuffer shot2Buffer;
	SoundBuffer shot3Buffer;
	Sound shot1;
	Sound shot2;
	Sound shot3;
};
struct LaserShotSounds
{
	SoundBuffer shot1Buffer;
	SoundBuffer shot2Buffer;
	SoundBuffer shot3Buffer;

	Sound shot1;
	Sound shot2;
	Sound shot3;
	Sound shot4;
};
struct StepsSounds
{
	SoundBuffer step1;
	SoundBuffer step2;
	SoundBuffer step3;
	SoundBuffer step4;
};
struct OneSound
{
	SoundBuffer soundBuf;
	Sound sound;
};
struct UsedSounds
{
	GunShotSounds playerGunShots;
	GunShotSounds gunShots;
	LaserShotSounds laserShots;
	StepsSounds steps;
	OneSound placeTower;
	OneSound dropItem;
	OneSound meteorFall;
	OneSound evilLaugh;
	OneSound explosion;
	OneSound heartbeat;
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
void SpawnExplosion(list<Explosion*> & explosions, Explosion & explosion, CameraShake & cameraShake, Vector2f position, RenderWindow & window)
{
	Explosion *newExplosion = new Explosion;
	*newExplosion = explosion;
	newExplosion->SetPosition(position);
	FloatRect rect;
	rect.left = window.getView().getCenter().x - window.getView().getSize().x / 2;
	rect.top = window.getView().getCenter().y - window.getView().getSize().y / 2;
	rect.height = window.getView().getSize().y;
	rect.width = window.getView().getSize().x;
	if (rect.contains(position))
	{
		newExplosion->GetSound()->play();
		cameraShake.SetShake(true);
	}	
	explosions.push_back(newExplosion);
}
void SpawnToxicCloud(list<ToxicCloud*> & toxicClouds, ToxicCloud & toxicCloud, Vector2f position)
{
	ToxicCloud *newToxicCloud = new ToxicCloud;
	*newToxicCloud = toxicCloud;
	newToxicCloud->SetPosition(position);
	toxicClouds.push_back(newToxicCloud);
}
void SpawnEnemieExplosion(list<EnemyExplosion*> & enemieExplosions, EnemyExplosion & enemyExplosion, Vector2f position)
{
	EnemyExplosion *newEnemyExplosion = new EnemyExplosion;
	*newEnemyExplosion = enemyExplosion;
	newEnemyExplosion->SetPosition(position);
	enemieExplosions.push_back(newEnemyExplosion);
}

void PlayerShot(Entities & entities, Vector2f mousePos)
{
	Bullet *bullet = new Bullet;					//Создаём пулю
	*bullet = entities.player.GetBullet();			//Присваиваем ей пулю от игрока
	bullet->SetStartPosition(entities.player.GetPosition());
	bullet->SetEnemyPos(mousePos);                  //Позиция цели
	entities.bullets.push_back(bullet);
	bullet->GetSound()->play();
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

					if (tower->canShot)
					{
						Bullet *bullet = new Bullet;
						*bullet = tower->GetBullet();
						bullet->SetEnemyPos(tower->GetEnemyPos());
						entities.bullets.push_back(bullet);
						FloatRect rect;
						rect.left = window.getView().getCenter().x - window.getView().getSize().x / 2;
						rect.top = window.getView().getCenter().y - window.getView().getSize().y / 2;
						rect.height = window.getView().getSize().y;
						rect.width = window.getView().getSize().x;
						if (rect.contains(tower->GetPosition()))
						{
							bullet->GetSound()->play();
						}
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
void EnemiesUpdateAndDraw(Entities & entities, UsedEntities & usedEntities, Coin & coin, RenderWindow & window, float & time)
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
			SpawnBonus(entities.bonuses, usedEntities.bonuses, itPosition);
			SpawnEnemieExplosion(entities.enemyExplosions, usedEntities.enemyExplosion, itPosition);
			if (rand()%100 <= 80)
			{
				SpawnToxicCloud(entities.toxicClouds, usedEntities.toxicCloud, itPosition);
			}

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
void IconsUpdateAndDraw(UsedEntities & usedEntities, Entities & entities, UsedTexts & texts, View & view, RenderWindow & window)
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

	texts.towersPrice.tower1.setPosition(view.getCenter() + Vector2f(-150, 230));
	window.draw(texts.towersPrice.tower1);
	texts.towersPrice.tower2.setPosition(view.getCenter() + Vector2f(-50, 230));
	window.draw(texts.towersPrice.tower2);
	texts.towersPrice.tower3.setPosition(view.getCenter() + Vector2f(50, 230));
	window.draw(texts.towersPrice.tower3);
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
void BonusesUpdateAndDraw(Entities & entities, UsedSounds & sounds, RenderWindow & window, float time)
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
				sounds.dropItem.sound.play();
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
void MeteorsUpdateAndDraw(Entities & entities, UsedEntities & usedEntities, CameraShake & cameraShake, RenderWindow & window, float time)
{
	for (auto itMeteor = entities.meteors.begin(); itMeteor != entities.meteors.end();)
	{
		Meteor *meteor = *itMeteor;
		meteor->Update(time);
		if (meteor->GetArrival())
		{
			SpawnExplosion(entities.explosions, usedEntities.explosion, cameraShake, meteor->GetArrivalPosition(), window);
			for (auto it = entities.enemies.begin(); it != entities.enemies.end();)
			{
				Enemy *enemy = *it;
				if (meteor->GetArrivalArea().intersects(enemy->damageArea.getGlobalBounds()))
				{
					enemy->TakeDamage(meteor->GetDamage());
				}
				it++;
			}
			for (auto it = entities.towers.begin(); it != entities.towers.end();)
			{
				Tower *tower = *it;
				if (meteor->GetArrivalArea().intersects(tower->boundsArea.getGlobalBounds()))
				{
					tower->TakeDamage(meteor->GetDamage());
				}
				it++;
			}
			if (meteor->GetArrivalArea().intersects(entities.player.GetGlobalBounds()))
			{
				entities.player.TakeDamage(meteor->GetDamage());
			}
			itMeteor = entities.meteors.erase(itMeteor);
			delete(meteor);
		}
		else
		{
			meteor->Draw(window);
			++itMeteor;
		}
	}
}
void ExplosionsUpdateAndDraw(list<Explosion*> & explosions, RenderWindow & window, float time)
{
	for (auto it = explosions.begin(); it != explosions.end();)
	{
		Explosion *explosion = *it;
		explosion->Update(time);
		if (explosion->GetIsDestroy())
		{
			it = explosions.erase(it);
			delete(explosion);
		}
		else
		{
			explosion->Draw(window);
			it++;
		}
	}
}
void ToxicCloudUpdateAndDraw(Entities & entities, RenderWindow & window, float & time)
{
	for (auto it = entities.toxicClouds.begin(); it != entities.toxicClouds.end();)
	{
		ToxicCloud *toxicCloud = *it;
		toxicCloud->Update(time);
		if (toxicCloud->GetIsDestroy())
		{
			it = entities.toxicClouds.erase(it);
			delete(toxicCloud);
		}
		else
		{
			if (toxicCloud->GetGlobalBounds().contains(entities.player.GetPosition()))
			{
				entities.player.TakeDamage(toxicCloud->GetDamage() * time/1000.0f);
			}
			toxicCloud->Draw(window);
			++it;
		}
	}
}
void EnemyExplosionUpdateAndDraw(list<EnemyExplosion*> & enemyExplosions, RenderWindow & window, float & time)
{
	for (auto it = enemyExplosions.begin(); it != enemyExplosions.end();)
	{
		EnemyExplosion *enemyExplosion = *it;
		enemyExplosion->Update(time);
		if (enemyExplosion->GetIsDestroy())
		{
			it = enemyExplosions.erase(it);
			delete(enemyExplosion);
		}
		else
		{
			enemyExplosion->Draw(window);
			++it;
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
void InitTowers(UsedTowers & towers, Textures & textures, UsedBullets & bullets)
{
	textures.tower1.loadFromFile(PATH_TO_TEXTURES + "towers/gun_turret.png");
	towers.tower1.SetSpriteMap(textures.tower1, 2, 64);
	towers.tower1.SetMaxHp(300);
	towers.tower1.SetBullet(bullets.gunShot);
	towers.tower1.SetReloadTime(200);
	towers.tower1.SetActionRadius(150);
	towers.tower1.SetPrice(50);

	textures.tower2.loadFromFile(PATH_TO_TEXTURES + "towers/twin_gun_turret.png");
	towers.tower2.SetSpriteMap(textures.tower2, 8, 8);
	towers.tower2.SetMaxHp(200);
	towers.tower2.SetBullet(bullets.twinGunShot);
	towers.tower2.bullet.bulletSprite.setScale(Vector2f(1.1f, 1.1f));
	towers.tower2.SetReloadTime(200);
	towers.tower2.SetActionRadius(200);
	towers.tower2.SetPrice(100);

	textures.tower3.loadFromFile(PATH_TO_TEXTURES + "towers/laser_turret.png");
	towers.tower3.SetSpriteMap(textures.tower3, 8, 8);
	towers.tower3.SetMaxHp(100);
	towers.tower3.SetBullet(bullets.laserShot);
	towers.tower3.bullet.bulletSprite.setScale(Vector2f(1.1f, 1.1f));
	towers.tower3.SetReloadTime(4000);
	towers.tower3.SetActionRadius(300);
	towers.tower3.SetPrice(300);
}
void InitIcons(UsedIcons & icons, UsedTexts & texts, Font & font)
{
	icons.icon1.SetSprite("gun_turret_icon");
	icons.icon2.SetSprite("twin_gun_turret_icon");
	icons.icon3.SetSprite("laser_turret_icon");

	icons.icon1.SetPosition(540, 650);
	icons.icon2.SetPosition(640, 650);
	icons.icon3.SetPosition(740, 650);

	texts.towersPrice.tower1.setString("50");
	texts.towersPrice.tower1.setPosition(500, 650);
	texts.towersPrice.tower1.setFont(font);
	texts.towersPrice.tower1.setCharacterSize(20);
	texts.towersPrice.tower2.setString("100");
	texts.towersPrice.tower2.setPosition(600, 650);
	texts.towersPrice.tower2.setFont(font);
	texts.towersPrice.tower2.setCharacterSize(20);
	texts.towersPrice.tower3.setString("300");
	texts.towersPrice.tower3.setPosition(700, 650);
	texts.towersPrice.tower3.setFont(font);
	texts.towersPrice.tower3.setCharacterSize(20);
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
	enemies.enemy3.SetDamage(15);
	enemies.enemy3.SetCoins(100);
	enemies.enemy3.SetSpeedAttackAnimation(0.01f);
	enemies.enemy3.SetSpeedRunAnimation(0.03f);
	enemies.enemy3.SetScale(1.2f, 1.2f);
}
void InitPlayer(Player & player, Textures & textures, Bullet & bullet, UsedSounds & usedSounds)
{
	textures.player.idle.loadFromFile(PATH_TO_TEXTURES + "player_idle.png");
	textures.player.run.loadFromFile(PATH_TO_TEXTURES + "player_run.png");
	player.SetSpriteMaps(textures.player.idle, 22, 8, textures.player.run, 22, 8);
	player.SetPosition(800, 600);
	player.SetSpeed(0.15f);
	player.SetBullet(bullet);
	player.SetTimeBetweenShots(150.0f);
	player.SetMaxHp(50);
	player.SetSoundSteps(usedSounds.steps.step1, usedSounds.steps.step2, usedSounds.steps.step3, usedSounds.steps.step4, 280, 30);
}
void InitAreasPlacingTower(AreasPlacingTower & areasPlacing)
{
	areasPlacing.placingArea.setRadius(150);
	Color placeAreaColor(0, 100, 200, 60);
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
	bonuses.speedIncrease.SetBonus("speedInc", textures.bonuses.speedIncTex, 0.05f, 8000, 10000);
	bonuses.fireAcceleration.SetBonus("fireAccel", textures.bonuses.fireAccelTex, 50, 8000, 10000);
	bonuses.damageIncrease.SetScale(0.5f, 0.5f);
	bonuses.healthIncrease.SetScale(0.5f, 0.5f);
	bonuses.speedIncrease.SetScale(0.5f, 0.5f);
	bonuses.fireAcceleration.SetScale(0.5f, 0.5f);
}
void InitBullets(UsedBullets & bullets, Textures & textures, UsedSounds & sounds)
{
	textures.bullets.gunShot.loadFromFile(PATH_TO_TEXTURES + "bullets/bullet.png");
	textures.bullets.twinGunShot.loadFromFile(PATH_TO_TEXTURES + "bullets/twin_bullet.png");
	textures.bullets.laserShot.loadFromFile(PATH_TO_TEXTURES + "bullets/laser_bullet.png");
	bullets.gunShot.SetTexture(textures.bullets.gunShot);
	bullets.twinGunShot.SetTexture(textures.bullets.twinGunShot);
	bullets.laserShot.SetTexture(textures.bullets.laserShot);
	bullets.playerGunShot.SetTexture(textures.bullets.gunShot);

	bullets.gunShot.SetDamage(5.0f);
	bullets.gunShot.SetSpeed(0.5f);
	bullets.gunShot.SetSounds(&sounds.gunShots.shot1, &sounds.gunShots.shot2, &sounds.gunShots.shot3);

	bullets.twinGunShot.SetDamage(10.0f);
	bullets.twinGunShot.SetSpeed(0.5f);
	bullets.twinGunShot.SetSounds(&sounds.gunShots.shot1, &sounds.gunShots.shot2, &sounds.gunShots.shot3);

	bullets.laserShot.SetDamage(70.0f);
	bullets.laserShot.SetSpeed(4.0f);
	bullets.laserShot.SetSounds(&sounds.laserShots.shot1, &sounds.laserShots.shot2, &sounds.laserShots.shot3);

	bullets.playerGunShot.SetDamage(5.0f);
	bullets.playerGunShot.SetSpeed(0.5f);
	bullets.playerGunShot.SetSounds(&sounds.playerGunShots.shot1, &sounds.playerGunShots.shot2, &sounds.playerGunShots.shot3);
}
void InitMeteor(Meteor & meteor, Textures & textures, UsedSounds & sounds)
{
	textures.meteor.texture.loadFromFile(PATH_TO_TEXTURES + "meteor/meteor.png");
	textures.meteor.shadow.loadFromFile(PATH_TO_TEXTURES + "meteor/meteor_shadow.png");
	textures.meteor.pointArrival.loadFromFile(PATH_TO_TEXTURES + "meteor/point_arrival.png");
	meteor.SetMeteor(textures.meteor.texture, textures.meteor.shadow, textures.meteor.pointArrival, 20.0f, 0.5f);
}
void InitExplosion(Explosion & explosion, Textures & textures, UsedSounds & sounds)
{
	textures.explosion.loadFromFile(PATH_TO_TEXTURES + "explosion/explosion.png");
	explosion.SetExplosion(textures.explosion, 6, 8, 0.04f);
	explosion.SetSound(&sounds.explosion.sound);
}
void InitCameraShake(CameraShake & cameraShake)
{
	cameraShake.SetOffsetWithShake(10);
}
void InitVignette(Vignette & vignette, Textures & textures)
{
	textures.vignette.loadFromFile(PATH_TO_TEXTURES + "vignette.png");
	vignette.SetTexture(textures.vignette);
}
void InitToxicCloud(ToxicCloud & toxicCloud, Textures & textures)
{
	textures.toxicCloud.loadFromFile(PATH_TO_TEXTURES + "toxic_cloud.png");
	toxicCloud.SetToxicCloud(textures.toxicCloud, 5, 12);
	toxicCloud.SetTimeToDestroy(7000.0f);
	toxicCloud.SetDamage(5.0f);
	toxicCloud.SetSpeedAnimation(0.01f);
}
void InitEnemyExplosion(EnemyExplosion & enemyExplosion, Textures & textures)
{
	textures.enemyExplosion.loadFromFile(PATH_TO_TEXTURES + "enemies/enemy_explosion.png");
	enemyExplosion.SetEnemyExplosion(textures.enemyExplosion, 5, 4);
	enemyExplosion.SetSpeedAnimation(0.02f);
	enemyExplosion.SetTimeToDestroy(20000.0f);
}

void InitMusics(Music & music, Music & winMusic, Music & loseMusic, Music & menuMusic)
{
	music.openFromFile(PATH_TO_MUSIC + "music.ogg");
	music.setLoop(true);
	winMusic.openFromFile(PATH_TO_MUSIC + "win.ogg");
	loseMusic.openFromFile(PATH_TO_MUSIC + "lose.ogg");
	menuMusic.openFromFile(PATH_TO_MUSIC + "menu.ogg");
}
void InitSounds(UsedSounds & sounds)
{
	sounds.gunShots.shot1Buffer.loadFromFile(PATH_TO_SOUNDS + "bullets/gunshot1.ogg");
	sounds.gunShots.shot2Buffer.loadFromFile(PATH_TO_SOUNDS + "bullets/gunshot2.ogg");
	sounds.gunShots.shot3Buffer.loadFromFile(PATH_TO_SOUNDS + "bullets/gunshot3.ogg");
	sounds.gunShots.shot1.setBuffer(sounds.gunShots.shot1Buffer);
	sounds.gunShots.shot2.setBuffer(sounds.gunShots.shot2Buffer);
	sounds.gunShots.shot3.setBuffer(sounds.gunShots.shot3Buffer);
	sounds.gunShots.shot1.setVolume(25);
	sounds.gunShots.shot2.setVolume(25);
	sounds.gunShots.shot3.setVolume(25);
	sounds.playerGunShots.shot1.setBuffer(sounds.gunShots.shot1Buffer);
	sounds.playerGunShots.shot2.setBuffer(sounds.gunShots.shot2Buffer);
	sounds.playerGunShots.shot3.setBuffer(sounds.gunShots.shot3Buffer);
	sounds.playerGunShots.shot1.setVolume(60);
	sounds.playerGunShots.shot2.setVolume(60);
	sounds.playerGunShots.shot3.setVolume(60);
	sounds.laserShots.shot1Buffer.loadFromFile(PATH_TO_SOUNDS + "bullets/laser1.ogg");
	sounds.laserShots.shot1Buffer.loadFromFile(PATH_TO_SOUNDS + "bullets/laser2.ogg");
	sounds.laserShots.shot1Buffer.loadFromFile(PATH_TO_SOUNDS + "bullets/laser3.ogg");
	sounds.laserShots.shot1.setBuffer(sounds.laserShots.shot1Buffer);
	sounds.laserShots.shot2.setBuffer(sounds.laserShots.shot2Buffer);
	sounds.laserShots.shot3.setBuffer(sounds.laserShots.shot3Buffer);
	sounds.steps.step1.loadFromFile(PATH_TO_SOUNDS + "walking/walk1.ogg");
	sounds.steps.step2.loadFromFile(PATH_TO_SOUNDS + "walking/walk2.ogg");
	sounds.steps.step3.loadFromFile(PATH_TO_SOUNDS + "walking/walk3.ogg");
	sounds.steps.step4.loadFromFile(PATH_TO_SOUNDS + "walking/walk4.ogg");

	sounds.placeTower.soundBuf.loadFromFile(PATH_TO_SOUNDS + "place_tower/place.ogg");
	sounds.placeTower.sound.setBuffer(sounds.placeTower.soundBuf);
	sounds.dropItem.soundBuf.loadFromFile(PATH_TO_SOUNDS + "drop_item.wav");
	sounds.dropItem.sound.setBuffer(sounds.dropItem.soundBuf);

	sounds.meteorFall.soundBuf.loadFromFile(PATH_TO_SOUNDS + "meteor_fall.ogg");
	sounds.meteorFall.sound.setBuffer(sounds.meteorFall.soundBuf);
	sounds.meteorFall.sound.setVolume(50);

	sounds.evilLaugh.soundBuf.loadFromFile(PATH_TO_SOUNDS + "evil_laugh.ogg");
	sounds.evilLaugh.sound.setBuffer(sounds.evilLaugh.soundBuf);

	sounds.explosion.soundBuf.loadFromFile(PATH_TO_SOUNDS + "explosion.ogg");
	sounds.explosion.sound.setBuffer(sounds.explosion.soundBuf);
	sounds.explosion.sound.setVolume(150);

	sounds.heartbeat.soundBuf.loadFromFile(PATH_TO_SOUNDS + "heartbeat.ogg");
	sounds.heartbeat.sound.setBuffer(sounds.heartbeat.soundBuf);
	sounds.heartbeat.sound.setVolume(400);
	sounds.heartbeat.sound.setLoop(true);
}

int main()
{
	RenderWindow window(VideoMode(1600, 900), "Game???", Style::Default);
	View view;
	view.reset(FloatRect(0, 0, 1280, 720));

	Music menuMusic;
	Music bgMusic;
	Music loseMusic;
	Music winMusic;
	UsedSounds usedSounds;
	UsedTexts usedTexts;

	Font font;
	font.loadFromFile(PATH_TO_FONTS + "font1.ttf");
	Text playerMoneyText("", font, 20);
	playerMoneyText.setStyle(Text::Bold);

	UsedEntities usedEntities;
	Textures textures;
	Entities entities;

	AreasPlacingTower areasPlacingTower;

	Coin coin;
	CameraShake cameraShake;
	Vignette vignette;
	
	InitBullets(usedEntities.bullets, textures, usedSounds);
	InitPlayer(entities.player, textures, usedEntities.bullets.playerGunShot, usedSounds);
	InitTowers(usedEntities.towers, textures, usedEntities.bullets);
	InitIcons(usedEntities.icons, usedTexts, font);
	InitEnemies(usedEntities.enemies, textures);
	InitCursors(usedEntities.cursors);
	InitAreasPlacingTower(areasPlacingTower);
	InitPortal(entities.portal, textures);
	InitObstacles(entities.obstacles);
	InitBonuses(usedEntities.bonuses, textures);
	InitCoin(coin, textures, font);
	InitMeteor(usedEntities.meteor, textures, usedSounds);
	InitExplosion(usedEntities.explosion, textures, usedSounds);
	InitCameraShake(cameraShake);
	InitToxicCloud(usedEntities.toxicCloud, textures);
	InitEnemyExplosion(usedEntities.enemyExplosion, textures);

	InitChangeHpView(usedEntities.changeHpView, font);

	InitMusics(bgMusic, winMusic, loseMusic, menuMusic);
	InitSounds(usedSounds);

	Tower *placingTower = new Tower;

	bool intersectAtPlacing = false;
	bool towerInstallation = false;
	bool drawActionArea = false;
	bool isShakeCamera = false;

	Sprite mapSprite;
	InitMap(mapSprite, textures);
	InitVignette(vignette, textures);

	vector<int> mapUsedEnemies = {1,1,2,2,1,3,3,1,1,1,1,1,1,1,1,2,3,2,1,2,3,2,1,2,2,2,1,2,3,3,
								  3,2,1,2,2,3,3,2,2,2,2,3,3,2,2,2,2,1,2,2,2,1,1,1,1,1,1,1,1,1,
								  1,2,2,2,2,2,2,3,3,3,3,3,3,2,2,2,2,1,3,1,1,1,1,1,1,1,1,1,1,3,
								  1,1,3,3,3,3,1,1,1,3,3,3,2,2,2,3,2,1,1,1,2,3,2,3,3,3,2,2,3,3,
								  2,2,2,2,1,1,1,2,2,2,2,3,3,3,3,2,2,1,1,1,1,1,2,3,3,3,3,3,3,3};

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
	window.setFramerateLimit(150);
	Clock clock;
	FPS fps;

	state gameState = state::menu;

	while (window.isOpen())
	{
		float time = (float)clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 1000;
		//fps.printFPS(time);

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
				if (gameState == state::game)
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
		}

		if (gameState == state::game)
		{
			if (bgMusic.getStatus() == SoundStream::Stopped) 
			{
				bgMusic.play();
			}

			timerEnemySpawn -= time;

			if (timerEnemySpawn <= 0)
			{
				if (difLevel >= 0 && difLevel < 5) timerEnemySpawn = 4000;
				else if (difLevel >= 5 && difLevel < 10) timerEnemySpawn = 3000;
				else if (difLevel >= 10 && difLevel < 15) timerEnemySpawn = 2000;
				else if (difLevel >= 15 && difLevel < 30) timerEnemySpawn = 1500;
				else if (difLevel >= 30) timerEnemySpawn = 500;

				if (iterEnemy != enemiesInLevel.end())
				{
					entities.enemies.push_back(*iterEnemy);
					iterEnemy++;
				}
				else
				{
					if (entities.enemies.size() == 0)
					{
						gameState = state::win;
						bgMusic.stop();
						winMusic.play();
					}
				}
				difLevel++;
			}
			intersectAtPlacing = false;

			if (rand()%1000 <= 4)
			{
				Meteor* newMeteor = new Meteor;
				*newMeteor = usedEntities.meteor;
				newMeteor->SetArrivalPosition(float(rand() % 2000), float(rand() % 2000));
				entities.meteors.push_back(newMeteor);
			}

			if (rand()%10000 == 0)
			{
				usedSounds.evilLaugh.sound.play();
			}

			window.clear(Color::White);

			window.draw(mapSprite);

			EnemyExplosionUpdateAndDraw(entities.enemyExplosions, window, time);
			PortalUpdateAndDraw(entities, window, time);
			MeteorsUpdateAndDraw(entities, usedEntities, cameraShake, window, time);
			ToxicCloudUpdateAndDraw(entities, window, time);
			ExplosionsUpdateAndDraw(entities.explosions, window, time);
			BonusesUpdateAndDraw(entities, usedSounds, window, time);
			TowerUpdateAndDraw(entities, placingTower, towerInstallation, intersectAtPlacing, drawActionArea, time, window);
			BulletUpdateAndDraw(entities, usedEntities, window, time);
			EnemiesUpdateAndDraw(entities, usedEntities, coin, window, time);
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
						usedSounds.placeTower.sound.play();
					}
				}
				else
				{
					placingTower->spriteMap.sprite.setColor(Color::Red);
				}
				placingTower->Update();
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
				if (cameraShake.GetShake()) cameraShake.Update(view, Vector2f(tempX, tempY), time);
				else view.setCenter(tempX, tempY);
			}
			else
			{
				if (cameraShake.GetShake()) cameraShake.Update(view, entities.player.GetPosition(), time);
				else view.setCenter(entities.player.GetPosition());
			}
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

			IconsUpdateAndDraw(usedEntities, entities, usedTexts, view, window);

			ostringstream playerMoneyString;
			playerMoneyString << entities.player.GetMoney();
			playerMoneyText.setString("Money: " + playerMoneyString.str());
			playerMoneyText.setPosition(view.getCenter() + Vector2f(-540, 260));
			window.draw(playerMoneyText);
			if (entities.player.GetCurrentHp() < entities.player.GetMaxHp() * 0.2f)
			{
				if (bgMusic.getVolume() != 30) bgMusic.setVolume(30);
				if (entities.player.GetBullet().GetVolumeSounds() != 20) entities.player.GetBullet().SetVolumeSounds(20);
				if (usedSounds.heartbeat.sound.getStatus() != SoundSource::Playing)
				{
					usedSounds.heartbeat.sound.play();
				}
				vignette.Draw(window);
			}
			else
			{
				if (bgMusic.getVolume() != 100) bgMusic.setVolume(100);
				if (entities.player.GetBullet().GetVolumeSounds() != 60) entities.player.GetBullet().SetVolumeSounds(60);
				if (usedSounds.heartbeat.sound.getStatus() != SoundSource::Stopped)
				{
					usedSounds.heartbeat.sound.stop();
				}
			}
			if (entities.player.GetCurrentHp() < 0) { gameState = state::lose; bgMusic.stop(); loseMusic.play(); };
		}
		if (gameState == state::win)
		{
			Win(winMusic, gameState, view, window);
			clock.restart();
		}
		if (gameState == state::lose)
		{
			usedSounds.heartbeat.sound.stop();
			Lose(loseMusic, gameState, view, window);
			clock.restart();
		}
		if (gameState == state::menu)
		{
			Menu(menuMusic, gameState, view, window, time);
			clock.restart();
		}

		window.display();
	}

	return 0;
}