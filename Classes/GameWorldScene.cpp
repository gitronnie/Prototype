#include "GameWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#define WHITE_TYPE   1
#define GREEN_TYPE   2
#define BLUE_TYPE   3

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameWorld::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameWorld::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameWorld::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    m_isChangeScene=false;
    m_WorldCounter=100;
    
    addChild(rootNode);
    setupGameCharacters();
    setupMonsters(1);
    setupMonsters(2);
    setupMonsters(3);
    scheduleUpdate();
    return true;
}

void GameWorld::setupGameCharacters()
{
    auto director = Director::getInstance();
    auto curRes =director->getWinSize();
    
    //SpriteBatchNode* spritebatch = SpriteBatchNode::create("sprites.png");
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("sprites.plist");
    
    m_pMagician = new GameSprite("slice123_.png","slice124_.png");
    m_pMagician->autorelease();
    //spritebatch->addChild(m_pMagician);
    //addChild(spritebatch);
    addChild(m_pMagician);
    m_pMagician->setScale(10.0f);
    m_pMagician->setPosition(curRes.width*0.15, curRes.height*0.8);
   
    
    m_pKnight = new GameSprite("slice354_.png","slice355_355.png");
    m_pKnight->autorelease();
    //spritebatch->addChild(m_pKnight);
    //addChild(spritebatch);
    addChild(m_pKnight);
    m_pKnight->setScale(10.0f);
    m_pKnight->setPosition(curRes.width*0.15, curRes.height*0.6);
    
    m_pWarrior = new GameSprite("slice368_@.png","slice369_@.png");
    m_pWarrior->autorelease();
    //spritebatch->addChild(m_pWarrior);
    //addChild(spritebatch);
    addChild(m_pWarrior);
    m_pWarrior->setScale(10.0f);
    m_pWarrior->setPosition(curRes.width*0.15, curRes.height*0.4);
    
}

void GameWorld::setupMonsters(int laneID)
{
    auto director = Director::getInstance();
    auto curRes =director->getWinSize();
    
    GameSprite* monster = new GameSprite("slice251_.png","slice252_.png");
    monster->autorelease();
    //spritebatch->addChild(m_pMonster);
    //addChild(spritebatch);
    //addChild(monster);
    monster->setFlippedX(true);
    monster->setScale(10.0f);
    
    //auto tintRed = TintTo::create(0.1f, 255,0,0);
    auto tintBlue = TintTo::create(0.1f, 0,255,0);
    auto tintGreen = TintTo::create(0.1f, 0,0,255);
    
    //float rndPosY[3] = {(curRes.height*0.8),};
    float rndPosY[3];
    rndPosY[0] = curRes.height*0.8;
    rndPosY[1] = curRes.height*0.6;
    rndPosY[2] = curRes.height*0.4;
    
    int rnd = rand()%2;
    
    switch (laneID) {
        case WHITE_TYPE:
                    monster->setPosition(curRes.width*0.85, rndPosY[rnd]);
                    monster->setSpeed(2.0f);
                    m_pMonsterGroup01.pushBack(monster);
                    addChild(m_pMonsterGroup01.back());
                    break;
        
        case GREEN_TYPE:
                    monster->setPosition(curRes.width*0.85, curRes.height*0.6);
                    monster->runAction(tintGreen);
                    m_pMonsterGroup02.pushBack(monster);
                    addChild(m_pMonsterGroup02.back());
                    break;
            
        case BLUE_TYPE:
                    monster->setPosition(curRes.width*0.85, curRes.height*0.4);
                    monster->runAction(tintBlue);
                    m_pMonsterGroup03.pushBack(monster);
                    addChild(m_pMonsterGroup03.back());
                    break;
        
        default:
            break;
    }
    
}

void GameWorld::update(float delta)
{
    //CCLOG("%f",delta);
    //float x = m_pMonster->getPositionX();
    //x -= 0.1f;
    //m_pMonster->setPosition(x, m_pMonster->getPositionY());
    m_WorldCounter--;
    if(m_isChangeScene){return;}
    
    monsterAI(m_pMonsterGroup01, m_pMagician, WHITE_TYPE);
    
    //Random adding
    if(m_WorldCounter == 0)
    {
        setupMonsters(1);
        //int addProbability = rand() % 100 + 1;
        //if(addProbability > 90){setupMonsters(1);}
        m_WorldCounter=100;
    }
}

void GameWorld::changeScene()
{
    auto curScene = GameWorld::createScene();
    Director::getInstance()->replaceScene(curScene);
    CCLOG("change scene");
}

void GameWorld::monsterAI(Vector<GameSprite*> &gameSpriteVector,Sprite* charSprite,int vectorIdx)
{
    if(gameSpriteVector.size()==0)
    {
        setupMonsters(vectorIdx);
        return;
    }
    for (Vector<GameSprite*>::iterator it = gameSpriteVector.begin() ; it != gameSpriteVector.end(); ++it)
    {
        if((*it)->getIsDead() && (*it)->getIsDeadAnimateEnd())
        {
            this->removeChild((*it));
            (&gameSpriteVector)->eraseObject((*it));
            
            //CCLOG("vector01:%d",m_pMonsterGroup01.size());
            if(gameSpriteVector.size()==0)
            {
                break;
            }
        }
        if((*it)->getGameOver())
        {
            changeScene();
            m_isChangeScene=true;
            break;
        }
        if(*it != NULL)
        {
            (*it)->processAI(charSprite->getBoundingBox());
        }
    }

}

bool GameWorld::onTouchBegan(Touch* touch, Event* event)
{
    CCLOG("onTouchBegan");
    return true;
}

void GameWorld::onTouchEnded(Touch* touch, Event* event)
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

void GameWorld::onTouchMoved(Touch* touch, Event* event)
{
    CCLOG("onTouchMoved");
}

void GameWorld::onTouchCancelled(Touch* touch, Event* event)
{
    CCLOG("onTouchCancelled");
}