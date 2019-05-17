#include "background.h"
#include "init.h"
#include "draw.h"
#include "thread"
#include "pages.h"
#include "wave.h"
#include "shadows.h"
#include "endGame.h"
#include <SFML/Network.hpp>

#pragma once

void runServer(unsigned short serverPort){
// Create a socket to receive a message from anyone
    sf::UdpSocket socket;
    sf::IpAddress ipClient1;
    sf::IpAddress ipClient2;
    unsigned short portClient1;
    unsigned short portClient2;
    sf::Packet packet;


    if (socket.bind(serverPort) != sf::Socket::Done)
        return;

    std::cout << "Server is listening to port " << serverPort << ", waiting for a message... " << std::endl;

    //get Ip and port 1 player
    if (socket.receive(packet, ipClient1, portClient1) != sf::Socket::Done)
        return;
    packet.clear();
    std::cout << "Message received from client1 " << ipClient1 << std::endl;

    // Send an answer to the 1 player
    if (socket.send(packet, ipClient1, portClient1) != sf::Socket::Done)
        return;
    std::cout << "Message sent to the client1:" << std::endl;


    //get Ip and port 2 player
    if (socket.receive(packet, ipClient2, portClient2) != sf::Socket::Done)
        return;
    packet.clear();
    std::cout << "Message received from client2 " << ipClient2 << std::endl;


    // Send an answer to the 2 player
    if (socket.send(packet, ipClient2, portClient2) != sf::Socket::Done)
        return;
    std::cout << "Message sent to the client2:" << std::endl;

//    srand(time(NULL));
//    musicAll.music[numberMusicGame].play();
//    hard = 5;
//
//    std::vector<Weapon> bullets;
//    std::vector<Bomb> bombs;
//    std::vector<Organism> zombies;
//    std::vector<Organism> zombies1;
//    std::vector<Organism> zombies2;
//    std::vector<Organism> zombies3;
//    std::vector<Organism> dogs;
//    std::vector<Corpse> dead;
//    std::vector<Feature> items;
//    std::vector<Opaque> houses;
//    std::vector<ConvexShape> trapezes;
//
//    setTextures();
//    setBackground(houses);
//
//
//
//    //Create PlayerSprite
//    Sprite spritePlayer(texturePlayerPaths[0]);
//    //Create ZombieSprite
//    Sprite spriteZombie(textureZombiePathsWalkFullHealth[0]);
//    //Create Zombie1Sprite
//    Sprite spriteZombie1(textureZombie1PathsWalkFullHealth[0]);
//    spriteZombie1.setScale(3, 3);
//    //Create Zombie2Sprite
//    Sprite spriteZombie2(textureZombie2PathsWalkFullHealth[0]);
//    spriteZombie2.setScale(1.5, 1.5);
//    //Create Zombie3prite
//    Sprite spriteZombie3(textureZombie3PathsWalkFullHealth[0]);
//    spriteZombie3.setScale(1.5, 1.5);
//    //Create DogSprite
//    Sprite spriteDog(textureDogPathsWalkFullHealth[0]);
//    //Create BulletSprite
//    textureBullet1.loadFromFile(pathToDirectory + "pngForGame/bullet1.png");
//    Sprite spriteBullet1(textureBullet1);
//    textureBullet2.loadFromFile(pathToDirectory + "pngForGame/bullet2.png");
//    Sprite spriteBullet2(textureBullet2);
//    //Create BombSprite
//    textureBomb1.loadFromFile(pathToDirectory + "pngForGame/bomb1.png");
//    Sprite spriteBomb1(textureBomb1);
//    textureBomb2.loadFromFile(pathToDirectory + "pngForGame/bomb2.png");
//    Sprite spriteBomb2(textureBomb2);
//    //Create items Textures
//    textureHeart.loadFromFile(pathToDirectory + "pngForGame/heart.png");
//    textureShield.loadFromFile(pathToDirectory + "pngForGame/shield.png");
//    textureBullet.loadFromFile(pathToDirectory + "pngForGame/bullets.png");
//    textureBomb.loadFromFile(pathToDirectory + "pngForGame/bombs.png");
//
//
//    //Init Player
//    texturePlayerInWater.loadFromFile(pathToDirectory + "pngForGame/playerInWater.png");
//
//    Organism player(playerFullHealth, playerFullProtection, playerSpeed, speedDrawPlayer, 0, false,
//                    texturePlayerPaths, texturePlayerPaths, texturePlayerPaths, numberPlayerPathsWalk, 0.01,
//                    texturePlayerPaths, texturePlayerPaths, texturePlayerPaths, numberPlayerPathsWalk, 0.01, spritePlayer);
//    while(true){
//        player.organism.setPosition(rand() % (sizeWindow.x * sizeTile - 200) + 100, rand() % (sizeWindow.y * sizeTile - 200) + 100);
//        if(player.getPosition().crossEnemy)
//            break;
//    }
//    Vector2u playerSize = player.organism.getTexture()->getSize();
//    player.organism.setOrigin((float)playerSize.x/2, (float)playerSize.y/2);
//    player.organism.setScale(0.6, 0.6);
//
//    //Create shadow
//    Texture textureShadow;
//    textureShadow.loadFromFile(pathToDirectory + "pngForGame/shadow.png");
//    Sprite spriteShadow(textureShadow);
//    spriteShadow.setOrigin(spriteShadow.getTexture()->getSize().x / 2, spriteShadow.getTexture()->getSize().y / 2);
//    spriteShadow.setColor(Color(255, 255, 255, 180));
//    spriteShadow.setPosition(player.organism.getPosition());
//    spriteShadow.setScale(0.5, 0.5);
//
//    textureCorpse.loadFromFile(corpsePath);
//
//    Clock clock;
//    Clock clockPause;
//    Clock clock6;
//
//    float timeBuffer6 = 0;
//    float timeBuffer7 = 0;
//    float timeBuffer8 = 0;
//    float timeBuffer9 = 0;
//    float timeBufferBombInit = 0;
//    float timebufferMinimapInit = 0;
//    float timeBufferMinimap = 0;
//
//    bool minimap = false;
//    Time time,time6, timePause;
//    timePause = clock6.restart();
//
//    //update Window
//
//    while (1)
//    {
//        time = clock.restart();
//        time6 = clock6.getElapsedTime();
//
//        timeBuffer6 += time.asSeconds();
//        timeBuffer7 += time.asSeconds();
//        timeBuffer8 += time.asSeconds();
//        timeBuffer9 += time.asSeconds();
//        timeBufferBombInit += time.asSeconds();
//        timeBufferMinimap += time.asSeconds();
//        timebufferMinimapInit += time.asSeconds();
//
//        std::cout << time.asSeconds()<< std::endl;
//
////1
//        time6 = clock6.getElapsedTime();
//        std::cout << " 1: "<< time6.asSeconds();
//
//
////2
//        time6 = clock6.getElapsedTime();
//        std::cout << " 2: "<<time6.asSeconds();
//
//        moveEnemies(zombies, player, time);
//        moveEnemies(zombies1, player, time);
//        moveEnemies(zombies2, player, time);
//        moveEnemies(zombies3, player, time);
//        moveEnemies(dogs, player, time);
//
////3
//        time6 = clock6.getElapsedTime();
//        std::cout <<" 3: "<< time6.asSeconds();
//
//        updateBomb(bombs, time);
//
////        strikeWeapon(gameView, bullets, zombies, dead, items);
////        strikeWeapon(gameView, bullets, zombies1, dead, items);
////        strikeWeapon(gameView, bullets, zombies2, dead, items);
////        strikeWeapon(gameView, bullets, zombies3, dead, items);
////        strikeWeapon(gameView, bullets, dogs, dead, items);
//
//        strikeBomb(bombs, zombies, dead, items);
//        strikeBomb(bombs, zombies1, dead, items);
//        strikeBomb(bombs, zombies2, dead, items);
//        strikeBomb(bombs, zombies3, dead, items);
//        strikeBomb(bombs, dogs, dead, items);
//
////        deleteWeapon(gameView, bullets, time);
//
//        deleteBomb(bombs);
//
////4
//        time6 = clock6.getElapsedTime();
//        std::cout << " 4: "<< time6.asSeconds();
//
//
////        movePlayer(gameView, player, zombies, zombies1, zombies2, zombies3, dogs, time, bubbleBar);
//
//        setShadow(houses, trapezes, player.organism.getPosition());
//        spriteShadow.setPosition(player.organism.getPosition());
//
////        updateFeatures(items, player, time, bulletBar, bombBar);
//
//
//        //sleep(seconds(3));
//
////5
//        time6 = clock6.getElapsedTime();
//        std::cout << " 5: " << time6.asSeconds();
//
//
//        for(auto &i : zombies)
//            i.rotate(player.organism.getPosition());
//        for(auto &i : zombies1)
//            i.rotate(player.organism.getPosition());
//        for(auto &i : zombies2)
//            i.rotate(player.organism.getPosition());
//        for(auto &i : zombies3)
//            i.rotate(player.organism.getPosition());
//        for(auto &i : dogs)
//            i.rotate(player.organism.getPosition());
//
//        int j = 0;
//        for(auto &i : bullets){
//            if(!i.move(time))
//                bullets.erase(bullets.begin() + j);
//            else
//                j++;
//        }
//
//        j = 0;
//        for(auto &i : dead){
//            i.update(time);
//            if(i.isDisappeared())
//                dead.erase(dead.begin() + j);
//            else
//                j++;
//        }
//
//        j = 0;
//        for(auto &i : items){
//            i.update(time);
//            if(i.isDisappeared())
//                items.erase(items.begin() + j);
//            else
//                j++;
//        }
//
//        //gameViewUpdate(gameView, windowSent.window, player, time);
//
//
//        //pause the game
//        if(Keyboard::isKeyPressed(Keyboard::Space) && timeBuffer9 > 0.3){
//            timeBuffer9 = 0;
//            clockPause.restart();
//            soundsAll.stop();
//
//            sleep(seconds(0.3));
//            while(!Keyboard::isKeyPressed(Keyboard::Space)){
//                sleep(seconds(0.01));
//            }
//            clock.restart();
//            timePause += clockPause.getElapsedTime();
//        }
//
//        if(Keyboard::isKeyPressed(Keyboard::Tab) && timebufferMinimapInit > 0.2){
//            timebufferMinimapInit = 0;
//            if(minimap)
//                minimap = false;
//            else
//                minimap = true;
//        }
//
//
//        //6
//        time6 = clock6.getElapsedTime();
//        std::cout << " 6: " << time6.asSeconds();
//
//        //7
//        time6 = clock6.getElapsedTime();
//        std::cout << " 7: " << time6.asSeconds();
//
////        createWave(windowSent.window, windowSent.mode, gameView, time6, time, spriteZombie, spriteZombie1, spriteZombie2, spriteZombie3, spriteDog,
////                   zombies, zombies1, zombies2, zombies3, dogs);
//
//
////8
//        time6 = clock6.getElapsedTime();
//        std::cout << " 8: " << time6.asSeconds();
//
//        std::cout << "End"<< std::endl;
//
//
//        if(player.health <= 0){
////            thread.terminate();
////            clearAll(zombies, zombies1, zombies2, zombies3, dogs, bullets, bombs, dead, items, houses, trapezes);
////            soundsAll.stop();
////            endGame(windowSent.window, gameView, time6 - timePause, spriteCursor);
//
//            return;
//        }
//    }
}
