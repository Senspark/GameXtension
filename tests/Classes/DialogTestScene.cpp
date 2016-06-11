//
//  DialogTest.cpp
//  senspark-test
//
//  Created by greewoo on 4/4/14.
//
//

#include "DialogTestScene.h"
#include "AppMacros.h"
#include "DialogDirector.h"
#include "QuestionDialog.h"
#include "AppMacros.h"
#include "PopupDialog.h"
#include "SimpleAudioEngine.h"
#include "TestSoundDialog.h"

static std::function<Layer*()> createFunctions[] = {
    CL(DialogPopup),
    CL(DialogQuestion),
    CL(DialogReplace),
    CL(DialogTransition),
    CL(DialogNotification),
    CL(DialogSound),
};

static int sceneIdx=-1;
#define MAX_LAYER (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    Layer* pLayer = (createFunctions[sceneIdx])();
   
    return pLayer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    Layer* pLayer = (createFunctions[sceneIdx])();
   
    return pLayer;
}

static Layer* restartAction()
{
    Layer* pLayer = (createFunctions[sceneIdx])();
   
    return pLayer;
}

void DialogTestScene::onEnter() {
    TestScene::onEnter();
}

void DialogTestScene::runThisTest() {
    FileFuncLog("..checked");
    sceneIdx = -1;
    addChild(nextAction());
    
    Director::getInstance()->replaceScene(this);
}

void DialogDemo::onEnter() {
    BaseTest::onEnter();
    
    
    senspark::DialogDirector::getInstance()->setParentScene(this);
    
    winSize = Director::getInstance()->getWinSize();
}

void DialogDemo::onExit() {
    BaseTest::onExit();
}

std::string DialogDemo::title() const {
    return "DialogTest";
}

std::string DialogDemo::subtitle() const {
    return "";
}

void DialogDemo::restartCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new DialogTestScene();
    s->addChild( restartAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void DialogDemo::nextCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new DialogTestScene();
    s->addChild( nextAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void DialogDemo::backCallback(Ref* pSender) {
    FileFuncLog("..checked");
    Scene* s = new DialogTestScene();
    s->addChild( backAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void DialogPopup::onEnter() {
    DialogDemo::onEnter();
    
    PopupDialog* dialog = (PopupDialog*) PopupDialog::dialog();
    dialog->build("Test popup dialog", "Ok", CallFunc::create(CC_CALLBACK_0(DialogPopup::okCallFunc, this)));
    senspark::DialogDirector::getInstance()->runWithDialog(dialog);
}

void DialogPopup::okCallFunc() {
    log("Called okCallFunc");
    DialogDirector::getInstance()->end();
}

std::string DialogPopup::subtitle() const {
    return "PopupDialog";
}

void DialogQuestion::onEnter() {
    DialogDemo::onEnter();    
    
    senspark::QuestionDialog* dialog =(senspark::QuestionDialog*) senspark::QuestionDialog::dialog();
    dialog->build("See this question dialog?","Yes", CallFunc::create(CC_CALLBACK_0(DialogQuestion::onYesCallFunc, this)), "No", NULL);
    senspark::DialogDirector::getInstance()->runWithDialog(dialog);
}

std::string DialogQuestion::subtitle() const {
    return "QuestionDialog";
}

void DialogQuestion::onYesCallFunc() {
    DialogDirector::getInstance()->end();
}

void DialogReplace::onEnter() {
    DialogDemo::onEnter();
    senspark::QuestionDialog* dialog = (senspark::QuestionDialog*) senspark::QuestionDialog::dialog();
    dialog->build("Replace this dialog?", "Yes", CallFunc::create(CC_CALLBACK_0(DialogReplace::onYesCallFunc, this)));
    senspark::DialogDirector::getInstance()->runWithDialog(dialog);
}

std::string DialogReplace::subtitle() const {
    return "ReplaceDialog";
}

void DialogReplace::onYesCallFunc() {
    senspark::Dialog* dialog = PopupDialog::dialog();
    senspark::DialogDirector::getInstance()->replaceWithDialog(dialog);
}

void DialogTransition::onEnter() {
    DialogDemo::onEnter();
    
    // create question dialog
    
    senspark::QuestionDialog* dialog = (senspark::QuestionDialog*) senspark::QuestionDialog::dialog();
    dialog->build("Pass to another dialog?", "Ok", CallFunc::create(CC_CALLBACK_0(DialogTransition::onPositiveCallFunc, this, new Value(0))) ,
                                             "Cancel", CallFunc::create(CC_CALLBACK_0(DialogTransition::onCloseCallFunc, this)) );
    // set new dialog original position
    dialog->getDialogNode()->setPosition(Vec2(-winSize.width/2, winSize.height/2));
    
    // create custom showing transition
    MoveTo* move_in =  MoveTo::create(1, Vec2(winSize.width/2, winSize.height/2));
    ActionInterval* move_ease_out = EaseBounceOut::create((ActionInterval*)(move_in->clone()) );
    
    senspark::DialogDirector::getInstance()->runWithDialog(dialog, move_ease_out);
}

std::string DialogTransition::subtitle() const {
    return "Transition";
}

void DialogTransition::onCloseCallFunc() {
    MoveTo* move_out =  MoveTo::create(1, Vec2(winSize.width/2, 3*winSize.height/2));
    ActionInterval* move_ease_in = EaseBounceIn::create((ActionInterval*)(move_out->clone()) );
    senspark::DialogDirector::getInstance()->end(move_ease_in);
}

void DialogTransition::onPositiveCallFunc(Value* data) {
    
    // first dialog yes call func
    if (data->asInt()==0) {
        // create popup dialog
        senspark::PopupDialog* dialog =(senspark::PopupDialog*) senspark::PopupDialog::dialog();
        dialog->build("Finish transition test?","Ok", CallFunc::create(CC_CALLBACK_0(DialogTransition::onPositiveCallFunc, this, new Value(1))));
        //dialog->setCloseCallFunc(CCCallFuncO::create(this, callfuncO_selector(DialogTransition::onCloseCallFunc), NULL)); // TODO:
        // set dialog original position
        dialog->getDialogNode()->setPosition(Vec2(-winSize.width/2, winSize.height/2));
        
        // create custom showing transition
        MoveTo* move_out =  MoveTo::create(1, Vec2(winSize.width/2, 3*winSize.height/2));
        ActionInterval* move_ease_in = EaseBounceIn::create((ActionInterval*)(move_out->clone()) );
        
        // create custom hiding transition
        MoveTo* move_in =  MoveTo::create(1, Vec2(winSize.width/2, winSize.height/2));
        ActionInterval* move_ease_out = EaseBounceOut::create((ActionInterval*)(move_in->clone()) );
        
        senspark::DialogDirector::getInstance()->replaceWithDialog(dialog, move_ease_in, move_ease_out);
    } else { // second dialog ok call func
        MoveTo* move_out =  MoveTo::create(1, Vec2(winSize.width/2, 3*winSize.height/2));
        ActionInterval* move_ease_in = EaseBounceIn::create((ActionInterval*)(move_out->clone()) );
        
        DialogDirector::getInstance()->end(move_ease_in);
    }
}

void DialogNotification::onEnter() {
    DialogDemo::onEnter();
    getEventDispatcher()->addCustomEventListener(SHOW_DIALOG_EVENT, CC_CALLBACK_1(DialogNotification::receiveShowDialogEvent, this));
    getEventDispatcher()->addCustomEventListener(HIDE_DIALOG_EVENT, CC_CALLBACK_1(DialogNotification::receiveShowDialogEvent, this));
    
    senspark::PopupDialog* dialog = (senspark::PopupDialog*) (PopupDialog::dialog());
    dialog->build("See console");
    
    senspark::DialogDirector::getInstance()->runWithDialog(dialog);
}

void DialogNotification::onExit() {
    DialogDemo::onExit();
    getEventDispatcher()->removeCustomEventListeners(SHOW_DIALOG_EVENT);
    getEventDispatcher()->removeCustomEventListeners(HIDE_DIALOG_EVENT);
}

void DialogNotification::receiveShowDialogEvent(EventCustom* data) {
    log("called receiveShowDialogEvent");
}

void DialogNotification::receiveHideDialogEvent(EventCustom* data) {
    log("called receiveHideDialogEvent");
}

std::string DialogNotification::subtitle() const {
    return "Notification";
}

void DialogSound::onEnter() {
    DialogDemo::onEnter();
    
    // play a sample effect
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("effect.mp3", false);
    
    // Delay 1 second to play sound then call runWithDialog
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(1), CallFunc::create(CC_CALLBACK_0(DialogSound::delayedCallFunc, this))));
}

void DialogSound::delayedCallFunc() {
   senspark::DialogDirector::getInstance()->runWithDialog(TestSoundDialog::dialog());
}

std::string DialogSound::subtitle() const {
    return "Sound";
}


