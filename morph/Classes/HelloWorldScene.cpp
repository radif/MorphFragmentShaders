#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "MorphSprite.h"

using namespace cocos2d;
using namespace CocosDenshion;

static std::vector<const char *> _shaders{
    "worry.fsh",
    "bend.fsh",
    "bend_touchable.fsh",
    "lens_touchable.fsh",
    "turnface_touchable.fsh",
    "turnface1_touchable.fsh",
    "stretch_revert_touchable.fsh",
    "stretch_inside_touchable.fsh",
    "stretch_outside_touchable.fsh",
    "stretch_touchable.fsh"
};

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

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
    if ( !CCLayer::init() )
    {
        return false;
    }

   
    
    CCMenuItemFont *item(CCMenuItemFont::create("Next", this, menu_selector(HelloWorld::menuNextCallback)));
    
    item->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 40, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(item, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    const CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF* pLabel = CCLabelTTF::create("Testing Transparency", "Thonburi", 34);
    
    // ask director the window size
    
    // position the label on the center of the screen
    pLabel->setPosition({size.width*.5f, size.height*.5f});
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    menuNextCallback(nullptr);
    return true;
}
void HelloWorld::addMorphSprite(const char * shaderName){
    MorphSprite *s((MorphSprite *)getChildByTag(123));
    if (s) 
        removeChild(s, true);
    
    const CCSize size = CCDirector::sharedDirector()->getWinSize();
    auto pSprite = MorphSprite::create("number.png",shaderName);
    
    pSprite->setPosition({size.width*.5f, size.height*.5f});
    pSprite->setTag(123);
    this->addChild(pSprite, 5);
    
    
    //adding label
    
    CCLabelTTF *l((CCLabelTTF *)getChildByTag(1234));
    if (l)
        removeChild(l, true);
    
    
    CCLabelTTF* pLabel = CCLabelTTF::create(shaderName, "Thonburi", 24);
    
    
    // position the label on the center of the screen
    pLabel->setPosition({size.width*.5f, 60});
    pLabel->setTag(1234);
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
}
void HelloWorld::menuNextCallback(CCObject* pSender)
{
    addMorphSprite(_shaders[_shaderIndex]);
    _shaderIndex++;
    if (_shaderIndex==_shaders.size())
        _shaderIndex=0;
}
