//
//  ExControlButton.h
//  GameXtension
//
//  Created by HuyPhan on 7/23/15.
//
//

#ifndef __GameXtension__ExControlButton__
#define __GameXtension__ExControlButton__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "SSMacros.h"

//USING_NS_CC;
USING_NS_CC_EXT;

//using namespace std;

NS_SS_BEGIN

class ExControlButton : public ControlButton
{
public:
    ExControlButton();
    static ExControlButton* create(cocos2d::ui::Scale9Sprite* sprite);

    void setFuncName(const std::string& strFuncName);
//    void setExTextColorForState(Control::State state, Color3B color);
    void setBgColorForState(Control::State state, cocos2d::Color3B color);
    void setIconColorForState(Control::State state, cocos2d::Color3B color);
    void setBorderColorForState(Control::State state, cocos2d::Color3B color);
    void updateUI();
    
    CREATE_FUNC(ExControlButton);
    
protected:
    virtual bool init() override;
    
    std::string _strFuncName;
    
//    std::map<Control::State, Color3B> _mapTextState;
    
    std::map<Control::State, cocos2d::Color3B> _mapBgState;
    std::map<Control::State, cocos2d::Color3B> _mapIconState;
    std::map<Control::State, cocos2d::Color3B> _mapBorderState;
};

#define CONVERT_TO_EX_BTN(__strFuncName__, __pBtn__, __selector__) \
{ \
    cocos2d::ui::Scale9Sprite* sprites[3]; \
    std::string strTempSpriteName = ""; \
    std::vector<std::string> vecString; \
    vecString.push_back("normal"); \
    vecString.push_back("select"); \
    vecString.push_back("disable"); \
    std::string strFuncName = __strFuncName__; \
    int spriteIndex = 0; \
    for(auto iter = vecString.begin(); iter != vecString.end(); iter++) \
    { \
        bool bBreak = false; \
        strTempSpriteName = cocos2d::__String::createWithFormat("%s_%s_01.png", strFuncName.c_str(), iter->c_str())->getCString(); \
        auto pFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(strTempSpriteName); \
        if(pFrame) \
        { \
            sprites[spriteIndex++] = cocos2d::ui::Scale9Sprite::createWithSpriteFrame(pFrame); \
            bBreak = true; \
        } \
    } \
    senspark::ExControlButton* pExBtn = senspark::ExControlButton::create(); \
    if (sprites[0] != nullptr) pExBtn->setBackgroundSpriteForState(sprites[0], cocos2d::extension::Control::State::NORMAL); \
    if (sprites[1] != nullptr) pExBtn->setBackgroundSpriteForState(sprites[1], cocos2d::extension::Control::State::HIGH_LIGHTED); \
    if (sprites[2] != nullptr) pExBtn->setBackgroundSpriteForState(sprites[2], cocos2d::extension::Control::State::DISABLED); \
    pExBtn->setEnabled(__pBtn__->isEnabled()); \
    pExBtn->setPreferredSize(__pBtn__->getPreferredSize()); \
    pExBtn->setPosition(__pBtn__->getPosition()); \
    pExBtn->setAnchorPoint(__pBtn__->getAnchorPoint()); \
    pExBtn->setScale(__pBtn__->getScaleX(), __pBtn__->getScaleY()); \
    pExBtn->setTitleLabel(__pBtn__->getTitleLabel()); \
    pExBtn->setZoomOnTouchDown(__pBtn__->getZoomOnTouchDown()); \
    pExBtn->setVisible(__pBtn__->isVisible()); \
    pExBtn->setRotation(__pBtn__->getRotation()); \
    pExBtn->setOpacity(__pBtn__->getOpacity()); \
    std::vector<Control::State> vecTemp; \
    vecTemp.push_back(Control::State::NORMAL); \
    vecTemp.push_back(Control::State::HIGH_LIGHTED); \
    vecTemp.push_back(Control::State::DISABLED); \
    for(auto iter = vecTemp.begin(); iter != vecTemp.end(); iter++) \
    { \
        if(__pBtn__->getTitleBMFontForState(*iter).compare("") != 0) \
        { \
            pExBtn->setTitleBMFontForState(__pBtn__->getTitleBMFontForState(*iter), *iter); \
        } \
        if(__pBtn__->getTitleTTFForState(*iter).compare("") != 0) \
        { \
            pExBtn->setTitleTTFForState(__pBtn__->getTitleTTFForState(*iter), *iter); \
            pExBtn->setTitleTTFSizeForState(__pBtn__->getTitleTTFSizeForState(*iter), *iter); \
        } \
        pExBtn->setTitleForState(__pBtn__->getTitleForState(*iter), *iter); \
        pExBtn->setTitleColorForState(__pBtn__->getTitleColorForState(*iter), *iter); \
    } \
    pExBtn->setFuncName(__strFuncName__); \
    if(__pBtn__->getParent()) \
    { \
        __pBtn__->getParent()->addChild(pExBtn, __pBtn__->getLocalZOrder(), __pBtn__->getTag()); \
        if(__pBtn__->getName().compare("") != 0) \
        { \
            pExBtn->setName(__pBtn__->getName()); \
        } \
        __pBtn__->getParent()->removeChild(__pBtn__); \
        __pBtn__ = nullptr; \
        __pBtn__ = pExBtn; \
    } \
    pExBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(__selector__), cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE); \
    pExBtn->updateUI(); \
}

NS_SS_END

#endif /* defined(__GameXtension__ExControlButton__) */
