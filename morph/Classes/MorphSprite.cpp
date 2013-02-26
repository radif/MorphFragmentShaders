//
//  MorphSprite.cpp
//  morph
//
//  Created by Radif Sharafullin on 2/21/13.
//
//

#include "MorphSprite.h"
using namespace cocos2d;

MorphSprite::MorphSprite(){}
MorphSprite::~MorphSprite(){}

MorphSprite* MorphSprite::create(const char *pszFileName, const char *fshFileName){
    MorphSprite *pobSprite = new MorphSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        pobSprite->initShader(fshFileName);
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

void MorphSprite::onEnter(){
    super::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void MorphSprite::onExit(){
    super::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}



void MorphSprite::initShader(const char *fshFileName){
    
    const GLchar *  fragmentSource =(GLchar *)CCString::createWithContentsOfFile(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(fshFileName))->getCString();
    
    CCGLProgram * program= new CCGLProgram;
    if (program){
        program->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, fragmentSource);
        setShaderProgram(program);
        program->release();
        program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
        program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);        
        program->link();
        program->updateUniforms();
        _timeUniformLocation = glGetUniformLocation(program->getProgram(), "u_time");
        
        _touch1PositionXUniformLocation= glGetUniformLocation(program->getProgram(), "u_touch1PosX");
        _touch1PositionYUniformLocation= glGetUniformLocation(program->getProgram(), "u_touch1PosY");
        
        _touch2PositionXUniformLocation= glGetUniformLocation(program->getProgram(), "u_touch2PosX");
        _touch2PositionYUniformLocation= glGetUniformLocation(program->getProgram(), "u_touch2PosY");
        
        scheduleUpdate();

        program->use();

    }
}

void MorphSprite::update(float dt)
{
    _totalTime += dt;
    getShaderProgram()->use();
    
    glUniform1f(_timeUniformLocation, _totalTime);
    
    glUniform1f(_touch1PositionXUniformLocation, _touch1Position.x);
    glUniform1f(_touch1PositionYUniformLocation, _touch1Position.y);
    
    glUniform1f(_touch2PositionXUniformLocation, _touch2Position.x);
    glUniform1f(_touch2PositionYUniformLocation, _touch2Position.y);
    
    
}

#pragma mark touches
cocos2d::CCPoint MorphSprite::convertToShaderSpace(const cocos2d::CCPoint & loc, bool & onSpriteArea){
    const CCSize sz(getContentSize());
    auto retVal(convertToNodeSpace(loc));
    retVal.x/=sz.width;
    retVal.y/=sz.height;
    
    retVal.y=1.0f-retVal.y;
    
    onSpriteArea=(!(retVal.x>1.f || retVal.x<0.f || retVal.y>1.f || retVal.y<0.f));
    if (!onSpriteArea)
        retVal={-1.f,-1.f};
    
    return retVal;
}

void MorphSprite::convertTouchesIntoShaderPoints(cocos2d::CCSet *pTouches, bool ended){
    if (ended) {
        _touch1Position={-1.f,-1.f};
        _touch2Position={-1.f,-1.f};
    }else{
        bool isTouching(false);
        int counter(0);
        for (CCSetIterator i(pTouches->begin());i!=pTouches->end();++i) {
            CCTouch *pTouch((CCTouch *)(*i));
            switch (counter) {
                case 0:
                    _touch1Position=convertToShaderSpace(pTouch->getLocation(), isTouching);
                    _touch2Position={-1.f,-1.f};
                    break;
                case 1:
                    _touch2Position=convertToShaderSpace(pTouch->getLocation(), isTouching);
                    break;
                default:
                    break;
            }
            counter++;
        }
    }
}
void MorphSprite::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    convertTouchesIntoShaderPoints(pTouches);
}
void MorphSprite::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    convertTouchesIntoShaderPoints(pTouches);
}
void MorphSprite::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    convertTouchesIntoShaderPoints(pTouches,true);
}
void MorphSprite::ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){
    ccTouchesEnded(pTouches, pEvent);
}




