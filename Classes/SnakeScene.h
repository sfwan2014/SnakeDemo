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
#define SNAKE_HEAD_BIT_MAST  0b0001
#define SNAKE_BODY_BIT_MAST  0b0010
#define SNAKE_FOOD_BIT_MAST  0b0100
#include "cocos2d.h"

typedef enum : int {
    Up = 0,
    Down,
    Left,
    Right,
} Direct;

class SnakeSprite:public cocos2d::Sprite{
private:
    int number;
    cocos2d::__Array *bodys;
    Direct direct;
    cocos2d::Point position;
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
    void end();
    
    void setPosition(cocos2d::Point p);
    cocos2d::Point getPosition();
    
    void addBody();
};

#endif /* defined(__Snake__SnakeScene__) */
