#pragma once
class FPS
{
public:
	FPS();
	~FPS();

	void printFPS(const float time);
private:
	float timer = 0;
	int fps = 0;
};