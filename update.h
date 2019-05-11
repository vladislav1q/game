#include "update.cpp"
#pragma once

bool isInside(Sprite &object, int sideOfBorder);

bool isInside(View &gameView, Sprite &object, int sideOfBorder);

bool isInside(Vector2f coordinates, float xSize, float ySize, int sideOfBorder);

bool isInside(View &gameView, Vector2f position, int sideOfBorder);

float maxmod(float a, float b);

void updateCursor(RenderWindow &window, Sprite &spriteCursor);

void addFeature(std::vector<Feature> &items, Vector2f position);

void updateFeatures(std::vector<Feature> &items, Organism &player, Time time, Bar &bulletBar, Bar &bombBar);

void gameViewUpdate(View &gameView, RenderWindow &window, Organism &player, Time time);

void strikeWeapon(View &gameView, std::vector <Weapon> &bullets, std::vector <Organism> &enemies,
                  std::vector<Corpse> &dead, std::vector<Feature> &items);

void updateBomb(std::vector<Bomb> &bombs, Time time);

void strikeBomb(const std::vector <Bomb> &bombs, std::vector <Organism> &enemies,
                std::vector<Corpse> &dead, std::vector<Feature> &items);

void deleteBomb(std::vector <Bomb> &bombs);

void moveEnemies(View &gameView, std::vector <Organism> &enemies, Organism &player, Time time);

void deleteWeapon(View &gameView, std::vector <Weapon> &bullets, Time time);

void movePlayer(View &gameView, Organism &player, std::vector<Organism> &enemies1, std::vector<Organism> &enemies2,
                std::vector<Organism> &enemies3, std::vector<Organism> &enemies4, std::vector<Organism> &enemies5,
                Time time, Bar &bubbleBar);

void clearAll(std::vector<Organism> &zombies, std::vector<Organism> &zombies1, std::vector<Organism> &zombies2, std::vector<Organism> &zombies3, std::vector<Organism> &dogs,
              std::vector<Weapon> &bullets, std::vector<Bomb> &bombs, std::vector <Corpse> &dead, std::vector<Feature> &items, std::vector<Opaque> &houses, std::vector<ConvexShape> &trapezes);

