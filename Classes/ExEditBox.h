//
//  ExEditBox.h
//  senspark-game-foundation
//
//  Created by HuyPhan on 12/1/14.
//
//

#ifndef __senspark_game_foundation__ExEditBox__
#define __senspark_game_foundation__ExEditBox__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "SSMacros.h"

//USING_NS_CC;
USING_NS_CC_EXT;
//using namespace std;

NS_SS_BEGIN

class ExEditBox : public cocos2d::ui::EditBox
{
public:
    
    ExEditBox();
    
    /**
     * create a edit box with size.
     * @return An autorelease pointer of ExEditBox, you don't need to release it only if you retain it again.
     */
    static ExEditBox* create(const cocos2d::Size& size,
                             cocos2d::ui::Scale9Sprite* normalSprite,
                             cocos2d::ui::Scale9Sprite* pressedSprite = nullptr,
                             cocos2d::ui::Scale9Sprite* disabledSprite = nullptr);
    
    // check for max text lenght
    void updateMaxTextLenght(float dt);
    
    // over  it for run the update
    virtual void onEnter(void) override;
    
    // exit schedule updateMaxTextLenght
    virtual void onExit(void) override;
    
    /**
     * @js NA
     * @lua NA
     */
    virtual void keyboardWillShow(cocos2d::IMEKeyboardNotificationInfo& info) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void keyboardDidShow(cocos2d::IMEKeyboardNotificationInfo& info) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void keyboardWillHide(cocos2d::IMEKeyboardNotificationInfo& info) override;
    /**
     * @js NA
     * @lua NA
     */
    virtual void keyboardDidHide(cocos2d::IMEKeyboardNotificationInfo& info) override;
    
protected:
    
    // flag for show do animation for key board moving
    CC_SYNTHESIZE(bool, _animationWhenKeyboardMoving, EnableAnimationWhenKeyboardMoving);
    
    // check for call update func
    bool _bIsScheduleUpdateMaxText;
    
    // previous text
    std::string _strPreviousText;
    
    // max texture size
    GLint _maxTextureSize;
    
    cocos2d::Label* pLable;
};

NS_SS_END

#endif /* defined(__DemoUI__ExEditBox__) */
