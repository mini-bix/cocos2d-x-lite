//
//  SDK_Common.h
//  cocos2d_libs
//
//  Created by gumin on 2017/5/4.
//
//

#ifndef SDK_Common_h
#define SDK_Common_h

namespace baiyou {
    
    typedef struct _LoginResult{
        int errorCode;
        std::string uid;
        std::string channel;
        std::string name;
    } LoginResult;
    
    typedef void LoginCallback(const LoginResult &);
    
    class SDK_Common {
        
    public:
        virtual ~SDK_Common() = 0;
        
        virtual bool init() = 0;
        
        virtual void Login(LoginCallback callback) = 0;
        
        virtual void Logout() = 0;
        
        virtual void Pay() = 0;
        
    };
    
}


#endif /* SDK_Common_h */
