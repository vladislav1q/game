#include "SFML/Graphics.hpp"

#pragma once

void endGame(RenderWindow &window, View &gameView, Time time6, Sprite &spriteCursor){

    window.setView(gameView);
    Event event;

    soundsAll.stop();
    soundsAll.sound[8].play();

    Font font;
    Text text;
    font.loadFromFile(pathToDirectory + "fonts/font.ttf");
    text.setFont(font);
    text.setCharacterSize(50);

    text.setString("         Game over!\nYourTime is " + std::to_string((int)time6.asSeconds()/60) + " min  " +
                   std::to_string((int)time6.asSeconds() % 60) + " sec");

    text.setFillColor(Color(255, 120, 70, 255));
    text.setStyle(Text::Bold | Text::Italic);
    text.setPosition(gameView.getCenter().x - 300, gameView.getCenter().y - 300);
    text.setOutlineThickness(2);
    text.setOutlineColor(Color::Red);

    Text name;
    font.loadFromFile(pathToDirectory + "fonts/font.ttf");
    name.setFont(font);
    name.setCharacterSize(50);
    name.setFillColor(Color(255, 120, 70, 255));
    name.setStyle(Text::Bold | Text::Italic);
    name.setPosition(gameView.getCenter().x - 300, gameView.getCenter().y - 150);
    name.setString("Enter your name and press ESC.\n\n");

    SortMap tmp;
    tmp.key = (int)time6.asSeconds();


//            clearAll(zombies, zombies1, zombies2, zombies3, dogs, bullets, bombs, dead, items);

    while (window.isOpen()){

        window.clear(Color(50, 100, 255, 0));
        window.draw(text);
        window.draw(name);
        window.display();

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
//                clearAll(zombies, zombies1, zombies2, zombies3, dogs, bullets, bombs, dead, items, houses, trapezes);
                window.close();
            }

            if (event.type == event.MouseButtonReleased)
                spriteCursor.setTexture(textureCursor0);
            if (event.type == event.MouseButtonPressed)
                spriteCursor.setTexture(textureCursor1);

            if (event.type == sf::Event::TextEntered)
            {

                if (event.text.unicode < 128)
                {
                    //if name is written
                    if(event.text.unicode == 27 && !tmp.string.empty()){
                        leaders.push_back(tmp);

                        std::ifstream in;
                        std::ofstream out;
                        std::string string;

                        in.open(pathToDirectory + "leaders.txt", std::ios::in);
                        if(in.is_open()){
                            while (getline(in, string))
                            {
                                if(string != "\0"){
                                    tmp.key = std::stoi(string);

                                    if(string.find(" ") != std::string::npos)
                                        tmp.string = string.substr(string.find(" ") + 1, 100);
                                    else
                                        tmp.string = "ERROR";

                                    leaders.push_back(tmp);
                                }
                            }
                        }
                        in.close();

                        //sort
                        std::sort(leaders.begin(), leaders.end(), cmp);

                        out.open(pathToDirectory + "leaders.txt", std::ios::out);

                        int number = 0;
                        for(auto &i : leaders){
                            out << i.key <<" " + i.string << std::endl;
                            number++;
                            if(number > maxNumberLeaders - 1)
                                break;
                        }
                        out.close();
                        leaders.clear();
                        //clearAll(zombies, zombies1, zombies2, zombies3, dogs, bullets, bombs, dead, items, houses, trapezes);
                        musicAll.music[numberMusicGame].pause();
                        return;

                        //if backspace
                    } else if(event.text.unicode == 8 && !tmp.string.empty()){
                        tmp.string.erase(tmp.string.end() - 1);
                        name.setString("Enter your name and press ESC.\n\n" + tmp.string);

                        //else add symbols to name
                    } else if(isalpha(static_cast<char>(event.text.unicode)) && tmp.string.size() < maxLengthName){
                        tmp.string += static_cast<char>(event.text.unicode);
                        name.setString("Enter your name and press ESC.\n\n" + tmp.string);
                    }
                }
            }
        }

    }
}