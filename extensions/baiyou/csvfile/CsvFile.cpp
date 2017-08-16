//
//  CsvFile.cpp
//  cocos2d_libs
//
//  Created by meng yao on 2017/8/16.
//
//

#include "CsvFile.h"
#include "platform/CCFileUtils.h"
namespace baiyou {
    void split(const std::string& s,std::string delim,std::vector<std::string>& ret)
    {
        size_t last = 0;
        size_t index = s.find_first_of(delim,last);
        while(index != std::string::npos)
        {
            ret.push_back(s.substr(last,index-last));
            last= index+1;
            index = s.find_first_of(delim,last);
        }
        
        ret.push_back(s.substr(last));
        
    }
    std::vector<std::string> CsvFile::parsingByFile(const std::string &filename){
        
        std::string fileStr = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
        std::vector<std::string> fileLists;
        split(fileStr,"\n",fileLists);
        return fileLists;
        
    }
    
    void CsvFile::getBody(const std::string &fileStr,std::vector<std::string>& elems)
    {
        split(fileStr,"\t",elems);
    }
    
    std::vector<std::string> CsvFile::getHead(const std::string &fileStr)
    {
        std::vector<std::string> fileLists ;
        split(fileStr,"\t",fileLists);
        return fileLists;
    }
}
