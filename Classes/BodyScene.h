//
//  BodyScene.h
//  Snake
//
//  Created by sfwan on 14-11-10.
//
//

#ifndef __Snake__BodyScene__
#define __Snake__BodyScene__

#include "cocos2d.h"
class BodyScene:public cocos2d::Sprite{
private:
    int x, y;
    cocos2d::Point position;
    cocos2d::Size size;
    // 显示背景
    cocos2d::LayerColor *layerColorBG;
public:
    virtual bool init();
    
    CREATE_FUNC(BodyScene);
    
    static BodyScene *createBody(cocos2d::Point position, cocos2d::Size size);;
    static BodyScene *createBody(int x, int y, cocos2d::Size size);;
    void enemyInit(cocos2d::Point position, cocos2d::Size size);
};

#endif /* defined(__Snake__BodyScene__) */
