#include "background.h"
#include "init.h"
#include "draw.h"
#include "button.h"
#include "music.h"

#pragma once

void openSettingMusicGame(RenderWindow &window, VideoMode &mode){
    Event event;

    Button classic(mode, "CLASSIC", pathToDirectory + "fonts/font.ttf", Color::Red, 0);
    Button dark(mode, "DARK", pathToDirectory + "fonts/font.ttf", Color::Red, 1);
    Button light(mode, "LIGHT", pathToDirectory + "fonts/font.ttf", Color::Red, 2);
    Button nomusic(mode, "NO MUSIC", pathToDirectory + "fonts/font.ttf", Color::Red, 3);

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
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), classic.sprite)){
                soundsAll.sound[9].play();
                numberMusicGame = 0;
                classic.update(window);
                dark.update(window);
                light.update(window);
                nomusic.update(window);
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), dark.sprite)){
                soundsAll.sound[9].play();
                numberMusicGame = 1;
                classic.update(window);
                dark.update(window);
                light.update(window);
                nomusic.update(window);
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), light.sprite)){
                soundsAll.sound[9].play();
                numberMusicGame = 2;
                classic.update(window);
                dark.update(window);
                light.update(window);
                nomusic.update(window);
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), nomusic.sprite)){
                soundsAll.sound[9].play();
                numberMusicGame = 6;
                classic.update(window);
                dark.update(window);
                light.update(window);
                nomusic.update(window);
            }
        }

        window.clear(Color(50, 100, 255, 0));


        back.update(window);
        updateCursor(window, spriteCursor);

        classic.draw(window);
        dark.draw(window);
        light.draw(window);
        nomusic.draw(window);
        back.draw(window);
        window.draw(spriteCursor);

        window.display();
    }

}
