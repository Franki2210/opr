#include "Header.h"
#include "SpriteMap.h"

void Menu(Music & BG, state & gameState, View & view, RenderWindow & window, float time)
{
	Texture newGameTexture;
	Texture exitTexture;
	Texture menuBackground;
	newGameTexture.loadFromFile(PATH_TO_TEXTURES + "new_game.png");
	exitTexture.loadFromFile(PATH_TO_TEXTURES + "exit.png");
	menuBackground.loadFromFile(PATH_TO_TEXTURES + "bg.png");
	Sprite newGameButton(newGameTexture);
	Sprite exitButton(exitTexture);
	Sprite menuBg(menuBackground);
	menuBg.setScale(2.5f, 2.5f);
	bool isMenu = 1;
	int menuNum = 0;
	newGameButton.setPosition(100, 30);
	exitButton.setPosition(100, 90);
	menuBg.setPosition(0, 0);
	window.setMouseCursorVisible(true);
	if (BG.getStatus() == SoundStream::Stopped) BG.play();
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	window.setView(view);
	menuBg.setColor(Color::White);
	while (isMenu)
	{
		if (newGameButton.getColor() != Color::White)
		{
			newGameButton.setColor(Color::White);
		}
		if (exitButton.getColor() != Color::White)
		{
			exitButton.setColor(Color::White);
		}
		
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		if (newGameButton.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window))) 
		{ 
			newGameButton.setColor(Color::Blue); 
			menuNum = 1; 
		}
		if (exitButton.getGlobalBounds().contains((Vector2f)Mouse::getPosition(window)))
		{ 
			exitButton.setColor(Color::Blue); 
			menuNum = 2; 
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) 
			{ 
				isMenu = false; 
				gameState = state::game; 
				window.setMouseCursorVisible(false); 
				BG.stop(); 
			}
			if (menuNum == 2) 
			{ 
				window.close(); 
				isMenu = false; 
			}
		}

		window.draw(menuBg);
		window.draw(newGameButton);
		window.draw(exitButton);
		window.display();
	}
}