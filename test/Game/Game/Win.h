#include "Header.h"

void Win(Music & BGMusic, state & gameState, View & view, RenderWindow & window)
{
	Texture exitTexture;
	Texture backgroundTexture;
	exitTexture.loadFromFile(PATH_TO_TEXTURES + "exit.png");
	backgroundTexture.loadFromFile(PATH_TO_TEXTURES + "win.jpg");
	Sprite exitButton(exitTexture);
	Sprite menuBg(backgroundTexture);
	menuBg.setScale(2, 2);
	bool isMenu = true;
	bool isExitButton = false;
	exitButton.setPosition(100, 90);
	menuBg.setPosition(0, 0);
	window.setMouseCursorVisible(true);
	if (BGMusic.getStatus() == SoundStream::Stopped) BGMusic.play();
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	window.setView(view);
	menuBg.setColor(Color::White);
	while (isMenu)
	{
		isExitButton = false;
		if (exitButton.getColor() != Color::White)
		{
			exitButton.setColor(Color::White);
		}
		window.clear(Color::White);

		if (exitButton.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
		{
			exitButton.setColor(Color::Blue);
			isExitButton = true;
		}

		if (Mouse::isButtonPressed(Mouse::Left) && isExitButton)
		{
			window.close();
			isMenu = false;
		}

		window.draw(menuBg);
		window.draw(exitButton);
		window.display();
	}
}