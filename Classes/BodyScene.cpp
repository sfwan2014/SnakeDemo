//
//  BodyScene.cpp
//  Snake
//
//  Created by sfwan on 14-11-10.
//
//

#include "BodyScene.h"
USING_NS_CC;

bool BodyScene::init(){
    if (!Sprite::init()) {
        return false;
    }
    return true;
}

BodyScene * BodyScene::createBody(cocos2d::Point position, cocos2d::Size size)
{
    BodyScene *enemy = new BodyScene();
    if (enemy && enemy->init()) {
        enemy->autorelease();
        enemy->enemyInit(position, size);
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return NULL;
}

BodyScene *BodyScene::createBody(int x, int y, cocos2d::Size size)
{
    BodyScene *enemy = new BodyScene();
    if (enemy && enemy->init()) {
        enemy->autorelease();
        enemy->enemyInit(cocos2d::Point(x,y), size);
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return NULL;
}
void BodyScene::enemyInit(cocos2d::Point position, cocos2d::Size size)
{
    this->x = position.x;
    this->y = position.y;
    this->position = position;
    this->size = size;
    this->setContentSize(size);
    this->cocos2d::Node::setPosition(position);
    layerColorBG = cocos2d::LayerColor::create(Color4B(200, 0, 100, 255), size.width, size.height);
    layerColorBG->setPosition(0,0);
    this->addChild(layerColorBG);
}