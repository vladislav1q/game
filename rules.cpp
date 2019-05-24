#include "init.h"
#include "button.h"
#include "music.h"
#include <fstream>

#pragma once

void openRule(RenderWindow &window, VideoMode &mode){
    Event event;

    Font font;
    font.loadFromFile(pathToDirectory + "fonts/font.ttf");
    Text text;
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(Color::Red);
    text.setPosition(100, 100);

    std::ifstream in;
    std::string string;

    in.open(pathToDirectory + "rules.txt", std::ios::in);
    if(in.is_open()){
        while (getline(in, string))
        {
            text.setString(text.getString() + "\n" + string);
        }
    }
    in.close();

    Button back(mode, "BACK", pathToDirectory + "fonts/font.ttf", Color::Red);
    Sprite spriteCursor(textureCursor0);
    setCursor(window, spriteCursor);

    Clock clock;
    Time time = clock.getElapsedTime();
    bool changeColor = false;
    int color = 0;

    while(window.isOpen()){

        while(window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }

            if (event.type == event.MouseButtonReleased)
                spriteCursor.setTexture(textureCursor0);
            if (event.type == event.MouseButtonPressed)
                spriteCursor.setTexture(textureCursor1);

            if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
               isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), back.sprite)){
                soundsAll.sound[9].play();
                return;
            }
        }

        time = clock.restart();
        if(!changeColor){
            color += (int)(time.asSeconds() * 200);
            if(color > 255){
                color = 255;
                changeColor = true;
            }
        } else{
            color -= (int)(time.asSeconds() * 200);
            if(color < 50){
                color = 50;
                changeColor = false;
            }
        }

        window.clear(Color(100, 100, color, 0));

        back.update(window);
        updateCursor(window, spriteCursor);

        window.draw(text);
        back.draw(window);
        window.draw(spriteCursor);

        window.display();
    }

}
