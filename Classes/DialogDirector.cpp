//
// DialogDirector.cpp
// GameXtension
//
// Created by greewoo on 7/3/13.
//
//

#include "DialogDirector.h"

NS_SS_BEGIN

DialogDirector* DialogDirector::_instance = NULL;

DialogDirector* DialogDirector::getInstance() {
	if (_instance == NULL) {
		_instance = new DialogDirector();
	}
	return _instance;
}

DialogDirector::DialogDirector() {
}

DialogDirector::~DialogDirector() {
}

void DialogDirector::runWithDialog(Dialog *dialog,
                                   cocos2d::FiniteTimeAction* inTransition) {
    addDialog(dialog, inTransition, cocos2d::Value(0));
}

void DialogDirector::end(cocos2d::FiniteTimeAction* outTransition) {
	if (outTransition != NULL) {
        cocos2d::Sequence* seq = cocos2d::Sequence::create(outTransition,
                                                           cocos2d::CallFunc::create(CC_CALLBACK_0(DialogDirector::removeDialog, this)), NULL);
		_dialogStack.top()->getDialogNode()->runAction(seq);
	} else {
		removeDialog();
	}
}

void DialogDirector::replaceWithDialog(Dialog* dialog,
                                       cocos2d::FiniteTimeAction* outTransition, cocos2d::FiniteTimeAction* inTransition) {
    std::unordered_map<std::string, cocos2d::Ref*> dict;
	if (outTransition != NULL) {
        if (inTransition != NULL) {
            inTransition->retain();
        }
        cocos2d::Sequence* seq = cocos2d::Sequence::create(outTransition,
                                                           cocos2d::CallFunc::create(CC_CALLBACK_0(DialogDirector::removeDialog, this)),
                                                           cocos2d::CallFunc::create(CC_CALLBACK_0(DialogDirector::addDialog, this, dialog, inTransition, cocos2d::Value(1))),
                                                           NULL);
		_dialogStack.top()->getDialogNode()->runAction(seq);
	} else {
		removeDialog();
        addDialog(dialog, inTransition, cocos2d::Value(0));
	}
}

void DialogDirector::removeDialog() {
    _parentScene->removeChild(_dialogStack.top());
    _dialogStack.pop();
}

void DialogDirector::addDialog(Dialog* dialog, cocos2d::FiniteTimeAction* inTransition, cocos2d::Value v) {
    _dialogStack.push(dialog);

	_parentScene->addChild(_dialogStack.top(), 1000);
    
	if (inTransition != NULL)
		dialog->getDialogNode()->runAction(inTransition);
    if (v.asInt()==1) {
        CC_SAFE_RELEASE(inTransition);
    }
}

Dialog* DialogDirector::getCurrentDialog() {
    if (_dialogStack.size()>0) {
        return _dialogStack.top();
    } else {
        return NULL;
    }
}

void DialogDirector::clear() {
    while ( ! _dialogStack.empty() )
    {
        _dialogStack.pop();
    }
}

void DialogDirector::setParentScene(cocos2d::Layer* parentScene) {
    this->_parentScene = parentScene;
    clear();
}

// Get parentScene that contains dialog
cocos2d::Layer* DialogDirector::getParentScene() {
    return _parentScene;
}

NS_SS_END
