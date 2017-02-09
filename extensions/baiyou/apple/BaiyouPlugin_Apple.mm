//
//  ProjectManifestReader_Apple.cpp
//  cocos2d_libs
//
//  Created by gumin on 2016/11/22.
//
//

#include "BaiyouPlugin_Apple.h"

#import "KeyChainStore.h"

#define KEY_UUID @"COM.AIYOU.DAOKEDAOZHIFANRENXIUXIAN.UUID"

namespace baiyou {
    
    BaiyouPlugin_Apple::~BaiyouPlugin_Apple(){
        
    }
    
    BaiyouPlugin* BaiyouPlugin::getInstance(){
        if (s_sharedBaiyouPlugin == nullptr)
        {
            s_sharedBaiyouPlugin = new (std::nothrow) BaiyouPlugin_Apple();
            if(!s_sharedBaiyouPlugin->init())
            {
                delete s_sharedBaiyouPlugin;
                s_sharedBaiyouPlugin = nullptr;
                NSLog(@"cocos2dx ERROR: Could not init BaiyouPlugin");
            }
        }
        return s_sharedBaiyouPlugin;
    }
    
    bool BaiyouPlugin_Apple::init(){
        return true;
    }
    std::string BaiyouPlugin_Apple::getProperty(const std::string& key) const{
        NSString* str = [[NSBundle mainBundle] objectForInfoDictionaryKey:[NSString stringWithUTF8String:key.c_str()]];
        if (str == NULL){
            return "";
        }else{
            return std::string(str.UTF8String);
        }
    }
    
    void BaiyouPlugin_Apple::restart() const{
    }
    
    std::string BaiyouPlugin_Apple::getUUID() const{
        NSString * strUUID = (NSString *)[KeyChainStore load:KEY_UUID];
        
        //首次执行该方法时，uuid为空
        if ([strUUID isEqualToString:@""] || !strUUID)
        {
            //生成一个uuid的方法
            CFUUIDRef uuidRef = CFUUIDCreate(kCFAllocatorDefault);
            
            strUUID = (NSString *)CFBridgingRelease(CFUUIDCreateString (kCFAllocatorDefault,uuidRef));
            
            //将该uuid保存到keychain
            [KeyChainStore save:KEY_UUID data:strUUID];
            
        }
        return std::string([strUUID UTF8String]);
    }
    
    std::string BaiyouPlugin_Apple::getBundleId() const{
        NSString *bundleIdentifier = [[NSBundle mainBundle] bundleIdentifier];
        return std::string(bundleIdentifier.UTF8String);
    }
    
    void BaiyouPlugin_Apple::setIdleTimerDisabled(bool dis) const{
#if TARGET_OS_IOS
        [[UIApplication sharedApplication] setIdleTimerDisabled:dis];
#endif
    }
}
