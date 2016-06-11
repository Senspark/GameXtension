//
//  ExControlButton.cpp
//  GameXtension
//
//  Created by HuyPhan on 7/23/15.
//
//

#include "ExControlButton.h"

USING_NS_SS;

ExControlButton* ExControlButton::create(ui::Scale9Sprite* sprite)
{
    ExControlButton *pRet = new (std::nothrow) ExControlButton();
    pRet->initWithBackgroundSprite(sprite);
    pRet->autorelease();
    return pRet;
}

ExControlButton::ExControlButton()
{
    
}
bool ExControlButton::init()
{
    bool bRet = false;
    
    do
    {
        // do some things here
        _strFuncName = "";
        
        bRet = ControlButton::init();
        
    }while(false);
    
    return bRet;
}

void ExControlButton::setFuncName(const std::string& strFuncName)
{
    if(this->_strFuncName.compare(strFuncName) != 0)
    {
        this->_strFuncName = strFuncName;
    }
}

//void ExControlButton::setExTextColorForState(Control::State state, Color3B color)
//{
//    _mapTextState[state] = color;
//}

void ExControlButton::setBgColorForState(Control::State state, Color3B color)
{
    _mapBgState[state] = color;
}

void ExControlButton::setIconColorForState(Control::State state, Color3B color)
{
    _mapIconState[state] = color;
}

void ExControlButton::setBorderColorForState(Control::State state, Color3B color)
{
    _mapBorderState[state] = color;
}

void ExControlButton::updateUI()
{
    // prepare and set sprite frame and set color for each layer in each state
    string          strSpriteFrameName          = "";
    string          strTemplateSpriteName       = "";
    string          strFunctional               = _strFuncName;
    SpriteFrame*    pSpriteFrame                = nullptr;
    
    // temp data for iterator all the item
    std::map<Control::State, string> mapTemp;
    mapTemp[Control::State::NORMAL]             = "%s_%s_%02d.png";
    mapTemp[Control::State::HIGH_LIGHTED]       = "%s_%s_%02d.png";
    mapTemp[Control::State::DISABLED]           = "%s_%s_%02d.png";
    
    std::map<Control::State, string> mapTempState;
    mapTempState[Control::State::NORMAL]         = "normal";
    mapTempState[Control::State::HIGH_LIGHTED]   = "select";
    mapTempState[Control::State::DISABLED]       = "disable";
    
    std::map<int, std::map<Control::State, Color3B> > mapTempColorForSrite;
    mapTempColorForSrite[0]                     = _mapBgState;
    mapTempColorForSrite[1]                     = _mapIconState;
    mapTempColorForSrite[2]                     = _mapBorderState;
    
    
    for(auto iter = mapTemp.begin(); iter != mapTemp.end(); iter++)
    {
//        // set color of the title first
//        if(_mapTextState.count(iter->first) > 0)
//        {
//            this->setTitleColorForState(_mapTextState[iter->first], iter->first);
//        }
        
        // need to do this wway because getBackgroundSpriteForState func return ui::Scale9Sprite* type not relative with Sprite* type
        // first look it so complicated but it must be that
        // get the sprite content
        auto pScale9Sprite              = this->getBackgroundSpriteForState(iter->first);
//        Sprite* pSprite = nullptr;
        
        // check if it all null
        if(pScale9Sprite == nullptr)
        {
            continue;
        }
        
        for(int nLayer = 0; nLayer < 3; nLayer++)
        {
            // reset var
            pSpriteFrame                = nullptr;
            strSpriteFrameName          = "";
            strTemplateSpriteName       = "";
            
            // build the sprite frame name
            strTemplateSpriteName   = iter->second;
            if(mapTempState.count(iter->first) > 0)
            {
                strSpriteFrameName      = __String::createWithFormat(strTemplateSpriteName.c_str(),
                                                                     strFunctional.c_str(),
                                                                     mapTempState[iter->first].c_str(),
                                                                     (int)(nLayer + 1))->getCString();
            }
            
            pSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(strSpriteFrameName);
            
            // check if pSpriteFrame continue null -> continue
            if(pSpriteFrame == nullptr)
            {
                continue;
            }
            
            if(nLayer == 0)
            {
                // set color for this
//                if (pSprite)
//                {
//                    if(mapTempColorForSrite[nLayer].count(iter->first) > 0)
//                    {
//                        pSprite->setColor(mapTempColorForSrite[nLayer][iter->first]);
//                    }
//                    pSprite->setSpriteFrame(pSpriteFrame);
//                }
                
                if(pScale9Sprite)
                {
                    if(mapTempColorForSrite[nLayer].count(iter->first) > 0)
                    {
                        pScale9Sprite->setColor(mapTempColorForSrite[nLayer][iter->first]);
                    }
                    pScale9Sprite->setSpriteFrame(pSpriteFrame);
                }
            }
            else
            {
                // check and get if exist
                Sprite*     pSpriteChild    = nullptr;
                auto        pChild          = /*pSprite != nullptr ?  (pSprite->getChildByTag((int)(nLayer + 1))) :*/
                                                    (pScale9Sprite != nullptr ? pScale9Sprite->getChildByTag((int)(nLayer + 1)) : nullptr);
                if(pChild != nullptr)
                {
                    pSpriteChild = dynamic_cast<Sprite*>(pChild);
                }
                
                // check if null -> create and add it
                if(pSpriteChild == nullptr)
                {
                    pSpriteChild = Sprite::createWithSpriteFrame(pSpriteFrame);
                }
                
                // if it not null -> add an continue
                if(pSpriteChild != nullptr)
                {
                    pSpriteChild->setAnchorPoint(Vec2::ZERO);
                    
                    if(mapTempColorForSrite[nLayer].count(iter->first) > 0)
                    {
                        pScale9Sprite->setColor(mapTempColorForSrite[nLayer][iter->first]);
                    }
                    
                    // add to root
//                    if (pSprite)
//                    {
//                        if(pSprite->getChildren().find(pSpriteChild) == pSprite->getChildren().end())
//                        {
//                            pSprite->addChild(pSpriteChild, 0, (int)(nLayer + 1));
//                        }
//                    }
                    
                    if (pScale9Sprite)
                    {
                        if(pScale9Sprite->getChildren().find(pSpriteChild) == pScale9Sprite->getChildren().end())
                        {
                            cocos2d::Rect rect;
                            rect.size = pSpriteChild->getContentSize();
                            pScale9Sprite->setCapInsets(rect);
                            pScale9Sprite->addChild(pSpriteChild, 0, (int)(nLayer + 1));
                        }
                    }
                    
                    // set tag for sure
                    pSpriteChild->setTag((int)(nLayer + 1));
                }
            }
        }
    }
}
