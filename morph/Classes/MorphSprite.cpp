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
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
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
        
        _touchPositionXUniformLocation= glGetUniformLocation(program->getProgram(), "u_touchPosX");
        _touchPositionYUniformLocation= glGetUniformLocation(program->getProgram(), "u_touchPosY");
        
        scheduleUpdate();

        program->use();

    }
}

void MorphSprite::update(float dt)
{
    _totalTime += dt;
    getShaderProgram()->use();
    
    glUniform1f(_timeUniformLocation, _totalTime);
    
    glUniform1f(_touchPositionXUniformLocation, _touchPosition.x);
    glUniform1f(_touchPositionYUniformLocation, _touchPosition.y);
    
    
}

#pragma mark touches
cocos2d::CCPoint MorphSprite::convertToShaderSpace(const cocos2d::CCPoint & loc, bool & onSpriteArea){
    const CCSize sz(getContentSize());
    auto retVal(convertToNodeSpace(loc));
    retVal.x/=sz.width;
    retVal.y/=sz.height;
    
    onSpriteArea=(!(retVal.x>1.f || retVal.x<0.f || retVal.y>1.f || retVal.y<0.f));
    if (!onSpriteArea)
        retVal={.5,.5};
    
    retVal.y=1.0f-retVal.y;
    return retVal;
}
bool MorphSprite::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    bool isTouching(false);
    _touchPosition=convertToShaderSpace(pTouch->getLocation(), isTouching);
        //std::cout<<_touchPosition.x << ", "<< _touchPosition.y<<"\n";
    return isTouching;
}
void MorphSprite::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    bool isTouching(false);
    _touchPosition=convertToShaderSpace(pTouch->getLocation(), isTouching);
}
void MorphSprite::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){}
void MorphSprite::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){}

