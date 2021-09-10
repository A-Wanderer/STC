#ifndef WebClient_CPP
#define WebClient_CPP

#include "web/web_client.h"
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <iostream>

WebClient::WebClient(const char* ip,int port){
    ip_ = ip;
    port_ = port;
}

WebClient::~WebClient(){
    shutdown(sockfd_,SHUT_RDWR);
}

void WebClient::prepare(){
    bzero(&server_address_,sizeof server_address_);
    server_address_.sin_family = AF_INET;

    inet_pton(AF_INET, ip_, &server_address_.sin_addr);
    server_address_.sin_port =htons(port_);

    int sockfd = socket(PF_INET,SOCK_STREAM,0);
    assert(sockfd >= 0);
    sockfd_ = sockfd;
}

void WebClient::sendMsg(std::string msg){
    if(connect(sockfd_,(sockaddr*)&server_address_,sizeof server_address_) < 0){
        std::cout << "failed" << std::endl;
    }
    else{
        const char *msg_ptr = msg.c_str();
        send(sockfd_,msg_ptr,strlen(msg_ptr),0);
    }

}

#endif