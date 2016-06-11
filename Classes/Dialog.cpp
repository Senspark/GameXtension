//
// Dialog.cpp
// GameXtension
//
// Created by greewoo on 7/2/13.
//
//

#include "Dialog.h"
#include "DialogDirector.h"
#include "SimpleAudioEngine.h"
#include "Utils.h"

NS_SS_BEGIN

Dialog::Dialog() : _dialogNode(NULL), _closeCallFunc(NULL) {
    
}

bool Dialog::onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE_WEAK(this, "dialogNode", cocos2d::Node*, _dialogNode);
    return false;
}

cocos2d::SEL_MenuHandler Dialog::onResolveCCBCCMenuItemSelector(cocos2d::Ref* pTarget, const char* pSelectorName) {
    return NULL;
}

cocos2d::extension::Control::Handler Dialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCloseButtonClickListener:", Dialog::onCloseButtonClickListener);
    return NULL;
}

void Dialog::onEnter() {
    cocos2d::Layer::onEnter();
    _dialogDirector = DialogDirector::getInstance();
    _parentScene = _dialogDirector->getParentScene();

    _touchListener = cocos2d::EventListenerTouchOneByOne::create();
    _touchListener->retain();
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = [=] (cocos2d::Touch* touch, cocos2d::Event* event) {
        return true;
    };
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);

    getEventDispatcher()->dispatchCustomEvent(SHOW_DIALOG_EVENT, _parentScene);

    pauseParentScene();

    CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void Dialog::onExit() {
    getEventDispatcher()->dispatchCustomEvent(HIDE_DIALOG_EVENT, _parentScene);
    getEventDispatcher()->removeEventListener(_touchListener);
    CC_SAFE_RELEASE(_touchListener);

    resumeParentScene();

    CocosDenshion::SimpleAudioEngine::getInstance()->resumeAllEffects();

    cocos2d::Layer::onExit();
}

void Dialog::setCloseCallFunc(cocos2d::CallFunc* closeCallFunc) {
    _closeCallFunc = closeCallFunc;
    _closeCallFunc->retain();
}

void Dialog::onCloseButtonClickListener(cocos2d::Ref *pSender, cocos2d::extension::Control::EventType ev) {
    if (_closeCallFunc==NULL) {
        DialogDirector::getInstance()->end();
    } else {
        DialogDirector::getInstance()->getParentScene()->runAction(_closeCallFunc);
    }
}

void Dialog::pauseParentScene() {
    cocos2d::Vector<cocos2d::Node*> allChildren = Utils::getChildrenRecursively(getParent(), this);
    for (int i=0; i<allChildren.size(); i++)
    {
        cocos2d::Node *node = allChildren.at(i);
        if (node!=NULL) {
            cocos2d::Director::getInstance()->getScheduler()->pauseTarget(node);
            cocos2d::Director::getInstance()->getActionManager()->pauseTarget(node);
        }
    }
}

void Dialog::resumeParentScene() {
    cocos2d::Vector<cocos2d::Node*> allChildren = Utils::getChildrenRecursively(getParent(), this);
    for (int i=0; i<allChildren.size(); i++)
    {
        cocos2d::Node *node = allChildren.at(i);
        if (node!=NULL) {
            cocos2d::Director::getInstance()->getScheduler()->resumeTarget(node);
            cocos2d::Director::getInstance()->getActionManager()->resumeTarget(node);
        }
    }
}

void Dialog::disableTouchParentScene() {
    cocos2d::Vector<cocos2d::Node*> allChildren = Utils::getChildrenRecursively(getParent(), this);
    for (int i=0; i<allChildren.size(); i++) {
        cocos2d::Node* child = allChildren.at(i);
        if (dynamic_cast<cocos2d::Layer*>(child))
        {
            getEventDispatcher()->pauseEventListenersForTarget(child);
        }
    }
}

void Dialog::enableTouchParentScene() {
    cocos2d::Vector<cocos2d::Node*> allChildren = Utils::getChildrenRecursively(getParent(), this);
    for (int i=0; i<allChildren.size(); i++) {
        cocos2d::Node* child = allChildren.at(i);
        if (dynamic_cast<cocos2d::Layer*>(child))
        {
            getEventDispatcher()->resumeEventListenersForTarget(child);
        }
    }

}
    
NS_SS_END
