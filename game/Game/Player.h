#pragma once
#include "Header.h"
#include "Entity.h"
#include "Bullet.h"
#include "Bonus.h"

struct SoundsSteps
{
	sf::Sound step1;
	sf::Sound step2;
	sf::Sound step3;
	sf::Sound step4;
};

class Player : public Entity
{
public:
	bool isMove = false;
	bool canShot = false;

	Player();
	Player(sf::Texture texIdle, const  int colIdle, const int lineIdle,
		sf::Texture texRun, const int colRun, const int lineRun);
	~Player();

	void SetSpriteMaps(sf::Texture & texIdle, const int colIdle, const int lineIdle,
		sf::Texture & texRun, const int colRun, const int lineRun);

	void SetSoundSteps(const sf::SoundBuffer & soundBuf1, const sf::SoundBuffer & soundBuf2, const sf::SoundBuffer & soundBuf3, const sf::SoundBuffer & soundBuf4,
		const float timeBetweenSounds, const float volume);

	sf::FloatRect GetGlobalBounds();

	//Направление движения
	Direction DirectionFromKey();
	sf::Vector2f MoveFromDirection(float const &time);

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

	void Draw(sf::RenderWindow & window);
private:
	float speed;
	Direction direction = Direction::Up;
	sf::FloatRect obstacle;
	Bullet bullet;
	//увести в таймер
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
	std::list<Bonus> activeBonuses;
};