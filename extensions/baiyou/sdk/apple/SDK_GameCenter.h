//
//  SDK_GameCenter.h
//  cocos2d_libs
//
//  Created by gumin on 2017/5/4.
//
//

#ifndef SDK_GameCenter_h
#define SDK_GameCenter_h
#include "SDK_Common.h"

namespace baiyou {
    
    class SDK_GameCenter : public SDK_Common{
        
    public:
        
        bool init();
        
        void Login(std::function<void (const LoginResult&)>);
        
        void Logout();
        
        void Pay();
        
    };
    
}


#endif /* SDK_GameCenter_h */
