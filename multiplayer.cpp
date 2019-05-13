#include "server.cpp"
#include "client.cpp"

#pragma once

bool serverRun = false;

void openMultiplayer(WindowSent windowSent){
    const unsigned short port = 50001;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();

    if(!serverRun){
        serverRun = true;
        sf::Thread serverThread(&runServer, port);
        serverThread.launch();
        sleep(seconds(0.5));
        runClient(port, ip);
    } else {
        runClient(port, ip);
    }
}
