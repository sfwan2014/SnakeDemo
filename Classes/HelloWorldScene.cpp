#include "HelloWorldScene.h"
#include "SnakeScene.h"
#include "BodyScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setSpeed(10);
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    drawBackground();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch *t, Event *e){
        if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation())) {
            Point point = t->getPreviousLocation();
            this->handleDirect(point);
            return true;
        }
        return  false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
//    auto contactListener = EventListenerPhysicsContact::create();
//    contactListener->onContactBegin = [this](PhysicsContact& contact){
//        switch (contact.getShapeA()->getBody()->getContactTestBitmask()|contact.getShapeB()->getBody()->getContactTestBitmask()) {
//            case SNAKE_BODY_BIT_MAST|SNAKE_HEAD_BIT_MAST:
//            {
////                log("自身相撞");
////                    snake->end();
////                    Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
//            }
//                break;
//            case SNAKE_HEAD_BIT_MAST|EDGE_BIT_MASK:
//            {
//                log("撞墙");
//                snake->end();
//                Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
//            }
//                break;
//            case SNAKE_HEAD_BIT_MAST|SNAKE_FOOD_BIT_MAST:
//            {
////                log("eat");
////                this->growUp();
////                this->createFood();
////                this->changeFoodPosition();
//            }
//                break;
//                
//            default:
//                break;
//        }
//        
//        return true;
//    };
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

void HelloWorld::handleDirect(cocos2d::Point point)
{
    Direct d = snake->getDirect();
    Point p = snake->getPosition();
    short xx = point.x - p.x;
    short yy = (point.y - (visibleSize.height-visibleSize.width)/2) - p.y;
    
    Direct newDirect = d;
    switch (d) {
        case Up:
        {
            if (abs(xx) > abs(yy)) {
                if (xx > 0) {
                    // right
                    newDirect = Right;
                } else {
                    //left
                    newDirect = Left;
                }
            } else {
                if (yy < 0) {
                    // down
//                    newDirect = Down;
                }
            }
        }
            break;
        case Down:
        {
            if (abs(xx) > abs(yy)) {
                if (xx > 0) {
                    // right
                    newDirect = Right;
                } else {
                    //left
                    newDirect = Left;
                }
            } else {
                if (yy > 0) {
                    // up
//                    newDirect = Up;
                }
                
            }
        }
            break;
        case Left:
        {
            if (abs(yy) > abs(xx)) {
                if (yy > 0) {
                    // up
                    newDirect = Up;
                } else {
                    //down
                    newDirect = Down;
                }
            } else {
                if (xx > 0) {
                    // right
//                    newDirect = Right;
                }
                
            }
        }
            break;
        case Right:
        {
            if (abs(yy) > abs(xx)) {
                if (yy > 0) {
                    // up
                    newDirect = Up;
                } else {
                    //down
                    newDirect = Down;
                }
            } else {
                if (xx < 0) {
                    // left
//                    newDirect = Left;
                }
                
            }
        }
            break;
        default:
            newDirect = d;
            break;
    }
    
    snake->setDirect(newDirect);
}

void HelloWorld::drawBackground()
{
    int width = visibleSize.width;
    int height = visibleSize.height;
 
    layerColorGB = cocos2d::LayerColor::create(Color4B(200,200,200,255), width, width);
    layerColorGB->setPosition(Point(0, (visibleSize.height-visibleSize.width)/2));
    addChild(layerColorGB);
    
    width = width;
    height = width;
    
    int column = width/20;
    int row = height/20;
    for (int i = 0; i < row; i++) {
        int y = i * 20;
        Point p = Point(0, y);
        Size size = Size(width, 1);
        LayerColor *line = LayerColor::create(Color4B(255, 0, 255, 200), size.width, size.height);
        line->setPosition(p);
        layerColorGB->addChild(line);
    }
    
    for (int j = 0; j < column; j++) {
        int x = j *20;
        Point p = Point(x, 0);
        Size size = Size(1, height);
        LayerColor *line = LayerColor::create(Color4B(255, 0, 255, 200), size.width, size.height);
        line->setPosition(p);
        layerColorGB->addChild(line);
    }
    // 创建蛇
    initSnake();
}

void HelloWorld::initSnake(){
    snake = SnakeSprite::createSnake(1);
    // eat
    snake->onEat = [this](SnakeSprite *s, void * v){
        this->growUp();
    };
    // game over
    snake->reGameOver = [](void *v){
        Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
    };
    layerColorGB->addChild(snake);
    snake->start();
    // 创建食物
    this->createFood();
    snake->setFood(food);
}

BodyScene* HelloWorld::createFood(){
    // 加入随机整数
    srand((unsigned)time(NULL));
    int x = rand()%32 * 20+10;
    int y = rand()%32 * 20+10;
    x = MIN(x, 630);
    y = MIN(y, 630);
    Point position = Point(x,y);
    Size size = Size(20,20);
    
    food = BodyScene::createBody(position, size);
    layerColorGB->addChild(food);
    return food;
}

void HelloWorld::growUp(){
    __Array *bodys = snake->getBodys();
    __Array *newBodys = __Array::create();
    newBodys->addObject(food);
    
    food->removeFromParent();
    snake->addChild(food);
    newBodys->addObjectsFromArray(bodys);
    snake->setBodys(newBodys);
    
    createFood();
    snake->setFood(food);
}
