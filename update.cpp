#include "objects.h"
#include "background.h"
#include "music.h"
#include "network.h"
#pragma once

bool isInside(View &gameView, Sprite &object, int sideOfBorder){     //   1
    float xSize = (float)object.getTexture()->getSize().x/2 * object.getScale().x;
    float ySize = (float)object.getTexture()->getSize().y/2 * object.getScale().y;

    switch (sideOfBorder){                                                          //  4 2
        case 0:{                                                                    //   3
            return isInside(gameView, object, 1) && isInside(gameView, object, 2)
                   && isInside(gameView, object, 3) && isInside(gameView, object, 4);
        }
        case 1:{
            return object.getPosition().y - ySize > 0;
        }
        case 2:{
            return object.getPosition().x + xSize < gameView.getCenter().x + gameView.getSize().x / 2;
        }
        case 3:{
            return object.getPosition().y + ySize < gameView.getCenter().y + gameView.getSize().y / 2;
        }
        case 4:{
            return object.getPosition().x - xSize > 0;
        }
        default:
            return false;
    }
}

bool isInside(View &gameView, Vector2f position, int sideOfBorder){     //   1
    switch (sideOfBorder){                                                          //  4 2
        case 0:{                                                                    //   3
            return isInside(gameView, position, 1) && isInside(gameView, position, 2)
                   && isInside(gameView, position, 3) && isInside(gameView, position, 4);
        }
        case 1:{
            return position.y > 0;
        }
        case 2:{
            return position.x < gameView.getCenter().x + gameView.getSize().x / 2;
        }
        case 3:{
            return position.y < gameView.getCenter().y + gameView.getSize().y / 2;
        }
        case 4:{
            return position.x > 0;
        }
        default:
            return false;
    }
}

bool isInside(Sprite &object, int sideOfBorder){
    float xSize = (float)object.getTexture()->getSize().x/2 * object.getScale().x;
    float ySize = (float)object.getTexture()->getSize().y/2 * object.getScale().y;
    //   1
    switch (sideOfBorder){                                                          //  4 2
        case 0:{                                                                    //   3
            return isInside(object, 1) && isInside(object, 2)
                   && isInside(object, 3) && isInside(object, 4);
        }
        case 1:{
            return object.getPosition().y - ySize > 0;
        }
        case 2:{
            return object.getPosition().x + xSize < sizeWindow.x * sizeTile;
        }
        case 3:{
            return object.getPosition().y + ySize < sizeWindow.y * sizeTile;
        }
        case 4:{
            return object.getPosition().x - xSize > 0;
        }
        default:
            return false;
    }
}

bool isInside(Vector2f coordinates, float xSize, float ySize, int sideOfBorder){
    //   1
    switch (sideOfBorder){                                                          //  4 2
        case 0:{                                                                    //   3
            return isInside(coordinates, xSize, ySize, 1) && isInside(coordinates, xSize, ySize, 2)
                   && isInside(coordinates, xSize, ySize, 3) && isInside(coordinates, xSize, ySize, 4);
        }
        case 1:{
            return coordinates.y - ySize / 2 >= 0;
        }
        case 2:{
            return coordinates.x + xSize / 2 <= sizeWindow.x * sizeTile;
        }
        case 3:{
            return coordinates.y + ySize / 2 <= sizeWindow.y * sizeTile;
        }
        case 4:{
            return coordinates.x - xSize / 2 >= 0;
        }
        default:
            return false;
    }
}

float maxmod(float a, float b){
    float moda, modb;

    if(a > 0)
        moda = a;
    else
        moda = -a;
    if(b > 0)
        modb = b;
    else
        modb = -b;

    if(moda > modb)
        return a;
    else
        return b;
}

void updateCursor(RenderWindow &window, Sprite &spriteCursor){
    spriteCursor.setPosition(window.mapPixelToCoords(Mouse::getPosition(window)).x,
                             window.mapPixelToCoords(Mouse::getPosition(window)).y);
}


void addFeature(std::vector<Feature> &items, Vector2f position){
    if(getProbability(heartProbability / hard)){
        Feature feature;
        feature.feature.setTexture(textureHeart);
        feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
        feature.feature.setScale(0.17, 0.17);
        feature.feature.setPosition(position);
        feature.type = 1;
        feature.value = 100;
        feature.timeBuffer = 0;
        items.push_back(feature);

    } else if(getProbability(shieldProbability / hard)){
        Feature feature;
        feature.feature.setTexture(textureShield);
        feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
        feature.feature.setScale(0.04, 0.04);
        feature.feature.setPosition(position);
        feature.type = 2;
        feature.value = 100;
        feature.timeBuffer = 0;
        items.push_back(feature);

    } else if(getProbability(bulletProbability / hard)){
        Feature feature;
        feature.feature.setTexture(textureBullet);
        feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
        feature.feature.setScale(0.1, 0.1);
        feature.feature.setPosition(position);
        feature.type = 3;
        feature.value = numberBulletsCage;
        feature.timeBuffer = 0;
        items.push_back(feature);
    } else if(getProbability(bombProbability / hard)){
        Feature feature;
        feature.feature.setTexture(textureBomb);
        feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
        feature.feature.setScale(0.035, 0.035);
        feature.feature.setPosition(position);
        feature.type = 4;
        feature.value = numberBombsCage;
        feature.timeBuffer = 0;
        items.push_back(feature);
    }
}

void addFeatureServer(Packet &packet, std::vector<Feature> &items, Vector2f position){
    Feature feature;

    if(getProbability(heartProbability / hard)){
        feature.feature.setTexture(textureHeart);
        feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
        feature.feature.setScale(0.17, 0.17);
        feature.feature.setPosition(position);
        feature.type = 1;
        feature.value = 100;
        feature.timeBuffer = 0;
        items.push_back(feature);
        SendFeature sendFeature(feature.type, feature.feature.getPosition());
        packet << SendType(packetType ::feature) << sendFeature;


    } else if(getProbability(shieldProbability / hard)){
        Feature feature;
        feature.feature.setTexture(textureShield);
        feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
        feature.feature.setScale(0.04, 0.04);
        feature.feature.setPosition(position);
        feature.type = 2;
        feature.value = 100;
        feature.timeBuffer = 0;
        items.push_back(feature);

        SendFeature sendFeature(feature.type, feature.feature.getPosition());
        packet << SendType(packetType ::feature) << sendFeature;

    } else if(getProbability(bulletProbability / hard)){
        Feature feature;
        feature.feature.setTexture(textureBullet);
        feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
        feature.feature.setScale(0.1, 0.1);
        feature.feature.setPosition(position);
        feature.type = 3;
        feature.value = numberBulletsCage;
        feature.timeBuffer = 0;
        items.push_back(feature);

        SendFeature sendFeature(feature.type, feature.feature.getPosition());
        packet << SendType(packetType ::feature) << sendFeature;

    } else if(getProbability(bombProbability / hard)){
        Feature feature;
        feature.feature.setTexture(textureBomb);
        feature.feature.setOrigin(feature.feature.getTexture()->getSize().x / 2.0, feature.feature.getTexture()->getSize().y / 2.0);
        feature.feature.setScale(0.035, 0.035);
        feature.feature.setPosition(position);
        feature.type = 4;
        feature.value = numberBombsCage;
        feature.timeBuffer = 0;
        items.push_back(feature);

        SendFeature sendFeature(feature.type, feature.feature.getPosition());
        packet << SendType(packetType ::feature) << sendFeature;
    }
}

void updateFeatures(std::vector<Feature> &items, Organism &player, Time time, Bar &bulletBar, Bar &bombBar){
    int k = 0;
    for(auto &i : items){
        if(i.isInsideOrganism(player)){
            soundsAll.sound[2].play();
            switch (i.type){
                case 1:{
                    player.health += i.value;
                    if(player.health > playerFullHealth)
                        player.health = playerFullHealth;
                    break;
                }
                case 2:{
                    player.protection += i.value;
                    if(player.protection > playerFullProtection)
                        player.protection = playerFullProtection;
                    break;
                }
                case 3:{
                    bulletBar.value += i.value;
                    break;
                }
                case 4:{
                    bombBar.value += i.value;
                    break;
                }
            }
            items.erase(items.begin() + k);

        } else
            k++;
    }
}
void updateFeatures2(std::vector<Feature> &items, Organism &player1, Organism &player2, Time time, Bar &bulletBar, Bar &bombBar){
    int k = 0;
    for(auto &i : items){
        if(i.isInsideOrganism(player1)){
            soundsAll.sound[2].play();
            switch (i.type){
                case 1:{
                    player1.health += i.value;
                    if(player1.health > playerFullHealth)
                        player1.health = playerFullHealth;
                    break;
                }
                case 2:{
                    player1.protection += i.value;
                    if(player1.protection > playerFullProtection)
                        player1.protection = playerFullProtection;
                    break;
                }
                case 3:{
                    bulletBar.value += i.value;
                    break;
                }
                case 4:{
                    bombBar.value += i.value;
                    break;
                }
            }
            items.erase(items.begin() + k);

        } else
            k++;
    }

    k = 0;
    for(auto &i : items){
        if(i.isInsideOrganism(player2)){
            switch (i.type){
                case 1:{
                    player2.health += i.value;
                    if(player2.health > playerFullHealth)
                        player2.health = playerFullHealth;
                    break;
                }
                case 2:{
                    player2.protection += i.value;
                    if(player2.protection > playerFullProtection)
                        player2.protection = playerFullProtection;
                    break;
                }
                default:
                    break;
            }
            items.erase(items.begin() + k);

        } else
            k++;
    }

}

void gameViewUpdate(View &gameView, RenderWindow &window, Organism &player, Time time){

    float gameViewLeft = (gameView.getCenter().x - gameView.getSize().x / 2) ;
    float gameViewRight = (gameView.getCenter().x + gameView.getSize().x / 2);
    float gameViewUp = (gameView.getCenter().y - gameView.getSize().y / 2);
    float gameViewDown = (gameView.getCenter().y + gameView.getSize().y / 2);

    Vector2f CurrentCenter = gameView.getCenter();
    Vector2f TargetCenter = player.organism.getPosition();

    if(isInside(gameView.getCenter(), gameView.getSize().x, gameView.getSize().y, 0)){
        //gameView.setCenter(player.organism.getPosition());
        //view is up
        if(gameViewUp == 0){
            //if(!isInside(TargetCenter, gameView.getSize().x, gameView.getSize().y, 1)){
            if(TargetCenter.y - gameView.getSize().y/2 < 0)
                TargetCenter.y = gameView.getCenter().y;
        }
        //view is down
        if(gameViewDown == sizeWindow.y*sizeTile){
            //if(!isInside(TargetCenter, gameView.getSize().x, gameView.getSize().y, 3)){
            if(TargetCenter.y + gameView.getSize().y/2 > sizeWindow.y*sizeTile)
                TargetCenter.y = gameView.getCenter().y;
        }
        //view is left
        if(gameViewLeft == 0){
            //if(!isInside(TargetCenter, gameView.getSize().x, gameView.getSize().y, 4)){
            if(TargetCenter.x - gameView.getSize().x/2 < 0)
                TargetCenter.x = gameView.getCenter().x;
        }
        //view is right
        if(gameViewRight == sizeWindow.x*sizeTile){
            //if(!isInside(TargetCenter, gameView.getSize().x, gameView.getSize().y, 2)){
            if(TargetCenter.x + gameView.getSize().x/2 > sizeWindow.x*sizeTile)
                TargetCenter.x = gameView.getCenter().x;
        }
        //This variant doesn't work sometimes, because time.asseconds is progressing
        //gameView.setCenter(CurrentCenter + (TargetCenter - CurrentCenter) * (float)exp(-200 * time.asSeconds()));
        gameView.setCenter(CurrentCenter + (TargetCenter - CurrentCenter) * (float)exp(-150 * 0.02));//***************
        window.setView(gameView);

    } else{
        if(!isInside(gameView.getCenter(), gameView.getSize().x, gameView.getSize().y, 4))
            gameView.setCenter(gameView.getSize().x/2, gameView.getCenter().y);

        if(!isInside(gameView.getCenter(), gameView.getSize().x, gameView.getSize().y, 2))
            gameView.setCenter(sizeWindow.x * sizeTile - gameView.getSize().x/2, gameView.getCenter().y);

        if(!isInside(gameView.getCenter(), gameView.getSize().x, gameView.getSize().y, 1))
            gameView.setCenter(gameView.getCenter().x, gameView.getSize().y/2);

        if(!isInside(gameView.getCenter(), gameView.getSize().x, gameView.getSize().y, 3))
            gameView.setCenter(gameView.getCenter().x, sizeWindow.y * sizeTile - gameView.getSize().y/2 );
    }
}

void strikeWeaponClient(std::vector <Weapon> &bullets, std::vector <Organism> &enemies, std::vector<Corpse> &dead, std::vector<Feature> &items){

    int numberBullets = 0;
    for(auto &i : bullets){
        int numberEnemies = 0;
        for(auto &k : enemies){

            if(i.isInsideOrganism(k)){
                k.health -= i.damage;
                bullets.erase(bullets.begin() + numberBullets);

                //DEAD
                if(k.health <= 0){
                    Corpse corpse(k.organism.getRotation(), k.organism.getPosition(), k.organism.getTexture()->getSize().x * k.organism.getScale().x);
                    corpse.corpse.setTexture(textureCorpse);
                    dead.push_back(corpse);

                    soundsAll.sound[7].play();

                    enemies.erase(enemies.begin() + numberEnemies);

                }
                break;
            }
            numberEnemies++;
        }
        numberBullets++;
    }
}

void strikeAllWeaponClient(std::vector <Weapon> &bullets, std::vector <Organism> &enemies1,
                           std::vector <Organism> &enemies2, std::vector <Organism> &enemies3, std::vector <Organism> &enemies4,
                           std::vector <Organism> &enemies5, std::vector<Corpse> &dead, std::vector<Feature> &items){
    strikeWeaponClient(bullets, enemies1, dead, items);
    strikeWeaponClient(bullets, enemies2, dead, items);
    strikeWeaponClient(bullets, enemies3, dead, items);
    strikeWeaponClient(bullets, enemies4, dead, items);
    strikeWeaponClient(bullets, enemies5, dead, items);
}

void strikeWeaponServer(Packet &packet, std::vector <Weapon> &bullets, std::vector <Organism> &enemies, std::vector<Corpse> &dead, std::vector<Feature> &items){

    int numberBullets = 0;
    for(auto &i : bullets){
        int numberEnemies = 0;
        for(auto &k : enemies){

            if(i.isInsideOrganism(k)){
                k.health -= i.damage;
                bullets.erase(bullets.begin() + numberBullets);

                //DEAD
                if(k.health <= 0){
                    Corpse corpse(k.organism.getRotation(), k.organism.getPosition(), k.organism.getTexture()->getSize().x * k.organism.getScale().x);
                    corpse.corpse.setTexture(textureCorpse);
                    dead.push_back(corpse);
                    addFeatureServer(packet, items, k.organism.getPosition());

                    soundsAll.sound[7].play();

                    enemies.erase(enemies.begin() + numberEnemies);

                }
                break;
            }
            numberEnemies++;
        }
        numberBullets++;
    }
}

void strikeAllWeaponServer(Packet &packet, std::vector <Weapon> &bullets, std::vector <Organism> &enemies1,
                           std::vector <Organism> &enemies2, std::vector <Organism> &enemies3, std::vector <Organism> &enemies4,
                           std::vector <Organism> &enemies5, std::vector<Corpse> &dead, std::vector<Feature> &items){
    strikeWeaponServer(packet, bullets, enemies1, dead, items);
    strikeWeaponServer(packet, bullets, enemies2, dead, items);
    strikeWeaponServer(packet, bullets, enemies3, dead, items);
    strikeWeaponServer(packet, bullets, enemies4, dead, items);
    strikeWeaponServer(packet, bullets, enemies5, dead, items);
}

void strikeWeapon(std::vector <Weapon> &bullets, std::vector <Organism> &enemies, std::vector<Corpse> &dead, std::vector<Feature> &items){

    int numberBullets = 0;
    for(auto &i : bullets){
        int numberEnemies = 0;
        for(auto &k : enemies){

            if(i.isInsideOrganism(k)){
                k.health -= i.damage;
                bullets.erase(bullets.begin() + numberBullets);

                //DEAD
                if(k.health <= 0){
                    Corpse corpse(k.organism.getRotation(), k.organism.getPosition(), k.organism.getTexture()->getSize().x * k.organism.getScale().x);
                    corpse.corpse.setTexture(textureCorpse);
                    dead.push_back(corpse);
                    addFeature(items, k.organism.getPosition());

                    soundsAll.sound[7].play();

                    enemies.erase(enemies.begin() + numberEnemies);

                }
                break;
            }
            numberEnemies++;
        }
        numberBullets++;
    }
}

void strikeAllWeapon(std::vector <Weapon> &bullets, std::vector <Organism> &enemies1,
                     std::vector <Organism> &enemies2, std::vector <Organism> &enemies3, std::vector <Organism> &enemies4,
                     std::vector <Organism> &enemies5, std::vector<Corpse> &dead, std::vector<Feature> &items){
    strikeWeapon(bullets, enemies1, dead, items);
    strikeWeapon(bullets, enemies2, dead, items);
    strikeWeapon(bullets, enemies3, dead, items);
    strikeWeapon(bullets, enemies4, dead, items);
    strikeWeapon(bullets, enemies5, dead, items);
}

void updateBomb(std::vector<Bomb> &bombs, Time time){
    for(auto &i : bombs){
        i.timeBuffer += time.asSeconds();
        i.timeExplode += time.asSeconds();

        if(i.timeBuffer > timeBufferBomb){
            i.timeBuffer -= timeBufferBomb;

            if(i.textureNumber == 1){
                i.textureNumber = 2;
                i.weapon.setTexture(textureBomb2);
            } else {
                i.textureNumber = 1;
                i.weapon.setTexture(textureBomb1);
            }
        }

    }
}

void strikeBomb(const std::vector <Bomb> &bombs, std::vector <Organism> &enemies, std::vector<Corpse> &dead, std::vector<Feature> &items){

    int numberBombs = 0;
    for(auto &i : bombs){

        if(i.timeExplode < timeBombExplore){
            numberBombs++;
            continue;
        }

        int numberEnemies = 0;
        for(auto &k : enemies){

            float squareLenght = (k.organism.getPosition().x - i.weapon.getPosition().x)*(k.organism.getPosition().x - i.weapon.getPosition().x) +
                                 (k.organism.getPosition().y - i.weapon.getPosition().y)*(k.organism.getPosition().y - i.weapon.getPosition().y);

            if(squareLenght <= bombDistanceExplode){
                k.health -= i.damage;

                //DEAD
                if(k.health <= 0){
                    Corpse corpse(k.organism.getRotation(), k.organism.getPosition(), k.organism.getTexture()->getSize().x * k.organism.getScale().x);
                    corpse.corpse.setTexture(textureCorpse);
                    dead.push_back(corpse);
                    addFeature(items, k.organism.getPosition());

                    soundsAll.sound[7].play();

                    enemies.erase(enemies.begin() + numberEnemies);
                }
                break;
            }
            numberEnemies++;
        }
        std::cout << std::endl;
        numberBombs++;
    }

}

void strikeAllBomb(const std::vector <Bomb> &bombs, std::vector <Organism> &enemies1, std::vector <Organism> &enemies2,
                   std::vector <Organism> &enemies3, std::vector <Organism> &enemies4, std::vector <Organism> &enemies5,
                   std::vector<Corpse> &dead, std::vector<Feature> &items){
    strikeBomb(bombs, enemies1, dead, items);
    strikeBomb(bombs, enemies2, dead, items);
    strikeBomb(bombs, enemies3, dead, items);
    strikeBomb(bombs, enemies4, dead, items);
    strikeBomb(bombs, enemies5, dead, items);
}

void strikeBombClient(const std::vector <Bomb> &bombs, std::vector <Organism> &enemies, std::vector<Corpse> &dead, std::vector<Feature> &items){

    int numberBombs = 0;
    for(auto &i : bombs){

        if(i.timeExplode < timeBombExplore){
            numberBombs++;
            continue;
        }

        int numberEnemies = 0;
        for(auto &k : enemies){

            float squareLenght = (k.organism.getPosition().x - i.weapon.getPosition().x)*(k.organism.getPosition().x - i.weapon.getPosition().x) +
                                 (k.organism.getPosition().y - i.weapon.getPosition().y)*(k.organism.getPosition().y - i.weapon.getPosition().y);

            if(squareLenght <= bombDistanceExplode){
                k.health -= i.damage;

                //DEAD
                if(k.health <= 0){
                    Corpse corpse(k.organism.getRotation(), k.organism.getPosition(), k.organism.getTexture()->getSize().x * k.organism.getScale().x);
                    corpse.corpse.setTexture(textureCorpse);
                    dead.push_back(corpse);

                    soundsAll.sound[7].play();

                    enemies.erase(enemies.begin() + numberEnemies);
                }
                break;
            }
            numberEnemies++;
        }
        std::cout << std::endl;
        numberBombs++;
    }

}

void strikeAllBombClient(const std::vector <Bomb> &bombs, std::vector <Organism> &enemies1, std::vector <Organism> &enemies2,
                         std::vector <Organism> &enemies3, std::vector <Organism> &enemies4, std::vector <Organism> &enemies5,
                         std::vector<Corpse> &dead, std::vector<Feature> &items){
    strikeBombClient(bombs, enemies1, dead, items);
    strikeBombClient(bombs, enemies2, dead, items);
    strikeBombClient(bombs, enemies3, dead, items);
    strikeBombClient(bombs, enemies4, dead, items);
    strikeBombClient(bombs, enemies5, dead, items);
}

void strikeBombServer(Packet &packet, const std::vector <Bomb> &bombs, std::vector <Organism> &enemies, std::vector<Corpse> &dead, std::vector<Feature> &items){

    int numberBombs = 0;
    for(auto &i : bombs){

        if(i.timeExplode < timeBombExplore){
            numberBombs++;
            continue;
        }

        int numberEnemies = 0;
        for(auto &k : enemies){

            float squareLenght = (k.organism.getPosition().x - i.weapon.getPosition().x)*(k.organism.getPosition().x - i.weapon.getPosition().x) +
                                 (k.organism.getPosition().y - i.weapon.getPosition().y)*(k.organism.getPosition().y - i.weapon.getPosition().y);

            if(squareLenght <= bombDistanceExplode){
                k.health -= i.damage;

                //DEAD
                if(k.health <= 0){
                    Corpse corpse(k.organism.getRotation(), k.organism.getPosition(), k.organism.getTexture()->getSize().x * k.organism.getScale().x);
                    corpse.corpse.setTexture(textureCorpse);
                    dead.push_back(corpse);
                    addFeatureServer(packet, items, k.organism.getPosition());

                    soundsAll.sound[7].play();

                    enemies.erase(enemies.begin() + numberEnemies);
                }
                break;
            }
            numberEnemies++;
        }
        std::cout << std::endl;
        numberBombs++;
    }

}

void strikeAllBombServer(Packet &packet, const std::vector <Bomb> &bombs, std::vector <Organism> &enemies1, std::vector <Organism> &enemies2,
                         std::vector <Organism> &enemies3, std::vector <Organism> &enemies4, std::vector <Organism> &enemies5,
                         std::vector<Corpse> &dead, std::vector<Feature> &items){
    strikeBombServer(packet, bombs, enemies1, dead, items);
    strikeBombServer(packet, bombs, enemies2, dead, items);
    strikeBombServer(packet, bombs, enemies3, dead, items);
    strikeBombServer(packet, bombs, enemies4, dead, items);
    strikeBombServer(packet, bombs, enemies5, dead, items);
}

void deleteBomb(std::vector <Bomb> &bombs){
    int numberBombs = 0;

    for(auto &i : bombs){
        if(i.timeExplode >= timeBombExplore){
            soundsAll.sound[3].play();
            bombs.erase(bombs.begin() + numberBombs);
        }

        numberBombs++;
    }
}

void moveEnemies2(std::vector <Organism> &enemies, Organism &player, Time time){
    for(auto &i :enemies){
        if(i.aim == player.aim){
            if(i.health < i.fullHealth*4.0/5 && i.health > i.fullHealth*1.0/2){
                i.path.pathIterator = 1;

            } else if(i.health < i.fullHealth*1.0/3 && i.health > 0){
                i.path.pathIterator = 2;

            }
            if(!player.isInsideOrganism(i) && !i.isInsideOrganism(player)){

                i.path.numberAttackNow = 0;
                i.direction = player.organism.getPosition()-i.organism.getPosition();

                if(i.move(time))
                    i.walkUpdate(time);

                else{
                    i.path.numberWalkNow = 0;
                    Time time1;
                    i.attackUpdate(time);
                }

            } else{
                i.path.numberWalkNow = 0;
                i.attackUpdate(time);
                float damage = i.damage*time.asSeconds();

                if(player.protection > 0){
                    player.protection -= damage * 0.8;
                    player.health -= damage * 0.2;
                } else
                    player.health -= damage;
            }
        }
    }
}

void moveEnemies(std::vector <Organism> &enemies, Organism &player, Time time){
    for(auto &i :enemies){
        if(i.health < i.fullHealth*4.0/5 && i.health > i.fullHealth*1.0/2){
            i.path.pathIterator = 1;

        } else if(i.health < i.fullHealth*1.0/3 && i.health > 0){
            i.path.pathIterator = 2;

        }
        if(!player.isInsideOrganism(i) && !i.isInsideOrganism(player)){

            i.path.numberAttackNow = 0;
            i.direction = player.organism.getPosition()-i.organism.getPosition();

            if(i.move(time))
                i.walkUpdate(time);

            else{
                i.path.numberWalkNow = 0;
                Time time1;
                i.attackUpdate(time);
            }

        } else{
            i.path.numberWalkNow = 0;
            i.attackUpdate(time);
            float damage = i.damage*time.asSeconds();

            if(player.protection > 0){
                player.protection -= damage * 0.8;
                player.health -= damage * 0.2;
            } else
                player.health -= damage;
        }
    }
}

void moveAllEnemies2(std::vector <Organism> &enemies1, std::vector <Organism> &enemies2, std::vector <Organism> &enemies3,
                     std::vector <Organism> &enemies4, std::vector <Organism> &enemies5, Organism &player, Time time){
    moveEnemies2(enemies1, player, time);
    moveEnemies2(enemies2, player, time);
    moveEnemies2(enemies3, player, time);
    moveEnemies2(enemies4, player, time);
    moveEnemies2(enemies5, player, time);
}
void moveAllEnemies(std::vector <Organism> &enemies1, std::vector <Organism> &enemies2, std::vector <Organism> &enemies3,
                    std::vector <Organism> &enemies4, std::vector <Organism> &enemies5, Organism &player, Time time){
    moveEnemies(enemies1, player, time);
    moveEnemies(enemies2, player, time);
    moveEnemies(enemies3, player, time);
    moveEnemies(enemies4, player, time);
    moveEnemies(enemies5, player, time);
}

void deleteWeapon(std::vector <Weapon> &bullets, Time time){
    int j = 0;
    for(auto &i : bullets){
        if(!isInside(i.weapon, 0)){
            bullets.erase(bullets.begin() + j);
        }
        j++;
    }
}

void movePlayer(View &gameView, Organism &player, std::vector<Organism> &enemies1, std::vector<Organism> &enemies2,
                std::vector<Organism> &enemies3, std::vector<Organism> &enemies4, std::vector<Organism> &enemies5,Time time, Bar &bubbleBar){
    player.walkUpdate(time);

    //May Add chance to move through zombies
    bool abilityGoRight = true;
    bool abilityGoLeft = true;
    bool abilityGoUp = true;
    bool abilityGoDown = true;

    for(auto &i : enemies1){
        if(!isInside(gameView, i.organism, 0))
            continue;
        if(player.isInsideOrganism(i) || i.isInsideOrganism(player)){
            Vector2f d = i.organism.getPosition() - player.organism.getPosition();

            if((d.x > 0) && (d.x == maxmod(d.x, d.y)))
                abilityGoRight = false;
            if((d.x < 0) && (d.x == maxmod((d.x), d.y)))
                abilityGoLeft = false;
            if((d.y < 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoUp = false;
            if((d.y > 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoDown = false;
        }
    }
    for(auto &i : enemies2){
        if(!isInside(gameView, i.organism, 0))
            continue;
        if(player.isInsideOrganism(i) || i.isInsideOrganism(player)){
            Vector2f d = i.organism.getPosition() - player.organism.getPosition();

            if((d.x > 0) && (d.x == maxmod(d.x, d.y)))
                abilityGoRight = false;
            if((d.x < 0) && (d.x == maxmod((d.x), d.y)))
                abilityGoLeft = false;
            if((d.y < 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoUp = false;
            if((d.y > 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoDown = false;
        }
    }
    for(auto &i : enemies3){
        if(!isInside(gameView, i.organism, 0))
            continue;
        if(player.isInsideOrganism(i) || i.isInsideOrganism(player)){
            Vector2f d = i.organism.getPosition() - player.organism.getPosition();

            if((d.x > 0) && (d.x == maxmod(d.x, d.y)))
                abilityGoRight = false;
            if((d.x < 0) && (d.x == maxmod((d.x), d.y)))
                abilityGoLeft = false;
            if((d.y < 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoUp = false;
            if((d.y > 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoDown = false;
        }
    }
    for(auto &i : enemies4){
        if(!isInside(gameView, i.organism, 0))
            continue;
        if(player.isInsideOrganism(i) || i.isInsideOrganism(player)){
            Vector2f d = i.organism.getPosition() - player.organism.getPosition();

            if((d.x > 0) && (d.x == maxmod(d.x, d.y)))
                abilityGoRight = false;
            if((d.x < 0) && (d.x == maxmod((d.x), d.y)))
                abilityGoLeft = false;
            if((d.y < 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoUp = false;
            if((d.y > 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoDown = false;
        }
    }
    for(auto &i : enemies5){
        if(!isInside(gameView, i.organism, 0))
            continue;
        if(player.isInsideOrganism(i) || i.isInsideOrganism(player)){
            Vector2f d = i.organism.getPosition() - player.organism.getPosition();

            if((d.x > 0) && (d.x == maxmod(d.x, d.y)))
                abilityGoRight = false;
            if((d.x < 0) && (d.x == maxmod((d.x), d.y)))
                abilityGoLeft = false;
            if((d.y < 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoUp = false;
            if((d.y > 0) && (d.y == maxmod(d.x, d.y)))
                abilityGoDown = false;
        }
    }

    int down = 0, right = 0;
    if((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && isInside(player.organism, 1) && abilityGoUp)
        down--;
    if((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && isInside(player.organism, 3) && abilityGoDown)
        down++;
    if((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && isInside(player.organism, 4) && abilityGoLeft)
        right--;
    if((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && isInside(player.organism, 2) && abilityGoRight)
        right++;

    if(right != 0 || down != 0){
        player.direction = Vector2f(right, down);
        player.move(time);
    }

    //if in water
    if(background[(int)(player.organism.getPosition().x / sizeTile)][(int)(player.organism.getPosition().y / sizeTile)].type == 18){
        if(bubbleBar.value > 0){
            bubbleBar.value -= time.asSeconds() * 20;
        } else{
            player.health -= time.asSeconds() * 10;
        }
        player.organism.setTexture(texturePlayerInWater);
    } else if(bubbleBar.value < fullBubbles){
        bubbleBar.value += time.asSeconds() * 8;
    }
}

void movePlayers(Organism &player1, Organism &player2, std::vector<Organism> &enemies1, std::vector<Organism> &enemies2,
                 std::vector<Organism> &enemies3, std::vector<Organism> &enemies4, std::vector<Organism> &enemies5,Time time, Bar &bubbleBar){
    player1.walkUpdate(time);
    player2.walkUpdate(time);

    //May Add chance to move through zombies
    bool abilityGoRight = true;
    bool abilityGoLeft = true;
    bool abilityGoUp = true;
    bool abilityGoDown = true;

//    int down = 0, right = 0;
//    if((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && isInside(player1.organism, 1) && abilityGoUp)
//        down--;
//    if((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && isInside(player1.organism, 3) && abilityGoDown)
//        down++;
//    if((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && isInside(player1.organism, 4) && abilityGoLeft)
//        right--;
//    if((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && isInside(player1.organism, 2) && abilityGoRight)
//        right++;


    int down = 0, right = 0;
    if(player1.aim == 1){
        if((Keyboard::isKeyPressed(Keyboard::Up)) && isInside(player1.organism, 1) && abilityGoUp)
            down--;
        if((Keyboard::isKeyPressed(Keyboard::Down)) && isInside(player1.organism, 3) && abilityGoDown)
            down++;
        if((Keyboard::isKeyPressed(Keyboard::Left)) && isInside(player1.organism, 4) && abilityGoLeft)
            right--;
        if((Keyboard::isKeyPressed(Keyboard::Right)) && isInside(player1.organism, 2) && abilityGoRight)
            right++;
    } else if(player1.aim == 2){
        if((Keyboard::isKeyPressed(Keyboard::W)) && isInside(player1.organism, 1) && abilityGoUp)
            down--;
        if((Keyboard::isKeyPressed(Keyboard::S)) && isInside(player1.organism, 3) && abilityGoDown)
            down++;
        if((Keyboard::isKeyPressed(Keyboard::A)) && isInside(player1.organism, 4) && abilityGoLeft)
            right--;
        if((Keyboard::isKeyPressed(Keyboard::D)) && isInside(player1.organism, 2) && abilityGoRight)
            right++;
    }


    if(right != 0 || down != 0){
        player1.direction = Vector2f(right, down);
        player1.move(time);
    }

    //if in water
    if(background[(int)(player1.organism.getPosition().x / sizeTile)][(int)(player1.organism.getPosition().y / sizeTile)].type == 18){
        if(bubbleBar.value > 0){
            bubbleBar.value -= time.asSeconds() * 20;
        } else{
            player1.health -= time.asSeconds() * 10;
        }
        player1.organism.setTexture(texturePlayerInWater);
    } else if(bubbleBar.value < fullBubbles){
        bubbleBar.value += time.asSeconds() * 8;
    }

    if((player2.organism.getPosition().x / sizeTile > 0 && player2.organism.getPosition().x / sizeTile < sizeWindow.x)&&
       (player2.organism.getPosition().y / sizeTile > 0 && player2.organism.getPosition().y / sizeTile < sizeWindow.x)){
        //player2.move(time);
        if(background[(int)(player2.organism.getPosition().x / sizeTile)][(int)(player2.organism.getPosition().y / sizeTile)].type == 18)
            player2.organism.setTexture(texturePlayerInWater);
    }


}

void clearAll(std::vector<Organism> &zombies, std::vector<Organism> &zombies1, std::vector<Organism> &zombies2, std::vector<Organism> &zombies3, std::vector<Organism> &dogs,
              std::vector<Weapon> &bullets, std::vector<Bomb> &bombs, std::vector <Corpse> &dead, std::vector<Feature> &items, std::vector<Opaque> &houses, std::vector<ConvexShape> &trapezes){

    trees1.clear();
    trees2.clear();
    trees3.clear();
    trees4.clear();
    trees5.clear();
    zombies.clear();
    zombies1.clear();
    zombies2.clear();
    zombies3.clear();
    dogs.clear();
    bullets.clear();
    bombs.clear();
    dead.clear();
    items.clear();
    houses.clear();
    trapezes.clear();

    textureZombie1PathsWalkFullHealth.clear();
    textureZombie1PathsWalkHalfHealth.clear();
    textureZombie1PathsWalkSmallHealth.clear();
    textureZombie1PathsAttackFullHealth.clear();
    textureZombie1PathsAttackHalfHealth.clear();
    textureZombie1PathsAttackSmallHealth.clear();

    textureZombie2PathsWalkFullHealth.clear();
    textureZombie2PathsWalkHalfHealth.clear();
    textureZombie2PathsWalkSmallHealth.clear();
    textureZombie2PathsAttackFullHealth.clear();
    textureZombie2PathsAttackHalfHealth.clear();
    textureZombie2PathsAttackSmallHealth.clear();

    textureZombie3PathsWalkFullHealth.clear();
    textureZombie3PathsWalkHalfHealth.clear();
    textureZombie3PathsWalkSmallHealth.clear();
    textureZombie3PathsAttackFullHealth.clear();
    textureZombie3PathsAttackHalfHealth.clear();
    textureZombie3PathsAttackSmallHealth.clear();

    textureDogPathsWalkFullHealth.clear();
    textureDogPathsAttackFullHealth.clear();

    textureZombiePathsWalkFullHealth.clear();
    textureZombiePathsWalkHalfHealth.clear();
    textureZombiePathsWalkSmallHealth.clear();
    textureZombiePathsAttackFullHealth.clear();
    textureZombiePathsAttackHalfHealth.clear();
    textureZombiePathsAttackSmallHealth.clear();

    texturePlayerPaths.clear();

    backgroundTypes.clear();

}

void updateMusic(float &timeBuffer6, float &timeBuffer7, Organism &player, View &gameView,
                 std::vector<Organism> &zombies, std::vector<Organism> &zombies1, std::vector<Organism> &zombies2,
                 std::vector<Organism> &zombies3, std::vector<Organism> &dogs){
    //sounds
    if(timeBuffer6 > 10){
        timeBuffer6 = 0;
        soundsAll.sound[4].play();
    }
    if(timeBuffer7 > 10 && player.health < playerFullHealth / 2){
        timeBuffer7 = 0;
        soundsAll.sound[5].play();
    } else if(player.health > playerFullHealth / 2){
        soundsAll.sound[5].pause();
    }

    //get total number of zombies
    int numberZombiesInGameView = 0;
    for(auto &i  : zombies){
        if(isInside(gameView, i.organism.getPosition(), 0))
            numberZombiesInGameView++;

    }
    for(auto &i  : zombies1){
        if(isInside(gameView, i.organism.getPosition(), 0))
            numberZombiesInGameView++;

    }
    for(auto &i  : zombies2){
        if(isInside(gameView, i.organism.getPosition(), 0))
            numberZombiesInGameView++;

    }
    for(auto &i  : zombies3){
        if(isInside(gameView, i.organism.getPosition(), 0))
            numberZombiesInGameView++;

    }
    for(auto &i  : dogs){
        if(isInside(gameView, i.organism.getPosition(), 0))
            numberZombiesInGameView++;

    }

    if(numberZombiesInGameView > 200){
        if(soundsAll.sound[6].getStatus() != soundsAll.sound[6].Playing)
            soundsAll.sound[6].play();
    } else if(numberZombiesInGameView < 100){
        soundsAll.sound[6].pause();
    }

    //water
    if(player.getPosition().type == 18){
        if(soundsAll.sound[10].getStatus() != soundsAll.sound[10].Playing)
            soundsAll.sound[10].play();
    } else {
        soundsAll.sound[10].pause();
    }
    //grass
    if(player.getPosition().type == 21 || player.getPosition().type == 80
       || player.getPosition().type == 16 || player.getPosition().type == 17){
        if(soundsAll.sound[11].getStatus() != soundsAll.sound[11].Playing)
            soundsAll.sound[11].play();
    } else {
        soundsAll.sound[11].pause();
    }
    //sand
    if(player.getPosition().type == 20){
        if(soundsAll.sound[12].getStatus() != soundsAll.sound[12].Playing)
            soundsAll.sound[12].play();
    } else {
        soundsAll.sound[12].pause();
    }
}

void rotateEnemies(std::vector<Organism> &zombies, std::vector<Organism> &zombies1, std::vector<Organism> &zombies2,
                   std::vector<Organism> &zombies3, std::vector<Organism> &dogs, Organism &player){
    for(auto &i : zombies){
        i.rotate(player.organism.getPosition());
    }
    for(auto &i : zombies1){
        i.rotate(player.organism.getPosition());
    }
    for(auto &i : zombies2){
        i.rotate(player.organism.getPosition());
    }
    for(auto &i : zombies3){
        i.rotate(player.organism.getPosition());
    }
    for(auto &i : dogs){
        i.rotate(player.organism.getPosition());
    }
}

void rotateEnemies2(std::vector<Organism> &zombies, std::vector<Organism> &zombies1, std::vector<Organism> &zombies2,
                    std::vector<Organism> &zombies3, std::vector<Organism> &dogs, Organism &player){
    for(auto &i : zombies){
        if(i.aim == player.aim)
            i.rotate(player.organism.getPosition());
    }
    for(auto &i : zombies1){
        if(i.aim == player.aim)
            i.rotate(player.organism.getPosition());
    }
    for(auto &i : zombies2){
        if(i.aim == player.aim)
            i.rotate(player.organism.getPosition());
    }
    for(auto &i : zombies3){
        if(i.aim == player.aim)
            i.rotate(player.organism.getPosition());
    }
    for(auto &i : dogs){
        if(i.aim == player.aim)
            i.rotate(player.organism.getPosition());
    }
}
