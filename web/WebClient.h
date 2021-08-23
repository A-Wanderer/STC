#ifndef WebClient_H
#define WebClient_H
#include <sys/socket.h>
#include <netinet/in.h>
class WebClient
{
private:
    /* data */
    const char* ip_;
    int port_;
    int sockfd_;
    sockaddr_in server_address_;
public:
    WebClient(/* args */) = delete;
    WebClient(const char *ip,int port);
    ~WebClient();
    void prepare();
    void sendMsg(std::string msg);
};

#endif // !WebClient