//
// QuestionDialog.cpp
// GameXtension
//
// Created by greewoo on 7/10/13.
//
//

#include "QuestionDialog.h"
#include "DialogDirector.h"
#include "CCBUtils.h"

NS_SS_BEGIN

Dialog* QuestionDialog::dialog() {
    cocosbuilder::NodeLoaderLibrary* nodeLoaderLibrary =
    cocosbuilder::NodeLoaderLibrary::getInstance();
    nodeLoaderLibrary->registerNodeLoader("QuestionDialog",
                                            QuestionDialogLoader::loader());
    return (Dialog*) CCBUtils::getInstance()->openNode("QuestionDialog");
}

QuestionDialog::QuestionDialog(): _questionLabel(NULL), _positiveCallFunc(NULL), _negativeCallFunc(NULL), _positiveButton(NULL), _negativeButton(NULL) {
    
}

QuestionDialog::~QuestionDialog() {
    
}

bool QuestionDialog::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "questionLabel", cocos2d::Label*, _questionLabel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "positiveButton", cocos2d::extension::ControlButton*, _positiveButton);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "negativeButton", cocos2d::extension::ControlButton*, _negativeButton);

    return Dialog::onAssignCCBMemberVariable(pTarget, pMemberVariableName, pNode);
}

SEL_MenuHandler QuestionDialog::onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName) {
    return Dialog::onResolveCCBCCMenuItemSelector(pTarget, pSelectorName);
}

cocos2d::extension::Control::Handler QuestionDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPositiveButtonClickListener:", QuestionDialog::onPositiveButtonClickListener);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onNegativeButtonClickListener:", QuestionDialog::onNegativeButtonClickListener);

    return Dialog::onResolveCCBCCControlSelector(pTarget, pSelectorName);
}

void QuestionDialog::onEnter() {
    Dialog::onEnter();
}

void QuestionDialog::onExit() {
    Dialog::onExit();
    
    if (_positiveCallFunc!=NULL)
        _positiveCallFunc->release();
    if (_negativeCallFunc!=NULL)
        _negativeCallFunc->release();
}

void QuestionDialog::onPositiveButtonClickListener(cocos2d::Ref* pSender, cocos2d::extension::Control::EventType ev) {
    if (_positiveCallFunc!=NULL) {
        cocos2d::log("Run action");
        //TODO: need to delay 1.1f second to wait outTransition of dialog. But there is bug if delay 1.1f
        cocos2d::Sequence* seq = cocos2d::Sequence::create(_positiveCallFunc, NULL);
        DialogDirector::getInstance()->getParentScene()->runAction(seq);
    } else {
        DialogDirector::getInstance()->end();
    }
}

void QuestionDialog::onNegativeButtonClickListener(cocos2d::Ref* pSender, cocos2d::extension::Control::EventType ev) {
    if (_negativeCallFunc!=NULL) {
        //TODO: need to delay 1.1f second to wait outTransition of dialog. But there is bug if delay 1.1f
        cocos2d::Sequence* seq = cocos2d::Sequence::create(_negativeCallFunc, NULL);
        DialogDirector::getInstance()->getParentScene()->runAction(seq);
    } else {
        DialogDirector::getInstance()->end();
    }
}

void QuestionDialog::build(const char* questionString, const char* positiveString, cocos2d::CallFunc* positiveCallFunc, const char* negativeString, cocos2d::CallFunc* negativeCallFunc) {

    _questionLabel->setString(questionString);

    _positiveButton->setTitleForState(positiveString, cocos2d::extension::Control::State::NORMAL);
    _positiveButton->setTitleForState(positiveString, cocos2d::extension::Control::State::HIGH_LIGHTED);
    _negativeButton->setTitleForState(negativeString, cocos2d::extension::Control::State::NORMAL);
    _negativeButton->setTitleForState(negativeString, cocos2d::extension::Control::State::HIGH_LIGHTED);

    if (positiveCallFunc!=NULL) {
        this->_positiveCallFunc = positiveCallFunc;
        this->_positiveCallFunc->retain();
    }
    
    if (negativeCallFunc!=NULL) {
        this->_negativeCallFunc = negativeCallFunc;
        this->_negativeCallFunc->retain();
    }
}
    
NS_SS_END
