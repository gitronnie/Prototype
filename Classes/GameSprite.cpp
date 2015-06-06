//
//  GameSprite.cpp
//  Prototype02
//
//  Created by Ronnie Tan on 6/6/15.
//
//

#include "GameSprite.h"
#include <string.h>

GameSprite::GameSprite(const std::string& frmName01,const std::string& frmName02):m_speed(0.5f),m_isDead(false),m_isGameOver(false)
{
    if(this->initWithSpriteFrameName(frmName01))
    {
        this->autorelease();
        
        SpriteFrameCache* cache = SpriteFrameCache::getInstance();
        Vector<SpriteFrame*> animFrames(2);
        SpriteFrame* frame1 = cache->getSpriteFrameByName( frmName01 );
        animFrames.pushBack(frame1);
        SpriteFrame* frame2 = cache->getSpriteFrameByName( frmName02 );
        animFrames.pushBack(frame2);
        auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
        Action* curAction = RepeatForever::create( Animate::create(animation));
        curAction->setTag(1);
        this->runAction(curAction);
    }

}

GameSprite::~GameSprite()
{

}

void GameSprite::setSpeed(float spd)
{
    m_speed=spd;
}

float GameSprite::getSpeed()
{
    return m_speed;
}

void GameSprite::setIsDead(bool isDead)
{
    m_isDead=isDead;
}
bool GameSprite::getIsDead()
{
    return m_isDead;
}

bool GameSprite::getGameOver()
{
    return m_isGameOver;
}

void GameSprite::processAI(Rect collideBox)
{
    auto director = Director::getInstance();
    auto curRes =director->getWinSize();
    
    Rect curBox = this->getBoundingBox();
    
    if(curBox.intersectsRect(collideBox))
    {
        m_isDead=true;
        return;
    }
 
    if(this->getPositionX() < (curRes.width*0.1))
    {
        //m_isGameOver=true;
        m_isDead=true;
        return;
    }
  
    float x = this->getPositionX();
    x -= m_speed;
    this->setPosition(x, this->getPositionY());
}