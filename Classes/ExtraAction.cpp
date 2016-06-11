//
//  ExtraAction.cpp
//  senspark-game-foundation
//
//  Created by greewoo on 5/3/14.
//
//

#include "ExtraAction.h"

NS_SS_BEGIN

ExtraAction* ExtraAction::create()
{
    ExtraAction* pRet = new ExtraAction();
    if (pRet)
    {
        pRet->autorelease();
    }
    return pRet;
}

ExtraAction* ExtraAction::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) ExtraAction();
    a->autorelease();
    return a;
}

ExtraAction* ExtraAction::reverse(void) const
{
    return ExtraAction::create();
}

bool ExtraAction::isDone() const {
    return true;
}

NS_SS_END
