//
//  MathUtils.h
//  GameXtension
//
//  Created by greewoo on 2/28/14.
// Finished version 1.0 by Lam Ho on 08/04/14.
//

#ifndef __GameXtension__MathUtils__
#define __GameXtension__MathUtils__

#include "cocos2d.h"
#include "SSMacros.h"

NS_SS_BEGIN

class MathUtils: public cocos2d::Ref {
    
public:
    /* Check three points A, B, C that is counter clockwise. */
    static bool ccw(cocos2d::Vec2 A, cocos2d::Vec2 B, cocos2d::Vec2 C);
    
    /* Check the segment A1, B1 and the segment A2, B2 that intersect each other. */
    static bool linesInterect(cocos2d::Vec2 A1, cocos2d::Vec2 B1, cocos2d::Vec2 A2, cocos2d::Vec2 B2);
    
    /*  Check the poly1 polygon intersects the poly2 polygon
     */
    static bool polygonsIntersect(std::vector<cocos2d::Point>& poly1, std::vector<cocos2d::Point>&  poly2);
    
};
    
NS_SS_END

#endif /* defined(__GameXtension__MathUtils__) */
