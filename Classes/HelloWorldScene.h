#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void update(float delta);

    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
private:
    
    Sprite* m_pMagician;
    Sprite* m_pKnight;
    Sprite* m_pWarrior;
    Sprite* m_pMonster;
    Vector<Sprite*> m_pMonsterGroup;
    
    void setupGameCharacters();
    Action* createAnimation(Sprite* curSprite,SpriteFrameCache* cache,const std::string& frmName01,const std::string& frmName02);
};

#endif // __HELLOWORLD_SCENE_H__
