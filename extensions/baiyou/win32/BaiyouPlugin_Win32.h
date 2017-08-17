//
//  ProjectManifestReader_Apple.hpp
//  cocos2d_libs
//
//  Created by gumin on 2016/11/22.
//
//

#ifndef BaiyouPlugin_Win32_hpp
#define BaiyouPlugin_Win32_hpp

#include <stdio.h>
#include "../BaiyouPlugin.h"
#include "cocos2d.h"
namespace baiyou {
    class CC_DLL BaiyouPlugin_Win32 : public BaiyouPlugin{
		~BaiyouPlugin_Win32();
        std::string getProperty(const std::string& key) const;
        std::string getUUID() const;
        void restart() const;
        bool init();
        std::string getBundleId() const;
        std::string getBundleVersion() const;
        std::string getDeviceInfo() const;
        void setIdleTimerDisabled(bool) const;
        void scheduleLocalNotification(const std::string& title,const std::string& content,int delay) const;
        void unScheduleAllLocalNotification() const;
    };
}

#endif /* BaiyouPlugin_Win32_hpp */
