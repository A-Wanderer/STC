#ifndef WEBSERVER_H
#define WEBSERVER_H
#include "pool/thread_pool.h"
#include "stc/stc_control.h"
#include "stc/matrix_control.h"
#include "epoll/epoller.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
class WebServer
{
private:
    /* data */
    const char* ip_;

    int port_;

    sockaddr_in address_;

    ThreadPool* pool_;

    STCControl* stc_control_;

    MatrixControl* mat_control_;

    Eigen::MatrixXcd fade_;

    Epoller* epoller_;

    uint32_t listenEvent_;

    uint32_t connEvent_;

    int listenFd_;
public:
    WebServer(/* args */) = delete;

    WebServer(const char *p,int port,Eigen::MatrixXcd fade);

    ~WebServer();

    Eigen::MatrixXi deModulateSTC(std::string mat_str);

    void initEventMode();

    void addClient(int fd, sockaddr_in addr);

    void closeConn(int fd);

    void dealRead(int fd);

    void dealListen();

    bool initSocket();

    int setFdNonblock(int fd);

    void start();
};


#endif // !WEBSERVER_H
