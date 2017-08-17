//
//  ProjectManifestReader_Apple.cpp
//  cocos2d_libs
//
//  Created by gumin on 2016/11/22.
//
//

#include "BaiyouPlugin_Win32.h"


namespace baiyou {
    
	BaiyouPlugin_Win32::~BaiyouPlugin_Win32(){
        
    }
    
    BaiyouPlugin* BaiyouPlugin::getInstance(){
        if (s_sharedBaiyouPlugin == nullptr)
        {
			s_sharedBaiyouPlugin = new (std::nothrow) BaiyouPlugin_Win32();
            if(!s_sharedBaiyouPlugin->init())
            {
                delete s_sharedBaiyouPlugin;
                s_sharedBaiyouPlugin = nullptr;
            }
        }
        return s_sharedBaiyouPlugin;
    }
    
	bool BaiyouPlugin_Win32::init(){
        return true;
    }
	std::string BaiyouPlugin_Win32::getProperty(const std::string& key) const{
		return "";
    }
    
	void BaiyouPlugin_Win32::restart() const{
    }
    
	std::string BaiyouPlugin_Win32::getUUID() const{
		return "";
    }
    
	std::string BaiyouPlugin_Win32::getBundleId() const{
		return "com.cocos.apps.simulator";
    }
    
	void BaiyouPlugin_Win32::setIdleTimerDisabled(bool dis) const{
    }
    
	void BaiyouPlugin_Win32::scheduleLocalNotification(const std::string& title, const std::string& content, int delay) const{
    }
    
	void BaiyouPlugin_Win32::unScheduleAllLocalNotification() const{
    }
    
	std::string BaiyouPlugin_Win32::getBundleVersion() const{
		return "";
    }
	std::string BaiyouPlugin_Win32::getDeviceInfo() const{
		return "{}";
    }
    
}
