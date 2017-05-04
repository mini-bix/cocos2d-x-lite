//
//  SDKCenter.cpp
//  cocos2d_libs
//
//  Created by gumin on 2017/5/4.
//
//

#include "SDKCenter.h"
#include "cocos2d.h"
#include "SDK_GameCenter.h"

namespace baiyou {
    
    SDKCenter* SDKCenter::s_instance = nullptr;
    
    SDKCenter* SDKCenter::getInstance(){
        if (s_instance == nullptr){
            s_instance = new SDKCenter();
        }
        return s_instance;
    }
    
    bool SDKCenter::init(const std::vector<int> &pluginIds){
        for (int i=0;i<pluginIds.size();i++){
            int pluginId = pluginIds[i];
            SDK_Common *sdk = nullptr;
            switch (pluginId) {
                case SDKPlugin::GameCenter:
                    sdk = new SDK_GameCenter();
                    sdk->init();
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
    
    void SDKCenter::Login(const int &sdkName){
        
    }
    
    void SDKCenter::Logout(const int &sdkName){
        
    }
    
    void SDKCenter::Pay(const int &sdkName){
        
    }
}
