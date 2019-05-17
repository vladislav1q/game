#include "background.cpp"

#pragma once

using namespace sf;

// returns 1 if straight
// returns 2 if left
// returns 3 if right
// returns 4 if back
int getProbability(float probabilityStraight, float probabilityLeft, float probabilityRight, float proprobabilityBack);

int getProbability(float probability);

void setBeach(int x, int y, int type, float speed);

void setRiverLRLine(int startX1, int startY1, int width);

void setRiverLRBridge(int x, int y, int width, int &riverLength);

void generateRiverLR();

void setRiverUDLine(int startX1, int startY1, int width);

void setRiverUDBridge(int x, int y, int width, int &riverLength);

void generateRiverUD();

void generateBeach();

void generateGrassBeach();

void generateGrassBeachCoast();

void generateCoast();

void generateBeachFlower();

void generateGrassFlower();

bool isEmptyBackground(int type, Vector2i position, Vector2i size);

void generateHouse();

void setCrossAbility();

void generateBox();

void setGrass();

void createTree1();
void createTree2();
void createTree3();
void createTree4();
void createTree5();

void generateTree(int type, std::vector<Vector2f> &tree);

void setBackground(std::vector<Opaque> &houses);


//very slow
//works if the map is less than 800*800
//do not start in thread if map is more than 600*600
void setMinimap(MinimapThread *minimap);

