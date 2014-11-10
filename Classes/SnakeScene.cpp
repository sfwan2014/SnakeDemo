//
//  SnakeScene.cpp
//  Snake
//
//  Created by sfwan on 14-11-10.
//
//

#include "SnakeScene.h"
#include "BodyScene.h"
USING_NS_CC;

bool SnakeSprite::init(){
    if ( !Sprite::init() )
    {
        return false;
    }
    
    return true;
}

SnakeSprite *SnakeSprite::createSnake(int num){
    
    SnakeSprite *enemy = new SnakeSprite();
    if (enemy && enemy->init()) {
        enemy->autorelease();
        enemy->enemyInit(num);
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return NULL;
}

void SnakeSprite::enemyInit(int num){
    number = num;
    bodys = __Array::create();
    bodys->retain();
    Point position = Point(100,100);
    Size size = Size(20, 20);
    BodyScene *body = BodyScene::createBody(position, size);
    
    body->setPhysicsBody(PhysicsBody::createBox(size));
    body->getPhysicsBody()->setContactTestBitmask(SNAKE_BIT_MAST);
    bodys->addObject(body);
    this ->addChild(body);
}

int SnakeSprite::getNember()
{
    return number;
}

void SnakeSprite::setNumber(int num)
{
    number = num;
}

Direct SnakeSprite::getDirect()
{
    return direct;
}
void SnakeSprite::setDirect(Direct d)
{
    direct = d;
}

bool SnakeSprite::start(){
    this->schedule(schedule_selector(SnakeSprite::run), 1);
    return true;
}

// 1 2 3 4 5
void SnakeSprite::run(float x){
    int count = (int)bodys->count();
    for (int i = count-1; i >= 0; i--) {
            BodyScene *body1 = (BodyScene *)bodys->getObjectAtIndex(i);
        if (i > 0) {
            BodyScene *body2 = (BodyScene *)bodys->getObjectAtIndex(i-1);
            body1->setPosition(body2->getPosition());
        } else {
            Point position = Point(body1->getPosition().x, body1->getPosition().y + 20);
            switch (direct) {
                case Up:
                {
                    position = Point(body1->getPosition().x, body1->getPosition().y + 20);
                }
                    break;
                case Down:
                {
                    position = Point(body1->getPosition().x, body1->getPosition().y - 20);
                }
                    break;
                case Left:
                {
                    position = Point(body1->getPosition().x - 20, body1->getPosition().y);
                }
                    break;
                case Right:
                {
                    position = Point(body1->getPosition().x+20, body1->getPosition().y);
                }
                    break;
                    
                default:
                    break;
            }
        
            body1->setPosition(position);
        }
    }
}
