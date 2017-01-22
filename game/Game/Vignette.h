#pragma once

class Vignette
{
public:
	Vignette();
	~Vignette();

	void SetTexture(sf::Texture & texture);

	void SetActive(bool value);
	bool GetActive();

	void Draw(sf::RenderWindow & window);
private:
	bool isActive = false;
	sf::Sprite sprite;
};