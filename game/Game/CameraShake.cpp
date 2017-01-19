#include "Header.h"
#include "CameraShake.h"

CameraShake::CameraShake() = default;
CameraShake::~CameraShake() = default;

void CameraShake::SetShake(bool shake)
{
	isShake = shake;
}
bool CameraShake::GetShake()
{
	return isShake;
}
void CameraShake::SetOffsetWithShake(const int value)
{
	offset = value;
}

void CameraShake::Update(View & view, const Vector2f & positionPlayer, const float time)
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