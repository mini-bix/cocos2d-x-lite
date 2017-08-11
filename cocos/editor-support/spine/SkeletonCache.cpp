//
//  SkeletonCache.cpp
//  cocos2d_libs
//
//  Created by gumin on 2017/5/20.
//
//

#include "SkeletonCache.h"
#include "spine/Cocos2dAttachmentLoader.h"
#include "spine/extension.h"
#include "spine/SkeletonJson.h"

namespace spine {

SkeletonCache* instance = NULL;

SkeletonCache * SkeletonCache::getInstance(){
    if (instance == NULL){
        instance = new SkeletonCache();
    }
    return instance;
}

SkeletonCache::SkeletonCache(){
    
}

SkeletonCache::~SkeletonCache(){
    
}

spAtlas* SkeletonCache::getAtlas(const std::string& atlasFile){
    spAtlas *atlas = NULL;
    auto it = this->cachedAtlas.find(atlasFile);
    if (it != this->cachedAtlas.end()){
        atlas = it->second;
    }
    if (!atlas){
        atlas = spAtlas_createFromFile(atlasFile.c_str(), 0);
        atlas->retainCount++;
        this->cachedAtlas[atlasFile] = atlas;
    }
    return atlas;
}
    
bool has_suffix(const std::string &str, const std::string &suffix)
{
    std::size_t index = str.find(suffix, str.size() - suffix.size());
    return (index != std::string::npos);
}

spSkeletonData* SkeletonCache::getSkeletonData(const std::string& skeletonDataFile, const std::string& atlasFile, float scale){
    
    std::ostringstream stringStream;
    stringStream << skeletonDataFile;
    stringStream << ",";
    stringStream << atlasFile;
    stringStream << ";";
    stringStream << scale;
    
    std::string key = stringStream.str();
    
    spSkeletonData *skeletonData = NULL;
    auto it = this->cachedSkeletonData.find(key);
    if (it != this->cachedSkeletonData.end()){
        skeletonData = it->second;
    }
    if (!skeletonData){
        auto _atlas = SkeletonCache::getInstance()->getAtlas(atlasFile);
        CCASSERT(_atlas, "Error reading atlas file.");
        auto _attachmentLoader = SUPER(Cocos2dAttachmentLoader_create(_atlas));
        if (has_suffix(skeletonDataFile, ".skel")){
            spSkeletonBinary* binary = spSkeletonBinary_createWithLoader(_attachmentLoader);
            binary->scale = scale;
            skeletonData = spSkeletonBinary_readSkeletonDataFile(binary, skeletonDataFile.c_str());
            CCASSERT(skeletonData, binary->error ? binary->error : "Error reading skeleton data file.");
            spSkeletonBinary_dispose(binary);
        }else{
            spSkeletonJson* json = spSkeletonJson_createWithLoader(_attachmentLoader);
            json->scale = scale;
            skeletonData = spSkeletonJson_readSkeletonDataFile(json, skeletonDataFile.c_str());
            CCASSERT(skeletonData, json->error ? json->error : "Error reading skeleton data file.");
            spSkeletonJson_dispose(json);
        }
        skeletonData->retainCount++;
        this->cachedSkeletonData[key] = skeletonData;
    }
    return skeletonData;
}

void SkeletonCache::removeUnusedAssets(){
    for (auto it =  this->cachedAtlas.begin();it!= this->cachedAtlas.end();){
        if (it->second->retainCount == 1){
            CCLOG("remove unused Spine Atlas %s",it->first.c_str());
            spAtlas_dispose(it->second);
            this->cachedAtlas.erase(it++);
        }else{
            it++;
        }
    }
    for (auto it =  this->cachedSkeletonData.begin();it!= this->cachedSkeletonData.end();){
        if (it->second->retainCount == 1){
            CCLOG("remove unused Spine SkeletonData %s",it->first.c_str());
            spSkeletonData_dispose(it->second);
            this->cachedSkeletonData.erase(it++);
        }else{
            it++;
        }
    }
}
    
void SkeletonCache::removeAll(){
    for (auto it =  this->cachedAtlas.begin();it!= this->cachedAtlas.end();it++){
        spAtlas_dispose(it->second);
    }
    for (auto it =  this->cachedSkeletonData.begin();it!= this->cachedSkeletonData.end();it++){
        spSkeletonData_dispose(it->second);
    }
    this->cachedAtlas.clear();
    this->cachedSkeletonData.clear();
}

}
