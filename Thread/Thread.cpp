#include "Thread.h"

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
            MY_CONSOLE_WRITE_LINE("Game::update");
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
            MY_CONSOLE_WRITE_LINE("Renderer::update" << vector.size());
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
        MY_CONSOLE_WRITE_LINE("Main::update");
    }

    return 0;
}
