#include "init.h"
#include "button.h"
#include "music.h"
#include <fstream>

#pragma once

bool cmp(SortMap &a, SortMap &b){
    return a.key > b.key;
}

void openLeaders(RenderWindow &window, VideoMode &mode){
    Event event;

    Font font;
    font.loadFromFile(pathToDirectory + "fonts/font.ttf");

    Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(Color(255, 120, 70, 255));
    text.setPosition(100, 50);
    text.setString("Top " + std::to_string(maxNumberLeaders) + " players of the game!");
    text.setOutlineThickness(2);
    text.setOutlineColor(Color::Red);

    //records
    Text text1;
    text1.setFont(font);
    text1.setCharacterSize(50);
    text1.setFillColor(Color::Red);
    text1.setPosition(100, 100);
    text1.setOutlineThickness(2);
    text1.setOutlineColor(Color::Black);

    //names
    Text text2;
    text2.setFont(font);
    text2.setCharacterSize(50);
    text2.setFillColor(Color::Red);
    text2.setPosition(1000, 100);
    text2.setOutlineThickness(2);
    text2.setOutlineColor(Color::Black);

    std::ifstream in;
    std::string string;

    in.open(pathToDirectory + "leaders.txt", std::ios::in);
    if(in.is_open()){
        while (getline(in, string))
        {
            if(string != "\0"){
                text1.setString(text1.getString() + "\n" + std::to_string(std::stoi(string)));

                if(string.find(" ") != std::string::npos)
                    text2.setString(text2.getString() + "\n" + string.substr(string.find(" ") + 1, 100));
            }
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
        window.draw(text1);
        window.draw(text2);
        back.draw(window);
        window.draw(spriteCursor);

        window.display();
    }

}
