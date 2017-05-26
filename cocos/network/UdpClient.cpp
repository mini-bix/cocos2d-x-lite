//
//  UdpClient.cpp
//  cocos2d_libs
//
//  Created by gumin on 2017/5/24.
//
//

#include "UdpClient.h"
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "cocos2d.h"

#define BUFFERLENGTH 1024*1024

NS_CC_BEGIN

namespace network {
    
    UdpClient::UdpClient() :recvThread(nullptr),sockfd(0),delegate(nullptr),zipEnabled(false){
        readbuf = (char *)malloc(BUFFERLENGTH);
    }
    
    UdpClient::~UdpClient(){
        Close();
        free(readbuf);
        if (recvThread){
            CC_SAFE_DELETE(recvThread);
        }
    }
    
    void UdpClient::setZipEnabled(bool _zip){
        zipEnabled = _zip;
    }
    
    int UdpClient::Connect(std::string addr){
        if (sockfd > 0){
            printf("UDPClient Already Connected");
            return -5;
        }
        size_t sepIndex = addr.find(":");
        if (sepIndex == std::string::npos){
            return -1;
        }
        std::string host_str = addr.substr(0,sepIndex);
        std::string port_str = addr.substr(sepIndex+1);
        
        int port = atoi(port_str.c_str());
        
        struct hostent *hostEnt = gethostbyname(host_str.c_str());
        if (hostEnt == NULL){
            return -2;
        }
        struct sockaddr_in servaddr;
        memset(&servaddr,0x00,sizeof(servaddr));
        if (hostEnt->h_addrtype == AF_INET){
            servaddr.sin_port = htons(port);
            servaddr.sin_family=AF_INET;
            memcpy(&servaddr.sin_addr, hostEnt->h_addr_list[0], sizeof(servaddr.sin_addr));
            printf( "resolved to %s:%d", inet_ntoa(servaddr.sin_addr),servaddr.sin_port);
        }else{
            printf("IPV6 Not Support Yet");
            return -3;
        }
        
        if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
        {
            printf("socketfd create error \r\n");
            return -4;
        }
        
        if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))==0)
        {
            printf("connect success\r\n");
        }else{
            if (this->delegate){
                this->delegate->onError(this,ErrorCode::CONNECTION_FAILURE);
            }
            return -6;
        }
        
        recvThread = new std::thread(&UdpClient::receiveThreadMain,this);
        
        Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
        
        if (this->delegate){
            this->delegate->onOpen(this);
        }
        return 0;
    }
    
    ssize_t UdpClient::Write(const void *buf, size_t nbyte){
        return write(sockfd, buf, nbyte);
    }
    
    void UdpClient::onReceivedData(const Data& data){
        if (delegate){
            delegate->onMessage(this, data);
        }
    }
    
    void UdpClient::receiveThreadMain(){
        while (sockfd >0) {
            ssize_t readed = read(sockfd, readbuf, BUFFERLENGTH);
            if (readed <0){
                continue;
            }
            char *copy = (char*)malloc(readed);
            memcpy(copy, readbuf, readed);
            dataListMutex.lock();
            dataList.push_back(Data(copy,readed,false));
            dataListMutex.unlock();
        }
        
    }
    
    void UdpClient::setDelegate(Delegate *_delegate){
        this->delegate = _delegate;
    }
    
    void UdpClient::Close(){
        if (sockfd > 0){
            close(sockfd);
            sockfd = 0;
        }
        if (recvThread && recvThread->joinable()){
            recvThread->join();
        }
        Director::getInstance()->getScheduler()->unscheduleUpdate(this);
        if (this->delegate){
            this->delegate->onClose(this);
        }
    }
    
    void UdpClient::update(float dt){
        if (dataListMutex.try_lock()){
            if (!dataList.empty()){
                for (int i=0;i<dataList.size();i++){
                    Data& data = dataList[i];
                    onReceivedData(data);
                    free(data.bytes);
                }
                dataList.clear();
            }
            dataListMutex.unlock();
        }
    }
    
    
}

NS_CC_END
