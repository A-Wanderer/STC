#ifndef WEBSERVER_CPP
#define WEBSERVER_CPP
#include "WebServer.h"
#include "pool/thread_pool.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <assert.h>
#include <iostream>
#include <thread>

WebServer::WebServer(const char *ip, int port){
    ip_ = ip;
    port_ = port;
    pool_ = new ThreadPool(5);
}

WebServer::~WebServer(){
    shutdown(sockfd_,SHUT_RDWR);
    delete pool_;
}

void WebServer::prepare(){
    bzero(&address_,sizeof address_);
    address_.sin_family = AF_INET;
    address_.sin_port = htons(port_);
    inet_pton(PF_INET,ip_,&address_.sin_addr);

    int sockfd = socket(PF_INET,SOCK_STREAM,0);
    assert(sockfd >= 0);
    sockfd_  = sockfd;
}

void WebServer::work(){
    int ret = bind(sockfd_,(sockaddr*)&address_,sizeof address_);
    ret = listen(sockfd_,20);
    assert(ret != -1);

    sockaddr_in client;
    socklen_t client_len = sizeof client;
    while(true){
        int conn = accept(sockfd_,(sockaddr*)&client,&client_len);
        if(conn < 0){
            std::cout << "failed" << std::endl;
        }
        else{
            pool_->addTask([conn](){
                char buff[1024];
                memset(buff , '\0',sizeof buff);
                int len = recv(conn,buff,1024,0);
                if(len != 0)
                    std::cout << buff << std::endl;
            });
        }
    }
}

#endif // !WEBSERVER_CPP
