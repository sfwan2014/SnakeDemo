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
    
    layerColorGB = cocos2d::LayerColor::create(Color4B(200,200,200,255), visibleSize.width, visibleSize.height);
    addChild(layerColorGB);
    
    snake = SnakeSprite::createSnake(1);
    addChild(snake);
    snake->start();
    
    this->createFood();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch *t, Event *e){
        Point point = t->getLocation();
        this->handleDirect(point);
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [this](PhysicsContact& contact){
        switch (contact.getShapeA()->getBody()->getContactTestBitmask()|contact.getShapeB()->getBody()->getContactTestBitmask()) {
            case SNAKE_BODY_BIT_MAST|SNAKE_HEAD_BIT_MAST:
            {
                log("自身相撞");
                    snake->end();
                    Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
            }
                break;
            case SNAKE_HEAD_BIT_MAST|EDGE_BIT_MASK:
            {
                log("撞墙");
                snake->end();
                Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
            }
                break;
            case SNAKE_HEAD_BIT_MAST|SNAKE_FOOD_BIT_MAST:
            {
                log("eat");
                snake->addBody();
                this->changeFoodPosition();
            }
                break;
                
            default:
                break;
        }
        
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

void HelloWorld::handleDirect(cocos2d::Point point)
{
    Direct d = snake->getDirect();
    Point p = snake->getPosition();
    short xx = point.x - p.x;
    short yy = point.y - p.y;
    
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

void HelloWorld::onEnter(){
    Layer::onEnter();
    
    auto bounds = Node::create();
    bounds->setContentSize(visibleSize);
    bounds->setPosition(visibleSize/2);
    bounds->setPhysicsBody(PhysicsBody::createEdgeBox(bounds->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT, 0));
    bounds->getPhysicsBody()->setContactTestBitmask(EDGE_BIT_MASK);
    addChild(bounds);
}

void HelloWorld::createFood(){
    int x = rand()%16 * 20;
    int y = rand()%24 * 20;
    Point position = Point(x,y);
    Size size = Size(20,20);
    food = BodyScene::createBody(position, size);
    food->setPhysicsBody(PhysicsBody::createBox(size));
    food->getPhysicsBody()->setContactTestBitmask(SNAKE_FOOD_BIT_MAST);
    addChild(food);
}

void HelloWorld::changeFoodPosition(){
    int x = rand()%16 * 20;
    int y = rand()%24 * 20;
    Point position = Point(x,y);
    food->setPosition(position);
}
