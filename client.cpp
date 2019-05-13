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

void runClient(unsigned short port, sf::IpAddress ip){

    sf::IpAddress ServerIp = ip;
    sf::UdpSocket socket;
    sf::Packet packet;


    packet << 21;
    int i = 21;

    if (socket.send(packet, ServerIp, port) != sf::Socket::Done)
        return;
    std::cout << "Message sent to the server: \"" << i << "\"" << std::endl;


    sf::IpAddress sender;
    unsigned short senderPort;
    if (socket.receive(packet, sender, senderPort) != sf::Socket::Done)
        return;
    int a;
    packet >> a;
    std::cout << "Message received from " << sender << "|" << a << std::endl;

}