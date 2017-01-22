#include "Header.h"
#include "LoadResources.h"
#include "Structures.h"
#include "Initialization.h"
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

using namespace sf;
using namespace std;

static const int SCREEN_WIDTH = 1600;
static const int SCREEN_HEIGHT = 900;
static const float VIEW_WIDTH = 1280.0f;
static const float VIEW_HEIGHT = 720.0f;
static const float MAP_SIZE = 2112.0f;
static const int CHANCE_DROP_BONUS = 20;
static const int CHANCE_SPAWN_TOXIC_CLOUD = 80;
static const int CHANCE_LAUGH_IN_SECONDS = 1;

Vector2f GetMousePosition(RenderWindow & window)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	return window.mapPixelToCoords(pixelPos);
}
void TowerInstall(Entities & entities, UsedSounds & usedSounds, const Vector2f mousePos, RenderWindow & window)
{
	if (entities.towerInstalling.towerInstallation)
	{
		entities.placingTower->SetPosition(mousePos);
		if (entities.towerInstalling.placingArea.getGlobalBounds().contains(mousePos) && !entities.towerInstalling.notPlacingArea.getGlobalBounds().contains(mousePos) && !entities.towerInstalling.intersectAtPlacing)
		{
			entities.placingTower->spriteMap.sprite.setColor(Color::Green);
			window.draw(entities.placingTower->actionArea);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				entities.towerInstalling.towerInstallation = false;
				entities.placingTower->isActive = true;
				entities.placingTower->spriteMap.sprite.setColor(Color::White);
				entities.towers.push_back(entities.placingTower);
				entities.player.SubCoins(entities.placingTower->GetPrice());
				entities.player.canShot = false;
				usedSounds.placeTower.sound.play();
			}
		}
		else
		{
			entities.placingTower->spriteMap.sprite.setColor(Color::Red);
		}
		entities.placingTower->Update();
		entities.towerInstalling.placingArea.setPosition(entities.player.GetPosition());
		entities.towerInstalling.notPlacingArea.setPosition(entities.player.GetPosition());
		window.draw(entities.towerInstalling.placingArea);
		window.draw(entities.towerInstalling.notPlacingArea);
		window.draw(entities.placingTower->spriteMap.sprite);
	}
}
void PlayerTracking(Player & player, CameraShake & cameraShake, const float mapSize, View & view, const float time)
{
	if (player.GetPosition().x < view.getSize().x / 2 || player.GetPosition().x > mapSize - view.getSize().x / 2 ||
		player.GetPosition().y < view.getSize().y / 2 || player.GetPosition().y > mapSize - view.getSize().y / 2)
	{
		float tempX = player.GetPosition().x;
		float tempY = player.GetPosition().y;
		if (player.GetPosition().x < view.getSize().x / 2)
			tempX = view.getSize().x / 2;
		if (player.GetPosition().x > mapSize - view.getSize().x / 2)
			tempX = mapSize - view.getSize().x / 2;
		if (player.GetPosition().y < view.getSize().y / 2)
			tempY = view.getSize().y / 2;
		if (player.GetPosition().y > mapSize - view.getSize().y / 2)
			tempY = mapSize - view.getSize().y / 2;

		if (cameraShake.GetShake())
			cameraShake.Update(view, Vector2f(tempX, tempY), time);
		else view.setCenter(tempX, tempY);
	}
	else
	{
		if (cameraShake.GetShake()) cameraShake.Update(view, player.GetPosition(), time);
		else view.setCenter(player.GetPosition());
	}
}

void SpawnEnemy(EnemySpawner & enemySpawn, list<Enemy*> & enemies)
{
	enemies.push_back(*enemySpawn.iterEnemy);
	enemySpawn.iterEnemy++;
	enemySpawn.numberEnemy++;
}
void SpawnCoin(list<Coin*> & coins, Coin & coin, const int value, Vector2f position)
{
	Coin *newCoin = new Coin;
	*newCoin = coin;
	newCoin->SetPosition(position);
	newCoin->SetValue(value);
	coins.push_back(newCoin);
}
void SpawnBonus(list<Bonus*> & bonuses, UsedBonuses & usedBonuses, Vector2f position)
{
	if (rand() % 100 <= CHANCE_DROP_BONUS)
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
	FloatRect rect(window.getView().getCenter().x - window.getView().getSize().x / 2, 
				   window.getView().getCenter().y - window.getView().getSize().y / 2,
				   window.getView().getSize().x, window.getView().getSize().y);
	if (rect.contains(position))
	{
		newExplosion->GetSound()->play();
		cameraShake.SetShake(true);
	}	
	explosions.push_back(newExplosion);
}
void SpawnExplosion(list<Explosion*> & explosions, Explosion & explosion, Vector2f position)
{
	Explosion *newExplosion = new Explosion;
	*newExplosion = explosion;
	newExplosion->SetPosition(position);
	explosions.push_back(newExplosion);
}
void SpawnToxicCloud(list<ToxicCloud*> & toxicClouds, ToxicCloud & toxicCloud, Vector2f position)
{
	ToxicCloud *newToxicCloud = new ToxicCloud;
	*newToxicCloud = toxicCloud;
	newToxicCloud->SetPosition(position);
	toxicClouds.push_back(newToxicCloud);
}
void SpawnEnemieExplosion(list<EnemyRemnants*> & enemieExplosions, EnemyRemnants & enemyExplosion, Vector2f position)
{
	EnemyRemnants *newEnemyExplosion = new EnemyRemnants;
	*newEnemyExplosion = enemyExplosion;
	newEnemyExplosion->SetPosition(position);
	newEnemyExplosion->SetRandomRotate();
	enemieExplosions.push_back(newEnemyExplosion);
}
void SpawnMeteor(Meteor & meteor, list<Meteor*> & meteors)
{
	Meteor* newMeteor = new Meteor;
	*newMeteor = meteor;
	newMeteor->SetArrivalPosition(float(rand() % (int)MAP_SIZE), float(rand() % (int)MAP_SIZE));
	meteors.push_back(newMeteor);
}
void SpawnBullet(list<Bullet*> & bullets, Tower *tower, RenderWindow & window)
{
	Bullet *bullet = new Bullet;
	*bullet = tower->GetBullet();
	bullet->SetEnemyPos(tower->GetEnemyPos());
	bullets.push_back(bullet);
	FloatRect rect(window.getView().getCenter().x - window.getView().getSize().x / 2,
		window.getView().getCenter().y - window.getView().getSize().y / 2,
		window.getView().getSize().x, window.getView().getSize().y);
	if (rect.contains(tower->GetPosition()))
	{
		bullet->GetSound().play();
	}
}

void PlayerShot(Entities & entities, Vector2f mousePos)
{
	Bullet *bullet = new Bullet;					//Создаём пулю
	*bullet = entities.player.GetBullet();			//Присваиваем ей пулю от игрока
	bullet->SetStartPosition(entities.player.GetPosition());
	bullet->SetEnemyPos(mousePos);                  //Позиция цели
	entities.bullets.push_back(bullet);
	bullet->GetSound().play();
	entities.player.canShot = false;
}
void CheckObstacles(Obstacles & obstacles, Player & player)
{
	if (obstacles.topObstacle.getGlobalBounds().contains(player.GetPosition()))
	{
		Vector2f VectorThrowing(0, 1);
		player.SetPosition(player.GetPosition() + VectorThrowing);
	}
	if (obstacles.downObstacle.getGlobalBounds().contains(player.GetPosition()))
	{
		Vector2f VectorThrowing(0, -1);
		player.SetPosition(player.GetPosition() + VectorThrowing);
	}
	if (obstacles.leftObstacle.getGlobalBounds().contains(player.GetPosition()))
	{
		Vector2f VectorThrowing(1, 0);
		player.SetPosition(player.GetPosition() + VectorThrowing);
	}
	if (obstacles.rightObstacle.getGlobalBounds().contains(player.GetPosition()))
	{
		Vector2f VectorThrowing(-1, 0);
		player.SetPosition(player.GetPosition() + VectorThrowing);
	}
}
void CheckPlayerHp(Player & player, Vignette & vignette, UsedSounds & usedSounds, UsedMusics & usedMusics, RenderWindow & window)
{
	if (player.GetCurrentHp() < player.GetMaxHp() * 0.2f)
	{
		if (usedMusics.game.getVolume() != 80) usedMusics.game.setVolume(80);
		if (player.GetBullet().GetVolumeSounds() != 20) player.GetBullet().SetVolumeSounds(20);
		if (usedSounds.heartbeat.sound.getStatus() != SoundSource::Playing)
		{
			usedSounds.heartbeat.sound.play();
		}
		vignette.Draw(window);
	}
	else
	{
		if (usedMusics.game.getVolume() != 100) usedMusics.game.setVolume(100);
		if (player.GetBullet().GetVolumeSounds() != 60) player.GetBullet().SetVolumeSounds(60);
		if (usedSounds.heartbeat.sound.getStatus() != SoundSource::Stopped)
		{
			usedSounds.heartbeat.sound.stop();
		}
	}
}

void TowerUpdateAndDraw(Entities & entities, UsedEntities & usedEntities, const float time, RenderWindow & window)
{
	entities.towerInstalling.intersectAtPlacing = false;
	for (auto it = entities.towers.begin(); it != entities.towers.end();)
	{
		Tower *tower = *it;
		if (tower->isDestroy)
		{
			SpawnExplosion(entities.explosions, usedEntities.towerExplosion, tower->GetPosition());
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
						SpawnBullet(entities.bullets, tower, window);
						tower->canShot = false;
					}
				}
			}

			//Препятствие для игрока
			if (tower->spriteMap.sprite.getGlobalBounds().intersects(entities.player.GetGlobalBounds()))
			{
				FloatRect towerBounds = tower->spriteMap.sprite.getGlobalBounds();
				if (towerBounds.contains(entities.player.GetPosition()))
				{
					Vector2f VectorBetween = tower->GetPosition() - entities.player.GetPosition();
					Vector2f VectorThrowing = GetUnitVector(VectorBetween);
					entities.player.SetPosition(entities.player.GetPosition() - VectorThrowing);
				}
			}

			//Если ставим новую башню...
			if (entities.towerInstalling.towerInstallation)
			{
				//Не даём поставить новую башню на место установленной
				if (tower->boundsArea.getGlobalBounds().contains(entities.placingTower->GetPosition()))
				{
					entities.towerInstalling.intersectAtPlacing = true;
				}
				window.draw(tower->boundsArea);
				window.draw(tower->actionArea);
			}
			tower->Draw(window);
			it++;
		}
	}
}
void EnemiesUpdateAndDraw(Entities & entities, UsedEntities & usedEntities, RenderWindow & window, const float time)
{
	for (auto itEnemy = entities.enemies.begin(); itEnemy != entities.enemies.end();)
	{
		Enemy *enemy = *itEnemy;
		Vector2f itPosition = enemy->GetPosition();
		if (enemy->isDestroy)
		{
			entities.player.AddCoins(enemy->GetCoins());
			SpawnCoin(entities.coins, usedEntities.coin, enemy->GetCoins(), itPosition);
			SpawnBonus(entities.bonuses, usedEntities.bonuses, itPosition);
			SpawnEnemieExplosion(entities.enemyExplosions, usedEntities.enemyExplosion, itPosition);
			if (rand()%100 <= CHANCE_SPAWN_TOXIC_CLOUD)
			{
				SpawnToxicCloud(entities.toxicClouds, usedEntities.toxicCloud, itPosition);
			}

			itEnemy = entities.enemies.erase(itEnemy);
			delete(enemy);
		}
		else
		{
			float minDistance = 5000.0f;
			if (!entities.towers.empty())
			{
				//Находим близжайшую башню
				Tower *nearTower = *entities.towers.begin();
				minDistance = CalculateDistance(itPosition, nearTower->GetPosition());
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
void MeteorsUpdateAndDraw(Entities & entities, UsedEntities & usedEntities, RenderWindow & window, const float time)
{
	for (auto itMeteor = entities.meteors.begin(); itMeteor != entities.meteors.end();)
	{
		Meteor *meteor = *itMeteor;
		meteor->Update(time);
		meteor->Draw(window);
		if (meteor->GetArrival())
		{
			SpawnExplosion(entities.explosions, usedEntities.explosion, usedEntities.cameraShake, meteor->GetArrivalPosition(), window);
			for (auto itEnemy = entities.enemies.begin(); itEnemy != entities.enemies.end();)
			{
				Enemy *enemy = *itEnemy;
				if (meteor->GetArrivalArea().contains(enemy->GetPosition()))
				{
					enemy->TakeDamage(meteor->GetDamage());
				}
				++itEnemy;
			}
			for (auto itTower = entities.towers.begin(); itTower != entities.towers.end();)
			{
				Tower *tower = *itTower;
				if (meteor->GetArrivalArea().contains(tower->GetPosition()))
				{
					tower->TakeDamage(meteor->GetDamage());
				}
				++itTower;
			}
			if (meteor->GetArrivalArea().contains(entities.player.GetPosition()))
			{
				entities.player.TakeDamage(meteor->GetDamage());
			}
			itMeteor = entities.meteors.erase(itMeteor);
			delete(meteor);
		}
		else ++itMeteor;
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
	float damage = 0;
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
				if (damage == 0)
				{
					damage = toxicCloud->GetDamage() * time / 1000.0f;
					entities.player.TakeDamage(damage);
				}
			}
			toxicCloud->Draw(window);
			++it;
		}
	}
}
void EnemyExplosionUpdateAndDraw(list<EnemyRemnants*> & enemyExplosions, RenderWindow & window, const float time)
{
	for (auto it = enemyExplosions.begin(); it != enemyExplosions.end();)
	{
		EnemyRemnants *enemyExplosion = *it;
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
void CursorUpdateAndDraw(UsedCursors & cursors, TowerInstalling & towerInstalling, const Vector2f mousePos, RenderWindow & window)
{
	if (towerInstalling.towerInstallation)
	{
		cursors.handCursor.setPosition(mousePos);
		window.draw(cursors.handCursor);
	}
	else
	{
		cursors.aimCursor.setPosition(mousePos);
		window.draw(cursors.aimCursor);
	}
}
void PlayerMoneyTextDraw(Player & player, Text & playerMoneyText, View & view, RenderWindow & window)
{
	ostringstream playerMoneyString;
	playerMoneyString << player.GetMoney();
	playerMoneyText.setString("Money: " + playerMoneyString.str());
	playerMoneyText.setPosition(view.getCenter() + Vector2f(-540, 260));
	window.draw(playerMoneyText);
}

void UpdateAndDraw(Entities & entities, UsedEntities & usedEntities, UsedSounds & usedSounds, UsedTexts & usedTexts, View & view, RenderWindow & window, const float time)
{
	window.draw(usedEntities.mapSprite);
	EnemyExplosionUpdateAndDraw(entities.enemyExplosions, window, time);
	PortalUpdateAndDraw(entities, window, time);
	ToxicCloudUpdateAndDraw(entities, window, time);
	BonusesUpdateAndDraw(entities, usedSounds, window, time);
	TowerUpdateAndDraw(entities, usedEntities, time, window);
	BulletUpdateAndDraw(entities, usedEntities, window, time);
	EnemiesUpdateAndDraw(entities, usedEntities, window, time);
	CoinsUpdateAndDraw(entities.coins, window, time);
	PlayerUpdateAndDraw(entities.player, window, time);
	ExplosionsUpdateAndDraw(entities.explosions, window, time);
	MeteorsUpdateAndDraw(entities, usedEntities, window, time);
	ChangeHpViewsUpdateAndDraw(entities, window, time);
	TowerInstall(entities, usedSounds, GetMousePosition(window), window);
	if (Mouse::isButtonPressed(Mouse::Left) && !entities.towerInstalling.towerInstallation && entities.player.canShot)
	{
		PlayerShot(entities, GetMousePosition(window));
	}
	CheckObstacles(entities.obstacles, entities.player);
	PlayerTracking(entities.player, usedEntities.cameraShake, MAP_SIZE, view, time);
	window.setView(view);
	CursorUpdateAndDraw(usedEntities.cursors, entities.towerInstalling, GetMousePosition(window), window);
	IconsUpdateAndDraw(usedEntities, entities, usedTexts, view, window);
	PlayerMoneyTextDraw(entities.player, usedTexts.playerMoneyText, view, window);
}

void EventUpdate(Event & event, RenderWindow & window, state & gameState, Entities & entities, UsedEntities & usedEntities)
{
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
						if (!entities.towerInstalling.towerInstallation) entities.placingTower = new Tower;
						*entities.placingTower = usedEntities.towers.tower1;
						entities.towerInstalling.towerInstallation = true;
					}
					if (event.key.code == Keyboard::Num2 && entities.player.GetMoney() >= usedEntities.towers.tower2.GetPrice())
					{
						if (!entities.towerInstalling.towerInstallation) entities.placingTower = new Tower;
						*entities.placingTower = usedEntities.towers.tower2;
						entities.towerInstalling.towerInstallation = true;
					}
					if (event.key.code == Keyboard::Num3 && entities.player.GetMoney() >= usedEntities.towers.tower3.GetPrice())
					{
						if (!entities.towerInstalling.towerInstallation) entities.placingTower = new Tower;
						*entities.placingTower = usedEntities.towers.tower3;
						entities.towerInstalling.towerInstallation = true;
					}

				}
				if (event.key.code == Keyboard::Escape) window.close();
			}
		}
	}
}

void Spawner(Entities & entities, UsedEntities & usedEntities, UsedSounds & usedSounds, const float time)
{
	usedEntities.enemySpawner.timerToSpawn.current -= time;
	if (usedEntities.enemySpawner.timerToSpawn.current <= 0)
	{
		auto iterMap = usedEntities.enemySpawner.timeEnemySpawnOfNumberEnemy.find(usedEntities.enemySpawner.numberEnemy);
		if (iterMap != usedEntities.enemySpawner.timeEnemySpawnOfNumberEnemy.end())
		{
			usedEntities.enemySpawner.timerToSpawn.initial = iterMap->second;
		}
		usedEntities.enemySpawner.timerToSpawn.current = usedEntities.enemySpawner.timerToSpawn.initial;

		if (usedEntities.enemySpawner.iterEnemy != usedEntities.enemySpawner.enemiesInLevel.end())
		{
			SpawnEnemy(usedEntities.enemySpawner, entities.enemies);
		}
	}

	usedEntities.timersSpawns.meteorSpawnTimer.current -= time;
	if (usedEntities.timersSpawns.meteorSpawnTimer.current <= 0)
	{
		SpawnMeteor(usedEntities.meteor, entities.meteors);
		usedEntities.timersSpawns.meteorSpawnTimer.current = usedEntities.timersSpawns.meteorSpawnTimer.initial;
	}

	usedEntities.timersSpawns.evilLaughTimer.current -= time;
	if (usedEntities.timersSpawns.evilLaughTimer.current <= 0)
	{
		if (rand() % 100 == CHANCE_LAUGH_IN_SECONDS)
		{
			usedSounds.evilLaugh.sound.play();
		}
		usedEntities.timersSpawns.evilLaughTimer.current = usedEntities.timersSpawns.evilLaughTimer.initial;
	}
}

state CheckGameState(EnemySpawner & enemySpawn, Entities & entities)
{
	if (enemySpawn.iterEnemy == enemySpawn.enemiesInLevel.end() && entities.enemies.size() == 0)
	{
		return state::win;
	}
	if (entities.player.GetCurrentHp() < 0) 
	{ 
		return state::lose; 
	}
	return state::game;
}

void InitGameEntities(UsedEntities & usedEntities, UsedSounds & usedSounds, UsedMusics & usedMusics, UsedTexts & usedTexts, Entities & entities, 
						Textures & textures)
{
	InitMeteorSpawnTimer(usedEntities.timersSpawns.meteorSpawnTimer);
	InitEvilLaughTimer(usedEntities.timersSpawns.evilLaughTimer);
	InitMusics(usedMusics);
	InitSounds(usedSounds);
	InitEntity(usedEntities, entities, textures, usedSounds, usedTexts);
	InitEnemySpawn(usedEntities);
	InitTextMoney(usedTexts);
	entities.placingTower = new Tower;
}


void PlayGame(Entities & entities, UsedEntities & usedEntities, UsedTexts & usedTexts, UsedSounds & usedSounds, UsedMusics & usedMusics, state & gameState,
				View & view, RenderWindow & window, Clock & clock)
{
	float time = (float)clock.getElapsedTime().asMicroseconds();
	clock.restart();
	time /= 1000;

	Event event;
	EventUpdate(event, window, gameState, entities, usedEntities);

	Spawner(entities, usedEntities, usedSounds, time);

	window.clear(Color::White);

	UpdateAndDraw(entities, usedEntities, usedSounds, usedTexts, view, window, time);
	CheckPlayerHp(entities.player, usedEntities.vignette, usedSounds, usedMusics, window);

	window.display();
	gameState = CheckGameState(usedEntities.enemySpawner, entities);
}

int main()
{
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Hell Gate", Style::Default);
	View view;
	view.reset(FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT));
	window.setKeyRepeatEnabled(false);

	Textures textures;
	UsedSounds usedSounds;
	UsedMusics usedMusics;
	UsedTexts usedTexts;
	UsedEntities usedEntities;

	Entities entities;
	
	if (!LoadTextures(textures) || !LoadSounds(usedSounds) || !LoadFont(usedTexts.font))
	{
		cout << "Not loaded resources" << endl;
		return EXIT_FAILURE;
	}
	InitGameEntities(usedEntities, usedSounds, usedMusics, usedTexts, entities, textures);

	Clock clock;
	state gameState = state::menu;

	while (window.isOpen())
	{
		if (gameState == state::game)
		{
			PlayGame(entities, usedEntities, usedTexts, usedSounds, usedMusics, gameState, view, window, clock);
		}
		if (gameState == state::win)
		{
			usedSounds.heartbeat.sound.stop();
			usedMusics.game.stop();
			Win(usedMusics.win, view, window);
		}
		if (gameState == state::lose)
		{
			usedMusics.game.stop();
			usedSounds.heartbeat.sound.stop();
			Lose(usedMusics.lose, view, window);
		}
		if (gameState == state::menu)
		{
			Menu(usedMusics, gameState, view, window);
			clock.restart();
		}
	}
	return 0;
}