//
//  SDKCenter.hpp
//  cocos2d_libs
//
//  Created by gumin on 2017/5/4.
//
//

#ifndef SDKCenter_h
#define SDKCenter_h

#include <stdio.h>
#include "SDK_Common.h"
namespace baiyou {
    
    typedef enum {
        GameCenter = 0,
    } SDKPlugin;
    
    class SDKCenter {
        
    public:
        static SDKCenter* getInstance();
        
        bool init(const std::vector<int> &pluginIds);
        
        void Login(const int &sdkName);
        
        void Logout(const int &sdkName);
        
        void Pay(const int &sdkName);
        
    protected:
        
        static SDKCenter* s_instance;
        
        std::map<int,SDK_Common*> plugins;
        
    };
}

#endif /* SDKCenter_hpp */
