//
//  SkeletonCache.hpp
//  cocos2d_libs
//
//  Created by gumin on 2017/5/20.
//
//

#ifndef SkeletonCache_h
#define SkeletonCache_h

#include <stdio.h>

#include "cocos2d.h"
#include "spine/spine.h"
#include <map>

namespace spine {

    class SkeletonCache : public cocos2d::Ref{
public:
    
    static SkeletonCache * getInstance();
    
    SkeletonCache();
    
    virtual ~SkeletonCache();
    
    spAtlas* getAtlas(const std::string& atlasFile);
    
    spSkeletonData* getSkeletonData(const std::string& skeletonDataFile, const std::string& atlasFile, float scale);
    
    void removeUnusedAssets();
    
private:
    std::map<std::string,spAtlas*> cachedAtlas;
    
    std::map<std::string,spSkeletonData*> cachedSkeletonData;
};

}

#endif /* SkeletonCache_hpp */
