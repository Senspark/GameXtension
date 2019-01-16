//
//  ExTabView.cpp
//  senspark-game-foundation
//
//  Created by HuyPhan on 11/24/14.
//
//

#include "ExTabView.h"

NS_SS_BEGIN

//#define IMG_TAB_NORMAL          "tab_normal.png"
//#define IMG_TAB_ACTIVE          "tab_active.png"
//#define IMG_BTN_CLOSE           "btn_tableview_close.png"
//#define IMG_BTN_CLOSE_SELECT    "btn_tableview_close_select.png"
#define TAG_TAB_ITEM            2015


MenuItemTab * MenuItemTab::create(const std::string& normalImage, const std::string& selectedImage, const std::string& disabledImage, const cocos2d::ccMenuCallback& callback)
{
    MenuItemTab *ret = new (std::nothrow) MenuItemTab();
    if (ret && ret->initWithNormalImage(normalImage, selectedImage, disabledImage, callback))
    {
        // check if image null
        if(ret->getSelectedImage() == nullptr)
        {
            auto pSprite = cocos2d::Sprite::createWithSpriteFrameName(selectedImage);
            ret->setSelectedImage(pSprite);
        }
        
        if(ret->getNormalImage() == nullptr)
        {
            auto pSprite = cocos2d::Sprite::createWithSpriteFrameName(normalImage);
            ret->setNormalImage(pSprite);
        }
        
        if(ret->getDisabledImage() == nullptr)
        {
            auto pSprite = cocos2d::Sprite::createWithSpriteFrameName(disabledImage);
            ret->setDisabledImage(pSprite);
        }
        
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void MenuItemTab::selected()
{
    MenuItem::selected();
    
    if (_normalImage)
    {
        if (_disabledImage)
        {
            _disabledImage->setVisible(false);
        }
        
//        if (_selectedImage)
//        {
//            _normalImage->setVisible(false);
//            _selectedImage->setVisible(true);
//        }
//        else
//        {
//            _normalImage->setVisible(true);
//        }
    }
}

void MenuItemTab::unselected()
{
    MenuItem::unselected();
//    if (_normalImage)
//    {
//        _normalImage->setVisible(true);
//        
//        if (_selectedImage)
//        {
//            _selectedImage->setVisible(false);
//        }
//        
//        if (_disabledImage)
//        {
//            _disabledImage->setVisible(false);
//        }
//    }
}

void MenuItemTab::cusSelected()
{
    MenuItemImage::selected();
}

void MenuItemTab::cusUnselected()
{
    unselected();
    if (_normalImage)
    {
        _normalImage->setVisible(true);
        
        if (_selectedImage)
        {
            _selectedImage->setVisible(false);
        }
        
        if (_disabledImage)
        {
            _disabledImage->setVisible(false);
        }
    }

}

ExTabView::ExTabView(cocos2d::Rect rect, std::string strTabNormal, std::string strTabActive, cocos2d::ccMenuCallback menuTabCallback, cocos2d::ccMenuCallback menuCloseCallback, std::string strTabClose, std::string strTabCloseSelect)
{
    this->setContentSize(rect.size);
    this->setPosition(rect.origin);
    
    // set default values
    _tabSize            = DEF_HEADER_SIZE;
    _leftMargin         = 8.0f;
//    _titleFontName      = "Marker Felt";
    _titleFontColor     = cocos2d::Color3B(0xfb, 0xcf, 0x4b);
    _titleFontSize      = 32.0f;
    _preSelectedTab     = nullptr;
    _selectedTab        = 0;
    _topCloseMargin     = 20.0f;
    _rightCloseMargin   = 20.0f;
    _menuCloseCallback  = menuCloseCallback;
    _menuTabCallback    = menuTabCallback;
    _realContentSize    = rect.size;
    _pMenu              = nullptr;
    _pTabScrollView     = nullptr;
    
    _nTabsCountScrollView = 0;
    
    this->setImgTabNormal(strTabNormal);
    this->setImgTabActive(strTabActive);
    this->setImgTabClose(strTabClose);
    this->setImgTabCloseSelect(strTabCloseSelect);
    
    // pre-load tab images
    cocos2d::Director::getInstance()->getTextureCache()->addImage(_strImgTabNormal);
    cocos2d::Director::getInstance()->getTextureCache()->addImage(_strImgTabActive);
    cocos2d::Director::getInstance()->getTextureCache()->addImage(_strImgTabClose);
    cocos2d::Director::getInstance()->getTextureCache()->addImage(_strImgTabCloseSelect);
    
    // get the size of the tab
    if(cocos2d::Director::getInstance()->getTextureCache()->getTextureForKey(_strImgTabNormal) != nullptr)
    {
        _tabSize = cocos2d::Director::getInstance()->getTextureCache()->getTextureForKey(_strImgTabNormal)->getContentSize();
    }
    else if (cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(_strImgTabNormal) != nullptr)
    {
        _tabSize = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(_strImgTabNormal)->getRect().size;
    }
    
    // create sub view container
    _realSubContentSize = cocos2d::Size(rect.size.width, rect.size.height - _tabSize.height);
    _backgroundColor    = cocos2d::Color4B(0,0,0,0);
    _tabView            = cocos2d::LayerColor::create(_backgroundColor, rect.size.width, rect.size.height - _tabSize.height);
    
    _tabView->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(_tabView);
}

ExTabView* ExTabView::create(cocos2d::Rect rect, std::string strTabNormal, std::string strTabActive, cocos2d::ccMenuCallback menuTabCallback, cocos2d::ccMenuCallback menuCloseCallback, std::string strTabClose, std::string strTabCloseSelect)
{
    ExTabView *pRet = new ExTabView(rect, strTabNormal, strTabActive, menuTabCallback, menuCloseCallback, strTabClose, strTabCloseSelect);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void ExTabView::addTab(std::string strTabName, Node* tabView, cocos2d::ccMenuCallback menuTabCallback/* = 0*/, bool bFitWidthWithText/* = false*/, float fTabWidth/* = -1.0f*/)
{
    TabData data;
    data.TabName        = strTabName;
    data.IsFitWidth     = bFitWidthWithText;
    data.TabWidth       = fTabWidth;
    _tabDataArray.push_back(data);
    
    _tabMenuCloseCallback.push_back(menuTabCallback);
    
    tabView->setContentSize(_realSubContentSize);
    _tabViewArray.pushBack(tabView);
}

void ExTabView::removeTab(int nIndex)
{
    // check if have tab to remove
    if((_tabDataArray.size() > nIndex) && (_tabViewArray.size() > nIndex) && (nIndex >= 0))
    {
        _tabDataArray.erase(_tabDataArray.begin() + nIndex);
        
        auto pObjTab = _tabViewArray.at(nIndex);
        if(pObjTab)
        {
            _tabViewArray.eraseObject(pObjTab);
        }
    }
}

void ExTabView::removeLastTab()
{
    if(_tabDataArray.size() > 0 && _tabViewArray.size() > 0)
    {
        this->removeTab(_tabDataArray.size() < _tabViewArray.size() ? (int)_tabDataArray.size() - 1 : (int)_tabViewArray.size() - 1);
    }
}

// tab clicked events
void ExTabView::tabClicked(Ref* obj)
{
    MenuItemTab* pMenuItem = dynamic_cast<MenuItemTab*>(obj);
    
    if(pMenuItem == nullptr)
    {
        return;
    }
    
    int nTabIndex = -1;
    
    if (pMenuItem != _preSelectedTab)
    {
        pMenuItem->cusSelected();
        
        // unselected previous one
        if (_preSelectedTab != NULL)
        {
            _preSelectedTab->cusUnselected();
        }
        _preSelectedTab = pMenuItem;
        
        // showing related tab view
        nTabIndex       = pMenuItem->getIndexMapping();
        _selectedTab    = nTabIndex;
        
        // remove previous tab view
        _tabView->removeAllChildren();
        _tabView->setColor(cocos2d::Color3B(_backgroundColor));
        _tabView->setOpacity(_backgroundColor.a);
        auto subView = _tabViewArray.at(nTabIndex);
        float yPos = _realContentSize.height - _tabSize.height - _realSubContentSize.height;
        subView->setPosition(cocos2d::Vec2(0.0f, yPos));
        _tabView->addChild(subView);
    }
    else
    {
        pMenuItem->cusSelected();
    }
    
    // call back
    bool bAldreadyCallBack = false;
    if(_tabMenuCloseCallback.size() > nTabIndex && nTabIndex >= 0)
    {
        if(_tabMenuCloseCallback.at(nTabIndex) != nullptr)
        {
            _tabMenuCloseCallback.at(nTabIndex)(pMenuItem);
            bAldreadyCallBack = true;
        }
    }
    
    if(_menuTabCallback && bAldreadyCallBack == false)
    {
        _menuTabCallback(pMenuItem);
    }
}

void ExTabView::setBackgroundColor(cocos2d::Color4B color)
{
    _backgroundColor = color;
    _tabView->setColor(cocos2d::Color3B(_backgroundColor));
}

void ExTabView::initTabData()
{
    ssize_t tabDataCount = _tabDataArray.size();
    ssize_t tabViewCount = _tabViewArray.size();
    
    if ((tabDataCount <= 0) || (tabViewCount <= 0))
    {
        return;
    }
    
    // calcu for the min tab pos
    ssize_t tabCount = std::min(tabDataCount, tabViewCount);
    
    // check and make menu clear
    if(_pMenu)
    {
        _pMenu->removeFromParentAndCleanup(true);
        this->removeChild(_pMenu);
        _pMenu = nullptr;
    }
    
    if(_pTabScrollView)
    {
        _pTabScrollView->removeFromParentAndCleanup(true);
        this->removeChild(_pTabScrollView);
        _pTabScrollView = nullptr;
    }
    
    // prepare for make menu item
    cocos2d::Vec2 vec2NextPos    = cocos2d::Vec2::ZERO;
    cocos2d::Vector<cocos2d::MenuItem*> menuItemArray;
    
    // clear all cells
    _mapCells.clear();
    _mapTabWidth.clear();
    
    // if the width of tabs is more container -> use ScrollView else use menu
    //float fRealTabsSize     = (_tabSize.width * tabCount + (_leftMargin * (tabCount - 1)));
    float fRealTabsSize     = _leftMargin * -1.0f;
    
    for(int i = 0; i < tabCount; i++)
    {
        if(_tabDataArray.at(i).TabWidth > 0.0f)
        {
            _mapTabWidth[i]   = _tabDataArray.at(i).TabWidth;
        }
        else if(_tabDataArray.at(i).IsFitWidth) // use tab name for calcu the
        {
            cocos2d::Label* pLabel = nullptr;
            if(_titleFontName.find(".fnt") != std::string::npos)
            {
                pLabel = cocos2d::Label::createWithBMFont(_titleFontName, _tabDataArray.at(i).TabName);
            }
            else
            {
                if (cocos2d::FileUtils::getInstance()->isFileExist(_titleFontName))
                {
                    pLabel = cocos2d::Label::createWithSystemFont(_tabDataArray.at(i).TabName, _titleFontName, _titleFontSize);
                }
                else
                {
                    pLabel = cocos2d::Label::createWithSystemFont(_tabDataArray.at(i).TabName, _titleFontName, _titleFontSize);
                }
            }
            
            _mapTabWidth[i] = pLabel->getContentSize().width * pLabel->getScaleX() * 1.2f;
        }
        else
        {
            _mapTabWidth[i] = _tabSize.width;
        }
        
        fRealTabsSize += _mapTabWidth[i] + _leftMargin;
    }
    
    float fBtnWidthTemp = 0.0f;
    if(_strImgTabClose.length() > 0)
    {
        auto pSpriteTemp = cocos2d::Sprite::create(_strImgTabClose);
        if(pSpriteTemp == nullptr)
        {
             pSpriteTemp = cocos2d::Sprite::createWithSpriteFrameName(_strImgTabClose);
        }
        
        if(pSpriteTemp)
        {
            fBtnWidthTemp = pSpriteTemp->getContentSize().width;
        }
    }
    
    float fRealTabsMargin   = (_menuCloseCallback != nullptr ? _rightCloseMargin + fBtnWidthTemp : 0.0f);
    float fRealMaxTabsSize  = (_realContentSize.width - fRealTabsMargin * 2.0f);
    
    if(fRealTabsSize > fRealMaxTabsSize)
    {
        // re-set
        _nTabsCountScrollView = 0;
        // add scrollview
        _pTabScrollView = TableView::create(this, cocos2d::Size(fRealMaxTabsSize, _tabSize.height));
        _pTabScrollView->setDirection(ScrollView::Direction::HORIZONTAL);
        _pTabScrollView->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
        _pTabScrollView->setPosition(cocos2d::Vec2(fRealTabsMargin,
                                          _realContentSize.height - _tabSize.height));
        _pTabScrollView->setDelegate(this);
        this->addChild(_pTabScrollView);
        for(int i = 0; i < tabCount; i++)
        {
            // increase count of cells + insert into index
            _nTabsCountScrollView++;
            _pTabScrollView->insertCellAtIndex(i);
        }
    }
    else
    {
        // set number of tabs for scroll view  = 0 -> because not use it
        _nTabsCountScrollView = 0;
        
        cocos2d::Vec2 vec2TabPos     = cocos2d::Vec2( (_realContentSize.width - (fRealTabsSize) - (_leftMargin * (tabCount - 1))) * 0.5f + _mapTabWidth[0] * 0.5f,
                                   (_realContentSize.height - (_tabSize.height * 0.5f)));
    
        for (int i = 0; i < tabCount; i++)
        {
            // set tab background
            vec2NextPos = vec2TabPos + cocos2d::Vec2((_mapTabWidth[i] + (_mapTabWidth.count(i + 1) > 0 ? _mapTabWidth[i + 1] : _mapTabWidth[i])) * 0.5f + _leftMargin, 0.0f);
            MenuItemTab* pMenuItem = MenuItemTab::create(_strImgTabNormal, _strImgTabActive, _strImgTabNormal, CC_CALLBACK_1(ExTabView::tabClicked, this));
            pMenuItem->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
            pMenuItem->setPosition(vec2TabPos);
            pMenuItem->setTag(i);
            pMenuItem->setName(_tabDataArray.at(i).TabName);
            pMenuItem->setIndexMapping(i);
            
            pMenuItem->setScaleX(_mapTabWidth[i] / pMenuItem->getContentSize().width);
            
            if (i == _selectedTab)
            {
                pMenuItem->cusSelected();
                _preSelectedTab = pMenuItem;
            
                _tabView->removeAllChildren();
                _tabView->setColor(cocos2d::Color3B(_backgroundColor));
                auto subView = _tabViewArray.at(i);
                float yPos = _realContentSize.height - _tabSize.height - _realSubContentSize.height;
                subView->setPosition(cocos2d::Vec2(0.0f, yPos));
                _tabView->addChild(subView);
            }
        
            // set tab title
            cocos2d::Label* pLabel = nullptr;
            if(_titleFontName.find(".fnt") != std::string::npos)
            {
                pLabel = cocos2d::Label::createWithBMFont(_titleFontName, _tabDataArray.at(i).TabName);
            }
            else
            {
                if (cocos2d::FileUtils::getInstance()->isFileExist(_titleFontName))
                {
                    pLabel = cocos2d::Label::createWithSystemFont(_tabDataArray.at(i).TabName, _titleFontName, _titleFontSize);
                }
                else
                {
                    pLabel = cocos2d::Label::createWithSystemFont(_tabDataArray.at(i).TabName, _titleFontName, _titleFontSize);
                }
            }
            pLabel->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
            pLabel->setColor(_titleFontColor);
            pLabel->setPosition(cocos2d::Vec2(_tabSize.width * 0.5f, _tabSize.height * 0.5f));
            pLabel->setScaleX(1.0f / pMenuItem->getScaleX());
            
            pMenuItem->addChild(pLabel);
        
            menuItemArray.pushBack(pMenuItem);
        
            vec2TabPos = vec2NextPos;
        }
    }
    
    // if menu callback event = nul <=> it will don't have close btn
    if(_menuCloseCallback && _strImgTabClose.length() > 0 && _strImgTabCloseSelect.length() > 0)
    {
        // add close btn
        cocos2d::MenuItemImage* pMenuItem = cocos2d::MenuItemImage::create(_strImgTabClose, _strImgTabCloseSelect, _strImgTabClose, _menuCloseCallback);
        
        // check if image null
        if(pMenuItem->getSelectedImage() == nullptr)
        {
            auto pSprite = cocos2d::Sprite::createWithSpriteFrameName(_strImgTabCloseSelect);
            pMenuItem->setSelectedImage(pSprite);
        }
        
        if(pMenuItem->getNormalImage() == nullptr)
        {
            auto pSprite = cocos2d::Sprite::createWithSpriteFrameName(_strImgTabClose);
            pMenuItem->setNormalImage(pSprite);
        }
        
        if(pMenuItem->getDisabledImage() == nullptr)
        {
            auto pSprite = cocos2d::Sprite::createWithSpriteFrameName(_strImgTabClose);
            pMenuItem->setDisabledImage(pSprite);
        }
        
        pMenuItem->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
        pMenuItem->setPosition(cocos2d::Vec2(_realContentSize.width - _rightCloseMargin - (pMenuItem->getContentSize().width * 0.5f),
                                    _realContentSize.height - _topCloseMargin - (pMenuItem->getContentSize().height * 0.5f)));
    
        menuItemArray.pushBack(pMenuItem);
    }
    
    if(menuItemArray.size() > 0)
    {
        _pMenu = cocos2d::Menu::createWithArray(menuItemArray);
        _pMenu->setPosition(cocos2d::Vec2::ZERO);
        this->addChild(_pMenu);
    }
}

void ExTabView::onEnter()
{
    this->initTabData();
    
    Node::onEnter();
}

void ExTabView::onExit()
{
    cocos2d::Director::getInstance()->getTextureCache()->removeTextureForKey(_strImgTabNormal);
    cocos2d::Director::getInstance()->getTextureCache()->removeTextureForKey(_strImgTabActive);
    cocos2d::Director::getInstance()->getTextureCache()->removeTextureForKey(_strImgTabClose);
    cocos2d::Director::getInstance()->getTextureCache()->removeTextureForKey(_strImgTabCloseSelect);
    
    Node::onExit();
}

void ExTabView::tableCellTouched(TableView* table, TableViewCell* cell)
{
    this->tabClicked(cell->getChildByTag(TAG_TAB_ITEM));
}

cocos2d::Size ExTabView::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
    return cocos2d::Size(_mapTabWidth[(int)idx] + _leftMargin, _tabSize.height);
}

TableViewCell* ExTabView::tableCellAtIndex(TableView *table, ssize_t idx)
{
    // get the cell at this index
    TableViewCell *pCell = table->cellAtIndex(idx);
    if (!pCell)
    {
        int i = (int)idx;
        // check if have just use
        if(_mapCells.at(i) != nullptr)
        {
            pCell = _mapCells.at(i);
        }
        else
        {
            pCell = new TableViewCell();
            pCell->autorelease();
        
        
            MenuItemTab* pMenuItem = MenuItemTab::create(_strImgTabNormal, _strImgTabActive, _strImgTabNormal, CC_CALLBACK_1(ExTabView::tabClicked, this));
            pMenuItem->setAnchorPoint(cocos2d::Vec2::ZERO);
            pMenuItem->setPosition(cocos2d::Vec2::ZERO);
            pMenuItem->setTag(TAG_TAB_ITEM);
            pMenuItem->setName(_tabDataArray.at(i).TabName);
            pMenuItem->setIndexMapping(i);
            
            pMenuItem->setScaleX(_mapTabWidth[i] / pMenuItem->getContentSize().width);
        
            if (i == _selectedTab)
            {
                pMenuItem->cusSelected();
                _preSelectedTab = pMenuItem;
            
                _tabView->removeAllChildren();
                _tabView->setColor(cocos2d::Color3B(_backgroundColor));
                auto subView = _tabViewArray.at(i);
                float yPos = _realContentSize.height - _tabSize.height - _realSubContentSize.height;
                subView->setPosition(cocos2d::Vec2(0.0f, yPos));
                _tabView->addChild(subView);
            }
        
            // set tab title
            cocos2d::Label* pLabel = nullptr;
            if(_titleFontName.find(".fnt") != std::string::npos)
            {
                pLabel = cocos2d::Label::createWithBMFont(_titleFontName, _tabDataArray.at(i).TabName);
            }
            else
            {
                if (cocos2d::FileUtils::getInstance()->isFileExist(_titleFontName))
                {
                    pLabel = cocos2d::Label::createWithSystemFont(_tabDataArray.at(i).TabName, _titleFontName, _titleFontSize);
                }
                else
                {
                    pLabel = cocos2d::Label::createWithSystemFont(_tabDataArray.at(i).TabName, _titleFontName, _titleFontSize);
                }
            }
            pLabel->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
            pLabel->setColor(_titleFontColor);
            pLabel->setPosition(cocos2d::Vec2(_tabSize.width * 0.5f, _tabSize.height * 0.5f));
            pLabel->setScaleX(1.0f / pMenuItem->getScaleX());
            
            pMenuItem->addChild(pLabel);
        
            pCell->addChild(pMenuItem);
            
            // insert back to map
            _mapCells.insert(i, pCell);
        }
    }
    
    return pCell;
}

ssize_t ExTabView::numberOfCellsInTableView(TableView *table)
{
    return _nTabsCountScrollView;
}


// just do nothing for this layer can't call to check touch for menu
bool ExTabView::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(unused_event);
    
    return true;
}

void ExTabView::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(unused_event);
}

void ExTabView::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(unused_event);
}

void ExTabView::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(unused_event);
}

NS_SS_END
