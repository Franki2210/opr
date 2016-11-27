#include "stdafx.h"

const float GRAVITY_ACCELERATION = 9.8f;
const float TIME_STEP = 0.1f;

float GetMaxHeight() 
{
	float maxHeight = 0;
	printf("Height: ");
	if (scanf("%f", &maxHeight) == 0 || maxHeight <= 0)
	{
		printf("\nExpected positive number\n");
		exit(1);
	}
	return maxHeight;
}

float CalculateTimeMaxHeight(const float maxHeight)
{
	return sqrt(maxHeight * 2 / GRAVITY_ACCELERATION);
}

float CalculateInitialVelocity(const float timeMaxHeight)
{
	return GRAVITY_ACCELERATION * timeMaxHeight;
}

void CalculateAndPrintPairHeightTime(const float initVelocity, const float time)
{
	double height = initVelocity * time - 0.5 * GRAVITY_ACCELERATION * time * time;
	printf("currentTime=%f, height=%f\n", time, height);
}

void PrintAllPairTimeHeight(const float initVelocity, const float timeMaxHeight)
{
	bool isMaxHeight = false;
	for (float currentTime = 0; currentTime < timeMaxHeight * 2; currentTime += TIME_STEP)
	{
		if (currentTime > timeMaxHeight && !isMaxHeight)
		{
			isMaxHeight = true;
			CalculateAndPrintPairHeightTime(initVelocity, timeMaxHeight);
		}
		CalculateAndPrintPairHeightTime(initVelocity, currentTime);
	}

	CalculateAndPrintPairHeightTime(initVelocity, timeMaxHeight * 2);
}

void ComputeAndPrintTimeAndHeight()
{
	float maxHeight = GetMaxHeight();
	float timeMaxHeight = CalculateTimeMaxHeight(maxHeight);
	printf("Time max height=%f\n", timeMaxHeight);
	float initVelocity = CalculateInitialVelocity(timeMaxHeight);
	PrintAllPairTimeHeight(initVelocity, timeMaxHeight);
}

int main(int, char *[])
{
	ComputeAndPrintTimeAndHeight();
	return 0;
}