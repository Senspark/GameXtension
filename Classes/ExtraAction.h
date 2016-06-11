//
//  ExtraAction.h
//  senspark-game-foundation
//
//  Created by greewoo on 5/3/14.
//
//

#ifndef __senspark_game_foundation__ExtraAction__
#define __senspark_game_foundation__ExtraAction__

#include "cocos2d.h"
#include "SSMacros.h"
#include "GameAction.h"

NS_SS_BEGIN

// Extra action for making a GameSequence or CCSpawn when only adding one action to it.
class ExtraAction : public GameAction
{
public:
    static ExtraAction* create();
    virtual ExtraAction* clone() const override;
    virtual ExtraAction* reverse(void) const override;
    virtual bool isDone() const override;
};

NS_SS_END

#endif /* defined(__senspark_game_foundation__ExtraAction__) */
