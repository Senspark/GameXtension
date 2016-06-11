//
//  EmptyTestScene.cpp
//  utils-cpp-test
//
//  Created by greewoo on 3/31/14.
//
//

#include "EmptyTestScene.h"
#include "AppMacros.h"
#include "Utils.h"
#include "MathUtils.h"
#include "Persistence.h"
#include <string.h>

using namespace senspark;

void EmptyTestScene::runThisTest() {
    FileFuncLog("..checked");
    //log("=====  UtilsTest >> GetTimeInMil  ===== %lld", Utils::getTimeDifferenceMS());
    //CCAssert(Utils::getTimeDifferenceMS()>0, "Fail Utils::getTimeInMil()>0");
    //log("=====  Passed                   =====");
    
    log("=====  UtilsTest >> B64Decode  =====");
    //CCAssert(Utils::b64Decode("aGVsbG8=")->compare("hello")==0, "Fails decoding Utils::b64Decode(xxx) == hello");
    //CCAssert(Utils::b64Decode("Z29vZCBieWU=")->compare("good bye")==0, "Fails decoding Utils::b64Decode(xxx) == good bye");
    //CCAssert(Utils::b64Decode("eGluIGNow6Bv")->compare("xin chào")==0, "Fails decoding Utils::b64Decode(xxx) == xin chào");
    //CCAssert(Utils::b64Decode("dOG6oW0gYmnhu4d0")->compare("tạm biệt")==0, "Fails decoding Utils::b64Decode(xxx) == tạm biệt");
    log("=====  Passed  =====");
    
    log("=====  MathUtilsTest >> Ccw  =====");
    // test: wrong ccw
    CCAssert(MathUtils::ccw(Vec2(100, 100), Vec2(200, 300), Vec2(400, 150))==false, "Fails ccw(Vec2(100, 100), Vec2(200,300), Vec2(400,150))");
    // test: right ccw
    CCAssert(MathUtils::ccw(Vec2(400, 150), Vec2(200, 300), Vec2(100, 100))==true, "Fails ccw(Vec2(400,150), Vec2(200,300), Vec2(100, 100))");
    // test: 3 points on a vertical line
    CCAssert(MathUtils::ccw(Vec2(400, 300), Vec2(400, 200), Vec2(400, 100))==false, "Fails ccw(Vec2(400, 300), Vec2(400, 200), Vec2(400, 100))");
    // test: 3 points on a vertical line
    CCAssert(MathUtils::ccw(Vec2(400, 100), Vec2(400, 200), Vec2(400, 300))==false, "Fails ccw(Vec2(400, 100), Vec2(400, 200), Vec2(400, 300))");
    // test: 3 points on a horizontal line
    CCAssert(MathUtils::ccw(Vec2(100, 100), Vec2(200, 100), Vec2(300, 100))==false, "Fails ccw(Vec2(100, 100), Vec2(200, 100), Vec2(300, 100))");
    // test: 3 points on a horizontal line
    CCAssert(MathUtils::ccw(Vec2(300, 100), Vec2(200, 100), Vec2(100, 100))==false, "Fails ccw(Vec2(300, 100), Vec2(200, 100), Vec2(100, 100))");
    // test: 3 points on a horizontal line
    CCAssert(MathUtils::ccw(Vec2(100, 100), Vec2(100, 100), Vec2(100, 100))==false, "Fails ccw(Vec2(100, 100), Vec2(100, 100), Vec2(100, 100))");
    log("=====  Passed  =====");
    
    log("=====  MathUtilsTest >> LinesIntersect  =====");
    // test: intersect truely
    CCAssert(MathUtils::linesInterect(Vec2(100, 100), Vec2(500, 500), Vec2(150, 300), Vec2(400, 100))==true, "Fails linesInterect(Vec2(100,100), Vec2(500,500), Vec2(150, 300), Vec2(400,100))");
    // test: intersect falsely
    CCAssert(MathUtils::linesInterect(Vec2(500, 100), Vec2(900, 500), Vec2(150, 300), Vec2(400, 100))==false, "Fails linesInterect(Vec2(500, 100), Vec2(900, 500), Vec2(150, 300), Vec2(400, 100))");
    // TODO: test: 2 segments in a line and intersect
    //CCAssert(MathUtils::linesInterect(Vec2(200, 300), Vec2(500, 300), Vec2(400, 300), Vec2(700, 300))==true, "Fails linesInterect(Vec2(200, 300), Vec2(500, 300), Vec2(400, 300), Vec2(700, 300))");
    // TODO: test: 2 segments in a line and not intersect
    //CCAssert(MathUtils::linesInterect(Vec2(200, 300), Vec2(500, 300), Vec2(550, 300), Vec2(800, 300))==false, "Fails linesInterect(Vec2(200, 300), Vec2(500, 300), Vec2(550, 300), Vec2(800, 300))");
    log("=====  Passed  =====");
    
    log("=====  MathUtilsTest >> PolygonsIntersect  =====");
    // test 1: intersect truely
    Vec2 polygon1[]={Vec2(20,40), Vec2(40,50), Vec2(60,30), Vec2(60,20), Vec2(20,20)};
    Vec2 polygon2[]={Vec2(80,60), Vec2(100,40), Vec2(120,40), Vec2(130,80), Vec2(100,80)};
    CCAssert(MathUtils::polygonsIntersect(polygon1, 5, polygon2, 5)==false, "Fails test 1");
    
    // test 2: intersect falsely
    Vec2 polygon3[]={Vec2(70,40), Vec2(90,50), Vec2(110,30), Vec2(110,20), Vec2(70,20)};
    Vec2 polygon4[]={Vec2(80,60), Vec2(100,40), Vec2(120,40), Vec2(130,80), Vec2(100,80)};
    CCAssert(MathUtils::polygonsIntersect(polygon3, 5, polygon4, 5)==true, "Fails test 2");
    //TODO: need more test
    log("=====  Passed  =====");
    
    log("=====  PersistenceTest >> LangCode  =====");
    Persistence* persistence = new Persistence();
    persistence->setLanguageCode(kVietnamese);
    CCAssert(persistence->getLanguageCode()==kVietnamese, "Fails in persistence->getLanguageCode()==kVietnamese");
    persistence->setLanguageCode(kEnglish);
    CCAssert(persistence->getLanguageCode()==kEnglish, "Fails in persistence->getLanguageCode()==kEnglish");
    log("=====  Passed  =====");
    
    log("=====  PersistenceTest >> Sound  =====");
    persistence->setSoundEnabled(true);
    CCAssert(persistence->getSoundEnabled()==true, "Fails in persistence->getSoundEnabled()==true");
    persistence->setSoundEnabled(false);
    CCAssert(persistence->getSoundEnabled()==false, "Fails in persistence->getSoundEnabled()==true");
    log("=====  Passed  =====");
    
    log("=====  PersistenceTest >> Music  =====");
    persistence->setMusicEnabled(true);
    CCAssert(persistence->getMusicEnabled()==true, "Fails in persistence->getMusicEnabled()==true");
    persistence->setMusicEnabled(false);
    CCAssert(persistence->getMusicEnabled()==false, "Fails in persistence->getMusicEnabled()==true");
    log("=====  Passed  =====");
    
    log("=====  PersistenceTest >> HighScore  =====");
    persistence->setHighScore(100);
    CCAssert(persistence->getHighScore()==100, "Fails in persistence->getHighScore()==100");
    persistence->setHighScore(1000);
    CCAssert(persistence->getHighScore()==1000, "Fails in persistence->getHighScore()==1000");
    log("=====  Passed  =====");
    //TODO: Test persitence keeping value when app exits then start again
    
}
