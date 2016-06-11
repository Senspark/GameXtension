//
// StringResource.h
// GameXtension
//
// Created by Duc Nguyen on 11/28/12.
// Finished version 1.0 by Lam Ho on 08/04/14.
//

/*
 This string resource manager class provides:
 - Get/Set default language
 - Get string with a providing language
 - Get string with the default language
 - Init language code array, language data dictionary path array, default language
 */

#ifndef __GameXtension__StringResource__
#define __GameXtension__StringResource__

#include <string>
#include "cocos2d.h"
#include "SSMacros.h"
#include <unordered_map>

NS_SS_BEGIN

USING_NS_CC;
using namespace std;

enum class LanguageType {
    UNDEFINED = -1,
    ENGLISH,
    ARABIC,
    CZECH,
    DUTCH,
    FINNISH,
    FRENCH,
    GERMAN,
    GREEK,
    HEBREW,
    HINDI,
    HUNGARIAN,
    INDONESIA,
    ITALIAN,
    JAPANESE,
    KOREAN,
    MALAYSIA,
    NORWEGIAN,
    POLISH,
    PORTUGUESE,
    ROMMANIA,
    RUSSIAN,
    CHINESE,
    SPANISH,
    SWEDISH,
    THAI,
    TURKISH,
    UKRAINIA,
    VIETNAMESE,
    LANGUAGE_TYPE_COUNT,
};

static const char* LANGUAGE_CODES[(int)LanguageType::LANGUAGE_TYPE_COUNT] = {
    "en",   // ENGLISH
    "ar",   // ARABIC
    "cs",  	// CZECH
    "nl",  	// DUTCH
    "fi",   // FINNISH
    "fr",   // FRENCH
    "de",   // GERMAN
    "el",   // GREEK
    "he",   // HEBREW
    "hi",   // HINDI
    "hu",   // HUNGARIAN
    "id",   // INDONESIA
    "it",   // ITALIAN
    "ja",   // JAPANESE
    "ko",	// KOREAN
    "ms",	// MALAYSIA
    "nb",   // NORWEGIAN
    "pl",   // POLISH
    "pt",   // PORTUGUESE
    "ro",   // ROMMANIA
    "ru",   // RUSSIAN
    "zh",   // CHINESE
    "es",   // SPANISH
    "sv",   // SWEDISH
    "th",   // THAI
    "tr",   // TURKISH
    "uk",   // UKRAINIA
    "vi"    // VIETNAMESE
};

class StringManager: public cocos2d::Ref {

public:
    static StringManager* getInstance();
    
    //Get/Set default language
    CC_SYNTHESIZE_READONLY(senspark::LanguageType, _defaultLanguage, DefaultLanguage);
    void setDefaultLanguage(senspark::LanguageType defaultLanguage);

    virtual void setDefaultLanguageCode(const string& langCode);
    virtual string getDefaultLanguageCode() {
        return _defaultLanguageCode;
    }
    
    // Get string with a providing language
    const string getString(const string &key, const string &langCode);
    const string getString(const string &key, senspark::LanguageType langType);
    
    // Check if support language
    bool isSupportLanguage(senspark::LanguageType type);
    
    // Get string with the default language
    const string getString(const string &key);
    
    // Init language code array, language data dictionary path array, default language
    int init(const char **langCodes, const char** dictionaryPaths, const char* defaultLangCode);
    int init(std::vector<senspark::LanguageType> langTypes, senspark::LanguageType defaultLangType);
    int init(senspark::LanguageType defaultLangType);

    static string getLangCode(senspark::LanguageType langType);
    static senspark::LanguageType getLangType(string langCode);
    
CC_CONSTRUCTOR_ACCESS:
    StringManager() {};
    virtual ~StringManager() {
        _dictionaries.clear();
    }
private:
    
    std::unordered_map<std::string,ValueMap> _dictionaries;
    string _defaultLanguageCode;
};

NS_SS_END

#endif /* defined(__GameXtension__StringResource__) */
