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

//USING_NS_CC;
USING_NS_CC_EXT;
//using namespace std;

NS_SS_BEGIN

#define DEF_HEADER_SIZE cocos2d::Size(77,42)

class MenuItemTab :         public cocos2d::MenuItemImage
{
    CC_SYNTHESIZE(int, m_nIndexMapping, IndexMapping);
public:
    static MenuItemTab * create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const cocos2d::ccMenuCallback& callback);
    
    virtual void selected() override;
    virtual void unselected() override;
    
    virtual void cusSelected();
    virtual void cusUnselected();
};

class ExTabView :         public cocos2d::Node,
                            public cocos2d::extension::TableViewDataSource,
                            public cocos2d::extension::TableViewDelegate
{
public:
    // tab data
    struct TabData
    {
        bool    IsFitWidth; // fit width with text
        std::string  TabName;    // tab name
        float   TabWidth;   // tab width
    };
    
    static ExTabView* create(cocos2d::Rect rect, std::string strTabNormal, std::string strTabActive, cocos2d::ccMenuCallback menuTabCallback = 0, cocos2d::ccMenuCallback menuCloseCallback = 0, std::string strTabClose = "", std::string strTabCloseSelect = "");
    
    ExTabView(cocos2d::Rect rect, std::string strTabNormal, std::string strTabActive, cocos2d::ccMenuCallback menuTabCallback = 0, cocos2d::ccMenuCallback menuCloseCallback = 0, std::string strTabClose = "", std::string strTabCloseSelect = "");
    
    void initTabData();
    
    // add or remove tab
    void addTab(std::string strTabName, cocos2d::Node* tabView, cocos2d::ccMenuCallback menuTabCallback = 0, bool bFitWidthWithText = false, float fTabWidth = -1.0f);
    void removeTab(int nIndex);
    void removeLastTab();
    
    virtual void onEnter();
    virtual void onExit();
    
    // handle touch events
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {};
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
    // tab clicked events
    void tabClicked(cocos2d::Ref* obj);
    
    // set background color
    void setBackgroundColor(cocos2d::Color4B color);
    
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
    CC_SYNTHESIZE(std::string, _titleFontName, TitleFontName);
    CC_SYNTHESIZE(cocos2d::Color3B, _titleFontColor, TitleFontColor);
    
    // default selected tab
    CC_SYNTHESIZE(int, _selectedTab, SelectedTab);
    
    // same tab title and related tab sub view
    CC_SYNTHESIZE_READONLY(std::vector<TabData>, _tabDataArray, TabDataArray);
    CC_SYNTHESIZE_READONLY(cocos2d::Vector<Node*>, _tabViewArray, TabViewArray);
    
    // call back when click on tab
    CC_SYNTHESIZE_READONLY(std::vector<cocos2d::ccMenuCallback>, _tabMenuCloseCallback, TabCallbackArray);
    
    // call back when do event close
    CC_SYNTHESIZE(cocos2d::ccMenuCallback, _menuCloseCallback, MenuCloseCallback);
    
    // call back when do event tab select
    CC_SYNTHESIZE(cocos2d::ccMenuCallback, _menuTabCallback, MenuTabCallback);
    
    CC_SYNTHESIZE(std::string, _strImgTabNormal, ImgTabNormal);
    CC_SYNTHESIZE(std::string, _strImgTabActive, ImgTabActive);
    CC_SYNTHESIZE(std::string, _strImgTabClose, ImgTabClose);
    CC_SYNTHESIZE(std::string, _strImgTabCloseSelect, ImgTabCloseSelect);
    
private:
    // main menu for add tab and exit btn
    cocos2d::Menu* _pMenu;
    
    // scroll view the container for all item
    cocos2d::extension::TableView* _pTabScrollView;
    
    // count of tabs if have in scroll view
    ssize_t _nTabsCountScrollView;
    // store map of cells -> prevent its init again -> lost selection on scrollView
    cocos2d::Map<int, TableViewCell*> _mapCells;
    
    std::map<int, float> _mapTabWidth; // tab width
    
    // table view real content size
    cocos2d::Size _realContentSize;
    
    // sub view real content size
    cocos2d::Size _realSubContentSize;
    
    // background color
    cocos2d::Color4B _backgroundColor;
    
    MenuItemTab* _preSelectedTab;
    cocos2d::LayerColor* _tabView;
};

NS_SS_END

#endif /* defined(__senspark_game_foundation__ExTabView__) */
