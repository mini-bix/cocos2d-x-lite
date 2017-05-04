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
        
        ~SDK_GameCenter();
        
        bool init();
        
        void Login(LoginCallback callback);
        
        void Logout();
        
        void Pay();
        
    };
    
}


#endif /* SDK_GameCenter_h */
