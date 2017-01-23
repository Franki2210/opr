#include "Header.h"
#include "SpriteMap.h"
#include "Structures.h"
#include "Menu.h"

using namespace sf;

void PauseBeforeNewGame(UsedMusics & usedMusics, RenderWindow & window)
{
	Texture blackScreenTexture;
	blackScreenTexture.loadFromFile(PATH_TO_TEXTURES + "black_screen.png");
	Sprite blackScreenSprite;
	blackScreenSprite.setTexture(blackScreenTexture);
	float timeToExtinction = 5.0f;
	float currAlpha = 0;
	Clock clock;

	usedMusics.menu.stop();
	usedMusics.alarm.play();

	while (timeToExtinction > 0)
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		timeToExtinction -= time;

		if (currAlpha < 255.0f)
		{
			currAlpha += 255.0f * time * 0.05;
			blackScreenSprite.setColor(Color(0, 0, 0, (Uint8)currAlpha));
		}
		else
		{
			blackScreenSprite.setColor(Color(0, 0, 0, 255));
		}

		if (timeToExtinction < 1.7f)
		{
			if (usedMusics.game.getStatus() == SoundSource::Stopped)
			{
				usedMusics.game.play();
			}
		}

		window.draw(blackScreenSprite);
		window.display();
	}
	usedMusics.alarm.stop();
}

void Menu(Textures & textures, UsedMusics & usedMusics, state & gameState, View & view, RenderWindow & window)
{
	Sprite newGameButton(textures.menu.buttonNewGame);
	Sprite exitButton(textures.menu.buttonExit);
	Sprite menuBg(textures.menu.menuBG);

	bool isMenu = true;

	newGameButton.setPosition(0, 0);
	exitButton.setPosition(0, 60);
	newGameButton.setScale(0.5f, 0.5f);
	exitButton.setScale(0.5f, 0.5f);
	menuBg.setPosition(0, 0);

	window.setMouseCursorVisible(true);
	usedMusics.menu.play();
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	window.setView(view);

	while (isMenu && window.isOpen())
	{
		if (newGameButton.getColor() != Color::White)
		{
			newGameButton.setColor(Color::White);
		}
		if (exitButton.getColor() != Color::White)
		{
			exitButton.setColor(Color::White);
		}

		if (FloatRect(0, 0, 400, 80).contains((Vector2f)Mouse::getPosition(window)))
		{
			newGameButton.setColor(Color(255, 80, 80));
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				isMenu = false;
				gameState = state::game;
				window.setMouseCursorVisible(false);
				PauseBeforeNewGame(usedMusics, window);
				usedMusics.menu.stop();
			}
		}
		if (FloatRect(0, 80, 400, 80).contains((Vector2f)Mouse::getPosition(window)))
		{
			exitButton.setColor(Color(255, 80, 80));
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				window.close();
			}
		}

		window.draw(menuBg);
		window.draw(newGameButton);
		window.draw(exitButton);
		window.display();
	}
}

void EndGame(Textures & textures, UsedMusics & musics, state & gameState, View & view, RenderWindow & window)
{	
	Sprite exitButton(textures.menu.buttonExit);
	Sprite menuBg;

	if (gameState == state::win)
	{
		menuBg.setTexture(textures.menu.winBG);
		musics.win.play();
	}
	else 
	{
		menuBg.setTexture(textures.menu.loseBG);
		musics.lose.play();
	}
	musics.game.stop();
	
	exitButton.setScale(0.5f, 0.5f);

	exitButton.setPosition(0, 0);
	menuBg.setPosition(0, 0);

	window.setMouseCursorVisible(true);

	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	window.setView(view);

	while (window.isOpen())
	{
		if (exitButton.getColor() != Color::White)
		{
			exitButton.setColor(Color::White);
		}
		window.clear(Color::White);

		if (FloatRect(0, 0, 400, 80).contains((Vector2f)Mouse::getPosition(window)))
		{
			exitButton.setColor(Color(255, 80, 80));
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				window.close();
			}
		}

		window.draw(menuBg);
		window.draw(exitButton);
		window.display();
	}
}