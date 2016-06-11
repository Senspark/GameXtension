//
// DialogDirector.h
// GameXtension
//
// Created by greewoo on 7/3/13.
// Finished version 1.0 by Lam Ho on 08/04/14.
//

/* DialogDirector provides:
 - Run a dialog with showing transition
 - Replace a running dialog with showing transition by new dialog with hiding transition
 - End a dialog with hiding transition
 - Support the default transition
 - Set current design size to dialog director
 - Get current dialog
 */

#ifndef __GameXtension__DialogDirector__
#define __GameXtension__DialogDirector__

#include "cocos2d.h"
#include "Dialog.h"
#include "SSMacros.h"
#include <stack>
#include <unordered_map>

NS_SS_BEGIN

class DialogDirector: public cocos2d::Ref {
    
public:
    static DialogDirector* getInstance();
    
    DialogDirector();
    
    virtual ~DialogDirector();
    
    /* Run a dialog with showing transition
     - dialog is a dialog needed to run
     - inTrasition is showing transition
     */
    void runWithDialog(Dialog* dialog, cocos2d::FiniteTimeAction* inTransition=NULL);
    
    /* Replace a running dialog with showing transition by new dialog with hiding transition
     - dialog is a new dialog replaces current one
     - outTransition is current hiding transition
     - inTransition is new showing transition
     */
    void replaceWithDialog(Dialog* dialog, cocos2d::FiniteTimeAction* outTransition = NULL, cocos2d::FiniteTimeAction* inTransition = NULL);
    
    /* End a dialog with hiding transition
     - outTransition is hiding transition
     */
    void end(cocos2d::FiniteTimeAction* outTransition=NULL);
    
    // Set parentScene that contains dialog
    void setParentScene(cocos2d::Layer* parentScene);
    
    // Get parentScene that contains dialog
    cocos2d::Layer* getParentScene();
    
    //Get current dialog
    Dialog* getCurrentDialog();
    
    /**
     Clear current dialogs
     */
    void clear();

protected:
    
    void removeDialog();
    
    void addDialog(Dialog* dialog, cocos2d::FiniteTimeAction* inTransition, cocos2d::Value v);
    

    
protected:
    cocos2d::Layer* _parentScene;
    std::stack<Dialog*> _dialogStack;
    static DialogDirector* _instance;
};
    
NS_SS_END

#endif /* defined(__GameXtension__DialogDirector__) */
