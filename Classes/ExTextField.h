//
//  ExTextField.h
//  senspark-game-foundation
//
//  Created by HuyPhan on 1/19/15.
//
//

#ifndef __senspark_game_foundation__ExTextField__
#define __senspark_game_foundation__ExTextField__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SSMacros.h"

USING_NS_CC;
using namespace std;

NS_SS_BEGIN

typedef std::function<void()> ccFuncCallback;

class ExTextFieldTTF : public TextFieldTTF
{
protected:
    string          _strRealText;            // real text
    string          _strVisiableText;        // just visible text
    CC_SYNTHESIZE(bool, _passwordEnabled, PasswordEnabled);
    char          _passwordStyleText;
    CC_SYNTHESIZE(int, _nMaxTextLenght, MaxTextLenght);
    CC_SYNTHESIZE(int, _nMaxTextCanShowLenght, MaxTextCanShowLenght);
    CC_SYNTHESIZE(ccFuncCallback, _updateBgCallBack, UpdateBgCallBack);
public:
    
    ExTextFieldTTF();
    
    /** creates a ExTextField from a fontname, alignment, dimension and font size */
    static ExTextFieldTTF * textFieldWithPlaceHolder(const std::string& placeholder, const cocos2d::Size& dimensions, TextHAlignment alignment, const std::string& fontName, float fontSize);
    /** creates a ExTextField from a fontname and font size */
    static ExTextFieldTTF * textFieldWithPlaceHolder(const std::string& placeholder, const std::string& fontName, float fontSize);
    
    // set real string
    void setRealString(const std::string& text);
    void updateString(const std::string& text);
    
    // for return correct folder
    virtual void setString(const std::string& text) override;
    virtual const std::string& getString() const override;
    
    // handle input and clear back
    virtual void insertText(const char * text, size_t len) override;
    virtual void deleteBackward() override;
    
    // override func for calcu the max show text
    virtual void setSystemFontSize(float fontSize) override;
    virtual void setSystemFontName(const std::string& systemFont) override;
    
    float getFixedWidth();
    void setFixedWidth(float fWidth);
    
    // check for max text lenght
    void updateMaxTextLenght(float dt);
    int calcuMaxCharCanShow(float maxWidth = 0.0f);
    
private:
    string getVisibleText(string strFullText, int& outPutMaxLenght);
    
    // max texture size
    GLint _maxTextureSize;
    float _fixedWidth;
    
    Label* pLabel;
};


// this cover class because ExTextFieldTTF have base class Lable can't add any child obj
class ExTextField : public Node
{
public:
    ExTextField();
    
    /** creates a ExTextField from a fontname, alignment, dimension and font size */
    static ExTextField * textFieldWithPlaceHolder(const std::string& placeholder, const cocos2d::Size& dimensions, TextHAlignment alignment, const std::string& fontName, float fontSize, SpriteFrame* spriteFrameBg);
    /** creates a ExTextField from a fontname and font size */
    static ExTextField * textFieldWithPlaceHolder(const std::string& placeholder, const std::string& fontName, float fontSize, SpriteFrame* spriteFrameBg);
    
    // some navigate to ExTextFieldTTF class
    virtual void setString(std::string strText);
    virtual const std::string getString();
    
    virtual void setSystemFontSize(float fontSize);
    virtual void setSystemFontName(const std::string& systemFont);
    
    virtual void setMaxTextLenght(int lenght);
    virtual int getMaxTextLenght();
    
    virtual void setPasswordEnabled(bool value);
    virtual bool getPasswordEnabled();
    
    virtual void setAnchorPoint(const Vec2& anchorPoint) override;
    virtual const cocos2d::Size& getContentSize() const override;
    
    // the func for set the fix width of background, if not, it just scale content the text
    void setFixedBackgroundWidth(float fWidth);
    
    /**
     @brief    Open keyboard and receive input text.
     */
    virtual bool attachWithIME();
    
    /**
     @brief    End text input and close keyboard.
     */
    virtual bool detachWithIME();
    
protected:
    ExTextFieldTTF* _pExTextFieldTTF;
    Sprite* _pSpriteBg;
    
    void updateBackgroundImg(); // update background scale
};

NS_SS_END

#endif /* defined(__senspark_game_foundation__ExTextField__) */
