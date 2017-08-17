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
        static std::vector<std::string> parsingByFile(const std::string& filename);
        static std::vector<std::string> getHead(const std::string& fileStr);
        static void getBody(const std::string& fileStr,std::vector<std::string>& elems);
        
    };
}
#endif /* CsvFile_hpp */
