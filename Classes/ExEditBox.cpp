//
//  ExEditBox.cpp
//  senspark-game-foundation
//
//  Created by HuyPhan on 12/1/14.
//
//

#include "ExEditBox.h"

NS_SS_BEGIN

ExEditBox::ExEditBox() :    _animationWhenKeyboardMoving(false),
                            _bIsScheduleUpdateMaxText(false),
                            _strPreviousText(""),
                            _maxTextureSize(0),
                            pLable(nullptr)
{
}

ExEditBox* ExEditBox::create(const cocos2d::Size &size,
                             ui::Scale9Sprite *normalSprite,
                             ui::Scale9Sprite *pressedSprite,
                             ui::Scale9Sprite* disabledSprite)
{
    ExEditBox* pRet = new (std::nothrow) ExEditBox();
    
    if (pRet != nullptr && pRet->initWithSizeAndBackgroundSprite(size, normalSprite))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

static Rect getRect(Node * pNode)
{
    Size contentSize = pNode->getContentSize();
    Rect rect = Rect(0, 0, contentSize.width, contentSize.height);
    return RectApplyTransform(rect, pNode->getNodeToWorldTransform());
}

void ExEditBox::keyboardWillShow(IMEKeyboardNotificationInfo& info)
{
    if(_animationWhenKeyboardMoving)
    {
        EditBox::keyboardWillShow(info);
    }
    else
    {
        // CCLOG("CCEditBox::keyboardWillShow");
        Rect rectTracked = getRect(this);
        // some adjustment for margin between the keyboard and the edit box.
        rectTracked.origin.y -= 4;
        
        // if the keyboard area doesn't intersect with the tracking node area, nothing needs to be done.
        if (!rectTracked.intersectsRect(info.end))
        {
            CCLOG("needn't to adjust view layout.");
            return;
        }
        
        // assume keyboard at the bottom of screen, calculate the vertical adjustment.
        _adjustHeight = info.end.getMaxY() - rectTracked.getMinY();
        // CCLOG("CCEditBox:needAdjustVerticalPosition(%f)", _adjustHeight);
        
//        if (_editBoxImpl != nullptr)
//        {
//            _editBoxImpl->doAnimationWhenKeyboardMove(info.duration, _adjustHeight);
//        }
    }
}

void ExEditBox::keyboardDidShow(IMEKeyboardNotificationInfo& info)
{
    if(_animationWhenKeyboardMoving)
    {
        EditBox::keyboardDidShow(info);
    }
}

void ExEditBox::keyboardWillHide(IMEKeyboardNotificationInfo& info)
{
    if(_animationWhenKeyboardMoving)
    {
        EditBox::keyboardWillHide(info);
    }
}

void ExEditBox::keyboardDidHide(IMEKeyboardNotificationInfo& info)
{
    if(_animationWhenKeyboardMoving)
    {
        EditBox::keyboardDidHide(info);
    }
}

void ExEditBox::updateMaxTextLenght(float dt)
{
    // do the calcu for max text lenght here
    if(_strPreviousText.compare("") == 0)
    {
        _strPreviousText = this->getText();
    }
    else
    {
        const char* text = this->getText();
        if(_strPreviousText.compare(text) != 0)
        {
            // update
            _strPreviousText = text;
            
            // check if nothing can't not calcu
            if(_strPreviousText.size() < 20)
            {
                return;
            }
            
            float fRealWidth = 0.0f;
            
            // plit it to 10 for calcu for get exact texture
            for (int i = 0; i < 3; i++)
            {
                pLable->setString(_strPreviousText.substr(i * _strPreviousText.size() / 3, _strPreviousText.size() / 3));
                fRealWidth += pLable->getContentSize().width;
                //log("Spice %i have width %f", i, pLable->getContentSize().width);
                
                if(pLable->getContentSize().width == 0.0f)
                {
                    // set it unschedule
                    _bIsScheduleUpdateMaxText = false;
                    this->unschedule(schedule_selector(ExEditBox::updateMaxTextLenght));
                    return;
                }
                
            }
            //log("Total width %f", fRealWidth);
            
            // because it make from scale 9 sprite
            //log("Previous MaxLenght %i", this->getMaxLength());
            //log("Size per charf %f, Char count %i", (fRealWidth / (float)_strPreviousText.size()), (int)_strPreviousText.size());
            this->setMaxLength((3.0f * (float)_maxTextureSize) / (fRealWidth / (float)_strPreviousText.size()) - 10); // - 10 mean just make sure it correct
            //log("Current MaxLenght %i", this->getMaxLength());
        }
    }
}

void ExEditBox::onEnter(void)
{
    EditBox::onEnter();
    
    // init for temp value
    _bIsScheduleUpdateMaxText       = false;
    
    // check if done set maxlenght
//    if(_maxLength <= 0)
    {
        _bIsScheduleUpdateMaxText   = true;
        pLable                      = Label::create();
//        pLable->setSystemFontName(_fontName);
//        pLable->setSystemFontSize(_fontSize);
        this->addChild(pLable);
        pLable->setVisible(false);
        
        // temp
        pLable->setString("qwertyuiopasdfghjklzxcvbnm123456789/*-+~`!@#$%^&*()_=,./<>?;':");
        
        // get max texture size
        _maxTextureSize             = 0;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTextureSize);
        
        this->setMaxLength((3.0f * _maxTextureSize) / (pLable->getContentSize().width / (float)pLable->getString().size()));
        this->schedule(schedule_selector(ExEditBox::updateMaxTextLenght), 0.1f);
    }
}

void ExEditBox::onExit(void)
{
    EditBox::onExit();
    
    // check and unschedule
    if(_bIsScheduleUpdateMaxText)
    {
        this->unschedule(schedule_selector(ExEditBox::updateMaxTextLenght));
    }
}

NS_SS_END
