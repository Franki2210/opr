#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <list>
#include <string>
#include <sstream>
#include <random>

using namespace sf;
using namespace std;

const string PATH_TO_TEXTURES = "recources/textures/";
const string PATH_TO_MUSIC = "recources/music/";
const string PATH_TO_SOUNDS = "recources/sounds/";
const string PATH_TO_FONTS = "recources/fonts/";
enum Direction { Up = 0, UpRight, Right, DownRight, Down, DownLeft, Left, UpLeft };
enum state { menu, game, lose, win };