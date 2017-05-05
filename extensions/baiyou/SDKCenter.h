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
#include <string>
#include <vector>
#include <map>
#include "sdk/SDK_Common.h"

namespace baiyou {
    
    typedef enum {
        GameCenter = 0,
    } SDKPluginCode;
    
    typedef enum {
        LoginSucc = 0,
        LoginFail,
        Logout,
    } UserResultCode;
    
    class UserResultListener
    {
    public:
        virtual void onUserResult(int ,int , const char* ) = 0;
    };
    
    class SDKUserInfo{
    public:
        inline std::string getUserId(){
            return _userId;
        }
        inline void setUserId(const std::string &value){
            _userId = value;
        }
        
        inline std::string getUserName(){
            return _userName;
        }
        inline void setUserName(const std::string &value){
            _userName = value;
        }
        
        inline std::string getAlias(){
            return _alias;
        }
        inline void setAlias(const std::string &value){
            _alias = value;
        }
    private:
        std::string _userId;
        std::string _userName;
        std::string _alias;
    };
    
    class SDKCenter {
        
    public:
        
        SDKCenter();
        
        ~SDKCenter();
        
        static SDKCenter* getInstance();
        
        bool init(const std::vector<int> &);
        
        void setUserResultListener(UserResultListener *);
        
        void Login(const int &);
        
        void Logout(const int &);
        
        void Pay(const int &);
        
        SDKUserInfo* getUserInfo(const int &);
        
    protected:
        
        static SDKCenter* s_instance;
        
        std::map<int,SDK_Common*> plugins;
        
        std::map<int,SDKUserInfo*> userInfos;
        
        UserResultListener * userResultListener;
        
    };
}

#endif /* SDKCenter_hpp */
