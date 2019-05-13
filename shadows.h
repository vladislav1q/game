#include <SFML/Graphics.hpp>

#pragma once

class Opaque{
public:
    Opaque(sf::Vector2f position1, sf::Vector2f size1) :
            position(position1),
            size(size1){};

    sf::Vector2f position;
    sf::Vector2f size;
};

float getLenght(Vector2f a){
    return sqrt(a.x*a.x + a.y*a.y);
}

Vector2f norm(Vector2f a){
    return a / getLenght(a);
}


void setShadow(std::vector<Opaque> &houses, std::vector<sf::ConvexShape> &trapezes, sf::Vector2f player){

//    Clock clock1;
//    Time time1 = clock1.getElapsedTime();
//    std::cout << std::endl << "Shadow started 0: " << time1.asSeconds();
    int shadowLength = 100000;

    trapezes.clear();
//    time1 = clock1.getElapsedTime();
//    std::cout << "1: " << time1.asSeconds() << std::endl;

    for(auto &i : houses){

        sf::ConvexShape trapeze0;
        sf::ConvexShape trapeze1;
        sf::ConvexShape trapeze2;
        sf::ConvexShape trapeze3;

        trapeze0.setPointCount(4);
        trapeze1.setPointCount(4);
        trapeze2.setPointCount(4);
        trapeze3.setPointCount(4);


        trapeze0.setPoint(0, sf::Vector2f(i.position.x, i.position.y));
        trapeze0.setPoint(1, sf::Vector2f(i.position.x, i.position.y) + norm(sf::Vector2f(i.position.x, i.position.y) - player) * (float)shadowLength);
        trapeze0.setPoint(2, sf::Vector2f(i.position.x + i.size.x, i.position.y) + norm(sf::Vector2f(i.position.x + i.size.x, i.position.y) - player) * (float)shadowLength);
        trapeze0.setPoint(3, sf::Vector2f(i.position.x + i.size.x, i.position.y));



        trapeze1.setPoint(0, sf::Vector2f(i.position.x + i.size.x, i.position.y));
        trapeze1.setPoint(1, sf::Vector2f(i.position.x + i.size.x, i.position.y) + norm(sf::Vector2f(i.position.x + i.size.x, i.position.y) - player) * (float)shadowLength);
        trapeze1.setPoint(2, sf::Vector2f(i.position.x + i.size.x, i.position.y + i.size.y) + norm(sf::Vector2f(i.position.x + i.size.x, i.position.y + i.size.y) - player) * (float)shadowLength);
        trapeze1.setPoint(3, sf::Vector2f(i.position.x + i.size.x, i.position.y + i.size.y));

        trapeze1.setPoint(0, sf::Vector2f(i.position.x + i.size.x, i.position.y + i.size.y));
        trapeze1.setPoint(1, sf::Vector2f(i.position.x + i.size.x, i.position.y + i.size.y) + norm(sf::Vector2f(i.position.x + i.size.x, i.position.y + i.size.y) - player) * (float)shadowLength);
        trapeze1.setPoint(2, sf::Vector2f(i.position.x, i.position.y + i.size.y) + norm(sf::Vector2f(i.position.x, i.position.y + i.size.y) - player) * (float)shadowLength);
        trapeze1.setPoint(3, sf::Vector2f(i.position.x, i.position.y + i.size.y));

        trapeze3.setPoint(0, sf::Vector2f(i.position.x, i.position.y + i.size.y));
        trapeze3.setPoint(1, sf::Vector2f(i.position.x, i.position.y + i.size.y) + norm(sf::Vector2f(i.position.x, i.position.y + i.size.y) - player) * (float)shadowLength);
        trapeze3.setPoint(2, sf::Vector2f(i.position.x, i.position.y) + norm(sf::Vector2f(i.position.x, i.position.y) - player) * (float)shadowLength);
        trapeze3.setPoint(3, sf::Vector2f(i.position.x, i.position.y));


        trapeze0.setFillColor(sf::Color(0, 0, 0, 255));
        trapeze1.setFillColor(sf::Color(0, 0, 0, 255));
        trapeze2.setFillColor(sf::Color(0, 0, 0, 255));
        trapeze3.setFillColor(sf::Color(0, 0, 0, 255));

        trapezes.push_back(trapeze0);
        trapezes.push_back(trapeze1);
        trapezes.push_back(trapeze2);
        trapezes.push_back(trapeze3);


    }
//    time1 = clock1.getElapsedTime();
//    std::cout << "2: " << time1.asSeconds() << std::endl;
}
