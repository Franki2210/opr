#pragma once

class CameraShake
{
public:
	CameraShake();
	~CameraShake();

	void SetShake(bool shake);
	bool GetShake();
	void SetOffsetWithShake(const int value);

	void Update(sf::View & view, const sf::Vector2f & positionPlayer, const float time);
private:
	float timeShake = 1000.0f;
	float timerShake = timeShake;
	int offset = 1;
	bool isShake = false;
};