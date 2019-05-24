#include "background.h"
#include "init.h"
#include "draw.h"
#include "settingsMap.h"
#include "settingsMusic.h"
#include "settingsVolume.h"

#pragma once

void openSetting(RenderWindow &window, VideoMode &mode){
    Event event;

    Button map(mode, "MAP SETTINGS", pathToDirectory + "fonts/font.ttf", Color::Red, 0);
    Button volume(mode, "Volume SETTINGS", pathToDirectory + "fonts/font.ttf", Color::Red, 1);
    Button music(mode, "MUSIC SETTINGS", pathToDirectory + "fonts/font.ttf", Color::Red, 2);

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
               isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), map.sprite)){
                soundsAll.sound[9].play();
                openSettingMap(window, mode);
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), volume.sprite)){
                soundsAll.sound[9].play();
                openSettingVolume(window, mode);
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), music.sprite)){
                soundsAll.sound[9].play();
                openSettingMusic(window, mode);
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

        map.update(window);
        volume.update(window);
        music.update(window);

        map.draw(window);
        volume.draw(window);
        music.draw(window);
        back.draw(window);
        window.draw(spriteCursor);

        window.display();
    }

}
