#include "Header.h"
#include "LoadRecources.h"
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

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 900;
const float VIEW_WIDTH = 1280.0f;
const float VIEW_HEIGHT = 720.0f;

void SpawnEnemy(vector<Enemy*> enemiesInLevel, vector<Enemy*>::iterator & iterEnemy, list<Enemy*> & enemies, int & numberEnemy)
{
	enemies.push_back(*iterEnemy);
	iterEnemy++;
	numberEnemy++;
}
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
void SpawnMeteor(Meteor & meteor, list<Meteor*> & meteors)
{
	Meteor* newMeteor = new Meteor;
	*newMeteor = meteor;
	newMeteor->SetArrivalPosition(float(rand() % 2000), float(rand() % 2000));
	meteors.push_back(newMeteor);
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
void CheckPlayerHp(Player & player, Vignette & vignette, UsedSounds & usedSounds, UsedMusics & usedMusics, state & gameState, RenderWindow & window)
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
	if (player.GetCurrentHp() < 0) { gameState = state::lose; usedMusics.game.stop(); usedMusics.lose.play(); };
}

void TowerUpdateAndDraw(Entities & entities, const bool drawActionArea, const float time, RenderWindow & window)
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
				if (tower->spriteMap.sprite.getGlobalBounds().intersects(entities.placingTower->spriteMap.sprite.getGlobalBounds()))
				{
					entities.towerInstalling.intersectAtPlacing = true;
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
		if (meteor->GetArrival())
		{
			SpawnExplosion(entities.explosions, usedEntities.explosion, usedEntities.cameraShake, meteor->GetArrivalPosition(), window);
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

void UpdateAndDraw(Entities & entities, UsedEntities & usedEntities, UsedSounds & usedSounds, const bool drawActionArea, RenderWindow & window, const float time)
{
	EnemyExplosionUpdateAndDraw(entities.enemyExplosions, window, time);
	PortalUpdateAndDraw(entities, window, time);
	MeteorsUpdateAndDraw(entities, usedEntities, window, time);
	ToxicCloudUpdateAndDraw(entities, window, time);
	ExplosionsUpdateAndDraw(entities.explosions, window, time);
	BonusesUpdateAndDraw(entities, usedSounds, window, time);
	TowerUpdateAndDraw(entities, drawActionArea, time, window);
	BulletUpdateAndDraw(entities, usedEntities, window, time);
	EnemiesUpdateAndDraw(entities, usedEntities, window, time);
	ChangeHpViewsUpdateAndDraw(entities, window, time);
}

void EventUpdate(Event & event, RenderWindow & window, state & gameState, Entities & entities, UsedEntities & usedEntities, bool & drawActionArea)
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
				if (event.key.code == Keyboard::R)
				{
					if (drawActionArea == false) drawActionArea = true;
					else drawActionArea = false;
				}
				if (event.key.code == Keyboard::Escape) window.close();
			}
		}
	}
}

void TowerInstall(Entities & entities, UsedEntities & usedEntities, UsedSounds & usedSounds, const Vector2f mousePos, RenderWindow & window)
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

void PlayerTracking(Player & player, CameraShake & cameraShake, const Vector2f & mapSize, View & view, const float time)
{
	if (player.GetPosition().x < view.getSize().x / 2 || player.GetPosition().x > mapSize.x - view.getSize().x / 2 ||
		player.GetPosition().y < view.getSize().y / 2 || player.GetPosition().y > mapSize.y - view.getSize().y / 2)
	{
		float tempX = player.GetPosition().x;
		float tempY = player.GetPosition().y;
		if (player.GetPosition().x < view.getSize().x / 2)
			tempX = view.getSize().x / 2;
		if (player.GetPosition().x > mapSize.x - view.getSize().x / 2)
			tempX = mapSize.x - view.getSize().x / 2;
		if (player.GetPosition().y < view.getSize().y / 2)
			tempY = view.getSize().y / 2;
		if (player.GetPosition().y > mapSize.y - view.getSize().y / 2)
			tempY = mapSize.y - view.getSize().y / 2;

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

int main()
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN); 
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Hell Gate", Style::Default);
	View view;
	view.reset(FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT));

	Textures textures;
	UsedSounds usedSounds;
	UsedMusics usedMusics;
	UsedTexts usedTexts;
	UsedEntities usedEntities;

	Entities entities;

	vector<Enemy*> enemiesInLevel;

	Font font;
	Text playerMoneyText;
	InitTextMoney(playerMoneyText, font);
	
	if (!LoadTextures(textures) || !LoadSounds(usedSounds))
	{
		return EXIT_FAILURE;
	}
	InitMusics(usedMusics);
	InitSounds(usedSounds);
	InitEntity(usedEntities, entities, textures, usedSounds, usedTexts, font);
	InitMapUsedEnemies(enemiesInLevel, usedEntities);

	Vector2f mapSize(usedEntities.mapSprite.getGlobalBounds().width, usedEntities.mapSprite.getGlobalBounds().height);

	vector<Enemy*>::iterator iterEnemy = enemiesInLevel.begin();
	entities.placingTower = new Tower;
	bool drawActionArea = false;

	float timerEnemySpawn = 4000;
	float timerMeteorSpawn = 1000;
	float timerEvilLaugh = 1000;
	int numberEnemy = 0;

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
		EventUpdate(event, window, gameState, entities, usedEntities, drawActionArea);

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f mousePos = window.mapPixelToCoords(pixelPos);

		entities.player.isMove = false;
		
		if (gameState == state::game)
		{
			if (usedMusics.game.getStatus() == SoundStream::Stopped) 
			{
				usedMusics.game.play();
			}

			timerEnemySpawn -= time;

			if (timerEnemySpawn <= 0)
			{
				if (numberEnemy >= 0 && numberEnemy < 5) timerEnemySpawn = 4000;
				else if (numberEnemy >= 5 && numberEnemy < 10) timerEnemySpawn = 3000;
				else if (numberEnemy >= 10 && numberEnemy < 15) timerEnemySpawn = 2000;
				else if (numberEnemy >= 15 && numberEnemy < 30) timerEnemySpawn = 1500;
				else if (numberEnemy >= 30) timerEnemySpawn = 500;

				if (iterEnemy != enemiesInLevel.end())
				{
					SpawnEnemy(enemiesInLevel, iterEnemy, entities.enemies, numberEnemy);
				}
				else
				{
					if (entities.enemies.size() == 0)
					{
						gameState = state::win;
						usedMusics.game.stop();
					}
				}
				numberEnemy++;
			}
			entities.towerInstalling.intersectAtPlacing = false;

			timerMeteorSpawn -= time;
			if (timerMeteorSpawn <= 0)
			{
				SpawnMeteor(usedEntities.meteor, entities.meteors);
				timerMeteorSpawn = 1000;
			}

			timerEvilLaugh -= time;
			if (timerEvilLaugh <= 0)
			{
				if (rand() % 100 == 1)
				{
					usedSounds.evilLaugh.sound.play();
				}
				timerEvilLaugh = 1000;
			}
			
			window.clear(Color::White);

			window.draw(usedEntities.mapSprite);
			UpdateAndDraw(entities, usedEntities, usedSounds, drawActionArea, window, time);

			if (Mouse::isButtonPressed(Mouse::Left) && !entities.towerInstalling.towerInstallation && entities.player.canShot)
			{
				PlayerShot(entities, mousePos);
			}

			TowerInstall(entities, usedEntities, usedSounds, mousePos, window);
			CheckObstacles(entities.obstacles, entities.player);
			PlayerUpdateAndDraw(entities.player, window, time);
			CoinsUpdateAndDraw(entities.coins, window, time);

			PlayerTracking(entities.player, usedEntities.cameraShake, mapSize, view, time);
			window.setView(view);

			CursorUpdateAndDraw(usedEntities.cursors, entities.towerInstalling, mousePos, window);
			IconsUpdateAndDraw(usedEntities, entities, usedTexts, view, window);

			ostringstream playerMoneyString;
			playerMoneyString << entities.player.GetMoney();
			playerMoneyText.setString("Money: " + playerMoneyString.str());
			playerMoneyText.setPosition(view.getCenter() + Vector2f(-540, 260));

			CheckPlayerHp(entities.player, usedEntities.vignette, usedSounds, usedMusics, gameState, window);
			window.draw(playerMoneyText);
		}
		if (gameState == state::win)
		{
			usedSounds.heartbeat.sound.stop();
			Win(usedMusics.win, gameState, view, window);
		}
		if (gameState == state::lose)
		{
			usedSounds.heartbeat.sound.stop();
			Lose(usedMusics.lose, gameState, view, window);
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