#pragma once
class FPS
{
public:
	FPS() :timer(0), fps(0) {};
	~FPS() = default;

	void printFPS(const float time)
	{
		timer += time;
		fps++;
		if (timer >= 1000) //Каждую секунду
		{
			cout << fps << endl;
			fps = 0;
			timer = 0;
		}
	}
private:
	float timer = 0;
	int fps = 0;
};