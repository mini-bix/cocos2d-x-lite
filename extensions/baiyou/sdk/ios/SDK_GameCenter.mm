//
//  SDK_GameCenter.m
//  cocos2d_libs
//
//  Created by gumin on 2017/5/4.
//
//

#import <Foundation/Foundation.h>
#include "SDK_GameCenter.h"
#import <GameKit/GameKit.h>

namespace baiyou {
    
    SDK_GameCenter::~SDK_GameCenter(){
        
    }
    
    bool SDK_GameCenter::init(){
        return true;
    }
    
    void SDK_GameCenter::Login(LoginCallback callback){
        GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
        if ([localPlayer isAuthenticated]){
            LoginResult result;
            result.errorCode = 0;
            result.uid = [localPlayer playerID];
            result.name = [localPlayer displayName];
            result.channel = "GameCenter";
            callback(result);
        }else{
            localPlayer.authenticateHandler = ^(UIViewController *viewController, NSError *error) {
                LoginResult result;
                if (error){
                    result.errorCode = 1;
                }else{
                    result.errorCode = 0;
                    result.uid = [localPlayer playerID];
                    result.name = [localPlayer displayName];
                    result.channel = "GameCenter";
                }
                callback(result);
            };
        }
    }
    
    void SDK_GameCenter::Logout(){
        
    }
    
    void SDK_GameCenter::Pay(){
        
    }
}

