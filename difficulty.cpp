#include "init.h"
#include "game.cpp"
#include "button.h"
#include "pages.h"
#include "multiplayer.cpp"

#pragma once

using namespace sf;

void difficulty(RenderWindow &window, VideoMode &mode){

    Button easy(mode, "EASY", pathToDirectory + "fonts/font.ttf", Color::Red, 0);
    Button medium(mode, "MEDIUM", pathToDirectory + "fonts/font.ttf", Color::Red, 1);
    Button hard(mode, "HARD", pathToDirectory + "fonts/font.ttf", Color::Red, 2);
    Button multiplayer(mode, "MULTIPLAYER", pathToDirectory + "fonts/font.ttf", Color::Red, 3);
    Button back(mode, "BACK", pathToDirectory + "fonts/font.ttf", Color::Red);

    Sprite spriteCursor(textureCursor0);
    setCursor(window, spriteCursor);

    Event event;

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
               isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), easy.sprite)){
                soundsAll.sound[9].play();
                musicAll.music[numberMusicMenu].pause();
                WindowSent windowSent(window, mode, 0.2);
                Thread thread(&openGame, windowSent);
                thread.launch();
                thread.wait();
                musicAll.music[numberMusicMenu].play();

                return;
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), medium.sprite)){
                soundsAll.sound[9].play();
                musicAll.music[numberMusicMenu].pause();
                WindowSent windowSent(window, mode, 1);
                Thread thread(&openGame, windowSent);
                thread.launch();
                thread.wait();
                musicAll.music[numberMusicMenu].play();

                return;
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), hard.sprite)){
                soundsAll.sound[9].play();
                musicAll.music[numberMusicMenu].pause();
                WindowSent windowSent(window, mode, 5);
                Thread thread(&openGame, windowSent);
                thread.launch();
                thread.wait();
                musicAll.music[numberMusicMenu].play();

                return;
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), multiplayer.sprite)){
                soundsAll.sound[9].play();
                musicAll.music[numberMusicMenu].pause();
                WindowSent windowSent(window, mode, 1);
                Thread thread(&openMultiplayer, windowSent);
                thread.launch();
                thread.wait();
                musicAll.music[numberMusicMenu].play();

                return;
            }

            if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
               isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), back.sprite)){
                soundsAll.sound[9].play();
                return;
            }
        }


        easy.update(window);
        medium.update(window);
        hard.update(window);
        multiplayer.update(window);
        back.update(window);
        updateCursor(window, spriteCursor);

        window.clear(Color(50, 100, 255, 0));
        easy.draw(window);
        medium.draw(window);
        hard.draw(window);
        multiplayer.draw(window);
        back.draw(window);
        window.draw(spriteCursor);

        window.display();
    }
}
