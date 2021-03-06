//
//  ExTabView.h
//  senspark-game-foundation
//
//  Created by HuyPhan on 11/24/14.
//
//

#ifndef __senspark_game_foundation__ExTabView__
#define __senspark_game_foundation__ExTabView__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "SSMacros.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

NS_SS_BEGIN

#define DEF_HEADER_SIZE Size(77,42)

class MenuItemTab :         public MenuItemImage
{
    CC_SYNTHESIZE(int, m_nIndexMapping, IndexMapping);
public:
    static MenuItemTab * create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const ccMenuCallback& callback);
    
    virtual void selected() override;
    virtual void unselected() override;
    
    virtual void cusSelected();
    virtual void cusUnselected();
};

class ExTabView :         public Node,
                            public cocos2d::extension::TableViewDataSource,
                            public cocos2d::extension::TableViewDelegate
{
public:
    // tab data
    struct TabData
    {
        bool    IsFitWidth; // fit width with text
        string  TabName;    // tab name
        float   TabWidth;   // tab width
    };
    
    static ExTabView* create(cocos2d::Rect rect, string strTabNormal, string strTabActive, ccMenuCallback menuTabCallback = 0, ccMenuCallback menuCloseCallback = 0, string strTabClose = "", string strTabCloseSelect = "");
    
    ExTabView(cocos2d::Rect rect, string strTabNormal, string strTabActive, ccMenuCallback menuTabCallback = 0, ccMenuCallback menuCloseCallback = 0, string strTabClose = "", string strTabCloseSelect = "");
    
    void initTabData();
    
    // add or remove tab
    void addTab(string strTabName, Node* tabView, ccMenuCallback menuTabCallback = 0, bool bFitWidthWithText = false, float fTabWidth = -1.0f);
    void removeTab(int nIndex);
    void removeLastTab();
    
    virtual void onEnter();
    virtual void onExit();
    
    // handle touch events
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onTouchCancelled(Touch *touch, Event *unused_event);
    
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
    // tab clicked events
    void tabClicked(Ref* obj);
    
    // set background color
    void setBackgroundColor(Color4B color);
    
    // properties
    // left margin for first tab
    CC_SYNTHESIZE(float, _leftMargin, LeftTabMargin);
    
    // right margin for close button
    CC_SYNTHESIZE(float, _topCloseMargin, TopCloseMargin);
    CC_SYNTHESIZE(float, _rightCloseMargin, RightCloseMargin);
    
    // tab header image size
    CC_SYNTHESIZE(cocos2d::Size, _tabSize, TabSize);
    
    // tab title font size and color
    CC_SYNTHESIZE(float, _titleFontSize,TitleFontSize);
    CC_SYNTHESIZE(string, _titleFontName, TitleFontName);
    CC_SYNTHESIZE(Color3B, _titleFontColor, TitleFontColor);
    
    // default selected tab
    CC_SYNTHESIZE(int, _selectedTab, SelectedTab);
    
    // same tab title and related tab sub view
    CC_SYNTHESIZE_READONLY(vector<TabData>, _tabDataArray, TabDataArray);
    CC_SYNTHESIZE_READONLY(Vector<Node*>, _tabViewArray, TabViewArray);
    
    // call back when click on tab
    CC_SYNTHESIZE_READONLY(vector<ccMenuCallback>, _tabMenuCloseCallback, TabCallbackArray);
    
    // call back when do event close
    CC_SYNTHESIZE(ccMenuCallback, _menuCloseCallback, MenuCloseCallback);
    
    // call back when do event tab select
    CC_SYNTHESIZE(ccMenuCallback, _menuTabCallback, MenuTabCallback);
    
    CC_SYNTHESIZE(string, _strImgTabNormal, ImgTabNormal);
    CC_SYNTHESIZE(string, _strImgTabActive, ImgTabActive);
    CC_SYNTHESIZE(string, _strImgTabClose, ImgTabClose);
    CC_SYNTHESIZE(string, _strImgTabCloseSelect, ImgTabCloseSelect);
    
private:
    // main menu for add tab and exit btn
    Menu* _pMenu;
    
    // scroll view the container for all item
    cocos2d::extension::TableView* _pTabScrollView;
    
    // count of tabs if have in scroll view
    ssize_t _nTabsCountScrollView;
    // store map of cells -> prevent its init again -> lost selection on scrollView
    Map<int, TableViewCell*> _mapCells;
    
    map<int, float> _mapTabWidth; // tab width
    
    // table view real content size
    cocos2d::Size _realContentSize;
    
    // sub view real content size
    cocos2d::Size _realSubContentSize;
    
    // background color
    Color4B _backgroundColor;
    
    MenuItemTab* _preSelectedTab;
    LayerColor* _tabView;
};

NS_SS_END

#endif /* defined(__senspark_game_foundation__ExTabView__) */
