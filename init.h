#include "init.cpp"

#pragma once

void setCursor(RenderWindow &window, Sprite &spriteCursor);

Weapon initBullet(RenderWindow &window, Sprite &spriteBullet, Organism &player, int damage, float angle);

Bomb initBomb(RenderWindow &window, Sprite &spriteBomb, int damage);