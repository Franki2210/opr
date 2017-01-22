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
	usedMusics.game.setVolume(100);
	while (timeToExtinction > 0)
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();

		timeToExtinction -= time;

		if (currAlpha < 255.0f)
		{
			currAlpha += 255.0f * time * 0.06f;
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
			//usedMusics.game.setVolume(100 - (100 * timeToExtinction / 2.0f));
		}
		else if (timeToExtinction <= 0)
		{
			usedMusics.game.setVolume(100);
		}

		window.draw(blackScreenSprite);
		window.display();
	}
	usedMusics.alarm.stop();
}

void Menu(UsedMusics & usedMusics, state & gameState, View & view, RenderWindow & window)
{
	Texture newGameTexture;
	Texture exitTexture;
	Texture menuBackground;

	newGameTexture.loadFromFile(PATH_TO_TEXTURES + "new_game.png");
	exitTexture.loadFromFile(PATH_TO_TEXTURES + "exit.png");
	menuBackground.loadFromFile(PATH_TO_TEXTURES + "bg.jpg");

	Sprite newGameButton(newGameTexture);
	Sprite exitButton(exitTexture);
	Sprite menuBg(menuBackground);
	newGameButton.setTextureRect(IntRect(0, 0, newGameTexture.getSize().x, newGameTexture.getSize().y));
	exitButton.setTextureRect(IntRect(0, 0, exitTexture.getSize().x, exitTexture.getSize().y));

	bool isMenu = 1;
	int menuNum = 0;

	newGameButton.setPosition(0, 0);
	exitButton.setPosition(0, 60);
	newGameButton.setScale(0.5f, 0.5f);
	exitButton.setScale(0.5f, 0.5f);
	menuBg.setPosition(0, 0);

	window.setMouseCursorVisible(true);
	usedMusics.menu.play();
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

		if (FloatRect(0, 0, 400, 80).contains((Vector2f)Mouse::getPosition(window)))
		{
			newGameButton.setColor(Color(255, 80, 80));
			menuNum = 1;
		}
		if (FloatRect(0, 80, 400, 80).contains((Vector2f)Mouse::getPosition(window)))
		{
			exitButton.setColor(Color(255, 80, 80));
			menuNum = 2;
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
			{
				isMenu = false;
				gameState = state::game;
				window.setMouseCursorVisible(false);
				PauseBeforeNewGame(usedMusics, window);
				usedMusics.menu.stop();
			}
			if (menuNum == 2)
			{
				window.close();
				isMenu = false;
			}
		}

		window.clear(Color::Black);
		window.draw(menuBg);
		window.draw(newGameButton);
		window.draw(exitButton);
		window.display();
	}
}

void Win(Music & BGMusic, View & view, RenderWindow & window)
{
	Texture exitTexture;
	Texture backgroundTexture;

	exitTexture.loadFromFile(PATH_TO_TEXTURES + "exit.png");
	backgroundTexture.loadFromFile(PATH_TO_TEXTURES + "win.png");

	Sprite exitButton(exitTexture);
	Sprite menuBg(backgroundTexture);

	exitButton.setScale(0.5f, 0.5f);

	bool isMenu = true;
	bool isExitButton = false;

	exitButton.setPosition(0, 0);
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

		if (FloatRect(0, 0, 400, 80).contains((Vector2f)Mouse::getPosition(window)))
		{
			exitButton.setColor(Color(255, 80, 80));
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

void Lose(Music & BGMusic, View & view, RenderWindow & window)
{
	Texture exitTexture;
	Texture backgroundTexture;

	exitTexture.loadFromFile(PATH_TO_TEXTURES + "exit.png");
	backgroundTexture.loadFromFile(PATH_TO_TEXTURES + "lose.png");

	Sprite exitButton(exitTexture);
	Sprite menuBg(backgroundTexture);

	exitButton.setScale(0.5f, 0.5f);

	bool isMenu = true;
	bool isExitButton = false;

	exitButton.setPosition(0, 0);
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

		if (FloatRect(0, 0, 400, 80).contains((Vector2f)Mouse::getPosition(window)))
		{
			exitButton.setColor(Color(255, 80, 80));
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