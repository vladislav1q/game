#include <math.h>
#include "paths.h"
#include "background.h"

#pragma once

using namespace sf;

Vector2f norm(Vector2f a);
float getLenght(Vector2f a);

unsigned int maxNumberLeaders = 15;
unsigned int maxLengthName = 20;

unsigned int numberEnemyProduced = 0;

float hard = 0;
int fullBubbles = 100;
int numberBars = 0;
int numberBulletsCage = 50;
int numberBombsCage = 10;

unsigned int speedBullet = 1500;

unsigned int zombieFullHealth = 300;
unsigned int zombie1FullHealth = 1000;
unsigned int zombie2FullHealth = 200;
unsigned int zombie3FullHealth = 200;
unsigned int dogFullHealth = 100;
unsigned int playerFullHealth = 300;

unsigned int playerFullProtection = 200;

unsigned int zombieSpeed = 170;
unsigned int zombie1Speed = 100;
unsigned int zombie2Speed = 150;
unsigned int zombie3Speed = 150;
unsigned int dogSpeed = 180;
unsigned int playerSpeed = 300;

unsigned int zombieDamage = 20;
unsigned int zombie1Damage = 50;
unsigned int zombie2Damage = 10;
unsigned int zombie3Damage = 10;
unsigned int dogDamage = 5;

float speedDrawZombie = 0.05;
float speedDrawZombie1 = 0.1;
float speedDrawZombie2 = 0.2;
float speedDrawZombie3 = 0.2;
float speedDrawDog = 0.1;
float speedDrawPlayer = 0.1;

float timeProducementZombie = 2;
float timeProducementZombie1 = 3;
float timeProducementZombie2 = 5;
float timeProducementZombie3 = 7;
float timeProducementDog = 1;
float timeBufferBomb = 0.3;
float timeBombExplore = 1;
float bloodDisappearTime = 0.05;
float timeDissapearItem = 0.1;

//not independent probabilities
float heartProbability = 0.01;
float shieldProbability = 0.02;
float bulletProbability = 0.15;
float bombProbability = 0.1;

float bombDistanceExplode = 100000;

unsigned int pistolDamage = 50;
unsigned int shotgunDamage = 25;
unsigned int bombDamage = 200;
float shotgunAngle = 2.0/180.0*3.1415;

Texture textureBullet1;
Texture textureBullet2;
Texture textureBomb1;
Texture textureBomb2;
Texture textureCursor0;
Texture textureCursor1;
Texture textureHeart;
Texture textureShield;
Texture textureBullet;
Texture textureBomb;
Texture texturePlayerInWater;
Texture textureLocation;

Sprite spritePlayer;
Sprite spriteZombie;
Sprite spriteZombie1;
Sprite spriteZombie2;
Sprite spriteZombie3;
Sprite spriteDog;
Sprite spriteBullet1;
Sprite spriteBullet2;
Sprite spriteBomb1;
Sprite spriteBomb2;

class SortMap{
public:
    int key;
    std::string string;
};

std::vector <SortMap> leaders;

class Corpse{
public:
    Corpse(float angle, Vector2f position, float size){
        texture = textureCorpse;
        corpse.setTexture(texture);
        corpse.setOrigin((float)texture.getSize().x / 2, (float)texture.getSize().y / 2);
        corpse.setScale(size/100, size/100);
        corpse.setRotation(angle);
        corpse.setPosition(position);
        timeBuffer = 0;
    }
    void update(Time time){
        timeBuffer += time.asSeconds();
        while(timeBuffer > bloodDisappearTime){
            timeBuffer -= bloodDisappearTime;
            if(corpse.getColor().a > 0)
                corpse.setColor(Color(255, 255, 255, corpse.getColor().a - 1));
        }
    }

    bool isDisappeared(){
        return corpse.getColor().a <= 0;
    }

    Sprite corpse;
    Texture texture;
    float timeBuffer;
};

class Path{
public:
    Path(std::vector <Texture> &walkFull,
         std::vector <Texture> &walkHalf,
         std::vector <Texture> &walkSmall,
         int numberwalk, float walktimebuffer,

         std::vector <Texture> &attackFull,
         std::vector <Texture> &attackHalf,
         std::vector <Texture> &attackSmall,
         int numberattack, float attacktimebuffer):

         PathsWalkFullHealth(walkFull),
         PathsWalkHalfHealth(walkHalf),
         PathsWalkSmallHealth(walkSmall),
         numberWalk(numberwalk),
         numberWalkNow(0),
         walkTimeBuffer(walktimebuffer),


         PathsAttackFullHealth(attackFull),
         PathsAttackHalfHealth(attackHalf),
         PathsAttackSmallHealth(attackSmall),
         numberAttack(numberattack),
         numberAttackNow(0),
         attackTimeBuffer(attacktimebuffer),
         pathIterator(0){};

    Path &operator=(const Path &path1){
        PathsWalkFullHealth = path1.PathsWalkFullHealth;
        PathsWalkHalfHealth = path1.PathsWalkHalfHealth;
        PathsWalkSmallHealth = path1.PathsWalkSmallHealth;
        numberWalk = path1.numberWalk;
        numberWalkNow = path1.numberWalkNow;
        walkTimeBuffer = path1.walkTimeBuffer;

        PathsAttackFullHealth = path1.PathsAttackFullHealth;
        PathsAttackHalfHealth = path1.PathsAttackHalfHealth;
        PathsAttackSmallHealth = path1.PathsAttackSmallHealth;
        numberAttack = path1.numberAttack;
        numberAttackNow = path1.numberAttackNow;
        attackTimeBuffer = path1.attackTimeBuffer;

        pathIterator = path1.pathIterator;
    }

    std::vector <Texture> &PathsWalkFullHealth;
    std::vector <Texture> &PathsWalkHalfHealth;
    std::vector <Texture> &PathsWalkSmallHealth;
    int numberWalk;
    int numberWalkNow;
    float walkTimeBuffer;

    std::vector <Texture> &PathsAttackFullHealth;
    std::vector <Texture> &PathsAttackHalfHealth;
    std::vector <Texture> &PathsAttackSmallHealth;
    int numberAttack;
    int numberAttackNow;
    float attackTimeBuffer;

    unsigned int pathIterator;
};

class Organism{
public:
    float health;
    unsigned int fullHealth;
    float protection;
    unsigned int speed;
    float speedDraw;
    int damage;
    bool enemy;
    Vector2f direction;
    Path path;
    Sprite organism;
    unsigned int uniqueNumber;
    int aim;

    Organism(
            int health1,
            int protection1,
            unsigned int speed1,
            float speedDraw1,
            int damage1,
            bool enemy1,

            std::vector <Texture> &walkFull,
            std::vector <Texture> &walkHalf,
            std::vector <Texture> &walkSmall,
            int numberwalk, float walktimebuffer,

            std::vector <Texture> &attackFull,
            std::vector <Texture> &attackHalf,
            std::vector <Texture> &attackSmall,
            int numberattack, float attacktimebuffer,

            Sprite &sprite1) :
                    health(health1),
                    fullHealth(health1),
                    protection(protection1),
                    speed(speed1),
                    speedDraw(speedDraw1),
                    damage(damage1),
                    enemy(enemy1),
                    direction(Vector2f(0,0)),
                    path(walkFull,
                            walkHalf,
                            walkSmall,
                            numberwalk,
                            walktimebuffer,

                            attackFull,
                            attackHalf,
                            attackSmall,
                            numberattack,
                            attacktimebuffer),
                    organism(sprite1),
                    uniqueNumber(numberEnemyProduced+1){
        numberEnemyProduced++;
        aim = rand() % 2;
    };

    ~Organism(){};

    void attackUpdate(Time time){
//        soundsAll.sound[0].play();
        path.attackTimeBuffer += time.asSeconds();
        if(path.attackTimeBuffer >= speedDraw){
            path.attackTimeBuffer -= speedDraw;
            path.numberAttackNow = (path.numberAttackNow + 1) % (path.numberAttack);

            if(path.pathIterator == 0){
                if(this->getPosition().type == 18)
                    organism.setTexture(path.PathsWalkFullHealth[path.numberWalk]);
                else
                    organism.setTexture(path.PathsAttackFullHealth[path.numberAttackNow]);

            } else if(path.pathIterator == 1){
                if(this->getPosition().type == 18)
                    organism.setTexture(path.PathsWalkHalfHealth[path.numberWalk]);
                else
                    organism.setTexture(path.PathsAttackHalfHealth[path.numberAttackNow]);

            } else if(path.pathIterator == 2){
                if(this->getPosition().type == 18)
                    organism.setTexture(path.PathsWalkSmallHealth[path.numberWalk]);
                else
                    organism.setTexture(path.PathsAttackSmallHealth[path.numberAttackNow]);
            }

        }
    }

    void walkUpdate(Time time){

        path.walkTimeBuffer += time.asSeconds();
        if(path.walkTimeBuffer >= speedDraw){
            path.walkTimeBuffer -= speedDraw;
            path.numberWalkNow = (path.numberWalkNow + 1) % (path.numberWalk);

            if(path.pathIterator == 0){
                if(this->getPosition().type == 18)
                    organism.setTexture(path.PathsWalkFullHealth[path.numberWalk]);
                else
                    organism.setTexture(path.PathsWalkFullHealth[path.numberWalkNow]);
            } else if(path.pathIterator == 1){
                if(this->getPosition().type == 18)
                    organism.setTexture(path.PathsWalkHalfHealth[path.numberWalk]);
                else
                    organism.setTexture(path.PathsWalkHalfHealth[path.numberWalkNow]);
            } else if(path.pathIterator == 2){
                if(this->getPosition().type == 18)
                    organism.setTexture(path.PathsWalkSmallHealth[path.numberWalk]);
                else
                    organism.setTexture(path.PathsWalkSmallHealth[path.numberWalkNow]);
            }
        }
    }

    void rotate(Vector2f rotateAround){
        Vector2f d = rotateAround - organism.getPosition();
        organism.setRotation((atan2f(d.y, d.x)*180-270)/M_PI);
    }

    bool move(Time time){
        //player
        Vector2f x = Vector2f(direction.x, 0) / getLenght(direction);
        Vector2f y = Vector2f(0, direction.y) / getLenght(direction);


        if(!enemy){
            bool move = false;

            //move X
            if(this->getNewPosition(speed*time.asSeconds()*x).crossPlayer && x.x != 0){
                if(this->getNewPosition(speed*time.asSeconds()*y).crossPlayer && y.y != 0){
                    organism.move(speed*time.asSeconds() * norm(y + x) * this->getNewPosition(speed*time.asSeconds()*y).speed);
                    move = true;
                } else{
                    organism.move(speed*time.asSeconds() * norm(x) * this->getNewPosition(speed*time.asSeconds()*x).speed);
                    move = true;
                }
            }
            //move Y
            else if(this->getNewPosition(speed*time.asSeconds()*y).crossPlayer && y.y != 0){
                organism.move(speed*time.asSeconds() * norm(y) * this->getNewPosition(speed*time.asSeconds()*y).speed);
                move = true;
            }

            return move;

        } else if(enemy){
            bool move = false;

            //move X
            if(this->getNewPosition(speed*time.asSeconds()*x).crossEnemy){
                if(this->getNewPosition(speed*time.asSeconds()*y).crossEnemy){
                    if((x+y).x != 0 || (x+y).y != 0){
                        organism.move(speed*time.asSeconds() * norm(y + x) * this->getNewPosition(speed*time.asSeconds() * y).speed);
                        move = true;
                    }

                } else{
                    if(x.x != 0){
                        organism.move(speed*time.asSeconds() * norm(x) * this->getNewPosition(speed*time.asSeconds() * x).speed);
                        move = true;
                    }
                }

            }
            //move Y
            else if(this->getNewPosition(speed*time.asSeconds()*y).crossEnemy){
                if(y.y != 0){
                    organism.move(speed*time.asSeconds() * norm(y) * this->getNewPosition(speed*time.asSeconds() * y).speed);
                    move = true;
                }
            }

            return move;

        } else
            return false;

    }

    bool isInsideOrganism(Organism enemy){
        float radiusEnemy = std::min(enemy.organism.getTexture()->getSize().x*enemy.organism.getScale().x*2/5,
                                     enemy.organism.getTexture()->getSize().y*enemy.organism.getScale().y*2/5);
        float radiusMy = std::min(organism.getTexture()->getSize().x*organism.getScale().x*2/5,
                                     organism.getTexture()->getSize().y*organism.getScale().y*2/5);
        Vector2f d = enemy.organism.getPosition() - organism.getPosition();

        return (getLenght(d) < radiusEnemy + radiusMy);
    }

    Background getPosition(){
        return background[(int)(organism.getPosition().x / sizeTile)][(int)(organism.getPosition().y / sizeTile)];
    }

    Background getNewPosition(Vector2f direct){
        return background[(int)((organism.getPosition().x + direct.x) / sizeTile)]
                [(int)((organism.getPosition().y + direct.y) / sizeTile)];
    }
};

class Feature{
public:
    Sprite feature;
    int type;
    int value;
    float timeBuffer;

    void update(Time time){
        timeBuffer += time.asSeconds();
        while(timeBuffer > timeDissapearItem){
            timeBuffer -= timeDissapearItem;
            if(feature.getColor().a > 0)
                feature.setColor(Color(255, 255, 255, feature.getColor().a - 1));
        }
    }

    bool isDisappeared(){
        return feature.getColor().a <= 80;
    }

    bool isInsideOrganism(Organism enemy){
        float radius = std::min(enemy.organism.getTexture()->getSize().x, enemy.organism.getTexture()->getSize().y)
                       *std::min(enemy.organism.getScale().x, enemy.organism.getScale().y);

        return (feature.getPosition().x < enemy.organism.getPosition().x + radius)
               && (feature.getPosition().x > enemy.organism.getPosition().x - radius)
               && (feature.getPosition().y > enemy.organism.getPosition().y - radius)
               && (feature.getPosition().y < enemy.organism.getPosition().y + radius);
    }
};

class Weapon{
public:
    int damage;
    float speed;
    Vector2f direction;
    Sprite weapon;

    void rotate(Vector2f rotateAround){
        Vector2f d = weapon.getPosition() - rotateAround;
        weapon.setRotation((-atan2f(d.x, d.y)*180)/M_PI);
    }

    bool move(Time time){
        Time time1;

        if(this->canCross(time) && this->canCross(time1)){
            weapon.setPosition(weapon.getPosition() + speed * time.asSeconds() * norm(direction));
            return true;
        } else
            return false;
    }

    bool isInsideOrganism(Organism enemy){
        float radius = std::min(enemy.organism.getTexture()->getSize().x, enemy.organism.getTexture()->getSize().y)/3
                *std::min(enemy.organism.getScale().x, enemy.organism.getScale().y);

        return (weapon.getPosition().x < enemy.organism.getPosition().x + radius)
               && (weapon.getPosition().x > enemy.organism.getPosition().x - radius)
               && (weapon.getPosition().y > enemy.organism.getPosition().y - radius)
               && (weapon.getPosition().y < enemy.organism.getPosition().y + radius);
    }

private:
    bool canCross(Time time){
        if((weapon.getPosition().x + time.asSeconds()*speed*direction.x > 0) &&
                (weapon.getPosition().x + time.asSeconds()*speed*direction.x < sizeWindow.x * sizeTile) &&
                (weapon.getPosition().y + time.asSeconds()*speed*direction.y > 0) &&
                (weapon.getPosition().y + time.asSeconds()*speed*direction.y < sizeWindow.y * sizeTile)){

            return background[(int)((weapon.getPosition().x + time.asSeconds()*speed*direction.x) / sizeTile)]
            [(int)((weapon.getPosition().y  + time.asSeconds()*speed*direction.x)/ sizeTile)].crossWeapon;
        } else
            return false;

    }
};

class Bomb{
public:
    int damage;
    Sprite weapon;
    int textureNumber;
    float timeBuffer;
    float timeExplode;


};

class Bar{
public:
    Bar(const std::string &str1, const std::string &str2, Color color, float scale){
        texture.loadFromFile(str1);
        sprite.setTexture(texture);
        sprite.setScale(scale, scale);
        shape.setFillColor(color);
        shape.setSize(Vector2f(190, 20));

        font.loadFromFile(str2);
        text.setFont(font);
        text.setCharacterSize(40);
        text.setFillColor(color);
        text.setStyle(Text::Bold | Text::Italic);

        value = 0;
    }

    void updateBar(View &gameView, float value, float maxValue){
        sprite.setPosition(gameView.getCenter().x + gameView.getSize().x/2 - 200,
                           gameView.getCenter().y - gameView.getSize().y/2 + 10 + 110*numberBars);
        shape.setPosition(sprite.getPosition().x, sprite.getPosition().y + 80);
        shape.setScale(value / maxValue, 1);

        text.setPosition(sprite.getPosition().x + 80, sprite.getPosition().y + 15);
        text.setString(std::to_string((int)(100*value / maxValue)) + "%");
    }

    void updateBarWeapon(View &gameView, int value, int maxValue){
        sprite.setPosition(gameView.getCenter().x + gameView.getSize().x/2 - 200,
                           gameView.getCenter().y - gameView.getSize().y/2 + 10 + 110*numberBars);
        shape.setPosition(sprite.getPosition().x, sprite.getPosition().y + 80);
        shape.setScale((value % maxValue) / (float)maxValue, 1);

        text.setPosition(sprite.getPosition().x + 80, sprite.getPosition().y + 15);
        text.setString(std::to_string((int)(value / maxValue)));
    }

    Font font;
    Text text;
    RectangleShape shape;
    Texture texture;
    Sprite sprite;
    float value;
};

class TimeBar{
public:
    TimeBar(const std::string &str){
        font.loadFromFile(str);
        text.setFont(font);
        text.setCharacterSize(50);
        text.setFillColor(Color(128, 255, 0, 255));
        text.setStyle(Text::Bold | Text::Italic);
        text.setPosition(0, 0);
    }

    void update(View &gameView, Time time){
        text.setPosition(gameView.getCenter().x - gameView.getSize().x/2 + 20,
                         gameView.getCenter().y - gameView.getSize().y/2 + 20);
        text.setString(std::to_string((int)time.asSeconds()/60) + " min  " + std::to_string((int)time.asSeconds() % 60) + " sec");
    }

    Font font;
    Text text;
};

//List of initializations used:
class Strike{
public:
    Strike(std::vector<Weapon> &bulletsNew, std::vector<Organism> &enemiesNew, View &view, std::vector<Corpse> &corpse) :
    bullets(bulletsNew), enemies(enemiesNew), gameView(view), dead(corpse){};

    View &gameView;
    std::vector<Weapon> &bullets;
    std::vector<Organism> &enemies;
    std::vector<Corpse> &dead;
};
