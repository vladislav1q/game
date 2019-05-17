#include <iostream>
#include <SFML/Graphics.hpp>
#include "random"
#include "paths.h"
#include "shadows.h"


#pragma once

using namespace sf;

float minimapScale = 0.2;   // = k/sizeTile, k = int
int minimapTransparancy = 255;
float minimapSize = 0.2;

float riverSpeed = 0.3;
float sandSpeed = 0.65;
float grassSpeed = 0.9;
float grassBeachSpeed = 0.8;
float roadSpeed = 1.0;
int bridgeFrequancy = 150;
int bridgeWidth = 10;
int maxRiverWidth = 10; // >=6

Texture textureTree1;
Sprite spriteTree1;
Texture textureTree2;
Sprite spriteTree2;
Texture textureTree3;
Sprite spriteTree3;
Texture textureTree4;
Sprite spriteTree4;
Texture textureTree5;
Sprite spriteTree5;

class Background {
public:
    Background(float speed1, bool crossPlayer1, bool crossEnemy1, bool crossWeapon1, unsigned int type1) :
        speed(speed1),
        crossPlayer(crossPlayer1),
        crossEnemy(crossEnemy1),
        crossWeapon(crossWeapon1),
        type(type1){};

    Background(){
        crossEnemy = false;
        crossPlayer = false;
        crossRay = false;
        speed = 1.f;
    }
    Background(bool a){
        crossEnemy = a;
        crossPlayer = a;
        crossRay = a;
        speed = 1.f;
    }
    float speed;          // Ex. you go through the water slower than on grass
    bool crossPlayer;   //  ability for the player.organism to go through this object
    bool crossEnemy;    //  ability for the zombies and other enemies to go through this object
    bool crossRay;
    bool crossWeapon;
    unsigned int type;           //to compare with others
};

class texturePath{
public:
    texturePath(const std::string str, const bool a){
        path = str;
        abilityCross = a;
    }

    bool abilityCross;
    std::string path;
    Texture texture;
};

class BackgroundType{
public:
    Background background;
    Sprite picture;
};

Background background[1000][1000];
std::map <int, BackgroundType> backgroundTypes;
std::vector<Vector2f> trees1;
std::vector<Vector2f> trees2;
std::vector<Vector2f> trees3;
std::vector<Vector2f> trees4;
std::vector<Vector2f> trees5;

std::vector<texturePath> textures = {
        texturePath(pathToDirectory + "pngForGame/box/boxLD.png", false),                             //0
        texturePath(pathToDirectory + "pngForGame/box/boxRD.png", false),                             //
        texturePath(pathToDirectory + "pngForGame/box/boxLU.png", false),                             //
        texturePath(pathToDirectory + "pngForGame/box/boxRU.png", false),                             //
        texturePath(pathToDirectory + "pngForGame/fense/fenseCornerLD.png", false),                   //4
        texturePath(pathToDirectory + "pngForGame/fense/fenseCornerRD.png", false),                   //
        texturePath(pathToDirectory + "pngForGame/fense/fenseCornerLU.png", false),                   //
        texturePath(pathToDirectory + "pngForGame/fense/fenseCornerRU.png", false),                   //
        texturePath(pathToDirectory + "pngForGame/fense/fenseHorisontal.png", false),                 //
        texturePath(pathToDirectory + "pngForGame/fense/fenseVertical.png", false),                   //9
        texturePath(pathToDirectory + "pngForGame/pavement/pavementBorderDown.png", true),            //
        texturePath(pathToDirectory + "pngForGame/pavement/pavementBorderLeft.png", true),            //
        texturePath(pathToDirectory + "pngForGame/pavement/pavementBorderUp.png", true),              //
        texturePath(pathToDirectory + "pngForGame/pavement/pavementBorderRight.png", true),           //
        texturePath(pathToDirectory + "pngForGame/pavement/pavementHorisontal.png", true),            //14
        texturePath(pathToDirectory + "pngForGame/pavement/pavementVertical.png", true),              //
        texturePath(pathToDirectory + "pngForGame/grassBeach.png", true),                             //
        texturePath(pathToDirectory + "pngForGame/grassBeachFlower.png", true),                       //
        texturePath(pathToDirectory + "pngForGame/river.png", false),                                  //
        texturePath(pathToDirectory + "pngForGame/road.png", true),                                   //19
        texturePath(pathToDirectory + "pngForGame/sand.png", true),                                   //
        texturePath(pathToDirectory + "pngForGame/grass.png", true),                                  //
        texturePath(pathToDirectory + "pngForGame/house/houseBorderDown.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseBorderLeft.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseBorderUp.png", false),                    //24
        texturePath(pathToDirectory + "pngForGame/house/houseBorderRight.png", false),                 //
        texturePath(pathToDirectory + "pngForGame/house/houseCornerLD.png", false),                    //
        texturePath(pathToDirectory + "pngForGame/house/houseCornerLU.png", false),                    //
        texturePath(pathToDirectory + "pngForGame/house/houseCornerRU.png", false),                    //
        texturePath(pathToDirectory + "pngForGame/house/houseCornerRD.png", false),                    //29
        texturePath(pathToDirectory + "pngForGame/house/houseDiagonalLD-RU.png", false),               //
        texturePath(pathToDirectory + "pngForGame/house/houseDiagonalLU-RD.png", false),               //
        texturePath(pathToDirectory + "pngForGame/house/houseHorisontal.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseVertical.png", false),                    //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderDown.png", false),                //34
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderLeft.png", false),                //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderUp.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderRight.png", false),               //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderDown1.png", false),                //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderLeft1.png", false),                //39
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderUp1.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderRight1.png", false),               //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderDown2.png", false),                //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderLeft2.png", false),                //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderUp2.png", false),                  //44
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderRight2.png", false),               //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderDown3.png", false),                //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderLeft3.png", false),                //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderUp3.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderRight3.png", false),               //49
        texturePath(pathToDirectory + "pngForGame/house/houseHorisontalLD.png", false),                //
        texturePath(pathToDirectory + "pngForGame/house/houseHorisontalLU.png", false),                //
        texturePath(pathToDirectory + "pngForGame/house/houseHorisontalRU.png", false),                //
        texturePath(pathToDirectory + "pngForGame/house/houseHorisontalRD.png", false),                //
        texturePath(pathToDirectory + "pngForGame/house/houseDiagonalRD-LU.png", false),               //54
        texturePath(pathToDirectory + "pngForGame/house/houseDiagonalRU-LD.png", false),               //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderLD.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderLU.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderRU.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderRD.png", false),                  //59
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderLD1.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderLU1.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderRU1.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderRD1.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderLD2.png", false),                  //64
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderLU2.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderRU2.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderRD2.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderLD3.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderLU3.png", false),                  //69
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderRU3.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseInBorderRD3.png", false),                  //
        texturePath(pathToDirectory + "pngForGame/house/houseVerticalLD.png", false),                //
        texturePath(pathToDirectory + "pngForGame/house/houseVerticalLU.png", false),                //
        texturePath(pathToDirectory + "pngForGame/house/houseVerticalRU.png", false),                //74
        texturePath(pathToDirectory + "pngForGame/house/houseVerticalRD.png", false),               //
        texturePath(pathToDirectory + "pngForGame/house/houseHorisontal0.png", false),                 //
        texturePath(pathToDirectory + "pngForGame/house/houseHorisontal1.png", false),                 //
        texturePath(pathToDirectory + "pngForGame/house/houseHorisontal2.png", false),                 //
        texturePath(pathToDirectory + "pngForGame/house/houseHorisontal3.png", false),                 //79
        texturePath(pathToDirectory + "pngForGame/grassFlower.png", true)                             //
};

// returns 1 if straight
// returns 2 if left
// returns 3 if right
// returns 4 if back
int getProbability(float probabilityStraight, float probabilityLeft, float probabilityRight, float proprobabilityBack){
    //srand(time(NULL));

    // 1000000 delete

    int randomNumber = rand() % 1000000;

    if(probabilityLeft + probabilityRight + probabilityStraight + proprobabilityBack != 1){
        std::cout << "Error with probability set" << std::endl;
        return 0;
    }

    if(randomNumber <= 1000000*probabilityStraight)
        return 1;
    else if(randomNumber <= 1000000*(probabilityStraight + probabilityLeft))
        return 2;
    else if(randomNumber <= 1000000*(probabilityStraight + probabilityLeft + probabilityRight))
        return 3;
    else
        return 4;
}

int getProbability(float probability){
    return ((rand() % 1000000) < 1000000 * probability);
}

void setBeach(int x, int y, int type, float speed){
    background[x][y].type = type;
    background[x][y].crossEnemy = true;
    background[x][y].crossPlayer = true;
    background[x][y].speed = speed;
}

void setRiverLRLine(int startX1, int startY1, int width){
    for(int i = -width; i <= width; i++){
        background[startX1][startY1 - i].type = 18;
        background[startX1][startY1 - i].crossPlayer = true;
        background[startX1][startY1 - i].crossEnemy = true;
        background[startX1][startY1 - i].speed = riverSpeed;
    }
}

void setRiverLRBridge(int x, int y, int width, int &riverLength){
    width = 2 * width + 14;
    if(riverLength > bridgeFrequancy && x > bridgeWidth && x < sizeWindow.x - bridgeWidth && y > width && y < sizeWindow.y - width){
        riverLength -= bridgeFrequancy;
        for(int i = -bridgeWidth / 2; i < bridgeWidth / 2; i++){
            for(int j = -width / 2; j < width / 2; j++){
                setBeach(x + i, y + j, 20, sandSpeed);
            }
        }
    }
}

void generateRiverLR() {
    int startX1 = 0;;
    int startY1 = rand() % (sizeWindow.y - 20) + 10;
    unsigned int width = rand() % (maxRiverWidth - 6) + 6;
    int riverLength = 0;

    setRiverLRLine(startX1, startY1, width);
    riverLength++;

    while (true) {
        float straight = 0.4;
        float left = (rand() % (int)(100 - straight*100))/100.0;
        float right = 1 - straight - left;
        int probability = getProbability(straight, left, right, 0);


        //straight
        if (probability == 1) {
            if (startX1 < sizeWindow.x) {
                startX1++;
                setRiverLRLine(startX1, startY1, width);
                riverLength++;
                setRiverLRBridge(startX1, startY1, width, riverLength);
            } else
                break;
            //right
        } else if (probability == 3) {
            if (startY1 < sizeWindow.y - (width + 1)) {
                startY1++;
                setRiverLRLine(startX1, startY1, width);
                riverLength++;
                setRiverLRBridge(startX1, startY1, width, riverLength);
            } else
                continue;
            //left
        } else if (probability == 2) {
            if (startY1 > (width)) {
                startY1--;
                setRiverLRLine(startX1, startY1, width);
                riverLength++;
                setRiverLRBridge(startX1, startY1, width, riverLength);
            } else
                continue;
        }
            //right
        else if (probability == 4) {
            if (startX1 > -1) {
                startX1--;
                setRiverLRLine(startX1, startY1, width);
                riverLength++;
                setRiverLRBridge(startX1, startY1, width, riverLength);
            } else
                continue;
        }
    }
}

void setRiverUDLine(int startX1, int startY1, int width){
    for(int i = -width; i <= width; i++){
        background[startX1 - i][startY1].type = 18;
        background[startX1 - i][startY1].crossPlayer = true;
        background[startX1 - i][startY1].crossEnemy = true;
        background[startX1 - i][startY1].speed = riverSpeed;
    }
}

void setRiverUDBridge(int x, int y, int width, int &riverLength){
    width = 2 * width + 14;
    if(riverLength > bridgeFrequancy && y > bridgeWidth && y < sizeWindow.y - bridgeWidth && x > width && x < sizeWindow.x - width){
        riverLength -= bridgeFrequancy;
        for(int i = -bridgeWidth / 2; i < bridgeWidth / 2; i++){
            for(int j = -width / 2; j < width / 2; j++){
                setBeach(x + j, y + i, 20, sandSpeed);
            }
        }
    }
}

void generateRiverUD() {
    int startX1 = rand() % (sizeWindow.x - 20) + 10;
    int startY1 = 0;
    unsigned int width = rand() % (maxRiverWidth - 6) + 6;
    int riverLength = 0;

    setRiverUDLine(startX1, startY1, width);
    riverLength++;

    while (true) {
        float straight = 0.4;
        float left = (rand() % (int)(100 - straight*100)) / 100.0;
        float right = 1 - straight - left;
        int probability = getProbability(straight, left, right, 0);

        //straight
        if (probability == 1) {
            if (startY1 < sizeWindow.y) {
                startY1++;
                setRiverUDLine(startX1, startY1, width);
                riverLength++;
                setRiverUDBridge(startX1, startY1, width, riverLength);
            } else
                break;
            //right
        } else if (probability == 3) {
            if (startX1 > width) {
                startX1--;
                setRiverUDLine(startX1, startY1, width);
                riverLength++;
                setRiverUDBridge(startX1, startY1, width, riverLength);
            } else
                continue;
            //left
        } else if (probability == 2) {
            if (startX1 < sizeWindow.x - (width + 1)) {
                startX1++;
                setRiverUDLine(startX1, startY1, width);
                riverLength++;
                setRiverUDBridge(startX1, startY1, width, riverLength);
            } else
                continue;
        }
            //back
        else if (probability == 4) {
            if (startY1 > -1) {
                startY1--;
                setRiverUDLine(startX1, startY1, width);
                riverLength++;
                setRiverUDBridge(startX1, startY1, width, riverLength);
            } else
                continue;
        }
    }
}

void generateBeach(){
    for (int i = 0; i < sizeWindow.x; i++) {
        for (int j = 0; j < sizeWindow.y; j++)
            if(background[i][j].type == 20){
                if(i > 0) {

                    if(background[i-1][j].type == 21)
                        setBeach(i-1, j, 200, sandSpeed);
                    //background[i-1][j].type = 200;

                    if(j > 0 && background[i-1][j-1].type == 21)
                        setBeach(i-1, j-1, 200, sandSpeed);
                    //background[i-1][j-1].type = 200;

                    if(j < sizeWindow.y - 1 && background[i-1][j+1].type == 21)
                        setBeach(i-1, j+1, 200, sandSpeed);
                    //background[i-1][j+1].type = 200;
                }

                if(i < sizeWindow.x - 1) {
                    if(background[i+1][j].type == 21)
                        setBeach(i+1, j, 200, sandSpeed);
                    //background[i+1][j].type = 200;

                    if(j > 0 && background[i+1][j-1].type == 21)
                        setBeach(i+1, j-1, 200, sandSpeed);
                    //background[i+1][j-1].type = 200;

                    if(j < sizeWindow.y - 1 && background[i+1][j+1].type == 21)
                        setBeach(i+1, j+1, 200, sandSpeed);
                    //background[i+1][j+1].type = 200;
                }
                if(j > 0 && background[i][j-1].type == 21)
                    setBeach(i, j-1, 200, sandSpeed);
                //background[i][j-1].type = 200;

                if(j < sizeWindow.y - 1 && background[i][j+1].type == 21)
                    setBeach(i, j+1, 200, sandSpeed);
                //background[i][j+1].type = 200;
            }
    }
    for (int i = 0; i < sizeWindow.x; i++) {
        for (int j = 0; j < sizeWindow.y; j++)
            if(background[i][j].type == 200)
                background[i][j].type = 20;
    }
}

void generateGrassBeach(){
    for (int i = 0; i < sizeWindow.x; i++) {
        for (int j = 0; j < sizeWindow.y; j++)
            if(background[i][j].type == 16){
                if(i > 0) {

                    if(background[i-1][j].type == 21)
                        setBeach(i-1, j, 200, grassBeachSpeed);
                    //background[i-1][j].type = 100;

                    if(j > 0 && background[i-1][j-1].type == 21)
                        setBeach(i-1, j-1, 200, grassBeachSpeed);
                    //background[i-1][j-1].type = 100;

                    if(j < sizeWindow.y - 1 && background[i-1][j+1].type == 21)
                        setBeach(i-1, j+1, 200, grassBeachSpeed);
                    //background[i-1][j+1].type = 100;
                }

                if(i < sizeWindow.x - 1) {
                    if(background[i+1][j].type == 21)
                        setBeach(i+1, j, 200, grassBeachSpeed);
                    //background[i+1][j].type = 100;

                    if(j > 0 && background[i+1][j-1].type == 21)
                        setBeach(i+1, j-1, 200, grassBeachSpeed);
                    //background[i+1][j-1].type = 100;

                    if(j < sizeWindow.y - 1 && background[i+1][j+1].type == 21)
                        setBeach(i+1, j+1, 200, grassBeachSpeed);
                    //background[i+1][j+1].type = 100;
                }
                if(j > 0 && background[i][j-1].type == 21)
                    setBeach(i, j-1, 200, grassBeachSpeed);
                //background[i][j-1].type = 100;

                if(j < sizeWindow.y - 1 && background[i][j+1].type == 21)
                    setBeach(i, j+1, 200, grassBeachSpeed);
                //background[i][j+1].type = 100;
            }
    }
    for (int i = 0; i < sizeWindow.x; i++) {
        for (int j = 0; j < sizeWindow.y; j++)
            if(background[i][j].type == 200)
                background[i][j].type = 16;
    }
}

void generateGrassBeachCoast(){
    for (int i = 0; i < sizeWindow.x; i++) {
        for (int j = 0; j < sizeWindow.y; j++)
            if(background[i][j].type == 20){
                if(i > 0) {

                    if(background[i-1][j].type == 21)
                        setBeach(i-1, j, 16, grassBeachSpeed);
                    //background[i-1][j].type = 16;

                    if(j > 0 && background[i-1][j-1].type == 21)
                        setBeach(i-1, j-1, 16, grassBeachSpeed);
                    //background[i-1][j-1].type = 16;

                    if(j < sizeWindow.y - 1 && background[i-1][j+1].type == 21)
                        setBeach(i-1, j+1, 16, grassBeachSpeed);
                    //background[i-1][j+1].type = 16;
                }
                if(i < sizeWindow.x - 1) {
                    if(background[i+1][j].type == 21)
                        setBeach(i+1, j, 16, grassBeachSpeed);
                    //background[i+1][j].type = 16;

                    if(j > 0 && background[i+1][j-1].type == 21)
                        setBeach(i+1, j-1, 16, grassBeachSpeed);
                    //background[i+1][j-1].type = 16;

                    if(j < sizeWindow.y - 1 && background[i+1][j+1].type == 21)
                        setBeach(i+1, j+1, 16, grassBeachSpeed);
                    //background[i+1][j+1].type = 16;
                }
                if(j > 0 && background[i][j-1].type == 21)
                    setBeach(i, j-1, 16, grassBeachSpeed);
                //background[i][j-1].type = 16;

                if(j < sizeWindow.y - 1 && background[i][j+1].type == 21)
                    setBeach(i, j+1, 16, grassBeachSpeed);
                //background[i][j+1].type = 16;
            }
    }

}

void generateCoast(){

    //Beautiful lakes in sand

    //Do not delete!!!

//    for (int i = 0; i < sizeWindow.x; i++) {
//        for (int j = 0; j < sizeWindow.y; j++)
//            if(background[i][j].type == 18){
//                if(i > 0) {
//                    background[i-1][j].type = 20;
//                    if(j > 0)
//                        background[i-1][j-1].type = 20;
//                    if(j < sizeWindow.y - 1)
//                        background[i-1][j+1].type = 20;
//                }
//                if(i < sizeWindow.x - 1) {
//                    background[i+1][j].type = 20;
//                    if(j > 0)
//                        background[i+1][j-1].type = 20;
//                    if(j < sizeWindow.y - 1)
//                        background[i+1][j+1].type = 20;
//                }
//                if(j > 0)
//                    background[i][j-1].type = 20;
//                if(j < sizeWindow.y - 1)
//                    background[i][j+1].type = 20;
//            }
//    }
    //river coast
    for (int i = 0; i < sizeWindow.x; i++) {
        for (int j = 0; j < sizeWindow.y; j++)
            if(background[i][j].type == 18){
                if(i > 0) {

                    if(background[i-1][j].type == 21)
                        setBeach(i-1, j, 20, sandSpeed);
                    //background[i-1][j].type = 20;

                    if(j > 0 && background[i-1][j-1].type == 21)
                        setBeach(i-1, j-1, 20, grassBeachSpeed);
                    //background[i-1][j-1].type = 20;

                    if(j < sizeWindow.y - 1 && background[i-1][j+1].type == 21)
                        setBeach(i-1, j+1, 20, sandSpeed);
                    //background[i-1][j+1].type = 20;
                }

                if(i < sizeWindow.x - 1) {
                    if(background[i+1][j].type == 21)
                        setBeach(i+1, j, 20, sandSpeed);
                    //background[i+1][j].type = 20;

                    if(j > 0 && background[i+1][j-1].type == 21)
                        setBeach(i+1, j-1, 20, sandSpeed);
                    //background[i+1][j-1].type = 20;

                    if(j < sizeWindow.y - 1 && background[i+1][j+1].type == 21)
                        setBeach(i+1, j+1, 20, sandSpeed);
                    //background[i+1][j+1].type = 20;
                }
                if(j > 0 && background[i][j-1].type == 21)
                    setBeach(i, j-1, 20, sandSpeed);
                //background[i][j-1].type = 20;

                if(j < sizeWindow.y - 1 && background[i][j+1].type == 21)
                    setBeach(i, j+1, 20, sandSpeed);
                //background[i][j+1].type = 20;
            }
    }

}

void generateBeachFlower(){
    for (int i = 0; i < sizeWindow.x; i++) {
        for (int j = 0; j < sizeWindow.y; j++)
            if(background[i][j].type == 16){
                if(getProbability(0.02))
                    background[i][j].type = 17;
            }
    }
}

void generateGrassFlower(){
    for (int i = 0; i < sizeWindow.x; i++) {
        for (int j = 0; j < sizeWindow.y; j++)
            if(background[i][j].type == 21){
                if(getProbability(0.005))
                    background[i][j].type = 80;
            }
    }
}

bool isEmptyBackground(int type, Vector2i position, Vector2i size){

    for(int i = position.x; i < position.x + size.x; i++){
        for(int j = position.y; j < position.y + size.y; j++){
            if(background[i][j].type != type)
                return false;
        }
    }

    return true;
}

void generateHouse(std::vector<Opaque> &houses){

    //srand(time(NULL));
    unsigned int startX1 = 0, startY1 = 0;
    Vector2i territoryHouse(rand() % 10 + 5, rand() % 10 + 5);
    //unsigned int territoryHouse = rand() % 10 + 5;
    unsigned int firstTosecondFloor = rand() % 5 + 2;
    unsigned  int secondFloor = rand() % 5 + 1;
    Vector2i sizeHouse(2*secondFloor + 4 + 2*firstTosecondFloor + 2*territoryHouse.x, 2*secondFloor + 4 + 2*firstTosecondFloor + 2*territoryHouse.y);


    for(int k = 0; k < 1000000; k++){
        startX1 = rand() % (sizeWindow.x - 40) + 20;
        startY1 = rand() % (sizeWindow.x - 40) + 20;
//        startX1 = 0;
//        startY1 = 0;
        if(isEmptyBackground(21, Vector2i(startX1, startY1), sizeHouse)){
            Vector2f a((startX1 + territoryHouse.x) * sizeTile, (startY1 + territoryHouse.y)* sizeTile);
            Vector2f b ((sizeHouse.x -  2*territoryHouse.x)* sizeTile, (sizeHouse.y - 2*territoryHouse.y) * sizeTile);
            houses.push_back(Opaque(a, b));
            break;
        }
    }

    //fense

    //corners
    background[startX1][startY1].type = 6;
    background[startX1 + sizeHouse.x - 1][startY1].type = 7;
    background[startX1 + sizeHouse.x - 1][startY1 + sizeHouse.y - 1].type = 5;
    background[startX1][startY1 + sizeHouse.y - 1].type = 4;

    //horisontal
    for(int i = startX1 + 1; i < startX1 + sizeHouse.x - 1; i++){
        background[i][startY1].type = 8;
        background[i][startY1 + sizeHouse.y - 1].type = 8;
    }

    //vertical
    for(int i = startY1 + 1; i < startY1 + sizeHouse.y - 1; i++){
        background[startX1][i].type = 9;
        background[startX1 + sizeHouse.x - 1][i].type = 9;
    }

    //doors

    //horisontal
    if(getProbability(0.8)){
        background[startX1 + sizeHouse.x / 2][startY1].type = 21;
        background[startX1 + sizeHouse.x / 2 - 1][startY1].type = 21;
        background[startX1 + sizeHouse.x / 2 + 1][startY1].type = 21;
    }
    if(getProbability(0.8)){
        background[startX1 + sizeHouse.x / 2][startY1 + sizeHouse.y - 1].type = 21;
        background[startX1 + sizeHouse.x / 2 - 1][startY1 + sizeHouse.y - 1].type = 21;
        background[startX1 + sizeHouse.x / 2 + 1][startY1 + sizeHouse.y - 1].type = 21;
    }

    //vertical
    if(getProbability(0.8)){
        background[startX1][startY1 + sizeHouse.y / 2].type = 21;
        background[startX1][startY1 + sizeHouse.y / 2 - 1].type = 21;
        background[startX1][startY1 + sizeHouse.y / 2 + 1].type = 21;
    }
    if(getProbability(0.8)){
        background[startX1 + sizeHouse.x - 1][startY1 + sizeHouse.y / 2].type = 21;
        background[startX1 + sizeHouse.x - 1][startY1 + sizeHouse.y / 2 - 1].type = 21;
        background[startX1 + sizeHouse.x - 1][startY1 + sizeHouse.y / 2 + 1].type = 21;
    }

    //house

    //corners
    background[startX1 + territoryHouse.x][startY1 + territoryHouse.y].type = 27;
    background[startX1 + sizeHouse.x - 1 - territoryHouse.x][startY1 + territoryHouse.y].type = 28;
    background[startX1 + sizeHouse.x - 1 - territoryHouse.x][startY1 + sizeHouse.y - 1 - territoryHouse.y].type = 29;
    background[startX1 + territoryHouse.x][startY1 + sizeHouse.y - 1 - territoryHouse.y].type = 26;

    //horisontal Border
    for(int i = startX1 + 1 + territoryHouse.x; i < startX1 + sizeHouse.x - 1 - territoryHouse.x; i++){
        background[i][startY1 + territoryHouse.y].type = 24;
        background[i][startY1 + sizeHouse.y - 1 - territoryHouse.y].type = 22;
    }

    //vertical Border
    for(int i = startY1 + 1 + territoryHouse.y; i < startY1 + sizeHouse.y - 1 - territoryHouse.y; i++){
        background[startX1 + territoryHouse.x][i].type = 23;
        background[startX1 + sizeHouse.x - 1 - territoryHouse.x][i].type = 25;
    }

    //vertical
    for(int i = 0; i < firstTosecondFloor; i++){
        for(int j = i; j < sizeHouse.y - 2 * territoryHouse.y - 2 - i; j++){
            background[startX1 + territoryHouse.x + 1 + i][startY1 + territoryHouse.y + 1 + j].type = 33;
            background[startX1 + sizeHouse.x- territoryHouse.x - 2 - i][startY1 + territoryHouse.y + 1 + j].type = 33;
        }
        for(int j = i; j < sizeHouse.x - 2 * territoryHouse.x - 2 - i; j++){
            background[startX1 + territoryHouse.x + 1 + j][startY1 + territoryHouse.y + 1 + i].type = 32;
            background[startX1 + territoryHouse.x + 1 + j][startY1 + sizeHouse.y- territoryHouse.y - 2 - i].type = 32;
        }
    }

    //diagonal
    for(int i = 0; i < firstTosecondFloor; i++){
        //LU
        background[startX1 + territoryHouse.x + 1 + i][startY1 + territoryHouse.y + 1 + i].type = 31;
        //LD
        background[startX1 + territoryHouse.x + 1 + i][startY1 + sizeHouse.y - territoryHouse.y - 2 - i].type = 30;
        //RU
        background[startX1 + sizeHouse.x - territoryHouse.x - 2 - i][startY1 + territoryHouse.y + 1 + i].type = 55;
        //RD
        background[startX1 + sizeHouse.x - territoryHouse.x - 2 - i][startY1 + sizeHouse.y - territoryHouse.y - 2 - i].type = 54;
    }

    //first floor

    //diagonal corners
    for(int i = 0; i < firstTosecondFloor - 1; i++){
        //LU
        background[startX1 + territoryHouse.x + 1 + i][startY1 + territoryHouse.y + 2 + i].type = 74;
        //LD
        background[startX1 + territoryHouse.x + 1 + i][startY1 + sizeHouse.y - territoryHouse.y - 3 - i].type = 75;
        //RU
        background[startX1 + sizeHouse.x - territoryHouse.x - 2 - i][startY1 + territoryHouse.y + 2 + i].type = 73;
        //RD
        background[startX1 + sizeHouse.x - territoryHouse.x - 2 - i][startY1 + sizeHouse.y - territoryHouse.y - 3 - i].type = 72;
    }

    for(int i = 0; i < firstTosecondFloor - 1; i++){
        //LU
        background[startX1 + territoryHouse.x + 2 + i][startY1 + territoryHouse.y + 1 + i].type = 50;
        //LD
        background[startX1 + territoryHouse.x + 2 + i][startY1 + sizeHouse.y - territoryHouse.y - 2 - i].type = 51;
        //RU
        background[startX1 + sizeHouse.x - territoryHouse.x - 3 - i][startY1 + territoryHouse.y + 1 + i].type = 53;
        //RD
        background[startX1 + sizeHouse.x - territoryHouse.x - 3 - i][startY1 + sizeHouse.y - territoryHouse.y - 2 - i].type = 52;
    }


    //second floor

    int color = rand() % 4;

    //corners
    //LU
    background[startX1 + 1 + territoryHouse.x + firstTosecondFloor][startY1 + 1 + territoryHouse.y + firstTosecondFloor].type = 57 + color*4;
    //LD
    background[startX1 + 1 + territoryHouse.x + firstTosecondFloor][startY1 + sizeHouse.y - 2 - territoryHouse.y - firstTosecondFloor].type = 56 + color*4;
    //RU
    background[startX1 + sizeHouse.x - 2 - territoryHouse.x - firstTosecondFloor][startY1 + 1 + territoryHouse.y + firstTosecondFloor].type = 58 + color*4;
    //RD
    background[startX1 + sizeHouse.x - 2 - territoryHouse.x - firstTosecondFloor][startY1 + sizeHouse.y - 2 - territoryHouse.y - firstTosecondFloor].type = 59 + color*4;


    //horisontal border
    for(int i = startX1 + 2 + territoryHouse.x + firstTosecondFloor; i < startX1 + sizeHouse.x - 2 - territoryHouse.x - firstTosecondFloor; i++){
        background[i][startY1 + 1 + territoryHouse.y + firstTosecondFloor].type = 36 + color*4;
        background[i][startY1 + sizeHouse.y - 2 - territoryHouse.y - firstTosecondFloor].type = 34 + color*4;
    }

    //vertical border
    for(int i = startY1 + 2 + territoryHouse.y + firstTosecondFloor; i < startY1 + sizeHouse.y - 2 - territoryHouse.y - firstTosecondFloor; i++){
        background[startX1 + 1 + territoryHouse.x + firstTosecondFloor][i].type = 35 + color*4;
        background[startX1 + sizeHouse.x - 2 - territoryHouse.x - firstTosecondFloor][i].type = 37 + color*4;
    }

    //inside
    for(int i = startX1 + 2 + territoryHouse.x + firstTosecondFloor; i < startX1 + sizeHouse.x - 2 - territoryHouse.x - firstTosecondFloor; i++){
        for(int j = startY1 + 2 + territoryHouse.y + firstTosecondFloor; j < startY1 + sizeHouse.y - 2 - territoryHouse.y - firstTosecondFloor; j++)
            background[i][j].type = 76 + color;
    }


}

void setCrossAbility(){
    for(int i = 0; i < sizeWindow.x; i++){
        for(int j = 0; j < sizeWindow.y; j++){
            if(background[i][j].type < 10 || (background[i][j].type > 21 && background[i][j].type < 80)){
                background[i][j].crossEnemy = false;
                background[i][j].crossPlayer = false;
                background[i][j].crossRay = false;
                background[i][j].crossWeapon = false;
                background[i][j].speed = 0;
            }
        }
    }
}

void generateBox(){
    for(int k = 0; k < 1000000; k++){
        int x = rand() % sizeWindow.x;
        int y = rand() % sizeWindow.y;

        if(isEmptyBackground(21, Vector2i(x, y), Vector2i(2,2)) || isEmptyBackground(21, Vector2i(x, y), Vector2i(2,2))){
            background[x][y].type = 2;
            background[x+1][y].type = 3;
            background[x+1][y+1].type = 1;
            background[x][y+1].type = 0;
            break;
        }
    }
}

void setGrass(){
    for (int i = 0; i < sizeWindow.x; i++) {
        for (int j = 0; j < sizeWindow.y; j++){
            background[i][j].type = 21;
            background[i][j].speed = grassSpeed;
            background[i][j].crossPlayer = true;
            background[i][j].crossEnemy = true;
            background[i][j].crossRay = true;
            background[i][j].crossWeapon = true;
        }
    }
}

void createTree1(){
    textureTree1.loadFromFile(pathToDirectory + "pngForGame/tree.png");
    spriteTree1.setTexture(textureTree1);
    spriteTree1.setColor(Color(255, 255, 255, 180));
}
void createTree2(){
    textureTree2.loadFromFile(pathToDirectory + "pngForGame/palm.png");
    spriteTree2.setTexture(textureTree2);
    spriteTree2.setColor(Color(255, 255, 255, 200));
}
void createTree3(){
    textureTree3.loadFromFile(pathToDirectory + "pngForGame/tree2.png");
    spriteTree3.setTexture(textureTree3);
    spriteTree3.setColor(Color(255, 255, 255, 200));
}
void createTree4(){
    textureTree4.loadFromFile(pathToDirectory + "pngForGame/tree3.png");
    spriteTree4.setTexture(textureTree4);
    spriteTree4.setColor(Color(255, 255, 255, 210));
}
void createTree5(){
    textureTree5.loadFromFile(pathToDirectory + "pngForGame/palm2.png");
    spriteTree5.setTexture(textureTree5);
    spriteTree5.setColor(Color(255, 255, 255, 210));
}

void generateTree(int type, std::vector<Vector2f> &tree){
    for(int k = 0; k < 1000000; k++){
        unsigned int x = rand() % (sizeWindow.x - 20) + 10;
        unsigned int y = rand() % (sizeWindow.y - 20) + 10;

        if(isEmptyBackground(type, Vector2i(x, y), Vector2i(8, 8))) {
            tree.push_back(Vector2f(x*sizeTile, y * sizeTile));
            break;
        }
    }
}

void setBackgroundTypes(){
    BackgroundType backgroundType;

    for (int i = 0; i < textures.size(); i++) {
        Background tmp(textures.operator[](i).abilityCross);

        textures.operator[](i).texture.loadFromFile(textures.operator[](i).path);
        backgroundType.picture.setTexture(textures.operator[](i).texture);
        backgroundType.background = tmp;
        backgroundType.background.type = i;

        backgroundTypes.insert(std::pair<int, BackgroundType>(i, backgroundType));
    }
}

void setBackground(std::vector<Opaque> &houses) {
    setBackgroundTypes();

    setGrass();

    for(int i = 0; i < sizeWindow.x / 300; i++){
        generateRiverLR();
    }

    for(int i = 0; i < sizeWindow.x / 300; i++){
        generateRiverUD();
    }

    generateCoast();
    for(int i = 0; i < 15; i++){
        generateBeach();
    }
    generateGrassBeachCoast();
    for(int i = 0; i < 20; i++){
        generateGrassBeach();
    }

    for(int i = 0; i < sizeWindow.x / 30; i++){
        generateHouse(houses);
    }

    createTree1();
    createTree2();
    createTree3();
    createTree4();
    createTree5();
    for(int i = 0; i < sizeWindow.x / 25; i++){
        generateTree(21, trees1);
    }
    for(int i = 0; i < sizeWindow.x / 25; i++){
        generateTree(21, trees3);
    }
    for(int i = 0; i < sizeWindow.x / 25; i++){
        generateTree(21, trees4);
    }
    for(int i = 0; i < sizeWindow.x / 20; i++){
        generateTree(20, trees2);
    }
    for(int i = 0; i < sizeWindow.x / 20; i++){
        generateTree(16, trees5);
    }

    for(int i = 0; i < sizeWindow.x / 20; i++){
        generateBox();
    }

    generateBeachFlower();
    generateGrassFlower();

    setCrossAbility();

}

struct MinimapThread{
    Image image;
    Texture texture;
    Sprite sprite;
};


//very slow
//works if the map is less than 800*800
//recommended not to start in thread if map is more than 600*600
void setMinimap(MinimapThread *minimap){

    Clock clock1;
    Time time1;
    time1 = clock1.getElapsedTime();
    std::cout << "Time thread1 " << time1.asSeconds();

    std::cout << "Thread started" << std::endl;

    minimap->image.create((sizeWindow.x * sizeTile), (sizeWindow.y * sizeTile), Color(255, 255, 255, 0));

    time1 = clock1.getElapsedTime();
    std::cout << "Time thread2 " << time1.asSeconds();

    for(int i = 0; i < sizeWindow.x; i++){
        for(int j = 0; j < sizeWindow.y; j++){
            Image tmp;
            tmp.loadFromFile(textures.operator[](background[i][j].type).path);
            minimap->image.copy(tmp, i * sizeTile, j * sizeTile, IntRect(0, 0, sizeTile, sizeTile));
        }
    }

    time1 = clock1.getElapsedTime();
    std::cout << "Time thread3 " << time1.asSeconds();

    minimap->texture.loadFromImage(minimap->image);

    time1 = clock1.getElapsedTime();
    std::cout << "Time thread4 " << time1.asSeconds() << std::endl;

    minimap->sprite.setTexture(minimap->texture);
    minimap->sprite.setOrigin(minimap->sprite.getTexture()->getSize().x / 2.0, minimap->sprite.getTexture()->getSize().y / 2.0);
    minimap->sprite.setScale(minimapScale, minimapScale);

    minimap->sprite.setColor(Color(255, 255, 255, minimapTransparancy));

    std::cout << "Thread ended" << std::endl;



    //minimap->image.saveToFile("/home/vladislav/CLionProjects/game/pngForGame/map.png");
}

