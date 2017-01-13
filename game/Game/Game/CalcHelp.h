#pragma once
#include "Header.h"

float CalculateDistance(Vector2f & startPosition, Vector2f & endPosition)
{
	Vector2f dirVector = endPosition - startPosition;
	return sqrt(dirVector.x * dirVector.x + dirVector.y * dirVector.y);
}

float CalculateDistance(Vector2f & vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}