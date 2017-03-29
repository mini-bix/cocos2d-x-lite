//
//  ProjectManifestReader.cpp
//  cocos2d_libs
//
//  Created by gumin on 2016/11/22.
//
//

#include "BaiyouPlugin.h"
#include "CCApplication.h"

namespace baiyou {
    BaiyouPlugin* BaiyouPlugin::s_sharedBaiyouPlugin = nullptr;
    
    bool _anySdkUserInitFinished;
    
    BaiyouPlugin::~BaiyouPlugin(){
        
    }
    std::string BaiyouPlugin::getProperty(const std::string& key) const{
        return "";
    }
    void BaiyouPlugin::restart() const{}
    void BaiyouPlugin::openURL(const std::string& url) const{
        cocos2d::Application::getInstance()->openURL(url);
    }
    std::string BaiyouPlugin::getUUID() const{
        return "";
    }
    bool BaiyouPlugin::init(){
        return true;
    }
    
    std::string BaiyouPlugin::getBundleId() const{
        return "";
    }
    
    void BaiyouPlugin::setIdleTimerDisabled(bool) const{
        
    }
    
    void BaiyouPlugin::scheduleLocalNotification(const std::string& title,const std::string& content,int delay) const{
        
    }
    
    void BaiyouPlugin::unScheduleAllLocalNotification() const{
        
    }
    
    bool BaiyouPlugin::GetAnySDKUserInitFinished(){
        return _anySdkUserInitFinished;
    }
    void BaiyouPlugin::SetAnySDKUserInitFinished(bool finished){
        _anySdkUserInitFinished = finished;
    }
    
}
