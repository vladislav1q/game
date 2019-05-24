#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#pragma once
using namespace sf;

Vector2i sizeWindow = Vector2i(500, 500);
int sizeTile = 20;

int numberZombiePathsWalk = 16;
int numberZombiePathsAttack = 9;
int numberPlayerPathsWalk = 1;
int numberZombie1PathsWalk = 4;
int numberZombie2PathsWalk = 4;
int numberZombie3PathsWalk = 4;
int numberDogPathsWalk = 4;

Texture textureCorpse;

const std::string pathToDirectory = "/home/vladislav/CLionProjects/game/";
//const std::string pathToDirectory = "/home/zygalo/game/";

const std::string zombie1PathsWalkFullHealth[5] = {
        pathToDirectory + "pngForGame/zombie2/1/21.png",
        pathToDirectory + "pngForGame/zombie2/1/22.png",
        pathToDirectory + "pngForGame/zombie2/1/23.png",
        pathToDirectory + "pngForGame/zombie2/1/24.png",
        pathToDirectory + "pngForGame/zombie2/1/inwater2.png"
};

const std::string zombie1PathsWalkHalfHealth[5] = {
        pathToDirectory + "pngForGame/zombie2/1/11.png",
        pathToDirectory + "pngForGame/zombie2/1/12.png",
        pathToDirectory + "pngForGame/zombie2/1/13.png",
        pathToDirectory + "pngForGame/zombie2/1/14.png",
        pathToDirectory + "pngForGame/zombie2/1/inwater1.png"
};

const std::string zombie1PathsWalkSmallHealth[5] = {
        pathToDirectory + "pngForGame/zombie2/1/01.png",
        pathToDirectory + "pngForGame/zombie2/1/02.png",
        pathToDirectory + "pngForGame/zombie2/1/03.png",
        pathToDirectory + "pngForGame/zombie2/1/04.png",
        pathToDirectory + "pngForGame/zombie2/1/inwater0.png"
};

const std::string zombie2PathsWalkFullHealth[5] = {
        pathToDirectory + "pngForGame/zombie2/2/21.png",
        pathToDirectory + "pngForGame/zombie2/2/22.png",
        pathToDirectory + "pngForGame/zombie2/2/23.png",
        pathToDirectory + "pngForGame/zombie2/2/24.png",
        pathToDirectory + "pngForGame/zombie2/2/inwater.png"
};

const std::string zombie2PathsWalkHalfHealth[5] = {
        pathToDirectory + "pngForGame/zombie2/2/11.png",
        pathToDirectory + "pngForGame/zombie2/2/12.png",
        pathToDirectory + "pngForGame/zombie2/2/13.png",
        pathToDirectory + "pngForGame/zombie2/2/14.png",
        pathToDirectory + "pngForGame/zombie2/2/inwater.png"
};

const std::string zombie2PathsWalkSmallHealth[5] = {
        pathToDirectory + "pngForGame/zombie2/2/01.png",
        pathToDirectory + "pngForGame/zombie2/2/02.png",
        pathToDirectory + "pngForGame/zombie2/2/03.png",
        pathToDirectory + "pngForGame/zombie2/2/04.png",
        pathToDirectory + "pngForGame/zombie2/2/inwater.png"
};

const std::string zombie3PathsWalkFullHealth[5] = {
        pathToDirectory + "pngForGame/zombie2/3/21.png",
        pathToDirectory + "pngForGame/zombie2/3/22.png",
        pathToDirectory + "pngForGame/zombie2/3/23.png",
        pathToDirectory + "pngForGame/zombie2/3/24.png",
        pathToDirectory + "pngForGame/zombie2/3/inwater.png"
};

const std::string zombie3PathsWalkHalfHealth[5] = {
        pathToDirectory + "pngForGame/zombie2/3/11.png",
        pathToDirectory + "pngForGame/zombie2/3/12.png",
        pathToDirectory + "pngForGame/zombie2/3/13.png",
        pathToDirectory + "pngForGame/zombie2/3/14.png",
        pathToDirectory + "pngForGame/zombie2/3/inwater.png"
};

const std::string zombie3PathsWalkSmallHealth[5] = {
        pathToDirectory + "pngForGame/zombie2/3/01.png",
        pathToDirectory + "pngForGame/zombie2/3/02.png",
        pathToDirectory + "pngForGame/zombie2/3/03.png",
        pathToDirectory + "pngForGame/zombie2/3/04.png",
        pathToDirectory + "pngForGame/zombie2/3/inwater.png"
};

const std::string dogPathsWalkFullHealth[5] = {
        pathToDirectory + "pngForGame/zombie2/dog/1.png",
        pathToDirectory + "pngForGame/zombie2/dog/2.png",
        pathToDirectory + "pngForGame/zombie2/dog/3.png",
        pathToDirectory + "pngForGame/zombie2/dog/4.png",
        pathToDirectory + "pngForGame/zombie2/dog/inwater.png"
};

const std::string zombiePathsWalkFullHealth[17] = {
        pathToDirectory + "pngForGame/zombie/walk/200.png",
        pathToDirectory + "pngForGame/zombie/walk/201.png",
        pathToDirectory + "pngForGame/zombie/walk/202.png",
        pathToDirectory + "pngForGame/zombie/walk/203.png",
        pathToDirectory + "pngForGame/zombie/walk/204.png",
        pathToDirectory + "pngForGame/zombie/walk/205.png",
        pathToDirectory + "pngForGame/zombie/walk/206.png",
        pathToDirectory + "pngForGame/zombie/walk/207.png",
        pathToDirectory + "pngForGame/zombie/walk/208.png",
        pathToDirectory + "pngForGame/zombie/walk/209.png",
        pathToDirectory + "pngForGame/zombie/walk/210.png",
        pathToDirectory + "pngForGame/zombie/walk/211.png",
        pathToDirectory + "pngForGame/zombie/walk/212.png",
        pathToDirectory + "pngForGame/zombie/walk/213.png",
        pathToDirectory + "pngForGame/zombie/walk/214.png",
        pathToDirectory + "pngForGame/zombie/walk/215.png",
        pathToDirectory + "pngForGame/zombie/inwater.png"
};

const std::string zombiePathsWalkHalfHealth[17] = {
        pathToDirectory + "pngForGame/zombie/walk/100.png",
        pathToDirectory + "pngForGame/zombie/walk/101.png",
        pathToDirectory + "pngForGame/zombie/walk/102.png",
        pathToDirectory + "pngForGame/zombie/walk/103.png",
        pathToDirectory + "pngForGame/zombie/walk/104.png",
        pathToDirectory + "pngForGame/zombie/walk/105.png",
        pathToDirectory + "pngForGame/zombie/walk/106.png",
        pathToDirectory + "pngForGame/zombie/walk/107.png",
        pathToDirectory + "pngForGame/zombie/walk/108.png",
        pathToDirectory + "pngForGame/zombie/walk/109.png",
        pathToDirectory + "pngForGame/zombie/walk/110.png",
        pathToDirectory + "pngForGame/zombie/walk/111.png",
        pathToDirectory + "pngForGame/zombie/walk/112.png",
        pathToDirectory + "pngForGame/zombie/walk/113.png",
        pathToDirectory + "pngForGame/zombie/walk/114.png",
        pathToDirectory + "pngForGame/zombie/walk/115.png",
        pathToDirectory + "pngForGame/zombie/inwater.png"
};

const std::string zombiePathsWalkSmallHealth[17] = {
        pathToDirectory + "pngForGame/zombie/walk/000.png",
        pathToDirectory + "pngForGame/zombie/walk/001.png",
        pathToDirectory + "pngForGame/zombie/walk/002.png",
        pathToDirectory + "pngForGame/zombie/walk/003.png",
        pathToDirectory + "pngForGame/zombie/walk/004.png",
        pathToDirectory + "pngForGame/zombie/walk/005.png",
        pathToDirectory + "pngForGame/zombie/walk/006.png",
        pathToDirectory + "pngForGame/zombie/walk/007.png",
        pathToDirectory + "pngForGame/zombie/walk/008.png",
        pathToDirectory + "pngForGame/zombie/walk/009.png",
        pathToDirectory + "pngForGame/zombie/walk/010.png",
        pathToDirectory + "pngForGame/zombie/walk/011.png",
        pathToDirectory + "pngForGame/zombie/walk/012.png",
        pathToDirectory + "pngForGame/zombie/walk/013.png",
        pathToDirectory + "pngForGame/zombie/walk/014.png",
        pathToDirectory + "pngForGame/zombie/walk/015.png",
        pathToDirectory + "pngForGame/zombie/inwater.png"
};

const std::string zombiePathsAttackFullHealth[9] = {
        pathToDirectory + "pngForGame/zombie/attack/20.png",
        pathToDirectory + "pngForGame/zombie/attack/21.png",
        pathToDirectory + "pngForGame/zombie/attack/22.png",
        pathToDirectory + "pngForGame/zombie/attack/23.png",
        pathToDirectory + "pngForGame/zombie/attack/24.png",
        pathToDirectory + "pngForGame/zombie/attack/25.png",
        pathToDirectory + "pngForGame/zombie/attack/26.png",
        pathToDirectory + "pngForGame/zombie/attack/27.png",
        pathToDirectory + "pngForGame/zombie/attack/28.png"
};
const std::string zombiePathsAttackHalfHealth[9] = {
        pathToDirectory + "pngForGame/zombie/attack/10.png",
        pathToDirectory + "pngForGame/zombie/attack/11.png",
        pathToDirectory + "pngForGame/zombie/attack/12.png",
        pathToDirectory + "pngForGame/zombie/attack/13.png",
        pathToDirectory + "pngForGame/zombie/attack/14.png",
        pathToDirectory + "pngForGame/zombie/attack/15.png",
        pathToDirectory + "pngForGame/zombie/attack/16.png",
        pathToDirectory + "pngForGame/zombie/attack/17.png",
        pathToDirectory + "pngForGame/zombie/attack/18.png"
};
const std::string zombiePathsAttackSmallHealth[9] = {
        pathToDirectory + "pngForGame/zombie/attack/00.png",
        pathToDirectory + "pngForGame/zombie/attack/01.png",
        pathToDirectory + "pngForGame/zombie/attack/02.png",
        pathToDirectory + "pngForGame/zombie/attack/03.png",
        pathToDirectory + "pngForGame/zombie/attack/04.png",
        pathToDirectory + "pngForGame/zombie/attack/05.png",
        pathToDirectory + "pngForGame/zombie/attack/06.png",
        pathToDirectory + "pngForGame/zombie/attack/07.png",
        pathToDirectory + "pngForGame/zombie/attack/08.png"
};

const std::string playerPathsWalkFullHealth[2] = {
        pathToDirectory + "pngForGame/player.png",
        pathToDirectory + "pngForGame/playerInWater.png"
};

const std::string corpsePath = pathToDirectory + "pngForGame/blood.png";


std::vector <Texture> textureZombie1PathsWalkFullHealth;
std::vector <Texture> textureZombie1PathsWalkHalfHealth;
std::vector <Texture> textureZombie1PathsWalkSmallHealth;
std::vector <Texture> textureZombie1PathsAttackFullHealth;
std::vector <Texture> textureZombie1PathsAttackHalfHealth;
std::vector <Texture> textureZombie1PathsAttackSmallHealth;

std::vector <Texture> textureZombie2PathsWalkFullHealth;
std::vector <Texture> textureZombie2PathsWalkHalfHealth;
std::vector <Texture> textureZombie2PathsWalkSmallHealth;
std::vector <Texture> textureZombie2PathsAttackFullHealth;
std::vector <Texture> textureZombie2PathsAttackHalfHealth;
std::vector <Texture> textureZombie2PathsAttackSmallHealth;

std::vector <Texture> textureZombie3PathsWalkFullHealth;
std::vector <Texture> textureZombie3PathsWalkHalfHealth;
std::vector <Texture> textureZombie3PathsWalkSmallHealth;
std::vector <Texture> textureZombie3PathsAttackFullHealth;
std::vector <Texture> textureZombie3PathsAttackHalfHealth;
std::vector <Texture> textureZombie3PathsAttackSmallHealth;

std::vector <Texture> textureDogPathsWalkFullHealth;
std::vector <Texture> textureDogPathsAttackFullHealth;

std::vector <Texture> textureZombiePathsWalkFullHealth;
std::vector <Texture> textureZombiePathsWalkHalfHealth;
std::vector <Texture> textureZombiePathsWalkSmallHealth;
std::vector <Texture> textureZombiePathsAttackFullHealth;
std::vector <Texture> textureZombiePathsAttackHalfHealth;
std::vector <Texture> textureZombiePathsAttackSmallHealth;

std::vector <Texture> texturePlayerPaths;

void setTextures(){

    Texture texture;
    //Zombie1
    for(int i = 0; i < numberZombie1PathsWalk; i++){
        texture.loadFromFile(zombie1PathsWalkFullHealth[i]);
        textureZombie1PathsWalkFullHealth.push_back(texture);
        texture.loadFromFile(zombie1PathsWalkHalfHealth[i]);
        textureZombie1PathsWalkHalfHealth.push_back(texture);
        texture.loadFromFile(zombie1PathsWalkSmallHealth[i]);
        textureZombie1PathsWalkSmallHealth.push_back(texture);

        texture.loadFromFile(zombie1PathsWalkFullHealth[0]);
        textureZombie1PathsAttackFullHealth.push_back(texture);
        texture.loadFromFile(zombie1PathsWalkHalfHealth[0]);
        textureZombie1PathsAttackHalfHealth.push_back(texture);
        texture.loadFromFile(zombie1PathsWalkSmallHealth[0]);
        textureZombie1PathsAttackSmallHealth.push_back(texture);
    }
    //in water
    texture.loadFromFile(zombie1PathsWalkFullHealth[numberZombie1PathsWalk]);
    textureZombie1PathsWalkFullHealth.push_back(texture);
    texture.loadFromFile(zombie1PathsWalkHalfHealth[numberZombie1PathsWalk]);
    textureZombie1PathsWalkHalfHealth.push_back(texture);
    texture.loadFromFile(zombie1PathsWalkSmallHealth[numberZombie1PathsWalk]);
    textureZombie1PathsWalkSmallHealth.push_back(texture);

    //Zombie2
    for(int i = 0; i < numberZombie2PathsWalk; i++){
        texture.loadFromFile(zombie2PathsWalkFullHealth[i]);
        textureZombie2PathsWalkFullHealth.push_back(texture);
        texture.loadFromFile(zombie2PathsWalkHalfHealth[i]);
        textureZombie2PathsWalkHalfHealth.push_back(texture);
        texture.loadFromFile(zombie2PathsWalkSmallHealth[i]);
        textureZombie2PathsWalkSmallHealth.push_back(texture);

        texture.loadFromFile(zombie2PathsWalkFullHealth[0]);
        textureZombie2PathsAttackFullHealth.push_back(texture);
        texture.loadFromFile(zombie2PathsWalkHalfHealth[0]);
        textureZombie2PathsAttackHalfHealth.push_back(texture);
        texture.loadFromFile(zombie2PathsWalkSmallHealth[0]);
        textureZombie2PathsAttackSmallHealth.push_back(texture);
    }
    //in water
    texture.loadFromFile(zombie2PathsWalkFullHealth[numberZombie2PathsWalk]);
    textureZombie2PathsWalkFullHealth.push_back(texture);
    texture.loadFromFile(zombie2PathsWalkHalfHealth[numberZombie2PathsWalk]);
    textureZombie2PathsWalkHalfHealth.push_back(texture);
    texture.loadFromFile(zombie2PathsWalkSmallHealth[numberZombie2PathsWalk]);
    textureZombie2PathsWalkSmallHealth.push_back(texture);

    //Zombie3
    for(int i = 0; i < numberZombie3PathsWalk; i++){
        texture.loadFromFile(zombie3PathsWalkFullHealth[i]);
        textureZombie3PathsWalkFullHealth.push_back(texture);
        texture.loadFromFile(zombie3PathsWalkHalfHealth[i]);
        textureZombie3PathsWalkHalfHealth.push_back(texture);
        texture.loadFromFile(zombie3PathsWalkSmallHealth[i]);
        textureZombie3PathsWalkSmallHealth.push_back(texture);

        texture.loadFromFile(zombie3PathsWalkFullHealth[0]);
        textureZombie3PathsAttackFullHealth.push_back(texture);
        texture.loadFromFile(zombie3PathsWalkHalfHealth[0]);
        textureZombie3PathsAttackHalfHealth.push_back(texture);
        texture.loadFromFile(zombie3PathsWalkSmallHealth[0]);
        textureZombie3PathsAttackSmallHealth.push_back(texture);
    }
    //in water
    texture.loadFromFile(zombie3PathsWalkFullHealth[numberZombie3PathsWalk]);
    textureZombie3PathsWalkFullHealth.push_back(texture);
    texture.loadFromFile(zombie3PathsWalkHalfHealth[numberZombie3PathsWalk]);
    textureZombie3PathsWalkHalfHealth.push_back(texture);
    texture.loadFromFile(zombie3PathsWalkSmallHealth[numberZombie3PathsWalk]);
    textureZombie3PathsWalkSmallHealth.push_back(texture);

    //Dog
    for(int i = 0; i < numberDogPathsWalk; i++){
        texture.loadFromFile(dogPathsWalkFullHealth[i]);
        textureDogPathsWalkFullHealth.push_back(texture);

        texture.loadFromFile(dogPathsWalkFullHealth[0]);
        textureDogPathsAttackFullHealth.push_back(texture);
    }
    //in water
    texture.loadFromFile(dogPathsWalkFullHealth[numberDogPathsWalk]);
    textureDogPathsWalkFullHealth.push_back(texture);

    //Zombie
    for(int i = 0; i < numberZombiePathsWalk; i++){
        texture.loadFromFile(zombiePathsWalkFullHealth[i]);
        textureZombiePathsWalkFullHealth.push_back(texture);
        texture.loadFromFile(zombiePathsWalkHalfHealth[i]);
        textureZombiePathsWalkHalfHealth.push_back(texture);
        texture.loadFromFile(zombiePathsWalkSmallHealth[i]);
        textureZombiePathsWalkSmallHealth.push_back(texture);
    }
    //in water
    texture.loadFromFile(zombiePathsWalkFullHealth[numberZombiePathsWalk]);
    textureZombiePathsWalkFullHealth.push_back(texture);
    texture.loadFromFile(zombiePathsWalkHalfHealth[numberZombiePathsWalk]);
    textureZombiePathsWalkHalfHealth.push_back(texture);
    texture.loadFromFile(zombiePathsWalkSmallHealth[numberZombiePathsWalk]);
    textureZombiePathsWalkSmallHealth.push_back(texture);

    for(int i = 0; i < numberZombiePathsAttack; i++){
        texture.loadFromFile(zombiePathsAttackFullHealth[i]);
        textureZombiePathsAttackFullHealth.push_back(texture);
        texture.loadFromFile(zombiePathsAttackHalfHealth[i]);
        textureZombiePathsAttackHalfHealth.push_back(texture);
        texture.loadFromFile(zombiePathsAttackSmallHealth[i]);
        textureZombiePathsAttackSmallHealth.push_back(texture);
    }

    //Player
    for(int i = 0; i < numberPlayerPathsWalk; i++){
        texture.loadFromFile(playerPathsWalkFullHealth[i]);
        texturePlayerPaths.push_back(texture);
    }
    //in water
    texture.loadFromFile(playerPathsWalkFullHealth[numberPlayerPathsWalk]);
    texturePlayerPaths.push_back(texture);


};

