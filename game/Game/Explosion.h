#pragma once

class Explosion
{
public:
	Explosion();
	~Explosion();

	void SetExplosion(Texture & texture, const int columnsInMap, const int linesInMap, const float speedAnimation_);

	void SetScale(const float x, const float y);

	void SetSound(Sound *sound_);
	Sound *GetSound();

	void SetPosition(const Vector2f position);

	bool GetIsDestroy();

	void Update(const float time);

	void Draw(RenderWindow & window);
private:
	SpriteMap spriteMap;
	bool isDestroy = false;
	float speedAnimation;
	float currFrame = 0;
	Sound *sound;
};