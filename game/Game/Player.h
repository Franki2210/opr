#pragma once
#include "Header.h"
#include "Entity.h"
#include "Bullet.h"
#include "Bonus.h"

struct SoundsSteps
{
	Sound step1;
	Sound step2;
	Sound step3;
	Sound step4;
};

class Player : public Entity
{
public:
	bool isMove = false;
	bool canShot = false;

	Player();
	Player(Texture texIdle, const  int colIdle, const int lineIdle,
		Texture texRun, const int colRun, const int lineRun);
	~Player();

	void SetSpriteMaps(Texture & texIdle, const int colIdle, const int lineIdle,
		Texture & texRun, const int colRun, const int lineRun);

	void SetSoundSteps(const SoundBuffer & soundBuf1, const SoundBuffer & soundBuf2, const SoundBuffer & soundBuf3, const SoundBuffer & soundBuf4,
		const float timeBetweenSounds, const float volume);

	FloatRect GetGlobalBounds();

	//Направление движения
	Direction DirectionFromKey();
	Vector2f MoveFromDirection(float const &time);

	//Пули
	void SetBullet(Bullet usedBullet);
	Bullet GetBullet();

	void SetTimeBetweenShots(float timeBetween);
	void SetSpeed(float value);

	void AddBonus(Bonus bonus);

	//Денюжка
	void AddCoins(int coin);
	void SubCoins(int coin);
	int GetMoney();

	void BonusUpdate(float time);

	void Update(float const & time);

	void Draw(RenderWindow & window);
private:
	float speed;
	Direction direction = Direction::Up;
	FloatRect obstacle;
	Bullet bullet;
	float reloadTime;
	float reloadTimer;
	float timeBetweenShots = 150;
	float timerBetweenShots = timeBetweenShots;
	float timeBetweenSoundsSteps;
	float timerBetweenSoundsSteps;
	SpriteMap spriteMapIdle;
	SpriteMap spriteMapRun;
	float currFrame = 0;
	float speedAnimation;
	int score;
	int coins = 0;

	SoundsSteps soundsSteps;
	list<Bonus> activeBonuses;
};