#include "Header.h"

void Win(Music & BG, state & gameState, View & view, RenderWindow & window)
{
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	//menuTexture1.loadFromFile(PATH_TO_TEXTURES + "new_game.png");
	menuTexture2.loadFromFile(PATH_TO_TEXTURES + "exit.png");
	menuBackground.loadFromFile(PATH_TO_TEXTURES + "win.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
	menuBg.setScale(3, 3);
	bool isMenu = 1;
	int menuNum = 0;
	//menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menuBg.setPosition(0, 0);
	window.setMouseCursorVisible(true);
	if (BG.getStatus() == SoundStream::Stopped) BG.play();
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
	window.setView(view);

	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		//menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menuBg.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		//if (IntRect(100, 30, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
		if (IntRect(100, 90, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			//if (menuNum == 1) { isMenu = false; gameState = state::game; window.setMouseCursorVisible(false); BG.stop(); }//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.close(); isMenu = false; }
		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.display();
	}
	////////////////////////////////////////////////////
}