//
//  SDK_AIYOUYUN.hpp
//  cocos2d_libs
//
//  Created by gumin on 2017/5/5.
//
//

#ifndef SDK_AIYOUYUN_h
#define SDK_AIYOUYUN_h

#include <stdio.h>

#include "SDK_Common.h"

namespace baiyou {
    
    class SDK_AIYOUYUN : public SDK_Common{
        
    public:
        
        bool init();
        
        void Login(std::function<void (const LoginResult&)>);
        
        void Logout();
        
        void Pay();
        
        bool handleURL(const char *);
        
        bool openURL(const char *);
        
        void OpenUserCenter();
        
    public:
        
        std::function<void (const LoginResult&)> _loginCallback;
        
        
    };
    
}

#endif /* SDK_AIYOUYUN_hpp */
