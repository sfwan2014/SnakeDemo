#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class SnakeSprite;
class BodyScene;
class HelloWorld : public cocos2d::Layer
{
private:
    cocos2d::Size visibleSize;
    cocos2d::LayerColor *layerColorGB;
    SnakeSprite *snake;
    BodyScene *food;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloWorld);
    // 判断方向
    void handleDirect(cocos2d::Point point);
    // 创建背景
    void drawBackground();
    // 初始化蛇
    void initSnake();
    // 初始化食物
    BodyScene* createFood();
    // 长大
    void growUp();
};

#endif // __HELLOWORLD_SCENE_H__
