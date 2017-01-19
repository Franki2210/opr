#include "Header.h"
#include "SpriteMap.h"
#include "Portal.h"

Portal::Portal() = default;
Portal::~Portal() = default;

void Portal::SetSpriteMap(Texture & texture, const int numColumns, const int numLines)
{
	spriteMap.SetSpriteMap(texture, numColumns, numLines);
}

void Portal::SetSpeedAnimation(const float value)
{
	speedAnimation = value;
}

void Portal::SetPosition(const float x, const float y)
{
	spriteMap.SetPosition(x, y);
}
void Portal::SetPosition(const Vector2f pos)
{
	spriteMap.SetPosition(pos);
}

void Portal::Update(const float time)
{
	currFrame += speedAnimation * time;
	if (currFrame > spriteMap.GetColumns()) currFrame = 0;
	spriteMap.SetFrame((int)currFrame);
}

void Portal::Draw(RenderWindow & window)
{
	window.draw(spriteMap.sprite);
}