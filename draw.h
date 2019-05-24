#include "objects.h"

#pragma once

using namespace sf;

struct Draw{

    Draw(RenderWindow &window1, View &gameView1, std::vector<Organism> &zombies1, std::vector<Organism> &zombies11,
         std::vector<Organism> &zombies21, std::vector<Organism> &zombies31, std::vector<Organism> &dogs1,
         std::vector<Corpse> &dead1, std::vector<Weapon> &bullets1, std::vector<Bomb> &bombs1, std::vector<Feature> &items1,  std::vector<ConvexShape> &trapezes1, Organism &player1,
         Bar &lifeBar1, Bar &bubbleBar1, Bar &shieldBar1, Bar &bulletBar1, Bar &bombBar1, TimeBar &timeBar1, Sprite &spriteCursor1, Sprite &shadow1) :
            window(window1),
            gameView(gameView1),
            zombies(zombies1),
            zombies1(zombies11),
            zombies2(zombies21),
            zombies3(zombies31),
            dogs(dogs1),
            dead(dead1),
            bullets(bullets1),
            bombs(bombs1),
            items(items1),
            trapezes(trapezes1),
            player(player1),
            lifeBar(lifeBar1),
            bubbleBar(bubbleBar1),
            shieldBar(shieldBar1),
            bulletBar(bulletBar1),
            bombBar(bombBar1),
            timeBar(timeBar1),
            spriteCursor(spriteCursor1),
            shadow(shadow1){};

    RenderWindow &window;
    View &gameView;

    std::vector<Organism> &zombies;
    std::vector<Organism> &zombies1;
    std::vector<Organism> &zombies2;
    std::vector<Organism> &zombies3;
    std::vector<Organism> &dogs;

    std::vector<Corpse> &dead;
    std::vector<Weapon> &bullets;
    std::vector<Bomb> &bombs;
    std::vector<Feature> &items;
    std::vector<ConvexShape> &trapezes;

    Organism &player;
    Bar &lifeBar;
    Bar &bubbleBar;
    Bar &shieldBar;
    Bar &bulletBar;
    Bar &bombBar;
    TimeBar &timeBar;

    Sprite &spriteCursor;
    Sprite &shadow;
};



void drawGameview(Draw &A){

    A.window.setView(A.gameView);

    A.window.clear();

    float gameViewLeft = (A.gameView.getCenter().x - A.gameView.getSize().x / 2) / sizeTile - 5 ;
    float gameViewRight = (A.gameView.getCenter().x + A.gameView.getSize().x / 2) / sizeTile + 5;
    float gameViewUp = (A.gameView.getCenter().y - A.gameView.getSize().y / 2) / sizeTile - 5;
    float gameViewDown = (A.gameView.getCenter().y + A.gameView.getSize().y / 2) / sizeTile + 5;

    if(gameViewLeft < 0)
        gameViewLeft = 0;
    if(gameViewRight > sizeWindow.x)
        gameViewRight = sizeWindow.x;
    if(gameViewUp < 0)
        gameViewUp = 0;
    if(gameViewDown > sizeWindow.y)
        gameViewDown = sizeWindow.y;

    for(int i = (int)gameViewLeft; i < gameViewRight; i++){
        for(int j = (int)gameViewUp;j < gameViewDown; j++){
            //not house
            if(background[i][j].type < 22 || background[i][j].type > 79){
                backgroundTypes.at(background[i][j].type).picture.setPosition(i * sizeTile, j * sizeTile);
                A.window.draw(backgroundTypes.at(background[i][j].type).picture);
            }
        }
    }


    for(auto &i : A.dead){
        if(isInside(A.gameView, i.corpse.getPosition(), 0))
            A.window.draw(i.corpse);
    }

    for(auto &i : A.bullets)
        A.window.draw(i.weapon);

    for(auto &i : A.bombs)
        A.window.draw(i.weapon);

    for(auto &i : A.zombies){
        //if(isInside(A.gameView, i.organism.getPosition(), 0))
        float squareLen = (A.player.organism.getPosition().x-i.organism.getPosition().x) * (A.player.organism.getPosition().x-i.organism.getPosition().x) +
                          (A.player.organism.getPosition().y-i.organism.getPosition().y) * (A.player.organism.getPosition().y-i.organism.getPosition().y);

        if(squareLen < (A.shadow.getScale().x * (float)1000) * (A.shadow.getScale().x * (float)1000))
            A.window.draw(i.organism);
    }

    for(auto &i : A.zombies1){
        float squareLen = (A.player.organism.getPosition().x-i.organism.getPosition().x) * (A.player.organism.getPosition().x-i.organism.getPosition().x) +
                          (A.player.organism.getPosition().y-i.organism.getPosition().y) * (A.player.organism.getPosition().y-i.organism.getPosition().y);

        if(squareLen < (A.shadow.getScale().x * (float)1000) * (A.shadow.getScale().x * (float)1000))
            A.window.draw(i.organism);
    }

    for(auto &i : A.zombies2){
        float squareLen = (A.player.organism.getPosition().x-i.organism.getPosition().x) * (A.player.organism.getPosition().x-i.organism.getPosition().x) +
                          (A.player.organism.getPosition().y-i.organism.getPosition().y) * (A.player.organism.getPosition().y-i.organism.getPosition().y);

        if(squareLen < (A.shadow.getScale().x * (float)1000) * (A.shadow.getScale().x * (float)1000))
            A.window.draw(i.organism);
    }

    for(auto &i : A.zombies3){
        float squareLen = (A.player.organism.getPosition().x-i.organism.getPosition().x) * (A.player.organism.getPosition().x-i.organism.getPosition().x) +
                          (A.player.organism.getPosition().y-i.organism.getPosition().y) * (A.player.organism.getPosition().y-i.organism.getPosition().y);

        if(squareLen < (A.shadow.getScale().x * (float)1000) * (A.shadow.getScale().x * (float)1000))
            A.window.draw(i.organism);
    }

    for(auto &i : A.dogs){
        float squareLen = (A.player.organism.getPosition().x-i.organism.getPosition().x) * (A.player.organism.getPosition().x-i.organism.getPosition().x) +
                          (A.player.organism.getPosition().y-i.organism.getPosition().y) * (A.player.organism.getPosition().y-i.organism.getPosition().y);

        if(squareLen < (A.shadow.getScale().x * (float)1000) * (A.shadow.getScale().x * (float)1000))
            A.window.draw(i.organism);
    }

    for(auto &i : A.items){
        //if(isInside(gameView, i.feature, 0))
        A.window.draw(i.feature);
    }

    A.window.draw(A.player.organism);

    for(auto &i :trees1){
        if(isInside(A.gameView, i, 0)){
            spriteTree1.setPosition(i);
            A.window.draw(spriteTree1);
        }
    }

    for(auto &i :trees2){
        if(isInside(A.gameView, i, 0)){
            spriteTree2.setPosition(i);
            A.window.draw(spriteTree2);
        }
    }

    for(auto &i :trees3){
        if(isInside(A.gameView, i, 0)){
            spriteTree3.setPosition(i);
            A.window.draw(spriteTree3);
        }
    }

    for(auto &i :trees4){
        if(isInside(A.gameView, i, 0)){
            spriteTree4.setPosition(i);
            A.window.draw(spriteTree4);
        }
    }

    for(auto &i :trees5){
        if(isInside(A.gameView, i, 0)){
            spriteTree5.setPosition(i);
            A.window.draw(spriteTree5);
        }
    }

    for(auto &i : A.trapezes){
        A.window.draw(i);
    }

    for(int i = (int)gameViewLeft; i < gameViewRight; i++){
        for(int j = (int)gameViewUp;j < gameViewDown; j++){
            //house
            if(background[i][j].type > 21 && background[i][j].type < 80){
                backgroundTypes.at(background[i][j].type).picture.setPosition(i * sizeTile, j * sizeTile);
                A.window.draw(backgroundTypes.at(background[i][j].type).picture);
            }
        }
    }

    A.window.draw(A.shadow);

    numberBars = 0;

    A.lifeBar.updateBar(A.gameView, A.player.health, playerFullHealth);
    if(A.player.health > 0){
        A.window.draw(A.lifeBar.sprite);
        A.window.draw(A.lifeBar.shape);
        A.window.draw(A.lifeBar.text);
        numberBars++;
    }

    A.bubbleBar.updateBar(A.gameView, A.bubbleBar.value, fullBubbles);
    if(A.bubbleBar.value > 0){
        A.window.draw(A.bubbleBar.sprite);
        A.window.draw(A.bubbleBar.shape);
        A.window.draw(A.bubbleBar.text);
        numberBars++;
    }

    A.shieldBar.updateBar(A.gameView, A.player.protection, playerFullProtection);
    if(A.player.protection > 0){
        A.window.draw(A.shieldBar.sprite);
        A.window.draw(A.shieldBar.text);
        A.window.draw(A.shieldBar.shape);
        numberBars++;
    }

    A.bulletBar.updateBarWeapon(A.gameView, A.bulletBar.value, numberBulletsCage);
    if(A.bulletBar.value > 0){
        A.window.draw(A.bulletBar.sprite);
        A.window.draw(A.bulletBar.text);
        A.window.draw(A.bulletBar.shape);
        numberBars++;
    }

    A.bombBar.updateBarWeapon(A.gameView,  A.bombBar.value, numberBombsCage);
    if(A.bombBar.value > 0){
        A.window.draw(A.bombBar.sprite);
        A.window.draw(A.bombBar.text);
        A.window.draw(A.bombBar.shape);
        numberBars++;
    }

    A.window.draw(A.timeBar.text);

    A.window.draw(A.spriteCursor);
    //A.window.display();

}

struct Draw2{

    Draw2(RenderWindow &window1, View &gameView1, std::vector<Organism> &zombies1, std::vector<Organism> &zombies11,
          std::vector<Organism> &zombies21, std::vector<Organism> &zombies31, std::vector<Organism> &dogs1,
          std::vector<Corpse> &dead1, std::vector<Weapon> &bullets1, std::vector<Bomb> &bombs1, std::vector<Feature> &items1,  std::vector<ConvexShape> &trapezes1,
          Organism &player11, Organism &player21,
          Bar &lifeBar1, Bar &bubbleBar1, Bar &shieldBar1, Bar &bulletBar1, Bar &bombBar1, TimeBar &timeBar1, Sprite &spriteCursor1, Sprite &shadow1) :
            window(window1),
            gameView(gameView1),
            zombies(zombies1),
            zombies1(zombies11),
            zombies2(zombies21),
            zombies3(zombies31),
            dogs(dogs1),
            dead(dead1),
            bullets(bullets1),
            bombs(bombs1),
            items(items1),
            trapezes(trapezes1),
            player1(player11),
            player2(player21),
            lifeBar(lifeBar1),
            bubbleBar(bubbleBar1),
            shieldBar(shieldBar1),
            bulletBar(bulletBar1),
            bombBar(bombBar1),
            timeBar(timeBar1),
            spriteCursor(spriteCursor1),
            shadow(shadow1){};

    RenderWindow &window;
    View &gameView;

    std::vector<Organism> &zombies;
    std::vector<Organism> &zombies1;
    std::vector<Organism> &zombies2;
    std::vector<Organism> &zombies3;
    std::vector<Organism> &dogs;

    std::vector<Corpse> &dead;
    std::vector<Weapon> &bullets;
    std::vector<Bomb> &bombs;
    std::vector<Feature> &items;
    std::vector<ConvexShape> &trapezes;

    Organism &player1;
    Organism &player2;
    Bar &lifeBar;
    Bar &bubbleBar;
    Bar &shieldBar;
    Bar &bulletBar;
    Bar &bombBar;
    TimeBar &timeBar;

    Sprite &spriteCursor;
    Sprite &shadow;
};



void drawGameview2(Draw2 &A){

    A.window.setView(A.gameView);

    A.window.clear();

    float gameViewLeft = (A.gameView.getCenter().x - A.gameView.getSize().x / 2) / sizeTile - 5 ;
    float gameViewRight = (A.gameView.getCenter().x + A.gameView.getSize().x / 2) / sizeTile + 5;
    float gameViewUp = (A.gameView.getCenter().y - A.gameView.getSize().y / 2) / sizeTile - 5;
    float gameViewDown = (A.gameView.getCenter().y + A.gameView.getSize().y / 2) / sizeTile + 5;

    if(gameViewLeft < 0)
        gameViewLeft = 0;
    if(gameViewRight > sizeWindow.x)
        gameViewRight = sizeWindow.x;
    if(gameViewUp < 0)
        gameViewUp = 0;
    if(gameViewDown > sizeWindow.y)
        gameViewDown = sizeWindow.y;

    for(int i = (int)gameViewLeft; i < gameViewRight; i++){
        for(int j = (int)gameViewUp;j < gameViewDown; j++){
            //not house
            if(background[i][j].type < 22 || background[i][j].type > 79){
                backgroundTypes.at(background[i][j].type).picture.setPosition(i * sizeTile, j * sizeTile);
                A.window.draw(backgroundTypes.at(background[i][j].type).picture);
            }
        }
    }


    for(auto &i : A.dead){
        if(isInside(A.gameView, i.corpse.getPosition(), 0))
            A.window.draw(i.corpse);
    }

    for(auto &i : A.bullets)
        A.window.draw(i.weapon);

    for(auto &i : A.bombs)
        A.window.draw(i.weapon);

    for(auto &i : A.zombies){
        //if(isInside(A.gameView, i.organism.getPosition(), 0))
        float squareLen = (A.player1.organism.getPosition().x-i.organism.getPosition().x) * (A.player1.organism.getPosition().x-i.organism.getPosition().x) +
                          (A.player1.organism.getPosition().y-i.organism.getPosition().y) * (A.player1.organism.getPosition().y-i.organism.getPosition().y);

        if(squareLen < (A.shadow.getScale().x * (float)1000) * (A.shadow.getScale().x * (float)1000))
            A.window.draw(i.organism);
    }

    for(auto &i : A.zombies1){
        float squareLen = (A.player1.organism.getPosition().x-i.organism.getPosition().x) * (A.player1.organism.getPosition().x-i.organism.getPosition().x) +
                          (A.player1.organism.getPosition().y-i.organism.getPosition().y) * (A.player1.organism.getPosition().y-i.organism.getPosition().y);

        if(squareLen < (A.shadow.getScale().x * (float)1000) * (A.shadow.getScale().x * (float)1000))
            A.window.draw(i.organism);
    }

    for(auto &i : A.zombies2){
        float squareLen = (A.player1.organism.getPosition().x-i.organism.getPosition().x) * (A.player1.organism.getPosition().x-i.organism.getPosition().x) +
                          (A.player1.organism.getPosition().y-i.organism.getPosition().y) * (A.player1.organism.getPosition().y-i.organism.getPosition().y);

        if(squareLen < (A.shadow.getScale().x * (float)1000) * (A.shadow.getScale().x * (float)1000))
            A.window.draw(i.organism);
    }

    for(auto &i : A.zombies3){
        float squareLen = (A.player1.organism.getPosition().x-i.organism.getPosition().x) * (A.player1.organism.getPosition().x-i.organism.getPosition().x) +
                          (A.player1.organism.getPosition().y-i.organism.getPosition().y) * (A.player1.organism.getPosition().y-i.organism.getPosition().y);

        if(squareLen < (A.shadow.getScale().x * (float)1000) * (A.shadow.getScale().x * (float)1000))
            A.window.draw(i.organism);
    }

    for(auto &i : A.dogs){
        float squareLen = (A.player1.organism.getPosition().x-i.organism.getPosition().x) * (A.player1.organism.getPosition().x-i.organism.getPosition().x) +
                          (A.player1.organism.getPosition().y-i.organism.getPosition().y) * (A.player1.organism.getPosition().y-i.organism.getPosition().y);

        if(squareLen < (A.shadow.getScale().x * (float)1000) * (A.shadow.getScale().x * (float)1000))
            A.window.draw(i.organism);
    }

    for(auto &i : A.items){
        //if(isInside(gameView, i.feature, 0))
        A.window.draw(i.feature);
    }

    A.window.draw(A.player1.organism);
    A.window.draw(A.player2.organism);

    for(auto &i :trees1){
        if(isInside(A.gameView, i, 0)){
            spriteTree1.setPosition(i);
            A.window.draw(spriteTree1);
        }
    }

    for(auto &i :trees2){
        if(isInside(A.gameView, i, 0)){
            spriteTree2.setPosition(i);
            A.window.draw(spriteTree2);
        }
    }

    for(auto &i :trees3){
        if(isInside(A.gameView, i, 0)){
            spriteTree3.setPosition(i);
            A.window.draw(spriteTree3);
        }
    }

    for(auto &i :trees4){
        if(isInside(A.gameView, i, 0)){
            spriteTree4.setPosition(i);
            A.window.draw(spriteTree4);
        }
    }

    for(auto &i :trees5){
        if(isInside(A.gameView, i, 0)){
            spriteTree5.setPosition(i);
            A.window.draw(spriteTree5);
        }
    }

    for(auto &i : A.trapezes){
        A.window.draw(i);
    }

    for(int i = (int)gameViewLeft; i < gameViewRight; i++){
        for(int j = (int)gameViewUp;j < gameViewDown; j++){
            //house
            if(background[i][j].type > 21 && background[i][j].type < 80){
                backgroundTypes.at(background[i][j].type).picture.setPosition(i * sizeTile, j * sizeTile);
                A.window.draw(backgroundTypes.at(background[i][j].type).picture);
            }
        }
    }

    A.window.draw(A.shadow);

    numberBars = 0;

    A.lifeBar.updateBar(A.gameView, A.player1.health, playerFullHealth);
    if(A.player1.health > 0){
        A.window.draw(A.lifeBar.sprite);
        A.window.draw(A.lifeBar.shape);
        A.window.draw(A.lifeBar.text);
        numberBars++;
    }

    A.bubbleBar.updateBar(A.gameView, A.bubbleBar.value, fullBubbles);
    if(A.bubbleBar.value > 0){
        A.window.draw(A.bubbleBar.sprite);
        A.window.draw(A.bubbleBar.shape);
        A.window.draw(A.bubbleBar.text);
        numberBars++;
    }

    A.shieldBar.updateBar(A.gameView, A.player1.protection, playerFullProtection);
    if(A.player1.protection > 0){
        A.window.draw(A.shieldBar.sprite);
        A.window.draw(A.shieldBar.text);
        A.window.draw(A.shieldBar.shape);
        numberBars++;
    }

    A.bulletBar.updateBarWeapon(A.gameView, A.bulletBar.value, numberBulletsCage);
    if(A.bulletBar.value > 0){
        A.window.draw(A.bulletBar.sprite);
        A.window.draw(A.bulletBar.text);
        A.window.draw(A.bulletBar.shape);
        numberBars++;
    }

    A.bombBar.updateBarWeapon(A.gameView,  A.bombBar.value, numberBombsCage);
    if(A.bombBar.value > 0){
        A.window.draw(A.bombBar.sprite);
        A.window.draw(A.bombBar.text);
        A.window.draw(A.bombBar.shape);
        numberBars++;
    }

    A.window.draw(A.timeBar.text);

    A.window.draw(A.spriteCursor);
    //A.window.display();

}

void drawMinimap(RenderWindow &window, View &gameView, View &minimapView,  bool &minimap, Organism &player, Sprite &location, Sprite &map, float thickness){

    if(minimap){
        Vector2f center = Vector2f(sizeWindow.x * sizeTile / 2.0, sizeWindow.y * sizeTile / 2.0);
        Vector2f plPos =  Vector2f((player.organism.getPosition().x - center.x) * minimapScale,
                                   (player.organism.getPosition().y - center.y) * minimapScale);

        RectangleShape rectangleShape(Vector2f(gameView.getSize().x * minimapSize, gameView.getSize().y * minimapSize));
        rectangleShape.setPosition(gameView.getCenter().x - gameView.getSize().x / 2  + gameView.getSize().x* (1 - minimapSize - thickness),
                                   gameView.getCenter().y - gameView.getSize().y / 2  + gameView.getSize().y* (1 - minimapSize - thickness));
        rectangleShape.setFillColor(Color(0, 0, 0, 0));
        rectangleShape.setOutlineThickness(thickness * 100);
        rectangleShape.setOutlineColor(Color(0, 0, 0, minimapTransparancy));
        window.draw(rectangleShape);


        window.setView(minimapView);
        map.setPosition(minimapView.getSize().x / 2, minimapView.getSize().y / 2);
        location.setPosition(minimapView.getSize().x / 2, minimapView.getSize().y / 2);

        float low, high;
        if((low = center.x* minimapScale + plPos.x - minimapView.getSize().x / 2) > 0 &&
           (high = center.x* minimapScale + plPos.x + minimapView.getSize().x / 2) < sizeWindow.x * sizeTile * minimapScale)
            map.move(Vector2f(-plPos.x, 0));

        else if(low < 0){
            map.move(Vector2f(-plPos.x + low, 0));
            location.move(low, 0);
        }

        else if(high > sizeWindow.x * sizeTile * minimapScale){
            map.move(Vector2f(-plPos.x + (high - sizeWindow.x * sizeTile * minimapScale), 0));
            location.move(high - sizeWindow.x * sizeTile * minimapScale, 0);
        }


        if((low = center.y* minimapScale + plPos.y - minimapView.getSize().y / 2) > 0 &&
           (high = center.y* minimapScale + plPos.y + minimapView.getSize().y / 2) < sizeWindow.y * sizeTile * minimapScale)
            map.move(Vector2f(0, -plPos.y));

        else if(low < 0){
            map.move(Vector2f(0, -plPos.y + low));
            location.move(0, low);
        }

        else if(high > sizeWindow.y * sizeTile * minimapScale){
            map.move(Vector2f(0, -plPos.y + (high - sizeWindow.y * sizeTile * minimapScale)));
            location.move(0, high - sizeWindow.y * sizeTile * minimapScale);
        }

        window.draw(map);
        window.draw(location);
    }

}
