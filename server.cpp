#include "background.h"
#include "init.h"
#include "draw.h"
#include "thread"
#include "pages.h"
#include "wave.h"
#include "shadows.h"
#include "endGame.h"
#include <SFML/Network.hpp>
#include "network.h"

//#pragma once

using namespace sf;

Mutex mutex;


class Client{
public:
    Client(UdpSocket &socket, IpAddress ipClient1, IpAddress ipClient2, unsigned short portClient1,
           unsigned short portClient2, std::vector<Weapon> &bullets, std::vector<Bomb> &bombs,
           Organism &player1,  Organism &player2) :
            socket(socket),
            ipClient1(ipClient1),
            ipClient2(ipClient2),
            portClient1(portClient1),
            portClient2(portClient2),
            bullets(bullets),
            bombs(bombs),
            player1(player1),
            player2(player2){};
    UdpSocket &socket;
    IpAddress ipClient1;
    IpAddress ipClient2;
    unsigned short portClient1;
    unsigned short portClient2;
    std::vector<Weapon> &bullets;
    std::vector<Bomb> &bombs;
    Organism &player1;
    Organism &player2;
};

class ClientInfo{
public:
    ClientInfo(UdpSocket &socket, IpAddress ipClient1, IpAddress ipClient2, unsigned short portClient1,
           unsigned short portClient2) :
            socket(socket),
            ipClient1(ipClient1),
            ipClient2(ipClient2),
            portClient1(portClient1),
            portClient2(portClient2){};

    UdpSocket &socket;
    IpAddress ipClient1;
    IpAddress ipClient2;
    unsigned short portClient1;
    unsigned short portClient2;
};

void getFromClient(Client &A);
void getMusic(ClientInfo clientInfo);


int main(){

    sizeWindow.x = 500;
    sizeWindow.y = 500;
    hard = 1;

    unsigned short serverPort = 20000;

    UdpSocket socket;
    IpAddress ipClient1;
    IpAddress ipClient2;
    unsigned short portClient1;
    unsigned short portClient2;
    Packet packet;

    UdpSocket socketMusic;
    unsigned short portMusic = serverPort + 1;

    if(socketMusic.bind(portMusic) != Socket::Done)
        return 2;
    if (socket.bind(serverPort) != sf::Socket::Done)
        return 2;

    std::cout << "Server is listening to port " << serverPort << ", waiting for a message... " << std::endl;

    //get Ip and port 1 player
    if (socket.receive(packet, ipClient1, portClient1) != sf::Socket::Done)
        return 1;
    packet.clear();
    std::cout << "Message received from client1 " << ipClient1 << std::endl;

    // Send an answer to the 1 player
    if (socket.send(packet, ipClient1, portClient1) != sf::Socket::Done)
        return 1;
    std::cout << "Message sent to the client1:" << std::endl;


    //get Ip and port 2 player
    if (socket.receive(packet, ipClient2, portClient2) != sf::Socket::Done)
        return 1;
    packet.clear();
    std::cout << "Message received from client2 " << ipClient2 << std::endl;


    // Send an answer to the 2 player
    if (socket.send(packet, ipClient2, portClient2) != sf::Socket::Done)
        return 1;
    std::cout << "Message sent to the client2:" << std::endl;

    std::cout << "ipClient1: " << ipClient1<< std::endl;
    std::cout << "ipClient2: " << ipClient2<< std::endl;
    std::cout << "portClient1: " << portClient1<< std::endl;
    std::cout << "portClient2: " << portClient2<< std::endl;


    srand(time(NULL));

    std::vector<Weapon> bullets;
    std::vector<Bomb> bombs;
    std::vector<Organism> zombies;
    std::vector<Organism> zombies1;
    std::vector<Organism> zombies2;
    std::vector<Organism> zombies3;
    std::vector<Organism> dogs;
    std::vector<Corpse> dead;
    std::vector<Feature> items;
    std::vector<Opaque> houses;
    std::vector<ConvexShape> trapezes;

    setTextures();
    setBackground(houses);


    //Create PlayerSprite
    spritePlayer.setTexture(texturePlayerPaths[0]);
    //Create ZombieSprite
    spriteZombie.setTexture(textureZombiePathsWalkFullHealth[0]);
    //Create Zombie1Sprite
    spriteZombie1.setTexture(textureZombie1PathsWalkFullHealth[0]);
    spriteZombie1.setScale(3, 3);
    //Create Zombie2Sprite
    spriteZombie2.setTexture(textureZombie2PathsWalkFullHealth[0]);
    spriteZombie2.setScale(1.5, 1.5);
    //Create Zombie3prite
    spriteZombie3.setTexture(textureZombie3PathsWalkFullHealth[0]);
    spriteZombie3.setScale(1.5, 1.5);
    //Create DogSprite
    spriteDog.setTexture(textureDogPathsWalkFullHealth[0]);
    //Create BulletSprite
    textureBullet1.loadFromFile(pathToDirectory + "pngForGame/bullet1.png");
    spriteBullet1.setTexture(textureBullet1);
    textureBullet2.loadFromFile(pathToDirectory + "pngForGame/bullet2.png");
    spriteBullet2.setTexture(textureBullet2);
    //Create BombSprite
    textureBomb1.loadFromFile(pathToDirectory + "pngForGame/bomb1.png");
    spriteBomb1.setTexture(textureBomb1);
    textureBomb2.loadFromFile(pathToDirectory + "pngForGame/bomb2.png");
    spriteBomb2.setTexture(textureBomb2);
    //Create items Textures
    textureHeart.loadFromFile(pathToDirectory + "pngForGame/heart.png");
    textureShield.loadFromFile(pathToDirectory + "pngForGame/shield.png");
    textureBullet.loadFromFile(pathToDirectory + "pngForGame/bullets.png");
    textureBomb.loadFromFile(pathToDirectory + "pngForGame/bombs.png");
    //create corpseTexture
    textureCorpse.loadFromFile(corpsePath);
    //create bars
    Bar lifeBar(pathToDirectory + "pngForGame/heart.png", pathToDirectory + "fonts/font.ttf", Color(255, 0, 0, 255), 0.3);
    TimeBar timeBar(pathToDirectory + "fonts/font.ttf");
    Bar shieldBar(pathToDirectory + "pngForGame/shield.png", pathToDirectory + "fonts/font.ttf", Color(131, 131, 157, 255), 0.09);
    Bar bulletBar(pathToDirectory + "pngForGame/bullets.png", pathToDirectory + "fonts/font.ttf", Color(255, 204, 0, 255), 0.17);
    Bar bombBar(pathToDirectory + "pngForGame/bombs.png", pathToDirectory + "fonts/font.ttf", Color(25, 51, 77, 255), 0.07);
    Bar bubbleBar(pathToDirectory + "pngForGame/bubble.png", pathToDirectory + "fonts/font.ttf", Color(51, 255, 255, 255), 0.08);
    bubbleBar.value = fullBubbles;
    //Init Player
    texturePlayerInWater.loadFromFile(pathToDirectory + "pngForGame/playerInWater.png");


    Clock clock;
    Clock clockPause;
    Clock clock6;

    float timeBuffer6 = 0;
    float timeBuffer7 = 0;
    float timeBuffer8 = 0;
    float timeBuffer9 = 0;
    float timeBufferBombInit = 0;
    float timebufferMinimapInit = 0;
    float timeBufferMinimap = 0;
    float timeBufferHard = 0;

    bool minimap = false;
    Time time,time6;

//    Draw A(windowSent.window, gameView, zombies, zombies1, zombies2, zombies3, dogs, dead, bullets, bombs, items, trapezes,
//           player, lifeBar, bubbleBar, shieldBar, bulletBar, bombBar, timeBar, spriteCursor, spriteShadow);

    packet.clear();

    std::cout << "Map is packing for the first client: " << std::endl;
    for(int i = 0; i < sizeWindow.x; i++){
        for(int j = 0; j < sizeWindow.y; j++){
            packet << SendType(packetType::map);
            packet << background[i][j];
        }
        packet << SendType(packetType::end);

        socket.send(packet, ipClient1, portClient1);
        sleep(seconds(0.005));
//        std::cout << "Map is sended to the first client: " << i << std::endl;
        packet.clear();
    }
    std::cout << "Map is sent to the first client: " << std::endl;

    std::cout << "Map is packing for the second client: " << std::endl;
    for(int i = 0; i < sizeWindow.x; i++){
        for(int j = 0; j < sizeWindow.y; j++){
            packet << SendType(packetType::map);
            packet << background[i][j];
        }
        packet << SendType(packetType::end);

        //socket.send(packet, ipClient1, portClient1);
        socket.send(packet, ipClient2, portClient2);
        sleep(seconds(0.01));
        packet.clear();
    }
    std::cout << "Map is sent to the second client: " << std::endl;


    //send trees
    packet.clear();

    for(auto &i : trees1){
        packet << SendType(packetType::tree);
        packet << SendTree(i, 1);
    }
    for(auto &i : trees2){
        packet << SendType(packetType::tree);
        packet << SendTree(i, 2);
    }
    for(auto &i : trees3){
        packet << SendType(packetType::tree);
        packet << SendTree(i, 3);
    }
    for(auto &i : trees4){
        packet << SendType(packetType::tree);
        packet << SendTree(i, 4);
    }
    for(auto &i : trees5){
        packet << SendType(packetType::tree);
        packet << SendTree(i, 5);
    }
    packet << SendType(packetType::end);

    socket.send(packet, ipClient1, portClient1);
    socket.send(packet, ipClient2, portClient2);
    packet.clear();

    for(auto &i :houses){
        packet << SendType(packetType::opaque);
        packet << i;
    }
    packet << SendType(packetType::end);

    socket.send(packet, ipClient1, portClient1);
    socket.send(packet, ipClient2, portClient2);
    packet.clear();


    Organism player1 = initPlayer();
    Organism player2 = initPlayer();

    SendPlayer sendPlayer1(player1.organism.getPosition(), player1.direction, player1.health, player1.organism.getRotation(), player1.aim);
    SendPlayer sendPlayer2(player2.organism.getPosition(), player2.direction, player2.health, player2.organism.getRotation(), player2.aim);


    packet << SendType(packetType ::player) << sendPlayer1 << sendPlayer2 << SendType(packetType ::end);
    socket.send(packet, ipClient1, portClient1);
    packet.clear();
    std::cout << "Players are sent to the first client: " << std::endl;

    packet << SendType(packetType ::player) << sendPlayer2 << sendPlayer1 << SendType(packetType ::end);
    socket.send(packet, ipClient2, portClient2);
    packet.clear();
    std::cout << "Players are sent to the second client: " << std::endl;

//    sleep(seconds(1));

    Client A(socket, ipClient1, ipClient2, portClient1, portClient2, bullets, bombs, player1, player2);

    Thread thread(getFromClient, A);
    thread.launch();


    ClientInfo clientInfo(socketMusic, ipClient1, ipClient2, portClient1 + 1, portClient2 + 1);
    Thread threadMusic(getMusic, clientInfo);
    threadMusic.launch();


    while (true)
    {
        time = clock.restart();

        timeBuffer6 += time.asSeconds();
        timeBuffer7 += time.asSeconds();
        timeBuffer8 += time.asSeconds();
        timeBuffer9 += time.asSeconds();
        timeBufferBombInit += time.asSeconds();
        timeBufferMinimap += time.asSeconds();
        timebufferMinimapInit += time.asSeconds();
        timeBufferHard += time.asSeconds();

        if(timeBufferHard > 10){
            timeBufferHard = 0;
            hard += 0.01;
        }

//        std::cout << time.asSeconds()<< std::endl;
//        time6 = clock6.getElapsedTime();
//        std::cout << " 2: "<<time6.asSeconds();

        //mutex.lock();

        moveAllEnemies2(zombies, zombies1, zombies2, zombies3, dogs, player1, time);
        moveAllEnemies2(zombies, zombies1, zombies2, zombies3, dogs, player2, time);

//        time6 = clock6.getElapsedTime();
//        std::cout <<" 3: "<< time6.asSeconds();

        updateBomb(bombs, time);

        strikeAllWeaponServer(packet, bullets, zombies, zombies1, zombies2,
                        zombies3, dogs, dead, items);

        strikeAllBombServer(packet, bombs, zombies, zombies1, zombies2, zombies3,
                      dogs, dead, items);

        deleteWeapon(bullets, time);
        deleteBomb(bombs);

////4
//        time6 = clock6.getElapsedTime();
//        std::cout << " 4: "<< time6.asSeconds();

        movePlayers(player1, player2, zombies, zombies1, zombies2, zombies3, dogs, time, bubbleBar);

        updateFeatures2(items, player1, player2, time, bulletBar, bombBar);

////5
//        time6 = clock6.getElapsedTime();
//        std::cout << " 50: " << time6.asSeconds();

        rotateEnemies(zombies, zombies1, zombies2, zombies3, dogs, player1);
        rotateEnemies(zombies, zombies1, zombies2, zombies3, dogs, player2);


        int j = 0;
        for(auto &i : bullets){
            if(!i.move(time))
                bullets.erase(bullets.begin() + j);
            else
                j+=2;
        }

        j = 0;
        for(auto &i : dead){
            i.update(time);
            if(i.isDisappeared())
                dead.erase(dead.begin() + j);
            else
                j++;
        }

        j = 0;
        for(auto &i : items){
            i.update(time);
            if(i.isDisappeared())
                items.erase(items.begin() + j);
            else
                j++;
        }

        //mutex.unlock();

        createEnemy(packet, time,  zombies, zombies1, zombies2, zombies3, dogs);

        if(packet.getData() != nullptr){
            packet << SendType(packetType::end);
            socket.send(packet, ipClient1, portClient1);
            socket.send(packet, ipClient2, portClient2);

            packet.clear();
        }
    }
}

void getMusic(ClientInfo clientInfo){
    Packet packet;
    IpAddress ipAddress;
    unsigned short port;

    while(true){
        clientInfo.socket.receive(packet, ipAddress, port);

        if(ipAddress == clientInfo.ipClient1 && port == clientInfo.portClient1)
            clientInfo.socket.send(packet, clientInfo.ipClient2, clientInfo.portClient2);
        else if(ipAddress == clientInfo.ipClient2 && port == clientInfo.portClient2)
            clientInfo.socket.send(packet, clientInfo.ipClient1, clientInfo.portClient1);

        packet.clear();
    }
}

void getFromClient(Client &A){
    Packet packetReceive;
    Packet packetSend;

    IpAddress ipClient;
    IpAddress ipReceiver;
    unsigned short portClient;
    unsigned short portReceiver;

    while(true){
        A.socket.receive(packetReceive, ipClient, portClient);

        if(ipClient == A.ipClient1 && portClient == A.portClient1){
            ipReceiver = A.ipClient2;
            portReceiver = A.portClient2;
        } else if(ipClient == A.ipClient2 && portClient == A.portClient2){
            ipReceiver = A.ipClient1;
            portReceiver = A.portClient1;
        }

        SendType type;
        SendPlayer sendPlayer;
        SendBomb sendBomb;
        SendBullet sendBullet;

        while(true){
            packetReceive >> type;

            if(type.type == packetType::end)
                break;

            switch (type.type){
                case packetType::player:{
                    packetReceive >> sendPlayer;
                    packetSend << SendType(packetType::player);
                    packetSend << sendPlayer;

                    //mutex.lock();
                    if(sendPlayer.type == A.player1.aim){
                        A.player1.organism.setRotation(sendPlayer.rotation);
                        A.player1.direction = sendPlayer.direction;
                        A.player1.health = sendPlayer.health;
                        A.player1.organism.setPosition(sendPlayer.position);
                    } else if(sendPlayer.type == A.player2.aim){
                        A.player2.organism.setRotation(sendPlayer.rotation);
                        A.player2.direction = sendPlayer.direction;
                        A.player2.health = sendPlayer.health;
                        A.player2.organism.setPosition(sendPlayer.position);
                    }
                    //mutex.unlock();
                    break;
                }
                case packetType::bomb:{
                    packetReceive >> sendBomb;
                    packetSend << SendType(packetType::bomb);
                    packetSend << sendBomb;

                    Bomb bomb;
                    bomb.weapon = spriteBomb1;
                    bomb.weapon.setPosition(sendBomb.position);
                    bomb.timeBuffer = 0;
                    bomb.timeExplode = 0;
                    bomb.damage = bombDamage;
                    bomb.textureNumber = 1;

                    //mutex.lock();
                    A.bombs.push_back(bomb);
                    //mutex.unlock();

                    break;
                }
                case packetType::bullet:{
                    packetReceive >> sendBullet;
                    packetSend << SendType(packetType::bullet) << sendBullet;

                    Weapon bullet;
                    bullet.direction = sendBullet.direction;
                    bullet.speed = speedBullet;
                    bullet.damage = sendBullet.damage;
                    if(bullet.damage == shotgunDamage)
                        bullet.weapon = spriteBullet2;
                    else
                        bullet.weapon = spriteBullet1;
                    bullet.weapon.setPosition(sendBullet.position);
                    bullet.weapon.setRotation(sendBullet.rotation);
                    bullet.speed = speedBullet;

                    //mutex.lock();
                    A.bullets.push_back(bullet);
                    //mutex.unlock();

                    break;
                }
                default:
                    break;
            }
        }

        if(packetSend.getData() != nullptr){
            packetSend << SendType(packetType::end);
            A.socket.send(packetSend, ipReceiver, portReceiver);
            packetSend.clear();
            packetReceive.clear();
        }
    }
}

