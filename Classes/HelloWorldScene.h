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
    virtual void onEnter();
    CREATE_FUNC(HelloWorld);
    void handleDirect(cocos2d::Point point);
    void drawBackground();
    
    BodyScene* createFood();
    void changeFoodPosition();
    void growUp();
};

#endif // __HELLOWORLD_SCENE_H__
