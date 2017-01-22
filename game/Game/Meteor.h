#pragma once

class Meteor
{
public:
	Meteor();
	~Meteor();
	Meteor(sf::Texture & texture, sf::Texture & textureShadow, sf::Texture & textureArrival, const float damageMeteor, const float speedMeteor);

	void SetMeteor(sf::Texture & texture, sf::Texture & textureShadow, sf::Texture & textureArrival, const float damageMeteor, const float speedMeteor);

	void SetArrivalPosition(const sf::Vector2f pos);
	void SetArrivalPosition(const float x, const float y);
	sf::Vector2f GetArrivalPosition();
	sf::Vector2f GetCurrentPosition();

	void SetMoveVector(const sf::Vector2f value);

	sf::FloatRect GetArrivalArea();
	float GetDamage();

	bool GetArrival();

	void Update(const float time);

	void Draw(sf::RenderWindow & window);

private:
	sf::Sprite sprite;
	sf::Sprite spriteShadow;
	sf::Sprite spritePointArrival;

	sf::Vector2f arrivalPosition;
	sf::Vector2f currPosition;
	sf::Vector2f moveVector = sf::Vector2f(-0.81f, 0.57f);
	sf::Vector2f startPosition;

	bool isArrival = false;

	float speed = 0.2f;
	float damage;
	sf::Sound *sound;
};