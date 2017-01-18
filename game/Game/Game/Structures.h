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
#include "EnemyExplosion.h"
#include "Vignette.h"
#include "CameraShake.h"

struct TexturesEnemy
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
	TexturesEnemy enemy1;
	TexturesEnemy enemy2;
	TexturesEnemy enemy3;
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
struct TowerInstalling
{
	CircleShape placingArea;
	CircleShape notPlacingArea;
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
	Sprite mapSprite;
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
	Coin coin;
	Vignette vignette;
	CameraShake cameraShake;
};

struct Entities
{
	Sprite mapSprite;
	Player player;
	Portal portal;
	Obstacles obstacles;
	TowerInstalling towerInstalling;
	Tower *placingTower;
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

struct ShotSounds
{
	SoundBuffer shot1Buffer;
	SoundBuffer shot2Buffer;
	SoundBuffer shot3Buffer;
	Sound shot1;
	Sound shot2;
	Sound shot3;
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
	Music menu;
	Music game;
	Music lose;
	Music win;
};