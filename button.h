#include "SFML/Graphics.hpp"

#pragma once

using namespace sf;

bool isInsideButton(Vector2f position, Sprite &sprite){
    return (position.x >= sprite.getPosition().x -  sprite.getTexture()->getSize().x / 2.0 &&
            position.x <= sprite.getPosition().x + sprite.getTexture()->getSize().x / 2.0 &&
            position.y >= sprite.getPosition().y - sprite.getTexture()->getSize().y / 2.0 &&
            position.y <= sprite.getPosition().y + sprite.getTexture()->getSize().y / 2.0);
}

class Button{
public:
    Button(VideoMode &mode, const std::string &textString, const std::string &fontString, const Color &textcolor, const int &numberButton){
        textColor = textcolor;

        texture1.loadFromFile(pathToDirectory + "pngForGame/button.png");
        texture2.loadFromFile(pathToDirectory + "pngForGame/button2.png");
        sprite.setTexture(texture1);
        sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0, sprite.getTexture()->getSize().y / 2.0);
        sprite.setPosition(mode.width / 2.0, 150 + 200 * numberButton);

        font.loadFromFile(fontString);

        text.setFont(font);
        text.setString(textString);
        text.setCharacterSize(40);
        text.setPosition(sprite.getPosition().x - sprite.getTexture()->getSize().x / 2 + 100,
                         sprite.getPosition().y - text.getCharacterSize() / 2.0);
        text.setFillColor(textcolor);
    }

    Button(VideoMode &mode, const std::string &textString, const std::string &fontString, const Color &textcolor){
        textColor = textcolor;

        texture1.loadFromFile(pathToDirectory + "pngForGame/button.png");
        texture2.loadFromFile(pathToDirectory + "pngForGame/button2.png");
        sprite.setTexture(texture1);
        sprite.setOrigin(sprite.getTexture()->getSize().x / 2.0, sprite.getTexture()->getSize().y / 2.0);
        sprite.setPosition(mode.width - sprite.getTexture()->getSize().x / 2.0, sprite.getTexture()->getSize().y / 2.0);

        font.loadFromFile(fontString);

        text.setFont(font);
        text.setString(textString);
        text.setCharacterSize(40);
        text.setPosition(sprite.getPosition().x - sprite.getTexture()->getSize().x / 2.0 + 100,
                         sprite.getPosition().y - text.getCharacterSize() / 2.0);
        text.setFillColor(textcolor);
    }

    void update(RenderWindow &window){
        if(isInsideButton(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y), sprite)){
            sprite.setScale(1.1, 1.1);
            if(Mouse::isButtonPressed(Mouse::Left)){
                sprite.setTexture(texture2);
            } else {
                sprite.setTexture(texture1);
            }
        } else{
            sprite.setTexture(texture1);
            sprite.setScale(1, 1);
        }
    }

    void draw(RenderWindow &window){
        window.draw(sprite);
        window.draw(text);
    }

    Text text;
    Font font;
    Color textColor;
    Texture texture1;
    Texture texture2;
    Sprite sprite;
};