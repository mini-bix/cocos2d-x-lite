//
//  SDKCenter.cpp
//  cocos2d_libs
//
//  Created by gumin on 2017/5/4.
//
//

#include "SDKCenter.h"
#include "cocos2d.h"

#if TARGET_OS_IOS
#include "SDK_GameCenter.h"
#endif

namespace baiyou {
    
    SDKCenter* SDKCenter::s_instance = nullptr;
    
    SDKCenter* SDKCenter::getInstance(){
        if (s_instance == nullptr){
            s_instance = new SDKCenter();
        }
        return s_instance;
    }
    
    SDKCenter::SDKCenter():userResultListener(nullptr)
    {
        
    }
    
    SDKCenter::~SDKCenter(){
    }
    
    bool SDKCenter::init(const std::vector<int> &pluginIds){
        for (int i=0;i<pluginIds.size();i++){
            int pluginId = pluginIds[i];
            SDK_Common *sdk = nullptr;
            switch (pluginId) {
                case SDKPluginCode::GameCenter:
                #if TARGET_OS_IOS
                    sdk = new SDK_GameCenter();
                    sdk->init();
                #endif
                    break;
                default:
                    break;
            }
            if (sdk){
                this->plugins[pluginId] = sdk;
            }else{
                CCLOG("SDK not Implemented %d",pluginId);
            }
        }
        return true;
    }
    
    void SDKCenter::setUserResultListener(UserResultListener *listener){
        this->userResultListener = listener;
    }
    
    void SDKCenter::Login(const int &pluginId){
        auto pIt = this->plugins.find(pluginId);
        if (pIt == this->plugins.end()){
            CCLOG("Login SDK not Found %d",pluginId);
            return;
        }
        pIt->second->Login([=](const LoginResult &result)->void{
            switch (result.errorCode) {
                case 0:
                {
                    auto userInfo = new SDKUserInfo();
                    userInfo->setUserId(result.uid);
                    userInfo->setUserName(result.name);
                    userInfo->setAlias(result.alias);
                    this->userInfos[pluginId] = userInfo;
                    this->userResultListener->onUserResult(pluginId, 0, "LoginSucc");
                }
                break;
                default:
                    this->userResultListener->onUserResult(pluginId, result.errorCode, "LoginFailed");
                break;
            }
        });
    }
    
    void SDKCenter::Logout(const int &pluginId){
        
    }
    
    void SDKCenter::Pay(const int &pluginId){
        
    }
    
    SDKUserInfo* SDKCenter::getUserInfo(const int &pluginId){
        auto pIt = this->userInfos.find(pluginId);
        if (pIt == this->userInfos.end()){
            return nullptr;
        }else{
            return pIt->second;
        }
    }
    
}
