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
    
    BaiyouPlugin::~BaiyouPlugin(){
        
    }
    std::string BaiyouPlugin::getProperty(const std::string& key) const{
        return "";
    }
    void BaiyouPlugin::restart() const{}
    void BaiyouPlugin::openURL(const std::string& url) const{
        cocos2d::Application::getInstance()->openURL(url);
    }
    bool BaiyouPlugin::init(){
        return true;
    }
    
}
