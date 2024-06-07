#include "Thread.h"

#include <thread>
#include <functional>
#include <iostream>
#include <condition_variable>
#include <vector>

std::condition_variable cv_logic;
std::condition_variable cv_render;
std::mutex mu1;
std::mutex mu2;
std::mutex mutex_vector;
std::vector<int> vector;
bool flag = false;

class Game
{
public:
	void update()
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(mu1);
			cv_logic.wait(lock, [] { return vector.empty(); });
			std::cout << "Game::update" << std::endl;
			vector.push_back(1);
			cv_logic.notify_all();

			flag = true;
			cv_render.wait(lock, [] {return !flag; });
			//std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
};


class Renderer
{
public:
	void update()
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(mu1);
			cv_logic.wait(lock, [] { return !vector.empty(); });
			std::cout << "Renderer::update" << vector.size() << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			vector.clear();
			flag = false;
			cv_render.notify_all();
		}
	}

};



int main()
{

	Game game;
	Renderer renderer;

	std::thread th1(std::bind(&Game::update, &game));
	std::thread th2(std::bind(&Renderer::update, &renderer));

	th1.join();
	th2.join();

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		std::cout << "Main::update" << std::endl;
	}

	return 0;
}