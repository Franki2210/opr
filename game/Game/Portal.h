#pragma once

class Portal
{
public:
	Portal();
	~Portal();

	void SetSpriteMap(Texture & texture, const int numColumns, const int numLines);

	void SetSpeedAnimation(const float value);

	void SetPosition(const float x, const float y);
	void SetPosition(const Vector2f pos);

	void Update(const float time);

	void Draw(RenderWindow & window);

private:
	SpriteMap spriteMap;
	float currFrame = 0;
	float speedAnimation = 0;
};