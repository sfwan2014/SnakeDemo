//
//  SnakeScene.h
//  Snake
//
//  Created by sfwan on 14-11-10.
//
//

#ifndef __Snake__SnakeScene__
#define __Snake__SnakeScene__
//#define EDGE_BIT_MASK   0b1000
//#define SNAKE_HEAD_BIT_MAST  0b0001
//#define SNAKE_BODY_BIT_MAST  0b0010
//#define SNAKE_FOOD_BIT_MAST  0b0100
#include "cocos2d.h"

typedef enum : int {
    Up = 0,
    Down,
    Left,
    Right,
} Direct;
class BodyScene;
class SnakeSprite:public cocos2d::Sprite{
private:
    int number;
    cocos2d::__Array *bodys;
    Direct direct;
    cocos2d::Point position;    //
    BodyScene *food;// food 用来判断是否吃到食物
public:
    std::function<void(SnakeSprite*, void*)> onEat;
    std::function<void(void*)> reGameOver;
    virtual bool init();
    // 创建方法
    static SnakeSprite *createSnake(int num);
    void enemyInit(int num);
    
    CREATE_FUNC(SnakeSprite);
    // get set 方向
    Direct getDirect();
    void setDirect(Direct d);
    // 跑的动作
    void run(float x);
    // 开始跑
    bool start();
    // 结束
    void end();
    
    void setPosition(cocos2d::Point p);
    cocos2d::Point getPosition();
    
    cocos2d::__Array *getBodys();
    void setBodys(cocos2d::__Array *bs);
    
    BodyScene *getFood();
    // 设置food 用来判断是否吃到食物
    void setFood(BodyScene *b);
    // 判断是否继续游戏
    bool GameOver();
    
//    void addBody();
};

#endif /* defined(__Snake__SnakeScene__) */
