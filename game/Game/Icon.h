#pragma once

class Icon
{
public:
	sf::Sprite sprite;

	Icon();
	Icon(std::string nameTexture);
	~Icon();

	void SetSprite(std::string nameTexture);

	void SetPosition(sf::Vector2f pos);
	void SetPosition(float x, float y);

	void SetActive(bool isActive_);
	bool GetActive();

	void Draw(sf::RenderWindow & window);

private:
	sf::Texture texture;
	bool isActive = false;
};