#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
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
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    addChild(rootNode);
    
    SpriteBatchNode* spritebatch = SpriteBatchNode::create("sprites.png");
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("sprites.plist");
    Sprite* Sprite1 = Sprite::createWithSpriteFrameName("slice354_.png");
    spritebatch->addChild(Sprite1);
    addChild(spritebatch);
    
    Vector<SpriteFrame*> animFrames(2);
    SpriteFrame* frame1 = cache->getSpriteFrameByName( "slice354_.png" );
    animFrames.pushBack(frame1);
    SpriteFrame* frame2 = cache->getSpriteFrameByName( "slice355_355.png" );
    animFrames.pushBack(frame2);
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    //auto animate = Animate::create(animation);
    Sprite1->runAction( RepeatForever::create( Animate::create(animation) ) );
    Sprite1->setScale(10.0f);
    Sprite1->setPosition(100, 100);
    return true;
}
