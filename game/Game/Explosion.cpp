#include "Header.h"
#include "SpriteMap.h"
#include "Explosion.h"

Explosion::Explosion() = default;
Explosion::~Explosion() = default;

void Explosion::SetExplosion(sf::Texture & texture, const int columnsInMap, const int linesInMap, const float speedAnimation)
{
	spriteMap.SetSpriteMap(texture, columnsInMap, linesInMap);
	spriteMap.sprite.setOrigin(spriteMap.sprite.getGlobalBounds().width / 2, spriteMap.sprite.getGlobalBounds().height * 0.7f);
	this->speedAnimation = speedAnimation;
}

void Explosion::SetScale(const float x, const float y)
{
	spriteMap.sprite.setScale(x, y);
}

void Explosion::SetSound(sf::Sound *sound)
{
	this->sound = sound;
}
sf::Sound *Explosion::GetSound()
{
	return sound;
}

void Explosion::SetPosition(const sf::Vector2f position)
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

void Explosion::Draw(sf::RenderWindow & window)
{
	window.draw(spriteMap.sprite);
}