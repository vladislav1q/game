#include "background.h"
#include "init.h"
#include "draw.h"
#include "button.h"
#include "music.h"
#include "settingsMusicGame.h"
#include "settingsMusicMenu.h"

#pragma once

void openSettingMusic(RenderWindow &window, VideoMode &mode){
    Event event;

    Button menu(mode, "MENU MUSIC", pathToDirectory + "fonts/font.ttf", Color::Red, 0);
    Button game(mode, "GAME MUSIC", pathToDirectory + "fonts/font.ttf", Color::Red, 1);

    Button back(mode, "BACK", pathToDirectory + "fonts/font.ttf", Color::Red);

    Sprite spriteCursor(textureCursor0);
    setCursor(window, spriteCursor);

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
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), menu.sprite)){
                soundsAll.sound[9].play();
                openSettingMusicMenu(window, mode);
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), game.sprite)){
                soundsAll.sound[9].play();
                openSettingMusicGame(window, mode);
            }
        }

        window.clear(Color(50, 100, 255, 0));


        back.update(window);
        updateCursor(window, spriteCursor);
        menu.update(window);
        game.update(window);

        menu.draw(window);
        game.draw(window);
        back.draw(window);
        window.draw(spriteCursor);

        window.display();
    }

}
