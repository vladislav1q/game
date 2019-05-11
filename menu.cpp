#include "pages.h"
#include "button.h"
#include "difficulty.cpp"

#pragma once

using namespace sf;

void menu(RenderWindow &window, VideoMode &mode){
    window.setMouseCursorVisible(false);
    View view(sf::FloatRect(0, 0, mode.width, mode.height));
    window.setView(view);

    Button startGame(mode, "START GAME", pathToDirectory + "fonts/font.ttf", Color::Red, 0);
    Button settings(mode, "SETTINGS", pathToDirectory + "fonts/font.ttf", Color::Red, 1);
    Button rules(mode, "HOW TO PLAY?", pathToDirectory + "fonts/font.ttf", Color::Red, 2);
    Button rating(mode, "RATING", pathToDirectory + "fonts/font.ttf", Color::Red, 3);
    Button exit(mode, "EXIT", pathToDirectory + "fonts/font.ttf", Color::Red, 4);

//    Texture textureCursor0;
//    Texture textureCursor1;
    textureCursor0.loadFromFile(pathToDirectory + "pngForGame/cursor0.png");
    textureCursor1.loadFromFile(pathToDirectory + "pngForGame/cursor1.png");
    Sprite spriteCursor(textureCursor0);
    setCursor(window, spriteCursor);

    Event event;

    //Sounds


    musicAll.music[numberMusicMenu].play();


    while(window.isOpen()){
        if(Keyboard::isKeyPressed(Keyboard::Space))
            musicAll.music[numberMusicMenu].pause();


        while(window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }

            if (event.type == event.MouseButtonReleased)
                spriteCursor.setTexture(textureCursor0);
            if (event.type == event.MouseButtonPressed)
                spriteCursor.setTexture(textureCursor1);


            if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
               isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), startGame.sprite)){
                soundsAll.sound[9].play();
                difficulty(window, mode);

                window.setView(view);
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), rules.sprite)){
                soundsAll.sound[9].play();
                openRule(window, mode);
            }


            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), settings.sprite)){
                soundsAll.sound[9].play();
                openSetting(window, mode);
            }

            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), exit.sprite)){
                soundsAll.sound[9].play();
                return;
            }


            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left &&
                    isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), rating.sprite)){
                soundsAll.sound[9].play();
                openLeaders(window, mode);
            }
        }


        startGame.update(window);
        settings.update(window);
        rules.update(window);
        rating.update(window);
        exit.update(window);
        updateCursor(window, spriteCursor);

        window.clear(Color(50, 100, 255, 0));
        startGame.draw(window);
        settings.draw(window);
        rules.draw(window);
        rating.draw(window);
        exit.draw(window);
        window.draw(spriteCursor);
        window.display();
    }
}
