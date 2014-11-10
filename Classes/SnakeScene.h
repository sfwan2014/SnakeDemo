//
//  SnakeScene.h
//  Snake
//
//  Created by sfwan on 14-11-10.
//
//

#ifndef __Snake__SnakeScene__
#define __Snake__SnakeScene__
#define EDGE_BIT_MASK   0b1000
#define SNAKE_BIT_MAST  0b0001
#include "cocos2d.h"

typedef enum : int {
    Up,
    Down,
    Left,
    Right,
} Direct;

class SnakeSprite:public cocos2d::Sprite{
private:
    int number;
    cocos2d::__Array *bodys;
    Direct direct;
public:
    virtual bool init();
    
    static SnakeSprite *createSnake(int num);
    void enemyInit(int num);
    
    CREATE_FUNC(SnakeSprite);
    
    int getNember();
    void setNumber(int num);
    
    Direct getDirect();
    void setDirect(Direct d);
    
    void run(float x);
    bool start();
};

#endif /* defined(__Snake__SnakeScene__) */
