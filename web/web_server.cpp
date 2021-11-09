#ifndef WEBSERVER_CPP
#define WEBSERVER_CPP
#include "web/web_server.h"
#include "log/log.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <assert.h>
#include <iostream>
#include <thread>

WebServer::WebServer(const char *ip, int port, Eigen::MatrixXcd fade){
    LInfo("=========server start==========");
    ip_ = ip;
    port_ = port;
    pool_ = new ThreadPool(5);
    mat_control_ = MatrixControl::getMatrixControl();
    stc_control_ = STCControl::getSTCControl();
    fade_ = fade;
    epoller_ = new Epoller();
    initEventMode();
    initSocket();
}

WebServer::~WebServer(){
    shutdown(listenFd_,SHUT_RDWR);
    delete pool_;
}

void WebServer::start() {
    int timeMS = -1;  /* epoll wait timeout == -1 无事件将阻塞 */
    while(true) {
        int eventCnt = epoller_->wait(0);
        for(int i = 0; i < eventCnt; i++) {
            int fd = epoller_->getEventFd(i);
            uint32_t events = epoller_->getEvents(i);
            if(fd == listenFd_) {
                dealListen();
            }
            else if(events & EPOLLIN) {
                dealRead(fd);
            }
            else if(events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {
                closeConn(fd);
            }
            else {
                ;
            }
        }
    }
}

Eigen::MatrixXi WebServer::deModulateSTC(std::string mat_str){
    auto b = mat_control_->stringToMatrixXcd(mat_str,1,2);
    return stc_control_->dataDeModulate(8,b,fade_);
}

void WebServer::initEventMode() {
    listenEvent_ = EPOLLRDHUP | EPOLLET;
    connEvent_ = EPOLLONESHOT | EPOLLRDHUP | EPOLLET;
}

void WebServer::addClient(int fd, sockaddr_in addr) {
    assert(fd > 0);
    epoller_->addFd(fd, EPOLLIN | connEvent_);
    setFdNonblock(fd);
}

void WebServer::closeConn(int fd) {
    epoller_->delFd(fd);
    close(fd);
}

void WebServer::dealRead(int fd) {
    pool_->addTask([fd,this](){
        char buff[1024];
        memset(buff , '\0',sizeof buff);
        int len = recv(fd,buff,1024,0);
        if(len != 0){
            std::string str = buff, answer;
            Eigen::MatrixXcd psk_data = mat_control_->stringToMatrixXcd(str,1,2);
            std::cout<<"receive data which cross fade channel : \n" << psk_data<<"\n";
            Eigen::MatrixXi &&mat =stc_control_->dataDeModulate(8,psk_data,fade_).adjoint();
            answer = mat_control_->matrixXiToString(mat);
            std::cout<<"receive std : " + answer<<"\n";
            LCritical("receive stc : " + answer);
        }
        closeConn(fd);
    });
}

void WebServer::dealListen() {
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    do {
        int fd = accept(listenFd_, (struct sockaddr *)&addr, &len);
        if(fd <= 0) { return;}
        LCritical("get a connect : " + std::to_string(fd));
        addClient(fd, addr);
    } while(listenEvent_ & EPOLLET);
}

bool WebServer::initSocket() {
    int ret;
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port_);

    struct linger optLinger = { 0 };
    optLinger.l_onoff = 1;
    optLinger.l_linger = 1;
    listenFd_ = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenFd_ >= 0);

    ret = setsockopt(listenFd_, SOL_SOCKET, SO_LINGER, &optLinger, sizeof(optLinger));
    assert(ret >= 0);

    int optval = 1;
    ret = setsockopt(listenFd_, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));
    assert(ret != -1);

    ret = bind(listenFd_, (struct sockaddr *)&addr, sizeof(addr));
    assert(ret >= 0);

    ret = listen(listenFd_, 6);
    assert(ret >= 0);

    ret = epoller_->addFd(listenFd_,  listenEvent_ | EPOLLIN);
    assert(ret != 0);

    setFdNonblock(listenFd_);
    return true;
}

int WebServer::setFdNonblock(int fd) {
    assert(fd > 0);
    return fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0) | O_NONBLOCK);
}
#endif // !WEBSERVER_CPP
