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
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    addChild(rootNode);
    setupGameCharacters();
    scheduleUpdate();
    return true;
}

void HelloWorld::setupGameCharacters()
{
    auto director = Director::getInstance();
    auto curRes =director->getWinSize();
    
    SpriteBatchNode* spritebatch = SpriteBatchNode::create("sprites.png");
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("sprites.plist");
    
    m_pMagician = Sprite::createWithSpriteFrameName("slice123_.png");
    spritebatch->addChild(m_pMagician);
    addChild(spritebatch);
    m_pMagician->runAction( createAnimation(m_pMagician,cache,"slice123_.png","slice124_.png") );
    m_pMagician->setScale(10.0f);
    m_pMagician->setPosition(curRes.width*0.15, curRes.height*0.8);
   
    
    m_pKnight = Sprite::createWithSpriteFrameName("slice354_.png");
    spritebatch->addChild(m_pKnight);
    addChild(spritebatch);
    m_pKnight->runAction( createAnimation(m_pKnight,cache,"slice354_.png","slice355_355.png") );
    m_pKnight->setScale(10.0f);
    m_pKnight->setPosition(curRes.width*0.15, curRes.height*0.6);
    
    m_pWarrior = Sprite::createWithSpriteFrameName("slice368_@.png");
    spritebatch->addChild(m_pWarrior);
    addChild(spritebatch);
    m_pWarrior->runAction( createAnimation(m_pWarrior,cache,"slice368_@.png","slice369_@.png") );
    m_pWarrior->setScale(10.0f);
    m_pWarrior->setPosition(curRes.width*0.15, curRes.height*0.4);
    
    m_pMonster = Sprite::createWithSpriteFrameName("slice251_.png");
    spritebatch->addChild(m_pMonster);
    addChild(spritebatch);
    m_pMonster->setFlippedX(true);
    m_pMonster->runAction( createAnimation(m_pMonster,cache,"slice251_.png","slice252_.png") );
    m_pMonster->setScale(10.0f);
    m_pMonster->setPosition(curRes.width*0.85, curRes.height*0.8);
}

Action* HelloWorld::createAnimation(Sprite* curSprite,SpriteFrameCache* cache,const std::string& frmName01,const std::string& frmName02)
{
    Vector<SpriteFrame*> animFrames(2);
    SpriteFrame* frame1 = cache->getSpriteFrameByName( frmName01 );
    animFrames.pushBack(frame1);
    SpriteFrame* frame2 = cache->getSpriteFrameByName( frmName02 );
    animFrames.pushBack(frame2);
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    Action* curAction = RepeatForever::create( Animate::create(animation));
    curAction->setTag(1);
    
    return curAction;
}

void HelloWorld::update(float delta)
{
    //CCLOG("%f",delta);
    float x = m_pMonster->getPositionX();
    x -= 0.1f;
    m_pMonster->setPosition(x, m_pMonster->getPositionY());
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    CCLOG("onTouchBegan");
    return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    CCLOG("onTouchEnded");
    
    if (m_pMagician->getActionByTag(2)||m_pKnight->getActionByTag(2)||m_pWarrior->getActionByTag(2)) {
        return;
    }
    
    Vec2 pos1 = m_pMagician->getPosition();
    Vec2 pos2 = m_pKnight->getPosition();
    Vec2 pos3 = m_pWarrior->getPosition();
    
    Action* mvMagician =MoveTo::create(0.5f, pos2);
    mvMagician->setTag(2);
    Action* mvKnight =MoveTo::create(0.5f, pos3);
    mvKnight->setTag(2);
    Action* mvWarrior =MoveTo::create(0.5f, pos1);
    mvWarrior->setTag(2);
    
    m_pMagician->runAction(mvMagician);
    m_pKnight->runAction(mvKnight);
    m_pWarrior->runAction(mvWarrior);
    
    //m_pMagician->setPosition(pos2);
    //m_pKnight->setPosition(pos3);
    //m_pWarrior->setPosition(pos1);
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    CCLOG("onTouchMoved");
}

void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
{
    CCLOG("onTouchCancelled");
}