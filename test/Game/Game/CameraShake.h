#pragma once
#include "Header.h"

class CameraShake
{
public:
	CameraShake() = default;
	~CameraShake() = default;

	void SetShake(bool shake)
	{
		isShake = shake;
	}
	bool GetShake()
	{
		return isShake;
	}
	void SetOffsetWithShake(const int value)
	{
		offset = value;
	}

	void Update(View & view, const Vector2f & positionPlayer, const float time)
	{
		if (timerShake > 0 && isShake)
		{
			timerShake -= time;
			Vector2f randPosition((offset / 2) - float(rand() % offset), (offset / 2) - float(rand() % offset));
			view.setCenter(positionPlayer + randPosition);
		}
		else
		{
			isShake = false;
			timerShake = timeShake;
		}
	}
private:
	float timeShake = 1000.0f;
	float timerShake = timeShake;
	int offset = 1;
	bool isShake;
};