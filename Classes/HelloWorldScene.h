#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class SnakeSprite;
class HelloWorld : public cocos2d::Layer
{
private:
    cocos2d::Size visibleSize;
    cocos2d::LayerColor *layerColorGB;
    SnakeSprite *snake;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC(HelloWorld);
    void handleDirect(cocos2d::Point point);
};

#endif // __HELLOWORLD_SCENE_H__
