#ifndef WEBSERVER_H
#define WEBSERVER_H
#include "pool/thread_pool.h"
#include <sys/socket.h>
#include <arpa/inet.h>
class WebServer
{
private:
    /* data */
    const char* ip_;
    int port_;
    sockaddr_in address_;
    int sockfd_;
    ThreadPool* pool_;
public:
    WebServer(/* args */) = delete;
    WebServer(const char *p,int port);
    ~WebServer();
    void prepare();
    void work();
};


#endif // !WEBSERVER_H
