//
//  GameSprite.h
//  Prototype02
//
//  Created by Ronnie Tan on 6/6/15.
//
//

#ifndef __Prototype02__GameSprite__
#define __Prototype02__GameSprite__

#include "cocos2d.h"

using namespace cocos2d;

class GameSprite : public Sprite
{
public:
    GameSprite( const std::string& frmName01,const std::string& frmName02);
    ~GameSprite();
    void setSpeed(float spd);
    float getSpeed();
    void setIsDead(bool isDead);
    bool getIsDead();
    bool getGameOver();
    bool getIsDeadAnimateEnd();
    void processAI(Rect collideBox);
    
private:
    float m_speed;
    bool m_isDead;
    bool m_isDeadAnimateEnd;
    bool m_isGameOver;
    void setIsDeadAnimateEnd();
    void animateDead();
};

#endif /* defined(__Prototype02__GameSprite__) */

