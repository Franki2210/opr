#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <windows.h>
#include <list>
#include <string>

using namespace sf;
using namespace std;

const string PATH_TO_TEXTURES = "recources/textures/";
enum Direction { Up = 0, UpRight, Right, DownRight, Down, DownLeft, Left, UpLeft };
