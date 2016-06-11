//
//  PopupDialog.h
//  GameXtension
//
//  Created by greewoo on 4/5/14.
//  Finished version 1.0 by Lam Ho on 08/04/14.
//  Use string of button instead label by Lam Ho on 20/06/14.

/*
 This class provides:
 - A simple popup dialog but you must create a ccb file with "PopupDialog" Name
 - A content string but you must create variable with "popupString" name and "Doc root var" target.
 - Ok button but you must connect Ok button with "okButton" variable, "okButtonClickListener:" selector and "Document root" target.
 */

#ifndef __GameXtension__PopupDialog__
#define __GameXtension__PopupDialog__

#include "cocos2d.h"
#include "SSMacros.h"
#include "cocosbuilder/CocosBuilder.h"
#include "Dialog.h"

NS_SS_BEGIN


class PopupDialog: public Dialog {
public:
    static Dialog* dialog();
    
    PopupDialog();
    
    virtual bool init();
    
    virtual bool onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    
    virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName);
    
    CREATE_FUNC(PopupDialog);
    
    virtual void onEnter();
    
    void onOkButtonClickListener(cocos2d::Ref* pSender, cocos2d::extension::Control::EventType ev);

    void build(const char* popupString, const char okString[]= "Ok", cocos2d::CallFunc* okCallFunc = NULL);

    cocos2d::Sprite* _statusSpr;
    cocos2d::Sprite* _iconStatusSpr;

protected:
    cocos2d::Label* _popupLabel;
    
    cocos2d::extension::ControlButton* _okButton;

    cocos2d::extension::ControlButton* _closeBtn;
    
    cocos2d::CallFunc* _okCallFunc;


};

class PopupDialogLoader: public cocosbuilder::LayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PopupDialogLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PopupDialog);
};

NS_SS_END

#endif /* defined(__GameXtension__PopupDialog__) */
