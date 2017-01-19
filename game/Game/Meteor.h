#pragma once

class Meteor
{
public:
	Meteor();
	~Meteor();

	void SetMeteor(Texture & texture, Texture & textureShadow, Texture & textureArrival, const float damage, const float speed);
	void SetSounds(Sound *sound_);
	Sound *GetSound();

	void SetArrivalPosition(const Vector2f pos);
	void SetArrivalPosition(const float x, const float y);
	Vector2f GetArrivalPosition();
	Vector2f GetCurrentPosition();

	void SetMoveVector(const Vector2f value);

	FloatRect GetArrivalArea();
	float GetDamage();

	bool GetArrival();

	void Update(const float time);

	void Draw(RenderWindow & window);

private:
	Sprite sprite;
	Sprite spriteShadow;
	Sprite spritePointArrival;

	Vector2f arrivalPosition;
	Vector2f currPosition;
	Vector2f moveVector = Vector2f(-0.81f, 0.57f);
	Vector2f startPosition;

	bool isArrival;

	float speed = 0.2f;
	float damage;
	Sound *sound;
};