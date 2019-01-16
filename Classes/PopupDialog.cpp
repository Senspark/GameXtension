//
//  PopupDialog.cpp
//  GameXtension
//
//  Created by greewoo on 4/5/14.
//
//

#include "PopupDialog.h"
#include "CCBUtils.h"
#include "DialogDirector.h"
#include "ExControlButton.h"

NS_SS_BEGIN

Dialog* PopupDialog::dialog() {
    cocosbuilder::NodeLoaderLibrary* nodeLoaderLibrary =
    cocosbuilder::NodeLoaderLibrary::getInstance();
    nodeLoaderLibrary->registerNodeLoader("PopupDialog",
                                            PopupDialogLoader::loader());
    return (Dialog*) CCBUtils::getInstance()->openNode("PopupDialog");
}

PopupDialog::PopupDialog(): _popupLabel(NULL), _okCallFunc(NULL), _okButton(NULL), _closeBtn(NULL), _iconStatusSpr(NULL), _statusSpr(NULL) {
    
}

bool PopupDialog::init() {
    Dialog::init();
    return true;
}

void PopupDialog::onEnter() {
    Dialog::onEnter();

    CONVERT_TO_EX_BTN("close_btn", _closeBtn, PopupDialog::onOkButtonClickListener);
}

bool PopupDialog::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "popupLabel", cocos2d::Label*, _popupLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "okButton", cocos2d::extension::ControlButton*, _okButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "closeBtn", cocos2d::extension::ControlButton*, _closeBtn);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "iconStatusSpr", cocos2d::Sprite*, _iconStatusSpr);
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "statusSpr", cocos2d::Sprite*, _statusSpr);
    return Dialog::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode);
}

cocos2d::SEL_MenuHandler PopupDialog::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName) {
    return Dialog::onResolveCCBCCMenuItemSelector(pTarget, pSelectorName);
}

cocos2d::extension::Control::Handler PopupDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onOkButtonClickListener:", PopupDialog::onOkButtonClickListener);
    return Dialog::onResolveCCBCCControlSelector(pTarget, pSelectorName);
}

void PopupDialog::onOkButtonClickListener(cocos2d::Ref* pSender, cocos2d::extension::Control::EventType ev) {
    if (_okCallFunc!=NULL) {
        this->runAction(_okCallFunc);
    } else {
        DialogDirector::getInstance()->end(cocos2d::EaseElasticIn::create(cocos2d::MoveTo::create(1, cocos2d::Point(cocos2d::Director::getInstance()->getWinSize().width/2*3,
                                                                                         cocos2d::Director::getInstance()->getWinSize().height/2)), 1.0f));
    }
}

void PopupDialog::build(const char* popupString, const char okString[], cocos2d::CallFunc* okCallFunc) {
    _popupLabel->setString(popupString);
    _popupLabel->setDimensions(getDialogNode()->getChildByTag(0)->getContentSize().width - 20, getDialogNode()->getChildByTag(0)->getContentSize().height);
    _okButton->setTitleForState(okString, cocos2d::extension::Control::State::NORMAL);
    _okButton->setTitleForState(okString, cocos2d::extension::Control::State::HIGH_LIGHTED);
    if (okCallFunc!=NULL) {
        this->_okCallFunc = okCallFunc;
        this->_okCallFunc->retain();
    }
}

NS_SS_END
