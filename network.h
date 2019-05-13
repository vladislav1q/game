#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "iostream"

#pragma once

using namespace sf;

struct SendBullet{
    SendBullet(Vector2f position1, Vector2f direction1) :
    position(position1),
    direction(direction1){};

    Vector2f position;
    Vector2f direction;
};

struct SendBomb{
    SendBomb(Vector2f position1) : position(position1){};

    Vector2f position;
};

struct SendFeature{
    SendFeature(int type1, Vector2f position1) :
    type(type1),
    position(position1){};

    int type;
    Vector2f position;
};

struct SendOrganism{
    SendOrganism(unsigned int uniqueNumber1, Vector2f position1, Vector2f direction1, float health1) :
        uniqueNumber(uniqueNumber1),
        position(position1),
        direction(direction1),
        health(health1){};

    //0 for player
    // 1 - unsigned long int for zombie
    unsigned int uniqueNumber;
    Vector2f position;
    Vector2f direction;
    float health;
};


//SendBullet
sf::Packet& operator <<(sf::Packet& packet, const SendBullet& A)
{
    return packet << A.position.x << A.position.y << A.direction.x << A.direction.y;
}
sf::Packet& operator >>(sf::Packet& packet, SendBullet& A)
{
    return packet >> A.position.x >> A.position.y >> A.direction.x >> A.direction.y;
}

//SendBomb
sf::Packet& operator <<(sf::Packet& packet, const SendBomb& A)
{
    return packet << A.position.x << A.position.y;
}
sf::Packet& operator >>(sf::Packet& packet, SendBomb& A)
{
    return packet >> A.position.x >> A.position.y;
}

//SendFeature
sf::Packet& operator <<(sf::Packet& packet, const SendFeature& A)
{
    return packet << A.type << A.position.x << A.position.y;
}
sf::Packet& operator >>(sf::Packet& packet, SendFeature& A)
{
    return packet >> A.type >> A.position.x >> A.position.y;
}

//SendOrganizm
sf::Packet& operator <<(sf::Packet& packet, const SendOrganism& A)
{
    return packet << A.uniqueNumber << A.health << A.position.x << A.position.y << A.direction.x << A.direction.y;
}
sf::Packet& operator >>(sf::Packet& packet, SendOrganism& A)
{
    return packet >> A.uniqueNumber >> A.health >> A.position.x >> A.position.y >> A.direction.x >> A.direction.y;
}

