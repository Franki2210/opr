#pragma once
#include "Header.h"
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
#include "Icon.h"
#include "ToxicCloud.h"
#include "EnemyRemnants.h"
#include "Vignette.h"
#include "CameraShake.h"

struct Timer
{
	float initial;
	float current;
};
struct TimersSpawns
{
	Timer meteorSpawnTimer;
	Timer evilLaughTimer;
};

struct EnemySpawner
{
	std::map<int, float> timeEnemySpawnOfNumberEnemy;
	Timer timerToSpawn;
	std::vector<Enemy*> enemiesInLevel;
	std::vector<Enemy*>::iterator iterEnemy;
	int numberEnemy = 0;
};

struct TexturesEnemy
{
	sf::Texture texRun;
	sf::Texture texAttack;
};
struct TexturesPlayer
{
	sf::Texture idle;
	sf::Texture run;
};
struct TextureBonuses
{
	sf::Texture fireAccelTex;
	sf::Texture speedIncTex;
	sf::Texture damageIncTex;
	sf::Texture healthIncTex;
};
struct TexturesBullets
{
	sf::Texture gunShot;
	sf::Texture twinGunShot;
	sf::Texture laserShot;
};
struct TexturesMeteor
{
	sf::Texture texture;
	sf::Texture shadow;
	sf::Texture pointArrival;
};

struct Textures
{
	TexturesEnemy enemy1;
	TexturesEnemy enemy2;
	TexturesEnemy enemy3;
	TexturesPlayer player;
	TextureBonuses bonuses;
	TexturesBullets bullets;
	TexturesMeteor meteor;
	sf::Texture tower1;
	sf::Texture tower2;
	sf::Texture tower3;
	sf::Texture coin;
	sf::Texture portal;
	sf::Texture map;
	sf::Texture explosion;
	sf::Texture towerExplosion;
	sf::Texture vignette;
	sf::Texture toxicCloud;
	sf::Texture enemyExplosion;
};

struct Obstacles
{
	sf::RectangleShape topObstacle;
	sf::RectangleShape downObstacle;
	sf::RectangleShape leftObstacle;
	sf::RectangleShape rightObstacle;
};
struct TowerInstalling
{
	sf::CircleShape placingArea;
	sf::CircleShape notPlacingArea;
	bool intersectAtPlacing;
	bool towerInstallation;
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
	sf::Sprite aimCursor;
	sf::Sprite handCursor;
	sf::Texture aimTex;
	sf::Texture handTex;
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
	sf::Sprite mapSprite;
	UsedIcons icons;
	UsedTowers towers;
	UsedEnemies enemies;
	UsedCursors cursors;
	UsedBonuses bonuses;
	UsedBullets bullets;
	ChangeHpView changeHpView;
	Meteor meteor;
	Explosion explosion;
	Explosion towerExplosion;
	ToxicCloud toxicCloud;
	EnemyRemnants enemyExplosion;
	Coin coin;
	Vignette vignette;
	CameraShake cameraShake;
	TimersSpawns timersSpawns;
	EnemySpawner enemySpawner;
};

struct Entities
{
	sf::Sprite mapSprite;
	Player player;
	Portal portal;
	Obstacles obstacles;
	TowerInstalling towerInstalling;
	Tower *placingTower;
	std::list<Tower*> towers;
	std::list<Enemy*> enemies;
	std::list<Bullet*> bullets;
	std::list<Coin*> coins;
	std::list<Bonus*> bonuses;
	std::list<ChangeHpView*> changeHpViews;
	std::list<Meteor*> meteors;
	std::list<Explosion*> explosions;
	std::list<ToxicCloud*> toxicClouds;
	std::list<EnemyRemnants*> enemyExplosions;
};

struct UsedTextsTowersPrice
{
	sf::Text tower1;
	sf::Text tower2;
	sf::Text tower3;
};
struct UsedTexts
{
	sf::Font font;
	UsedTextsTowersPrice towersPrice;
	sf::Text playerMoneyText;
};

struct ShotSounds
{
	sf::SoundBuffer shot1Buffer;
	sf::SoundBuffer shot2Buffer;
	sf::SoundBuffer shot3Buffer;
	sf::Sound shot1;
	sf::Sound shot2;
	sf::Sound shot3;
};
struct StepsSounds
{
	sf::SoundBuffer step1;
	sf::SoundBuffer step2;
	sf::SoundBuffer step3;
	sf::SoundBuffer step4;
};
struct OneSound
{
	sf::SoundBuffer soundBuf;
	sf::Sound sound;
};
struct UsedSounds
{
	ShotSounds playerGunShots;
	ShotSounds gunShots;
	ShotSounds laserShots;
	StepsSounds steps;
	OneSound placeTower;
	OneSound dropItem;
	OneSound meteorFall;
	OneSound evilLaugh;
	OneSound explosion;
	OneSound heartbeat;
};

struct UsedMusics
{
	sf::Music menu;
	sf::Music game;
	sf::Music lose;
	sf::Music win;
	sf::Music alarm;
};