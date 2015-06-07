#ifndef __GAMEWORLD_SCENE_H__
#define __GAMEWORLD_SCENE_H__

#include "cocos2d.h"
#include "GameSprite.h"
using namespace cocos2d;

class GameWorld : public cocos2d::Layer
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
    CREATE_FUNC(GameWorld);
    
private:
    
    GameSprite* m_pMagician;
    GameSprite* m_pKnight;
    GameSprite* m_pWarrior;
    
    bool m_isChangeScene;
    int m_WorldCounter;
    int m_Hits;
    int m_Misses;
    //GameSprite* m_pMonster;
    Vector<GameSprite*> m_pMonsterGroup01;
    Vector<GameSprite*> m_pMonsterGroup02;
    Vector<GameSprite*> m_pMonsterGroup03;
    
    void setupGameCharacters();
    void setupMonsters(int laneID);
    void changeScene();
    void monsterAI(Vector<GameSprite*> &gameSpriteVector,Sprite* charSprite,int vectorIdx);
 
};

#endif // __GameWorld_SCENE_H__
