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

void runServer(unsigned short port){
// Create a socket to receive a message from anyone
    sf::UdpSocket socket;


    if (socket.bind(port) != sf::Socket::Done)
        return;
    std::cout << "Server is listening to port " << port << ", waiting for a message... " << std::endl;

    // Wait for a message

    sf::IpAddress sender;
    unsigned short senderPort;
    sf::Packet packet;
    if (socket.receive(packet, sender, senderPort) != sf::Socket::Done)
        return;
    int b;
    packet >> b;
    std::cout << "Message received from client " << sender << ": \"" << b << "\"" << std::endl;
    packet.clear();


    packet << 20;
    b = 20;
    // Send an answer to the client
    if (socket.send(packet, sender, senderPort) != sf::Socket::Done)
        return;

    std::cout << "Message sent to the client: \"" << b << "\"" << std::endl;
}
