#include "Header.h"
#include "Structures.h"
#include "CameraShake.h"
#include "Vignette.h"
#include "ToxicCloud.h"
#include "EnemyRemnants.h"
#include "Initialization.h"

void InitCursors(UsedCursors & cursors)
{
	if (!cursors.aimTex.loadFromFile(PATH_TO_TEXTURES + "aim_cursor.png"))
	{
		std::cout << "Сорян, не загрузилась: " << "aim_cursor.png" << std::endl;
	}
	cursors.aimCursor.setTexture(cursors.aimTex);
	cursors.aimCursor.setOrigin(cursors.aimTex.getSize().x / 2.0f, cursors.aimTex.getSize().y / 2.0f);
	cursors.aimCursor.setScale(0.15f, 0.24f);

	if (!cursors.handTex.loadFromFile(PATH_TO_TEXTURES + "hand_cursor.png"))
	{
		std::cout << "Сорян, не загрузилась: " << "hand_cursor.png" << std::endl;
	}
	cursors.handCursor.setTexture(cursors.handTex);
	cursors.handCursor.setOrigin(cursors.handTex.getSize().x / 2.0f, cursors.handTex.getSize().y / 2.0f);
	cursors.handCursor.setScale(0.5, 0.5);
}
void InitTowers(UsedTowers & towers, Textures & textures, UsedBullets & bullets)
{

	towers.tower1.SetSpriteMap(textures.tower1, 2, 64);
	towers.tower1.SetMaxHp(300);
	towers.tower1.SetBullet(bullets.gunShot);
	towers.tower1.SetReloadTime(200);
	towers.tower1.SetActionRadius(150);
	towers.tower1.SetPrice(100);

	towers.tower2.SetSpriteMap(textures.tower2, 8, 8);
	towers.tower2.SetMaxHp(200);
	towers.tower2.SetBullet(bullets.twinGunShot);
	towers.tower2.SetReloadTime(200);
	towers.tower2.SetActionRadius(200);
	towers.tower2.SetPrice(200);

	towers.tower3.SetSpriteMap(textures.tower3, 8, 8);
	towers.tower3.SetMaxHp(100);
	towers.tower3.SetBullet(bullets.laserShot);
	towers.tower3.SetReloadTime(4000);
	towers.tower3.SetActionRadius(300);
	towers.tower3.SetPrice(300);
}
void InitIcons(UsedIcons & icons, UsedTexts & texts)
{
	icons.icon1.SetSprite("gun_turret_icon");
	icons.icon2.SetSprite("twin_gun_turret_icon");
	icons.icon3.SetSprite("laser_turret_icon");

	icons.icon1.SetPosition(540, 650);
	icons.icon2.SetPosition(640, 650);
	icons.icon3.SetPosition(740, 650);

	texts.towersPrice.tower1.setString("100");
	texts.towersPrice.tower1.setPosition(500, 650);
	texts.towersPrice.tower1.setFont(texts.font);
	texts.towersPrice.tower1.setCharacterSize(20);
	texts.towersPrice.tower2.setString("200");
	texts.towersPrice.tower2.setPosition(600, 650);
	texts.towersPrice.tower2.setFont(texts.font);
	texts.towersPrice.tower2.setCharacterSize(20);
	texts.towersPrice.tower3.setString("300");
	texts.towersPrice.tower3.setPosition(700, 650);
	texts.towersPrice.tower3.setFont(texts.font);
	texts.towersPrice.tower3.setCharacterSize(20);
}
void InitEnemies(UsedEnemies & enemies, Textures & textures)
{
	enemies.enemy1.SetTextureRun(textures.enemy1.texRun, 16, 16);
	enemies.enemy1.SetTextureAttack(textures.enemy1.texAttack, 11, 16);
	enemies.enemy1.SetPosition(800, 800);
	enemies.enemy1.SetMaxHp(40);
	enemies.enemy1.SetSpeed(0.17f);
	enemies.enemy1.SetDamage(5);
	enemies.enemy1.SetCoins(10);
	enemies.enemy1.SetSpeedAttackAnimation(0.01f);
	enemies.enemy1.SetSpeedRunAnimation(0.04f);

	enemies.enemy2.SetTextureRun(textures.enemy2.texRun, 24, 16);
	enemies.enemy2.SetTextureAttack(textures.enemy2.texAttack, 22, 16);
	enemies.enemy2.SetPosition(800, 800);
	enemies.enemy2.SetMaxHp(70);
	enemies.enemy2.SetSpeed(0.12f);
	enemies.enemy2.SetDamage(10);
	enemies.enemy2.SetCoins(25);
	enemies.enemy2.SetSpeedAttackAnimation(0.01f);
	enemies.enemy2.SetSpeedRunAnimation(0.04f);

	enemies.enemy3.SetTextureRun(textures.enemy3.texRun, 30, 9);
	enemies.enemy3.SetTextureAttack(textures.enemy3.texAttack, 15, 9);
	enemies.enemy3.SetPosition(800, 800);
	enemies.enemy3.SetMaxHp(300);
	enemies.enemy3.SetBossAnim(true);
	enemies.enemy3.SetSpeed(0.1f);
	enemies.enemy3.SetDamage(20);
	enemies.enemy3.SetCoins(100);
	enemies.enemy3.SetSpeedAttackAnimation(0.01f);
	enemies.enemy3.SetSpeedRunAnimation(0.03f);
	enemies.enemy3.SetScale(1.2f, 1.2f);
}
void InitPlayer(Player & player, Textures & textures, Bullet & bullet, UsedSounds & usedSounds)
{
	player.SetSpriteMaps(textures.player.idle, 22, 8, textures.player.run, 22, 8);
	player.SetPosition(800, 600);
	player.SetSpeed(0.18f);
	player.SetBullet(bullet);
	player.SetTimeBetweenShots(150.0f);
	player.SetMaxHp(50);
	player.SetSoundSteps(usedSounds.steps.step1, usedSounds.steps.step2, usedSounds.steps.step3, usedSounds.steps.step4, 280, 30);
}
void InitAreasPlacingTower(TowerInstalling & towerInstalling)
{
	towerInstalling.placingArea.setRadius(150);
	sf::Color placeAreaColor(0, 100, 200, 60);
	towerInstalling.placingArea.setFillColor(placeAreaColor);
	towerInstalling.placingArea.setOrigin(towerInstalling.placingArea.getRadius(), towerInstalling.placingArea.getRadius());

	towerInstalling.notPlacingArea.setRadius(50);
	sf::Color nonPlaceAreaColor(200, 0, 0, 30);
	towerInstalling.notPlacingArea.setFillColor(nonPlaceAreaColor);
	towerInstalling.notPlacingArea.setOrigin(towerInstalling.notPlacingArea.getRadius(), towerInstalling.notPlacingArea.getRadius());
	towerInstalling.intersectAtPlacing = false;
	towerInstalling.towerInstallation = false;
}
void InitPortal(Portal & portal, Textures & textures)
{
	portal.SetSpriteMap(textures.portal, 7, 1);
	portal.SetSpeedAnimation(0.01f);
	portal.SetPosition(800, 800);
}
void InitCoin(Coin & coin, Textures & textures, sf::Font font)
{
	coin.SetSpriteMap(textures.coin, 10, 1);
	coin.SetFont(font);
}
void InitChangeHpView(ChangeHpView & changeHpView, sf::Font font)
{
	changeHpView.SetFont(font);
}
void InitMap(sf::Sprite & map, Textures & textures)
{
	map.setTexture(textures.map);
	map.setScale(2, 2);
}
void InitObstacles(Obstacles & obstacles)
{
	obstacles.topObstacle.setPosition(0, 0);
	obstacles.topObstacle.setSize(sf::Vector2f(2050, 74));
	obstacles.downObstacle.setPosition(0, 1994);
	obstacles.downObstacle.setSize(sf::Vector2f(2050, 74));
	obstacles.leftObstacle.setPosition(0, 74);
	obstacles.leftObstacle.setSize(sf::Vector2f(95, 1920));
	obstacles.rightObstacle.setPosition(2018, 74);
	obstacles.rightObstacle.setSize(sf::Vector2f(95, 1920));
}
void InitBonuses(UsedBonuses & bonuses, Textures & textures)
{
	bonuses.damageIncrease.SetBonus("damageInc", textures.bonuses.damageIncTex, 15, 15000, 15000);
	bonuses.healthIncrease.SetBonus("healthInc", textures.bonuses.healthIncTex, 20, 15000, 0);
	bonuses.speedIncrease.SetBonus("speedInc", textures.bonuses.speedIncTex, 0.05f, 15000, 15000);
	bonuses.fireAcceleration.SetBonus("fireAccel", textures.bonuses.fireAccelTex, 50, 15000, 15000);
	bonuses.damageIncrease.SetScale(0.5f, 0.5f);
	bonuses.healthIncrease.SetScale(0.5f, 0.5f);
	bonuses.speedIncrease.SetScale(0.5f, 0.5f);
	bonuses.fireAcceleration.SetScale(0.5f, 0.5f);
}
void InitBullets(UsedBullets & bullets, Textures & textures, UsedSounds & sounds)
{
	bullets.gunShot.SetTexture(textures.bullets.gunShot);
	bullets.twinGunShot.SetTexture(textures.bullets.twinGunShot);
	bullets.laserShot.SetTexture(textures.bullets.laserShot);
	bullets.playerGunShot.SetTexture(textures.bullets.gunShot);
	bullets.twinGunShot.SetScaleSprite(1.1f, 1.1f);
	bullets.laserShot.SetScaleSprite(1.1f, 1.1f);

	bullets.gunShot.SetDamage(5.0f);
	bullets.gunShot.SetSpeed(0.5f);
	bullets.gunShot.SetSounds(sounds.gunShots.shot1, sounds.gunShots.shot2, sounds.gunShots.shot3);

	bullets.twinGunShot.SetDamage(10.0f);
	bullets.twinGunShot.SetSpeed(0.5f);
	bullets.twinGunShot.SetSounds(sounds.gunShots.shot1, sounds.gunShots.shot2, sounds.gunShots.shot3);

	bullets.laserShot.SetDamage(70.0f);
	bullets.laserShot.SetSpeed(3.0f);
	bullets.laserShot.SetSounds(sounds.laserShots.shot1, sounds.laserShots.shot2, sounds.laserShots.shot3);

	bullets.playerGunShot.SetDamage(5.0f);
	bullets.playerGunShot.SetSpeed(1.0f);
	bullets.playerGunShot.SetSounds(sounds.playerGunShots.shot1, sounds.playerGunShots.shot2, sounds.playerGunShots.shot3);
}
void InitMeteor(Meteor & meteor, Textures & textures)
{
	meteor.SetMeteor(textures.meteor.texture, textures.meteor.shadow, textures.meteor.pointArrival, 100.0f, 1.2f);
}
void InitExplosion(Explosion & explosion, Textures & textures, UsedSounds & sounds)
{
	explosion.SetExplosion(textures.explosion, 6, 8, 0.04f);
	explosion.SetScale(1.3f, 1.3f);
	explosion.SetSound(&sounds.explosion.sound);
}
void InitTowerExplosion(Explosion & explosion, Textures & textures)
{
	explosion.SetExplosion(textures.towerExplosion, 6, 9, 0.04f);
	explosion.SetScale(1.2f, 1.2f);
}
void InitCameraShake(CameraShake & cameraShake)
{
	cameraShake.SetOffsetWithShake(5);
}
void InitVignette(Vignette & vignette, Textures & textures)
{
	vignette.SetTexture(textures.vignette);
}
void InitToxicCloud(ToxicCloud & toxicCloud, Textures & textures)
{
	toxicCloud.SetToxicCloud(textures.toxicCloud, 5, 12);
	toxicCloud.SetTimeToDestroy(7000.0f);
	toxicCloud.SetDamage(5.0f);
	toxicCloud.SetSpeedAnimation(0.01f);
}
void InitEnemyExplosion(EnemyRemnants & enemyExplosion, Textures & textures)
{
	enemyExplosion.SetEnemyExplosion(textures.enemyExplosion, 5, 4);
	enemyExplosion.SetSpeedAnimation(0.02f);
	enemyExplosion.SetTimeToDestroy(20000.0f);
}
void InitMeteorSpawnTimer(Timer & meteorSpawnTimer)
{
	meteorSpawnTimer.initial = 1000.0f;
	meteorSpawnTimer.current = meteorSpawnTimer.initial;
}
void InitEvilLaughTimer(Timer & timer)
{
	timer.initial = 1000.0f;
	timer.current = timer.initial;
}

void InitEntity(UsedEntities & usedEntities, Entities & entities, Textures & textures, UsedSounds & usedSounds, UsedTexts & usedTexts)
{
	InitBullets(usedEntities.bullets, textures, usedSounds);
	InitPlayer(entities.player, textures, usedEntities.bullets.playerGunShot, usedSounds);
	InitTowers(usedEntities.towers, textures, usedEntities.bullets);
	InitIcons(usedEntities.icons, usedTexts);
	InitEnemies(usedEntities.enemies, textures);
	InitCursors(usedEntities.cursors);
	InitAreasPlacingTower(entities.towerInstalling);
	InitPortal(entities.portal, textures);
	InitObstacles(entities.obstacles);
	InitBonuses(usedEntities.bonuses, textures);
	InitCoin(usedEntities.coin, textures, usedTexts.font);
	InitMeteor(usedEntities.meteor, textures);
	InitExplosion(usedEntities.explosion, textures, usedSounds);
	InitTowerExplosion(usedEntities.towerExplosion, textures);
	InitCameraShake(usedEntities.cameraShake);
	InitToxicCloud(usedEntities.toxicCloud, textures);
	InitEnemyExplosion(usedEntities.enemyExplosion, textures);
	InitChangeHpView(usedEntities.changeHpView, usedTexts.font);
	InitMap(usedEntities.mapSprite, textures);
	InitVignette(usedEntities.vignette, textures);
}

void InitEnemySpawn(UsedEntities & usedEntities)
{
	std::vector<int> mapUsedEnemies = { 1,1,2,2,3,3,2,2,2,1,2,2,2,2,1,3,3,2,3,2,3,2,1,2,2,2,1,2,3,3,
								   1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,2,2,1,1,1,1,1,1,1,1,1,
								   1,2,2,2,2,2,2,3,3,3,3,3,3,2,2,2,2,1,3,1,1,1,1,1,1,1,1,1,1,3,
								   1,1,3,3,3,3,1,1,1,3,3,3,2,2,2,3,2,1,1,1,2,3,2,3,3,3,2,2,3,3,
								   2,2,2,2,1,1,1,2,2,2,2,3,3,3,3,2,2,1,1,1,1,1,2,3,3,3,3,3,3,3 };
	usedEntities.enemySpawner.timeEnemySpawnOfNumberEnemy = {  { 0, 4000.0f },
												{ 2, 3000.0f },
												{ 10, 2000.0f },
												{ 15, 1500.0f },
												{ 30, 500.0f } };
	usedEntities.enemySpawner.timerToSpawn.initial = usedEntities.enemySpawner.timeEnemySpawnOfNumberEnemy.find(0)->second;
	usedEntities.enemySpawner.timerToSpawn.current = usedEntities.enemySpawner.timerToSpawn.initial;

	usedEntities.enemySpawner.enemiesInLevel.reserve(mapUsedEnemies.size());
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
		usedEntities.enemySpawner.enemiesInLevel.push_back(newEnemy);
	}
	usedEntities.enemySpawner.iterEnemy = usedEntities.enemySpawner.enemiesInLevel.begin();
}

void InitTextMoney(UsedTexts & texts)
{
	texts.font.loadFromFile(PATH_TO_FONTS + "font.ttf");
	texts.playerMoneyText.setFont(texts.font);
	texts.playerMoneyText.setCharacterSize(20);
	texts.playerMoneyText.setStyle(sf::Text::Bold);
}

void InitMusics(UsedMusics & usedMusics)
{
	usedMusics.game.openFromFile(PATH_TO_MUSIC + "music.ogg");
	usedMusics.game.setLoop(true);
	usedMusics.win.openFromFile(PATH_TO_MUSIC + "win.ogg");
	usedMusics.lose.openFromFile(PATH_TO_MUSIC + "lose.ogg");
	usedMusics.menu.openFromFile(PATH_TO_MUSIC + "menu.ogg");
	usedMusics.alarm.openFromFile(PATH_TO_MUSIC + "alarm.ogg");
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