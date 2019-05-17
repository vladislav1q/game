#include "server.cpp"
#include "client.cpp"

#pragma once


void openMultiplayer(WindowSent windowSent){
    const unsigned short serverPort = 5000;
    unsigned short clientPort = 0;

    //works if the game is run on one computer
    //solution:
    //sf::IpAddress ip("192.168.10.62");
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();

    int number = 0;
    std::cout << "Enter number of player you want to be(1 or 2)" << std::endl;
    std::cin >> number;

    if(number == 1){
        sf::Thread serverThread(&runServer, serverPort);
        serverThread.launch();
        sleep(seconds(0.5));
        clientPort = serverPort + number;
        runClient(windowSent, serverPort, clientPort,  ip);
    } else {
        clientPort = serverPort + number;
        runClient(windowSent, serverPort, clientPort,  ip);
    }
}
