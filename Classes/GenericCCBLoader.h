//
//  GenericCCBLoader.h
//  GameXtension
//
//  Created by greewoo on 6/12/16.
//
//

#ifndef GenericCCBLoader_h
#define GenericCCBLoader_h

template<class Object_Type, class Base_Loader_Type> class GenericCCBLoader: public Base_Loader_Type {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GenericCCBLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Object_Type);
};

#endif /* GenericCCBLoader_h */
