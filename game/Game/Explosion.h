#pragma once

class Explosion
{
public:
	Explosion();
	~Explosion();

	void SetExplosion(sf::Texture & texture, const int columnsInMap, const int linesInMap, const float speedAnimation);

	void SetScale(const float x, const float y);

	void SetSound(sf::Sound *sound);
	sf::Sound *GetSound();

	void SetPosition(const sf::Vector2f position);

	bool GetIsDestroy();

	void Update(const float time);

	void Draw(sf::RenderWindow & window);
private:
	SpriteMap spriteMap;
	bool isDestroy = false;
	float speedAnimation;
	float currFrame = 0;
	sf::Sound *sound;
};