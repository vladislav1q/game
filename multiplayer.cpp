//#include "server.cpp"
#include "client.cpp"

#pragma once


void openMultiplayer(WindowSent windowSent){
    const unsigned short serverPort = 20000;
    unsigned short clientPort = 20005 + rand() % 1000;

    //works if the game is run on one computer
    //solution:
    sf::IpAddress ipServer("10.55.129.201");
    //sf::IpAddress ip = sf::IpAddress::getLocalAddress();

//    int number = 0;
//    std::cout << "Enter number of player you want to be(1 or 2)" << std::endl;
//    std::cin >> number;


    runClient(windowSent, serverPort, clientPort,  ipServer);

}
