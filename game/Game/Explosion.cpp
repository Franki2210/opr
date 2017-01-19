#include "Header.h"
#include "SpriteMap.h"
#include "Explosion.h"

Explosion::Explosion() = default;
Explosion::~Explosion() = default;

void Explosion::SetExplosion(Texture & texture, const int columnsInMap, const int linesInMap, const float speedAnimation_)
{
	spriteMap.SetSpriteMap(texture, columnsInMap, linesInMap);
	speedAnimation = speedAnimation_;
}

void Explosion::SetScale(const float x, const float y)
{
	spriteMap.sprite.setScale(x, y);
}

void Explosion::SetSound(Sound *sound_)
{
	sound = sound_;

}
Sound *Explosion::GetSound()
{
	return sound;
}

void Explosion::SetPosition(const Vector2f position)
{
	spriteMap.sprite.setPosition(position);
}

bool Explosion::GetIsDestroy()
{
	return isDestroy;
}

void Explosion::Update(const float time)
{
	currFrame += speedAnimation * time;
	spriteMap.SetFrame((int)currFrame);
	if (currFrame >= spriteMap.GetColumns() * spriteMap.GetLines())
	{
		isDestroy = true;
	}
}

void Explosion::Draw(RenderWindow & window)
{
	window.draw(spriteMap.sprite);
}