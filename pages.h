#pragma once

#include "settings.cpp"
#include "rules.cpp"
#include "rating.cpp"
#include "music.h"

class WindowSent{
public:
    WindowSent(RenderWindow &window1, VideoMode &mode1, int hard1):
            window(window1),
            mode(mode1),
            hard(hard1){};

    RenderWindow &window;
    VideoMode &mode;
    int hard;
};

void openSetting(RenderWindow &window, VideoMode &mode);

void openRule(RenderWindow &window, VideoMode &mode);

void openLeaders(RenderWindow &window, VideoMode &mode);
