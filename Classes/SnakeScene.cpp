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

    bodys->addObject(body);
    this ->addChild(body);
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
    this->schedule(schedule_selector(SnakeSprite::run), 0.2);
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

BodyScene *SnakeSprite::getFood()
{
    return food;
}
void SnakeSprite::setFood(BodyScene *b)
{
    CC_SAFE_RELEASE(food);
    food = b;
    food->retain();
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
            
        } else {
            Point position = Point(body1->getPosition().x, body1->getPosition().y + space);
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
    
    if (GameOver()) {
        end();
        reGameOver(NULL);
    }
}

bool SnakeSprite::GameOver(){
    
    BodyScene *first = (BodyScene *)bodys->getObjectAtIndex(0);
    for (int i = 1; i < bodys->count(); i++) {
        BodyScene *body = (BodyScene *)bodys->getObjectAtIndex(i);
        if (first->getPosition() == body->getPosition()) {
            return true;
        }
    }
    
    if (first->getPosition().x <= 0 || first->getPosition().y <= 0 || first->getPosition().x >= 640 || first->getPosition().y >= 640) {
        return true;
    }
    
    log("(x1=%f, y1=%f) (x2=%f, y2=%f)",first->getPosition().x, first->getPosition().y, food->getPosition().x, food->getPosition().y);
    if (first->getPosition() == food->getPosition()) {
        // eat
        onEat(this, NULL);
    }
    
    return false;
}
