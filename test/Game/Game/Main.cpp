#include "Header.h"
#include "LoadRecources.h"
#include "Structures.h"
#include "InitializationEntities.h"
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
#include "CameraShake.h"
#include "Menu.h"
#include "Lose.h"
#include "Win.h"

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;

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
void EnemiesUpdateAndDraw(Entities & entities, UsedEntities & usedEntities, Coin & coin, RenderWindow & window, const float time)
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
void BulletUpdateAndDraw(Entities & entities, UsedEntities & usedEntities, RenderWindow & window, const float time)
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
				bullet->SetIsDestroy(true);
				SpawnChangeHpView(entities.changeHpViews, usedEntities.changeHpView, damage, bulletPosition);
				break;
			}
			enemy++;
		}
		if (bullet->GetIsDestroy())
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
void CoinsUpdateAndDraw(list<Coin*> & coins, RenderWindow & window, const float time)
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
void PortalUpdateAndDraw(Entities & entities, RenderWindow & window, const float time)
{
	entities.portal.Update(time);
	entities.portal.Draw(window);
}
void PlayerUpdateAndDraw(Player & player, RenderWindow & window, const float time)
{
	player.Update(time);
	player.Draw(window);
}
void BonusesUpdateAndDraw(Entities & entities, UsedSounds & sounds, RenderWindow & window, const float time)
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
void ChangeHpViewsUpdateAndDraw(Entities & entities, RenderWindow & window, const float time)
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
void MeteorsUpdateAndDraw(Entities & entities, UsedEntities & usedEntities, CameraShake & cameraShake, RenderWindow & window, const float time)
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
void ExplosionsUpdateAndDraw(list<Explosion*> & explosions, RenderWindow & window, const float time)
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
void ToxicCloudUpdateAndDraw(Entities & entities, RenderWindow & window, const float time)
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
void EnemyExplosionUpdateAndDraw(list<EnemyExplosion*> & enemyExplosions, RenderWindow & window, const float time)
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

void InitMusics(UsedMusics & usedMusics)
{
	usedMusics.game.openFromFile(PATH_TO_MUSIC + "music.ogg");
	usedMusics.game.setLoop(true);
	usedMusics.win.openFromFile(PATH_TO_MUSIC + "win.ogg");
	usedMusics.lose.openFromFile(PATH_TO_MUSIC + "lose.ogg");
	usedMusics.menu.openFromFile(PATH_TO_MUSIC + "menu.ogg");
}

void InitSounds(UsedSounds & sounds)
{
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
	sounds.laserShots.shot1.setBuffer(sounds.laserShots.shot1Buffer);
	sounds.laserShots.shot2.setBuffer(sounds.laserShots.shot2Buffer);
	sounds.laserShots.shot3.setBuffer(sounds.laserShots.shot3Buffer);

	sounds.placeTower.sound.setBuffer(sounds.placeTower.soundBuf);
	sounds.dropItem.sound.setBuffer(sounds.dropItem.soundBuf);

	sounds.evilLaugh.sound.setBuffer(sounds.evilLaugh.soundBuf);

	sounds.explosion.sound.setBuffer(sounds.explosion.soundBuf);
	sounds.explosion.sound.setVolume(150);

	sounds.heartbeat.sound.setBuffer(sounds.heartbeat.soundBuf);
	sounds.heartbeat.sound.setVolume(400);
	sounds.heartbeat.sound.setLoop(true);
}

int main()
{
	RenderWindow window(VideoMode(1600, 900), "Game???", Style::Default);
	View view;
	view.reset(FloatRect(0, 0, 1280, 720));

	Textures textures;
	UsedSounds usedSounds;
	UsedMusics usedMusics;
	UsedTexts usedTexts;
	UsedEntities usedEntities;

	Entities entities;

	Font font;
	font.loadFromFile(PATH_TO_FONTS + "font.ttf");
	Text playerMoneyText("", font, 20);
	playerMoneyText.setStyle(Text::Bold);
	
	if (!LoadTextures(textures) || !LoadSounds(usedSounds))
	{
		return EXIT_FAILURE;
	}
	InitMusics(usedMusics);
	InitSounds(usedSounds);

	InitEntity(usedEntities, entities, textures, usedSounds, usedTexts, font);

	Tower *placingTower = new Tower;

	bool drawActionArea = false;
	bool isShakeCamera = false;

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
							if (!entities.towerInstalling.towerInstallation) placingTower = new Tower;
							*placingTower = usedEntities.towers.tower1;
							entities.towerInstalling.towerInstallation = true;
						}
						if (event.key.code == Keyboard::Num2 && entities.player.GetMoney() >= usedEntities.towers.tower2.GetPrice())
						{
							if (!entities.towerInstalling.towerInstallation) placingTower = new Tower;
							*placingTower = usedEntities.towers.tower2;
							entities.towerInstalling.towerInstallation = true;
						}
						if (event.key.code == Keyboard::Num3 && entities.player.GetMoney() >= usedEntities.towers.tower3.GetPrice())
						{
							if (!entities.towerInstalling.towerInstallation) placingTower = new Tower;
							*placingTower = usedEntities.towers.tower3;
							entities.towerInstalling.towerInstallation = true;
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
			if (usedMusics.game.getStatus() == SoundStream::Stopped) 
			{
				usedMusics.game.play();
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
						usedMusics.game.stop();
					}
				}
				difLevel++;
			}
			entities.towerInstalling.intersectAtPlacing = false;

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

			window.draw(usedEntities.mapSprite);

			EnemyExplosionUpdateAndDraw(entities.enemyExplosions, window, time);
			PortalUpdateAndDraw(entities, window, time);
			MeteorsUpdateAndDraw(entities, usedEntities, usedEntities.cameraShake, window, time);
			ToxicCloudUpdateAndDraw(entities, window, time);
			ExplosionsUpdateAndDraw(entities.explosions, window, time);
			BonusesUpdateAndDraw(entities, usedSounds, window, time);
			TowerUpdateAndDraw(entities, placingTower, entities.towerInstalling.towerInstallation, entities.towerInstalling.intersectAtPlacing, drawActionArea, time, window);
			BulletUpdateAndDraw(entities, usedEntities, window, time);
			EnemiesUpdateAndDraw(entities, usedEntities, usedEntities.coin, window, time);
			ChangeHpViewsUpdateAndDraw(entities, window, time);

			if (Mouse::isButtonPressed(Mouse::Left) && !entities.towerInstalling.towerInstallation && entities.player.canShot)
			{
				PlayerShot(entities, mousePos);
			}

			//Установка башни
			if (entities.towerInstalling.towerInstallation)
			{
				placingTower->SetPosition(mousePos);
				if (entities.towerInstalling.placingArea.getGlobalBounds().contains(mousePos) && !entities.towerInstalling.notPlacingArea.getGlobalBounds().contains(mousePos) && !entities.towerInstalling.intersectAtPlacing)
				{
					placingTower->spriteMap.sprite.setColor(Color::Green);
					window.draw(placingTower->actionArea);
					if (Mouse::isButtonPressed(Mouse::Left))
					{
						entities.towerInstalling.towerInstallation = false;
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
				entities.towerInstalling.placingArea.setPosition(entities.player.GetPosition());
				entities.towerInstalling.notPlacingArea.setPosition(entities.player.GetPosition());
				window.draw(entities.towerInstalling.placingArea);
				window.draw(entities.towerInstalling.notPlacingArea);
				window.draw(placingTower->spriteMap.sprite);
			}

			CheckObstacles(entities.obstacles, entities.player);
			PlayerUpdateAndDraw(entities.player, window, time);
			CoinsUpdateAndDraw(entities.coins, window, time);

			if (entities.player.GetPosition().x < 640 || entities.player.GetPosition().x > 1472 || 
				entities.player.GetPosition().y < 360 || entities.player.GetPosition().y > 1752)
			{
				float tempX = entities.player.GetPosition().x;
				float tempY = entities.player.GetPosition().y;
				if (entities.player.GetPosition().x < 640) tempX = 640;
				if (entities.player.GetPosition().x > 1472) tempX = 1472;
				if (entities.player.GetPosition().y < 360) tempY = 360;
				if (entities.player.GetPosition().y > 1752) tempY = 1752;
				if (usedEntities.cameraShake.GetShake()) usedEntities.cameraShake.Update(view, Vector2f(tempX, tempY), time);
				else view.setCenter(tempX, tempY);
			}
			else
			{
				if (usedEntities.cameraShake.GetShake()) usedEntities.cameraShake.Update(view, entities.player.GetPosition(), time);
				else view.setCenter(entities.player.GetPosition());
			}
			window.setView(view);

			if (entities.towerInstalling.towerInstallation)
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
				if (usedMusics.game.getVolume() != 80) usedMusics.game.setVolume(80);
				if (entities.player.GetBullet().GetVolumeSounds() != 20) entities.player.GetBullet().SetVolumeSounds(20);
				if (usedSounds.heartbeat.sound.getStatus() != SoundSource::Playing)
				{
					usedSounds.heartbeat.sound.play();
				}
				usedEntities.vignette.Draw(window);
			}
			else
			{
				if (usedMusics.game.getVolume() != 100) usedMusics.game.setVolume(100);
				if (entities.player.GetBullet().GetVolumeSounds() != 60) entities.player.GetBullet().SetVolumeSounds(60);
				if (usedSounds.heartbeat.sound.getStatus() != SoundSource::Stopped)
				{
					usedSounds.heartbeat.sound.stop();
				}
			}
			if (entities.player.GetCurrentHp() < 0) { gameState = state::lose; usedMusics.game.stop(); usedMusics.lose.play(); };
		}
		if (gameState == state::win)
		{
			Win(usedMusics.win, gameState, view, window);
			clock.restart();
		}
		if (gameState == state::lose)
		{
			usedSounds.heartbeat.sound.stop();
			Lose(usedMusics.lose, gameState, view, window);
			clock.restart();
		}
		if (gameState == state::menu)
		{
			Menu(usedMusics.menu, gameState, view, window, time);
			clock.restart();
		}

		window.display();
	}

	return 0;
}