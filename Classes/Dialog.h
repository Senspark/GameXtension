//
// Dialog.h
// GameXtension
//
// Created by greewoo on 7/2/13.
// Finished version 1.0 by Lam Ho on 08/04/14.
// Use string of button instead label by Lam Ho on 20/06/14.

/*
 Base dialog class provides:
 - DialogNode contains all dialog items. You must create a CCNode in ccb file bind with "dialogNode" variable name and "Doc root var" target.
 - Close button and already handled close event. You must create close button with "onCloseButtonClickListener" selector and "Doc root" target.
 - Disable touch from the parent scene when showing
 - Enable touch for parent scene when hiding
 - Post a notification SHOW_DIALOG_NOTIFICATION when it's in onEnter
 - Post a notificaiton HIDE_DIALOG_NOTIFICATION when it's in onExit
 */

#ifndef __GameXtension__Dialog__
#define __GameXtension__Dialog__

#include "SSMacros.h"
#include "cocos2d.h"
#include "cocosbuilder/CocosBuilder.h"

NS_SS_BEGIN

#define SHOW_DIALOG_EVENT "senspark-show-event"

#define HIDE_DIALOG_EVENT "senspark-hide-event"

class DialogDirector;

class Dialog: public cocos2d::Layer,  public cocosbuilder::CCBMemberVariableAssigner, public cocosbuilder::CCBSelectorResolver  {
    
public:
    Dialog();
    
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref* target, const char* memberVariableName, cocos2d::Node* node);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref *target, const char* selectorName);
    
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * target, const char* selectorName);
    
    virtual void onEnter();
    
    virtual void onExit();
    
    virtual void onCloseButtonClickListener(cocos2d::Ref *pSender, cocos2d::extension::Control::EventType ev);
    
    // Get the dialog node contains the dialog items. This dialogNode is binded by "dialogNode" name select type "doc root var" in CocosBuilder
    CC_SYNTHESIZE(cocos2d::Node*, _dialogNode, DialogNode);

    // get/set out transition
    void setCloseCallFunc(cocos2d::CallFunc* closeCallFunc);
    
protected:
    // call this in onEnter of custom dialog if you want to pause parent actions and sound
    void pauseParentScene();
    
    // call this in onExit of custom dialog if you want to resume parent actions and sound
    void resumeParentScene();
    
private:
    void disableTouchParentScene();
    
    void enableTouchParentScene();
    
    cocos2d::CallFunc* _closeCallFunc;

    DialogDirector* _dialogDirector;

    cocos2d::Ref* _parentScene;

    cocos2d::EventListenerTouchOneByOne* _touchListener;
};

NS_SS_END

#endif /* defined(__GameXtension__Dialog__) */
