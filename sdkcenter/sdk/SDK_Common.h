//
//  SDK_Common.h
//  cocos2d_libs
//
//  Created by gumin on 2017/5/4.
//
//

#ifndef SDK_Common_h
#define SDK_Common_h
#include <string>
#include <functional>

namespace baiyou {
    
    typedef struct _LoginResult{
        int errorCode;
        std::string uid;
        std::string channel;
        std::string name;
        std::string alias;
        bool isGuest;
    } LoginResult;
    
    
    class SDK_Common {
        
    public:
        
        std::function<void (void)> logoutCallback;
        
        virtual bool init() = 0;
        
        virtual void Login(std::function<void (const LoginResult&)>) = 0;
        
        virtual void Logout() = 0;
        
        virtual void Pay() = 0;
        
        virtual bool handleURL(const char *) = 0;
        
        virtual bool openURL(const char *) = 0;
        
        virtual void OpenUserCenter() = 0;
        
    };
    
}


#endif /* SDK_Common_h */
