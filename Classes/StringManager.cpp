//
// StringManager.cpp
// GameXtension
//
// Created by Duc Nguyen on 11/28/12.
//
//

#include "StringManager.h"

NS_SS_BEGIN

StringManager* _instance = NULL;

StringManager* StringManager::getInstance() {
    if (_instance == NULL) {
        _instance = new StringManager();
    }
    return _instance;
}

int StringManager::init(const char **langCodes, const char** dictionaryPaths, const char* defaultLangCode) {
    setDefaultLanguageCode(defaultLangCode);

    for (int i=0; langCodes[i]!=NULL; i++) {
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(dictionaryPaths[i]);
        if (dict.size() > 0) {
            _dictionaries[langCodes[i]] = dict;
            log("Support language %s", langCodes[i]);
        } else {
            log("Not support language %s", langCodes[i]);
        }
    }
  
    CCLOG("Language count = %ld", _dictionaries.size());
    
    return (int) _dictionaries.size();
}

int StringManager::init(std::vector<senspark::LanguageType> langTypes, senspark::LanguageType defaultLangType) {
    setDefaultLanguageCode(getLangCode(defaultLangType));
    
    for (auto langType : langTypes) {
        ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(StringUtils::format("%s.lproj/strings.plist", LANGUAGE_CODES[int(langType)]));
        _dictionaries[getLangCode(langType)] = dict;
        if (dict.size() > 0) {
            _dictionaries[getLangCode(langType)] = dict;
            log("Support language %s", getLangCode(langType).c_str());
        } else {
            log("Not support language %s", getLangCode(langType).c_str());
        }
    }
    CCLOG("Language count = %ld", _dictionaries.size());
    return (int) _dictionaries.size();
}

int StringManager::init(senspark::LanguageType defaultLangType)
{
    setDefaultLanguageCode(getLangCode(defaultLangType));
    
    for(int i = (int)senspark::LanguageType::UNDEFINED + 1; i < (int)senspark::LanguageType::LANGUAGE_TYPE_COUNT; i++)
    {
        string strFileName = string(LANGUAGE_CODES[i]) + ".lproj/strings.plist";
        if (FileUtils::getInstance()->isFileExist(strFileName))
        {
            ValueMap dict = FileUtils::getInstance()->getValueMapFromFile(strFileName);
            _dictionaries[getLangCode((senspark::LanguageType)i)] = dict;
            log("Support language %s", getLangCode((senspark::LanguageType)i).c_str());
        }
        else
        {
            log("Not support language %s", getLangCode((senspark::LanguageType)i).c_str());
        }
    }
    
    log("Language count = %ld", _dictionaries.size());
    return (int) _dictionaries.size();
}

void StringManager::setDefaultLanguage(senspark::LanguageType defaultLanguage)
{
    _defaultLanguage        = defaultLanguage;
    _defaultLanguageCode    = getLangCode(defaultLanguage);
}

bool StringManager::isSupportLanguage(senspark::LanguageType type)
{
    // check if has data for a language
    return (_dictionaries.count(getLangCode(type)) > 0);
}

void StringManager::setDefaultLanguageCode(const string &langCode) {
    _defaultLanguageCode = langCode;
    _defaultLanguage = getLangType(langCode);
}

const string StringManager::getString(const string &key, const string &langCode)
{
    // return value
    string strValue     = "";
    string strLangCode  = langCode;
    std::string defaultLangCode = "en";
    
    // check if exist input language data
    if (_dictionaries.count(strLangCode) == 0)
    {
        strLangCode     = getDefaultLanguageCode();
    }
    
    // recheck again
    if (_dictionaries.count(strLangCode) > 0)
    {
        // check exist key
        if(_dictionaries[strLangCode].count(key) > 0)
        {
            strValue    = _dictionaries[strLangCode][key].asString();
        } else if (_dictionaries[defaultLangCode].count(key) > 0) {
            strValue = _dictionaries[defaultLangCode][key].asString();
        }
    }

    return strValue;
}

const string StringManager::getString(const string &key, senspark::LanguageType langType) {
    return getString(key, getLangCode(langType));
}

const string StringManager::getString(const string &key) {
    return getString(key, _defaultLanguage);
}

string StringManager::getLangCode(senspark::LanguageType langType) {
    return LANGUAGE_CODES[int(langType)];
}

senspark::LanguageType StringManager::getLangType(string langCode) {
    for (int i = 0; i < int(senspark::LanguageType::LANGUAGE_TYPE_COUNT); i++) {
        if (langCode.compare(LANGUAGE_CODES[i]) == 0) {
            return senspark::LanguageType(i);
        }
    }
    return senspark::LanguageType::UNDEFINED;
}

NS_SS_END
