#include "background.h"
#include "init.h"
#include "draw.h"
#include "button.h"
#include "music.h"

#pragma once

void openSettingMap(RenderWindow &window, VideoMode &mode){
    Event event;

    Button big(mode, "BIG MAP", pathToDirectory + "fonts/font.ttf", Color::Red, 0);
    Button medium(mode, "MEDIUM MAP", pathToDirectory + "fonts/font.ttf", Color::Red, 1);
    Button small(mode, "SMALL MAP", pathToDirectory + "fonts/font.ttf", Color::Red, 2);

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

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), small.sprite)){
                soundsAll.sound[9].play();
                small.update(window);
                medium.update(window);
                big.update(window);
                sizeWindow = Vector2i(300, 300);
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), medium.sprite)){
                soundsAll.sound[9].play();
                small.update(window);
                medium.update(window);
                big.update(window);
                sizeWindow = Vector2i(500, 500);
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), big.sprite)){
                soundsAll.sound[9].play();
                small.update(window);
                medium.update(window);
                big.update(window);
                sizeWindow = Vector2i(700, 700);
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

        small.draw(window);
        medium.draw(window);
        big.draw(window);
        back.draw(window);
        window.draw(spriteCursor);

        window.display();
    }

}
