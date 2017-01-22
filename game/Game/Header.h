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

//TODO: убрать using namespace...

static const std::string PATH_TO_TEXTURES = "recources/textures/";
static const std::string PATH_TO_MUSIC = "recources/music/";
static const std::string PATH_TO_SOUNDS = "recources/sounds/";
static const std::string PATH_TO_FONTS = "recources/fonts/";
enum Direction { Up = 0, UpRight, Right, DownRight, Down, DownLeft, Left, UpLeft };
enum state { menu, game, lose, win };