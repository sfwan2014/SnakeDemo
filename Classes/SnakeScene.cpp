//
//  SnakeScene.cpp
//  Snake
//
//  Created by sfwan on 14-11-10.
//
//

#include "SnakeScene.h"
#include "BodyScene.h"

#define BODY_WIDTH          20

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
    Point position = Point((640-BODY_WIDTH)/2,(640-BODY_WIDTH)/2);
    Size size = Size(BODY_WIDTH, BODY_WIDTH);
    BodyScene *body = BodyScene::createBody(position, size);
    
    body->setPhysicsBody(PhysicsBody::createBox(size));
    body->getPhysicsBody()->setContactTestBitmask(SNAKE_HEAD_BIT_MAST);
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
    this->schedule(schedule_selector(SnakeSprite::run), 0.5);
    return true;
}

void SnakeSprite::end(){
    this->unschedule(schedule_selector(SnakeSprite::run));
    CC_SAFE_DELETE(bodys);
}

void SnakeSprite::setPosition(cocos2d::Point p)
{
    position = p;
}

cocos2d::Point SnakeSprite::getPosition()
{
    return position;
}

cocos2d::__Array* SnakeSprite::getBodys(){
    return bodys;
}

void SnakeSprite::setBodys(cocos2d::__Array *bs)
{
    CC_SAFE_DELETE(bodys);
    bodys = __Array::create();
    bodys = bs;
    bodys->retain();
}

// 1 2 3 4 5
void SnakeSprite::run(float x){
    
    int space = BODY_WIDTH;
    int count = (int)bodys->count();
    for (int i = count-1; i >= 0; i--) {
            BodyScene *body1 = (BodyScene *)bodys->getObjectAtIndex(i);
        if (i > 0) {
            BodyScene *body2 = (BodyScene *)bodys->getObjectAtIndex(i-1);
            body1->setPosition(body2->getPosition());
            body1->getPhysicsBody()->setContactTestBitmask(SNAKE_BODY_BIT_MAST);
            
        } else {
            Point position = Point(body1->getPosition().x, body1->getPosition().y + space);
            body1->getPhysicsBody()->setContactTestBitmask(SNAKE_HEAD_BIT_MAST);
            switch (direct) {
                case Up:
                {
                    position = Point(body1->getPosition().x, body1->getPosition().y + space);
                }
                    break;
                case Down:
                {
                    position = Point(body1->getPosition().x, body1->getPosition().y - space);
                }
                    break;
                case Left:
                {
                    position = Point(body1->getPosition().x - space, body1->getPosition().y);
                }
                    break;
                case Right:
                {
                    position = Point(body1->getPosition().x+space, body1->getPosition().y);
                }
                    break;
                    
                default:
                    break;
            }
            setPosition(position);
            body1->setPosition(position);
        }
    }
}

void SnakeSprite::addBody()
{
    Point position = ((BodyScene *)bodys->getLastObject())->getPosition();
    Size size = Size(BODY_WIDTH, BODY_WIDTH);
    BodyScene *body = BodyScene::createBody(position, size);
    body->setPhysicsBody(PhysicsBody::createBox(size));
    if (bodys->count()> 2) {
        body->getPhysicsBody()->setContactTestBitmask(SNAKE_BODY_BIT_MAST);
    }
    bodys->addObject(body);
    this ->addChild(body);
}
