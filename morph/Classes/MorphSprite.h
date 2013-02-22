//
//  MorphSprite.h
//  morph
//
//  Created by Radif Sharafullin on 2/21/13.
//
//

#ifndef __morph__MorphSprite__
#define __morph__MorphSprite__

#include "cocos2d.h"

class MorphSprite : public cocos2d::CCSprite, public cocos2d::CCTargetedTouchDelegate {
    typedef cocos2d::CCSprite super;
    
    int _timeUniformLocation=0;
    float _totalTime=0;
    
    int _touchPositionXUniformLocation=0; int _touchPositionYUniformLocation=0;
    cocos2d::CCPoint _touchPosition{.5f,.5f};
    
    void initShader(const char *fshFileName);
    void update(float dt);
    
    virtual void onEnter();
    virtual void onExit();
    
    //touches
    cocos2d::CCPoint convertToShaderSpace(const cocos2d::CCPoint & loc, bool & onSpriteArea);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
public:
    static MorphSprite* create(const char *pszFileName, const char *fshFileName);
protected:
    MorphSprite();
    virtual ~MorphSprite();
};

#endif /* defined(__morph__MorphSprite__) */
