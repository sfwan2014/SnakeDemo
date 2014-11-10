#include "HelloWorldScene.h"
#include "SnakeScene.h"

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
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch *t, Event *e){
        Point point = t->getLocation();
        this->handleDirect(point);
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [](PhysicsContact& contact){
        switch (contact.getShapeA()->getBody()->getContactTestBitmask()|contact.getShapeB()->getBody()->getContactTestBitmask()) {
            case SNAKE_BIT_MAST:
            {
                log("自身相撞");
            }
                break;
            case SNAKE_BIT_MAST|EDGE_BIT_MASK:
            {
                log("撞墙");
                Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
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
    short xx = point.x - visibleSize.width/2.0;
    short yy = point.y - visibleSize.height/2.0;
    
    Direct newDirect;
    
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
                    newDirect = Down;
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
                    newDirect = Up;
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
                    newDirect = Right;
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
                    newDirect = Left;
                }
                
            }
        }
            break;
            newDirect = d;
        default:
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