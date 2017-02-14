//
//  ProjectManifestReader_Apple.hpp
//  cocos2d_libs
//
//  Created by gumin on 2016/11/22.
//
//

#ifndef ProjectManifestReader_Apple_hpp
#define ProjectManifestReader_Apple_hpp

#include <stdio.h>
#include "BaiyouPlugin.h"

namespace baiyou {
    class BaiyouPlugin_Apple : public BaiyouPlugin{
        ~BaiyouPlugin_Apple();
        std::string getProperty(const std::string& key) const;
        std::string getUUID() const;
        void restart() const;
        bool init();
        std::string getBundleId() const;
        void setIdleTimerDisabled(bool) const;
        void scheduleLocalNotification(const std::string& title,const std::string& content,int delay) const;
        void unScheduleAllLocalNotification() const;
    };
}

#endif /* ProjectManifestReader_Apple_hpp */
