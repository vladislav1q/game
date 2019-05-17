#include "background.h"
#include "init.h"
#include "draw.h"
#include "thread"
#include "pages.h"
#include "music.h"

#pragma once

int waveDuration = 30;
const float waveRelax = 100;
unsigned int numberWave = 0;

float timewaveDurationBuffer = 0;
float timewaveRelaxBuffer = waveRelax;
float timeTextBuffer = 0;

bool wave = false;
bool textShow = false;

float timeBuffer1 = 0;
float timeBuffer2 = 0;
float timeBuffer3 = 0;
float timeBuffer4 = 0;
float timeBuffer5 = 0;

void createWave(RenderWindow &window, VideoMode &mode, View &gameView, Time &time, Time &dt,
                Sprite &spriteZombie, Sprite &spriteZombie1, Sprite &spriteZombie2, Sprite &spriteZombie3, Sprite &spriteDog,
                std::vector<Organism> &zombies, std::vector<Organism> &zombies1, std::vector<Organism> &zombies2,
                std::vector<Organism> &zombies3, std::vector<Organism> &dogs){

    timewaveDurationBuffer += dt.asSeconds();

    timeBuffer1 += dt.asSeconds();
    timeBuffer2 += dt.asSeconds();
    timeBuffer3 += dt.asSeconds();
    timeBuffer4 += dt.asSeconds();
    timeBuffer5 += dt.asSeconds();

    if(!wave){
        if(timewaveRelaxBuffer < waveRelax)
            timewaveRelaxBuffer += dt.asSeconds();
        else{
            timewaveRelaxBuffer = 0;
            timewaveDurationBuffer = 0;
            wave = true;
            numberWave++;

            timeProducementZombie /= 2;
            timeProducementZombie1 /= 2;
            timeProducementZombie2 /= 2;
            timeProducementZombie3 /= 2;
            timeProducementDog /= 2;

            textShow = true;
            waveDuration *= 2;
        }
    } else {
        if(timewaveDurationBuffer > waveDuration){
            timewaveRelaxBuffer = 0;
            timewaveDurationBuffer = 0;
            wave = false;
            textShow = true;
        } else {

            if(timeBuffer1 > timeProducementZombie){
                timeBuffer1 = 0;

                //Create zombie
                Organism zombie(zombieFullHealth, 100, zombieSpeed, speedDrawZombie, zombieDamage, true,
                                textureZombiePathsWalkFullHealth, textureZombiePathsWalkHalfHealth, textureZombiePathsWalkSmallHealth, numberZombiePathsWalk, 0.001,
                                textureZombiePathsAttackFullHealth, textureZombiePathsAttackHalfHealth, textureZombiePathsAttackSmallHealth, numberZombiePathsAttack, 0.001,
                                spriteZombie);
                while(true){
                    zombie.organism.setPosition(rand() % (sizeWindow.x * sizeTile - 200 + 100), rand() % (sizeWindow.y * sizeTile - 200) + 100);
                    if(zombie.getPosition().crossEnemy && !isInside(gameView, zombie.organism, 0))
                        break;
                }
                Vector2u enemySize = zombie.organism.getTexture()->getSize();
                zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);
                zombie.organism.setScale(0.75, 0.75);

                zombies.push_back(zombie);
            }
            if(timeBuffer2 > timeProducementZombie1 / hard){
                timeBuffer2 = 0;

                Organism zombie(zombie1FullHealth, 100, zombie1Speed, speedDrawZombie1, zombie1Damage, true,
                                textureZombie1PathsWalkFullHealth, textureZombie1PathsWalkHalfHealth, textureZombie1PathsWalkSmallHealth, numberZombie1PathsWalk, 0.001,
                                textureZombie1PathsAttackFullHealth, textureZombie1PathsAttackHalfHealth, textureZombie1PathsAttackSmallHealth, numberZombie1PathsWalk, 0.001,
                                spriteZombie1);
                while(true){
                    zombie.organism.setPosition(rand() % (sizeWindow.x * sizeTile - 200 + 100), rand() % (sizeWindow.y * sizeTile - 200) + 100);
                    if(zombie.getPosition().crossEnemy && !isInside(gameView, zombie.organism, 0))
                        break;
                }
                Vector2u enemySize = zombie.organism.getTexture()->getSize();
                zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);
                zombie.organism.setScale(1.3, 1.3);

                zombies1.push_back(zombie);
            }
            if(timeBuffer3 > timeProducementZombie2 / hard){
                timeBuffer3 = 0;

                Organism zombie(zombie2FullHealth, 100, zombie2Speed, speedDrawZombie2, zombie2Damage, true,
                                textureZombie2PathsWalkFullHealth, textureZombie2PathsWalkHalfHealth, textureZombie2PathsWalkSmallHealth, numberZombie2PathsWalk, 0.001,
                                textureZombie2PathsAttackFullHealth, textureZombie2PathsAttackHalfHealth, textureZombie2PathsAttackSmallHealth, numberZombie2PathsWalk, 0.001,
                                spriteZombie2);
                while(true){
                    zombie.organism.setPosition(rand() % (sizeWindow.x * sizeTile - 200 + 100), rand() % (sizeWindow.y * sizeTile - 200) + 100);
                    if(zombie.getPosition().crossEnemy && !isInside(gameView, zombie.organism, 0))
                        break;
                }
                Vector2u enemySize = zombie.organism.getTexture()->getSize();
                zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);
                zombie.organism.setScale(1.4, 1.4);

                zombies2.push_back(zombie);
            }


            if(timeBuffer4 > timeProducementZombie3 / hard){
                timeBuffer4 = 0;

                Organism zombie(zombie3FullHealth, 100, zombie3Speed, speedDrawZombie3, zombie3Damage, true,
                                textureZombie3PathsWalkFullHealth, textureZombie3PathsWalkHalfHealth, textureZombie3PathsWalkSmallHealth, numberZombie3PathsWalk, 0.001,
                                textureZombie3PathsAttackFullHealth, textureZombie3PathsAttackHalfHealth, textureZombie3PathsAttackSmallHealth, numberZombie3PathsWalk, 0.001,
                                spriteZombie3);

                while(true){
                    zombie.organism.setPosition(rand() % (sizeWindow.x * sizeTile), rand() % (sizeWindow.y * sizeTile));
                    if(zombie.getPosition().crossEnemy && !isInside(gameView, zombie.organism, 0))
                        break;
                }
                Vector2u enemySize = zombie.organism.getTexture()->getSize();
                zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);
                zombie.organism.setScale(1.4, 1.4);

                zombies3.push_back(zombie);
            }
            if(timeBuffer5 > timeProducementDog / hard){
                timeBuffer5 = 0;

                Organism zombie(dogFullHealth, 100, dogSpeed, speedDrawDog, dogDamage, true,
                                textureDogPathsWalkFullHealth, textureDogPathsWalkFullHealth, textureDogPathsWalkFullHealth, numberZombie2PathsWalk, 0.001,
                                textureDogPathsAttackFullHealth, textureDogPathsAttackFullHealth, textureDogPathsAttackFullHealth, numberZombie2PathsWalk, 0.001,
                                spriteDog);
                while(true){
                    zombie.organism.setPosition(rand() % (sizeWindow.x * sizeTile - 200 + 100), rand() % (sizeWindow.y * sizeTile - 200) + 100);
                    if(zombie.getPosition().crossEnemy && !isInside(gameView, zombie.organism, 0))
                        break;
                }
                Vector2u enemySize = zombie.organism.getTexture()->getSize();
                zombie.organism.setOrigin((float)enemySize.x/2, (float)enemySize.y/2);
                zombie.organism.setScale(1.0, 1.0);
                dogs.push_back(zombie);
            }
        }

    }


    Font font;
    font.loadFromFile(pathToDirectory + "fonts/font.ttf");
    Text text;
    text.setFont(font);
    text.setCharacterSize(70);
    text.setFillColor(Color(255, 120, 70, 220));
    text.setPosition(gameView.getCenter().x - 100, gameView.getCenter().y - mode.height / 2 + 100);
    text.setOutlineThickness(2);
    text.setOutlineColor(Color::Red);

    if(textShow){
        timeTextBuffer += dt.asSeconds();
        if(wave){
            text.setString(std::to_string(numberWave) + " WAVE");
            window.draw(text);
        } else {
            text.setString(std::to_string(numberWave) + " WAVE FINISHED");
            window.draw(text);
        }

    }

    if(timeTextBuffer > 5){
        timeTextBuffer = 0;
        textShow = false;
    }

    //std::cout << std::endl << "WAVE: " << wave << "NUMBER WAVE: " << numberWave << "TEXT: " << textShow << std::endl;

}