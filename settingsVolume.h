#include "background.h"
#include "init.h"
#include "draw.h"
#include "button.h"
#include "music.h"

#pragma once

void openSettingVolume(RenderWindow &window, VideoMode &mode){
    Event event;

    Button loud(mode, "LOUD", pathToDirectory + "fonts/font.ttf", Color::Red, 0);
    Button medium(mode, "MEDIUM", pathToDirectory + "fonts/font.ttf", Color::Red, 1);
    Button quiet(mode, "QUIET", pathToDirectory + "fonts/font.ttf", Color::Red, 2);
    Button nomusic(mode, "SOUNDLESS", pathToDirectory + "fonts/font.ttf", Color::Red, 3);

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
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), loud.sprite)){
                soundsAll.sound[9].play();
                musicAll.setVolume(100);
                soundsAll.setVolume(100);
                loud.update(window);
                medium.update(window);
                quiet.update(window);
                nomusic.update(window);
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), medium.sprite)){
                soundsAll.sound[9].play();
                musicAll.setVolume(70);
                soundsAll.setVolume(70);
                loud.update(window);
                medium.update(window);
                quiet.update(window);
                nomusic.update(window);
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), quiet.sprite)){
                soundsAll.sound[9].play();
                musicAll.setVolume(30);
                soundsAll.setVolume(30);
                loud.update(window);
                medium.update(window);
                quiet.update(window);
                nomusic.update(window);
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), nomusic.sprite)){
                soundsAll.sound[9].play();
                musicAll.setVolume(0);
                soundsAll.setVolume(0);
                loud.update(window);
                medium.update(window);
                quiet.update(window);
                nomusic.update(window);
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

        loud.draw(window);
        medium.draw(window);
        quiet.draw(window);
        nomusic.draw(window);
        back.draw(window);
        window.draw(spriteCursor);

        window.display();
    }

}
