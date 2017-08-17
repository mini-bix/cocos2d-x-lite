//
//  CsvFile.hpp
//  cocos2d_libs
//
//  Created by meng yao on 2017/8/16.
//
//

#ifndef CsvFile_hpp
#define CsvFile_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include "cocos2d.h"
namespace baiyou {
	class CC_DLL CsvFile{
    public:
        CsvFile(){};
        virtual ~CsvFile(){};
    public:
        static void parsingByFile(const std::string& filename,std::string& jsonStr);
        static void parsingCsvToJsonSting(std::vector<std::string> csv,std::string& jsonStr);
        static std::vector<std::string> getHead(const std::string& fileStr);
        static void getBody(const std::string& fileStr,std::vector<std::string>& elems);
        static void split(const std::string& s,std::string delim,std::vector<std::string>& ret);
    };
}
#endif /* CsvFile_hpp */
