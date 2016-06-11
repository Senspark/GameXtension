//
// QuestionDialog.h
// GameXtension
//
// Created by greewoo on 7/10/13.
// Finished version 1.0 by Lam Ho on 08/04/14.
// Use string of button instead label by Lam Ho on 20/06/14.

/*
 This class provides:
 - Question dialog but you must create a ccb file for Question Dialog with name "QuestionDialog"
 - Positive button and positiveCallFunc to handle yes event. Connect Positive button with "positiveButton" variable, "onPositiveButtonClickListener" selector and "Document root" target. You must call DialogDirector::sharedDirector()->end() to close dialog if possitiveCallFunc!=NULL
 - Negative button and negativeCallFunc to handle no event. Connect Negative button with "negativeButton" variable, "onNegativeButtonClickListener" selector and "Document root" target. You must call DialogDirector::sharedDirector()->end() to close dialog if negativeCallFunc!=NULL
 - Set question string for dialog. You must create a label and bind "questionLabel" variable with "Doc root var" target.
 */

#ifndef __GameXtension__QuestionDialog__
#define __GameXtension__QuestionDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "SSMacros.h"
#include "Dialog.h"
#include "cocosbuilder/CocosBuilder.h"

USING_NS_CC;
USING_NS_CC_EXT;

NS_SS_BEGIN

class QuestionDialog: public Dialog {
public:
    CREATE_FUNC(QuestionDialog);
    
    static Dialog* dialog();
    
    QuestionDialog();
    
    virtual ~QuestionDialog();
    
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref* pTarget, const char* pSelectorName);
    
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    
    virtual void onEnter();
    
    virtual void onExit();
    
    void onPositiveButtonClickListener(cocos2d::Ref*, cocos2d::extension::Control::EventType ev);
    
    void onNegativeButtonClickListener(cocos2d::Ref*, cocos2d::extension::Control::EventType ev);
    
    /*
        Build a question dialog.
        - questionString is the question string.
        - positiveString is string for positive menu.
        - positiveCallFunc will be called when pressing positive menu.
        - negativeString is string for negative menu.
        - negativeCallFunc will be called when pressing positive menu.
     */
    void build(const char* questionString, const char positiveString[]="Yes", cocos2d::CallFunc* positiveCallFunc=NULL, const char negativeString[]="No",  cocos2d::CallFunc* negativeCallFunc=NULL);
    
protected:
    cocos2d::Label* _questionLabel;
    
    cocos2d::CallFunc* _positiveCallFunc;
    
    cocos2d::CallFunc* _negativeCallFunc;

    cocos2d::extension::ControlButton* _positiveButton;

    cocos2d::extension::ControlButton* _negativeButton;
};

NS_SS_END

class QuestionDialogLoader: public cocosbuilder::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(QuestionDialogLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(senspark::QuestionDialog);
};


#endif
