#pragma once

class Vignette
{
public:
	Vignette();
	~Vignette();

	void SetTexture(Texture & texture);

	void SetActive(bool value);
	bool GetActive();

	void Draw(RenderWindow & window);
private:
	bool isActive = false;
	Sprite sprite;
};