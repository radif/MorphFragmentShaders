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

class MorphSprite : public cocos2d::CCSprite, public cocos2d::CCTouchDelegate {
    typedef cocos2d::CCSprite super;
    
    int _timeUniformLocation=0;
    float _totalTime=0;
    
    int _touch1PositionXUniformLocation=0; int _touch1PositionYUniformLocation=0;
    cocos2d::CCPoint _touch1Position{-1.f,-1.f};
    
    int _touch2PositionXUniformLocation=0; int _touch2PositionYUniformLocation=0;
    cocos2d::CCPoint _touch2Position{-1.f,-1.f};
    
    void initShader(const char *fshFileName);
    void update(float dt);
    
    virtual void onEnter();
    virtual void onExit();
    
    //touches
    cocos2d::CCPoint convertToShaderSpace(const cocos2d::CCPoint & loc, bool & onSpriteArea);
    void convertTouchesIntoShaderPoints(cocos2d::CCSet *pTouches, bool ended=false);

    // optional
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
public:
    static MorphSprite* create(const char *pszFileName, const char *fshFileName);
protected:
    MorphSprite();
    virtual ~MorphSprite();
};

#endif /* defined(__morph__MorphSprite__) */
