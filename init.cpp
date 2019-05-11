#include "update.h"
#pragma once

void setCursor(RenderWindow &window, Sprite &spriteCursor){
    spriteCursor.setScale(0.05f, 0.05f);
    spriteCursor.setOrigin(spriteCursor.getPosition().x + spriteCursor.getTexture()->getSize().x
                                                          * spriteCursor.getScale().x,
                           spriteCursor.getPosition().y + spriteCursor.getTexture()->getSize().y
                                                          * spriteCursor.getScale().y);
}

Weapon initBullet(RenderWindow &window, Sprite &spriteBullet, Organism &player, int damage, float angle){
    Weapon bullet;
    Vector2f mousePosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x, window.mapPixelToCoords(sf::Mouse::getPosition(window)).y);
    bullet.weapon = spriteBullet;

    Vector2f r = Vector2f(bullet.weapon.getTexture()->getSize().x * bullet.weapon.getScale().x * 2, bullet.weapon.getTexture()->getSize().y * bullet.weapon.getScale().y * 2.7);
    float sinFi = sin(player.organism.getRotation() * 3.1415/180 + 3.1415/4);
    float cosFi = cos(player.organism.getRotation() * 3.1415/180 + 3.1415/4);
    Vector2f startAtGun(r.x*cosFi - r.y*sinFi, r.x*sinFi + r.y*cosFi);
    bullet.weapon.setPosition(player.organism.getPosition() + startAtGun);

    Vector2f direction = mousePosition - bullet.weapon.getPosition();
    Vector2f dr = angle * Vector2f(-direction.y, direction.x);
    bullet.direction = direction + dr;

    bullet.direction = norm(bullet.direction);
    bullet.speed = 1500;
    bullet.damage = damage;
    bullet.rotate(window, mousePosition);

    return bullet;
}

Bomb initBomb(RenderWindow &window, Sprite &spriteBomb, int damage){
    Bomb bomb;
    bomb.weapon = spriteBomb;
    bomb.weapon.setScale(0.3, 0.3);
    bomb.weapon.setOrigin(bomb.weapon.getTexture()->getSize().x * bomb.weapon.getScale().x,
                          bomb.weapon.getTexture()->getSize().y * bomb.weapon.getScale().y);
    bomb.weapon.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x,
                            window.mapPixelToCoords(sf::Mouse::getPosition(window)).y);
    bomb.textureNumber = 1;
    bomb.damage = damage;
    bomb.timeBuffer = 0;
    bomb.timeExplode = 0;

    return bomb;
}


