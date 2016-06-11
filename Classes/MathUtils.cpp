//
//  MathUtils.cpp
//  GameXtension
//
//  Created by greewoo on 2/28/14.
//
//

#include "MathUtils.h"
#include <math.h>

NS_SS_BEGIN

bool MathUtils::ccw(cocos2d::Vec2 A, cocos2d::Vec2 B, cocos2d::Vec2 C) {
    return (C.y-A.y)*(B.x-A.x) > (B.y-A.y)*(C.x-A.x);
}

/* Changes from header:
    - A is A1
    - B is B1
    - C is A2
    - D is B2
 */
bool MathUtils::linesInterect(cocos2d::Vec2 A, cocos2d::Vec2 B, cocos2d::Vec2 C, cocos2d::Vec2 D) {
    return ccw(A,C,D) != ccw(B,C,D) && ccw(A,B,C) != ccw(A,B,D);
}

bool MathUtils::polygonsIntersect(std::vector<cocos2d::Point>& poly1,
                                  std::vector<cocos2d::Point>&  poly2)
{
    for (int i=0; i<poly1.size(); i++) {
        int i1=i+1;
        if (i==poly1.size()-1) {
            i1=0;
        }
        
        cocos2d::Vec2 a1 = poly1[i];
        cocos2d::Vec2 a2 = poly1[i1];
        
        for (int j=0; j<poly2.size(); j++) {
            int j1=j+1;
            if (j==poly2.size()-1) {
                j1=0;
            }
            cocos2d::Vec2 b1 = poly2[j];
            cocos2d::Vec2 b2 = poly2[j1];
            if (linesInterect(a1, a2, b1, b2)) {
                return true;
            }
        }
    }
    return false;
}

NS_SS_END
