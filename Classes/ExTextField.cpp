//
//  ExTextField.cpp
//  senspark-game-foundation
//
//  Created by HuyPhan on 1/19/15.
//
//

#include "ExTextField.h"

NS_SS_BEGIN

#define MARGIN_LEFT_RIGHT 5.0f

static int _calcCharCount(const char * text)
{
    int n = 0;
    char ch = 0;
    while ((ch = *text))
    {
        CC_BREAK_IF(! ch);
        
        if (0x80 != (0xC0 & ch))
        {
            ++n;
        }
        ++text;
    }
    return n;
}

ExTextFieldTTF::ExTextFieldTTF() :      _strRealText(""),
                                        _strVisiableText(""),
                                        _passwordEnabled(false),
                                        _passwordStyleText('*'),
                                        _nMaxTextCanShowLenght(INT_MAX),
                                        _nMaxTextLenght(INT_MAX),
                                        pLabel(nullptr),
                                        _maxTextureSize(0),
                                        _fixedWidth(-1.0f)
{
}

ExTextFieldTTF * ExTextFieldTTF::textFieldWithPlaceHolder(const std::string& placeholder, const cocos2d::Size& dimensions, cocos2d::TextHAlignment alignment, const std::string& fontName, float fontSize)
{
    ExTextFieldTTF *ret = new (std::nothrow) ExTextFieldTTF();
    if(ret && ret->initWithPlaceHolder("", dimensions, alignment, fontName, fontSize))
    {
        ret->autorelease();
        if (placeholder.size()>0)
        {
            ret->setPlaceHolder(placeholder);
        }
        ret->setMaxTextCanShowLenght(ret->calcuMaxCharCanShow());
        
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

ExTextFieldTTF * ExTextFieldTTF::textFieldWithPlaceHolder(const std::string& placeholder, const std::string& fontName, float fontSize)
{
    ExTextFieldTTF *ret = new (std::nothrow) ExTextFieldTTF();
    if(ret && ret->initWithPlaceHolder("", fontName, fontSize))
    {
        ret->autorelease();
        if (placeholder.size()>0)
        {
            ret->setPlaceHolder(placeholder);
        }
        ret->setMaxTextCanShowLenght(ret->calcuMaxCharCanShow());
        
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void ExTextFieldTTF::setString(const std::string& text)
{
    _strVisiableText = text;
    // check password
    if(_passwordEnabled)
    {
        std::string strTemp(_strVisiableText.size(), _passwordStyleText);
        _strVisiableText = strTemp;
    }
    TextFieldTTF::setString(_strVisiableText);
}

void ExTextFieldTTF::setRealString(const std::string& text)
{
    // canot set because lenght > Max
    if(text.size() > _nMaxTextLenght)
    {
        return;
    }
    
    if (text.compare(_strRealText))
    {
        _strRealText = text;
        // do some things for calcu the new text lenght
        _strVisiableText = this->getVisibleText(_strRealText, _nMaxTextCanShowLenght);
        
        // check password
        std::string strSetValue = _strVisiableText;
        if(_passwordEnabled)
        {
            std::string strTemp(strSetValue.size(), _passwordStyleText);
            strSetValue = strTemp;
        }
        TextFieldTTF::setString(strSetValue);
    }
    
    cocos2d::log("Real string: %s", _strRealText.c_str());
    cocos2d::log("Show string: %s", _strVisiableText.c_str());
    cocos2d::log("On screen:   %s", _inputText.c_str());
}

void ExTextFieldTTF::updateString(const std::string& text)
{
    _strVisiableText = this->getVisibleText(text, _nMaxTextCanShowLenght);
    
    // check password
    std::string strSetValue = _strVisiableText;
    if(_passwordEnabled)
    {
        std::string strTemp(strSetValue.size(), _passwordStyleText);
        strSetValue = strTemp;
    }
    TextFieldTTF::setString(strSetValue);
    
    cocos2d::log("Real string: %s", _strRealText.c_str());
    cocos2d::log("Show string: %s", _strVisiableText.c_str());
    cocos2d::log("On screen:   %s", _inputText.c_str());
    
    // update call back any edit change text
    if(_updateBgCallBack)
    {
        _updateBgCallBack();
    }
}

const std::string& ExTextFieldTTF::getString() const
{
    return _strRealText;
}

void ExTextFieldTTF::insertText(const char * text, size_t len)
{
    // can't insert any on char -> current lenght > Max
    if(_strRealText.size() >= _nMaxTextLenght)
    {
        return;
    }
    
    std::string insert(text, len);
    
    // insert \n means input end
    int pos = static_cast<int>(insert.find('\n'));
    if ((int)insert.npos != pos)
    {
        len = pos;
        insert.erase(pos);
    }
    
    if (len > 0)
    {
        if (_delegate && _delegate->onTextFieldInsertText(this, insert.c_str(), len))
        {
            // delegate doesn't want to insert text
            return;
        }
        
        _charCount += _calcCharCount(insert.c_str());
        std::string sText(_strRealText);//(_inputText);
        sText.append(insert);
        
        // ExTextField
        _strRealText.append(insert);
        updateString(_strRealText);
    }
    
    if ((int)insert.npos == pos) {
        return;
    }
    
    // '\n' inserted, let delegate process first
    if (_delegate && _delegate->onTextFieldInsertText(this, "\n", 1))
    {
        return;
    }
    
    // if delegate hasn't processed, detach from IME by default
    detachWithIME();
}

void ExTextFieldTTF::deleteBackward()
{
    size_t len = _strVisiableText.length();
    if (! len)
    {
        // there is no string
        return;
    }
    
    // get the delete byte number
    size_t deleteLen = 1;    // default, erase 1 byte
    
    while(0x80 == (0xC0 & _strVisiableText.at(len - deleteLen)))
    {
        ++deleteLen;
    }
    
    if (_delegate && _delegate->onTextFieldDeleteBackward(this, _strVisiableText.c_str() + len - deleteLen, static_cast<int>(deleteLen)))
    {
        // delegate doesn't want to delete backwards
        return;
    }
    
    // if all text deleted, show placeholder string
    if (len <= deleteLen)
    {
        _inputText = "";
        
        // ExTextField
        _strRealText = "";
        _strVisiableText = "";
        
        _charCount = 0;
        Label::setTextColor(_colorSpaceHolder);
        Label::setString(_placeHolder);
        
        // update call back any edit change text
        if(_updateBgCallBack)
        {
            _updateBgCallBack();
        }
        
        return;
    }
    
    
    // ExTextField
    size_t realLen = _strRealText.length();
    std::string realText(_strRealText.c_str(), realLen - deleteLen);
    _strRealText = realText;
    
    // set new input text
    std::string text(_strVisiableText.c_str(), len - deleteLen);
    TextFieldTTF::setString(text);
    
    
    // update interface
    updateString(_strRealText);
    
    cocos2d::log("Real string: %s", _strRealText.c_str());
    cocos2d::log("Show string: %s", _strVisiableText.c_str());
    cocos2d::log("On screen:   %s", _inputText.c_str());
}

void ExTextFieldTTF::setSystemFontSize(float fontSize)
{
    // call from base func
    TextFieldTTF::setSystemFontSize(fontSize);
    
    // calcu the max text can show
    if(this->pLabel)
    {
        this->setMaxTextCanShowLenght(this->calcuMaxCharCanShow());
    }
}

void ExTextFieldTTF::setSystemFontName(const std::string& systemFont)
{
    // call from base func
    TextFieldTTF::setSystemFontName(systemFont);
    
    //// calcu the max text can show
    if(this->pLabel)
    {
        this->setMaxTextCanShowLenght(this->calcuMaxCharCanShow());
    }
}

float ExTextFieldTTF::getFixedWidth()
{
    return _fixedWidth;
}

void ExTextFieldTTF::setFixedWidth(float fWidth)
{
    if(fWidth > 0.0f && _fixedWidth != fWidth)
    {
        _fixedWidth = fWidth;
        this->setMaxTextCanShowLenght(this->calcuMaxCharCanShow(_fixedWidth));
        if(_updateBgCallBack)
        {
            _updateBgCallBack();
        }
    }
}

std::string ExTextFieldTTF::getVisibleText(std::string strFullText, int &outPutMaxLenght)
{
    std::string strTemp              = "";
    int nCharCount              = outPutMaxLenght;
    int nFullTextCharCount      = (int)strFullText.size();
    
    // check for not the lenght of text when have fix width
    if(_fixedWidth > 0.0f)
    {
        nCharCount              = (int)_inputText.size();
        bool bTempReCheck       = this->getContentSize().width * this->getScaleX() > _fixedWidth;
        if(bTempReCheck)
        {
            do
            {
                if(nCharCount <= 0)
                {
                    nCharCount = 0;
                    break;
                }
                
                nCharCount--;
                strTemp         = strFullText.substr(nFullTextCharCount - nCharCount);
                if(_passwordEnabled)
                {
                    std::string strTemp2(strTemp.size(), _passwordStyleText);
                    strTemp = strTemp2;
                }
                Label::setString(strTemp);
                
                // temp
                bTempReCheck       = this->getContentSize().width * this->getScaleX() > _fixedWidth;
                
            }while (bTempReCheck);
        }
        else
        {
            do
            {
                if(nCharCount >= nFullTextCharCount)
                {
                    nCharCount = nFullTextCharCount;
                    break;
                }
                
                nCharCount++;
                strTemp         = strFullText.substr(nFullTextCharCount - nCharCount);
                if(_passwordEnabled)
                {
                    std::string strTemp2(strTemp.size(), _passwordStyleText);
                    strTemp = strTemp2;
                }
                Label::setString(strTemp);
                
                // temp
                bTempReCheck       = this->getContentSize().width * this->getScaleX() < _fixedWidth;
                
                
                if(!bTempReCheck)
                {
                    nCharCount--;
                }
                
            }while (bTempReCheck);
        }
        
        // update
        outPutMaxLenght = nCharCount;
    }
    
    
    
    // check if less than current
    if(nFullTextCharCount <= outPutMaxLenght)
    {
        strTemp = strFullText;
    }
    else
    {
        strTemp = strFullText.substr(nFullTextCharCount - outPutMaxLenght);
    }
    
    return strTemp;
}

int ExTextFieldTTF::calcuMaxCharCanShow(float maxWidth)
{
    this->pLabel = Label::create();
    this->pLabel->setSystemFontName(this->getSystemFontName());
    this->pLabel->setSystemFontSize(this->getSystemFontSize());
    this->pLabel->setString("qwertyuiopasdfghjklzxcvbnm123456789/*-+~`!@#$%^&*()_=,./<>?;':");
    
    _maxTextureSize             = 0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTextureSize);
    float fTempWidth = maxWidth == 0.0f ? _maxTextureSize : maxWidth;
    
    // because it can't select text -> you just show 1x max texture size
    int nTemp                   = (/*3.0f*/ 1.0f * fTempWidth) / (pLabel->getContentSize().width / (float)pLabel->getString().size());
    
    // it must be can't not less than 10
    nTemp                       = MAX(nTemp, 10);
    
    this->pLabel                = nullptr;
    
    cocos2d::log("Max tex size %d", _maxTextureSize);
    cocos2d::log("Max char     %d", nTemp);
    
    return nTemp;
}

ExTextField::ExTextField() : _pExTextFieldTTF(nullptr),
                             _pSpriteBg(nullptr)
{
}

ExTextField * ExTextField::textFieldWithPlaceHolder(const std::string& placeholder, const cocos2d::Size& dimensions, cocos2d::TextHAlignment alignment, const std::string& fontName, float fontSize, cocos2d::SpriteFrame* spriteFrameBg)
{
    ExTextField *pExTextField = new (std::nothrow) ExTextField();
    if (pExTextField && spriteFrameBg)
    {
        pExTextField->autorelease();
        
        // init bg
        pExTextField->_pSpriteBg = cocos2d::Sprite::createWithSpriteFrame(spriteFrameBg);
        pExTextField->addChild(pExTextField->_pSpriteBg);
        
        // init the text
        pExTextField->_pExTextFieldTTF = ExTextFieldTTF::textFieldWithPlaceHolder(placeholder, dimensions, alignment, fontName, fontSize);
        pExTextField->addChild(pExTextField->_pExTextFieldTTF);
        pExTextField->_pExTextFieldTTF->setUpdateBgCallBack(CC_CALLBACK_0(ExTextField::updateBackgroundImg, pExTextField));
        pExTextField->_pExTextFieldTTF->setPosition(cocos2d::Vec2(MARGIN_LEFT_RIGHT, 0.0f));
        
        pExTextField->updateBackgroundImg();
        
        return pExTextField;
    }
    CC_SAFE_DELETE(pExTextField);
    return nullptr;
}

ExTextField * ExTextField::textFieldWithPlaceHolder(const std::string& placeholder, const std::string& fontName, float fontSize, cocos2d::SpriteFrame* spriteFrameBg)
{
    ExTextField *pExTextField = new (std::nothrow) ExTextField();
    if (pExTextField && spriteFrameBg)
    {
        pExTextField->autorelease();
        
        // init bg
        pExTextField->_pSpriteBg = cocos2d::Sprite::createWithSpriteFrame(spriteFrameBg);
        pExTextField->addChild(pExTextField->_pSpriteBg);
        
        // init the text
        pExTextField->_pExTextFieldTTF = ExTextFieldTTF::textFieldWithPlaceHolder(placeholder, fontName, fontSize);
        pExTextField->addChild(pExTextField->_pExTextFieldTTF);
        pExTextField->_pExTextFieldTTF->setUpdateBgCallBack(CC_CALLBACK_0(ExTextField::updateBackgroundImg, pExTextField));
        pExTextField->_pExTextFieldTTF->setPosition(cocos2d::Vec2(MARGIN_LEFT_RIGHT, 0.0f));
        
        pExTextField->updateBackgroundImg();
        
        return pExTextField;
    }
    CC_SAFE_DELETE(pExTextField);
    return nullptr;
}

void ExTextField::setString(std::string strText)
{
    this->_pExTextFieldTTF->setRealString(strText);
}

const std::string ExTextField::getString()
{
    return this->_pExTextFieldTTF->getString();
}

void ExTextField::setSystemFontSize(float fontSize)
{
    this->_pExTextFieldTTF->setSystemFontSize(fontSize);
    this->updateBackgroundImg();
}

void ExTextField::setSystemFontName(const std::string& systemFont)
{
    this->setSystemFontName(systemFont);
    this->updateBackgroundImg();
}

void ExTextField::setMaxTextLenght(int lenght)
{
    this->_pExTextFieldTTF->setMaxTextLenght(lenght);
}

int ExTextField::getMaxTextLenght()
{
    return this->_pExTextFieldTTF->getMaxTextLenght();
}

void ExTextField::setPasswordEnabled(bool value)
{
    this->_pExTextFieldTTF->setPasswordEnabled(value);
}

bool ExTextField::getPasswordEnabled()
{
    return this->_pExTextFieldTTF->getPasswordEnabled();
}

void ExTextField::setAnchorPoint(const cocos2d::Vec2& anchorPoint)
{
    Node::setAnchorPoint(anchorPoint);
    
    this->_pSpriteBg->setAnchorPoint(anchorPoint);
    this->_pExTextFieldTTF->setAnchorPoint(anchorPoint);
}

const cocos2d::Size& ExTextField::getContentSize() const
{
    return this->_pExTextFieldTTF->getContentSize();
}

void ExTextField::setFixedBackgroundWidth(float fWidth)
{
    this->_pExTextFieldTTF->setFixedWidth(fWidth);
}

void ExTextField::updateBackgroundImg()
{
    // if _fixedWidth < 0 -> the back ground will content the text, if not, just exactly _fixedWidth and fix width
    // get the content size of text
    float fTextWidth        = this->_pExTextFieldTTF->getContentSize().width * this->_pExTextFieldTTF->getScaleX();
    float fTextHeight       = this->_pExTextFieldTTF->getContentSize().height * this->_pExTextFieldTTF->getScaleY();
    
    
    if(this->_pExTextFieldTTF->getFixedWidth() > 0.0f)
    {
        fTextWidth          = this->_pExTextFieldTTF->getFixedWidth();
    }
    
    fTextWidth              += MARGIN_LEFT_RIGHT * 2.0f;
    fTextHeight             *= 1.2f;
    
    // update the height & width
    float fScaleX           = fTextWidth / this->_pSpriteBg->getContentSize().width;
    float fScaleY           = fTextHeight / this->_pSpriteBg->getContentSize().height;
    this->_pSpriteBg->setScale(fScaleX, fScaleY);
}

bool ExTextField::attachWithIME()
{
    return this->_pExTextFieldTTF->attachWithIME();
}

bool ExTextField::detachWithIME()
{
    return this->_pExTextFieldTTF->detachWithIME();
}

NS_SS_END
