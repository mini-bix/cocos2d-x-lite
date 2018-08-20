//
//  CsvFile.cpp
//  cocos2d_libs
//
//  Created by meng yao on 2017/8/16.
//
//

#include "CsvFile.h"
#include "platform/CCFileUtils.h"
#include <sstream>
namespace baiyou {
//    bool js_isNum(const std::string& str)
//    {
//        std::stringstream sin(str);
//        double d;
//        char c;
//        if(!(sin >> d))
//            return false;
//        if (sin >> c)
//            return false;
//        return true;
//    }
    void CsvFile::split(const std::string& s,std::string delim,std::vector<std::string>& ret)
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
    void CsvFile::parsingByFile(const std::string &filename,std::string& jsonStr){
        
        std::string fileStr = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);
        std::vector<std::string> fileLists;
        split(fileStr,"\r",fileLists);
        
        parsingCsvToJsonSting(fileLists,jsonStr);
        
    }
    void  CsvFile::parsingCsvToJsonSting(std::vector<std::string> csv,std::string& jsonStr)
    {
        if (csv.empty()) {
            return ;
        }
        std::vector<std::string>::iterator csvIter = csv.begin();
        std::vector<std::string> head = getHead((*csvIter));
        if (head.empty()) {
            return ;
        }
        jsonStr = "[";

        std::vector<std::string> body;
        body.resize(head.size());
        csvIter++;
        while (csvIter != csv.end()) {
            body.clear();
            getBody((*csvIter),body);
            csvIter++;
            if (body.empty() || body.size() != head.size()) {
                CCLOG("size of line not match head size %s",(*csvIter).c_str());
                continue;
            }
            jsonStr += "{";
            std::vector<std::string>::iterator headIter = head.begin();
            std::vector<std::string>::iterator bodyIter = body.begin();
            while(headIter != head.end() && bodyIter != body.end()) {
               
                jsonStr += "\"" + (*headIter) + "\": " + (*bodyIter);
               
                headIter++;
                bodyIter++;
                if (headIter != head.end() && bodyIter != body.end()) {
                    jsonStr += ",";
                }
            }
           
            if (csvIter != csv.end()) {
                jsonStr += "},";
            }else{
                jsonStr += "}";
            }
        }
        jsonStr += "]";
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