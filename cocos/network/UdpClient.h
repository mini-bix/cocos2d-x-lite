//
//  UdpClient.hpp
//  cocos2d_libs
//
//  Created by gumin on 2017/5/24.
//
//

#ifndef UdpClient_h
#define UdpClient_h

#include <stdio.h>
#include <string>
#include "platform/CCPlatformMacros.h"
#include "platform/CCStdC.h"
#include <thread>
#include <vector>
#include <mutex>

NS_CC_BEGIN

namespace network {
    
    class CC_DLL UdpClient {
        
    public:
        enum class ErrorCode
        {
            TIME_OUT,           /** &lt; value 0 */
            CONNECTION_FAILURE, /** &lt; value 1 */
            UNKNOWN,            /** &lt; value 2 */
        };
        
        struct Data
        {
            Data(char* _bytes,ssize_t _len):bytes(_bytes), len(_len){}
            char* bytes;
            ssize_t len;
        };
        
        class Delegate
        {
        public:
            virtual ~Delegate() {}

            virtual void onOpen(UdpClient* uc) = 0;

            virtual void onBinary(UdpClient* uc, const Data& data) = 0;

            virtual void onClose(UdpClient* uc) = 0;

            virtual void onError(UdpClient* uc, const ErrorCode& error) = 0;
        };
        
        
    public:
        
        UdpClient();
        
        virtual ~UdpClient();
        
        int Connect(std::string addr);
        
        ssize_t Write(const void *buf, size_t nbyte);
        
        void Close();
        
        void onReceivedData(const Data& data);
        
        void setDelegate(Delegate *_delegate);
        
    private:
        
        void receiveThreadMain();
    public:
        void update(float dt);
        
    private:
        int sockfd;
        std::thread *recvThread;
        Delegate *delegate;
        char *readbuf;
        std::vector<Data> dataList;
        std::mutex dataListMutex;
    };
}

NS_CC_END

#endif /* UdpClient_hpp */
