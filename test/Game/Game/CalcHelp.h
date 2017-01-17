#pragma once
#include "Header.h"

float CalculateDistance(const Vector2f & startPosition, const Vector2f & endPosition)
{
	Vector2f dirVector = endPosition - startPosition;
	return sqrt(dirVector.x * dirVector.x + dirVector.y * dirVector.y);
}

float CalculateDistance(const Vector2f & vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}