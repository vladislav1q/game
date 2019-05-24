#include "menu.h"


using namespace sf;

int main()
{
    VideoMode mode = VideoMode::getDesktopMode();
    RenderWindow window(VideoMode(mode.width, mode.height), "ZOMBIE ATTACK" /*sf::Style::Fullscreen*/);

    window.setFramerateLimit(200);

    menu(window, mode);

//    WindowSent windowSent(window, mode);
//    Thread thread(&game, windowSent);
//    thread.launch();
//    thread.wait();

    return 0;
}
